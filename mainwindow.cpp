#include "mainwindow.h"
#include <QMessageBox>
#include <QtMath>


MainWindow::MainWindow(QWidget*  parent )
   : QGraphicsView(parent),
     scene { new QGraphicsScene(this) },
     willBeDragged { false },
     itemsVec {},
     currentItem { nullptr },
     figureIndex {}
{

   this->setMinimumSize(500, 600);

   setScene(scene);

   scene->addItem(createNewItem(QPoint(0, 0)));
}

MainWindow::~MainWindow()
{
    for (auto &item : scene->items())
    {
        //Вот это делать было необязательно:
        scene->removeItem(item);

        //Цикл обхода сцены затевался только
        //ради такого действа:
        delete item;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{


    //------------ При нажатии правой кнопки на итеме удаляем его ---------------
    //----------------------------- Begin: --------------------------------------

    if (mouseEvent->button() == Qt::RightButton)
    {
        if (!onEmptyPlaceClicked(mouseEvent))
        {
            //Если клик - не на пустом месте, то currentItem должен
            //содержать не-NULL-значение
            assert (currentItem != nullptr);

            removeOneItem(currentItem);
            currentItem = nullptr;
        }

        return;
    }

    //----------------------End of нажатии правой.-------------------------------

    if (mouseEvent->button() != Qt::LeftButton)
        return;


    //----- При нажатии левой кнопки на пустом месте создаём новый итем --------
    //----------------------------- Begin: -------------------------------------

    if (onEmptyPlaceClicked(mouseEvent))
    {
        assert(currentItem == nullptr);

        QGraphicsItem *veryShortLifePointerThatOnlyNeedsForAssertBelow
            { createNewItem(mapToScene(mouseEvent->pos())) };

        assert(veryShortLifePointerThatOnlyNeedsForAssertBelow != nullptr);

        return;
    }

    //--------------End of нажатие левой на пустом месте.------------------------

    //----- При зажимании левой кнопки на итеме захватываем его -----------------
    //------------------------------ Begin: -------------------------------------

    else // !onEmptyPlaceclicked
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));

        currentItem = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());

        willBeDragged = true;
    }

    //-------------------- End of нажатие левой на итеме. ------------------------
}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{

    if (!willBeDragged)
        return;

    //----- При отпускании левой кнопки переносим итем на место курсора ----------
    //------------------------------ Begin: --------------------------------------

    if (mouseEvent->button() == Qt::LeftButton)
    {

        this->setCursor(QCursor(Qt::ArrowCursor));

        currentItem->setPos(mapToScene(mouseEvent->pos()));
        willBeDragged = false;
        currentItem = nullptr;
    }

    //-------------- End of отпускание левой кнопки мыши. -------------------------

    else //Релизнута какая-то другая кнопка
            return;
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (!willBeDragged)
        return;

    assert(currentItem != nullptr);

    currentItem->setPos(mapToScene(mouseEvent->pos()));
}

//Если false, то currentItem будет содержать адрес на
//QGraphicsItem в куче, иначе - nullptr
bool MainWindow::onEmptyPlaceClicked(QMouseEvent *mouseEvent)
{
    //Присвоение адреса на итем переменной-указателю currentItem
    //есть побочный продукт работы данной функции
    currentItem = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());

    if (currentItem == nullptr)
        return true;

    return false;
}

QGraphicsItem *MainWindow::createNewItem(const QPointF point)
{
    QBrush brush;
    brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    //"Красный" - значит "красивый" xD
    QPen pen(QColor("red"));

    QGraphicsItem *newItem;

    switch (figureIndex)
     {
    case 0: //Прямоугольник
     {
        QGraphicsRectItem *rectItem =
            new QGraphicsRectItem(point.x(), point.y(), 70, 80);

        rectItem->setPen(pen);
        rectItem->setBrush(brush);

        newItem = rectItem;

        break;
     }
    case 1: //Эллипс
     {
        QGraphicsEllipseItem *ellipseItem =
            new QGraphicsEllipseItem(point.x(), point.y(), 70, 80);

        ellipseItem->setPen(pen);
        ellipseItem->setBrush(brush);

        newItem = ellipseItem;

        break;
     }
    case 2: //Пятиконечная звезда
     {
        qreal X = point.x();
        qreal Y = point.y();
        qreal sz = 50; //размер звезды

        QPointF p1{ X, Y - sz };
        QPointF p2 { X + sz * qSin(M_PI/5), Y + sz * qCos(M_PI/5) };

        QPointF p3 { X + sz * qSin(M_PI/5), Y + sz * qCos(M_PI/5) };
        QPointF p4 { X - sz * qCos(M_PI/10), Y - sz * qSin(M_PI/10) };

        QPointF p5 { X - sz * qCos(M_PI/10), Y - sz * qSin(M_PI/10) };
        QPointF p6 { X + sz * qCos(M_PI/10), Y - sz * qSin(M_PI/10) };

        QPointF p7 { X+ sz * qCos(M_PI/10), Y - sz * qSin(M_PI/10) };
        QPointF p8 { X - sz * qSin(M_PI/5), Y + sz * qCos(M_PI/5) };

        QPointF p9 { X - sz * qSin(M_PI/5), Y + sz * qCos(M_PI/5) };
        QPointF p10 { X, Y - sz };

        QPolygonF polygon;
        polygon << p1 << p2 << p3 << p4 << p5 << p6 << p7 << p8 << p9 << p10;

        QGraphicsPolygonItem *starItem = new QGraphicsPolygonItem (polygon);

        starItem->setPen(pen);
        starItem->setBrush(brush);

        newItem = starItem;

        break;
     }
    default:
     {
    //    qDebug() << "How did u managed get here?";
        break;
     }

    }

    itemsVec.push_back(newItem);

    scene->addItem(newItem);

    figureIndex++;

    if (figureIndex > 2)   // У нас только три модели фигуры,
          figureIndex = 0; // поэтому заходим на новый круг

    return newItem;
}

void MainWindow::removeOneItem(QGraphicsItem *item)
{
    if (!item) //nullptr
        return;

    assert(itemsVec.size() == scene->items().count());

    itemsVec.removeOne(item);

    scene->removeItem(item);

    delete item;
}

void MainWindow::wheelEvent(QWheelEvent *wheelEvent)
{
    QGraphicsItem *graphicsItem {
        scene->itemAt(mapToScene(wheelEvent->pos()),
            QTransform()) };

    if (graphicsItem == nullptr)
        return;

    qreal measure { 0.5 };

    if ((wheelEvent->delta()) > 0 )
        graphicsItem->setScale(measure);

    else
        graphicsItem->setScale(1 / measure);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    QPointF cursorPosition =
        mapToScene(mapFromGlobal(QCursor::pos()));

    QGraphicsItem *graphicsItem {
        scene->itemAt(cursorPosition,
            QTransform()) };

    if (graphicsItem == nullptr)
        return;

    qreal measure { 0.5 };

    if (keyEvent->key() == Qt::Key_Minus)
        graphicsItem->setScale(measure);

    else if (keyEvent->key() == Qt::Key_Plus)
        graphicsItem->setScale(1 / measure);
}

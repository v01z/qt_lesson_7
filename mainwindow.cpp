#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
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

    qDebug () << "***********Deleting vector elements ***";
    qDebug() << "Vec size is: " << itemsVec.size();

    for (auto &item : itemsVec)
    {

        qDebug () << item;

        itemsVec.removeOne(item);

        qDebug() << "Vec after deleting element is: " << itemsVec.size();
        qDebug() << "Vec's count is: " << itemsVec.count();
    }

    //иногда вектор весь не очищается. вернёмся сюда позже
    qDebug() << "Vec size after deleting all elements is: " << itemsVec.size();

    for (const auto &elem : itemsVec)
        qDebug () << elem;

    qDebug () << "***********Deleting scene's elements ***";
    qDebug() << "Scene has items: " << scene->items().count();

    for (auto &item : scene->items())
    {

        qDebug() << "Removing from scene item: " << item;
        scene->removeItem(item);

        delete item;
    }

    qDebug() << "Scene has items now: " << scene->items().count();

    //Лишний код
    if (scene)
        delete scene;
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{


    //------------ При нажатии правой кнопки на итеме удаляем его. Begin:---------

    if (mouseEvent->button() == Qt::RightButton)
    {
//        if (!onEmptyPlaceClicked(mouseEvent) && items(mouseEvent->pos()).size() > 0)
        if (!onEmptyPlaceClicked(mouseEvent))
        {
            //Если не на пустом месте, то currentItem должен содержать valid-значение
            assert (currentItem != nullptr);

            qDebug() << currentItem;

            removeOneItem(currentItem);
            currentItem = nullptr;
            assert(currentItem == nullptr); //debug only
        }

        return;
    }

    //-----------End of нажaтии правой -------------------------------------------

    if (mouseEvent->button() != Qt::LeftButton)
        return;


    //----- При нажатии левой кнопки на пустом месте создаём новый итем. Begin:-

    if (onEmptyPlaceClicked(mouseEvent))
    {
        assert(currentItem == nullptr);
        assert(createNewItem(mapToScene(mouseEvent->pos())) != nullptr);

        return;
    }

    //-----------End of нажатие левой  ------------------------------------------

    //----- При зажимании левой кнопки на итеме захватываем его. Begin:-

    else // !onEmptyPlaceclicked
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        currentItem = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
        willBeDragged = true;
    }

    //-----------End of нажатие левой  ------------------------------------------
}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{

    if (!willBeDragged)
        return;

    //----- При отпускании левой кнопки переносим итем на место курсора-------
    if (mouseEvent->button() == Qt::LeftButton)
    {

        this->setCursor(QCursor(Qt::ArrowCursor));

        currentItem->setPos(mapToScene(mouseEvent->pos()));
        willBeDragged = false;
        currentItem = nullptr;
    }

    else //Релизнута какая-то другая кнопка
            return;

}

//I will use this func to rotate items, если будет свободное время
void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (!willBeDragged)
        return;

    assert(currentItem != nullptr);

    currentItem->setPos(mapToScene(mouseEvent->pos()));
}

//Если false, то будет currentItem будет valid, иначе currentItem будет nullptr
bool MainWindow::onEmptyPlaceClicked(QMouseEvent *mouseEvent)
{
    //Получение currentItem есть побочный продукт данной функции
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

    QPen pen(QColor("red"));

    QGraphicsItem *newItem;

    switch (figureIndex)
    {
    case 0:
    {
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(point.x(), point.y(),
                                70, 80);
        rectItem->setPen(pen);
        rectItem->setBrush(brush);
        newItem = rectItem;
        break;
    }
    case 1:
    {
        QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem(point.x(), point.y(),
                                70, 80);
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
        qDebug() << "How did u managed get here?";
        break;
    }
    }

    itemsVec.push_back(newItem);

    qDebug() << "Added new element: " << newItem;
    qDebug() << "Vec size is now: " << itemsVec.size();

    scene->addItem(newItem);

    figureIndex++;

    if (figureIndex > 2)
     figureIndex = 0;

    return newItem;
}

void MainWindow::removeOneItem(QGraphicsItem *item)
{
    if (!item) //nullptr
        return;

    assert(itemsVec.size() == scene->items().count());

    qDebug() << "+++++ Removing one element from vector +++++";
    qDebug() << "Vector size before is: " << itemsVec.size();

    itemsVec.removeOne(item);

    qDebug() << "Vector size after is: " << itemsVec.size();
    qDebug () << '\n';

    qDebug() << "***** Removing one element from scene*****";
    qDebug() << "Scene itmes count before is: " << scene->items().count();

    scene->removeItem(item);

    qDebug() << "Scene items count after isis: " << scene->items().count();
    qDebug () << '\n';

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

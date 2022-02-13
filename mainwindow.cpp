#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget*  parent )
   : QGraphicsView(parent),
     scene { new QGraphicsScene(this) },
     willBeDragged { false },
     itemsVec {},
     currentItem { nullptr }
{

   this->setMinimumSize(500, 600);

   setScene(scene);


   QGraphicsEllipseItem *firstItem = (QGraphicsEllipseItem*)createNewItem(QPoint(0, 0));

   scene->addItem(firstItem);


}

MainWindow::~MainWindow()
{
    qDebug() << "Destructor of MainWindow called";
    /*
    if (ellipseItem)
        delete ellipseItem;
        */

    qDebug () << "***********Deleting vector elements ***";
    qDebug() << "Vec size is: " << itemsVec.size();
    for (auto &item : itemsVec)
    {

        qDebug () << item;
        itemsVec.removeOne(item);
//        delete item;
        qDebug() << "vec after deleting element is: " << itemsVec.size();
        qDebug() << "vec count is: " << itemsVec.count();
    }

    //иногда вектор весь не очищается. вернёмся сюда позже
    qDebug() << "Vec size after deleteng all is: " << itemsVec.size();
//        delete item;

    qDebug() << "scene has items: " << scene->items().count();
    for (auto &item : scene->items())
    {

        qDebug() << "Removing from scene item: " << item;
        scene->removeItem(item);
    }
    qDebug() << "scene has items now: " << scene->items().count();

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

        currentItem = createNewItem(mapToScene(mouseEvent->pos()));

        return;
    }

    //-----------End of нажатие левой  ------------------------------------------

    //----- При зажимании левой кнопки на итеме захватываем его. Begin:-

    else // !onEmptyPlaceclicked
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        currentItem = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
        willBeDragged = true; //заменить на currentItem == or != nullptr
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
        willBeDragged = false; ////заменить на currentItem == or != nullptr
        currentItem = nullptr;
    }

    else //Релизнута какая-то другая кнопка
            return;

}

//for rotate too
void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    //if (currentItem == nullptr)
    if (!willBeDragged)
        return;

    assert(currentItem != nullptr);

    currentItem->setPos(mapToScene(mouseEvent->pos()));
}

//Если false, то будет содержать currentItem, иначе currentItem будет nullptr
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

   QGraphicsEllipseItem *newItem = new QGraphicsEllipseItem(point.x(), point.y(),
                                                            70, 80);
   if (!newItem)
       return nullptr;

   QBrush brush;
   brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
   brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать


   newItem->setPen(QPen(QColor("red")));
   newItem->setBrush(brush);

   itemsVec.push_back(newItem);
   qDebug() << "Added new element: " << newItem;
   qDebug() << "Vec size is now: " << itemsVec.size();
   scene->addItem(newItem);

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
    item = nullptr;
}

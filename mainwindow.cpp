#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget*  parent )
   : QGraphicsView(parent),
     scene { new QGraphicsScene(this) },
     itemIsUnderMouse { false },
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
    if (ellipseItem)
        delete ellipseItem;

    for (auto &item : itemsVec)
        delete item;
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{


    //------------ При нажатии правой кнопки на итеме удаляем его. Begin:---------

    if (mouseEvent->button() == Qt::RightButton)
    {
        if (!onEmptyPlaceClicked(mouseEvent) && items(mouseEvent->pos()).size() > 0)
        {
            //delete item
            // getItemUsingPosition
            QGraphicsItem *item = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
//            QGraphicsItem *item = scene->itemAt(mouseEvent->pos(), QTransform());
            //debug
            if (item == nullptr)
            {
                qDebug() << "is nullptr on mouse press event";
                return;
            }
            qDebug() << item;
            scene->removeItem(item);
            //vector.at[remove]
            qDebug() << "vec size before: " << itemsVec.size();
            //itemsVec.erase(std::find_if(itemsVec.begin(), itemsVec.end(),[&item](QGraphicsItem *elem){
            //capture all. потому вернуть строчку выше (полсе дебб)
            itemsVec.erase(std::find_if(itemsVec.begin(), itemsVec.end(),[&](QGraphicsItem *elem){

               //return elem == item;
                elem = item;
                qDebug() << elem;
                qDebug() << itemsVec.size();
                return elem;
            }));

            qDebug() << "vec size after: " << itemsVec.size();
            qDebug() << "hrere"; //itemIsUnderMouse intercepts this
            delete item;

        }

        return;
    }

    //-----------End of нажтии правой -------------------------------------------

    if (mouseEvent->button() != Qt::LeftButton)
        return;


    //----- При нажатии левой кнопки на пустом месте создаём новый итем. Begin:-

    if (onEmptyPlaceClicked(mouseEvent))
    {
//        itemsVec.push_back(new QGraphicsItem()); //create func that creat item in turn
        //createNewItem(mapToScene(mouseEvent->pos()));
        //debug
        //if (createNewItem(mouseEvent->pos()) == nullptr)
        if ((currentItem = createNewItem(mapToScene(mouseEvent->pos()))) == nullptr)
        {
            qDebug() << "is nullptr inside mousePress and creating new item";
        }
        return;
        //end debug
    }

    //-----------End of нажатие левой  ------------------------------------------

    //----- При зажимании левой кнопки на итеме захватываем его. Begin:-

    else // !onEmptyPlaceclicked
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        currentItem = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
        itemIsUnderMouse = true; //заменить на currentItem == or != nullptr
    }

    //-----------End of нажатие левой  ------------------------------------------
}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{

        qDebug() << "getting here";
    if (!itemIsUnderMouse)
    {
        //func() that creates new item (or mb move it to MainWindow::on_click ?)
        return;
    }

    //----- При отпускании левой кнопки переносим итем на место курсора-------
    //if (mouseEvent->button() == Qt::LeftButton)
    if (mouseEvent->button() == Qt::LeftButton && currentItem != nullptr)
    {

        this->setCursor(QCursor(Qt::ArrowCursor));

        //QGraphicsItem *item = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
//        QGraphicsEllipseItem *item = (QGraphicsEllipseItem*)scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
//        assert (item != nullptr);
        //debug
        /*
        if (item == nullptr)
        {
            qDebug() << "is nullptr inside realeased mouse button";
            return;
        }
        */
        //end debug
        currentItem->setPos(mapToScene(mouseEvent->pos()));
        itemIsUnderMouse = false; ////заменить на currentItem == or != nullptr
        currentItem = nullptr;
    }
    /*
    else
        if (mouseEvent->button() == Qt::RightButton && items(mouseEvent->pos()).size() > 0)
        {
//         //
        }
        */
    else
            return;


}

//for rotate too
void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (currentItem == nullptr)
        return;

    currentItem->setPos(mapToScene(mouseEvent->pos()));
    /*
    if (!itemIsUnderMouse)
        return;
    //QGraphicsItem *item = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
    QGraphicsEllipseItem*item = (QGraphicsEllipseItem*)(scene->itemAt(mapToScene(mouseEvent->pos()), QTransform()));
    //QGraphicsItem *item = scene->itemAt(mouseEvent->pos(), QTransform());
    //QGraphicsEllipseItem*item = (QGraphicsEllipseItem*)scene->itemAt(mouseEvent->pos(), QTransform());
    //debug
    if (item == nullptr)
    {
        qDebug() << "is nullptr inside moveEvent";
        return;
    }
    //end debug

    item->setPos(mapToScene(mouseEvent->pos()));
    */
}

bool MainWindow::onEmptyPlaceClicked(QMouseEvent *mouseEvent) const
{
    if (items(mouseEvent->pos()).size() < 1)
        return true;

    return false;
}

//const QGraphicsItem *MainWindow::createNewItem(const QPoint point)
//const QGraphicsItem *MainWindow::createNewItem(const QPointF point)
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

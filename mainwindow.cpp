#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget*  parent )
   : QGraphicsView(parent),
     scene { new QGraphicsScene(this) },
     itemIsUnderMouse { false },
     itemsVec {}
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


    if (mouseEvent->button() == Qt::RightButton)
    {
        if (!onEmptyPlaceClicked(mouseEvent) && items(mouseEvent->pos()).size() > 0)
        {
            //delete item
            // getItemUsingPosition
            QGraphicsItem *item = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
            //debug
            if (item == nullptr)
            {
                qDebug() << "is nullptr on mouse press event";
                return;
            }
            scene->removeItem(item);
            //vector.at[remove]
            qDebug() << "hrere"; //itemIsUnderMouse intercepts this
            delete item;

        }

        return;
    }

    if (mouseEvent->button() != Qt::LeftButton)
        return;

    if (onEmptyPlaceClicked(mouseEvent))
    {
//        itemsVec.push_back(new QGraphicsItem()); //create func that creat item in turn
        //createNewItem(mapToScene(mouseEvent->pos()));
        //debug
        if (createNewItem(mouseEvent->pos()) == nullptr)
        {
            qDebug() << "is nullptr inside mousePress and creating new item";
        }
        return;
        //end debug
    }

    this->setCursor(QCursor(Qt::ClosedHandCursor));

    itemIsUnderMouse = true;

}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
        qDebug() << "getting here";
    if (!itemIsUnderMouse)
    {
        //func() that creates new item (or mb move it to MainWindow::on_click ?)
        return;
    }

    if (mouseEvent->button() == Qt::LeftButton)
    {

        this->setCursor(QCursor(Qt::ArrowCursor));

        QGraphicsItem *item = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
//        assert (item != nullptr);
        //debug
        if (item == nullptr)
        {
            qDebug() << "is nullptr";
            return;
        }
        //end debug
        item->setPos(mapToScene(mouseEvent->pos()));
        itemIsUnderMouse = false;
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
    if (!itemIsUnderMouse)
        return;
    QGraphicsItem *item = scene->itemAt(mapToScene(mouseEvent->pos()), QTransform());
//    QGraphicsItem *item = scene->itemAt(mouseEvent->pos(), QTransform());
    //debug
    if (item == nullptr)
    {
        qDebug() << "is nullptr inside moveEvent";
        return;
    }
    //end debug

    item->setPos(mapToScene(mouseEvent->pos()));
}

bool MainWindow::onEmptyPlaceClicked(QMouseEvent *mouseEvent) const
{
    if (items(mouseEvent->pos()).size() < 1)
        return true;

    return false;
}

const QGraphicsItem *MainWindow::createNewItem(const QPoint point)
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
   scene->addItem(newItem);

   return newItem;
}

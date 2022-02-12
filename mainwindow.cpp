#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget*  parent )
   : QGraphicsView(parent),
     scene { new QGraphicsScene(this) },
     itemIsUnderMouse { false }
{

   this->setMinimumSize(500, 600);

   setScene(scene);

   ellipseItem = new QGraphicsEllipseItem(0, 0, 70, 80);
   ellipseItem->setPen(QPen(QColor("red")));
   QBrush brush;
   brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
   brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать
   ellipseItem->setBrush(brush);

   scene->addItem(ellipseItem);


}

MainWindow::~MainWindow()
{
    if (ellipseItem)
        delete ellipseItem;
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{

    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if (items(mouseEvent->pos()).size() < 1)
        return;

   qDebug() << "There are" << items(mouseEvent->pos()).size()
             << "items at position" << mapToScene(mouseEvent->pos());

    this->setCursor(QCursor(Qt::ClosedHandCursor));
    itemIsUnderMouse = true;

    qDebug() << "pressed";
}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if (!itemIsUnderMouse)
        return;

    this->setCursor(QCursor(Qt::ArrowCursor));

    ellipseItem->setPos(mapToScene(mouseEvent->pos()));
    itemIsUnderMouse = false;

}

//for rotate
void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    /*
    qDebug() << "mouse pos: " << mouseEvent->pos() <<
        " *** ellips pos: " << ellipseItem->pos();
        */

//    ellipseItem->setPos(mouseEvent->pos());
}

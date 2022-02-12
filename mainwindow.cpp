#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget*  parent )
//MainWindow::MainWindow(QWidget* /* parent */)
   : QGraphicsView(parent),
     scene { new QGraphicsScene(this) }
     //ellipseItem { new QGraphicsEllipseItem(this) }
//   : view ( new QGraphicsView(this))
{

//    view->setMinimumSize(500, 600);
//  scene = new QGraphicsScene(this);                      // Новая сцена
   this->setMinimumSize(500, 600);
 //  scence = new QGraphicsScene(view);                      // Новая сцена

   setScene(scene);
 //  scene->addRect(-300,0,300,300);                        // Добавляем

                                                           // прямоугольник
  // scene->addText("Текст через Graphics View Framework"); // Добавляем текст
   //scence->addEllipse(-50, -50, 100, 100);
   //scene->addEllipse(0, 0, 100, 100);

   ///******
   ///

   ellipseItem = new QGraphicsEllipseItem(0, 0, 70, 80);
   ellipseItem->setPen(QPen(QColor("red")));
   //ellipseItem->brush().setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
   QBrush brush;
   brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
   brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать
   ellipseItem->setBrush(brush);
   qDebug() << ellipseItem->brush();

   qDebug () << ellipseItem->rect();
   scene->addItem(ellipseItem);

}

MainWindow::~MainWindow()
{
    if (ellipseItem)
        delete ellipseItem;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//   event
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

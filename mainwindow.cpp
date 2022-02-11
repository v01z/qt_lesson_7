#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
   : QGraphicsView(parent)
{
   scence = new QGraphicsScene(this);                      // Новая сцена
   setScene(scence);
   scence->addRect(-300,0,300,300);                        // Добавляем
                                                           // прямоугольник
   scence->addText("Текст через Graphics View Framework"); // Добавляем текст
   scence->addEllipse(-50, -50, 100, 100);
}
MainWindow::~MainWindow()
{

}

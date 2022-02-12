#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QGraphicsItem>
//#include <QVector>
//#include "blockscheme.h"
#include <QGraphicsItem>

class MainWindow : public QGraphicsView
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();
private:
//   QGraphicsView *view;
   QGraphicsScene *scene;
   QGraphicsEllipseItem *ellipseItem;

protected:
   void mousePressEvent(QMouseEvent *event) override;
   void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
};

#endif // MAINWINDOW_H

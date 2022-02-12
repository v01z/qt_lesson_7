#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QVector>
#include <QGraphicsItem>
#include <QMouseEvent>

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
   bool itemIsUnderMouse;

protected:
   void mousePressEvent(QMouseEvent*) override;
   void mouseReleaseEvent(QMouseEvent*) override;
   void mouseMoveEvent(QMouseEvent*) override;

private slots:
};

#endif // MAINWINDOW_H

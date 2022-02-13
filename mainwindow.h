#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QGraphicsItem>
#include <QMouseEvent>


class MainWindow : public QGraphicsView
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();
private:
   QGraphicsScene *scene;
   bool willBeDragged;
   QVector<QGraphicsItem*> itemsVec;
   bool onEmptyPlaceClicked(QMouseEvent*);
   QGraphicsItem *createNewItem(const QPointF);
   void removeOneItem(QGraphicsItem*);
   QGraphicsItem *currentItem;
   size_t figureIndex;

protected:
   void mousePressEvent(QMouseEvent*) override;
   void mouseReleaseEvent(QMouseEvent*) override;
   void mouseMoveEvent(QMouseEvent*) override;
   void wheelEvent(QWheelEvent*) override;
   void keyPressEvent(QKeyEvent*) override;

private slots:
};

#endif // MAINWINDOW_H

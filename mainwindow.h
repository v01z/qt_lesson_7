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
//   QGraphicsView *view;
   QGraphicsScene *scene;
   QGraphicsEllipseItem *ellipseItem;
   bool itemIsUnderMouse;
   QVector<QGraphicsItem*> itemsVec;
   bool onEmptyPlaceClicked(QMouseEvent*) const;
   const QGraphicsItem *createNewItem(const QPoint);

protected:
   void mousePressEvent(QMouseEvent*) override;
   void mouseReleaseEvent(QMouseEvent*) override;
   void mouseMoveEvent(QMouseEvent*) override;

private slots:
};

#endif // MAINWINDOW_H

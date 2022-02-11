#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>

class MainWindow : public QGraphicsView
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = 0);
   ~MainWindow();
private:
   QGraphicsView *view;
   QGraphicsScene *scence;
protected:
private slots:
};

#endif // MAINWINDOW_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QToolBar>
#include <QKeyEvent>
#include <QMutableMapIterator>
#include <QMap>
#include "plane.h"
#include "shoot.h"

#include "enemy.h"


namespace Ui
{
    class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QToolBar *fileToolBar;
    QMap<int,Shoot*> *map;
    QMap<int,Enemy*> *enemymap;


protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void checkCollision();
    void removeDestroyed();
    void animate();
public slots:

private:
    Ui::Widget *ui;
    void createToolBar();
    Plane *plane;
    int timerId;
    bool gameOver;
    bool gameWon;
    int enemyCount;
    int shootCount;
    int SCORE;
    int escaped;
    bool paused;
    QTime xt;
    QTime n;

};

#endif // WIDGET_H

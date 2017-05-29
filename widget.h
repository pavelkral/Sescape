#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QToolBar>
#include <QKeyEvent>
#include <QMutableMapIterator>
#include <QMediaPlayer>
#include <QMediaPlaylist>
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
	QMediaPlayer * m_player;
	QMediaPlayer * m_player1;// Audio player
	QMediaPlaylist * m_playlist;
	QSet<int> pressedKeys;


protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
	bool eventFilter(QObject * obj, QEvent * event);
    void checkCollision();
    void removeDestroyed();
    void animate();
	void shoot();
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
	QTime sht;

};

#endif // WIDGET_H

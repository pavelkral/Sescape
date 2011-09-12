#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QImage>
#include <QRect>
#include <QTimer>
#include <QTime>

class Enemy : public QObject
{
    Q_OBJECT

public:

    Enemy(QObject *parent = 0);
    ~Enemy();

public:
   void resetState(int,int);
   void moveTop(int);
   void autoMove();
   void Destroyed();
   void setXDir(int);
   void setYDir(int);
   int getXDir();
   int getYDir();
   QRect getRect();
   QImage & getImage();
   bool destroyed;
   int irot;

private:
    int angle;
    int speed;
    int xdir;
    int ydir;
    int timerd;
    QTime xt;
    QTime n;
    QImage image;
    QRect rect;

protected:
  virtual void timerEvent(QTimerEvent *event);

};

#endif // ENEMY_H

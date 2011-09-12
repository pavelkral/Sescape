#include "enemy.h"
#include <QDebug>
#include <QObject>
#include <math.h>


Enemy::Enemy(QObject *parent)
    : QObject(parent)

{
    xdir = 0;
    ydir = 1;
    destroyed = FALSE;
    image.load(":images/enemy.png");
    rect = image.rect();
    timerd = startTimer(100);
    xt = QTime::currentTime();
    xt = QTime::currentTime().addSecs(1);
    irot = 1;
}
Enemy::~Enemy()
{
    killTimer(timerd);
    qDebug() << "Enemy deleted:" <<  "OK";
}

void Enemy::resetState(int x,int y)
{
  rect.moveTo(x,y);
}
void Enemy::autoMove()
{
  rect.translate(xdir, ydir);


}
void Enemy::Destroyed()
{
    image.load(":images/explo.png");
    destroyed=TRUE;
}
void Enemy::timerEvent(QTimerEvent *event)
{

    n = QTime::currentTime();
    if(xt > n){
       image.load(":images/enemy2.png");

    }
    if(xt < n){
        image.load(":images/enemy.png");
        xt = QTime::currentTime().addSecs(1);
    }
    /*
    if(irot == 1){
        image.load(":images/enemyr1.png");
    }
    if(irot == 2){
        image.load(":images/enemyr2.png");
   }
    if(irot == 3){
        image.load(":images/enemyr3.png");
    }
    if(irot == 4){
        image.load(":images/enemy.png");
        irot = 0;
      // qDebug() << "Rotation:" <<  irot;
    }
    irot++;
    */
}

QRect Enemy::getRect(){
  return rect;
}

QImage & Enemy::getImage(){
  return image;
}
void Enemy::moveTop(int top)
{
  rect.moveTop(top);
}

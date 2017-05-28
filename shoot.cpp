#include "shoot.h"
#include <QDebug>


Shoot::Shoot()
{
  xdir = 0;
  ydir = -1;
  destroyed = false;
  image.load(":images/shoot2.png");
  rect = image.rect();

}
Shoot::~Shoot()
{
   qDebug() << "Shoot deleted:" <<  "OK";
}

void Shoot::resetState(int x,int y)
{
    rect.moveTo(x,y);
}
void Shoot::autoMove()
{
    int x =  xdir;
    int y = -5 + ydir;
    rect.translate(x, y);

 }

void Shoot::Destroyed()
{
    destroyed=true;
}
QRect Shoot::getRect(){
   return rect;
}

QImage & Shoot::getImage(){
  return image;
}
void Shoot::moveTop(int top)
{
  rect.moveTop(top);
}

void Shoot::setXDir(int x)
{
  xdir = x;
}

void Shoot::setYDir(int y)
{
  ydir = y;
}

int Shoot::getXDir()
{
  return xdir;
}

int Shoot::getYDir()
{
  return ydir;
}





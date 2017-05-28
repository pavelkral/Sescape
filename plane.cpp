#include "plane.h"
#include <QDebug>

Plane::Plane(){

	image.load(":images/plane3.png");
    rect = image.rect();
    resetState();
  }
Plane::~Plane(){

qDebug() << "Plane deleted:" <<  "OK";

}
void Plane::moveLeft(int left){
if (rect.left() >= 2)
rect.moveTo(left, rect.top());
}

void Plane::moveRight(int right){
if (rect.right() <= 580)

  rect.moveTo(right, rect.top());

}

void Plane::resetState(){

rect.moveTo(200, 290);

}

QRect Plane::getRect(){

return rect;

}

QImage & Plane::getImage(){

return image;

}


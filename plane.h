#ifndef PLANE_H
#define PLANE_H

#include <QImage>
#include <QRect>

class Plane
{
public:
    Plane();
    ~Plane();

 public:
    void resetState();
    void moveLeft(int);
    void moveRight(int);
    QRect getRect();
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
};

#endif // PLANE_H

#ifndef SHOOT_H
#define SHOOT_H

#include <QImage>
#include <QRect>

class Shoot
{
public:
    Shoot();
    ~Shoot();

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

  private:
    int angle;
    int speed;
    int xdir;
    int ydir;
    bool stuck;
    QImage image;
    QRect rect;

};

#endif // SHOOT_H

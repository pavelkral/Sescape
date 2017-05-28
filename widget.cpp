#include <QImage>
#include <QDebug>
#include <QPixmap>
#include <QMutableMapIterator>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ui_widget.h"
#include "widget.h"
#include "shoot.h"
#include "plane.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Space Escape");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":images/sky.png")));
    this->setPalette(palette);
    plane = new Plane;
    map = new QMap<int,Shoot *>;
    enemymap = new QMap<int,Enemy *>;

    shootCount = 0;
    enemyCount = 0;
    SCORE = 0;
    escaped = 0;
    gameOver = false;
    gameWon = false;
    paused = false;
    xt = QTime::currentTime();
    xt = QTime::currentTime().addSecs( 2 );
    timerId = startTimer(30);
    qDebug() << "Game Started:" << xt ;
}

//...............................................................................................................


Widget::~Widget()
{
    QMap< int,Shoot *>::const_iterator i = map->constBegin();
    QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();

    while (i != map->constEnd()) {
     delete i.value();
         ++i;
     }
       while (e != enemymap->constEnd()) {
          delete  e.value();
              ++e;
          }

    enemymap->clear();
    delete enemymap;
    map->clear();
    delete map;
    delete plane;
    delete ui;
}

//...............................................................................................................


void Widget::createToolBar()
{
    fileToolBar = new QToolBar(this);
  //fileToolBar->addWidget(ui->label);
  //fileToolBar->addSeparator();
  //fileToolBar->addWidget(ui->label_2);
}

//...............................................................................................................


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (gameOver) {
      QFont font("Courier", 15, QFont::DemiBold);
      QFontMetrics fm(font);
      int textWidth = fm.width("Game Over");
      painter.setFont(font);
      int h = height();
      int w = width();
      painter.translate(QPoint(w/2, h/2));
      painter.drawText(-textWidth/2, 0, "Game Over");
      killTimer(timerId);
    }
    else if(gameWon) {
          QFont font("Courier", 15, QFont::DemiBold);
          QFontMetrics fm(font);
          int textWidth = fm.width("Victory");
          painter.setFont(font);
          int h = height();
          int w = width();
          painter.translate(QPoint(w/2, h/2));
          painter.drawText(-textWidth/2, 0, "Victory");
          killTimer(timerId);
    }

    else{
        painter.drawImage(plane->getRect(),plane->getImage());
        QMap< int,Shoot *>::const_iterator i = map->constBegin();
        QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();

        while (i != map->constEnd()) {
                 painter.drawImage(i.value()->getRect(),
                     i.value()->getImage());
             ++i;
         }
        while (e != enemymap->constEnd()) {
          painter.drawImage(e.value()->getRect(),
                  e.value()->getImage());
            ++e;
          }
    }
    if(paused) {
             QFont font("Courier", 15, QFont::DemiBold);
             QFontMetrics fm(font);
             int textWidth = fm.width("Paused");
             painter.setFont(font);
             int h = height();
             int w = width();
             painter.translate(QPoint(w/2, h/2));
             painter.drawText(-textWidth/2, 0, "Paused");
             killTimer(timerId);
       }


}

//...............................................................................................................


void Widget::timerEvent(QTimerEvent *event)
{
    ui->label_3->setText(QString("SCORE %1").arg(SCORE));
    ui->label_4->setText(QString("ENEMY ESCAPED %1").arg(escaped));

    if(SCORE >= 25){
        gameWon = true;

    }
    if(escaped >= 8){
        gameOver = true;

    }

    int x = 20;

    n = QTime::currentTime();
    if(xt < n){
		qDebug() << "New enemy :" << xt << "Time n:" << n ;

		int v2 = rand() % 6 + 1;
		srand (time(NULL));
		qDebug() << "Random:" << v2 ;

		Enemy* en =new Enemy();

		switch (v2) {
		case 1:
			en->resetState(x,-60);
			break;
		case 2:
			en->resetState(x+100,-60);
			break;
		case 3:
			en->resetState(x+200,-60);
			break;
		case 4:
			en->resetState(x+300,-60);
			break;
		case 5:
			en->resetState(x+400,-60);
			break;
		case 6:
			en->resetState(x+500,-60);
			break;
		default:
			break;
		}

		//en->resetState(x,-60);
		enemymap->insert(enemyCount,en);
		enemyCount++;
		qDebug() << "New Enemy:" << enemyCount ;

       QString str;
       str.append(QString("%1").arg(enemyCount));
       QString uiENEMY = "ENEMY:" + str + "";
       ui->label_2->setText(uiENEMY);

		xt = QTime::currentTime().addSecs( 3 );
    }


    this->animate();
    checkCollision();
    removeDestroyed();
    repaint();

}

//...............................................................................................................


void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
       {
              int x = plane->getRect().x();
              for (int i=1; i<=10; i++)
              plane->moveLeft(x--);
        break;
       }
         case Qt::Key_Right:
        {
              int x = plane->getRect().x();
              for (int i=1; i<=10; i++)
              plane->moveRight(x++);
        }
        break;
        case Qt::Key_P:
       {
                if(paused){
                    timerId = startTimer(30);
                    paused = false;
                    xt = QTime::currentTime();
                    xt = QTime::currentTime().addSecs( 10 );
                }
                else{
                  paused = true;

                }
       }
    case Qt::Key_N:
   {
            if(gameOver || gameWon){
                QMap< int,Shoot *>::const_iterator i = map->constBegin();
                QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();
               while (i != map->constEnd()) {
                 delete i.value();
                     ++i;
                 }
                   while (e != enemymap->constEnd()) {
                      delete  e.value();
                          ++e;
                      }
                enemymap->clear();
                map->clear();
                timerId = startTimer(30);
                shootCount = 0;
                enemyCount = 0;
                SCORE = 0;
                escaped = 0;
                gameOver = false;
                gameWon = false;
                paused = false;
                xt = QTime::currentTime();
                xt = QTime::currentTime().addSecs( 2 );
            }
            else{
                }
   }
       break;
         case Qt::Key_Space:
        {
           if(!paused){
				int x = plane->getRect().x() + 32;
                int y = plane->getRect().y();

                Shoot* k =new Shoot();
                k->resetState(x,y);
                map->insert(shootCount,k);

                QString str;
                str.append(QString("%1").arg(shootCount));
                QString uishoots = "SHOOTS:" + str + "";
                ui->label->setText(uishoots);
                shootCount++;
          }
        }
        break;
         case Qt::Key_Escape:
        {
              qApp->exit();
           // qApp->quit();
        }
        break;
    default:
        QWidget::keyPressEvent(event);

    }
}

//...............................................................................................................

void Widget::checkCollision()
{
    QMap< int,Shoot *>::const_iterator i = map->constBegin();
    while (i != map->constEnd()) {
        QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();
        while (e != enemymap->constEnd()) {
           if ((i.value()->getRect()).intersects(e.value()->getRect())) {
                e.value()->Destroyed();
                i.value()->Destroyed();
                SCORE = SCORE + 1;
                qDebug() << "Colision: Enemy" << e.key() << "Shoot" << i.key() ;
            }
          ++e;
        }
      ++i;
    }

    QMap< int,Enemy *>::const_iterator en = enemymap->constBegin();
    while (en != enemymap->constEnd()) {
        if ((en.value()->getRect()).intersects(plane->getRect())) {
            en.value()->Destroyed();
            qDebug() << "Crash:" << en.key() ;
            gameOver = true;

        }
        if (en.value()->getRect().top() == 320){
           en.value()->Destroyed();;
           escaped++;

        }
    ++en;
    }

}
void Widget::removeDestroyed()
{
    QMutableMapIterator<int,Shoot *> i(*map);
    while (i.hasNext()) {
        i.next();
        if (i.value()->destroyed ){
          qDebug() << "Remove Shoot:" << i.key() ;
            i.remove();
        }
    }
    QMutableMapIterator<int,Enemy*> c(*enemymap);
    while (c.hasNext()) {
        c.next();
        if (c.value()->destroyed ){
		  qDebug() << "Remove Enemy key:" << c.key() << "value:" << c.value() << "from map on adress:" <<  &enemymap << "on pointer:" <<  enemymap ;
            c.remove();
        }
    }
}
void Widget::animate()
{
    QMap< int,Shoot *>::const_iterator i = map->constBegin();
    while (i != map->constEnd()) {
      i.value()->autoMove();

         ++i;
     }
    QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();
    while (e != enemymap->constEnd()) {
        e.value()->autoMove();

       ++e;
    }
}


//...............................................................................................................

#include <QImage>
#include <QDebug>
#include <QPixmap>
#include <math.h>
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

    timerId = startTimer(30);
    shootCount = 0;
    enemyCount = 0;
    SCORE = 0;
    escaped = 0;
    gameOver = FALSE;
    gameWon = FALSE;
    paused = FALSE;

    xt = QTime::currentTime();
    xt = QTime::currentTime().addSecs( 2 );
    qDebug() << "Start time:" << xt ;
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
  //  fileToolBar->addWidget(ui->label);
 //   fileToolBar->addSeparator();
  //  fileToolBar->addWidget(ui->label_2);
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
        gameWon = TRUE;
    }
    if(escaped >= 8){
        gameOver = TRUE;
    }

    int x = 20;

    n = QTime::currentTime();
    if(xt < n){
        qDebug() << "Time t:" << xt << "Time n:" << n ;
       for (int i=0; i<6; i++) {
            Enemy* en =new Enemy();
            en->resetState(x,-60);
            enemymap->insert(enemyCount,en);
            enemyCount++;

            x=x+100;
          }
       QString str;
       str.append(QString("%1").arg(enemyCount));
       QString uiENEMY = "ENEMY:" + str + "";
       ui->label_2->setText(uiENEMY);

        xt = QTime::currentTime().addSecs( 10 );
    }

    QMap< int,Shoot *>::const_iterator i = map->constBegin();
    QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();

    while (i != map->constEnd()) {
      i.value()->autoMove();
         ++i;
     }

    while (e != enemymap->constEnd()) {
        e.value()->autoMove();
        if(e.value()->destroyed == TRUE){
           delete e.value();
           enemymap->remove(e.key());
        }
          ++e;
      }

    checkCollision();
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
                    paused = FALSE;
                    xt = QTime::currentTime();
                    xt = QTime::currentTime().addSecs( 10 );
                }
                else{
                  paused = TRUE;

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
                gameOver = FALSE;
                gameWon = FALSE;
                paused = FALSE;
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
                int x = plane->getRect().x();
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

        int control2 =0;
        int control = 0;
        while (i != map->constEnd()) {
            QMap< int,Enemy *>::const_iterator e = enemymap->constBegin();
           while (e != enemymap->constEnd()) {
               if ((i.value()->getRect()).intersects(e.value()->getRect())) {
                    e.value()->Destroyed();
                    control = 1;
                    control2 = 1;
                    SCORE = SCORE + 1;
                    qDebug() << "Destroyed: KEY" << i.key() ;
                }

                ++e;
                control=0;
              }
           if (i.value()->getRect().bottom() == 30 ){
                control2 = 1;

           }
           if(control2 == 1){
               delete i.value();
               map->remove(i.key());
           }

        ++i;
        control2 = 0;
        }

        QMap< int,Enemy *>::const_iterator en = enemymap->constBegin();

        while (en != enemymap->constEnd()) {
            if ((en.value()->getRect()).intersects(plane->getRect())) {
                en.value()->Destroyed();
                qDebug() << "crash:" << en.key() ;
                gameOver = TRUE;

             }
            if (en.value()->getRect().top() == 320){
               delete en.value();
               enemymap->remove(en.key());
               escaped++;

                   }
               ++en;
           }

}

//...............................................................................................................
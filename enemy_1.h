#ifndef ENEMY_1_H
#define ENEMY_1_H
#include"enemy.h"

class Enemy_1:public Enemy
{
public:
    Enemy_1(WayPoint *startWayPoint, MainWindow *game,int type,QPixmap &sprite):Enemy(startWayPoint,game,type,sprite){
        //this->m_sprite = sprite;
    }
};


#endif // ENEMY_1_H

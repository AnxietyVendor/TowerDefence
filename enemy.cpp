#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(30, 30);

Enemy::Enemy(WayPoint *startWayPoint, MainWindow *game,int type,QPixmap &sprite/* = QPixmap(":/image/enemy.png")*/)
    : QObject(0)
    , m_active(false)
    , m_maxHp(40)
    , m_currentHp(40)
    , m_walkingSpeed(4.0)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())//设置初始位置为初始路点
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_type(type)
    , m_state(1)
    , m_sprite(sprite)
{
}

Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemy::doActivate()
{
    m_active = true;//受到信号后处于激活状态
}

void Enemy::switchsprite1()
{
    int static count = 1;
    if(count > 8) count = 1;
        switch(count)
        {
            case 1:m_sprite=QPixmap(":/image/enemy_unit_1_a.png");break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:m_sprite=QPixmap(":/image/enemy_unit_1_b.png");break;
            case 6:break;
            case 7:break;
            case 8:break;
            default:break;
        }
    count++;
}

void Enemy::switchsprite2()
{
    int static count = 1;
    if(count > 8) count = 1;
        switch(count)
        {
            case 1:m_sprite=QPixmap(":/image/enemy_unit_2_a.png");break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:m_sprite=QPixmap(":/image/enemy_unit_2_b.png");break;
            case 6:break;
            case 7:break;
            case 8:break;
            default:break;
        }
    count++;
}
void Enemy::switchsprite3()
{
    int static count = 1;
    if(count > 8) count = 1;
        switch(count)
        {
            case 1:m_sprite=QPixmap(":/image/enemy_unit_3_a.png");break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:m_sprite=QPixmap(":/image/enemy_unit_3_b.png");break;
            case 6:break;
            case 7:break;
            case 8:break;
            default:break;
        }
    count++;
}
void Enemy::switchsprite7()
{
    int static count = 1;
    if(count > 8) count = 1;
        switch(count)
        {
            case 1:m_sprite=QPixmap(":/image/enemy_unit_7_a.png");break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:m_sprite=QPixmap(":/image/enemy_unit_7_b.png");break;
            case 6:break;
            case 7:break;
            case 8:break;
            default:break;
        }
    count++;
}
void Enemy::switchsprite8()
{
    int static count = 1;
    if(count > 8) count = 1;
        switch(count)
        {
            case 1:m_sprite=QPixmap(":/image/enemy_unit_8_a.png");break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:m_sprite=QPixmap(":/image/enemy_unit_8_b.png");break;
            case 6:break;
            case 7:break;
            case 8:break;
            default:break;
        }
    count++;
}
void Enemy::switchsprite9()
{
    int static count = 1;
    if(count > 8) count = 1;
        switch(count)
        {
            case 1:m_sprite=QPixmap(":/image/enemy_unit_9_c.png");break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:m_sprite=QPixmap(":/image/enemy_unit_9_d.png");break;
            case 6:break;
            case 7:break;
            case 8:break;
            default:break;
        }
    count++;
}

void Enemy::move()
{
    if(m_state){
        switch(m_type)
        {
        case 1:switchsprite1();break;
        case 2:switchsprite2();break;
        case 3:switchsprite3();break;
        case 4:break;
        case 5:break;
        case 6:break;
        case 7:switchsprite7();break;
        case 8:switchsprite8();break;
        case 9:switchsprite9();break;
        default:break;
        }
    }
    else{
        switch(m_type)
        {
        case 1:m_sprite=QPixmap(":/image/1_a_ice_2.png");break;
        case 2:m_sprite=QPixmap(":/image/2_a_ice_2.png");break;
        case 3:m_sprite=QPixmap(":/image/3_a_ice_2.png");break;
        case 4:break;
        case 5:break;
        case 6:break;
        case 7:m_sprite=QPixmap(":/image/7_a_ice_2.png");break;
        case 8:m_sprite=QPixmap(":/image/8_a_ice_2.png");break;
        case 9:m_sprite=QPixmap(":/image/9_a_ice_2.png");break;
        default:break;
        }
    }

        if (!m_active)//未激活状态不移动
            return;

        if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
        {
            // 敌人抵达了一个航点
            if (m_destinationWayPoint->nextWayPoint())
            {
                // 还有下一个航点
                m_pos = m_destinationWayPoint->pos();
                m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
            }
            else
            {
                // 表示进入基地
                m_game->getHpDamage();
                m_game->removedEnemy(this);
                return;
            }
        }

        // 还在前往航点的路上
        // 目标航点的坐标
        QPoint targetPoint = m_destinationWayPoint->pos();
        // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

        // 向量标准化
        qreal movementSpeed = m_walkingSpeed;
        QVector2D normalized(targetPoint - m_pos);
        normalized.normalize();
        m_pos = m_pos + normalized.toPoint() * movementSpeed;

        // 确定敌人选择方向
        // 默认图片向左,需要修正180度转右
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 90;


}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    //painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty()&&m_attackedTower2List.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    foreach (Tower2 *attacker, m_attackedTower2List)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{
    m_game->audioPlayer()->playSound(bianpaotower);
    m_currentHp -= damage;

    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {
        m_game->audioPlayer()->playSound(die);
        m_game->awardGold(100);
        getRemoved();
    }
}
void Enemy::getslow()//受到子弹2攻击时减速
{
    m_walkingSpeed=1.8;
    m_state = 0;//冰冻状态

    // 阵亡,需要移除
}
void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::getAttacked(Tower2 *attacker)
{
    m_attackedTower2List.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower2 *attacker)
{
    m_attackedTower2List.removeOne(attacker);
}


void Enemy::getPromoted(int ratio)
{
    m_maxHp = add_Hp*ratio;
    m_currentHp = add_Hp*ratio;
    m_walkingSpeed = m_walkingSpeed*1.25;
}


QPoint Enemy::pos() const
{
    return m_pos;
}

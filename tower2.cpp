#include "tower2.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower2::ms_fixedSize(32, 55);

Tower2::Tower2(QPoint pos, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/tower_unit_3_a.png"*/)
    : m_attacking(false)
    , m_attackRange(150)
    , m_damage(5)
    , m_fireRate(1000)
    , m_rotationSprite(0.0)
    , m_chooseEnemy(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower2::~Tower2()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void Tower2::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        /*
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;
        */
        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower2::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::blue);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width(), -ms_fixedSize.height());
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Tower2::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower2::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower2::shootWeapon()
{
    Bullet2 *bullet = new Bullet2(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet2(bullet);
}

void Tower2::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower2::lostSightOfEnemy()
{
    m_chooseEnemy->
            gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}
void Tower2::levelUp()
{
    m_damage+=5;
    m_attackRange+=100;
    const QPixmap &newpicture= QPixmap(":/image/tower_unit_3_b.png");
    m_sprite=newpicture;
}
QPoint Tower2::getposition()
{
    return m_pos;
}

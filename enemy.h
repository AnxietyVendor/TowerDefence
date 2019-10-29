#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class Tower2;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow *game,int type,QPixmap &sprite /*= QPixmap(":/image/enemy.png")*/);
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getslow();
    void getRemoved();//清除死亡敌人
    void getAttacked(Tower *attacker);
    void getAttacked(Tower2 *attacker);

    void gotLostSight(Tower *attacker);
    void gotLostSight(Tower2 *attacker);
    void getPromoted(int ratio);
    void switchsprite1();//循环更新sprite
    void switchsprite2();
    void switchsprite3();
    void switchsprite7();
    void switchsprite8();
    void switchsprite9();
    QPoint pos() const;

public slots:
    void doActivate();//槽

protected:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    int             add_Hp = 40;
    int             add_Speed = 1.0;
    int             m_type;//类型变量
    int             m_state;//状态变量，是否被冷冻，1表示正常，0表示冰冻
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;
    QList<Tower2 *>  m_attackedTower2List;

    QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};

#endif // ENEMY_H

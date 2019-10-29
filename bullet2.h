#ifndef BULLET2_H
#define BULLET2_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;

class Bullet2 : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet2(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow *game, const QPixmap &sprite = QPixmap(":/image/bullet2.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *			m_target;
    MainWindow *	m_game;
    int				m_damage;

    static const QSize ms_fixedSize;
};

#endif // BULLET2_H

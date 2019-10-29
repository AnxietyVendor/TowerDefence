#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include"tower2.h"
#include"bullet2.h"

namespace Ui {
class MainWindow;
}

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void getHpDamage(int damage = 1);
	void removedEnemy(Enemy *enemy);
	void removedBullet(Bullet *bullet);
	void addBullet(Bullet *bullet);
    void removedBullet2(Bullet2 *bullet);
    void addBullet2(Bullet2 *bullet);
	void awardGold(int gold);

	AudioPlayer* audioPlayer() const;
	QList<Enemy *> enemyList() const;

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);

private slots:
	void updateMap();
	void gameStart();
    void receivesignal();
    void level();
    void reboot();
private:
	void loadTowerPositions();
	void addWayPoints();
	bool loadWave();
	bool canBuyTower() const;
    bool canBuyTower2() const;
	void drawWave(QPainter *painter);
	void drawHP(QPainter *painter);
	void drawPlayerGold(QPainter *painter);
	void doGameOver();
	void preLoadWavesInfo();
signals:
    void winfinish();
    void lostfinish();
private:
    Ui::MainWindow *		ui;
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    int                     m_level=1;
    AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
    QList<Bullet2 *>		m_bullet2List;
    QList<Tower2 *>         m_tower2List;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "enemy_1.h"
#include "bullet.h"
#include "audioplayer.h"
#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include<QProcess>
#include<QDir>
#include <QPixmap>
static const int TowerCost = 300;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_waves(0)
    , m_playerHp(5)
    , m_playrGold(1500)
    , m_gameEnded(false)
    , m_gameWin(false)
{


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(42);
    // 设置300ms后游戏启动

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTowerPositions()
{
    if(m_level==1)
    {
    QFile file(":/config/TowersPosition.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    QList<QVariant> array = reader.data();
    foreach (QVariant dict, array)
    {
        QMap<QString, QVariant> point = dict.toMap();
        int x = point.value("x").toInt();
        int y = point.value("y").toInt();
        m_towerPositionsList.push_back(QPoint(x, y));
    }

    file.close();
    }
    else if(m_level==2)
    {
    QFile file(":/config/TowersPosition2.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    QList<QVariant> array = reader.data();
    foreach (QVariant dict, array)
    {
        QMap<QString, QVariant> point = dict.toMap();
        int x = point.value("x").toInt();
        int y = point.value("y").toInt();
        m_towerPositionsList.push_back(QPoint(x, y));
    }

    file.close();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(m_level==1)
    {
        if (m_gameEnded || m_gameWin)
        {
            QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
            QPainter painter(this);
            painter.setPen(QPen(Qt::red));
            painter.drawText(rect(), Qt::AlignCenter, text);
            if(m_gameWin){

                QMessageBox::about(NULL, "result", "you win!!");

                emit winfinish();
            }

             else{
                QMessageBox::about(NULL, "result", "you lost!!");

                 emit lostfinish();
             }
            return;

        }

        QPixmap cachePix(":/image/BGlevel1-1.png");
        QPainter cachePainter(&cachePix);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&cachePainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&cachePainter);

        foreach (const Tower2 *tower, m_tower2List)
            tower->draw(&cachePainter);

   // foreach (const WayPoint *wayPoint, m_wayPointsList)
    //    wayPoint->draw(&cachePainter);

        foreach (const Enemy *enemy, m_enemyList)
            enemy->draw(&cachePainter);

        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&cachePainter);
        foreach (const Bullet2 *bullet, m_bullet2List)
            bullet->draw(&cachePainter);

        drawWave(&cachePainter);
        drawHP(&cachePainter);
        drawPlayerGold(&cachePainter);

        QPainter painter(this);
        painter.drawPixmap(0, 0, cachePix);
        }
        else if(m_level==2)
        {

            if (m_gameEnded || m_gameWin)
            {
                //QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
                //QPainter painter(this);
                //painter.setPen(QPen(Qt::red));
                //painter.drawText(rect(), Qt::AlignCenter, text);
                if(m_gameWin){
                    QMessageBox::about(NULL, "result", "you win!!");

                    emit winfinish();
                }

                 else{
                    QMessageBox::about(NULL, "result", "you lost!!");

                    emit lostfinish();
                 }
                return;
                return;
            }

        QPixmap cachePix(":/image/BGlevel1-2.png");
        QPainter cachePainter(&cachePix);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&cachePainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&cachePainter);

        foreach (const Tower2 *tower, m_tower2List)
            tower->draw(&cachePainter);

   //     foreach (const WayPoint *wayPoint, m_wayPointsList)
     //       wayPoint->draw(&cachePainter);

        foreach (const Enemy *enemy, m_enemyList)
            enemy->draw(&cachePainter);

        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&cachePainter);
        foreach (const Bullet2 *bullet, m_bullet2List)
            bullet->draw(&cachePainter);

        drawWave(&cachePainter);
        drawHP(&cachePainter);
        drawPlayerGold(&cachePainter);

        QPainter painter(this);
        painter.drawPixmap(0, 0, cachePix);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos=event->pos();
    if(event->button()==Qt::LeftButton)
    {
        auto it=m_towerPositionsList.begin();
            while (it!=m_towerPositionsList.end())
            {
                if(it->containPoint(pressPos))
                {
                    if(it->towertype()==0&&m_playrGold>=300 )
                    {
                        it->setTowerType(1);
                        m_audioPlayer->playSound(build);
                        m_playrGold -= TowerCost;
                        it->setHasTower();

                        Tower *tower = new Tower(it->centerPos(), this);
                        m_towersList.push_back(tower);
                        update();
                        break;
                    }
                    else if(it->towertype()==1&&!it->hasTower2()&&m_playrGold>=500 )
                    {
                                            m_audioPlayer->playSound(upgrade);
                                            m_playrGold -= 500;
                                            it->setHasTower2();
                                            auto zhazha=m_towersList.begin();
                                            while(zhazha!=m_towersList.end())
                                            {
                                                if( it->containPoint((*zhazha)->getposition()))
                                                { (*zhazha)->levelUp();
                                                    update();
                                                     break;
                                                }
                                                ++zhazha;
                                            }
                    }
                }
                it++;
            }
    }
    if(event->button()==Qt::RightButton)
    {
        auto it=m_towerPositionsList.begin();
            while (it!=m_towerPositionsList.end())
            {
                if(it->containPoint(pressPos))
                {
                    if(it->towertype()==0&&m_playrGold>=200 )
                    {
                        it->setTowerType(2);
                        m_audioPlayer->playSound(build);
                        m_playrGold -= 200;
                        it->setHas2Tower();

                        Tower2 *tower = new Tower2(it->centerPos(), this);
                        m_tower2List.push_back(tower);
                        update();
                        break;
                    }
                    else if(it->towertype()==2&&!it->has2Tower2()&&m_playrGold>=400 )
                    {
                                            m_audioPlayer->playSound(upgrade);
                                            m_playrGold -= 400;
                                            it->setHas2Tower2();
                                            auto zhazha=m_tower2List.begin();
                                            while(zhazha!=m_tower2List.end())
                                            {
                                                if( it->containPoint((*zhazha)->getposition()))
                                                { (*zhazha)->levelUp();
                                                    update();
                                                     break;
                                                }
                                                ++zhazha;
                                            }
                    }
                }
                it++;
            }
    }
}

bool MainWindow::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}
bool MainWindow::canBuyTower2() const
{
    if(m_playrGold>=500)
        return true;
    return false;
}

void MainWindow::drawWave(QPainter *painter)
{
    const QPixmap &sprite = QPixmap(":/image/blackboard.png");
    painter->drawPixmap(0,0, sprite);
    painter->setPen(QPen(Qt::black));
    painter->drawText(QRect(30,70, 125,90), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 40,125, 55), QString("HP : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(30, 20, 125, 35), QString("GOLD : %1").arg(m_playrGold));
}

void MainWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void MainWindow::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

AudioPlayer *MainWindow::audioPlayer() const
{
    return m_audioPlayer;
}

void MainWindow::addWayPoints()
{
    if(m_level==1)
    {
        WayPoint *wayPoint1 = new WayPoint(QPoint(511, 382));
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(537, 350));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(539, 306));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(539, 216));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(540, 150));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(493, 150));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(414, 150));
        m_wayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(330, 150));
        m_wayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(280, 151));
        m_wayPointsList.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);

        WayPoint *wayPoint10 = new WayPoint(QPoint(234, 203));
        m_wayPointsList.push_back(wayPoint10);
        wayPoint10->setNextWayPoint(wayPoint9);

        WayPoint *wayPoint11 = new WayPoint(QPoint(225, 294));
        m_wayPointsList.push_back(wayPoint11);
        wayPoint11->setNextWayPoint(wayPoint10);

        WayPoint *wayPoint12 = new WayPoint(QPoint(224, 357));
        m_wayPointsList.push_back(wayPoint12);
        wayPoint12->setNextWayPoint(wayPoint11);

        WayPoint *wayPoint13 = new WayPoint(QPoint(238, 419));
        m_wayPointsList.push_back(wayPoint13);
        wayPoint13->setNextWayPoint(wayPoint12);

        WayPoint *wayPoint14 = new WayPoint(QPoint(269, 463));
        m_wayPointsList.push_back(wayPoint14);
        wayPoint14->setNextWayPoint(wayPoint13);

        WayPoint *wayPoint15 = new WayPoint(QPoint(308, 509));
        m_wayPointsList.push_back(wayPoint15);
        wayPoint15->setNextWayPoint(wayPoint14);

        WayPoint *wayPoint16 = new WayPoint(QPoint(349, 559));
        m_wayPointsList.push_back(wayPoint16);
        wayPoint16->setNextWayPoint(wayPoint15);

        WayPoint *wayPoint17 = new WayPoint(QPoint(359, 766));
        m_wayPointsList.push_back(wayPoint17);
        wayPoint17->setNextWayPoint(wayPoint16);

    }
    else if(m_level==2)
    {

        WayPoint *wayPoint1 = new WayPoint(QPoint(688, 102));
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(687, 20));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(143, 20));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(148, 459));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(392, 459));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(387, 340));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(650, 340));
        m_wayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(652, 719));
        m_wayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(12, 724));
        m_wayPointsList.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);




    }
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{
    m_audioPlayer->playSound(loseplayerhp);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}
void MainWindow::removedBullet2(Bullet2 *bullet)
{
    Q_ASSERT(bullet);

    m_bullet2List.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet2(Bullet2 *bullet)
{
    Q_ASSERT(bullet);

    m_bullet2List.push_back(bullet);
}

void MainWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    foreach (Tower2 *tower, m_tower2List)
        tower->checkEnemyInRange();
    update();
}

void MainWindow::preLoadWavesInfo()
{
    if(m_level==1)
    {
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
    }
    else if(m_level==2)
    {
        QFile file(":/config/Waves2.plist");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
            return;
        }

        PListReader reader;
        reader.read(&file);

        // 获取波数信息
        m_wavesInfo = reader.data();

        file.close();
    }
}

bool MainWindow::loadWave()
{
    if(m_level==1)
    {
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 1; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();//从plist读取spawntime
        QPixmap sprite_1 = QPixmap(":/image/enemy_unit_1_a.png");
        QPixmap sprite_2 = QPixmap(":/image/enemy_unit_2_a.png");
        QPixmap sprite_3 = QPixmap(":/image/enemy_unit_3_a.png");


        Enemy *enemy_1 = new Enemy_1(startWayPoint, this,1, sprite_1);
        Enemy *enemy_2 = new Enemy_1(startWayPoint, this,2, sprite_2);
        Enemy *enemy_3 = new Enemy_1(startWayPoint, this,3, sprite_3);
        //enemy_1->switchsprite();
        enemy_1->getPromoted(m_waves + 1);//同一波敌人不同速度++生命++
        enemy_2->getPromoted(m_waves + 1);
        enemy_3->getPromoted(m_waves + 1);
        if (i % 2 == 0) {
            m_enemyList.push_back(enemy_1);
            QTimer::singleShot(spawnTime, enemy_1, SLOT(doActivate()));
        }
        else if (i % 2 != 0 && i % 3== 0) {
            m_enemyList.push_back(enemy_2);
            QTimer::singleShot(spawnTime, enemy_2, SLOT(doActivate()));
        }
        else {
            m_enemyList.push_back(enemy_3);
            QTimer::singleShot(spawnTime, enemy_3, SLOT(doActivate()));

        }

    }


    return true;
    }
    else if(m_level==2)
    {
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();


    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();//从plist读取spawntime数


        QPixmap sprite_7 = QPixmap(":/image/enemy_unit_7_a.png");
        QPixmap sprite_8 = QPixmap(":/image/enemy_unit_8_a.png");
        QPixmap sprite_9 = QPixmap(":/image/enemy_unit_9_a.png");


        //Enemy *enemy_1 = new Enemy_1(startWayPoint, this,7, sprite_5);
        Enemy *enemy_7 = new Enemy_1(startWayPoint, this,7, sprite_7);
        Enemy *enemy_8 = new Enemy_1(startWayPoint, this,8, sprite_8);
        Enemy *enemy_9 = new Enemy_1(startWayPoint, this,9, sprite_9);

        enemy_7->getPromoted(m_waves + 1);//同一波敌人不同速度++生命++
        enemy_8->getPromoted(m_waves + 1);
        enemy_9->getPromoted(m_waves + 1);

        if (i % 2 == 0) {
            m_enemyList.push_back(enemy_7);
            QTimer::singleShot(spawnTime, enemy_7, SLOT(doActivate()));
        }
        else if (i % 2 != 0 && i%3 == 0) {
            m_enemyList.push_back(enemy_8);
            QTimer::singleShot(spawnTime, enemy_8, SLOT(doActivate()));
        }
        else {
            m_enemyList.push_back(enemy_9);
            QTimer::singleShot(spawnTime, enemy_9, SLOT(doActivate()));

        }

    }
    //continue;
    return true;
    }
    else
    return false;
}

QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::gameStart()
{
    loadWave();
}
void MainWindow::receivesignal()
{
    setFixedSize(771, 771);
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();

    m_audioPlayer = new AudioPlayer(this);
    m_audioPlayer->startBGM();
    QTimer::singleShot(300, this, SLOT(gameStart()));
    show();

}
void MainWindow::level()
{
    m_level=2;
}
void MainWindow::reboot(){
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}

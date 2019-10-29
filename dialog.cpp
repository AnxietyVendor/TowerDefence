#include "dialog.h"
#include "ui_dialog.h"
#include<QMediaPlayer>
#include<QDir>
static const QString s_curDir = QDir::currentPath() + "/";

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),backgroundMusic(NULL)
{
        backgroundMusic = new QMediaPlayer(this);

        backgroundMusic->setMedia(QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\menu.mp3"));

        backgroundMusic->play();
        ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete backgroundMusic;
    delete ui;
}
void Dialog::on_pushButton_2_clicked()
{
    this->hide();
    backgroundMusic->stop();
    emit showwindow1();
}

void Dialog::on_pushButton_clicked()
{
    this->hide();
    backgroundMusic->stop();
    emit changelevel();
    emit showwindow1();
}


void Dialog::on_pushButton_3_clicked()
{
    emit quit1();
}

void Dialog::showagain(){
    this->show();
}

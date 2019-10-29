#include "mainwindow.h"
#include <QApplication>
#include"dialog.h"
#include<QString>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
    Dialog d;
    QObject::connect(&d,SIGNAL(showwindow1()),&w,SLOT(receivesignal()));//通过按钮实现主窗口的展现
    QObject::connect(&d,SIGNAL(quit1()),&a,SLOT(quit()));//如果点击退出则全部窗口关闭
    QObject::connect(&d,SIGNAL(changelevel()),&w,SLOT(level()));//使关卡变为2，从而读取第二关的相关数据

    QObject::connect(&w,SIGNAL(winfinish()),&w,SLOT(reboot()));//清空缓存
    QObject::connect(&w,SIGNAL(winfinish()),&d,SLOT(showagain()));//把对话框显示出来
    QObject::connect(&w,SIGNAL(lostfinish()),&a,SLOT(quit()));//直接把窗口关掉，
    d.show();
	return a.exec();
}

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QMediaPlayer>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void showagain();
signals:
    void showwindow1();
    void quit1();
    void changelevel();
private:
    Ui::Dialog *ui;
    QMediaPlayer *backgroundMusic;
};

#endif // DIALOG_H

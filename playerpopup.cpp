#include "playerpopup.h"
#include "ui_playerpopup.h"
#include <QDebug>

playerPopup::playerPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playerPopup)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
}

playerPopup::~playerPopup()
{
    delete ui;
}

void playerPopup::on_LEFTButton_clicked()
{
    emit movePlayer(0);
}

void playerPopup::on_UPButton_clicked()
{
    emit movePlayer(2);
}

void playerPopup::on_RIGHTButton_clicked()
{
    emit movePlayer(1);
}

void playerPopup::on_DOWNButton_clicked()
{
    emit movePlayer(3);
}

void playerPopup::setEdits(int x, int y){
    this->ui->xEdit->setText(QString::number(x));
    this->ui->yEdit->setText(QString::number(y));
}

void playerPopup::on_xEdit_editingFinished()
{
    emit xChanged(ui->xEdit->text().toInt());
}

void playerPopup::on_yEdit_editingFinished()
{
    emit yChanged(ui->yEdit->text().toInt());
}

#include "playerpopup.h"
#include "ui_playerpopup.h"
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QMessageBox>
#include <QCloseEvent>

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

void playerPopup::closeEvent(QCloseEvent* event){
    event->ignore();
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

void playerPopup::setTextureURL(QString newURL){
    ui->texturePathLabel->setText(newURL);
}

void playerPopup::on_textureButton_clicked()
{
    QFileDialog openDialog(this, "Open Player Texture Image");
    openDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last());

    QStringList supportedMimeTypes = QStringList();
    for(int i=0;i<QImageReader::supportedMimeTypes().size();i++){
        if(QImageReader::supportedMimeTypes().at(i)!=""){
            supportedMimeTypes.append(QString(QImageReader::supportedMimeTypes().at(i)));
        }
    }
    openDialog.setMimeTypeFilters(supportedMimeTypes);

    if(openDialog.exec()==QFileDialog::Accepted){
        QImageReader reader(openDialog.selectedFiles().first());
        QImage mapImg = reader.read();
            if (mapImg.isNull()) {
                QMessageBox::information(this, "Couldn't load image",reader.errorString());
                return;
            }

        emit textureChanged(openDialog.selectedFiles().first());
    }
}

void playerPopup::keyPressEvent(QKeyEvent* event){

    switch(event->key()){
        case Qt::Key_W:
            emit yChanged(ui->yEdit->text().toInt()-1);
            break;
        case Qt::Key_A:
            emit xChanged(ui->xEdit->text().toInt()-1);
            break;
        case Qt::Key_S:
            emit yChanged(ui->yEdit->text().toInt()+1);
            break;
        case Qt::Key_D:
            emit xChanged(ui->xEdit->text().toInt()+1);
            break;

    }
}

void playerPopup::on_sizeBox_valueChanged(int arg1)
{
    if(arg1<1){
        ui->sizeBox->setValue(1);
        arg1 = 1;
    }

    emit sizeChanged(arg1);
}

void playerPopup::setSize(int newSize){
    ui->sizeBox->setValue(newSize);
}

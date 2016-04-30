#include "combatmap.h"
#include "ui_combatmap.h"
#include "settings.h"
#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QImageReader>
#include <QMessageBox>
#include <QPainter>
#include <QMap>
#include <QMouseEvent>

CombatMap::CombatMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CombatMap)
{
    ui->setupUi(this);
    ui->gridLayout_scroll->removeWidget(ui->gridLabel);
    ui->gridLayout_scroll->addWidget(ui->gridLabel,0,0,Qt::AlignCenter);
    ui->gridLayout_scroll->removeWidget(ui->imgLabel);
    ui->gridLayout_scroll->addWidget(ui->imgLabel,0,0,Qt::AlignCenter);
    QMap<QString, int> settings = Settings::readSettings();
    gridWidth = settings["gridWidth"];
    gridHeight = settings["gridHeight"];
    QImage map = QImage("img/blank.png");
    if(!map.isNull()){
        ui->imgLabel->setPixmap(QPixmap::fromImage(map));
        generateGrid();
    }

    connect(ui->gridLabel,SIGNAL(clicked(QMouseEvent*)),this,SLOT(gridClicked(QMouseEvent*)));

}

CombatMap::~CombatMap()
{
    delete ui;
}

void CombatMap::on_actionOpen_Image_triggered()
{
    QFileDialog openDialog(this, "Open Map Image");
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
            }
        ui->imgLabel->setPixmap(QPixmap::fromImage(mapImg));
        ui->imgLabel->resize(mapImg.size());
        generateGrid();
    }
}

void CombatMap::generateGrid(){
    if(ui->imgLabel->pixmap()==NULL) return;

    QPixmap grid(ui->imgLabel->size());
    grid.fill(Qt::transparent);
    QPainter* paint = new QPainter(&grid);
    paint->setPen(QColor(0,0,0));

    for(int x=0;x<ui->imgLabel->width();x+=gridWidth){
        paint->drawLine(x,0,x,ui->imgLabel->height());
    }

    for(int y=0;y<ui->imgLabel->height();y+=gridHeight){
        paint->drawLine(0,y,ui->imgLabel->width(),y);
    }

    for(int i=0;i<participants.length();i++){
        QImage image = QImage(participants[i]->texturePath);
        if(!image.isNull()){
            image = image.scaled(gridWidth, gridHeight);
            paint->drawImage(participants[i]->x*gridWidth,participants[i]->y*gridHeight,image);
        }
    }
    delete paint;
    ui->gridLabel->setPixmap(grid);
}

void CombatMap::on_actionOptions_triggered()
{
    Settings* settingWindow = new Settings();
    connect(settingWindow,SIGNAL(settingsChanged(QMap<QString, int>*)),this,SLOT(settings_changed(QMap<QString, int>*)));
    settingWindow->show();
}

void CombatMap::settings_changed(QMap<QString, int> *settings){
    gridWidth = settings->value("gridWidth");
    gridHeight = settings->value("gridHeight");
    generateGrid();
}

void CombatMap::on_addPlayerButton_clicked()
{
    CombatParticipant *newPlayer = new CombatParticipant("Player "+QString::number(participants.length()),new QListWidgetItem());

    for(int i=0;i<participants.length();i++){
        if(participants[i]->x==newPlayer->x&&participants[i]->y==newPlayer->y){
            newPlayer->x++;
        }
    }

    ui->playerList->addItem(newPlayer->item);
    connect(ui->playerList,SIGNAL(currentTextChanged(QString)),newPlayer,SLOT(textChanged(QString)));
    participants << newPlayer;
    generateGrid();
}

void CombatMap::on_removePlayerButton_clicked()
{
    if(ui->playerList->currentItem()==NULL) return;
    CombatParticipant* current;
    for(int i=0;i<participants.length();i++){
        if(participants.at(i)->item == ui->playerList->currentItem()){
            current = participants.takeAt(i);
        }
    }
    delete ui->playerList->currentItem();

    if(current!=NULL)delete current;

    generateGrid();
}

void CombatMap::gridClicked(QMouseEvent* event){
    qDebug()<<event->pos();
    for(int i=0;i<participants.length();i++){
        QRect playerGrid = QRect(participants[i]->x*gridWidth,participants[i]->y*gridHeight,gridWidth,gridHeight);
        qDebug() << playerGrid;
        if(playerGrid.contains(event->pos().x(),event->pos().y())){
            participants[i]->item->setSelected(true);
        }
    }
}

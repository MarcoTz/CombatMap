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

CombatMap::CombatMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CombatMap)
{
    ui->setupUi(this);
    ui->gridLayout_scroll->removeWidget(ui->gridLabel);
    ui->gridLayout_scroll->addWidget(ui->gridLabel,0,0,Qt::AlignCenter);
    ui->gridLayout_scroll->removeWidget(ui->imgLabel);
    ui->gridLayout_scroll->addWidget(ui->imgLabel,0,0,Qt::AlignCenter);
    gridWidth = 16;
    gridHeight = 16;
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

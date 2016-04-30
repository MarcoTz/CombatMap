#include "settings.h"
#include "ui_settings.h"
#include <QDebug>
#include <QFile>
#include <QMap>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    QMap<QString, int> settings = readSettings();
    ui->gridHeightEdit->setText(QString::number(settings["gridHeight"]));
    ui->gridWidthEdit->setText(QString::number(settings["gridWidth"]));
}

Settings::~Settings()
{
    delete ui;
}

QMap<QString, int> Settings::readSettings(){
    QMap<QString,int> settings;
    QFile configFile("conf.cfg");

    if(!configFile.open(QIODevice::ReadOnly)) return settings;

    while(!configFile.atEnd()){
        QString line = configFile.readLine();
        line.replace(" ","");
        line.replace("\n","");
        if(line.startsWith("gridWidth=")){
            settings["gridWidth"] = line.replace("gridWidth=","").toInt();
        }else if(line.startsWith("gridHeight")){
            settings["gridHeight"] = line.replace("gridHeight=","").toInt();
        }
    }
    return settings;
}

void Settings::writeSettings(){
     QFile configFile("conf.cfg");

     if(!configFile.open(QIODevice::WriteOnly)) return;

     QTextStream out(&configFile);
     out << "gridWidth=" << ui->gridWidthEdit->text() << "\n";
     out << "gridHeight=" << ui->gridHeightEdit->text() << "\n";

}

void Settings::on_OK_clicked()
{
    writeSettings();
    QMap<QString, int> settings;
    settings["gridHeight"] = ui->gridHeightEdit->text().toInt();
    settings["gridWidth"] = ui->gridWidthEdit->text().toInt();
    emit(settingsChanged(&settings));
    done(0);
}

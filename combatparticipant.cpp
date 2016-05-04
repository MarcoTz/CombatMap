#include "combatparticipant.h"
#include <QDebug>

CombatParticipant::CombatParticipant(QString name, QListWidgetItem* item, int x, int y, int speed, QString texturePath, QObject *parent) : QObject(parent)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->texturePath = texturePath;
    this->name = name;
    this->item = item;
    this->item->setFlags(this->item->flags() | Qt::ItemIsEditable);
    this->item->setText(this->name);

    this->popup = new playerPopup(qobject_cast<QWidget *>(parent));
    this->popup->setWindowTitle(this->name);
    this->popup->setEdits(this->x,this->y);
    this->popup->setTextureURL(this->texturePath);
    this->popup->setSpeed(this->speed);

    connect(this->popup,SIGNAL(movePlayer(int)),this,SLOT(movePlayer(int)));
    connect(this->popup,SIGNAL(xChanged(int)),this,SLOT(changeX(int)));
    connect(this->popup,SIGNAL(yChanged(int)),this,SLOT(changeY(int)));
    connect(this->popup,SIGNAL(textureChanged(QString)),this,SLOT(textureChanged(QString)));
    connect(this->popup,SIGNAL(speedChanged(int)),this,SLOT(speedChanged(int)));
}

void CombatParticipant::textChanged(QString newName){
    this->name = newName;
    this->popup->setWindowTitle(newName);
}

//0: left
//1: right
//2: up
//3: down
void CombatParticipant::movePlayer(int direction){
    switch(direction){
        case 0:
            this->x--;
            break;
        case 1:
            this->x++;
            break;
        case 2:
            this->y--;
            break;
        case 3:
            this->y++;
            break;
    }
    emit updateGrid(this);
}

void CombatParticipant::changeX(int newx){
    this->x = newx;
    emit updateGrid(this);
}

void CombatParticipant::changeY(int newy){
    this->y = newy;
    emit updateGrid(this);
}

void CombatParticipant::textureChanged(QString newPath){
    this->texturePath=newPath;
    emit updateGrid(this);
}

void CombatParticipant::speedChanged(int newSpeed){
    this->speed = newSpeed;
}

#include "combatparticipant.h"

CombatParticipant::CombatParticipant(QString name, QListWidgetItem* item, int x, int y, QString texturePath, QObject *parent) : QObject(parent)
{
    this->x = x;
    this->y = y;
    this->texturePath = texturePath;
    this->name = name;
    this->item = item;
    this->item->setFlags(this->item->flags() | Qt::ItemIsEditable);
    this->item->setText(this->name);
}

void CombatParticipant::textChanged(QString newName){
    this->name = newName;
}

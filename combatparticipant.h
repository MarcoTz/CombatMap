#ifndef COMBATPARTICIPANT_H
#define COMBATPARTICIPANT_H

#include <QObject>
#include <QImage>
#include <QListWidgetItem>
#include "playerpopup.h"

class CombatParticipant : public QObject
{
    Q_OBJECT
public:
    explicit CombatParticipant(QString name="", QListWidgetItem* item=NULL, int x=0, int y=0, QString texturePath = "img/player.png", QObject *parent = 0);

    QString texturePath;
    int x;
    int y;
    QString name;
    QListWidgetItem* item;
    playerPopup* popup;

private:


signals:
    void updateGrid(CombatParticipant*);

public slots:
    void textChanged(QString);
    void movePlayer(int);
    void changeX(int);
    void changeY(int);
    void textureChanged(QString);
};

#endif // COMBATPARTICIPANT_H

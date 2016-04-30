#ifndef COMBATPARTICIPANT_H
#define COMBATPARTICIPANT_H

#include <QObject>
#include <QImage>
#include <QListWidgetItem>

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

private:


signals:

public slots:
    void textChanged(QString);
};

#endif // COMBATPARTICIPANT_H

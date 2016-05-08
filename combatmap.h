#ifndef COMBATMAP_H
#define COMBATMAP_H

#include <QMainWindow>
#include "combatparticipant.h"

namespace Ui {
class CombatMap;
}

class CombatMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit CombatMap(QWidget *parent = 0);
    ~CombatMap();
    void closeEvent(QCloseEvent*);
    void showEvent(QShowEvent *);

private slots:
    void on_actionOpen_Image_triggered();
    void on_actionOptions_triggered();
    void settings_changed(QMap<QString, int>*);
    void on_addPlayerButton_clicked();
    void on_removePlayerButton_clicked();
    void gridClicked(QMouseEvent*);
    void updateGrid(CombatParticipant*);
    void on_playerList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_actionTogglePlayerList_triggered();

private:
    Ui::CombatMap *ui;
    QList<CombatParticipant*> participants;
    int gridWidth;
    int gridHeight;
    void generateGrid();
    void updatePlayerList();
    void resetPlayers();
};

#endif // COMBATMAP_H

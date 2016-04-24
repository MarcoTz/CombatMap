#ifndef COMBATMAP_H
#define COMBATMAP_H

#include <QMainWindow>

namespace Ui {
class CombatMap;
}

class CombatMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit CombatMap(QWidget *parent = 0);
    ~CombatMap();

private slots:
    void on_actionOpen_Image_triggered();
    void on_actionOptions_triggered();
    void settings_changed(QMap<QString, int>*);

private:
    Ui::CombatMap *ui;
    int gridWidth;
    int gridHeight;
    void generateGrid();
};

#endif // COMBATMAP_H

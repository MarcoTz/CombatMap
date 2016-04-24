#include "combatmap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CombatMap w;
    w.show();

    return a.exec();
}

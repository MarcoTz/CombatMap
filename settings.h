#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_OK_clicked();

private:
    Ui::Settings *ui;
    QMap<QString, int> readSettings();
    void writeSettings();
    int gridWidth;
    int gridHeight;

signals:
    void settingsChanged(QMap<QString, int> *settings);

};

#endif // SETTINGS_H

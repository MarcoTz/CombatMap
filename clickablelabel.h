#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class clickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit clickableLabel(QWidget* parent=0);
signals:
    void clicked(QMouseEvent*);
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H

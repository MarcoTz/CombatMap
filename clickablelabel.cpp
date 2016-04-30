#include "clickablelabel.h"

clickableLabel::clickableLabel(QWidget* parent):QLabel(parent){
}

void clickableLabel::mousePressEvent(QMouseEvent *event){
    emit clicked(event);
}

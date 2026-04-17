#include "mycombobox.h"

#include <QMouseEvent>


myComboBox::myComboBox(QWidget *parent) : QComboBox(parent)
{

}

void myComboBox::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        emit on_ComboBox_click();
    }
    QComboBox::mousePressEvent(e);
}

#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include <QWidget>

class myComboBox : public QComboBox
{
    Q_OBJECT
public:
    myComboBox(QWidget* parent);
protected:
    void mousePressEvent(QMouseEvent *e) override;

signals:
    void on_ComboBox_click();
};

#endif // MYCOMBOBOX_H

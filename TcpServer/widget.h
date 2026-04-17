#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include "mycombobox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QTcpServer *sever;

public slots:
    void on_newClient_connect();

private slots:
    void on_btnListen_clicked();
    void on_readyRead_handler();
    void mdisconnected();
    void mstateChanged(QAbstractSocket::SocketState socketState);

    void on_pushButtonSend_clicked();
    void mComboBox_reflesh();

    void on_comboBoxChildren_activated(int index);

    void on_btnStopListen_clicked();

    void on_btnLineout_clicked();

private:
    Ui::Widget *ui;
    int childIndex;

    void mInsertTextByColor(Qt::GlobalColor, QString str);
};
#endif // WIDGET_H

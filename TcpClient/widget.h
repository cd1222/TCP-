#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpSocket>
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnDisconnect_clicked();

    void on_btnConnect_clicked();
    void mRead_Data_From_Sever();

    void on_btnSend_clicked();

    void onConnected();
    void onError(QAbstractSocket::SocketError);

    void onTimeOut();

private:
    Ui::Widget *ui;
    QTcpSocket *client;
    QTimer *timer;

    void mInsertTextByColor(Qt::GlobalColor, QString str);
};
#endif // WIDGET_H

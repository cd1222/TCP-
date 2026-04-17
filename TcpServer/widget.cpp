#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QTcpSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);

    sever = new QTcpServer(this);

    //bool QTcpServer::listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0)
    QHostAddress addr("192.168.1.110");

    connect(sever,SIGNAL(newConnection()),this,SLOT(on_newClient_connect()));
    connect(ui->comboBoxChildren,&myComboBox::on_ComboBox_click,this,&Widget::mComboBox_reflesh);

    ui->btnStopListen->setEnabled(false);
    ui->btnLineout->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);

    QList<QHostAddress> addresss = QNetworkInterface::allAddresses();
    for(QHostAddress addr : addresss){
        if(addr.protocol() == QAbstractSocket::IPv4Protocol){
            ui->comboBoxAddr->addItem(addr.toString());
        }
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_newClient_connect()
{
    //qDebug()<<"listen on_newClient_connect";
    if(sever->hasPendingConnections())
    {
        QTcpSocket *connected = sever->nextPendingConnection();
        //qDebug()<<"address:"<<connected->peerAddress()<<"host: "<<connected->peerPort();
        ui->textEditRev->insertPlainText("新的连接[客户端地址： "+ connected->peerAddress().toString() + "端口号： " + QString::number(connected->peerPort())+"]\n");

        connect(connected,SIGNAL(readyRead()),this,SLOT(on_readyRead_handler()));
        //void QAbstractSocket::disconnected()
        //connect(connected,SIGNAL(disconnected()),this,SLOT(mdisconnected()));
        //void QAbstractSocket::stateChanged(QAbstractSocket::SocketState socketState)
        connect(connected,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(mstateChanged(QAbstractSocket::SocketState)));
    }
    if(!ui->pushButtonSend->isEnabled())
    {
        ui->pushButtonSend->setEnabled(true);
    }
}


void Widget::on_btnListen_clicked()
{
    //QHostAddress addr("192.168.1.110");
    int port = ui->lineEditPort->text().toInt();

    if(!sever->listen(QHostAddress(ui->comboBoxAddr->currentText()), port)){
        QMessageBox msgBox;
        msgBox.setWindowTitle("监听失败");
        msgBox.setText("端口号被占用");
        msgBox.exec();
        return;
    }
    ui->btnListen->setEnabled(false);
    ui->btnStopListen->setEnabled(true);
    ui->btnLineout->setEnabled(true);
}

void Widget::on_readyRead_handler()
{
    QTcpSocket *temSock = qobject_cast<QTcpSocket *>(sender());

    QByteArray revData = temSock->readAll();
    //ui->textEditRev->insertPlainText("客户端： "+revData);
    mInsertTextByColor(Qt::black,"客户端："+revData+'\n');
}

void Widget::mdisconnected()
{
    QTcpSocket *temSock = qobject_cast<QTcpSocket *>(sender());
    ui->textEditRev->insertPlainText("客户端断开");
    temSock->deleteLater();
}

void Widget::mstateChanged(QAbstractSocket::SocketState socketState)
{
    QTcpSocket *temSock = qobject_cast<QTcpSocket *>(sender());
    qDebug()<<"mstateChanged "<< socketState;
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
    //case QAbstractSocket::ClosingState:
        ui->textEditRev->insertPlainText("客户端断开\n");
        temSock->deleteLater();
        mComboBox_reflesh();
        break;
    case QAbstractSocket::ConnectingState:
    case QAbstractSocket::ConnectedState:
        ui->textEditRev->insertPlainText("客户端接入\n");
        break;

    }
}

void Widget::on_pushButtonSend_clicked()
{
    QList<QTcpSocket*> tcpSocketClients = sever->findChildren<QTcpSocket*>();
    QByteArray sendData = ui->textEditSend->toPlainText().toStdString().c_str();
    if(ui->comboBoxChildren->currentText() != "all" && ui->comboBoxChildren->currentIndex() != -1)
    {
        tcpSocketClients[childIndex]->write(sendData);
    }else{
        for(QTcpSocket* tmp:tcpSocketClients)
            tmp->write(sendData);
    }
    mInsertTextByColor(Qt::red,"本机"+sendData+'\n');
}

void Widget::mComboBox_reflesh()
{
    ui->comboBoxChildren->clear();

    QList<QTcpSocket*> tcpSocketClients = sever->findChildren<QTcpSocket*>();
    for(QTcpSocket* tmp:tcpSocketClients)
        if(tmp != nullptr)
            ui->comboBoxChildren->addItem(QString::number(tmp->peerPort()));
    ui->comboBoxChildren->addItem("all");
}

void Widget::on_comboBoxChildren_activated(int index)
{
    childIndex = index;
}

void Widget::on_btnStopListen_clicked()
{
    QList<QTcpSocket*> tcpSocketClients = sever->findChildren<QTcpSocket*>();
    for(QTcpSocket* tmp:tcpSocketClients)
        tmp->close();

    sever->close();
    ui->btnListen->setEnabled(true);
    ui->btnStopListen->setEnabled(false);
    ui->btnLineout->setEnabled(false);
}

void Widget::on_btnLineout_clicked()
{
    on_btnStopListen_clicked();
    delete sever;
    this->close();
}

void Widget::mInsertTextByColor(Qt::GlobalColor color, QString str)
{
    QTextCursor cursor = ui->textEditRev->textCursor();
    QTextCharFormat format;
    format.setForeground(QBrush(QColor(color)));
    cursor.setCharFormat(format);
    cursor.insertText(str);
}

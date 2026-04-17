#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);

    ui->btnDisconnect->setEnabled(false);
    ui->btnSend->setEnabled(false);

    client = new QTcpSocket(this);
    connect(client,SIGNAL(readyRead()),this,SLOT(mRead_Data_From_Sever()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnDisconnect_clicked()
{
    client->disconnectFromHost();

    client->close();
    ui->textEditRev->append("中止连接！\n");
    ui->btnConnect->setEnabled(true);
    ui->lineEditIPAddr->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->btnSend->setEnabled(false);
    ui->btnDisconnect->setEnabled(false);
}

void Widget::on_btnConnect_clicked()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(5000);
   // virtual void  connectToHost(const QHostAddress &address, quint16 port, QIODevice::OpenMode openMode = ReadWrite)
    client->connectToHost(ui->lineEditIPAddr->text(),ui->lineEditPort->text().toInt());

    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    connect(client,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(client,SIGNAL(QAbstractSocket::SocketError),this,SLOT(onError(QAbstractSocket::SocketError)));
    this->setEnabled(false);
    timer->start();
}

void Widget::mRead_Data_From_Sever()
{
    ui->textEditRev->moveCursor(QTextCursor::End);
    ui->textEditRev->ensureCursorVisible();
    mInsertTextByColor(Qt::black,"服务器："+client->readAll()+'\n');
}

void Widget::on_btnSend_clicked()
{
    QByteArray sendData = ui->textEditSend->toPlainText().toUtf8();
    client->write(sendData);
    //ui->textEditRev->insertPlainText(ui->textEditSend->toPlainText().toUtf8());

    mInsertTextByColor(Qt::red,"本机"+sendData+'\n');

}

void Widget::onConnected()
{
    this->setEnabled(true);
    ui->textEditRev->append("连接服务器成功！\n");
    ui->btnConnect->setEnabled(false);
    ui->lineEditIPAddr->setEnabled(false);
    ui->lineEditPort->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->btnSend->setEnabled(true);
}

void Widget::onError(QAbstractSocket::SocketError error)
{
    qDebug()<<"连接错误"<<error;
    this->setEnabled(true);
}

void Widget::onTimeOut()
{
    ui->textEditRev->insertPlainText("连接超时");
    client->abort();
    this->setEnabled(true);
}

void Widget::mInsertTextByColor(Qt::GlobalColor color, QString str)
{
    QTextCursor cursor = ui->textEditRev->textCursor();
    QTextCharFormat format;
    format.setForeground(QBrush(QColor(color)));
    cursor.setCharFormat(format);

    cursor.insertText(str);
}

#pragma once

#include <QWidget>
#include <qtcpsocket.h>
#include <qtcpserver.h>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QApplication>

struct trapStruct {
    int item1;
    int x1;
    int y1;
    int item2;
    int x2;
    int y2;
    int OK_status;
};
class trap_server : public QWidget
{
    Q_OBJECT

public:
    explicit trap_server(QStackedWidget*,QWidget* parent = 0);

    QTcpServer* m_server;

    QList<QTcpSocket*> m_sockets;  

    void startServer();  

    void SendMessage(trapStruct);

    void changeToGamemode();

public slots:
    void slot_newConnection();   

    trapStruct slot_readMessage();   
private:
    QStackedWidget* baseWidget;
    trapStruct trap_each;
    int count;
};

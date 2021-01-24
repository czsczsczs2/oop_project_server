#pragma once

#include <QWidget>
#include <qtcpsocket.h>
#include <qtcpserver.h>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QApplication>

struct recv_Struct {
    int x1;
    int y1;
    int acting_1;
    int direction_1;
    int jumped_1;
    int winner_1;

    int x2;
    int y2;
    int acting_2;
    int direction_2;
    int jumped_2;
    int winner_2;

    int x3;
    int y3;
    int acting_3;
    int direction_3;
    int jumped_3;
    int winner_3;

    int x4;
    int y4;
    int acting_4;
    int direction_4;
    int jumped_4;
    int winner_4;
};

struct SendStruct {
    int identity;
    int x;
    int y;
    int acting;
    int direction;
    int jumped;
    int winner;
};

class gamemode_server : public QWidget
{
	Q_OBJECT

public:
    explicit gamemode_server(QStackedWidget*,QWidget* parent = 0);

    QTcpServer* m_server;

    QList<QTcpSocket*> m_sockets;   // 連線到server的所有客戶.  連結串列方式, 在伺服器端的一個備份(客戶端的socket)

    void startServer();    // 啟動一個server

    void SendMessage(recv_Struct package);

    void disconnect();

    void timerEvent(QTimerEvent*);
public slots:
    void slot_newConnection();    //  對應客戶端的 connectToHost();

    SendStruct slot_readMessage();   // 每一個socket繫結
private:
    QStackedWidget* baseWidget;
    recv_Struct package;
    SendStruct pos;
    int time;
};

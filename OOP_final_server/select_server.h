#pragma once

#include <QWidget>
#include <qtcpsocket.h>
#include <qtcpserver.h>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QApplication>

class select_server : public QWidget
{
	Q_OBJECT

public:
    explicit select_server(QStackedWidget*,QWidget* parent = 0);

    QTcpServer* m_server;

    QList<QTcpSocket*> m_sockets;   

    void startServer();    

    void SendMessage();

    void timerEvent(QTimerEvent*);

    void changeToTrap();
public slots:
    void slot_newConnection();    

    void slot_readMessage();   
private:
    QStackedWidget* baseWidget;
    int time;
    QString str;
};

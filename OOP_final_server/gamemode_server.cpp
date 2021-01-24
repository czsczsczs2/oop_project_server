#include "gamemode_server.h"
#include <iostream>
using namespace std;
gamemode_server::gamemode_server(QStackedWidget* stackWidget,QWidget* parent)
    : QWidget(parent)
{
    baseWidget = stackWidget;
    time = startTimer(100);
    package.x1 = 5;
    package.x2 = 5;
    package.x3 = 5;
    package.x4 = 5;
    package.y1 = 0;
    package.y2 = 0;
    package.y3 = 0;
    package.y4 = 0;
    package.acting_1 = 0;
    package.acting_2 = 0;
    package.acting_3 = 0;
    package.acting_4 = 0;
    package.direction_1 = 0;
    package.direction_2 = 0;
    package.direction_3 = 0;
    package.direction_4 = 0;
    package.jumped_1 = 0;
    package.jumped_2 = 0;
    package.jumped_3 = 0;
    package.jumped_4 = 0;
    package.winner_1 = 0;
    package.winner_2 = 0;
    package.winner_3 = 0;
    package.winner_4 = 0;
    startServer();
}
void gamemode_server::startServer()
{
    m_server = new QTcpServer(this);

    m_server->listen(QHostAddress::Any, 4896);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));
}
void gamemode_server::slot_newConnection()
{
    QTcpSocket* socket = m_server->nextPendingConnection();

    m_sockets.push_back(socket);

    connect(socket, SIGNAL(readyRead()), this, SLOT(slot_readMessage()));

}


SendStruct gamemode_server::slot_readMessage()
{
    QTcpSocket* socket = (QTcpSocket*)QObject::sender();
    socket->read((char*)&pos, sizeof(pos));

    if (pos.identity == 1) {
        package.x1 = pos.x;
        package.y1 = pos.y;
        package.acting_1 = pos.acting;
        package.direction_1 = pos.direction;
        package.jumped_1 = pos.jumped;
        package.winner_1 = pos.winner;
        if (pos.winner) {
            package.winner_2 = pos.winner;
            package.winner_3 = pos.winner;
            package.winner_4 = pos.winner;
            SendMessage(package);
            disconnect();
        }
    }
    else if (pos.identity == 2) {
        package.x2 = pos.x;
        package.y2 = pos.y;
        package.acting_2 = pos.acting;
        package.direction_2 = pos.direction;
        package.jumped_2 = pos.jumped;
        package.winner_2 = pos.winner;
        if (package.winner_2) {
            package.winner_1 = pos.winner;
            package.winner_3 = pos.winner;
            package.winner_4 = pos.winner;
            SendMessage(package);
            disconnect();
        }
    }
    else if (pos.identity == 3) {
        package.x3 = pos.x;
        package.y3 = pos.y;
        package.acting_3 = pos.acting;
        package.direction_3 = pos.direction;
        package.jumped_3 = pos.jumped;
        package.winner_3 = pos.winner;
        if (package.winner_3) {
            package.winner_1 = pos.winner;
            package.winner_2 = pos.winner;
            package.winner_4 = pos.winner;
            SendMessage(package);
            disconnect();
        }
    }
    else if (pos.identity == 4) {
        package.x4 = pos.x;
        package.y4 = pos.y;
        package.acting_4 = pos.acting;
        package.direction_4 = pos.direction;
        package.jumped_4 = pos.jumped;
        package.winner_4 = pos.winner;
        if (package.winner_4) {
            package.winner_1 = pos.winner;
            package.winner_2 = pos.winner;
            package.winner_3 = pos.winner;
            SendMessage(package);
            disconnect();
        }
    }
    return pos;
}

void gamemode_server::SendMessage(recv_Struct package) {
    for (int i = 0; i < m_sockets.size(); i++) {
        m_sockets[i]->write((char*)&package, sizeof(package));
    }
}

void gamemode_server::timerEvent(QTimerEvent* event) {
    SendMessage(package);
}
void gamemode_server::disconnect() {
    for (int i = 0; i < m_sockets.size(); i++) {
        m_sockets[i]->disconnectFromHost();
        m_sockets[i]->close();
    }
}
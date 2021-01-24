#include "trap_server.h"
#include "gamemode_server.h"
#include "OOP_final_server.h"
//trap server
trap_server::trap_server(QStackedWidget* stackedWidget,QWidget* parent)
    : QWidget(parent)
{
    baseWidget = stackedWidget;
    count = 0;
    trap_each.item1 = 0;
    trap_each.x1 = 0;
    trap_each.y1 = 0;
    trap_each.item2 = 0;
    trap_each.x2 = 0;
    trap_each.y2 = 0;
    trap_each.OK_status = 100;
    startServer();
}
void trap_server::startServer()
{
    m_server = new QTcpServer(this);

    m_server->listen(QHostAddress::Any, 1234);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));
}
void trap_server::slot_newConnection()
{
    // 把新加入的socket放入連結串列中
    QTcpSocket* socket = m_server->nextPendingConnection();

    m_sockets.push_back(socket);

    connect(socket, SIGNAL(readyRead()), this, SLOT(slot_readMessage()));
}

// 每一個socket處理收到訊息的函式
trapStruct trap_server::slot_readMessage()
{
    QTcpSocket* socket = (QTcpSocket*)QObject::sender();  // 獲得是哪個socket收到了訊息
    socket->read((char*)&trap_each, sizeof(trap_each));
    count++;
    if (count == 4) {
        trap_each.OK_status = 200;
        changeToGamemode();
        SendMessage(trap_each);
    }
    else
        SendMessage(trap_each);
    return trap_each;
}

void trap_server::SendMessage(trapStruct trap_each) {
    for (int i = 0; i < m_sockets.size(); i++) {
        m_sockets[i]->write((char*)&trap_each, sizeof(trap_each));
    }
}
void trap_server::changeToGamemode() {
    gamemode_server* nextWigdet = new gamemode_server(baseWidget);
    baseWidget->addWidget(nextWigdet);
    baseWidget->setCurrentWidget(nextWigdet);


//    delete nextWigdet;
}
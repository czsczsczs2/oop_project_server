#include "select_server.h"
#include "gamemode_server.h"
#include "trap_server.h"
#include "ui_OOP_final_server.h"

select_server::select_server(QStackedWidget* stackWidget,QWidget* parent)
    : QWidget(parent)
{
    baseWidget = stackWidget;
    time = startTimer(200);
    str = "1111";
    startServer();
}
void select_server::startServer()
{
    m_server = new QTcpServer(this);

    m_server->listen(QHostAddress::Any, 8000);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));
}
void select_server::slot_newConnection()
{
    // ��s�[�J��socket��J�s����C��
    QTcpSocket* socket = m_server->nextPendingConnection();

    m_sockets.push_back(socket);

    connect(socket, SIGNAL(readyRead()), this, SLOT(slot_readMessage()));
}

// �C�@��socket�B�z����T�����禡
void select_server::slot_readMessage()
{
    QTcpSocket* socket = (QTcpSocket*)QObject::sender();  // ��o�O����socket����F�T��
    str = socket->readAll();
    if (str[0] == "F") {
        changeToTrap();
        SendMessage();
    }
}
void select_server::SendMessage() {
    for (int i = 0; i < m_sockets.size(); i++) {
        m_sockets[i]->write(str.toUtf8());
    }
}
void select_server::changeToTrap() {
    trap_server* nextWigdet = new trap_server(baseWidget);
    baseWidget->addWidget(nextWigdet);
    baseWidget->setCurrentWidget(nextWigdet);
}
void select_server::timerEvent(QTimerEvent* event) {
    SendMessage();
}
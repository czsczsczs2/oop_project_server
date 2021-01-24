#include "OOP_final_server.h"
OOP_final_server::OOP_final_server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    stack = new QStackedWidget();
    stack->addWidget(new select_server(stack));
    setCentralWidget(stack);
}

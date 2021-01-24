#pragma once
#include "gamemode_server.h"
#include "select_server.h"
#include "trap_server.h"
#include "ui_OOP_final_server.h"
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QApplication>

class OOP_final_server : public QMainWindow
{
    Q_OBJECT

public:
    OOP_final_server(QWidget *parent = Q_NULLPTR);
private:
    Ui::OOP_final_serverClass ui;
    QStackedWidget* stack;
};
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab4_OptimalTreeApp.h"

class lab4_OptimalTreeApp : public QMainWindow
{
    Q_OBJECT

public:
    lab4_OptimalTreeApp(QWidget *parent = nullptr);
    ~lab4_OptimalTreeApp();

private:
    Ui::lab4_OptimalTreeAppClass ui;
};


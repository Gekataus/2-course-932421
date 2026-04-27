#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BinarySearchTreeApp.h"

class BinarySearchTreeApp : public QMainWindow
{
    Q_OBJECT

public:
    BinarySearchTreeApp(QWidget *parent = nullptr);
    ~BinarySearchTreeApp();

private:
    Ui::BinarySearchTreeAppClass ui;
};


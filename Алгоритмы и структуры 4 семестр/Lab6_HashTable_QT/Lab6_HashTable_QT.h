#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab6_HashTable_QT.h"

class Lab6_HashTable_QT : public QMainWindow
{
    Q_OBJECT

public:
    Lab6_HashTable_QT(QWidget *parent = nullptr);
    ~Lab6_HashTable_QT();

private:
    Ui::Lab6_HashTable_QTClass ui;
};


#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QHeaderView>
#include "hashtable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void buildTable();

    HashTable* hashTable_;
    QTableWidget* table_;
};
#include <QString>
#include <QTableWidgetItem>
#include <sstream>
#include <iostream>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Hash Table");
    resize(600, 400);

    table_ = new QTableWidget(this);
    table_->setColumnCount(2);
    table_->setHorizontalHeaderLabels(QStringList() << "h(k)" << "Key -> Value");

    table_->verticalHeader()->setVisible(false);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_->setSelectionMode(QAbstractItemView::NoSelection);
    table_->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setCentralWidget(table_);

    // Создание хеш-таблицы
    hashTable_ = new HashTable(10);

    // Добавление элементов
    hashTable_->insert(25, "Двадцать_пять");
    hashTable_->insert(10, "Десять");
    hashTable_->insert(80, "Восемьдесят");
    hashTable_->insert(33, "Тридцать_три");
    hashTable_->insert(12, "Двенадцать");

    // Заполнение таблицы
    buildTable();
}

MainWindow::~MainWindow()
{
    delete hashTable_;
}

void MainWindow::buildTable()
{
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    hashTable_->printTableToConsole();

    std::cout.rdbuf(old);

    QString output = QString::fromStdString(buffer.str());
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    table_->setRowCount(lines.size());

    for (int i = 0; i < lines.size(); i++)
    {
        QString line = lines[i];
        int colonPos = line.indexOf(':');

        if (colonPos != -1)
        {
            QString index = line.left(colonPos).trimmed();
            QString content = line.mid(colonPos + 1).trimmed();

            table_->setItem(i, 0, new QTableWidgetItem(index));

            if (content == "None")
            {
                table_->setItem(i, 1, new QTableWidgetItem("EMPTY"));
            }
            else
            {
                table_->setItem(i, 1, new QTableWidgetItem(content));
            }
        }
    }
}
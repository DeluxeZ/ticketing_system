#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ticket.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QList<int> train;  //储存符合查询车次要求的列车编号
    static int departure_id;  //储存用户所选起点站id
    static int destination_id;//储存用户所选目的地id
    static QString date;      //储存用户所选日期

private slots:
    void on_queryButton_clicked();
    void on_reset_clicked();


private:
    Ui::MainWindow *ui;
    ticket *tic;
};

#endif // MAINWINDOW_H

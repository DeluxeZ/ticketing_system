#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticket.h"
#include <QSqlQuery>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

QList<int> MainWindow::train;
int MainWindow::departure_id = 0;
int MainWindow::destination_id = 0;
QString MainWindow::date = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("铁路购票系统");
    this->setStyleSheet("background-color:#DDD;");
    ui->calendarWidget->setMinimumDate(QDate::currentDate());
    ui->departure->setStyleSheet("border-radius:3px;border:1px solid black;text-align:center;background-color:white");
    ui->destination->setStyleSheet("border-radius:3px;border:1px solid black;text-align:center;background-color:white");
    ui->calendarWidget->setStyleSheet("background-color:#bbffaa;color:#0033ff");
    ui->queryButton->setStyleSheet("QPushButton{border-radius:3px;border:none;background-color:#0066ff;color:white;font-family:微软雅黑;}"
                                   "QPushButton:hover{background-color:#0033ff}");
    ui->reset->setStyleSheet("QPushButton{border-radius:3px;border:none;background-color:#0066ff;color:white;font-family:微软雅黑;}"
                             "QPushButton:hover{background-color:#0033ff}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_queryButton_clicked()
{
    if ( ui->departure->currentIndex() == 0 ){
        QMessageBox::information(NULL, "请注意", "请选择出发地");
    }
    else if ( ui->destination->currentIndex() == 0 ){
        QMessageBox::information(NULL, "请注意", "请选择目的地");
    }
    else{
        train.clear();
        MainWindow::date = ui->calendarWidget->selectedDate().toString("MM月dd日 dddd");
        departure_id = ui->departure->currentIndex();
        destination_id = ui->destination->currentIndex();
        if ( departure_id >= destination_id ){
            QMessageBox::information(NULL,"注意","仅支持由北京向东三省的列车，请重新选择");
            ui->departure->setCurrentIndex(0);
            ui->destination->setCurrentIndex(0);
        }
        else {
            QString string = "%" + QString::number(departure_id,10) + "%" + QString::number(destination_id,10) + "%";
            QSqlQuery query_train_info;
            query_train_info.exec("SELECT train_id FROM train_info WHERE station_passed LIKE '"+ string + "'");
            while ( query_train_info.next() ) {
                train << query_train_info.value(0).toInt();
            }
            tic = new ticket();
            tic->show();
        }
    }
}

void MainWindow::on_reset_clicked()
{
    ui->departure->setCurrentIndex(0);
    ui->destination->setCurrentIndex(0);
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
}


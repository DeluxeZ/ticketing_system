#include "details.h"
#include "ui_details.h"
#include <ticket.h>
#include <QSqlQuery>
#include <QDebug>
#include <QListWidgetItem>
#include <QStandardItem>

details::details(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::details)
{
    ui->setupUi(this);
    ui->detail->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color:rgb(118,154,225);color: white;}");
    ui->detail->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->close->setStyleSheet("QPushButton{border-radius:3px;border:1px solid rgb(200,200,200);background-color:rgb(230,230,230)}"
                             "QPushButton:hover{background-color:rgb(240,240,240)}");
    this->setWindowTitle("车票详情");
    QStringList list_leavetime;
    QStringList list_arrivetime;
    QStringList list_station;
    QSqlQuery query;
    query.exec("select station_id, arrive_time, leave_time from pass_info where train_id = " + QString::number(ticket::T));
    QSqlQuery query_station;
    while ( query.next() ) {
        int station_id = query.value(0).toInt();
        query_station.exec("select station_name from station_info where station_id = " + QString::number(station_id));
        query_station.next();
        QString arrive_time = query.value(1).toString();
        if ( arrive_time == NULL ){
            arrive_time = "--";
        }
        else {
            arrive_time = arrive_time.mid(0,5);
        }
        QString leave_time = query.value(2).toString();
        if( leave_time == NULL ){
            leave_time = "--";
        }
        else {
            leave_time = leave_time.mid(0,5);
        }
        list_station.append(query_station.value(0).toString());
        list_arrivetime.append(arrive_time);
        list_leavetime.append(leave_time);
    }

    for( int i = 0; i < list_station.length(); i ++ ){
        ui->detail->insertRow(i);
        ui->detail->setItem(i, 0, new QTableWidgetItem(list_station[i]));
        ui->detail->setItem(i, 1, new QTableWidgetItem(list_arrivetime[i]));
        ui->detail->setItem(i, 2, new QTableWidgetItem(list_leavetime[i]));
    }
}

details::~details()
{
    delete ui;
}

void details::on_close_clicked()
{
    this->hide();
}

#include "mainwindow.h"
#include "ticket.h"
#include "ui_ticket.h"
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
#include <QString>
#include <paysucc.h>
#include <details.h>

QList<int> ticket::Train_id;
QList<int> ticket::Departure_id;
QList<int> ticket::Destination_id;
QList<QString> ticket::Train_number;
QString ticket::Departure;
QString ticket::Destination;
QList<QString> ticket::Leavetime;
QList<QString> ticket::Arrivetime;
QList<int> ticket::Price_hardseat;
QList<int> ticket::Price_hardbed;
QList<int> ticket::Price_softbed;
QList<int> ticket::Count_hardseat;
QList<int> ticket::Count_tophardbed;
QList<int> ticket::Count_midhardbed;
QList<int> ticket::Count_bothardbed;
QList<int> ticket::Count_softbed;
int ticket::T = 0;

ticket::ticket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ticket)
{
    ui->setupUi(this);
    this->setWindowTitle("车票查询");
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,50);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnWidth(4,50);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,100);
    ui->tableWidget->setColumnWidth(7,100);
    ui->close->setStyleSheet("QPushButton{border-radius:3px;border:1px solid rgb(200,200,200);background-color:rgb(230,230,230)}"
                             "QPushButton:hover{background-color:rgb(240,240,240)}");
    ui->refresh->setStyleSheet("QPushButton{border-radius:3px;border:1px solid rgb(200,200,200);background-color:rgb(230,230,230)}"
                               "QPushButton:hover{background-color:rgb(240,240,240)}");
    ui->details->setStyleSheet("QPushButton{border-radius:3px;border:1px solid rgb(200,200,200);background-color:rgb(230,230,230)}"
                               "QPushButton:hover{background-color:rgb(240,240,240)}");
    ui->pushButton->setStyleSheet("QPushButton{border-radius:3px;background-color:#0066ff;color:white}"
                                  "QPushButton:hover{background-color:#0033ff}");
    ui->tableWidget->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color:rgb(118,154,225);color: white;}");

    QSqlQuery query_train_info;
    QSqlQuery query_ticket_info;
    QSqlQuery query_pass_info;
    QSqlQuery query_station_info;
    int train, departure, destination, price_hardseat, price_hardbed, price_softbed, count_hardseat;
    int count_tophardbed,count_midhardbed,count_bothardbed,count_hardbed,count_softbed;
    QString train_number, departure_station,destination_station,arrive_time,leave_time;

    Train_id.clear();
    Arrivetime.clear();
    Leavetime.clear();
    Destination.clear();
    Departure.clear();
    Train_number.clear();
    Departure_id.clear();
    Destination_id.clear();
    Price_hardseat.clear();
    Price_hardbed.clear();
    Price_softbed.clear();
    Count_hardseat.clear();
    Count_tophardbed.clear();
    Count_midhardbed.clear();
    Count_bothardbed.clear();
    Count_softbed.clear();


    for( int i = 0; i < MainWindow::train.length(); i ++ ){
        train = MainWindow::train[i];
        departure = MainWindow::departure_id;
        destination = MainWindow::destination_id;

        query_train_info.exec("select train_number from train_info where train_id = " + QString::number(train));
        query_train_info.next();
        train_number = query_train_info.value(0).toString();
        query_station_info.exec("select station_name from station_info where station_id = " + QString::number(departure));
        query_station_info.next();
        departure_station = query_station_info.value(0).toString();
        query_station_info.exec("select station_name from station_info where station_id = " + QString::number(destination));
        query_station_info.next();
        destination_station = query_station_info.value(0).toString();
        query_pass_info.exec("select leave_time from pass_info where station_id = " + QString::number(departure)
                                 + " and train_id = " + QString::number(train));
        query_pass_info.next();
        leave_time = query_pass_info.value(0).toString();
        query_pass_info.exec("select arrive_time from pass_info where station_id = " + QString::number(destination)
                                 + " and train_id = " + QString::number(train));
        query_pass_info.next();
        arrive_time = query_pass_info.value(0).toString();
        query_ticket_info.exec("select * from ticket_info where from_id = " + QString::number(departure) +
                          " and to_id = " + QString::number(destination) + " and train_id = " + QString::number(train));
        query_ticket_info.next();
        price_hardseat = query_ticket_info.value(3).toInt();
        price_hardbed = query_ticket_info.value(4).toInt();
        price_softbed = query_ticket_info.value(5).toInt();
        count_hardseat = query_ticket_info.value(6).toInt();
        count_tophardbed = query_ticket_info.value(7).toInt();
        count_midhardbed = query_ticket_info.value(8).toInt();
        count_bothardbed = query_ticket_info.value(9).toInt();
        count_hardbed = count_bothardbed + count_midhardbed + count_tophardbed;
        count_softbed = query_ticket_info.value(10).toInt();

        Arrivetime << arrive_time;
        Leavetime << leave_time;
        Destination = destination_station;
        Departure = departure_station;
        Train_number << train_number;
        Train_id << train;
        Departure_id << departure;
        Destination_id << destination;
        Price_hardseat << price_hardseat;
        Price_hardbed << price_hardbed;
        Price_softbed << price_softbed;
        Count_hardseat << count_hardseat;
        Count_tophardbed << count_tophardbed;
        Count_midhardbed << count_midhardbed;
        Count_bothardbed << count_bothardbed;
        Count_softbed << count_softbed;


        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(train_number));
        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(departure_station));
        ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(destination_station));
        ui->tableWidget->item(i,2)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(leave_time.mid(0,5)));
        ui->tableWidget->item(i,3)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(arrive_time.mid(0,5)));
        ui->tableWidget->item(i,4)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem( "余票：" + QString::number(count_hardseat) + " 票价：" + QString::number(price_hardseat) ));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem( "余票：" + QString::number(count_hardbed) + " 票价：" + QString::number(price_hardbed) ));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem( "余票：" + QString::number(count_softbed) + " 票价：" + QString::number(price_softbed) ));
    }
}

ticket::~ticket()
{
    delete ui;
}

void ticket::on_refresh_clicked()
{
    for (int i = 0; i < MainWindow::train.length(); i ++ ) {
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query_train_info;
    QSqlQuery query_ticket_info;
    QSqlQuery query_pass_info;
    QSqlQuery query_station_info;
    int train, departure, destination, price_hardseat, price_hardbed, price_softbed, count_hardseat;
    int count_tophardbed,count_midhardbed,count_bothardbed,count_hardbed,count_softbed;
    QString train_number, departure_station,destination_station,arrive_time,leave_time;

    Train_id.clear();
    Arrivetime.clear();
    Leavetime.clear();
    Destination.clear();
    Departure.clear();
    Train_number.clear();
    Departure_id.clear();
    Destination_id.clear();
    Price_hardseat.clear();
    Price_hardbed.clear();
    Price_softbed.clear();
    Count_hardseat.clear();
    Count_tophardbed.clear();
    Count_midhardbed.clear();
    Count_bothardbed.clear();
    Count_softbed.clear();

    for( int i = 0; i < MainWindow::train.length(); i ++ ){
        train = MainWindow::train[i];
        departure = MainWindow::departure_id;
        destination = MainWindow::destination_id;

        query_train_info.exec("select train_number from train_info where train_id = " + QString::number(train));
        query_train_info.next();
        train_number = query_train_info.value(0).toString();
        query_station_info.exec("select station_name from station_info where station_id = " + QString::number(departure));
        query_station_info.next();
        departure_station = query_station_info.value(0).toString();
        query_station_info.exec("select station_name from station_info where station_id = " + QString::number(destination));
        query_station_info.next();
        destination_station = query_station_info.value(0).toString();
        query_pass_info.exec("select leave_time from pass_info where station_id = " + QString::number(departure)
                                 + " and train_id = " + QString::number(train));
        query_pass_info.next();
        leave_time = query_pass_info.value(0).toString();
        query_pass_info.exec("select arrive_time from pass_info where station_id = " + QString::number(destination)
                                 + " and train_id = " + QString::number(train));
        query_pass_info.next();
        arrive_time = query_pass_info.value(0).toString();
        query_ticket_info.exec("select * from ticket_info where from_id = " + QString::number(departure) +
                          " and to_id = " + QString::number(destination) + " and train_id = " + QString::number(train));
        query_ticket_info.next();
        price_hardseat = query_ticket_info.value(3).toInt();
        price_hardbed = query_ticket_info.value(4).toInt();
        price_softbed = query_ticket_info.value(5).toInt();
        count_hardseat = query_ticket_info.value(6).toInt();
        count_tophardbed = query_ticket_info.value(7).toInt();
        count_midhardbed = query_ticket_info.value(8).toInt();
        count_bothardbed = query_ticket_info.value(9).toInt();
        count_hardbed = count_bothardbed + count_midhardbed + count_tophardbed;
        count_softbed = query_ticket_info.value(10).toInt();

        Arrivetime << arrive_time;
        Leavetime << leave_time;
        Destination = destination_station;
        Departure = departure_station;
        Train_number << train_number;
        Train_id << train;
        Departure_id << departure;
        Destination_id << destination;
        Price_hardseat << price_hardseat;
        Price_hardbed << price_hardbed;
        Price_softbed << price_softbed;
        Count_hardseat << count_hardseat;
        Count_tophardbed << count_tophardbed;
        Count_midhardbed << count_midhardbed;
        Count_bothardbed << count_bothardbed;
        Count_softbed << count_softbed;

        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(train_number));
        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(departure_station));
        ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(destination_station));
        ui->tableWidget->item(i,2)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(leave_time.mid(0,5)));
        ui->tableWidget->item(i,3)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(arrive_time.mid(0,5)));
        ui->tableWidget->item(i,4)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem( "余票：" + QString::number(count_hardseat) + " 票价：" + QString::number(price_hardseat) ));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem( "余票：" + QString::number(count_hardbed) + " 票价：" + QString::number(price_hardbed) ));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem( "余票：" + QString::number(count_softbed) + " 票价：" + QString::number(price_softbed) ));
    }
}

void ticket::on_pushButton_clicked()
{
    QList<QTableWidgetItem*> item1 = ui->tableWidget->selectedItems();
    if ( item1.isEmpty() ){
        QMessageBox::information(NULL,"注意","请选择您要购买的车次座位");
    }
    else{
        QTableWidgetItem *item = item1.first();
        int row = item->row();
        int col = item->column();
        ticket::T = row;
        QString str = item->text();
        QSqlQuery query;
        int count;
        if ( col == 5 ){
            count = Count_hardseat[row];
        }
        else if ( col == 6 ){
            count = Count_tophardbed[row] + Count_midhardbed[row] + Count_bothardbed[row];
        }
        else{
            count = Count_softbed[row];
        }

        if ( count == 0 ){
            QMessageBox::information(NULL,"注意","无余票");
        }
        else{
            QMessageBox::StandardButton result = QMessageBox::information(NULL, "注意", "是否购买", QMessageBox::Yes | QMessageBox::No);
            if ( result == QMessageBox::Yes ){
                QSqlQuery query_ticket;
                if ( col == 5 ){
                    query_ticket.exec("update ticket_info set count_hardseat = " + QString::number(Count_hardseat[row]-1) + " where train_id = "
                                      + QString::number(MainWindow::train[row]) + " and not (from_id >= " + QString::number(Destination_id[row]) +
                                      " or to_id <= " + QString::number(Departure_id[row]) + ");");
                }
                else if ( col == 6 ){
                    if ( Count_tophardbed[row] != 0 ){
                        query_ticket.exec("update ticket_info set count_tophardbed = " + QString::number(Count_tophardbed[row]-1) + " where train_id = "
                                          + QString::number(MainWindow::train[row]) + " and not (from_id >= " + QString::number(Destination_id[row]) +
                                          " or to_id <= " + QString::number(Departure_id[row]) + ");");
                    }
                    else if ( Count_midhardbed[row] != 0 ) {
                        query_ticket.exec("update ticket_info set count_midhardbed = " + QString::number(Count_midhardbed[row]-1) + " where train_id = "
                                          + QString::number(MainWindow::train[row]) + " and not (from_id >= " + QString::number(Destination_id[row]) +
                                          " or to_id <= " + QString::number(Departure_id[row]) + ");");
                    }
                    else {
                        query_ticket.exec("update ticket_info set count_bothardbed = " + QString::number(Count_bothardbed[row] - 1) + " where train_id = "
                                          + QString::number(MainWindow::train[row]) + " and not (from_id >= " + QString::number(Destination_id[row]) +
                                          " or to_id <= " + QString::number(Departure_id[row]) + ");");
                    }
                }
                else {
                    query_ticket.exec("update ticket_info set count_softbed = " + QString::number(Count_softbed[row] - 1) + " where train_id = "
                                      + QString::number(MainWindow::train[row]) + " and not (from_id >= " + QString::number(Destination_id[row]) +
                                      " or to_id <= " + QString::number(Departure_id[row]) + ");");
                }

                pay = new paysucc();
                pay->show();
            }
        }
    }
}

void ticket::on_details_clicked()
{
    QList<QTableWidgetItem*> item1 = ui->tableWidget->selectedItems();
    if ( item1.isEmpty() ){
        QMessageBox::information(NULL,"注意","请选择您要查询的车次座位");
    }
    else{
        QTableWidgetItem *item = item1.first();
        int row = item->row();
        ticket::T = MainWindow::train[row];
        detail = new details();
        detail->show();
    }
}

void ticket::on_close_clicked()
{
    this->hide();
}

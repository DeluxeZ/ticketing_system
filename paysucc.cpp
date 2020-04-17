#include "paysucc.h"
#include "ui_paysucc.h"
#include "ticket.h"
#include "mainwindow.h"
#include <QDebug>


paysucc::paysucc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paysucc)
{
    QString departure = ticket::Departure;
    ui->setupUi(this);
    this->setWindowTitle("购票成功");
    ui->departure_lineEdit->setText(departure);
    ui->destination_lineEdit->setText(ticket::Destination);
    ui->departurelabel->setText(ticket::Leavetime[ticket::T].mid(0,5));
    ui->destinationlabel->setText(ticket::Arrivetime[ticket::T].mid(0,5));
    ui->date->setText(MainWindow::date);
    ui->train_number->setText(ticket::Train_number[ticket::T]);
    ui->departure_lineEdit->setEnabled(false);
    ui->departure_lineEdit->setStyleSheet("border:1px rgb(196,196,251) solid; color:black;border-radius:3px;background-color:rgb(220,220,220)");
    ui->destination_lineEdit->setEnabled(false);
    ui->destination_lineEdit->setStyleSheet("border:1px rgb(196,196,251) solid; color:black;border-radius:3px;background-color:rgb(220,220,220)");
    ui->date->setEnabled(false);
    ui->date->setStyleSheet("border:1px rgb(196,196,251) solid; color:black;border-radius:3px;background-color:rgb(220,220,220)");
    ui->exit->setStyleSheet("QPushButton{border:none;border-radius:3px;background-color:rgb(230,230,230)}"
                            "QPushButton:hover{background-color:rgb(240,240,240)}");
}

paysucc::~paysucc()
{
    delete ui;
}

void paysucc::on_exit_clicked()
{
    this->hide();
}

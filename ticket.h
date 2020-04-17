#ifndef TICKET_H
#define TICKET_H

#include <QWidget>
#include "paysucc.h"
#include "details.h"

namespace Ui {
class ticket;
}

class ticket : public QWidget
{
    Q_OBJECT

public:
    explicit ticket(QWidget *parent = nullptr);
    ~ticket();

    static int T;                     //储存用户选择的车辆
    static QString Departure;         //储存用户所选出发地的名字
    static QString Destination;       //储存用户所选目的地的名字
    static QList<QString> Leavetime;  //储存符合用户所选列车的出发时间
    static QList<QString> Arrivetime; //储存符合用户所选列车的到站时间
    static QList<QString> Train_number;//储存符合用户所选列车编号

private slots:
    void on_pushButton_clicked();
    void on_refresh_clicked();

    void on_details_clicked();

    void on_close_clicked();

private:
    Ui::ticket *ui;
    static QList<int> Train_id;
    static QList<int> Departure_id;
    static QList<int> Destination_id; 
    static QList<int> Price_hardseat;
    static QList<int> Price_hardbed;
    static QList<int> Price_softbed;
    static QList<int> Count_hardseat;
    static QList<int> Count_tophardbed;
    static QList<int> Count_midhardbed;
    static QList<int> Count_bothardbed;
    static QList<int> Count_softbed;
    paysucc* pay;
    details* detail;

};

#endif // TICKET_H

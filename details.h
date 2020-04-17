#ifndef DETAILS_H
#define DETAILS_H

#include <QWidget>

namespace Ui {
class details;
}

class details : public QWidget
{
    Q_OBJECT

public:
    explicit details(QWidget *parent = nullptr);
    ~details();

private slots:
    void on_close_clicked();

private:
    Ui::details *ui;
};

#endif // DETAILS_H

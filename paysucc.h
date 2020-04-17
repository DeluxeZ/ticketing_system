#ifndef PAYSUCC_H
#define PAYSUCC_H

#include <QDialog>

namespace Ui {
class paysucc;
}

class paysucc : public QDialog
{
    Q_OBJECT

public:
    explicit paysucc(QWidget *parent = nullptr);
    ~paysucc();

private slots:
    void on_exit_clicked();

private:
    Ui::paysucc *ui;
};

#endif // RESULT_H

#ifndef INTERESTRATE_H
#define INTERESTRATE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class interestRate;
}

class interestRate : public QDialog
{
    Q_OBJECT

public:
    explicit interestRate(QWidget *parent = 0);
    ~interestRate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::interestRate *ui;
};

#endif // INTERESTRATE_H

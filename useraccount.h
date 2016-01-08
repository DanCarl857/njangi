#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QDialog>
#include "login.h"

namespace Ui {
class userAccount;
}

class userAccount : public QDialog
{
    Q_OBJECT

public:
    explicit userAccount(QWidget *parent = 0);
    ~userAccount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::userAccount *ui;
};

#endif // USERACCOUNT_H


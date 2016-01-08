/****************************** Module Header ******************************\
* Module Name:  Transaction.h
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* MainInterface for Transaction
\***************************************************************************/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include "loan.h"
#include "other.h"
#include "save.h"
#include "withdraw.h"
#include "payback.h"

namespace Ui {
class Transaction;
}

class Transaction : public QDialog
{
    Q_OBJECT

public:
    explicit Transaction(QWidget *parent = 0);
    void setPrimaryKey(QString);
    QString getPrimaryKey() const;
    void loadLCD(QString);
    ~Transaction();

private slots:
    void on_saveButton_clicked();

    void on_witthdrawButton_clicked();

    void on_otherButton_clicked();

    void on_loanButton_clicked();

    void on_payBackButton_clicked();

private:
    Ui::Transaction *ui;
    QString key;
};

#endif // TRANSACTION_H

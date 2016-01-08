/****************************** Module Header ******************************\
* Module Name:  Withdraw.h
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Withdraw from account
\***************************************************************************/

#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QDialog>

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Withdraw;
}

class Withdraw : public QDialog
{
    Q_OBJECT

public:
    explicit Withdraw(QWidget *parent = 0);
    void setPrimaryKey(QString);
    ~Withdraw();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Withdraw *ui;
    QString key;
};

#endif // WITHDRAW_H

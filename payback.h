/****************************** Module Header ******************************\
* Module Name:  Payback.h
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Payback loan
\***************************************************************************/

#ifndef PAYBACK_H
#define PAYBACK_H

#include <QDialog>


#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class PayBack;
}

class PayBack : public QDialog
{
    Q_OBJECT

public:
    explicit PayBack(QWidget *parent = 0);
    void setPrimaryKey(QString);
    ~PayBack();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PayBack *ui;
    QString key;
    float loan;
};

#endif // PAYBACK_H

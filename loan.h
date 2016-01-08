/****************************** Module Header ******************************\
* Module Name:  Loan.h
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Provides the interface to take a loan.
\***************************************************************************/

#ifndef LOAN_H
#define LOAN_H

#include <QDialog>


#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTreeWidgetItem>

namespace Ui {
class Loan;
}

class Loan : public QDialog
{
    Q_OBJECT

public:
    explicit Loan(QWidget *parent = 0);
    void setPrimaryKey(QString);
    ~Loan();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Loan *ui;
    QString key;
};

#endif // LOAN_H

/****************************** Module Header ******************************\
* Module Name:  Transaction.cpp
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* MainInterface for Transaction
\***************************************************************************/

#include "transaction.h"
#include "ui_transaction.h"

Transaction::Transaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transaction)
{
    ui->setupUi(this);
    ui->savingsLabel->setText("<h2><font color=green>Savings</font></h2>");
    ui->loanLabel->setText("<h2><font color=red>Loan</font></h2>");
    setFixedSize(width(), height());

    ui->saveButton->setIconSize(QSize(90,100));
}
void Transaction::setPrimaryKey(QString k)
{
    key = k;
    loadLCD(k);
}
QString Transaction::getPrimaryKey() const
{
    return key;
}
void Transaction::loadLCD(QString k)
{
    QString command = "select first_name,last_name,savings,loan from accounts where id=" +
            QString("\'") + k + QString("\'");
    QSqlQuery query(command);
    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Error",query.lastError().text());
        return;
    }
    else
    {
        while(query.next())
        {
            ui->nameLable->setText(QString("<h1>") + query.value(0).toString() + QString(" ") + query.value(1).toString() + QString("</h1>"));
            ui->savingLcd->display(query.value(2).toString());
            ui->loanLcd->display(query.value(3).toString());
        }
    }
}

Transaction::~Transaction()
{
    delete ui;
}

void Transaction::on_saveButton_clicked()
{
    Save save;
    save.setPrimaryKey(getPrimaryKey());
    save.exec();

    loadLCD(getPrimaryKey());
    return ;
}

void Transaction::on_witthdrawButton_clicked()
{
    Withdraw withdraw;
    withdraw.setPrimaryKey(getPrimaryKey());
    withdraw.exec();

    loadLCD(getPrimaryKey());

    return ;
}

void Transaction::on_otherButton_clicked()
{
    Other other;
    other.setPrimaryKey(getPrimaryKey());
    other.exec();
    return ;
}

void Transaction::on_loanButton_clicked()
{
    Loan loan;
    loan.setPrimaryKey(getPrimaryKey());
    loan.exec();

    loadLCD(getPrimaryKey());
    return ;
}

void Transaction::on_payBackButton_clicked()
{
    PayBack payBack;
    payBack.setPrimaryKey(getPrimaryKey());
    payBack.exec();

    loadLCD(getPrimaryKey());
    return ;
}

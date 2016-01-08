/****************************** Module Header ******************************\
* Module Name:  Withdraw.cpp
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Withdraw from account
\***************************************************************************/

#include "withdraw.h"
#include "ui_withdraw.h"

Withdraw::Withdraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Withdraw)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0,1000000000,this));
    setFixedSize(width(), height());
}

Withdraw::~Withdraw()
{
    delete ui;
}
void Withdraw::setPrimaryKey(QString k)
{
    key = k;
}

void Withdraw::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","You must input all fields");
        return ;
    }
    QSqlQuery query("select savings from accounts where id=" + key);
    while(query.next())
    {
        if(query.value(0).toInt() < ui->lineEdit->text().toInt())
        {
            QMessageBox::warning(this,"Error","You cannot withdraw more than you have.\nConsider taking a loan");
            return ;
        }
    }

    QString historyCommand;
    QString accountCommand;

    historyCommand += "insert into records values (" +
            key + QString(",") + QString("0") + QString(",") + ui->lineEdit->text() + QString(",") +
            QString("0,0,\'") +
            ui->dateEdit->text() +QString("\'") + QString(");");
    accountCommand += "update accounts set savings=savings-"+ui->lineEdit->text()+
            QString(" where id=") + key;

    QSqlQuery query1(historyCommand);
    if(query1.lastError().isValid())
    {
        QMessageBox::warning(this,"Records Sql Error",query1.lastError().text());
        return ;
    }
    QSqlQuery query2(accountCommand);
    if(query2.lastError().isValid())
    {
        QMessageBox::warning(this,"Accounts Sql Error",query2.lastError().text());
        return ;
    }
    QMessageBox::information(this,"Success","Operation Successful");
    close();
}

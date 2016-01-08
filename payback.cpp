/****************************** Module Header ******************************\
* Module Name:  Payback.cpp
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Payback loan
\***************************************************************************/

#include "payback.h"
#include "ui_payback.h"

PayBack::PayBack(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PayBack)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0,1000000000,this));
    setFixedSize(width(), height());

}
void PayBack::setPrimaryKey(QString k)
{
    key = k;

    QString command = "select loan from accounts where id=" +
            QString("\'") + key + QString("\'");

    QSqlQuery query(command);
    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Error",query.lastError().text());
        return ;
    }
    else
    {
        while(query.next())
        {
            ui->loanLcd->display(query.value(0).toString());
            loan = query.value(0).toFloat();
        }
    }
}

PayBack::~PayBack()
{
    delete ui;
}

void PayBack::on_pushButton_clicked()
{

    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","You must complete all fields");
        return ;
    }

    if(ui->lineEdit->text().toFloat() > loan)
    {
        QMessageBox::warning(this,"Error","You cannot pay more than you owe");
        return ;
    }

    QString historyCommand;
    QString accountCommand;

    historyCommand += "insert into records values ("+
            key + QString(",0,0,0,") + ui->lineEdit->text() + QString(",\'") +
            ui->dateEdit->text() + QString("\'") + QString(");");
    accountCommand += "update accounts set loan=loan-" + ui->lineEdit->text() +
                QString(" where id=") + key;

    QSqlQuery query1(historyCommand);
    if(query1.lastError().isValid())
    {
        QMessageBox::warning(this,"PayBack recording Error",query1.lastError().text());
        return ;
    }
    QSqlQuery query2(accountCommand);
    if(query2.lastError().isValid())
    {
        QMessageBox::warning(this,"Account update Error",query2.lastError().text());
        return ;
    }

    if(ui->lineEdit->text().toFloat() == loan)
    {
        QSqlQuery query("update accounts set date_due=NULL where id=" + key);
        while(query.lastError().isValid())
        {
            QMessageBox::warning(this,"sql Error",query.lastError().text());
            return ;
        }
        QSqlQuery query1("updaet surtee set surtee1=NULL, surtee2=NULL, surtee3=NULL where id=" + key);
        if(query.lastError().isValid())
        {
            QMessageBox::warning(this,"Update surtee error",query.lastError().text());
            return ;
        }
        QSqlQuery restor("delete from surtee where id=" + key);
        if(restor.lastError().isValid())
        {
            QMessageBox::warning(this,"restor surtee error",restor.lastError().text());
            return ;
        }
    }
    QMessageBox::information(this,"Success","Operation Successful");
    close();
}

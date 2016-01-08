/****************************** Module Header ******************************\
* Module Name:  Save.cpp
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Save money
\***************************************************************************/

#include "save.h"
#include "ui_save.h"
#include <QDebug>

Save::Save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Save)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0,100000000,this));
    setFixedSize(width(), height());
}
void Save::setPrimaryKey(QString k)
{
    key = k;
}

Save::~Save()
{
    delete ui;
}

void Save::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","You must input all fields");
        return ;
    }

    QString historyCommand;
    QString accountCommand;

    historyCommand += "insert into records values ("+
            key + QString(",") + ui->lineEdit->text() + QString(",") +
            QString("0,0,0,\'") +
            ui->dateEdit->text() +QString("\'") + QString(");");

    accountCommand += "update accounts set savings=savings+"+ui->lineEdit->text()+
            QString(" where id=") + key;

    QSqlQuery query1(historyCommand);
    if(query1.lastError().isValid())
    {
        QMessageBox::warning(this,"Update records Sql Error",query1.lastError().text());
        return ;
    }
    QSqlQuery query2(accountCommand);
    if(query2.lastError().isValid())
    {
        QMessageBox::warning(this,"Update accounts Sql Error",query2.lastError().text());
        return ;
    }
    QMessageBox::information(this,"Success","Operation Successful");
    close();
}

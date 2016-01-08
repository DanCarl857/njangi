/****************************** Module Header ******************************\
* Module Name:  Loan.cpp
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Provides the interface to take a loan.
\***************************************************************************/

#include "loan.h"
#include "ui_loan.h"
#include <QDebug>

Loan::Loan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loan)
{
    ui->setupUi(this);
    //set integer validator
    ui->lineEdit->setValidator(new QIntValidator(0,100000000));
    setFixedSize(width(), height());
}
void Loan::setPrimaryKey(QString k)
{
    //primary key
    key = k;

    //get loan from accounts table and set it as lcd display number
    QString command = "select loan from accounts where id=" +
            QString("\'") + k + QString("\'");
    QSqlQuery query1(command);
    if(query1.lastError().isValid())
    {
        QMessageBox::warning(this,"Error",query1.lastError().text());
        return ;
    }
    else
    {
        while(query1.next())
        {
            ui->lcdNumber->display(query1.value(0).toString());
        }
    }

    //fill the QTreeWidget will all members of the system
    int j = 0;
    QSqlQuery query("select first_name,last_name,savings from accounts where id != " + key);

    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Loan Error",query.lastError().text());
        return ;
    }
    while(query.next())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        for(int i = 0; i < 3; i++)
            item->setText(i,query.value(i).toString());
        ui->treeWidget->insertTopLevelItem(j++,item);
    }
}

Loan::~Loan()
{
    delete ui;
}

//double click to select surtee
void Loan::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(ui->treeWidget_2->topLevelItemCount() == 3)
    {
        QMessageBox::warning(this,"Error","Max number of surtees reached");
        return ;
    }
    QTreeWidgetItem *row = new QTreeWidgetItem(ui->treeWidget_2);
    for(int i = 0; i < 2; i++)
        row->setText(i,item->text(i));

    for(int i = 0; i < ui->treeWidget_2->topLevelItemCount() - 1; i++)
    {
        QTreeWidgetItem *currentItem = ui->treeWidget_2->topLevelItem(i);
        if(!currentItem)
            break;

        if((row->text(0) == currentItem->text(0)) && (row->text(1) == currentItem->text(1)))
        {

            QMessageBox::warning(this,"Error","Already added surtee");
            break;
        }
    }
    ui->treeWidget_2->insertTopLevelItem(ui->treeWidget_2->topLevelItemCount(),row);
}

void Loan::on_pushButton_clicked()
{
    if(ui->dateEdit->text() >= ui->dateEdit_2->text())
    {
        QMessageBox::warning(this,"Error","Date and Date Due cannot be the same");
        return ;
    }
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","You must fill all fields");
        return ;
    }
    if(ui->lcdNumber->value() != 0.0)
    {
        QMessageBox::warning(this,"Error","You are on loan");
        return ;
    }

    if(ui->treeWidget_2->topLevelItemCount() != 3)
    {
        QMessageBox::warning(this,"Error","You must have 3 surtees");
        return ;
    }
    QSqlQuery records("insert into records values ("+key+ ",0,0,"+ui->lineEdit->text()+",0,\'"+
                         ui->dateEdit->text()+"\');");
    if(records.lastError().isValid())
    {
        QMessageBox::warning(this,"loan records error",records.lastError().text());
        return ;
    }
    QSqlQuery account("update accounts set loan=" + ui->lineEdit->text() + ",date_due=\'" +
                      ui->dateEdit_2->text() + "\' where id=" + key + ";");

    if(account.lastError().isValid())
    {
        QMessageBox::warning(this,"loan accounts error",account.lastError().text());
        return ;
    }
    QString s[3];
    for(int i = 0; i < 3; ++i)
    {
        QSqlQuery command("select id from accounts where first_name=\'" +
                          ui->treeWidget->topLevelItem(i)->text(0) + QString("\' and last_name=\'") +
                          ui->treeWidget->topLevelItem(i)->text(1) + QString("\'"));
        if(command.lastError().isValid())
        {
            QMessageBox::warning(this, "surtee error1", command.lastError().text());
            return;
        }
        while(command.next())
            s[i] = command.value(0).toString();
    }
    QSqlQuery ins("insert into surtee values(" + key + QString(",") + s[0] + QString(",") + s[1] + QString(",") + s[2]
            + QString(")"));

    if(ins.lastError().isValid())
    {
        QMessageBox::warning(this, "surtee error2", ins.lastError().text());
        return;
    }
    QMessageBox::information(this,"Success","operation successfull");
    close();
}

void Loan::on_pushButton_3_clicked()
{
    ui->treeWidget_2->clear();
}

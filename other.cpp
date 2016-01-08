
/****************************** Module Header ******************************\
* Module Name:  Other.cpp
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Provides the interface to micsillenous transactions
\***************************************************************************/

#include "other.h"
#include "ui_other.h"


Other::Other(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Other)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0,100000));
    ui->lineEdit_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    setFixedSize(width(), height());

    QSqlQuery query("select description from others;");
    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Sql Error",query.lastError().text());
        return ;
    }

    while(query.next())
    {
        QString str = query.value(0).toString();
        if(ui->comboBox->findText(str) == -1)
            ui->comboBox->addItem(str);
    }
}
void Other::setPrimaryKey(QString k)
{
    key = k;
}

Other::~Other()
{
    delete ui;
}

void Other::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
    }
    else
    {
        ui->lineEdit_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}
void Other::on_pushButton_clicked()
{

    if(ui->comboBox->currentText().isEmpty())
    {
        QMessageBox::warning(this,"Error","You must select an event");
        return ;
    }
    QSqlQuery query("insert into others values (" + key + ",\'" +
                    ui->comboBox->currentText()+ "\'," + ui->lineEdit->text() + ",\'" +
                    ui->dateEdit->text() + "\');");

    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Others Sql Error",query.lastError().text());
        return ;
    }
    QMessageBox::information(this,"Success","Operation Successful");
    close();
}
void Other::on_pushButton_3_clicked()
{
    if(ui->comboBox->findText(ui->lineEdit_2->text()) == -1)
        ui->comboBox->addItem(ui->lineEdit_2->text());
}

/****************************** Module Header ******************************\
* Module Name:  deleteUser.cpp
* Project:      Njangi System
* Copyright (c) Piar Systems
*
* MainInterface for deleteuser
\***************************************************************************/
#include "deleteuser.h"
#include "ui_deleteuser.h"

deleteUser::deleteUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteUser)
{
    ui->setupUi(this);
    setFixedHeight(130);
    setFixedWidth(398);
}

deleteUser::~deleteUser()
{
    delete ui;
}

//clicking ok on the delete user dialog
void deleteUser::on_pushButton_2_clicked()
{
    QString name = ui->lineEdit->text();

    //revoke all the privileges the user has first
    QSqlQuery revUser;
    QString revStr = "revoke all privileges, grant option from \'";
    revStr += name + QString("\'@'localhost'");

    revUser.prepare(revStr);
    revUser.exec();

    if(revUser.lastError().isValid())
    {
        QMessageBox::warning(this, "ErrorTest", revUser.lastError().text(), QMessageBox::Ok);
        return;
    }

    //delete the user by removing him/her from the database
    //Form the query for removing the user
    QString command = "DROP USER \'";
    command += name;
    command += "\'@'localhost'";

    QSqlQuery query;
    query.prepare(command);
    query.exec();

    if(query.lastError().isValid())
    {
        QMessageBox::warning(this, "Error", query.lastError().text(),QMessageBox::Ok);
        return;
    }

    //inform mysql server of the changes;
    QSqlQuery info;
    info.prepare("flush privileges");
    info.exec();

    if(info.lastError().isValid())
    {
        QMessageBox::warning(this, "Error", info.lastError().text(),QMessageBox::Ok);
        return;
    }
    //inform user of success of operation
    QMessageBox::information(this, "Success", "Operation successful", QMessageBox::Ok);
    this->close();
}

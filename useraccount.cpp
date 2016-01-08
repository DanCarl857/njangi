/* This module takes care of the creating users from the dashboard
 */
#include "useraccount.h"
#include "ui_useraccount.h"

userAccount::userAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userAccount)
{
    ui->setupUi(this);

    //set fixed size
    setFixedSize(width(), height());
}

userAccount::~userAccount()
{
    delete ui;
}

//clicking on the create button on the useraccount dialog
void userAccount::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!", "New username field empty");
        return;
    }
    if(ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!", "New password field empty");
        return;
    }

    //create user with new user credentials
    QSqlQuery query;
    QString command = "GRANT ALL ON njangiSystem.* TO \'";
    command += ui->lineEdit->text() + QString("\'");
    command += "@'localhost' IDENTIFIED BY \'";
    command += ui->lineEdit_2->text() + QString("\'");

    query.prepare(command);
    query.exec();

    if(query.lastError().isValid())
    {
        QMessageBox::warning(this, "User Status", "Invalid credentials");
        return;
    }
    else
    {
        QMessageBox::information(this, "Status", "User successfully created\n"
                                 "Login wth new user credentials to use the user.", QMessageBox::Ok);
        close();
    }

}

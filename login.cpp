/*
 * This is the login module
 * It takes care of logining in and creating the database modules
 */
#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->groupBox_2->setEnabled(false);

    //make login dialog unsizable
    setFixedHeight(399);
    setFixedWidth(386);
}

Login::~Login()
{
    delete ui;
}

//clicking on the no user account button
void Login::on_pushButton_3_clicked()
{
    //if the no user button is clicked it shows...
    //...the page for entering the new user account
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_3->setVisible(false);
}

//clicking on the back button on for new user
void Login::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_3->setVisible(true);
}

//clicking ok button on the dashboard
void Login::on_pushButton_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    if(index == 0)
    {
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this, "Error!","Username field empty");
            return;
        }
        if(ui->lineEdit_2->text().isEmpty())
        {
            QMessageBox::warning(this, "Error!","Password field empty");
            return;
        }
        if(connectToDb(ui->lineEdit->text(),ui->lineEdit_2->text()))
        {
            close();
            createAllTables();
            mainWindow.fillTreeWidget();
            mainWindow.show();
        }
        else
        {
            QMessageBox::warning(this, "Error", "Wrong username or password");
            return;
        }
    }
    if(index == 1)
    {
        if(ui->lineEdit_5->text().isEmpty())
        {
            QMessageBox::warning(this, "Error!","New Username field empty");
            return;
        }
        if(ui->lineEdit_6->text().isEmpty())
        {
            QMessageBox::warning(this, "Error!","New Password field empty");
            return;
        }

        //create user with new user credentials
        QSqlQuery query;
        QString command = "GRANT ALL ON njangiSystem.* TO \'";
        command += ui->lineEdit_5->text() + QString("\'");
        command += "@'localhost' IDENTIFIED BY \'";
        command += ui->lineEdit_6->text() + QString("\'");

        query.prepare(command);
        query.exec();

        if(query.lastError().isValid())
        {
            QMessageBox::warning(this, "User Status", query.lastError().text());
            return;
        }
        else
        {
            if(connectToDb(ui->lineEdit_5->text(),ui->lineEdit_6->text()))
            {
                close();
                createAllTables();
                mainWindow.fillTreeWidget();
                mainWindow.show();
            }
            else
            {
                QMessageBox::warning(this, "Error", "User not successfully created");
                return;
            }
        }
    }
}

//clicking on validate on the dashboard
void Login::on_pushButton_5_clicked()
{
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!","Root username field empty");
        return;
    }
    if(ui->lineEdit_4->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!","Root password field empty");
        return;
    }
    if(connectToDb(ui->lineEdit_3->text(), ui->lineEdit_4->text()))
    {
        ui->groupBox_2->setEnabled(true);
        QMessageBox::information(this, "Status","Login successful");
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Invalid Username or Password");
        return;
    }
}

//connecting to the database using given credentials
bool Login::connectToDb(QString userName, QString password)
{

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName(userName);
    db.setHostName("localhost");
    db.setPassword(password);

    if(!db.open())
    {
       //If database connection failed...
       //...display error message and exit
       QMessageBox::warning(this, "Connection Status", "Connection failed");
       return false;
    }

    return true;
}

//create all the tables for the database
void Login::createAllTables()
{
        QSqlQuery createDb;
        createDb.prepare("CREATE DATABASE IF NOT EXISTS njangiSystem ");
        createDb.exec();

        if(createDb.lastError().isValid())
        {
            QMessageBox::warning(this, "Database Error", createDb.lastError().text());
            return;
        }

        QSqlQuery useDb;
        useDb.prepare("USE njangiSystem");
        useDb.exec();

        if(useDb.lastError().isValid())
        {
            QMessageBox::warning(this, "Use database error", useDb.lastError().text());
            return;
        }

        //create the table for accounts
        QSqlQuery query;
        query.prepare("CREATE TABLE IF NOT EXISTS accounts("
                      "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                      "first_name VARCHAR(20) NOT NULL,"
                      "middle_name VARCHAR(20) NOT NULL,"
                      "last_name VARCHAR(20) NOT NULL,"
                      "position VARCHAR(30) DEFAULT 'floorMember',"
                      "address VARCHAR(30) NULL,"
                      "phone_number INT NULL,"
                      "savings FLOAT DEFAULT 0.0,"
                      "interest FLOAT DEFAULT 0.0,"
                      "loan FLOAT DEFAULT 0.0,"
                      "date_due DATE);");
        query.exec();
        if(query.lastError().isValid())
        {
            QMessageBox::warning(this, "error", query.lastError().text());
        }


        //create the table for records(individual)
        QSqlQuery query1;
        query1.prepare("CREATE TABLE IF NOT EXISTS records("
                       "id INT UNSIGNED,"
                       "saved FLOAT DEFAULT 0.0,"
                       "withdrawn FLOAT DEFAULT 0.0,"
                       "loan_debit FLOAT DEFAULT 0.0,"
                       "loan_credit FLOAT DEFAULT 0.0,"
                       "date DATE NOT NULL);");
        query1.exec();
        if(query1.lastError().isValid())
        {
            QMessageBox::warning(this, "error", query1.lastError().text());
        }

        //create the table for surtees
        QSqlQuery query2;
        query2.prepare("CREATE TABLE IF NOT EXISTS surtee("
                       "id INT UNSIGNED,"
                       "surtee1 INT NOT NULL,"
                       "surtee2 INT NOT NULL,"
                       "surtee3 INT NOT NULL);");
        query2.exec();

        //create the table for others
        QSqlQuery query3;
        query3.prepare("CREATE TABLE IF NOT EXISTS others("
                       "id INT UNSIGNED,"
                       "description VARCHAR(15),"
                       "amount FLOAT DEFAULT 0.0,"
                       "date DATE);");
        query3.exec();

}



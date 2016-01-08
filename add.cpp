#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
}

Add::~Add()
{
    delete ui;
}

void Add::on_createButton_clicked()
{
    QMessageBox::StandardButton reply;

    if(ui->firstNameLineEdit->text().isEmpty() 			||
            ui->middleNameLineEdit->text().isEmpty() 	||
            ui->lastNameLineEdit->text().isEmpty() 		||
            ui->positionLineEdit->text().isEmpty() 		||
            ui->addressLineEdit->text().isEmpty() 		||
            ui->phoneNumberLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","You must input all fields");
        return ;
    }
    QString info = QString("Is the information correct?\n\n")
         + QString("First Name: ") + ui->firstNameLineEdit->text() + QString("\n")
         + QString("Middle Name: ") + ui->middleNameLineEdit->text() + QString("\n")
         + QString("Last Name: ") + ui->lastNameLineEdit->text() + QString("\n")
         + QString("Position:  ") + ui->positionLineEdit->text() + QString("\n")
         + QString("Address :  ") + ui->addressLineEdit->text() + QString("\n")
         + QString("Phone # :  ") + ui->phoneNumberLineEdit->text() + QString("\n\n")
         + QString("Yes to proceed | No to edit");

    reply = QMessageBox::question(this,"Verification",info,QMessageBox::Yes|QMessageBox::No);

    if(reply == QMessageBox::No)
    {
        return ;
    }
    if(reply == QMessageBox::Yes)
    {
        //check if the member already exists
        QSqlQuery check("select id from accounts where first_name =\'" + ui->firstNameLineEdit->text() + "\' and " +
                        "middle_name = \'" + ui->middleNameLineEdit->text() + "\' and " +
                        "last_name = \'" + ui->lastNameLineEdit->text() + "\'");
        if(check.lastError().isValid())
        {
            QMessageBox::warning(this,"Checkin Error",check.lastError().text());
            return ;
        }
        if(check.size() == 0)   //member does not exists
        {
            QSqlQuery add("insert into accounts values (NULL,\'"
                          + ui->firstNameLineEdit->text() + "\','"
                          + ui->middleNameLineEdit->text() + "\','"
                          + ui->lastNameLineEdit->text() + "\','"
                          + ui->positionLineEdit->text() + "\','"
                          + ui->addressLineEdit->text() + "\','"
                          + ui->phoneNumberLineEdit->text() + "\',0,0,0,NULL);");
            if(add.lastError().isValid())
            {
                QMessageBox::warning(this,"Add error",add.lastError().text());
                return ;
            }
            else
            {
                QMessageBox::information(this,"Success","Operation successfull");
                close();
            }
        }
        else
        {
            QMessageBox::warning(this,"Duplcate","Member already exists");
            return ;
        }
    }
}

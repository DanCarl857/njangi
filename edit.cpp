
#include "edit.h"
#include "ui_edit.h"

EDIT::EDIT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EDIT)
{
    ui->setupUi(this);
    QRegExp regExp("[0-9][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]"); // to input only int the telephone lineEdit;

    ui->lineEdit_6->setValidator(new QRegExpValidator(regExp, this));


}
void EDIT::setPrimaryKey(QString k)
{
    key = k;
    QSqlQuery selct;
    selct.prepare("SELECT * FROM accounts WHERE id= '"+key+"'");

   if( selct.exec())
   {
       while(selct.next())
       {
          ui->lineEdit->setText(selct.value(1).toString());
          ui->lineEdit_2->setText(selct.value(2).toString());
          ui->lineEdit_3->setText(selct.value(3).toString());
          ui->lineEdit_4->setText(selct.value(4).toString());
          ui->lineEdit_5->setText(selct.value(5).toString());
          ui->lineEdit_6->setText(selct.value(6).toString());
      }

   }

}


EDIT::~EDIT()
{
    delete ui;
}






void EDIT::on_pushButton_2_clicked() // when ok button clicked it update database

{
    QMessageBox::StandardButton sure; //help you to be sure if you want to update or not
    sure= QMessageBox::warning(this,"Alert","You are about to update a status",QMessageBox::Yes | QMessageBox::No);
    if(sure==QMessageBox::Yes)
    {

             if (!(ui->lineEdit->text().isEmpty()) && !(ui->lineEdit_3->text().isEmpty()))
        {


              QSqlQuery up(QString("UPDATE  accounts SET accounts.first_name =\'%1\',accounts.middle_name =\'%2\',accounts.last_name =\'%3\',accounts.position =\'%4\',accounts.address =\'%5\',accounts.phone_number =\'%6\' WHERE accounts.id=\'%7\'")
                .arg(ui->lineEdit->text()) .arg(ui->lineEdit_2->text()) .arg(ui->lineEdit_3->text()) .arg(ui->lineEdit_4->text()) .arg(ui->lineEdit_5->text()) .arg(ui->lineEdit_6->text()) .arg(key));
                up.exec();
                QMessageBox::information(this, "Success", "Successfully edited");
                 this->close();
        }
             else
        {
        QMessageBox::warning(this,"Warning","<b>First Name</b> and <b>Last Name</b> fields must be <b>Entered</b> ");

        }
     }
}

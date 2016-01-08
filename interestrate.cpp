#include "interestrate.h"
#include "ui_interestrate.h"

interestRate::interestRate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interestRate)
{
    ui->setupUi(this);
    ui->lineEdit->setText("45");
    ui->lineEdit_2->setText("23");
    setFixedHeight(237);
    setFixedWidth(404);
}

interestRate::~interestRate()
{
    delete ui;
}

//clicking change on the interest rate form
void interestRate::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
       QMessageBox::warning(this, "Error", "All fields must be filled");
       return;
    }
}

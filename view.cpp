#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

}

View::~View()
{
    delete ui;
}
void View::setPrimaryKey(QString k)
{
    key = k;

    QSqlQuery query("select first_name,last_name,savings,loan,interest from accounts where id=" + key);
    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Errror",query.lastError().text());
        return ;
    }

    while(query.next())
    {
        ui->nameLabel->setText("<h1>"+query.value(0).toString()+" " + query.value(1).toString()+ "</h1>");
        ui->savingsLcdNumber->display(query.value(2).toString());
        ui->interestLcdNumber->display(query.value(3).toString());
        ui->loanLcdNumber->display(query.value(4).toString());
    }

    int i =0;
    QSqlQuery query1("select id from surtee where surtee1="+key+ " or surtee2="+key+" or surtee3=" +key);
    if(query1.lastError().isValid())
    {
        QMessageBox::warning(this,"Error",query1.lastError().text());
        return ;
    }
    while(query1.next())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->surteeTreeWidget);

        QSqlQuery query2("select first_name,last_name from accounts where id=" + query1.value(0).toString());
        if(query2.lastError().isValid())
        {
            QMessageBox::warning(this,"Error",query.lastError().text());
            return ;
        }
        while(query2.next())
        {
            item->setText(0,query2.value(0).toString());
            item->setText(1,query2.value(1).toString());
        }
        ui->surteeTreeWidget->insertTopLevelItem(i++,item);
    }
    int j = 0;
   QSqlQuery query3("select saved,withdrawn,loan_debit,loan_credit,date from records where id=" + key);
   if(query3.lastError().isValid())
   {
       QMessageBox::warning(this,"Error",query3.lastError().text());
       return ;
   }
   while(query3.next())
   {
       QTreeWidgetItem *item = new QTreeWidgetItem(ui->transactionsTreeWidget);
       for(int i = 0; i < 5; i++)
           item->setText(i,query3.value(i).toString());
       ui->transactionsTreeWidget->insertTopLevelItem(j++,item);
   }
}
//print button on view dialog
void View::on_pushButton_2_clicked()
{

}

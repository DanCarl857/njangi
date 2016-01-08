/*
 * This module controls the functionality of
 * the main window
 */

#include "njangisystem.h"
#include "ui_njangisystem.h"
#include "useraccount.h"
#include "deleteuser.h"
#include "transaction.h"
#include "interestrate.h"

njangiSystem::njangiSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::njangiSystem)
{
    ui->setupUi(this);

    //make unsizable
    setMaximumHeight(height());
    setMaximumWidth(width());
    setMinimumHeight(600);
    setMinimumWidth(450);
    //make personal buttons disabled
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
}

njangiSystem::~njangiSystem()
{
    delete ui;
}

//clicking exit under file in toolbar
void njangiSystem::on_actionExit_triggered()
{
    this->close();
}

//clicking about under help in toolbar
void njangiSystem::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About Njangi App",
                             "Version 1.0.0.0\n\n Njangi system is an app which manages the finances"
                                " of a njangi.\n\n (c) 2015, Unity Systems Cmr",QMessageBox::Ok);
}

//clicking on the delete button on the dashboard
void njangiSystem::on_pushButton_4_clicked()
{
    QString key = ui->treeWidget->currentItem()->text(0);

    QMessageBox::StandardButton verify;
    verify = QMessageBox::question(this, "Member delete", "You are about to delete a member\n\nContinue?",
                          QMessageBox::Yes | QMessageBox::No);
    //if user takes yes
    if(verify == QMessageBox::Yes)
    {
        QSqlQuery delCommAcc("delete from accounts where id=" + key + QString(";"));
        if(delCommAcc.lastError().isValid())
        {
            QMessageBox::warning(this, "Warining", delCommAcc.lastError().text());
            return;
        }
        QSqlQuery delCommOth("delete from others where id=" + key + QString(";"));
        if(delCommOth.lastError().isValid())
        {
            QMessageBox::warning(this, "Error", delCommOth.lastError().text());
            return;
        }
        QSqlQuery delComRec("delete from records where id=" + key + QString(";"));
        if(delComRec.lastError().isValid())
        {
            QMessageBox::warning(this, "Error", delComRec.lastError().text());
            return;
        }
        QSqlQuery delComSur("delete from surtee where id=" + key + QString(";"));
        if(delComSur.lastError().isValid())
        {
            QMessageBox::warning(this, "Error", delComRec.lastError().text());
            return;
        }
        ui->treeWidget->clear();
        ui->treeWidget_2->clear();
        fillTreeWidget();
    }
    else
    {

    }
}

//clicking a QTreeWidgetItem on the treeWidget
void njangiSystem::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //enable all the disabled buttons
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

//function fills the tree widget with the data from...
//...the mysql database
void njangiSystem::fillTreeWidget()
{
    QSqlQuery query("select current_date()");
    if(query.lastError().isValid())
    {
        QMessageBox::warning(this,"Error",query.lastError().text());
        return ;
    }
    else
    {
        while(query.next())
        {
            ui->dateLabel->setText("<h1>" + query.value(0).toString() + "</h1>");
        }
    }
    //display results of query in tree widget
    QSqlQuery showTable;
    showTable.prepare("select * from accounts");
    showTable.exec();

    if(showTable.lastError().isValid())
    {
        QMessageBox::warning(this, "Query failed", showTable.lastError().text(), QMessageBox::Ok);
    }

    int i = 0;
    while(showTable.next())
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
        for(int j = 0; j < 11; ++j)
        {
            itm->setText(j, showTable.value(j).toString());
        }
        ui->treeWidget->insertTopLevelItem(i, itm);
        ++i;
    }

    //display results on the summary page
    QSqlQuery summary("select id, first_name, last_name, savings, loan, interest from accounts");

    if(summary.lastError().isValid())
    {
        QMessageBox::warning(this, "Error", summary.lastError().text());
        return;
    }
    int p = 0;
    while(summary.next())
    {
        QSqlQuery summary1("select sum(amount) from others where id=" + summary.value(0).toString());

        if(summary1.lastError().isValid())
        {
            QMessageBox::warning(this,"Error", summary1.lastError().text());
            return;
        }
        QString amount;
        while(summary1.next())
        {
            amount = summary1.value(0).toString();
        }

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_2);
        for(int j = 0; j < 6; ++j)
        {
            item->setText(j, summary.value(j).toString());
        }
        item->setText(6, amount);
        ui->treeWidget_2->insertTopLevelItem(p++, item);
    }

    QSqlQuery totalSavings("select sum(savings) from accounts");

    if(totalSavings.lastError().isValid())
    {
        QMessageBox::warning(this,"Error", totalSavings.lastError().text());
        return;
    }
    while(totalSavings.next())
    {
        ui->lcdNumber->display(totalSavings.value(0).toString());
    }

    QSqlQuery totalLoan("select sum(loan) from accounts");

    if(totalLoan.lastError().isValid())
    {
        QMessageBox::warning(this,"Error", totalLoan.lastError().text());
        return;
    }
    while(totalLoan.next())
    {
        ui->lcdNumber_2->display(totalLoan.value(0).toString());
    }
}

//what happens when user types in the search bar
void njangiSystem::on_lineEdit_textChanged(const QString &arg1)
{

    //clear list first
    ui->treeWidget->clear();

    QSqlQuery query1;
    QString str = "select * from accounts where first_name like ";
    str += "\"%";
    str += arg1 + QString("%\"");

    query1.prepare(str);
    query1.exec();

    if(query1.lastError().isValid())
    {
        QMessageBox::warning(this, "Search Error", query1.lastError().text(), QMessageBox::Ok);
        return;
    }
    int numSize = query1.size();

    //if nothing is found reprint the original list
    if(numSize == 0)
    {
        fillTreeWidget();
    }
    else
    {
        int q = 0;
        while(query1.next())
        {
            QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
            for(int j = 0; j < 11; ++j)
            {
                itm->setText(j, query1.value(j).toString());
            }
            ui->treeWidget->insertTopLevelItem(q, itm);
            ++q;
        }
    }
}

//clicking on the create user button on the settings dashboard
void njangiSystem::on_pushButton_7_clicked()
{
   userAccount *account = new userAccount;
   account->setModal(true);
   account->exec();
}

//clicking on the delete user button on the settings dashboard
void njangiSystem::on_pushButton_8_clicked()
{
    QMessageBox::StandardButton verify;
    verify = QMessageBox::question(this, "Warning!", "You are about to delete a user.\nContinue?", QMessageBox::Yes |
                                   QMessageBox::No);

    //if user selects yes
    if(verify == QMessageBox::Yes)
    {
        deleteUser *user = new deleteUser;
        user->exec();
    }
    else
    {
        return;
    }
}

//clicking on the change interest rates on the settings form
void njangiSystem::on_pushButton_10_clicked()
{
    interestRate *rate = new interestRate;
    rate->exec();
}

//clicking on the transaction button on the dashboard
void njangiSystem::on_pushButton_5_clicked()
{
   Transaction *transaction  = new Transaction;
   QTreeWidgetItem *item = ui->treeWidget->currentItem();
   QString id = item->text(0);
   transaction->setPrimaryKey(id);
   transaction->exec();
   ui->treeWidget->clear();
   ui->treeWidget_2->clear();
   fillTreeWidget();
}

//clicking on the view button
void njangiSystem::on_pushButton_3_clicked()
{
    view = new View;
    view->setPrimaryKey(ui->treeWidget->currentItem()->text(0));
    view->show();
}

//clicking on the sign in button on the settings page
void njangiSystem::on_pushButton_12_clicked()
{
    if(ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "user name field empty");
        return;
    }
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "password field empty");
        return;
    }

    Login *log = new Login;

    //connect with provided credentials and check if root
    if(log->connectToDb(ui->lineEdit_2->text(), ui->lineEdit_3->text()))
    {
        //verify if the user is a root user
        QString testUser("Carlson");
        QString testPassword("man123");

        QSqlQuery query;
        QString command = "GRANT ALL ON njangiSystem.* TO \'";
        command += testUser + QString("\'");
        command += "@'localhost' IDENTIFIED BY \'";
        command += testPassword + QString("\'");

        query.prepare(command);
        query.exec();

        if(query.lastError().isValid())
        {
            QMessageBox::warning(this, "Warining", "Root username and password required");
            return;
        }
        else
        {
            //enable buttons if user is root
            ui->pushButton_7->setEnabled(true);
            ui->pushButton_8->setEnabled(true);
            ui->pushButton_10->setEnabled(true);

            QSqlQuery query1("DROP USER \'" + testUser + "\'@'localhost'");

            if(query1.lastError().isValid())
            {
                QMessageBox::warning(this, "Error", "Drop user error");
                return;
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Invalid credentials", "Invalid username or password",QMessageBox::Cancel);
        return;
    }
}

//clicking on the add member button
void njangiSystem::on_pushButton_clicked()
{
    Add *memb = new Add;
    memb->exec();
    ui->treeWidget->clear();
    ui->treeWidget_2->clear();
    fillTreeWidget();
}


//clicking on the edit button
void njangiSystem::on_pushButton_2_clicked()
{
    EDIT *edit = new EDIT;
    edit->setPrimaryKey(ui->treeWidget->currentItem()->text(0));
    edit->exec();
    ui->treeWidget->clear();
    ui->treeWidget_2->clear();
    fillTreeWidget();

}
//print button on summary tab
void njangiSystem::on_pushButton_9_clicked()
{

}

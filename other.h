/****************************** Module Header ******************************\
* Module Name:  Other.h
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Provides the interface to micsillenous transactions
\***************************************************************************/

#ifndef OTHER_H
#define OTHER_H

#include <QDialog>


#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Other;
}

class Other : public QDialog
{
    Q_OBJECT

public:
    explicit Other(QWidget *parent = 0);
    void setPrimaryKey(QString);
    ~Other();

private slots:
    void on_checkBox_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Other *ui;
    QString key;
};

#endif // OTHER_H

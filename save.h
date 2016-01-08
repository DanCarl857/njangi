/****************************** Module Header ******************************\
* Module Name:  Save.h
* Project:      Njangi System
* Copyright (c) Unity Systems
*
* Save money
\***************************************************************************/
#ifndef SAVE_H
#define SAVE_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Save;
}

class Save : public QDialog
{
    Q_OBJECT

public:
    explicit Save(QWidget *parent = 0);
    void setPrimaryKey(QString);
    ~Save();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Save *ui;
    QString key;
};

#endif // SAVE_H

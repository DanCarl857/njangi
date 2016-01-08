#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QMessageBox>
#include<QString>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>


namespace Ui {
class EDIT;
}

class EDIT : public QDialog
{
    Q_OBJECT



public:
    explicit EDIT(QWidget *parent = 0);
    void setPrimaryKey(QString);

    ~EDIT();

private slots:

    void on_pushButton_2_clicked();






private:
    Ui::EDIT *ui;
    QString key;
};

#endif // EDIT_H

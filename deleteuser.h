#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>

namespace Ui {
class deleteUser;
}

class deleteUser : public QDialog
{
    Q_OBJECT

public:
    explicit deleteUser(QWidget *parent = 0);
    ~deleteUser();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::deleteUser *ui;
};

#endif // DELETEUSER_H

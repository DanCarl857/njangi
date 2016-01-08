#ifndef NJANGISYSTEM_H
#define NJANGISYSTEM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QTreeWidgetItem>
#include "view.h"
#include "add.h"
#include "edit.h"


namespace Ui {
class njangiSystem;
}

class njangiSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit njangiSystem(QWidget *parent = 0);
    ~njangiSystem();
    void fillTreeWidget();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_pushButton_4_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_12_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::njangiSystem *ui;
    View *view;

};

#endif // NJANGISYSTEM_H

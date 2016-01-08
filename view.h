#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class View;
}

class View : public QDialog
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    void setPrimaryKey(QString );
    ~View();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::View *ui;
    QString key;
};

#endif // VIEW_H

#ifndef DIALOG_H
#define DIALOG_H
#include <QSqlRecord>
#include <QDialog>
#include "database.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void showDialog(const QSqlRecord &);
private:
    Ui::Dialog *ui;
    QVector <QStringList> speciallytiz;
    QSqlRecord rec;
private slots:
    void onFacultChanged(int);
signals:
    void recordCompleted(QSqlRecord);
};


#endif // DIALOG_H

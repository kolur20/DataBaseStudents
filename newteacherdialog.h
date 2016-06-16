#ifndef NEWTEACHERDIALOG_H
#define NEWTEACHERDIALOG_H
#include <QDialog>
#include <QSqlRecord>
#include "database.h"

namespace Ui {
class newTeacherDialog;
}

class newTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newTeacherDialog(QWidget *parent = 0);
    ~newTeacherDialog();

    void showDialog(const QSqlRecord &);
private:
    Ui::newTeacherDialog *ui;
    QVector <QStringList> speciallytiz, post;
    QSqlRecord rec;

signals:
    void recordCompleted(QSqlRecord);
};

#endif // NEWTEACHERDIALOG_H

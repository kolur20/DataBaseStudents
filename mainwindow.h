#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRecord>
#include <QMessageBox>
#include "database.h"
#include "dialog.h"
#include "newteacherdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newRecordButton_clicked();
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;

    DataBase *database;

    QSqlTableModel *StudentsTableModel,
                   *TeachersTableModel;

    QStringList StudentsTableHeaders,
                TeachersTableHeaders;

    QMetaObject::Connection newRecordConnection,
                            delRecordConnection;

    Dialog *newStudent;
    newTeacherDialog *newTeacher;
private:
    void loadViewModel(const QString &table, QTableView *view, QSqlTableModel *model, QStringList &headers);
};

#endif // MAINWINDOW_H

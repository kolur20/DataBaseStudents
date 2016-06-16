#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QtSql/QSqlQuery>
#include <QFile>
#include <QDebug>

#define DATABASE_NAME "STUDENTS.sqlite"

#define STUDENTS_TABLE "STUDENTS" //таблица студентов
#define TEACHERS_TABLE "TEACHERS" //таблица преподавателей

#define FIELD_FIO "FIO" //фио
#define FIELD_FACULTY "FACULTY" //факультет
#define FIELD_SPECIALITI "SPECIALITI" //специальность
#define FIELD_GROUP "_GROUP" //группа
#define FIELD_RECORD_BOOK "RECORD_BOOK" //зачетка
#define FIELD_YEAR_OF_BIRTH "YEAR_OF_BIRTH" //год рождения
#define FIELD_PHONE "PHONE" //телефон

#define FIELD_POST "POST" //должность

class DataBase : public QObject
{
        Q_OBJECT
public:
    DataBase(QObject *parent = 0) : QObject(parent)
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(DATABASE_NAME);
    }

    bool connectToDataBase();

private:
    QSqlDatabase database;
    QSqlQuery *query;

    bool openDataBase();
    bool createDataBase();

    bool createStudentsTable();
    bool createTeachersTable();

public slots:

    void closeDataBase();
    void removeDataBase();

};



#endif // DATABASE_H

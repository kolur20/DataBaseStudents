#include "database.h"


bool DataBase::connectToDataBase() {

    if (QFile::exists(DATABASE_NAME))
        return openDataBase();
    else
        return createDataBase();
}


bool DataBase::openDataBase() {

    if (!database.open()) {
        qDebug() << database.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::createDataBase() {

    if (openDataBase())
        return createStudentsTable()&&
               createTeachersTable();
    return false;
}


void DataBase::closeDataBase() {
    database.close();
}



void DataBase::removeDataBase() {
    closeDataBase();
    QFile db_file(DATABASE_NAME);
    if (!db_file.remove())
        qDebug() << "База данных не удалена.";
    else
        qDebug() << "База данных удалена.";
}



bool DataBase::createStudentsTable() {
    QSqlQuery query;

    if (!query.exec("CREATE TABLE "   STUDENTS_TABLE " ("
                    "ID               INTEGER PRIMARY KEY AUTOINCREMENT, "
                    FIELD_FIO"    TEXT,"
                    FIELD_FACULTY"      TEXT,"
                    FIELD_SPECIALITI"   TEXT,"
                    FIELD_GROUP"        TEXT,"
                    FIELD_RECORD_BOOK"         TEXT,"
                    FIELD_YEAR_OF_BIRTH"     DATE,"
                    FIELD_PHONE"        TEXT"
                    ")"))
    {
        qDebug() << "Ошибка создания таблицы"
                 << STUDENTS_TABLE
                 << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::createTeachersTable()
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE " TEACHERS_TABLE " ("
                    "ID               INTEGER PRIMARY KEY AUTOINCREMENT, "
                    FIELD_FIO"    TEXT,"
                    FIELD_SPECIALITI"   TEXT,"
                    FIELD_POST "    TEXT,"
                    FIELD_PHONE"        TEXT"
                    ")"))
    {
        qDebug() << "Ошибка создания таблицы"
                 << TEACHERS_TABLE
                 << query.lastError().text();
        return false;
    }
    return true;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


enum TABLE
{
    StudentsTableTab,
    TeachersTableTab
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    newStudent(new Dialog(parent)),
    database(new DataBase(parent)),
    newTeacher(new newTeacherDialog(parent))
{
    ui->setupUi(this);

    StudentsTableHeaders << "ID"
                         << "ФИО"
                         << "Факультет"
                         << "Специальность"
                         << "Группа"
                         << "Зачетка"
                         << "Дата рождения"
                         << "Телефон";

    TeachersTableHeaders << "ID"
                         << "ФИО"
                         << "Кафедра"
                         << "Должность"
                         << "Телефон";

    connect(this->ui->ExitButton, SIGNAL(clicked(bool)),this,SLOT(close()));
    if (this->database->connectToDataBase())
    {
        StudentsTableModel = new QSqlTableModel(parent);
        TeachersTableModel = new QSqlTableModel(parent);

        loadViewModel(STUDENTS_TABLE,this->ui->StudentsTableView, StudentsTableModel, StudentsTableHeaders);
        loadViewModel(TEACHERS_TABLE,this->ui->TeachersTableView, TeachersTableModel, TeachersTableHeaders);

        connect(this->ui->tabWidget,QTabWidget::currentChanged, [=](int index)
        {
            disconnect(this->newRecordConnection);
            switch (index) {
            case TABLE::StudentsTableTab:
            {
               newRecordConnection = connect(ui->newRecordButton, QPushButton::clicked, [=]()
                {
                    emit this->newStudent->showDialog(StudentsTableModel->record());
                    newRecordConnection = connect(this->newStudent, Dialog::recordCompleted, [&](QSqlRecord rec)
                    {
                        StudentsTableModel->insertRecord(-1,rec);
                        StudentsTableModel->select();
                        disconnect(newRecordConnection);
                    });
                });

               delRecordConnection = connect(ui->delRecordButton,QPushButton::clicked, [=]()
               {
                  QModelIndex current = ui->StudentsTableView->currentIndex();
                  this->StudentsTableModel->removeRow(current.row());
                  this->StudentsTableModel->select();
               });
            }
                break;

            case TABLE::TeachersTableTab:
            {
                newRecordConnection = connect(ui->newRecordButton, QPushButton::clicked, [=]()
                 {
                     emit this->newTeacher->showDialog(TeachersTableModel->record());
                     newRecordConnection = connect(this->newTeacher, newTeacherDialog::recordCompleted, [&](QSqlRecord rec)
                     {
                         TeachersTableModel->insertRecord(-1,rec);
                         TeachersTableModel->select();
                         disconnect(newRecordConnection);
                     });
                 });

                delRecordConnection = connect(ui->delRecordButton,QPushButton::clicked, [=]()
                {
                   QModelIndex current = ui->TeachersTableView->currentIndex();
                   this->TeachersTableModel->removeRow(current.row());
                   this->TeachersTableModel->select();
                });
            }
                break;

            }
            });
        ui->tabWidget->setCurrentIndex(0);
        emit ui->tabWidget->currentChanged(0);
    }
    else
        qDebug() << "ошибка подключения к базе данных";

}


void MainWindow::loadViewModel(const QString &table, QTableView *view, QSqlTableModel *model, QStringList &headers) {

    model->setTable(table);
    model->select();
    view->setModel(model);

    for(int i = 0; i < model->columnCount(); i++)
        model->setHeaderData(i, Qt::Horizontal,headers[i]);

    for (int c = 0; c < view->horizontalHeader()->count(); ++c)
        view->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);


    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setColumnHidden(0, true);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->horizontalHeader()->setStretchLastSection(true);

}


MainWindow::~MainWindow()
{
    if (this->ui->clearDataBaseCheckBox->checkState())
    {

        this->database->removeDataBase();
        return;
    }
    delete ui;
}

void MainWindow::on_newRecordButton_clicked()
{
    switch(this->ui->tabWidget->currentIndex())
    {
    case TABLE::StudentsTableTab:
        this->newStudent->show();
        break;

    case TABLE::TeachersTableTab:
        this->newTeacher->show();
        break;
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString search = ui->searchLineEdit->text();
    if (search.isEmpty())
    {
       QMessageBox msq (QMessageBox::Information,
                        "Ошибка!",
                        "Поиск не может быть пустым",
                        QMessageBox::Ok);
       msq.exec();
       return;
    }
    int current_tab = this->ui->tabWidget->currentIndex();
    switch (current_tab) {

    case TABLE::StudentsTableTab:
    {
        int row_count = StudentsTableModel->rowCount();
        QModelIndex founded_index;
        for( int i = 0; i < row_count; i++ )
        {
            QModelIndex name = StudentsTableModel->index(i, 1);
            QModelIndex phone = StudentsTableModel->index(i,7);
            QModelIndex book = StudentsTableModel->index(i,5);
            if(StudentsTableModel->data(name).toString() == search ||
               StudentsTableModel->data(phone).toString() == search||
               StudentsTableModel->data(book).toString() == search)
            {
                ui->StudentsTableView->setFocus();
                ui->StudentsTableView->setCurrentIndex(name);
                ui->StudentsTableView->setCurrentIndex(phone);
                ui->StudentsTableView->setCurrentIndex(book);
                return;
            }
        }
        QMessageBox msg(QMessageBox::Information,
                        "Поиск",
                        QString("Поиск %1 не дал результатов").arg(search),
                        QMessageBox::Ok);
        msg.exec();
    }

        break;

//    case TABLE::TeachersTableTab:
//    {

//    }
//        break;
    default:
        break;
    }
}

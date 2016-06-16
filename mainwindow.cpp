#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>


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
            disconnect(this->dialogRecordConnection);
            disconnect(this->newRecordConnection);
            disconnect(this->delRecordConnection);
            switch (index)
            {
            case TABLE::StudentsTableTab:
            {
               newRecordConnection = connect(ui->newRecordButton, QPushButton::clicked, [=]()
                {
                    emit this->newStudent->showDialog(StudentsTableModel->record());
                    dialogRecordConnection = connect(this->newStudent, Dialog::recordCompleted, [&](QSqlRecord rec)
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
                     dialogRecordConnection = connect(this->newTeacher, newTeacherDialog::recordCompleted, [&](QSqlRecord rec)
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

    case TABLE::TeachersTableTab:
    {
        int row_count = TeachersTableModel->rowCount();
        for( int i = 0; i < row_count; i++ )
        {
            QModelIndex name = TeachersTableModel->index(i, 1);
            if(TeachersTableModel->data(name).toString() == search)
            {
                ui->TeachersTableView->setFocus();
                ui->TeachersTableView->setCurrentIndex(name);
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
    default:
        break;
    }
}
void MainWindow::on_pushButton_clicked()
{
    int current_tab = this->ui->tabWidget->currentIndex();

    QPrinter printer;
    QTableView *myWidget;

    switch(current_tab)
    {
    case TABLE::StudentsTableTab:
        myWidget = this->ui->StudentsTableView;
        break;

    case TABLE::TeachersTableTab:
        myWidget = this->ui->TeachersTableView;
        break;
    default:
        return;
    }

    QPixmap pix = myWidget->grab();
    QPainter painter;
    printer.setResolution(QPrinter::HighResolution);

    printer.setPageMargins (15,15,15,15,QPrinter::Millimeter);
    painter.begin(&printer);
    double xscale = printer.pageRect().width()/double(myWidget->width() + 50);
    double yscale = printer.pageRect().height()/double(myWidget->height() + 50);
    double scale = qMin(xscale, yscale);
    painter.scale(scale, scale);

    painter.drawPixmap(0, 0, pix);
    painter.end();

    myWidget->render(&painter);

}

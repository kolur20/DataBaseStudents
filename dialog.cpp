#include "dialog.h"
#include "ui_dialog.h"

enum Facultets {
    Avia,
    Automatic,
    Agroprom,
    BGD,
    Transport,
    Stroitel,
    Menedjment,
    IiBT,
    Mashin};

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->speciallytiz.append(QStringList()
                              << "Вертолётостроение"
                              << "Ремонт и обслуживание воздушных судов"
                              << "Холодильная, криогенная техника и системы жизнеобеспечения");
    this->speciallytiz.append(QStringList()
                              <<"Автоматизация технологических процессов и производств"
                              <<"Управление в технических системах"
                              <<"Инноватика"
                              <<"Технологические машины и оборудование"
                              <<"Энергетическое машиностроение"
                              <<"Мехатроника и робототехника");
    this->speciallytiz.append(QStringList()
                              <<"Продукты питания из растительного сырья"
                              <<"Технологические машины и оборудование");
    this->speciallytiz.append(QStringList()
                              <<"Водные биоресурсы и аквакультура"
                              <<"Техносферная безопасность"
                              <<"Пожарная безопасность");
    this->speciallytiz.append(QStringList()
                              <<"Геодезия и дистанционное зондирование. Геодезическое обеспечение строительства инженерных сооружений"
                              <<"Геодезия и дистанционное зондирование. Геодезия"
                              <<"Прикладная геодезия. Инженерная геодезия");
    this->speciallytiz.append(QStringList()
                              <<"Строительство"
                              <<"Строительство уникальных зданий и сооружений");
    this->speciallytiz.append(QStringList()
                              <<"Антикризисное управление"
                              <<"Маркетинг"
                              <<"Торговое дело"
                              <<"Экономика");
    this->speciallytiz.append(QStringList()
                              <<"Информационные системы в научных исследований"
                              <<"Прикладная информатика. Прикладная информатика в информационной сфере"
                              <<"Математическое обеспечение и администрирование информационных систем"
                              <<"Программная инженерия");
    this->speciallytiz.append(QStringList()
                              <<"Конструирование изделий лёгкой промышленности"
                              <<"Машиностроение"
                              <<"Оборудование и технология сварочного производства"
                              <<"Металлургия"
                              <<"Материаловедение и технологии материалов"
                              <<"Наноинженерия");




    connect(this->ui->FacultyComboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(onFacultChanged(int)));
    emit ui->FacultyComboBox->currentIndexChanged(0);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onFacultChanged(int fakNum)
{

    this->ui->CpecialitiComboBox->clear();
    switch(fakNum)
    {

    case Avia:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[0]);
        break;

    case Automatic:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[1]);
        break;

    case Agroprom:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[2]);
        break;

    case BGD:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[3]);
        break;

    case Transport:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[4]);
        break;

    case Stroitel:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[5]);
        break;

    case Menedjment:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[6]);
        break;

    case IiBT:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[7]);
        break;

    case Mashin:
        this->ui->CpecialitiComboBox->addItems(this->speciallytiz[8]);
        break;


    }
}

void Dialog::showDialog(const QSqlRecord &rec)
{
    this->rec = rec;
    this->show();

    connect(ui->selectRecordButton,QPushButton::clicked, [&]()
    {

        this->rec.setValue(FIELD_FACULTY,this->ui->FacultyComboBox->currentText());
        this->rec.setValue(FIELD_FIO,this->ui->FioLineEdit->text());
        this->rec.setValue(FIELD_GROUP,this->ui->GroupLineEdit->text());
        this->rec.setValue(FIELD_PHONE,this->ui->PhoneLineEdit->text());
        this->rec.setValue(FIELD_SPECIALITI,this->ui->CpecialitiComboBox->currentText());

        this->rec.setValue(FIELD_YEAR_OF_BIRTH, this->ui->BirthDateEdit->text());
        this->rec.setValue(FIELD_RECORD_BOOK, this->ui->BookLineEdit->text());

//        qDebug() << this->ui->BirthDateEdit->text()
//                 << this->ui->BookLineEdit->text();

        emit this->recordCompleted(this->rec);


        this->hide();
        this->ui->FioLineEdit->clear();
        this->ui->GroupLineEdit->clear();
        this->ui->PhoneLineEdit->clear();
        this->ui->BookLineEdit->clear();



    });
}

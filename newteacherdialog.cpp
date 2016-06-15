#include "newteacherdialog.h"
#include "ui_newteacherdialog.h"

newTeacherDialog::newTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newTeacherDialog)
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

    this->post.append(QStringList()
                      <<"Аспирант"
                      <<"Ассистент"
                      <<"Ведущий научный сотрудник"
                      <<"Главный научный сотрудник"
                      <<"Докторант"
                      <<"Доцент"
                      <<"Младший научный сотрудник"
                      <<"Научный сотрудник"
                      <<"Преподаватель"
                      <<"Профессор"
                      <<"Старший преподаватель"
                      <<"Стажер"
                      <<"Старший научный сотрудник"
                      <<"Студент");
    emit ui->facultyComboBox->currentIndexChanged(0);
    emit ui->postComboBox->currentIndexChanged(0);
//connect exit

}

newTeacherDialog::~newTeacherDialog()
{
    delete ui;
}

void newTeacherDialog::showDialog(const QSqlRecord &rec)
{
    this->rec = rec;
    this->show();
    connect(ui->selectRecordButton,QPushButton::clicked, [&]()
    {

    this->rec.setValue(FIELD_FIO, this->ui->fioLineEdit->text());
    this->rec.setValue(FIELD_PHONE, this->ui->phoneLineEdit->text());
    this->rec.setValue(FIELD_POST, this->ui->postComboBox->currentText()  );
    this->rec.setValue(FIELD_SPECIALITI, this->ui->facultyComboBox->currentText());

    emit this->recordCompleted(this->rec);
    this->hide();
    this->ui->fioLineEdit->clear();
    this->ui->phoneLineEdit->clear();
    });

}

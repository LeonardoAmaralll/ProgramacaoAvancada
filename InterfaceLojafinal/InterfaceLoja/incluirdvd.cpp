#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::clear()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString nome = ui->lineEdit->text();
    QString preco = ui->lineEdit_2->text();
    QString dur = ui->lineEdit_3->text();
    emit signIncluirDVD(nome, preco, dur);
}

#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::clear()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}

void IncluirCD::on_buttonBox_accepted()
{
    QString nome = ui->lineEdit->text();
    QString preco = ui->lineEdit_2->text();
    QString faixas = ui->lineEdit_3->text();
    emit signIncluirCD(nome, preco, faixas);
}

#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::clear()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}

void IncluirLivro::on_buttonBox_accepted()
{
    QString nome = ui->lineEdit->text();
    QString preco = ui->lineEdit_2->text();
    QString autor = ui->lineEdit_3->text();
    emit signIncluirLivro(nome, preco, autor);

}

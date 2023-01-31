#include "mainloja.h"
#include "ui_mainloja.h"

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
{
    ui->setupUi(this);

    statusBar()->insertWidget(0, new QLabel("Total de Itens:"));
    //statusBar()->insertWidget(1, new QLabel(/*TotalItens*/));

}

MainLoja::~MainLoja()
{
    delete ui;
}


void MainLoja::on_tableWidget_cellDoubleClicked(int row, int column)
{

}


void MainLoja::on_tableWidget_2_cellDoubleClicked(int row, int column)
{

}


void MainLoja::on_tableWidget_3_cellDoubleClicked(int row, int column)
{

}


void MainLoja::on_action_Ler_triggered()
{
    QString file;
    file = QFileDialog::getOpenFileName(this, tr("Ler estoque"));
    std::string file2 = file.toUtf8().constData();
    bool verify = X->ler(file2);
    if(verify != true)
    {
        QMessageBox fail;
        fail.critical(nullptr,"Erro","Não Foi Possivel Abrir o Arquivo");
    }
}


#include "mainloja.h"
#include "ui_mainloja.h"

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    , X()
    , inclLivro(nullptr)
    , inclCD(nullptr)
    , inclDVD(nullptr)
    , total_itens(nullptr)
{
    ui->setupUi(this);



    inclLivro = new IncluirLivro(this);
    inclCD = new IncluirCD(this);
    inclDVD = new IncluirDVD(this);
    total_itens = new QLabel(this);
    total_itens->setNum(0);

    ui->label->setStyleSheet("background-color:lightgray");
    ui->label_2->setStyleSheet("background-color:lightgray");
    ui->label_3->setStyleSheet("background-color:lightgray");

    ui->tableWidget->setStyleSheet("QHeaderView::section {background-color:lightgray}");
    ui->tableWidget_2->setStyleSheet("QHeaderView::section {background-color:lightgray}");
    ui->tableWidget_3->setStyleSheet("QHeaderView::section {background-color:lightgray}");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    connect(inclLivro, &IncluirLivro::signIncluirLivro,
            this,&MainLoja::slotIncluirLivro);

    connect(inclCD, &IncluirCD::signIncluirCD,
            this,&MainLoja::slotIncluirCD);

    connect(inclDVD, &IncluirDVD::signIncluirDVD,
            this,&MainLoja::slotIncluirDVD);

    statusBar()->insertWidget(0, new QLabel("Total de Itens:"));
    statusBar()->insertWidget(1, total_itens);

    exibeListas();



}

MainLoja::~MainLoja()
{
    delete ui;
}


void MainLoja::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if(row < ui->tableWidget->rowCount() )
    {
        X.excluirLivro(row);
        exibeListas();
    }
}


void MainLoja::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    if(row < ui->tableWidget_2->rowCount() )
    {
        X.excluirCD(row);
        exibeListas();
    }
}


void MainLoja::on_tableWidget_3_cellDoubleClicked(int row, int column)
{
    if(row < ui->tableWidget_3->rowCount() )
    {
        X.excluirDVD(row);
        exibeListas();
    }
}


void MainLoja::on_action_Ler_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Ler estoque",QString(),"Text files (*.txt)");
    std::string arq = file.toStdString();
    std::string arq2;
    for(int i = arq.size(); i >= 0; i--)
    {
        if(arq[i] == '/')
        {
            arq2 = arq.substr(i+1);
            break;
        }
    }
    bool verify = X.ler(arq2);
    if(!verify)
    {
        QMessageBox fail;
        fail.critical(nullptr,"Erro","Nao Foi Possivel Abrir o Arquivo");
        return;
    }
    exibeListas();
}



void MainLoja::on_action_Salvar_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Salvar estoque");
    std::string arq = file.toStdString();
    std::string arq2;
    for(int i = arq.size(); i >= 0; i--)
    {
        if(arq[i] == '/')
        {
            arq2 = arq.substr(i+1);
            break;
        }
    }
    bool verify = X.salvar(arq2);
    if(!verify)
    {
        QMessageBox fail;
        fail.critical(nullptr,"Erro","Nao Foi Possivel Salvar o Arquivo");
        return;
    }
}


void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void MainLoja::on_action_Incluir_Livro_triggered()
{
    inclLivro->clear();
    inclLivro->show();
}

void MainLoja::on_action_Incluir_CD_triggered()
{
    inclCD->clear();
    inclCD->show();
}

void MainLoja::on_action_Incluir_DVD_triggered()
{
    inclDVD->clear();
    inclDVD->show();
}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
    std::string nomePL = nome.toStdString();
    unsigned precoPL = round(preco.toUInt() * 100);
    std::string autorL = autor.toStdString();
    Livro L(nomePL,precoPL,autorL);
    X.incluirLivro(L);
    if(L.getNome() == "" || L.getPreco() <= 0 || L.getAutor() == "")
    {
        QMessageBox fail;
        fail.critical(this, "Livro invalido", QString("Nao foi possivel incluir o Livro\n") + QString("Nome=") + nome + QString("\nPreco=") + preco +QString("\nAutor=") + autor);
    }
    else
    {
        exibeListas();
    }
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString faixas)
{
    std::string nomePC = nome.toStdString();
    unsigned precoPC = round(preco.toUInt() * 100);
    unsigned faixasC = faixas.toUInt();
    CD C(nomePC, precoPC, faixasC);
    X.incluirCD(C);
    if(C.getNome() == "" || C.getPreco() <= 0 || C.getNumFaixas() <= 0)
    {
        QMessageBox fail;
        fail.critical(this, "Livro invalido", QString("Nao foi possivel incluir o CD\n") + QString("Nome=") + nome + QString("\nPreco=") + preco +QString("\nN Faixas=") + faixas);
    }
    else
    {
        exibeListas();
    }
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString dur)
{
    std::string nomePD = nome.toStdString();
    unsigned precoPD = round(preco.toUInt() * 100);
    unsigned durD = dur.toUInt();
    DVD D(nomePD,precoPD,durD);
    X.incluirDVD(D);
    if(D.getNome() == "" || D.getPreco() <= 0 || D.getDuracao() <= 0)
    {
        QMessageBox fail;
        fail.critical(this, "Livro invalido", QString("Nao foi possivel incluir o DVD\n") + QString("Nome=") + nome + QString("\nPreco=") + preco +QString("\nDuracao=") + dur);
    }
    else
    {
        exibeListas();
    }
}

void MainLoja::exibeListas()
{
    ui->tableWidget->clearContents();
    ui->tableWidget_2->clearContents();
    ui->tableWidget_3->clearContents();

    ui->tableWidget->setRowCount(X.getNumLivro());
    ui->tableWidget_2->setRowCount(X.getNumCD());
    ui->tableWidget_3->setRowCount(X.getNumDVD());

    for(int i = 0; i <= int(X.getNumLivro()) - 1;i++)
    {
        QLabel *col;
        QLabel *col2;
        QLabel *col3;

        Livro liv = X.getLivro(i);
        col = new QLabel(liv.getNome().c_str());
        col2 = new QLabel(QString::number(liv.getPreco(),'f',2));
        col3 = new QLabel(liv.getAutor().c_str());

        col->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        col2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        col3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

        ui->tableWidget->setCellWidget(i,0,col);
        ui->tableWidget->setCellWidget(i,1,col2);
        ui->tableWidget->setCellWidget(i,2,col3);
    }

    for(int i = 0; i <= int(X.getNumCD()) - 1;i++)
    {
        QLabel *col;
        QLabel *col2;
        QLabel *col3;

        CD cd = X.getCD(i);
        col = new QLabel(cd.getNome().c_str());
        col2 = new QLabel(QString::number(cd.getPreco(),'f',2));
        col3 = new QLabel(QString::number(cd.getNumFaixas()));

        col->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        col2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        col3->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

        ui->tableWidget_2->setCellWidget(i,0,col);
        ui->tableWidget_2->setCellWidget(i,1,col2);
        ui->tableWidget_2->setCellWidget(i,2,col3);

    }

    for(int i = 0; i <= int(X.getNumDVD()) - 1;i++)
    {
        QLabel *col;
        QLabel *col2;
        QLabel *col3;

        DVD dvd = X.getDVD(i);
        col = new QLabel(dvd.getNome().c_str());
        col2 = new QLabel(QString::number(dvd.getPreco(),'f',2));
        col3 = new QLabel(QString::number(dvd.getDuracao()));

        col->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        col2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        col3->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

        ui->tableWidget_3->setCellWidget(i,0,col);
        ui->tableWidget_3->setCellWidget(i,1,col2);
        ui->tableWidget_3->setCellWidget(i,2,col3);
    }

    total_itens->setNum(int(X.getNumLivro()+X.getNumCD()+X.getNumDVD()));
}



#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include "loja.h"
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();

    void exibeListas();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_tableWidget_2_cellDoubleClicked(int row, int column);

    void on_tableWidget_3_cellDoubleClicked(int row, int column);

    void on_action_Ler_triggered();

    void on_action_Salvar_triggered();

    void on_actionSair_triggered();

    void on_action_Incluir_Livro_triggered();

    void on_action_Incluir_CD_triggered();

    void on_action_Incluir_DVD_triggered();

    void slotIncluirLivro(QString nome,QString preco, QString autor);

    void slotIncluirCD(QString nome,QString preco, QString faixas);

    void slotIncluirDVD(QString nome,QString preco, QString dur);

private:
    Ui::MainLoja *ui;
    Loja X;
    IncluirLivro* inclLivro;
    IncluirCD* inclCD;
    IncluirDVD* inclDVD;
    QLabel* total_itens;
};
#endif // MAINLOJA_H

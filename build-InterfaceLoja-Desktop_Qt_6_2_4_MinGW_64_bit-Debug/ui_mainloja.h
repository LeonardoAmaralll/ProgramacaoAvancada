/********************************************************************************
** Form generated from reading UI file 'mainloja.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINLOJA_H
#define UI_MAINLOJA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainLoja
{
public:
    QAction *action_Ler;
    QAction *action_Salvar;
    QAction *actionSair;
    QAction *action_Incluir_Livro;
    QAction *action_Incluir_CD;
    QAction *action_Incluir_DVD;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableWidget *tableWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTableWidget *tableWidget_3;
    QMenuBar *menubar;
    QMenu *menuItem;
    QMenu *menuArquivo;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainLoja)
    {
        if (MainLoja->objectName().isEmpty())
            MainLoja->setObjectName(QString::fromUtf8("MainLoja"));
        MainLoja->resize(1000, 600);
        action_Ler = new QAction(MainLoja);
        action_Ler->setObjectName(QString::fromUtf8("action_Ler"));
        action_Salvar = new QAction(MainLoja);
        action_Salvar->setObjectName(QString::fromUtf8("action_Salvar"));
        actionSair = new QAction(MainLoja);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        action_Incluir_Livro = new QAction(MainLoja);
        action_Incluir_Livro->setObjectName(QString::fromUtf8("action_Incluir_Livro"));
        action_Incluir_CD = new QAction(MainLoja);
        action_Incluir_CD->setObjectName(QString::fromUtf8("action_Incluir_CD"));
        action_Incluir_DVD = new QAction(MainLoja);
        action_Incluir_DVD->setObjectName(QString::fromUtf8("action_Incluir_DVD"));
        centralwidget = new QWidget(MainLoja);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAutoFillBackground(true);
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Plain);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setFrameShape(QFrame::Box);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAutoFillBackground(true);
        label_2->setFrameShape(QFrame::Box);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        tableWidget_2 = new QTableWidget(centralwidget);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_2->setTabKeyNavigation(false);
        tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_2->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableWidget_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAutoFillBackground(true);
        label_3->setFrameShape(QFrame::Box);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        tableWidget_3 = new QTableWidget(centralwidget);
        if (tableWidget_3->columnCount() < 3)
            tableWidget_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_3->setTabKeyNavigation(false);
        tableWidget_3->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_3->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(tableWidget_3);


        horizontalLayout->addLayout(verticalLayout_3);

        MainLoja->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainLoja);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuItem = new QMenu(menubar);
        menuItem->setObjectName(QString::fromUtf8("menuItem"));
        menuArquivo = new QMenu(menubar);
        menuArquivo->setObjectName(QString::fromUtf8("menuArquivo"));
        MainLoja->setMenuBar(menubar);
        statusBar = new QStatusBar(MainLoja);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setMouseTracking(false);
        statusBar->setContextMenuPolicy(Qt::DefaultContextMenu);
        statusBar->setAcceptDrops(true);
        MainLoja->setStatusBar(statusBar);
        QWidget::setTabOrder(tableWidget, tableWidget_3);
        QWidget::setTabOrder(tableWidget_3, tableWidget_2);

        menubar->addAction(menuArquivo->menuAction());
        menubar->addAction(menuItem->menuAction());
        menuItem->addAction(action_Incluir_Livro);
        menuItem->addAction(action_Incluir_CD);
        menuItem->addAction(action_Incluir_DVD);
        menuArquivo->addAction(action_Ler);
        menuArquivo->addAction(action_Salvar);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);

        retranslateUi(MainLoja);

        QMetaObject::connectSlotsByName(MainLoja);
    } // setupUi

    void retranslateUi(QMainWindow *MainLoja)
    {
        MainLoja->setWindowTitle(QCoreApplication::translate("MainLoja", "Estoque em loja", nullptr));
        action_Ler->setText(QCoreApplication::translate("MainLoja", "\"Ler\"", nullptr));
        action_Salvar->setText(QCoreApplication::translate("MainLoja", "\"Salvar\"", nullptr));
        actionSair->setText(QCoreApplication::translate("MainLoja", "Sair", nullptr));
        action_Incluir_Livro->setText(QCoreApplication::translate("MainLoja", "\"Incluir Livro\"", nullptr));
        action_Incluir_CD->setText(QCoreApplication::translate("MainLoja", "\"Incluir CD\"", nullptr));
        action_Incluir_DVD->setText(QCoreApplication::translate("MainLoja", "\"Incluir DVD\"", nullptr));
        label->setText(QCoreApplication::translate("MainLoja", "LIVROS", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainLoja", "NOME", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainLoja", "PRECO", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainLoja", "AUTOR", nullptr));
        label_2->setText(QCoreApplication::translate("MainLoja", "CDS", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainLoja", "NOME", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainLoja", "PRECO", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainLoja", "N FAIXAS", nullptr));
        label_3->setText(QCoreApplication::translate("MainLoja", "DVDS", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainLoja", "NOME", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainLoja", "PRECO", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainLoja", "DURACAO", nullptr));
        menuItem->setTitle(QCoreApplication::translate("MainLoja", "Item", nullptr));
        menuArquivo->setTitle(QCoreApplication::translate("MainLoja", "Arquivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainLoja: public Ui_MainLoja {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINLOJA_H

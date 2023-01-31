#ifndef INCLUIRDVD_H
#define INCLUIRDVD_H

#include <QDialog>

namespace Ui {
class IncluirDVD;
}

class IncluirDVD : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirDVD(QWidget *parent = nullptr);
    ~IncluirDVD();

     void clear();

private:
    Ui::IncluirDVD *ui;

signals:
    QString signIncluirDVD(QString nome, QString preco, QString dur);

private slots:
    void on_buttonBox_accepted();
};

#endif // INCLUIRDVD_H

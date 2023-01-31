#include "whatsprog_login.h"
#include "ui_whatsprog_login.h"
#include "whatsprog_main.h"
#include <qmessagebox.h>

WhatsProgLogin::WhatsProgLogin(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WhatsProgLogin)
{
  ui->setupUi(this);

  ui->lineEditSenhaUsuario->setEchoMode( QLineEdit::Password );
}

WhatsProgLogin::~WhatsProgLogin()
{
  delete ui;
}

void WhatsProgLogin::slotLogin(bool NovoUsuario)
{
  novoUsuario = NovoUsuario;
  if (novoUsuario) setWindowTitle("Usuario - Criar");
  else setWindowTitle("Usuario - Conectar");
  ui->lineEditIpServidor->clear();
  ui->lineEditNomeUsuario->clear();
  ui->lineEditSenhaUsuario->clear();
  show();
}

void WhatsProgLogin::on_buttonBox_accepted()
{
    QString ip,user,senha;

    ip = ui->lineEditIpServidor->text();
    user = ui->lineEditNomeUsuario->text();
    senha = ui->lineEditSenhaUsuario->text();

    if(testarNomeUsuario(user.toStdString()) && testarSenha(senha.toStdString()))
    {
        emit sign_newuser(ip,user,senha, novoUsuario);
        ui->lineEditIpServidor->clear();
        ui->lineEditNomeUsuario->clear();
        ui->lineEditSenhaUsuario->clear();
    }
    else
    {
        QMessageBox::critical(this, "Erro ao logar", "Valores errados");
    }
}

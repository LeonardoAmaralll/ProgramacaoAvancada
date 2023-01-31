#include <QApplication>
#include <QMessageBox>
#include <thread>

#include "whatsprog_main.h"
#include "../MySocket/mysocket.h"
#include "whatsprog_dados_cliente.h"
#include "whatsprog_dados.h"

/// A variavel global que contem todas as msgs de todas as conversas
WhatsProgDadosCliente DC;
/// O socket do cliente, a ser utilizado por todas as threads
tcp_mysocket sock;
/// A thread de leitura do socket
std::thread thr; // Thread nao executando (not joinable)


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  WhatsProgMain w;

  //inicializa a API de sockets
  mysocket_status ini_socket = mysocket::init();
  if(ini_socket != mysocket_status::SOCK_OK){
      std::cerr << "Biblioteca mysocket nao pode ser inicializada\n";
      exit(1);
  }

  w.show();

  int prov = a.exec();

  if (thr.joinable()){
      thr.join();
  }

  //Encerra a API de sockets
  mysocket::end();
  return prov;
}

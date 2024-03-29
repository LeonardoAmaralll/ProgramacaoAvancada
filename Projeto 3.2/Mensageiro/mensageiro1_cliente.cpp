#include <iostream>
#include <string.h>
#include <thread>

#include "../MySocket/mysocket.h"
#include "mensageiro.h"

using namespace std;

/* ==================================================================

Este aplicativo cliente-servidor permite o envio de mensagens entre
os softwares clientes e o software servidor.
As mensagens trocadas sao formadas pelos seguintes campos:
1) Usuario - uma string
   Significa o destinatario, nas msgs do cliente para o servidor,
   ou o remetente, nas msgs do servidor para o cliente
2) Texto - uma string
   Contem a msg efetivamente enviada

A primeira msg a ser enviada pelo cliente para o servidor eh
diferente das demais. Deve conter apenas o nome do usuario. Esse
nome identificarah o cliente daih em diante: todas as msgs enviadas
para esse nome do usuario serao direcionadas pelo servidor para esse
cliente.
O login (nome do cliente) deve ter entre 4 e 16 caracteres.

================================================================== */

/* ==================================================================

Este programa tem uma thread principal que espera que o usu�rio
digite alguma coisa e envia esta msg para um servidor via
socket. Uma outra thread imprime todas as msgs recebidas pelo
socket.

================================================================== */

/// Aqui vao as vari�veis globais das duas threads

// O socket de comunicacao
tcp_mysocket s;
// O flag que indica que o software deve encerrar todas as threads
bool fim = false;

/// Esta e a thread que escreve em tela as mensagens recebidas

void le_msg(void)
{
  string remetente,msg;
  mysocket_status iResult;

  cout << "Iniciando a thread de leitura do socket!\n";
  while (!fim) {
    try
    {
      // Leh login do remetente (sem timeout)
      iResult = s.read_string(remetente);
      if (!fim && s.connected())
      {
        if (iResult==mysocket_status::SOCK_ERROR) throw "leitura do remetente";
        if (iResult==mysocket_status::SOCK_DISCONNECTED) throw "servidor desconectou";
        // Leh texto da mensagem
        // Maximo MENSAGEIRO_TIMEOUT segundos depois do remetente
        iResult = s.read_string(msg, 1000*MENSAGEIRO_TIMEOUT);
        if (iResult==mysocket_status::SOCK_ERROR) throw "leitura do texto";
        if (iResult==mysocket_status::SOCK_DISCONNECTED) throw "servidor desconectou";
        if (iResult==mysocket_status::SOCK_TIMEOUT) throw "timeout no texto";
        // Avisa msg recebida
        cout << endl
             << "=========================================================\n"
             << "Mensagem recebida de " << remetente <<":\n"
             << msg << endl
    	       << "=========================================================\n";
      }
    }
    catch(const char* err)
    {
      cerr << "Erro na leitura do socket: " << err << endl;
      fim = true;
    }
  }
}

/// O programa principal contem o ciclo que envia as mensagens digitadas

int main(int argc, char **argv)
{
  thread thr;
  string usuario;
  string msg;
  mysocket_status iResult;

  // Inicializa a biblioteca de sockets
  iResult = mysocket::init();
  if (iResult != mysocket_status::SOCK_OK) {
    cerr << "Biblioteca mysocket nao pode ser inicializada\n";
    exit(1);
  }

  // Determina o numero IP do servidor
  cout << "Maquina onde estah rodando o servidor (IP): ";
  cin >> ws;
  getline(cin, msg);

  // Conecta com o servidor
  iResult = s.connect(msg.c_str(), MENSAGEIRO_PORTA);
  if (iResult == mysocket_status::SOCK_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << MENSAGEIRO_PORTA << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << MENSAGEIRO_PORTA << endl;
    exit(2);
  }

  // Cria a thread que escreve as mensagens recebidas
  thr = thread(le_msg);
  if (!thr.joinable())
  {
    cerr << "Problema ao criar thread\n";
    s.close();
    exit(3);
  }
  // Espera 1 seg para as mensagens nao se sobreporem no terminal
  this_thread::sleep_for(chrono::seconds(1));

  // Envia para o servidor o nome de usuario que identificarah esse cliente
  do
  {
    cout << "Login deste cliente [4 a 16 caracteres]: ";
    cin >> ws;
    getline(cin, usuario);
  } while (usuario.size()<4 || usuario.size()>16);
  iResult = s.write_string(usuario);
  if ( iResult == mysocket_status::SOCK_ERROR )
  {
    cerr << "Problema na escrita do login no socket...\n";
    exit(4);
  }

  // Este � o ciclo que envia as mensagens digitadas
  while (!fim)
  {
    // Solicita o destinatario
    if (!fim)
    {
      do
      {
        cout << "Usuario para enviar msg [4 a 16 caracteres, FIM para terminar]: ";
        cin >> ws;
        getline(cin, usuario);
      } while (!fim && usuario!="FIM" && (usuario.size()<4 || usuario.size()>16));
      if (!fim) fim = (usuario=="FIM");
    }
    // Solicita o texto da msg
    if (!fim)
    {
      do
      {
        cout << "Mensagem a enviar [FIM para terminar]: ";
        cin >> ws;
        getline(cin, msg);
      } while (!fim && msg.size()==0);
      if (!fim) fim = (msg=="FIM");
    }
    // Se decidiu terminar e o socket ainda estah aberto,
    // informa ao servidor
    if (fim && s.connected())
    {
      iResult = s.write_string("FIM");
      // Nao testa o resultado pq o programa jah estah acabando mesmo...
    }
    // Envia o destinatario
    if (!fim)
    {
      iResult = s.write_string(usuario);
      if ( iResult != mysocket_status::SOCK_OK )
      {
        cout << "Problema na escrita do usuario no socket...\n";
        fim = true;
      }
    }
    // Envia o texto
    if (!fim)
    {
      iResult = s.write_string(msg);
      if ( iResult != mysocket_status::SOCK_OK )
      {
        cout << "Problema na escrita do texto no socket...\n";
        fim = true;
      }
    }
    // Espera 1 seg para as mensagens nao se sobreporem no terminal
    this_thread::sleep_for(chrono::seconds(1));
  }

  // Encerra o socket
  s.close();

  // Espera pelo fim da thread de recepcao
  if (thr.joinable())
  {
    cout << "Esperando o fim da thread...\n";
    thr.join();
  }

  // Encerra a biblioteca de sockets
  mysocket::end();
}

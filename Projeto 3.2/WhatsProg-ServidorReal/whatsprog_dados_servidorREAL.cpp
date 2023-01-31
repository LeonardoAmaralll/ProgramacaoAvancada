#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "whatsprog_dados_servidorREAL.h"

/// O flag que indica que o software deve encerrar todas as threads
extern bool fim;


/// Funcao auxiliar que imprime um comando tratado pelo servidor
static void imprimeComando(bool recebido, const string& user, ComandoWhatsProg cmd,
                           int id, const string& user2)
{
  cout << "CMD " << (recebido ? "REC DE" : "ENV P/") << ' '
       << user << ": " << nome_cmd(cmd);
  if (id > 0) cout << ',' << id;
  if (user2.size() > 0) cout << ',' << user2;
  cout << endl;
}

/// Funcao auxiliar que imprime um comando enviado pelo servidor
inline static void imprimeComandoEnviado(const string& user, ComandoWhatsProg cmd,
    int id=-1, const string& user2="")
{
  imprimeComando(false, user, cmd, id, user2);
}

/// Funcao auxiliar que imprime um comando recebido pelo servidor
inline static void imprimeComandoRecebido(const string& user, ComandoWhatsProg cmd,
    int id=-1, const string& user2="")
{
  imprimeComando(true, user, cmd, id, user2);
}

/// Funcoes auxiliares para impressao
ostream& operator<<(ostream& O, const Mensagem& M)
{
  O << M.getId() << ';' << nome_status(M.getStatus()) << ';'
    << M.getRemetente() << ';' << M.getDestinatario() << ';'
    << M.getTexto();
  return O;
}

ostream& operator<<(ostream& O, const Usuario& U)
{
  O << U.getLogin() << ';' << U.getLastId();
  return O;
}

/// CLASSE USUARIO

/// Construtor default
Usuario::Usuario(): login(""), senha(""), s(), last_id(0) {}

/// Funcao de consulta ao valor para login
const string& Usuario::getLogin() const
{
  return login;
}

/// Fixa login e senha do usuario
/// Retorna true se OK; false em caso de erro
bool Usuario::setUsuario(const string& L, const string& S)
{
  if (!testarNomeUsuario(L) || !testarSenha(S))
  {
    return false;
  }
  login = L;
  senha = S;
  return true;
}

/// Testa se a senha eh valida
/// Aqui normalmente haveria criptografia.
/// Mas como eh um software didatico...
bool Usuario::validarSenha(const string& S) const
{
  return senha==S;
}

/// Funcoes de acesso ao socket do usuario
const tcp_mysocket& Usuario::getSocket() const
{
  return s;
}

/// Alteracao do socket de um usuario
void Usuario::swapSocket(tcp_mysocket& S)
{
  s.swap(S);
}

/// Consulta do estado do socket
bool Usuario::connected() const
{
  return s.connected();
}

bool Usuario::closed() const
{
  return s.closed();
}

/// Funcoes de envio de dados via socket
mysocket_status Usuario::read_int(int32_t& num, long milisec) const
{
  return s.read_int(num,milisec);
}

mysocket_status Usuario::write_int(int32_t num) const
{
  return s.write_int(num);
}

mysocket_status Usuario::read_string(string& msg, long milisec) const
{
  return s.read_string(msg,milisec);
}

mysocket_status Usuario::write_string(const string& msg) const
{
  return s.write_string(msg);
}

/// Fechamento do socket
void Usuario::close()
{
  s.close();
}

/// Consulta da ultima ID do usuario
int32_t Usuario::getLastId() const
{
  return last_id;
}

bool Usuario::setLastId(int32_t ID)
{
  if (ID<=0 || ID<=last_id)
  {
    return false;
  }
  last_id = ID;
  return true;
}

/// CLASSE WHATSPROGDADOSSERVIDOR

/// Funcoes de acesso aas funcionalidades basicas dos sockets
mysocket_status WhatsProgDadosServidor::listen(const char *port, int nconex)
{
  return c.listen(port,nconex);
}

/// Fecha os sockets de todos os usuarios conectados
void WhatsProgDadosServidor::closeSockets()
{
  c.close();
  for(USS = Usuarios.begin(); USS != Usuarios.end(); USS++)
  {
      USS->close();
  }
}

/* **************************************************************************************
ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
para o servidor real, a nao ser que seja feita uma analise muito cuidadosa.
A fonte que contem informacao correta sobre como implementar o servidor eh
a especificacao. Alguns trechos de outros programas, como o servidor do mensageiro,
podem servir de ideia ou inspiracao, embora ***CERTAMENTE*** precisem ser adaptados.
************************************************************************************** */
/// Envia para o usuario as mensagens que estejam arquivadas (paraUsuario[])
/// com status MSG_RECEBIDA e que sejam destinadas ao usuario.
/// Apos o envio, altera o status da msg enviada para MSG_ENTREGUE
/// No servidor real deveria ser:
/// Envia todas as mensagens que estejam no buffer com status MSG_RECEBIDA
/// e que sejam destinadas ao destinatario para o qual o parametro iDest aponta.
/// Apos o envio, altera o status das msgs enviadas para MSG_ENTREGUE
/// void WhatsProgDadosServidor::enviarRecebidas(IterUsuario iDest)
void WhatsProgDadosServidor::enviarMsg(Usuario user)
{
  Mensagem M;
  if (user.connected())
  {
    do
    {
      ME1 = find(Mensagens.begin(), Mensagens.end(), testDestStatus(user.getLogin(),MsgStatus::MSG_RECEBIDA));
      //M = *ME1;
      if (ME1->getStatus()==MsgStatus::MSG_RECEBIDA)
      {
        bool envioOK = (user.write_int(CMD_NOVA_MSG) != mysocket_status::SOCK_ERROR);
        if (envioOK) envioOK = (user.write_int(M.getId()) != mysocket_status::SOCK_ERROR);
        if (envioOK) envioOK = (user.write_string(M.getRemetente()) != mysocket_status::SOCK_ERROR);
        if (envioOK) envioOK = (user.write_string(M.getTexto()) != mysocket_status::SOCK_ERROR);
        if (envioOK)
        {
          imprimeComandoEnviado(user.getLogin(), CMD_NOVA_MSG, ME1->getId(), ME1->getRemetente());
          // Mensagem enviada
          ME1->setStatus(MsgStatus::MSG_ENTREGUE);
          // Procura o usuario remetente
          US = find(Usuarios.begin(), Usuarios.end(),ME1->getRemetente());
          if (US != Usuarios.end() && US->connected())
          {
            // Remetente existe
            // Testa se o remetente estah conectado
            // Se sim, envia a confirmacao de entrega da mensagem

            /* No servidor FAKE nao faz nenhum teste aqui nem envia a confirmacao para o remetente ...
               Os usuarios simulados estao sempre "conectados" ...
               "Mente" que enviou a confirmacao para o remetente */

            imprimeComandoEnviado(ME1->getRemetente(), CMD_MSG_ENTREGUE, ME1->getId(), "");

          }
          else
          {
            // Remetente nao existe
            // NUNCA deve ocorrer no servidor FAKE
            cerr << "Remetente (" << ME1->getRemetente() << ") de uma msg armazenada nao existe\n";
          }
        }
        else
        {
          // Nao conseguiu enviar para o destinatario
          cerr << "Erro no envio de msg para destinatario " << user.getLogin() << ". Desconectando\n";
          user.close();
        }
      }
    }while(ME1 != Mensagens.end());
  }
}

/* **************************************************************************************
ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
para o servidor real, a nao ser que seja feita uma analise muito cuidadosa.
A fonte que contem informacao correta sobre como implementar o servidor eh
a especificacao. Alguns trechos de outros programas, como o servidor do mensageiro,
podem servir de ideia ou inspiracao, embora ***CERTAMENTE*** precisem ser adaptados.
************************************************************************************** */
/// Envia para o usuario as confirmacoes de visualizacao das mensagens
/// que estejam arquivadas (doUsuario[]) com status MSG_LIDA
/// e que tenham sido enviadas pelo usuario.
/// Apos o envio da confirmacao, apaga a msg
/// No servidor real deveria ser:
/// Envia todas as confirmacoes de visualizacao das mensagens
/// que estejam no buffer com status MSG_LIDA e que tenham sido enviadas
/// pelo remetente para o qual o parametro iRemet aponta.
/// Apos o envio das confirmacoes, remove as msgs do buffer
/// void WhatsProgDadosServidor::enviarConfirmacoes(IterUsuario iRemet)
void WhatsProgDadosServidor::enviarConfirmacoesParaUsuario(Usuario user)
{
  Mensagem M;
  if (user.connected()) while (ME2 != Mensagens.end())
    {
      ME2 = find(Mensagens.begin(), Mensagens.end(), testRemetStatus(user.getLogin(), MsgStatus::MSG_LIDA));
      if (ME2->getStatus()==MsgStatus::MSG_LIDA)
      {
        bool envioOK = (user.write_int(CMD_MSG_LIDA2) != mysocket_status::SOCK_ERROR);
        if (envioOK) envioOK = (user.write_int(M.getId()) != mysocket_status::SOCK_ERROR);
        if (!envioOK)
        {
          cerr << "Erro no envio de confirmacao de visualizaco para remetente "
               << user.getLogin() << ". Desconectando\n";
          user.close();
        }
        else
        {
          // A confirmacao de visualizacao foi enviada
          imprimeComandoEnviado(user.getLogin(), CMD_MSG_LIDA2, ME2->getId());
          // Remove a msg do buffer
          Mensagens.erase(ME2);
        }
      }
    }
}

/* **************************************************************************************
ATENCAO: a parte a seguir da implementacao do servidor FAKE pode ser parcialmente adaptada
para o servidor real, mas requer uma analise muito cuidadosa.
A fonte que contem informacao correta sobre como implementar o servidor eh
a especificacao. Alguns trechos de outros programas, como o servidor do mensageiro, tambem
podem servir de ideia ou inspiracao, embora ***CERTAMENTE*** precisem ser adaptados.
************************************************************************************** */
/// Funcao que efetivamente desempenha as tarefas do servidor
int WhatsProgDadosServidor::main_thread()
{
  /// A fila para select (esperar dados em varios sockets)
  mysocket_queue f;

  mysocket_status iResult;
  int32_t cmd;
  int32_t id;

  /// As ultimas ids dos usuarios fake (soh faz sentido no servidor fake)
  /// No servidor real, as last_id estao armazenados em cada usuario na
  /// lista de usuarios
  ///int32_t last_id[2] = {0,0};

  while (!fim)
  {
    fim = !c.accepting();
    if (fim)
    {
      cerr << "Socket de conexoes nao estah aceitando conexoes. Encerrando\n";
      return -1;
    }
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clear();
    f.include(c);
    for(USQ = Usuarios.begin(); USQ != Usuarios.end(); USQ++){


        ///f.include(c);
        // Soh tem um usuario neste servidor fake...
        // No servidor real, teria que percorrer a lista de usuarios e incluir
        // todos os que estiverem conectados
        if (USQ->connected())
        {
        f.include(USQ->getSocket());
        }
    }
    // Espera que chegue algum dado em qualquer dos sockets da fila
    iResult = f.wait_read(TIMEOUT_WHATSPROG*1000000000000000000);

    if (iResult == mysocket_status::SOCK_ERROR)
    {
      if (!fim) cerr << "Erro na espera por alguma atividade\n";
      fim = true;
    }
    if (iResult == mysocket_status::SOCK_TIMEOUT)
    {
      if (!fim) cerr << "Erro na espera por alguma atividade\n";
      fim = true;

      // Saiu por timeout: nao houve atividade em nenhum socket da fila
      // Pode aproveitar para salvar o arquivo de dados no servidor real (opcional)

      /* **************************************************************************************
      ATENCAO: ***NADA*** da parte a seguir da implementacao do servidor FAKE pode ser adaptada
      para o servidor real.
      A fonte que contem informacao correta sobre como implementar o servidor eh
      a especificacao. Alguns trechos de outros programas, como o servidor do mensageiro,
      podem servir de ideia ou inspiracao, embora ***CERTAMENTE*** precisem ser adaptados.
      ************************************************************************************** */
      /* Fim da parte que ***NAO*** pode ser adaptada para o servidor real ***************** */
    }
    if (iResult == mysocket_status::SOCK_OK)
    {
      // Houve atividade em algum socket da fila
      // Testa em qual socket houve atividade.

      // Primeiro, testa os sockets dos clientes
      // Soh tem um usuario neste servidor fake...
      // No servidor real, teria que percorrer a lista de usuarios e testar
      // cada um dos sockets de usuario
      for(US2 = Usuarios.begin(); US2 != Usuarios.end(); US2++){

      if (!fim && US2->connected() && f.had_activity(US2->getSocket()))
      {
        // Leh o comando recebido do cliente
        iResult = US2->read_int(cmd);
        if (iResult != mysocket_status::SOCK_OK)
        {
          // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
          // Nao deve ser mysocket_status::SOCK_TIMEOUT porque a funcao read_int nao foi chamada com tempo maximo
          if (iResult == mysocket_status::SOCK_ERROR)
          {
            cerr << "Erro na leitura de comando do cliente " << US2->getLogin() << ". Desconectando\n";
          }
          US2->close();
        }
        // Se a leitura foi correta, executa o comando lido
        if (US2->connected()) switch(cmd)
          {
          case CMD_NEW_USER:
          case CMD_LOGIN_USER:
          {
            // Soh pode chegar comando de definicao de usuario em socket recem-criado
            cerr << "Tentativa de redefinicao de usuario no socket do cliente " << US2->getLogin() << ". Desconectando\n";
            US2->close();
            break;
          }
          case CMD_LOGIN_OK:
          case CMD_LOGIN_INVALIDO:
          case CMD_MSG_RECEBIDA:
          case CMD_MSG_ENTREGUE:
          case CMD_MSG_LIDA2:
          case CMD_ID_INVALIDA:
          case CMD_USER_INVALIDO:
          case CMD_MSG_INVALIDA:
          default:
          {
            // Comando invalido
            cerr << "Comando invalido (" << nome_cmd((ComandoWhatsProg)cmd) << ") recebido do cliente "
                 << US2->getLogin() << ". Desconectando\n";
            US2->close();
            break;
          }
          case CMD_NOVA_MSG:
          {
            Mensagem M;
            string destinatario;
            string texto;

            // Receber a msg
            iResult = US2->read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK)
            {
              iResult = US2->read_string(destinatario, TIMEOUT_WHATSPROG*1000);
            }
            if (iResult == mysocket_status::SOCK_OK)
            {
              iResult = US2->read_string(texto, TIMEOUT_WHATSPROG*1000);
            }
            if (iResult != mysocket_status::SOCK_OK)
            {
              // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
              if (iResult == mysocket_status::SOCK_ERROR)
              {
                cerr << "Erro na recepcao de parametros de CMD_NOVA_MSG do cliente "
                     << US2->getLogin() << ". Desconectando\n";
              }
              US2->close();
            }
            // Comeca a preencher os campos da mensagem recebida
            bool msg_valida = (M.setStatus(MsgStatus::MSG_RECEBIDA) && M.setRemetente(US2->getLogin()));
            // Testa se a id da msg estah correta
            if (msg_valida && US2->connected() &&
                (!M.setId(id) || (id <= US2->getLastId())))
            {
              cerr << "Mensagem com ID invalida " << id << " recebida do cliente "
                   << US2->getLogin() << ". Enviando cmd de erro\n";
              US2->write_int(CMD_ID_INVALIDA);
              US2->write_int(id);
              msg_valida = false;
            }
            // Testa se o texto da msg estah correto
            if (msg_valida && US2->connected() &&
                !M.setTexto(texto))
            {
              cerr << "Mensagem com texto invalido recebida do cliente "
                   << US2->getLogin() << ". Enviando cmd de erro\n";
              US2->write_int(CMD_MSG_INVALIDA);
              US2->write_int(id);
              msg_valida = false;
            }
            // Procura se o destinatario eh um usuario cadastrado
            US3 = find(Usuarios.begin(), Usuarios.end(), destinatario);

            if (msg_valida && US2->connected())
            {
              // Neste servidor fake, nao hah lista de usuarios cadastrados
              // Os unicos outros usuarios cadastrados sao "userfake1" e "userfake2"


              // Testa se o destinatario da msg estah correto
              if (US3 == Usuarios.end())
              {
                cerr << "Mensagem com destinatario invalido " << destinatario << " recebida do cliente "
                     << US2->getLogin() << ". Enviando cmd de erro\n";
                US2->write_int(CMD_USER_INVALIDO);
                US2->write_int(id);
                msg_valida = false;
              }
            }
            if (msg_valida && US2->connected())
            {
              // Mensagem valida
              imprimeComandoRecebido(US2->getLogin(), CMD_NOVA_MSG, id, destinatario);
              // Insere a mensagem no buffer
              // Este servidor fake nao tem um buffer de verdade
              // Apenas guarda, para simulacao, a ultima msg recebida
              // (do usuario para userfake1 e para userfake2)
              // No servidor real, a mensagem teria que ser inserida (push_back)
              // na lista de mensagens
              Mensagens.push_back(M);

              // Atualiza a ultima ID recebida
              US3->setLastId(id);
              // Envia a confirmacao de recebimento
              bool envioOK = (US3->write_int(CMD_MSG_RECEBIDA) == mysocket_status::SOCK_OK);
              if (envioOK) envioOK = (US3->write_int(id) == mysocket_status::SOCK_OK);
              if (!envioOK)
              {
                cerr << "Erro no envio de confirmacao de recebimento para remetente " << US3->getLogin() << ". Desconectando\n";
                US3->close();
              }
              else
              {
                imprimeComandoEnviado(US2->getLogin(), CMD_MSG_RECEBIDA, id);
              }
              // Testa se o destinatario estah conectado
              // Se sim, envia a mensagem e muda status para MSG_ENTREGUE

              /* **************************************************************************************
              ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
              para o servidor real, a nao ser que seja feita uma analise muito cuidadosa.
              A fonte que contem informacao correta sobre como implementar o servidor eh
              a especificacao. Alguns trechos de outros programas, como o servidor do mensageiro,
              podem servir de ideia ou inspiracao, embora ***CERTAMENTE*** precisem ser adaptados.
              ************************************************************************************** */
              // Neste servidor fake, userfake1 e userfake2 estao sempre conectados
              // e os envios para eles sempre dao certo...
              imprimeComandoEnviado(M.getDestinatario(), CMD_NOVA_MSG, M.getId(), M.getRemetente());
              // Mensagem enviada: atualiza status no "buffer"

              M.setStatus(MsgStatus::MSG_ENTREGUE);
              //doUsuario[ M.getDestinatario()=="userfake1" ? 0 : 1 ] = M;
              // Testa se o remetente estah conectado
              // Se sim, envia a confirmacao de entrega da mensagem
              if (US3->connected())
              {
                envioOK = (US2->write_int(CMD_MSG_ENTREGUE) != mysocket_status::SOCK_ERROR);
                if (envioOK) envioOK = (US2->write_int(M.getId()) != mysocket_status::SOCK_ERROR);
                if (!envioOK)
                {
                  cerr << "Erro no envio de confirmacao de entrega para remetente "
                       << US2->getLogin() << ". Desconectando\n";
                  US2->close();
                }
                else
                {
                  imprimeComandoEnviado(US2->getLogin(), CMD_MSG_ENTREGUE, M.getId(), "");
                }
              }
              /* Fim da parte que ***NAO*** pode ser adaptada para o servidor real ***************** */
            }
            break;
          } // Fim do case CMD_NOVA_MSG
          case CMD_MSG_LIDA1:
          {
            string remetente;

            // Receber os parametros do comando
            iResult = US2->read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult  == mysocket_status::SOCK_OK) iResult = US2->read_string(remetente, TIMEOUT_WHATSPROG*1000);
            if (iResult  != mysocket_status::SOCK_OK)
            {
              // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
              if (iResult == mysocket_status::SOCK_ERROR)
              {
                cerr << "Erro na recepcao de parametros de CMD_MSG_LIDA1 do cliente "
                     << US2->getLogin() << ". Desconectando\n";
              }
              US2->close();
            }
            if (US2->connected())
            {
              // Os parametros da confirmacao de visualizacao foram recebidos
              // Procura pelo remetente.
              // Neste servidor fake, o remetente eh sempre userfake1 ou userfake2
              // No servidor real, faria um find na lista de usuarios
              bool erro(false);
               USEREAD = find(Usuarios.begin(), Usuarios.end(), remetente);
              // Caso exista o remetente,
              // procura pela msg que estah sendo confirmada
              // Neste servidor fake, nao existe um buffer real de mensages
              // Apenas testa se a unica mensagem armazenada tem remetente e id corretos
              // No servidor real, faria um find na lista de mensagens
              ME = find(Mensagens.begin(), Mensagens.end(), testRemetId(remetente, USEREAD->getLastId()));

              if (!erro)
              {
                //int indice = (remetente=="userfake1" ? 0 : 1);
                erro = (USEREAD->getLogin() != remetente ||
                        ME->getId()!=id);
              }
              if (erro)
              {
                cerr << "CMD_MSG_LIDA1 de mensagem inexistente (" << id << "," << remetente
                     << ") recebida do cliente " << US2->getLogin() << ". Desconectando\n";
                US2->close();
              }

              // A msg confirmada existe no buffer
              imprimeComandoRecebido(US2->getLogin(), CMD_MSG_LIDA1, id, remetente);
              // Altera o status da msg no buffer
              // Neste servidor fake, nao existe um buffer real de mensages
              // No servidor real, a alteracao seria feita na mensagem que foi encontrada na lista
              //int indice = (remetente=="userfake1" ? 0 : 1);
              ME->setStatus(MsgStatus::MSG_LIDA);
              // Testa se o remetente estah conectado
              // Se sim, envia a confirmacao de visualizacao e remove a msg do buffer
              // Neste servidor fake, userfake1 e userfake2 estao sempre conectados
              // e os "envios" para eles sempre dao certo...
              if(USEREAD->connected())
              {
                  imprimeComandoEnviado(remetente, CMD_MSG_LIDA2, ME->getId());
                  Mensagens.erase(ME);
              }
          }
            break;
          } // Fim do case CMD_MSG_LIDA1
          case CMD_LOGOUT_USER:
          {
            imprimeComandoRecebido(US2->getLogin(), CMD_LOGOUT_USER);
            US2->close();
            break;
          } // Fim do case CMD_LOGOUT_USER
          } // Fim do switch
      }
      }
       // Fim do if (had_activity) no socket do cliente

      // Depois, testa se houve atividade no socket de conexao
      if (!fim && c.accepting() && f.had_activity(c))
      {
        tcp_mysocket t;
        string login, senha;

        // Aceita provisoriamente a nova conexao
        if (c.accept(t)!=mysocket_status::SOCK_OK)
        {
          cerr << "Não foi possível estabelecer uma conexao\n";
          t.close();
          // Encerra a thread do servidor
          fim = true;
        }
        // Leh o comando
        if (t.connected())
        {
          iResult = t.read_int(cmd, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
            cerr << "Erro na leitura do comando de conexao. Desconectando\n";
            t.close();
          }
        }
        // Testa o comando
        if (t.connected() &&
            (cmd!=CMD_LOGIN_USER && cmd!=CMD_NEW_USER))
        {
          cerr << "Comando (" << cmd << ") invalido. Desconectando\n";
          t.close();
        }
        // Leh o parametro com o login do usuario que deseja se conectar
        if (t.connected())
        {
          iResult = t.read_string(login, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            cerr << "Erro na leitura de login. Desconectando\n";
            t.close();
          }
        }
        // Leh o parametro com a senha do usuario que deseja se conectar
        if (t.connected())
        {
          iResult = t.read_string(senha, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            cerr << "Erro na leitura de senha. Desconectando\n";
            t.close();
          }
        }
        // Testa o login e senha
        if (t.connected() &&
            (!testarNomeUsuario(login) || !testarSenha(senha)))
        {
          cerr << "Login/senha (" << login << "/" << senha << ") invalido. Desconectando\n";
          t.write_int(CMD_LOGIN_INVALIDO);
          t.close();
        }
        // Testa se o usuario eh adequado
        if (t.connected())
        {
          NEWUSER = find(Usuarios.begin(), Usuarios.end(), login);
          Usuario NOVOUSER;

          /* **************************************************************************************
          ATENCAO: a parte a seguir da implementacao do servidor FAKE pode ser parcialmente adaptada
          para o servidor real, mas requer uma analise muito cuidadosa.
          A fonte que contem informacao correta sobre como implementar o servidor eh
          a especificacao. Alguns trechos de outros programas, como o servidor do mensageiro, tambem
          podem servir de ideia ou inspiracao, embora ***CERTAMENTE*** precisem ser adaptados.
          ************************************************************************************** */

          if (cmd == CMD_NEW_USER)
          {
            // Verifica se jah existe um usuario cadastrado com esse login



            if (login == NEWUSER->getLogin())
            {
              // Jah existe um usuario com esse login. Nao pode criar
              cerr << "Login (" << login << ") jah utilizado. Desconectando\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Este servidor fake soh pode ter um usuario cadastrado
            // Soh vai aceitar o novo usuario se ninguem estiver conectado
            if (NEWUSER->connected() && NEWUSER != Usuarios.end())
            {
              // Jah existe um usuario conectado. Nao pode criar
              cerr << "Usuario (" << NEWUSER->getLogin() << ") estah conectado no momento. Desconectando\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            if (t.connected())
            {
              // Insere novo usuario
              // Soh pode ter um usuario cadastrado
              // Portanto, ele vai sobrescrever um eventual usuario previamente cadastrado
              // Esse usuario anterior, caso tente futuramente se conectar com login jah
              // cadastrado, nao serah reconhecido

              // APENAS NO SERVIDOR FAKE:
              // Precisa apagar as msgs armazenadas pq podem ser de um outro usuario
              // que vai ser sobrescrito
              /*for (int i=0; i<2; i++)
              {
                paraUsuario[i] = Mensagem();
                doUsuario[i] = Mensagem();
              }*/


              if (NOVOUSER.setUsuario(login,senha))
              {
                NOVOUSER.resetId();
                NOVOUSER.swapSocket(t);
                Usuarios.push_back(NOVOUSER);
              }
              else
              {
                cerr << "Usuario (" << login << "/" << senha << ") e/ou socket invalidos. Desconectando\n";
                t.write_int(CMD_LOGIN_INVALIDO);
                t.close();
              }
            }
          }
          else  // else cmd == CMD_NEW_USER; implica cmd eh CMD_LOGIN_USER
          {
            if (login != NEWUSER->getLogin())
            {
              // Nao existe um usuario com esse login. Nao pode conectar
              cerr << "Login (" << login << ") nao existe. Desconectando\n";
              login = "invalido";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Testa se a senha confere
            if (t.connected() && !NEWUSER->validarSenha(senha))
            {
              // Senha invalida
              cerr << "Senha para usuario (" << login << ") nao confere. Desconectando\n";
              senha = "invalida";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Testa se o cliente jah estah conectado
            if (t.connected() && NEWUSER->connected())
            {
              // O usuario jah estah conectado
              cerr << "Usuario (" << login << ") jah estah conectado. Desconectando\n";
              login = "invalido";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Associa o socket que se conectou a um usuario cadastrado
            if (t.connected())
            {
              NEWUSER->swapSocket(t);
            }
          } // fim cmd eh CMD_LOGIN_USER
          /* Fim da parte que pode ser PARCIALMENTE adaptada para o servidor real ************** */

          // Envia a confirmacao de conexao
          if (login==NOVOUSER.getLogin() && NOVOUSER.connected())
          {
            imprimeComandoRecebido(login, (ComandoWhatsProg)cmd);
            bool envioOK = (NOVOUSER.write_int(CMD_LOGIN_OK) == mysocket_status::SOCK_OK);
            if (!envioOK)
            {
              cerr << "Erro no envio de confirmacao de login para cliente "
                   << NOVOUSER.getLogin() << ". Desconectando\n";
              NOVOUSER.close();
            }
            else
            {
              imprimeComandoEnviado(NOVOUSER.getLogin(), CMD_LOGIN_OK);
            }
          }
          if(login==NEWUSER->getLogin() && NEWUSER->connected())
          {
            imprimeComandoRecebido(login, (ComandoWhatsProg)cmd);
            bool envioOK = (NEWUSER->write_int(CMD_LOGIN_OK) == mysocket_status::SOCK_OK);
            if (!envioOK)
            {
              cerr << "Erro no envio de confirmacao de login para cliente "
                   << NEWUSER->getLogin() << ". Desconectando\n";
              NEWUSER->close();
            }
            else
            {
              imprimeComandoEnviado(NEWUSER->getLogin(), CMD_LOGIN_OK);
            }
          }
          // Se for um cliente antigo, envia para o cliente que se reconectou:
          // a) as mensagens enviadas para ele que estao no buffer
          // b) as confirmacoes de visualizacao para ele que estao no buffer
          if (login==NEWUSER->getLogin() && NEWUSER->connected())
          {
            // No servidor real, essas funcoes auxiliares teriam que receber como
            // parametro um iterador para o usuario que se conectou.

            // mensagens enviadas para ele que estao no buffer
            enviarMsg(*NEWUSER);
            // as confirmacoes de visualizacao para ele que estao no buffer
            //enviarConfirmacoesParaUsuario(*NEWUSER);
          }
        } // fim do teste se usuario eh adequado
      } // fim if (had_activity) no socket de conexoes
    } // Fim do teste se a espera por atividade foi mysocket_status::SOCK_OK
  } // Fim do while (!fim), laco principal da thread

  cout << "\nServidor encerrado.\n";

  return 0;
}

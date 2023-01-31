#include <iostream>
#include "Matriz.h"

using namespace std;

int main()
{
  Matriz A(3,3, 1.0), B, C;
  unsigned N;

  cout << "Matriz de 1's:\n";
  cout << A;

  cout << "Digite a dimensao (>0) da matriz quadrada a ser lida:\n";
  do
  {
    cout << "Linhas/colunas: ";
    cin >> N;
  } while (N==0);
  B.resize(N,N);
  cout << "Digite os elementos da matriz:\n";
  cin >> B;

  // Salvando a transposta da matriz digitada
  C = !B;  // Transposta
  if (C.salvar("teste.txt"))
  {
    cout << "Transposta salva com sucesso\n";
  }
  else
  {
    cerr << "Erro no salvamento da transposta\n";
  }

  // Alterando um elemento da matriz
  C.set(0,0, 3.1416);

  // Lendo a matriz transposta
  if (A.ler("teste.txt"))
  {
    cout << "Transposta lida com sucesso\n";
  }
  else
  {
    cerr << "Erro na leitura da transposta\n";
  }

  cout << "Matriz:\n";
  cout << B;
  cout << "Transposta:\n";
  cout << A;
  cout << "Transposta alterada:\n";
  cout << C;
  cout << "Soma da matriz com a transposta:\n";
  cout << A+B;

  return 0;
}

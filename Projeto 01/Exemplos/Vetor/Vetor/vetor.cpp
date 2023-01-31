#include <iostream>
#include <cmath>  // para sqrt

#include "vetor.h"

using namespace std;

/// Construtor default (obrigatorio jah que a classe envolve alocacao de memoria)
Vetor::Vetor(): N(0), x(nullptr) {}

/// Construtor por copia (obrigatorio jah que a classe envolve alocacao de memoria)
Vetor::Vetor(const Vetor& V): N(V.N), x(nullptr)
{
  if (N>0) x = new double[N];
  for (unsigned i=0; i<N; i++) x[i] = V.x[i];
}

/// Um construtor especifico, no qual o parametro de entrada indica
/// a dimensao do vetor
Vetor::Vetor(unsigned Num): N(Num), x(nullptr)
{
  if (N>0) x = new double[N];
  /// Inicializa todos os elementos com zero
  for (unsigned i=0; i<N; i++) x[i] = 0.0;
}

/// Destrutor (obrigatorio jah que a classe envolve alocacao de memoria)
Vetor::~Vetor()
{
  if (x!=nullptr) delete[] x;
}

/// Operador de atribuicao (obrigatorio jah que a classe envolve alocacao de memoria)
/// Retorna void, entao nao serah possivel fazer atribuicao multipla em uma linha (A=B=C;)
void Vetor::operator=(const Vetor& V)
{
  /// Primeiro, testa se o usuario nao estah fazendo uma atribuicao redundante, tal como A=A
  /// Soh faz alguma coisa se nao for esse tipo de situacao absurda
  if (this != &V)
  {
    /// Caso as dimensoes sejam diferentes, desaloca a area anterior e aloca uma nova area
    if (this->N != V.N)
    {
      if (x!=nullptr) delete[] x;
      N = V.N;
      if (N>0) x = new double[N];
      else x = nullptr;
    }
    /// Copia os valores dos elementos
    for (unsigned i=0; i<N; i++) x[i] = V.x[i];
  }
}

/// Metodo de consulta que retorna a dimensao do vetor
unsigned Vetor::size() const {return N;}

/// Metodo de consulta que retorna o valor de um elemento do vetor
double Vetor::operator[](unsigned i) const
{
  if (i>=N)
  {
    cerr << "Indice invalido\n";
    return 0.0;
  }
  return x[i];
}

/// Metodo de alteracao de valor de um elemento do vetor
void Vetor::set(unsigned i, double valor)
{
  if (i>=N)
  {
    cerr << "Indice invalido\n";
    return;
  }
  x[i]=valor;
}

/// Acrescenta um elemento ao final do vetor (aumenta de tamanho)
void Vetor::push_back(double valor)
{
  // Cria um vetor provisorio (Passo 1 do algoritmo classico: ver resumo sobre ponteiros)
  // Aloca uma nova area com N+1 elementos (Passo 2)
  double* prov = new double[N+1];
  // Copia todos os elementos da area antiga para nova (Passo 3)
  // Se N==0, nao entra nenhuma vez no for e nao copia nada
  for (unsigned i=0; i<N; i++) prov[i]=x[i];
  // Copia o novo valor para o final da area nova (Passo 4)
  prov[N]=valor;
  // Libera a area antiga (Passo 5)
  if (x!=nullptr) delete[] x;
  // Faz o ponteiro do vetor apontar para a nova area (Passo 6)
  x = prov;
  // Aumenta a dimensao do vetor (Passo 7)
  N++;
}

/// As funcoes que implementam os operadores de entrada e saida de dados
/// Como nao sao metodos da classe (sao funcoes) mas precisam acessar dados privados
/// da classe, sao declaradas como friend

ostream& operator<<(ostream& X, const Vetor& V)
{
  X << '[';
  for (unsigned i=0; i<V.N; i++)
  {
    X << V.x[i];
    if (i+1==V.N) X << ']';
    else X << ';';
  }
  return X;
}

istream& operator>>(istream& X, Vetor& V)
{
  for (unsigned i=0; i<V.N; i++) X >> V.x[i];
  return X;
}

/// Soma de vetores
Vetor Vetor::operator+(const Vetor& V) const
{
  if (N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return Vetor();
  }
  Vetor prov(N);
  for (unsigned i=0; i<N; i++) prov.x[i] = x[i] + V.x[i];
  return prov;
}

/// Subtracao de vetores (- binario)
Vetor Vetor::operator-(const Vetor& V) const
{
  if (N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return Vetor();
  }
  Vetor prov(N);
  for (unsigned i=0; i<N; i++) prov.x[i] = x[i] - V.x[i];
  return prov;
}

/// Negativo de um vetor (- unario)
Vetor Vetor::operator-() const
{
  Vetor prov(N);
  for (unsigned i=0; i<N; i++) prov.x[i] = -x[i];
  return prov;
}

/// Norma euclidiana de um vetor
double Vetor::norma() const
{
  double soma(0.0);
  for (unsigned i=0; i<N; i++) soma += x[i]*x[i];
  return sqrt(soma);
}

/// Produto escalar
double Vetor::escalar(const Vetor& V) const
{
  if (N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return 0.0;
  }
  double prov(0.0);
  for (unsigned i=0; i<N; i++) prov += x[i]*V.x[i];
  return prov;
}

/// Produto vetorial (apenas para vetores de dimensao 3)
Vetor Vetor::vetorial(const Vetor& V) const
{
  if (N!=3 || N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return Vetor();
  }
  Vetor prov(3);
  prov.x[0] = x[1]*V.x[2] - x[2]*V.x[1];
  prov.x[1] = x[2]*V.x[0] - x[0]*V.x[2];
  prov.x[2] = x[0]*V.x[1] - x[1]*V.x[0];
  return prov;
}

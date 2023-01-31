#include <fstream> // Para leitura/escrita em arquivo
#include <string>
#include "Matriz.h"

using namespace std;

/// Construtor default (obrigatorio jah que a classe envolve alocacao de memoria)
Matriz::Matriz(): NL(0), NC(0), x(nullptr) {}

/// Construtor por copia (obrigatorio jah que a classe envolve alocacao de memoria)
Matriz::Matriz(const Matriz& N): NL(N.NL), NC(N.NC), x(nullptr)
{
  // Aloca o vetor de linhas
  x = new double*[NL];

  // Aloca as linhas
  for (unsigned i=0; i<NL; i++) x[i] = new double[NC];

  // Copia os elementos
  for (unsigned i=0; i<NL; i++)
  {
    for (unsigned j=0; j<NC; j++) x[i][j] = N.x[i][j];
  }
}

/// Um construtor especifico,
/// no qual os parametros de entrada indicam a dimensao da matriz
Matriz::Matriz(unsigned numL, unsigned numC, double valor_inicial):
  NL(numL), NC(numC), x(nullptr)
{
  if (numL==0 || numC==0)
  {
    NL = NC = 0;
    return;
  }

  // Aloca o vetor de linhas
  x = new double*[NL];

  // Aloca as linhas e atribui valor inicial
  for (unsigned i=0; i<NL; i++)
  {
    x[i] = new double[NC];
    for (unsigned j=0; j<NC; j++) x[i][j] = valor_inicial;
  }
}

/// Destrutor (obrigatorio jah que a classe envolve alocacao de memoria)
Matriz::~Matriz()
{
  if (x!=nullptr)
  {
    // Libera as linhas
    for (unsigned i=0; i<NL; i++) if (x[i]!=nullptr) delete[] x[i];

    // Libera o vetor de linhas
    delete[] x;
  }
}

/// Operador de atribuicao (obrigatorio jah que a classe envolve alocacao de memoria)
/// Retorna void, entao nao serah possivel fazer atribuicao multipla em uma linha (A=B=C;)
void Matriz::operator=(const Matriz& N)
{
  // Inicialmente, testa se nao estah fazendo A=A
  // Soh faz alguma coisa se nao for isso
  if (this!=&N)
  {
    // Altera a dimensao da matriz que estah sendo atribuida (this)
    // A funcao resize soh faz nova alocacao se a dimensao desejada for diferente da atual
    resize(N.NL,N.NC);

    // Copia o valor dos elementos
    for (unsigned i=0; i<NL; i++)
    {
      for (unsigned j=0; j<NC; j++) x[i][j] = N.x[i][j];
    }
  }
}

/// Metodos de consulta que retornam as dimensoes da matriz
unsigned Matriz::getNumL(void) const
{
  return NL;
}

unsigned Matriz::getNumC(void) const
{
  return NC;
}

/// Metodo de consulta que retorna o valor de um elemento da matriz
/// Este metodo eh chamado no lado direito de uma operacao
/// Por exemplo, y = x.at(2,3) ou cout << x.at(2,3)
/// Nao foi sobrecarregado o operador[] que eh normalmente utilizado
/// para indices porque ele soh permite um unico parametro
double Matriz::at(unsigned i, unsigned j) const
{
  if (i>=NL || j>=NC)
  {
    cerr << "Indices incompativeis\n";
    return 0.0;
  }
  return x[i][j];
}

/// Metodo de alteracao do tamanho (redimensionamento) de uma matriz existente
/// ATENCAO: lembrar que essa funcao nao pode ser utilizada em nenhum construtor,
/// pois tenta liberar a memoria anterior que nao existe em uma matriz sendo criada
void Matriz::resize(unsigned numL, unsigned numC)
{
  // Soh faz alguma coisa se a dimensao atual nao for igual aa desejada
  // Se jah for igual, nao faz nada
  if (NL!=numL || NC!=numC)
  {
    // As dimensoes sao diferentes
    // Libera a area antiga e aloca nova area com a dimensao desejada
    if (x!=nullptr)
    {
      // Libera as linhas
      for (unsigned i=0; i<NL; i++) if (x[i]!=nullptr) delete[] x[i];
      // Libera o vetor de linhas
      delete[] x;
    }
    // Fixa as dimensoes iguais aas dimensoes desejadas
    NL = numL;
    NC = numC;

    // Aloca o vetor de linhas
    x = new double*[NL];
    // Aloca as linhas
    for (unsigned i=0; i<NL; i++) x[i] = new double[NC];
  }
}

/// Metodo de alteracao de valor de um elemento da matriz
void Matriz::set(unsigned i, unsigned j, double valor)
{
  if (i>=NL || j>=NC)
  {
    cerr << "Indices incompativeis\n";
    return;
  }
  x[i][j] = valor;
}

/// A funcao friend que implementa o operador de saida de dados
ostream& operator<<(ostream& X, const Matriz& N)
{
  if (N.NL==0 || N.NC==0)
  {
    // Nao hah nada a imprimir
    return X;
  }
  for (unsigned i=0; i<N.NL; i++)
  {
    for (unsigned j=0; j<N.NC; j++)
    {
      // Imprime um espaco separador entre elementos
      if (j!=0) X << ' ';
      // Imprime o valor do elemento
      X << N.x[i][j];
    }
    X << endl;
  }
  return X;
}

/// A funcao friend que implementa o operador de entrada de dados
istream& operator>>(istream& X, Matriz& N)
{
  if (N.NL==0 || N.NC==0)
  {
    cerr << "Matriz de dimensao nula\n";
    return X;
  }
  for (unsigned i=0; i<N.NL; i++)
  {
    for (unsigned j=0; j<N.NC; j++)
    {
      X >> N.x[i][j];
    }
  }
  return X;
}

/// Leitura de uma matriz de arquivo
/// Recebe como parametro o nome do arquivo
/// Retorna true se a leitura ocorreu sem problema, false em caso de erro
bool Matriz::ler(string nome_arq)
{
  // Construtor da classe ifstream nao aceita como parametro uma string
  // Requer um array de char, a "string" antiga de C (nao a string C++)
  // Usando a funcao membro c_str() da classe string que retorna o array
  // de char com mesmo conteudo da string
  ifstream arq(nome_arq.c_str());
  if (!arq.is_open()) return false;

  // Leh o cabecalho inicial
  // Como eh uma palavra sem espaco, pode ser lida com >>
  // Nao precisa de getline, ws, ignore, etc.
  string cabecalho;
  arq >> cabecalho;
  if (!arq.good() || cabecalho!="MATRIZ")
  {
    arq.close();
    return false;
  }

  // Leh as dimensoes
  unsigned numL, numC;
  arq >> numL >> numC;
  if (!arq.good() || numL==0 || numC==0)
  {
    arq.close();
    return false;
  }

  // Redimensiona a matriz
  resize(numL, numC);

  // Leh os elementos
  // NL e NC de this jah estao com novos valores corretos apos o resize
  for (unsigned i=0; i<NL; i++)
  {
    for (unsigned j=0; j<NC; j++)
    {
      arq >> x[i][j];
      if (!arq.good())
      {
        arq.close();
        return false;
      }
    }
  }

  arq.close();
  return true;
}

/// Escrita de uma matriz em arquivo
/// Recebe como parametro o nome do arquivo
/// Retorna true se a escrita ocorreu sem problema, false em caso de erro
bool Matriz::salvar(string nome_arq)
{
  // Construtor da classe ofstream nao aceita como parametro uma string
  // Requer um array de char, a "string" antiga de C (nao a string C++)
  // Usando a funcao membro c_str() da classe string que retorna o array
  // de char com mesmo conteudo da string
  ofstream arq(nome_arq.c_str());
  if (!arq.is_open()) return false;

  arq << "MATRIZ " << NL << ' ' << NC << endl;
  for (unsigned i=0; i<NL; i++)
  {
    for (unsigned j=0; j<NC; j++)
    {
      if (j!=0) arq << ' ';
      arq << x[i][j];
    }
    arq << endl;
  }

  arq.close();
  return true;
}

/// Soma de matrizes
Matriz Matriz::operator+(const Matriz& N) const
{
  if (NL != N.NL || NC != N.NC || NL==0 || NC==0)
  {
    cerr << "Matrizes de dimensao incompativeis ou nulas\n";
    return Matriz();
  }
  Matriz prov(NL,NC);
  for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
    {
      prov.x[i][j] = this->x[i][j] + N.x[i][j];
    }
  return prov;
}

/// Subtracao de matrizes
Matriz Matriz::operator-(const Matriz& N) const
{
  if (NL != N.NL || NC != N.NC || NL==0 || NC==0)
  {
    cerr << "Matrizes de dimensao incompativeis ou nulas\n";
    return Matriz();
  }
  Matriz prov(NL,NC);
  for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
      prov.x[i][j] = this->x[i][j] - N.x[i][j];
  return prov;
}

/// Negativa de uma matriz
Matriz Matriz::operator-() const
{
  if (NL==0 || NC==0)
  {
    cerr << "Matriz de dimensao nula\n";
    return Matriz();
  }
  Matriz prov(NL,NC);
  for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
      prov.x[i][j] = - x[i][j];
  return prov;
}

/// Produto de matrizes
Matriz Matriz::operator*(const Matriz& N) const
{
  if (NC != N.NL || NL==0 || NC==0 || N.NC==0)
  {
    cerr << "Matrizes de dimensao incompativeis ou nulas\n";
    return Matriz();
  }
  Matriz prov(NL,N.NC);
  for (unsigned i=0; i<prov.NL; i++) for (unsigned j=0; j<prov.NC; j++)
    {
      prov.x[i][j] = 0.0;
      for (unsigned k=0; k<NC; k++) prov.x[i][j] += x[i][k]*N.x[k][j];
    }
  return prov;
}

/// Transposta de uma matriz
Matriz Matriz::operator!(void) const
{
  if (NL==0 || NC==0)
  {
    cerr << "Matriz de dimensao nula\n";
    return Matriz();
  }
  Matriz prov(NC,NL);
  for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
      prov.x[j][i] = x[i][j];
  return prov;

}

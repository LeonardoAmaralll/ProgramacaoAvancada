#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <iostream>

class Matriz
{
private:
  /// As dimensoes da matriz (sempre >= 0, por isso unsigned int)
  unsigned NL, NC;
  /// O ponteiro para o array de ponteiros para elementos
  double* *x;

public:
  /// Construtor default (obrigatorio jah que a classe envolve alocacao de memoria)
  Matriz();
  /// Construtor por copia (obrigatorio jah que a classe envolve alocacao de memoria)
  Matriz(const Matriz& N);
  /// Um construtor especifico,
  /// no qual os parametros de entrada indicam a dimensao da matriz
  Matriz(unsigned numL, unsigned numC, double valor_inicial=0.0);

  /// Destrutor (obrigatorio jah que a classe envolve alocacao de memoria)
  ~Matriz();

  /// Operador de atribuicao (obrigatorio jah que a classe envolve alocacao de memoria)
  /// Retorna void, entao nao serah possivel fazer atribuicao multipla em uma linha (A=B=C;)
  void operator=(const Matriz& N);

  /// Metodos de consulta que retornam as dimensoes da matriz
  unsigned getNumL(void) const;
  unsigned getNumC(void) const;

  /// Metodo de consulta que retorna o valor de um elemento da matriz
  /// Nao foi sobrecarregado o operador[] que eh normalmente utilizado
  /// para indices porque ele soh permite um unico parametro
  double at(unsigned i, unsigned j) const;

  /// Metodo de alteracao do tamanho (redimensionamento) de uma matriz existente
  /// ATENCAO: lembrar que essa funcao nao pode ser utilizada em nenhum construtor,
  /// pois tenta liberar a memoria anterior que nao existe em uma matriz sendo criada
  void resize(unsigned numL, unsigned numC);

  /// Metodo de alteracao de valor de um elemento da matriz
  void set(unsigned i, unsigned j, double valor);

  /// As funcoes que implementam os operadores de entrada e saida de dados
  /// Como nao sao metodos da classe (sao funcoes) mas precisam acessar dados privados
  /// da classe, sao declaradas como friend
  friend std::ostream& operator<<(std::ostream& X, const Matriz& N);
  friend std::istream& operator>>(std::istream& X, Matriz& N);

  /// Leitura de uma matriz de arquivo
  /// Recebe como parametro o nome do arquivo
  /// Retorna true se a leitura ocorreu sem problema, false em caso de erro
  bool ler(std::string nome_arq);

  /// Escrita de uma matriz em arquivo
  /// Recebe como parametro o nome do arquivo
  /// Retorna true se a escrita ocorreu sem problema, false em caso de erro
  bool salvar(std::string nome_arq);

  /// Operadores algebricos
  Matriz operator+(const Matriz& N) const;
  Matriz operator-(const Matriz& N) const;
  Matriz operator-() const;
  Matriz operator*(const Matriz& N) const;

  /// Operacoes matriciais
  Matriz operator!(void) const;  // Transposta
};

#endif // _MATRIZ_H_

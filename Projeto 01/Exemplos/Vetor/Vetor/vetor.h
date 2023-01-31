#ifndef _VETOR_H_
#define _VETOR_H_

#include <iostream>

class Vetor
{
private:
  /// A dimensao do vetor (sempre >= 0)
  unsigned N;
  /// O ponteiro que aponta para os elementos do vetor
  double *x;

public:
  /// Construtor default (obrigatorio jah que a classe envolve alocacao de memoria)
  Vetor();
  /// Construtor por copia (obrigatorio jah que a classe envolve alocacao de memoria)
  Vetor(const Vetor& V);
  /// Um construtor especifico, no qual o parametro de entrada indica a dimensao do vetor
  /// Esse construtor NAO deve ser usado como conversor de unsigned -> Vetor, pois seria incorreto
  /// Por isso, foi declarado como explicit
  explicit Vetor(unsigned Num);

  /// Destrutor (obrigatorio jah que a classe envolve alocacao de memoria)
  ~Vetor();
  /// Operador de atribuicao (obrigatorio jah que a classe envolve alocacao de memoria)
  /// Retorna void, entao nao serah possivel fazer atribuicao multipla em uma linha (A=B=C;)
  void operator=(const Vetor& V);

  /// Metodo de consulta que retorna a dimensao do vetor
  unsigned size() const;
  /// Metodo de consulta que retorna o valor de um elemento do vetor
  double operator[](unsigned i) const;
  /// Metodo de alteracao de valor de um elemento do vetor
  void set(unsigned i, double valor);
  /// Acrescenta um elemento ao final do vetor (aumenta de tamanho)
  void push_back(double valor);

  /// As funcoes que implementam os operadores de entrada e saida de dados
  /// Como nao sao metodos da classe (sao funcoes) mas precisam acessar dados privados
  /// da classe, sao declaradas como friend
  friend std::ostream& operator<<(std::ostream& X, const Vetor& V);
  friend std::istream& operator>>(std::istream& X, Vetor& V);

  /// Soma de vetores
  Vetor operator+(const Vetor& V) const;
  /// Subtracao de vetores (- binario)
  Vetor operator-(const Vetor& V) const;
  /// Negativo de um vetor (- unario)
  Vetor operator-() const;

  /// Norma euclidiana de um vetor
  double norma() const;
  /// Produto escalar
  double escalar(const Vetor& V) const;
  /// Produto vetorial (apenas para vetores de dimensao 3)
  Vetor vetorial(const Vetor& V) const;
};

#endif

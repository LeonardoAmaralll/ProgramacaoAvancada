#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>


class Poly
{
private:
    unsigned D;
    double *a;

public:
    ///Construtores
    Poly();
    Poly(const Poly& P);
    explicit Poly(unsigned n);

    ///Destrutor
    ~Poly();

    ///Métodos
    void recriar(unsigned m);
    bool empty() const;
    bool isZero() const;
    int getGrau() const;
    double getCoef(const unsigned i) const;
    double getValor(const double x);
    void setCoef(const unsigned i, const double c);
    bool salvar(std::string nome_arq);
    bool ler(std::string nome_arq);

    ///Sobrecarga de Operadores
    double operator()(const double x);
    double operator[](const unsigned i);

    void operator=(const Poly& P);
    Poly operator+(const Poly& P) const;
    Poly operator-(const Poly& P) const;
    Poly operator-() const;
    Poly operator*(const Poly& P) const;

    friend std::ostream& operator<<(std::ostream& X, const Poly& P);
    friend std::istream& operator>>(std::istream& X, Poly& P);
};
#endif
///UNSIGNED EM FOR DE I--, CONVERSOES E UTILIZAÇÃO DE GRAU OU DIMENSAO;

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
    poly(const Poly& P);
    *///explicit Poly(unsigned n);

    ///Destrutor
    ~Poly();

    ///Métodos
    void recriar(unsigned m);
    bool empty();
    bool isZero();
    int getGrau();
    double getCoef(unsigned i);
    double getValor(double x);
    void setCoef(unsigned i, double c);
    bool salvar(std::string nome_arq);
    bool ler(std::string nome_arq);

    ///Sobrecarga de Operadores
    double operator()(Poly::getValor(double x) const);
    double operator[](Poly::getCoef(unsigned i) const);

    void operator=(const Poly& P);
    Poly operator+(const Poly& P) const;
    Poly operator-(const Poly& P) const;
    Poly operator-() const;
    Poly operator*(const Poly& P) const;

    friend std::ostream& operator<<(std::ostream& x, const Poly& P);
    friend std::istream& operator<<(std::istream& x, Poly& P);
};
#endif
///OBS: APÓS FINALIZAR, ANALISAR O QUE DEVE SER CONST OU EXPLICIT.

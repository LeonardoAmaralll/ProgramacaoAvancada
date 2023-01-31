#include <iostream>
#include <cmath>
#include "Poly.h"

using namespace std;

///Construtor Default
Poly::Poly() : D(0), a(nullptr){}

///Construtor por cópia
Poly::Poly(const Poly& P) : D(P.D), a(nullptr)
{
    if (D>0) a = new double[D];
    for (unsigned i=0; i<D); i++) a[i] = P.a[i];

}

///Construtor Específico
Poly::Poly(unsigned g) : D(g+1), a(nullptr)
{
    if (g>0)
    {
        a = new double[D];
        for (unsigned i=0; i<g; i++) a[i] = 0.0;
        a[g] = 1.0;
    }
    else if (g == 0)
    {
        a = new double[1];
        a[0] = 0.0;
    }
}

///Destrutor
Poly::~Poly()
{
    if (a!=nullptr) delete[] a;
}

///Métodos
void Poly::recriar(unsigned g)
{
   if (g != getGrau() && g >= 0)
   {
       if (a != nullptr) delete[] a;
       if (g > 0)
       {
            D = g+1;
            a = new double[D];
            for (unsigned i=0; i<g; i++) a[i] = 0.0;
            a[g] = 1.0;
       }
        else if (g == 0)
        {
            a = new double[1];
            a[0] = 0.0;
        }
   }
}

bool Poly::empty()
{
    if (D == 0) return true;

    return false;
}

bool Poly::isZero()
{
    if (D == 1 && a[0] == 0) return true;

    return false;
}

int Poly::getGrau() const
{
    return int(D)-1;
}

double Poly::getCoef(unsigned i)
{
    if (i <= getGrau()) return a[i];

    return 0.0;
}

double Poly::getValor(double x)
{
    double aux;
    if (empty == true) return 0.0;

    for(int i = 0; i<getGrau(); i++) aux = (pow(x,i) * getCoef(i)) + aux;
    return aux;

}

void Poly::setCoef(unsigned i, double c)
{
    if ( i <= getGrau() )
    {
        if( (getGrau() == 0 && a[0] == 0.0) || (getGrau() > 0 && a[getGrau()] != 0.0) ) a[i] = c;
    }
    else cerr <<"Operacao Inválida"<<endl;
}

bool Poly::salvar(std::string nome_arq)
{
    ofstream arq(nome_arq.c_str());
    if (!arq.is_open()) return false;

    arq << "POLY " << D << endl;

    if (D > 0)
    {
        for (unsigned i=0; i<getGrau(); i++)
        {
            if (i!=0) arq << ' ';
            arq << a[i];
        }
    arq << endl;
    }



    arq.close();
    return true;
}

 bool Poly::ler(std::string nome_arq)
 {
    ifstream arq(nome_arq.c_str());
    if (!arq.is_open()) return false;

    string cabecalho;
    unsigned dim;
    unsigned c(0);
    arq >> cabecalho;
    if (!arq.good() || cabecalho!="POLY" )
    {
        arq.close();
        return false;
    }
    arq >> dim;
    if (!arq.good() || dim != D)
    {
        arq.close();
        return false;
    }
    for (unsigned i=0; i<getGrau(); i++)
    {
      arq >> a[i];
      c++;
      if (!arq.good())
      {
        arq.close();
        return false;
      }
    }
    if (c < D || a[getGrau()] == 0.0)
    {
        arq.close();
        return false;
    }
    arq.close();
    return true;
}

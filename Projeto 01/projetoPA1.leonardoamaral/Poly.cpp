#include <iostream>
#include <cmath>
#include <fstream>
#include "Poly.h"

using namespace std;

///Construtor Default
Poly::Poly() : D(0), a(nullptr){}

///Construtor por cópia
Poly::Poly(const Poly& P) : D(P.D), a(nullptr)
{
    if (D>0) a = new double[D];
    for (unsigned i=0; i<D; i++) a[i] = P.a[i];

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
    else
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
    if (int(g) == getGrau() && g <= 0)
    {
        do{
            cerr <<"Grau invalido"<< endl;
            cout << "Grau do polinomio: "  ;
            cin >> g;
        }while(int(g) == getGrau());
    }
    else
    {
        if (a != nullptr) delete[] a;
            if (g > 0)
            {
                D = g+1;
                a = new double[D];
                for (unsigned i=0; i<g; i++) a[i] = 0.0;
                a[g] = 1.0;
            }
            if (g == 0)
            {
                D = 1;
                a = new double[1];
                a[0] = 0.0;
            }
    }
}

bool Poly::empty() const
{
    if (D == 0) return true;

    return false;
}

bool Poly::isZero() const
{
    if (D == 1 && a[0] == 0) return true;

    return false;
}

int Poly::getGrau() const
{
    return int(D)-1;
}

double Poly::getCoef(unsigned i) const
{
    if (int(i) <= getGrau()) return a[i];

    return 0.0;
}

double Poly::getValor(double x)
{
    double aux;
    if (empty() == true) return 0.0;

    for(unsigned i = 0; i<D; i++) aux += (pow(x,i) * a[i]);
    return aux;

}

void Poly::setCoef(unsigned i, double c)
{
    if ( int(i) <= getGrau() )
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
        for (unsigned i=0; i<D; i++)
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
    double* aa;
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
    aa = new double[dim];
    for (unsigned i=0; i<dim; i++)
    {
      arq >> aa[i];
      c++;
      if (!arq.good())
      {
        arq.close();
        return false;
      }
    }
    if (c < dim || aa[getGrau()] == 0.0)
    {
        arq.close();
        return false;
    }
    D = dim;
    for(unsigned i = 0; i < D; i++) a[i] = aa[i];
    arq.close();
    return true;
}

///Sobrecarga de Operadores

double Poly::operator()(const double x )
{
    return getValor(x);
}

double Poly::operator[](const unsigned i)
{
    return getCoef(i);
}

void Poly::operator=(const Poly& P)
{
    if (this != &P)
    {
        if (this->D != P.D)
        {
            if (a!=nullptr) delete[] a;
            D = P.D;
            if (D>0) a = new double[D];
            else a = nullptr;
        }
        for (unsigned i=0; i<D; i++) a[i] = P.a[i];
    }
}

Poly Poly::operator+(const Poly& P) const
{
    if (empty() == true || isZero() == true) return P;
    if (P.empty() == true || P.isZero() == true) return *this;

    Poly prov( max(getGrau(),P.getGrau()) );
    int cont(0);



    for (unsigned i=0; i<prov.D; i++) prov.a[i] = a[i] + P.a[i];
    for (int i=prov.getGrau(); i>=0; i--)
    {
        if(prov.a[i] == 0.0) cont++;
        else break;
    }
    if(cont > 0)
    {
        Poly prov2(getGrau()-cont);
        if(prov.getGrau() - cont > 0)
        {
            for (int i=0; i<int(prov2.D); i++) prov2.a[i] = prov.a[i];
        }
        else if(prov.getGrau() - cont == 0)
        {
            prov2.a[0] = prov.a[0];
        }
        return prov2;
    }
    return prov;
}



Poly Poly::operator-(const Poly& P) const
{
    if (empty() == true || isZero() == true) return -P;
    if (P.empty() == true || P.isZero() == true) return *this;

    Poly prov( max(getGrau(),P.getGrau()) );
    int cont(0);



    for (unsigned i=0; i<prov.D; i++) prov.a[i] = a[i] - P.a[i];
    for (int i=prov.getGrau(); i>=0; i--)
    {
        if(prov.a[i] == 0.0) cont++;
        else break;
    }
    if(cont > 0)
    {
        Poly prov2(getGrau()-cont);
        if(prov.getGrau() - cont > 0)
        {
            for (int i=0; i<prov2.getGrau(); i++) prov2.a[i] = prov.a[i];
            prov2.a[prov2.getGrau()] = prov.a[prov2.getGrau()] * prov2.a[prov2.getGrau()];
        }
        else if(prov.getGrau() - cont == 0)
        {
            prov2.a[0] = prov.a[0];
        }
        return prov2;
    }
    return prov;
}

Poly Poly::operator-() const
{
    Poly prov(getGrau());
    for (unsigned i=0; i<D; i++) prov.a[i] = -a[i];
    return prov;
}

Poly Poly::operator*(const Poly& P) const
{
    if (empty() == true || P.empty() == true) return Poly();
    if ( (isZero() == true || P.isZero() == true) && (empty() != true || P.empty() != true) ) return Poly(0);

    int cont(getGrau()+P.getGrau());
    Poly prov(getGrau()+P.getGrau());
    prov.a[getGrau()+P.getGrau()] = 0.0;
    for(int i=getGrau(); i>=0; i--)
    {
        for(int j=P.getGrau(); j >= 0; j--)
        {
            prov.a[cont] += a[i] * P.a[j];
            if (cont>=0) cont--;
        }
    }

    return prov;
}

ostream& operator<<(ostream& X, const Poly& P)
{
    if (P.empty()) return X;

    for(int i=P.getGrau(); i>=0; i--)
    {
        if(P.a[i] != 0)
        {
            if (i >= 0)
            {
                if(P.a[i] < 0) X << "-";
            }
            if ((P.a[i] != 1.0 && P.a[i] != -1.0) || i == 0)X << abs(P.a[i]);
            if (i > 1 && P.a[i] != 1.0 && P.a[i] != -1.0) X <<"*x^"<<i;
            if ((i > 1 && P.a[i] == 1.0) || (i > 1 && P.a[i] == -1.0)) X <<"x^"<<i;
            if (i == 1 && P.a[i] != 1.0 && P.a[i] != -1.0) X << "*x";
            if ((i == 1 && P.a[i] == 1.0) || (i == 1 && P.a[i] == -1.0)) X << "x";
            if (i > 0 && P.a[i-1] != 0.0 ) X <<"+";
        }
    }
    return X;
}

istream& operator>>(istream& X, Poly& P)
{
    if (P.empty() == true)
    {
        cout << "Vazio" << endl;
        return X;
    }
    for(int i = P.getGrau(); i >= 0; i--)
    {
        if((i == P.getGrau()) && P.getGrau() > 0)
        {
            do
            {
                cout << "Valor de x^" <<i<<":";
                X >> P.a[P.getGrau()];
            }while(P.a[P.getGrau()] == 0.0);
        }
        else
        {
            cout << "Valor de x^" <<i<<":";
            X >> P.a[i];
        }
    }
    return X;
}

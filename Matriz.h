#ifndef MATRIZ_H
#define MATRIZ_H
#include <QString> //inclue String do QT

namespace TP2{

class Matriz{
private:
    int quantLinhas;
    int quantColunas;
    int *ptrMatriz; //ponteiro da matriz
public:
    Matriz(int l, int c);
    ~Matriz(){if (ptrMatriz) delete [] ptrMatriz;} //se o ponteiro da matriz foi criado, então ele é apagado
    int getQuantLinhas()const{return quantLinhas;}
    int getQuantColunas()const{return quantColunas;}
    int getElemento(int l, int c) const; //pegar o elemento da matriz
    void setElemento(int l, int c, int e); // preencher a matriz
    QString getMatriz() const; //imprime a matriz
    Matriz* operator +(Matriz const * const mat); //sobrecarga do operador de soma
    Matriz* operator -(Matriz const * const mat); //sobrecarga do operador de subtração
    Matriz* operator *(Matriz const * const mat); //sobrecarga do operador de multiplicação
    Matriz* calcularTransposta() const ; //faz a matriz transposta
    bool triangularSuperior() const;
    bool triangularInferior() const;
    bool simetrica() const;
    bool permutacao() const;
    bool identidade() const;
    Matriz* multiplicar(int k)const; //multiplica a matriz por uma constante
    bool operator ==(Matriz const * const mat); //sobrecarga do operador de igualdade
    bool operator !=(Matriz const * const mat); //sobrecarga do operador de diferença
    bool ortogonal () const;
    Matriz* operator^(int x)const; //sobrecarga do operador de potenciação
};

}//Fim TP2

#endif // MATRIZ_H

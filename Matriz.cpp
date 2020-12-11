#include "Matriz.h"

namespace TP2{

Matriz::Matriz(int l ,int c): //construtor zera todos os elementos do metodo
    quantLinhas(0),
    quantColunas(0),
    ptrMatriz(0)
{
    if (l <= 0) throw QString ("Quantidade de linhas deve superior a zero"); //tratamento de exceção para verificar se os valores digitados para linha são validos
    if (c <= 0) throw QString ("Quantidade de colunas deve superior a zero"); //tratamento de exceção para verificar se os valores digitados para coluna são valido
    try{
        ptrMatriz = new int[l*c]; //cria um ponteiro para matriz com o tamanho da matriz criada
    }
    catch(std::bad_alloc&){
        throw QString("Memória insuficiente"); //trata a exceção da memoria estar cheia, justamente por mexer com ponteiros
    }
    quantLinhas = l;
    quantColunas = c;
}

int Matriz::getElemento(int l, int c) const{
    if((l<0)||(l>=quantLinhas)){
        throw QString ("Linha fora do intervalo valido1");
    }
    if((c<0)||(c>=quantColunas)){
        throw QString ("Coluna fora do intervalo valido1");
    }
    int pos = l*quantColunas+c;
    return *(ptrMatriz+pos);
}

void Matriz::setElemento(int l, int c, int e){
    if((l<0)||(l>=quantLinhas)){
        throw QString ("Linha fora do intervalo valido2");
    }
    if((c<0)||(c>=quantColunas)){
        throw QString ("Coluna fora do intervalo valido2");
    }
    int pos = l*quantColunas+c;
    *(ptrMatriz+pos) = e;
}

Matriz* Matriz::operator +(Matriz const * const mat){
    if( quantLinhas  != mat->getQuantLinhas() || quantColunas != mat->getQuantColunas()){
        throw QString("Nao pode ser adicionadas matriz de tamanhos diferentes");
    }

    try{
        Matriz *aux = new Matriz(quantLinhas,quantColunas);
        for(int i=0; i<quantLinhas; i++){
            for(int j=0; j<quantColunas; j++){
                int valor = this->getElemento(i,j) + mat->getElemento(i,j);
                aux->setElemento(i,j,valor);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória insuficiente");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos adicionar as matrizes");
    }
}

Matriz* Matriz::operator -(Matriz const * const mat){
    if( quantLinhas  != mat->getQuantLinhas() || quantColunas != mat->getQuantColunas()){
        throw QString("Nao pode ser subtraídas matriz de tamanhos diferentes");
    }

    try{
        Matriz *aux = new Matriz(quantLinhas,quantColunas);
        for(int i=0; i<quantLinhas; i++){
            for(int j=0; j<quantColunas; j++){
                int valor = this->getElemento(i,j) - mat->getElemento(i,j);
                aux->setElemento(i,j,valor);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória insuficiente");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos subtrair as matrizes");
    }
}

Matriz* Matriz::operator *(Matriz const * const mat){
    if(this->quantColunas!= mat->getQuantLinhas()){
        throw QString("Nao pode ser multiplicadas matriz com linhas e colunas diferentes");
    }

    try{
        Matriz *aux = new Matriz(this->quantLinhas,mat->quantColunas);
        int valor = 0;
        for(int i=0; i<quantLinhas; i++){
            for(int j=0; j<mat->quantColunas; j++){
                for (int k=0; k < mat->quantLinhas; k++){
                    valor+= this->getElemento(i,k) * mat->getElemento(k, j);
                    aux->setElemento(i,j,valor);
                }
                valor = 0;
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória insuficiente");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos multiplicar as matrizes");
    }

}
QString Matriz::getMatriz() const{
    QString saida = "";
    for (int i=0; i < quantLinhas; i++){
        for (int j=0; j < quantColunas;j++){
            saida += QString::number(getElemento(i,j));
            saida += " ";
        }
        saida += "\n";
    }
    return saida;
}

Matriz* Matriz::calcularTransposta() const {
    try{
    Matriz *aux = new Matriz(this->quantColunas,this->quantLinhas);
    int valor;
    for(int i=0; i<quantLinhas; i++) {
       for(int j=0; j<quantColunas; j++) {
           valor = getElemento(i,j);
           aux->setElemento(j,i,this->getElemento(i,j));
       }
   }
   return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória insuficiente");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos fazer a matriz transposta.");
    }
}

bool Matriz::triangularInferior() const{
    for(int i=0; i<quantLinhas; i++){
        for (int j= i+1; j<quantColunas; j++){
            if ((ptrMatriz[i * quantLinhas+j])!=0)
                return false;
            if (this->quantLinhas != this->quantColunas) return false;
            }
    }
    return true;
}
bool Matriz::triangularSuperior() const{
    for(int i=0; i<quantColunas; i++){
        for (int j=i + 1; j<quantLinhas; j++){
            if ((ptrMatriz[j * quantColunas + i])!=0)
                return false;
            if (this->quantLinhas != this->quantColunas) return false;

         }
      }
        return true;
}

bool Matriz::simetrica() const{
    for(int i=0; i<this->getQuantLinhas(); i++){
        for(int j=0; j<this->getQuantColunas(); j++){
            if(this->getElemento(i, j) != this->getElemento(j ,i)){
                return false;
            }
        }
    }
    return true;
}
bool Matriz::permutacao() const{
    if(this->quantColunas != this->quantLinhas) return false;
    for (int i=0; i<quantLinhas; i++) {
        int aux=0;
        for (int j=0; j<quantColunas; j++) {
            aux=aux + getElemento(i, j);
        }
        if(aux!=1)
            return false;
       // if(this->quantColunas != this->quantLinhas) return false;
    }
    return true;
}

bool Matriz::identidade() const{

    if(this->getQuantLinhas()!=this->getQuantColunas()){
        return false;
       }
    for(int i=0; i<this->getQuantLinhas(); i++){
        for(int j=0; j<this->getQuantColunas(); j++){
            if((i!=j && this->getElemento(i,j)!=0) ||(i==j && this->getElemento(i,j)!=1)){
            return false;
            }
        }
    }
    return true;
}
Matriz* Matriz::multiplicar(int k)const{
    try{
    Matriz *aux = new Matriz(quantLinhas, quantColunas);
    for(int i=0; i<quantLinhas; i++){
        for(int j=0; j<quantColunas; j++){
            int valor = this->getElemento(i,j)*k;
            aux->setElemento(i,j,valor);
        }
    }
    return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória insuficiente");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos multiplicar as matrizes");
    }
}
bool Matriz::operator ==(Matriz const * const mat){
    if ( quantLinhas != mat->getQuantLinhas() || quantColunas != mat->getQuantColunas()) return false;

    for(int i = 0; i < quantLinhas; i++){
        for(int j = 0; j < quantColunas; j++){
            if(this->getElemento(i, j) == mat->getElemento(i, j)) return false;
        }
    }
    return true;
}
bool Matriz::operator !=(Matriz const * const mat){
    if (this->quantLinhas!=mat->quantLinhas||this->quantColunas!=mat->quantColunas){
        return false;
    }
    for (int i=0; i<quantLinhas; i++){
       for(int j=0; j<quantColunas; j++){
          if(this-> getElemento(i,j)!=mat->getElemento(i,j))
             return false;
       }
    }
    return true;
}

bool Matriz::ortogonal () const{
    if(this->quantLinhas!=this->quantColunas)return false; //tem que ser quadrada
    try{
        Matriz* aux = this->calcularTransposta(); //matriz auxiliar guardando matriz transposta
        Matriz* mat = *aux *this; // multiplica transposta pela matriz normal
        delete aux;

        int e = mat->getElemento(0,0);
        if (e == 0){
            delete mat;
            return false;
        }
        else{
            for(int i=0; i<quantLinhas; i++){
                int valor = mat->getElemento(i, i); //diagonal principal: 00,11,22,33, etc
                mat->setElemento(i, i, (valor/e));
            }
            if(mat->identidade()){
                delete mat;
                return true;

            }
        }
        delete mat;
        return false;

    }
    catch(std::bad_alloc&){
        throw QString("Memoria insuficiente.\n");
    }
    catch(QString &erro){
            throw QString ("Matriz auxiliar nao criada.");

    }
    return true;

}

Matriz* Matriz::operator^(int x)const{
    if(x<0)
            throw QString ("O expoente deve ser maior que zero.");
        try{
            if(x==0){
                Matriz *aux=new Matriz(quantColunas,quantLinhas);
                for(int i=0; i<quantLinhas; i++){
                    for(int j=0; j<quantColunas; j++){
                        if(j!=i){
                            aux->setElemento(i,j,0);
                        }else{
                            aux->setElemento(i,j,1);
                        }
                    }
                }
                return aux;
             }else if(x==1){
                Matriz *aux = new Matriz(quantLinhas,quantColunas);
                for(int i=0; i<quantLinhas; i++){
                    for(int j=0; j<quantColunas; j++){
                            int valor = this->getElemento(i,j);
                            aux->setElemento(i,j,valor);

                    }

                }
                return aux;
            }else{
                Matriz *aux = new Matriz(quantLinhas,quantColunas);
                for(int i=0; i<quantLinhas; i++){
                     for(int j=0; j<quantColunas; j++){
                         int valor = this->getElemento(i,j);
                         aux->setElemento(i,j,valor);
                     }
                 }
                 for(int cont=1; cont< x; cont++){
                     Matriz *aux2=aux;
                     aux = (*aux) * this;
                     delete aux2;
                 }
                 return aux;
             }
        }catch(std::bad_alloc&){
            throw QString("Memoria insuficiente.");
        }
        catch(QString &erro){
                throw QString ("A matriz deve ser quadrada.");

        }
}

}//Fim TP2

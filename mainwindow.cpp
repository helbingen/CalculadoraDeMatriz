#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    matA(0),
    matB(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonLimpar->setEnabled(false);
    ui->textEditSaida->setEnabled(false);
    ui->pushButtonLimparB->setEnabled(false);
    ui->textEditSaidaB->setEnabled(false);
    ui->textEditResultado->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCriar_clicked()
{
    try{
        int linha = ui->lineEditLinhas->text().toInt();
        int coluna = ui->lineEditColunas->text().toInt();
        matA = new TP2::Matriz(linha, coluna);
        for(int i = 0; i < linha; i ++){
            for(int j = 0; j < coluna; j++){
                int elemento = QInputDialog::getInt(this, "leitura", "Matriz A [" + QString::number(i)+"]["+QString::number(j)+"]:");
                matA->setElemento(i,j,elemento);
            }
        }
        ui->textEditSaida->setText(matA->getMatriz());
        ui->pushButtonCriar->setEnabled(false);
        ui->lineEditLinhas->setEnabled(false);
        ui->lineEditColunas->setEnabled(false);
        ui->pushButtonLimpar->setEnabled(true);
    }
    catch(QString erro){
        QMessageBox::information(this,"erro", erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::information(this,"erro", "Memória insuficiente");
    }
}

void MainWindow::on_pushButtonLimpar_clicked()
{
    if (matA) delete matA;
    ui->lineEditLinhas->setEnabled(true);
    ui->lineEditColunas->setEnabled(true);
    ui->pushButtonCriar->setEnabled(true);
    ui->pushButtonLimpar->setEnabled(false);
    ui->lineEditColunas->setText("");
    ui->lineEditLinhas->setText("");
    ui->textEditSaida->setText("");
}

void MainWindow::on_pushButtonCriarB_clicked()
{
    try{
        int linha = ui->lineEditLinhasB->text().toInt();
        int coluna = ui->lineEditColunasB->text().toInt();
        matB = new TP2::Matriz(linha, coluna);
        for(int i = 0; i < linha; i ++){
            for(int j = 0; j < coluna; j++){
                int elemento = QInputDialog::getInt(this, "leitura", "Matriz A [" + QString::number(i)+"]["+QString::number(j)+"]:");
                matB->setElemento(i,j,elemento);
            }
        }
        ui->textEditSaidaB->setText(matB->getMatriz());
        ui->pushButtonCriarB->setEnabled(false);
        ui->lineEditLinhasB->setEnabled(false);
        ui->lineEditColunasB->setEnabled(false);
        ui->pushButtonLimparB->setEnabled(true);
    }
    catch(QString erro){
        QMessageBox::information(this,"erro", erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::information(this,"erro", "Memória insuficiente");
    }
}

void MainWindow::on_pushButtonLimparB_clicked()
{
    if (matB) delete matB;
    ui->lineEditLinhasB->setEnabled(true);
    ui->lineEditColunasB->setEnabled(true);
    ui->pushButtonCriarB->setEnabled(true);
    ui->pushButtonLimparB->setEnabled(false);
    ui->lineEditColunasB->setText("");
    ui->lineEditLinhasB->setText("");
    ui->textEditSaidaB->setText("");

}

void MainWindow::on_pushButtonSoma_clicked()
{
    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicionado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicionado");
        TP2::Matriz *matC = 0;
        matC = (*matA)+matB; //matC = matA->operator +(matB); chamada equivalente
        ui->textEditResultado->setText(matC->getMatriz());
        //ui->lineEditColunasB->setText(QString::number(matC->getElemento(0,1)));
        //ui->lineEditLinhasB->setText(QString::number(matC->getElemento(0,0)));
        if(matC) delete matC;
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonSub_clicked()
{

    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicinado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicinado");
        TP2::Matriz *matC = 0;
       // int elemento = QInputDialog::getInt(this, "it");
        int elemento = QInputDialog::getInt(this, "leitura", "1- A-B \n2- B-A.");
        if(elemento!=1 && elemento!=2) throw QString ("Número inválido.");
        if (elemento==1) matC = (*matA)-matB;
        if (elemento==2) matC =  (*matB)-matA;
        ui->textEditResultado->setText(matC->getMatriz());

        if(matC) delete matC;
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonTrans_clicked()
{
    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicinado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicinado");
        TP2::Matriz *matC = 0;
        int elemento = QInputDialog::getInt(this, "leitura", "1- A^t \n2- B^t.");
        if(elemento!=1 && elemento!=2) throw QString ("Número inválido.");
        if (elemento==1){
            matC = matA->calcularTransposta();
        }
        if (elemento==2){
            matC = matB->calcularTransposta();
        }
        ui->textEditResultado->setText(matC->getMatriz());

        if(matC) delete matC;
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonMulti_clicked()
{
    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicinado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicinado");
        TP2::Matriz *matC = 0;
       // int elemento = QInputDialog::getInt(this, "it");
        int elemento = QInputDialog::getInt(this, "leitura", "1- A*B \n2- B*A.");
        if(elemento!=1 && elemento!=2) throw QString ("Número inválido.");
        if (elemento==1){
            if(matA->getQuantColunas() == matB->getQuantLinhas()) matC=(*matA)*matB;

        }
       if (elemento==2){
           if (matB->getQuantColunas() == matA->getQuantLinhas()) matC =  (*matB)*matA;
       }
        ui->textEditResultado->setText(matC->getMatriz());

        if(matC) delete matC;

    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButtoninfo_clicked() //simétrica
{
    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicionado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicionado");
        QString saida = "";

        if(matA->simetrica()==true)
            saida += "A matriz A é simétrica \n";
        else saida+= "A matriz A não é simétrica \n";
        if (matB->simetrica()==true)
            saida += "A matriz B é simétrica \n";
        else saida+= "A matriz B não é simétrica \n";


        ui->textEditComparar->setText(saida);
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonTeste_clicked() //permutação
{
    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicionado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicionado");
        QString saida = "";

        if(matA->permutacao()==true)
            saida += "A matriz A é de permutação \n";
        if(matB->permutacao()==true)
            saida += "A matriz B é de permutação \n";
        ui->textEditComparar->setText(saida);
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonTriangular_clicked()
{
    try{
        if(!matA) throw QString("Matriz A nao existe - não pode ser adicionado");
        if(!matB) throw QString("Matriz B nao existe - não pode ser adicionado");
        QString saida = "";

        if(matA->triangularInferior()==true)
            saida += "A matriz A é triangular inferior \n";
        if(matB->triangularInferior()==true)
        saida += "A matriz B é triangular inferior \n";
        if(matA->triangularSuperior()==true)
        saida += "A matriz A é triangular superior \n";
        if(matB->triangularSuperior()==true)
        saida += "A matriz B é triangular superior \n";

        ui->textEditComparar->setText(saida);
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonInfoX_clicked()
{
    try{
        if(!matA) throw QString("Matriz A nao existe.");
        if(!matB) throw QString("Matriz B nao existe.");
        QString saida = "";

        if(matA->triangularInferior()==true)
            saida += "A matriz A é triangular inferior \n";
        if(matB->triangularInferior()==true)
            saida += "A matriz B é triangular inferior \n";
        if(matA->triangularSuperior()==true)
            saida += "A matriz A é triangular superior \n";
        if(matB->triangularSuperior()==true)
            saida += "A matriz B é triangular superior \n";
        if(matA->permutacao()==true)
            saida += "A matriz A é de permutação \n";
        if(matB->permutacao()==true)
            saida += "A matriz B é de permutação \n";
        if(matA->simetrica()==true)
            saida += "A matriz A é simétrica \n";
        if (matB->simetrica()==true)
            saida += "A matriz B é simétrica \n";
        if (matA->identidade()==true)
            saida += "A matriz A é identidade \n";
        if(matB->identidade()==true)
            saida += "A matriz B é identidade \n";
        //if(matA->operator !=(matB))
        if((matA)!=matB)
            saida += "Matrizes são diferentes \n";
        //if(matA->operator ==(matB))
        if((matA)==matB)
            saida += "Matrizes são iguais \n";
        if(matA->ortogonal()== true)
            saida += "Matriz A é ortogonal \n";
        if(matB->ortogonal()== true)
            saida += "Matriz B é ortogonal \n";

        ui->textEditComparar->setText(saida);
    }catch(QString erro){
        QMessageBox::information(this,"erro",erro);
    }
    catch(std::bad_alloc&){
         QMessageBox::information(this,"erro","Matriz nao pode ser criada");
    }
}


void MainWindow::on_pushButtonMulti_2_clicked()
{
    try{
        ui->textEditResultado->setText("");
        int op=QInputDialog::getInt(this,"Digite:","1-Para multiplicar por A;\n2-Para multiplicar por B.\n");
        int num = QInputDialog::getInt(this, "selecione","Digite o valor a ser multiplicado");
        if(op==1){
            if(matA==0) throw QString("Matriz B nao existe");


            int k = num;

            TP2::Matriz *matC=matA->multiplicar(k);
            QString saida= matC->getMatriz();
            ui->textEditResultado->setText(saida);
            delete matC;
        }else{
            if(matB==0) throw QString("Matriz B nao existe");
            int k = num;

            TP2::Matriz *matC=matB->multiplicar(k);
            QString saida= matC->getMatriz();

            ui->textEditResultado->setText(saida);
            delete matC;
        }
    }catch(QString erro){
            QMessageBox::information(this, "Erro No Sistema",erro);
        }

}

void MainWindow::on_pushButtonPotencia_clicked()
{
    try{
        ui->textEditResultado->setText("");
        int op=QInputDialog::getInt(this,"Digite:","1-Para pontencializar A;\n 2-Para potencializarB.\n");
        int exp = QInputDialog::getInt(this,"Digite:","Digite o numero para ser potencializado");
        if(op==1){
            if(matA==0) throw QString("Matriz A nao existe");
                int x = exp;
            TP2::Matriz *matC = *matA^x;
            QString saida= matC->getMatriz();
            ui->textEditResultado->setText(saida);
            delete matC;
        }else{
            if(matB==0) throw QString("Matriz B nao existe");
            int x = exp;
            TP2::Matriz *matC = *matB^x;
            QString saida= matC->getMatriz();
            ui->textEditSaida->setText(saida);

            delete matC;
        }
    }catch(QString erro){
        QMessageBox::information(this, "Erro No Sistema",erro);
    }
}

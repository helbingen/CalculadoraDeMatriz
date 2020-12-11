#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Matriz.h>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButtonCriar_clicked();

    void on_pushButtonLimpar_clicked();

    void on_pushButtonCriarB_clicked();

    void on_pushButtonLimparB_clicked();

    void on_pushButtonSoma_clicked();

    void on_pushButtonSub_clicked();

    void on_pushButton_clicked();

    void on_pushButtonTrans_clicked();

    void on_pushButtonMulti_clicked();

    void on_pushButtoninfo_clicked();

    void on_pushButtonTeste_clicked();

    void on_pushButtonTriangular_clicked();

    void on_pushButtonInfoX_clicked();

    void on_pushButtonMulti_2_clicked();

    void on_pushButtonPotencia_clicked();

private:
    Ui::MainWindow *ui;
    TP2::Matriz *matA; //cria um ponteiro do tipo Matriz
    TP2::Matriz *matB;

};

#endif // MAINWINDOW_H

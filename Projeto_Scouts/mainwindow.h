#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QDebug>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "jogador.h"
#include "desempenho.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void inserirJogadorNaTabela(int row);
    ~MainWindow();

private slots:
    void on_inserir_clicked();
    void on_OrdenarNome_clicked();

    void on_OrdenarPontos_clicked();

    void on_OrdenarAssist_clicked();

    void on_OrdenarReb_clicked();

    void on_OrdenarFaltas_clicked();

    void on_OrdenarDesempenho_clicked();

    void salvar();
    void carregar();

    void on_tab_geral_cellDoubleClicked(int row, int column);

    void on_tab_geral_cellClicked(int row, int column);


    void on_Limpar_clicked();

private:
    void atualizarTabela();

    jogador atleta;
    desempenho elenco;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

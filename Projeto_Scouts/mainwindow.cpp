#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "desempenho.h"
#include <QTableWidgetItem>
#include <QVector>
#include <QFileDialog>
#include <algorithm>
#include <QDesktopServices>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->actionSalvar,
            SIGNAL(triggered()), this, SLOT(salvar()));
    connect (ui->actionCarregar,
            SIGNAL(triggered()), this, SLOT(carregar()));
}

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::salvar()
{
    QString nomeArquivo = QFileDialog::getSaveFileName(this,
                                                          "Elenco",
                                                         "",
                                                          "CSV(*.csv)");
    elenco.salvarTime(nomeArquivo);

}

void MainWindow::carregar()
{
    QString nomeArquivo = QFileDialog::getOpenFileName(this,
                                                           "Elenco",
                                                           "",
                                                           "CSV(*.csv)");
    elenco.carregarTime(nomeArquivo);

    for(int i=0;i<elenco.size();i++){
    ui->tab_geral->insertRow(i);
    atleta.setNome(elenco[i].getNome());
    atleta.setPontos(elenco[i].getPontos());
    atleta.setAssist(elenco[i].getAssist());
    atleta.setRebotes(elenco[i].getRebotes());
    atleta.setFaltas(elenco[i].getFaltas());
    inserirJogadorNaTabela(i);
  }
}


void MainWindow::on_inserir_clicked()
{
    if(ui->input_a->text().size()<=2) return;

    atleta.setNome( ui->input_a->text());
    atleta.setPontos(QString(ui->input_b->text()).toInt());
    atleta.setRebotes(QString(ui->input_c->text()).toInt());
    atleta.setFaltas(QString(ui->input_d->text()).toInt());
    atleta.setAssist(QString(ui->input_e->text()).toInt());

    if(atleta.getNome()!="Add jogador")
    {
    int qnt_row = ui->tab_geral->rowCount();
    ui->tab_geral->insertRow(qnt_row);
    ui->input_a->clear();
    ui->input_b->clear();
    ui->input_c->clear();
    ui->input_d->clear();
    ui->input_e->clear();

    elenco.inserirJogador(atleta);
    inserirJogadorNaTabela(qnt_row);
    qDebug() << "Passei" << endl;
    }
}


void MainWindow::inserirJogadorNaTabela(int row)
{
    qDebug() << "Entrei" << endl;
    ui->tab_geral->setItem(row,0,new QTableWidgetItem(atleta.getNome()));
    ui->tab_geral->setItem(row,1,new QTableWidgetItem(QString::number(atleta.getPontos())));
    ui->tab_geral->setItem(row,2,new QTableWidgetItem(QString::number(atleta.getAssist())));
    ui->tab_geral->setItem(row,3,new QTableWidgetItem(QString::number(atleta.getRebotes())));
    ui->tab_geral->setItem(row,4,new QTableWidgetItem(QString::number(atleta.getFaltas())));
    ui->tab_geral->setItem(row, 5, new QTableWidgetItem(QString(elenco.status(double(atleta.getPontos()), double(atleta.getRebotes()), double(atleta.getAssist())))));
    qDebug() << "Saí" << endl;
}

void MainWindow::atualizarTabela()
{
        for(int i=ui->tab_geral->rowCount(); i>=0;i--){
        ui-> tab_geral->removeRow(i);}
        for(int i=0; i<elenco.size();i++){
            atleta.setNome(elenco[i].getNome());
            atleta.setPontos(elenco[i].getPontos());
            atleta.setFaltas(elenco[i].getFaltas());
            atleta.setRebotes(elenco[i].getRebotes());
            atleta.setAssist(elenco[i].getAssist());
            int qnt_row = ui->tab_geral->rowCount();
            ui-> tab_geral->insertRow(qnt_row);
            inserirJogadorNaTabela(i);}
}


void MainWindow::on_OrdenarNome_clicked()
{
    elenco.ordenarPorNome();
        atualizarTabela();
}

void MainWindow::on_OrdenarPontos_clicked()
{
    elenco.ordenarPorPontos();
        atualizarTabela();
}

void MainWindow::on_OrdenarAssist_clicked()
{
    elenco.ordenarPorAssist();
        atualizarTabela();
}

void MainWindow::on_OrdenarReb_clicked()
{
    elenco.ordenarPorRebotes();
        atualizarTabela();
}

void MainWindow::on_OrdenarFaltas_clicked()
{
    elenco.ordenarPorFaltas();
        atualizarTabela();
}


void MainWindow::on_tab_geral_cellDoubleClicked(int row, int column)
{
    jogador novo;
    if(column==0){
        bool ok;
        QMessageBox::StandardButton editar = QMessageBox::question(this, "Editar: ", "Deseja alterar o nome?");
        if(editar==QMessageBox::Yes){
            QString nome = QInputDialog::getText(this, "Alterar nome: ", "Nome: ", QLineEdit::Normal,"",&ok);
            if(ok && !nome.isEmpty()){
             novo.setNome(nome);
             novo.setAssist(elenco[row].getAssist());
             novo.setPontos(elenco[row].getPontos());
             novo.setRebotes(elenco[row].getRebotes());
             novo.setFaltas(elenco[row].getFaltas());

            elenco.inserirJogador(novo);
            ui->tab_geral->setItem(row,0,new QTableWidgetItem(novo.getNome()));
            }
        }
    }
      else if(column==1){
        bool ok;
        QMessageBox::StandardButton editar = QMessageBox::question(this, "Editar: ", "Deseja alterar PONTOS?");
        if(editar==QMessageBox::Yes){
            QString nome = QInputDialog::getText(this, "Alterar pontos: ", "Pontos: ", QLineEdit::Normal,"",&ok);
            if(ok && !nome.isEmpty()){
             novo.setPontos(nome.toInt());
             novo.setAssist(elenco[row].getAssist());
             novo.setNome(elenco[row].getNome());
             novo.setRebotes(elenco[row].getRebotes());
             novo.setFaltas(elenco[row].getFaltas());

            elenco.inserirJogador(novo);
            ui->tab_geral->setItem(row,1,new QTableWidgetItem(QString::number(novo.getPontos())));
            }
        }
    }
          else if(column==2){
                bool ok;
                QMessageBox::StandardButton editar = QMessageBox::question(this, "Editar: ", "Deseja alterar ASSISTÊNCIAS?");
                if(editar==QMessageBox::Yes){
                    QString nome = QInputDialog::getText(this, "Alterar assitências: ", "Assistências: ", QLineEdit::Normal,"",&ok);
                    if(ok && !nome.isEmpty()){
                     novo.setAssist(nome.toInt());
                     novo.setPontos(elenco[row].getPontos());
                     novo.setNome(elenco[row].getNome());
                     novo.setRebotes(elenco[row].getRebotes());
                     novo.setFaltas(elenco[row].getFaltas());

                    elenco.inserirJogador(novo);
                    ui->tab_geral->setItem(row,2,new QTableWidgetItem(QString::number(novo.getAssist())));
                    }
         }
            }
    else if(column==3){
          bool ok;
          QMessageBox::StandardButton editar = QMessageBox::question(this, "Editar: ", "Deseja alterar REBOTES?");
          if(editar==QMessageBox::Yes){
              QString nome = QInputDialog::getText(this, "Alterar rebotes: ", "Rebotes: ", QLineEdit::Normal,"",&ok);
              if(ok && !nome.isEmpty()){
               novo.setRebotes(nome.toInt());
               novo.setPontos(elenco[row].getPontos());
               novo.setNome(elenco[row].getNome());
               novo.setAssist(elenco[row].getAssist());
               novo.setFaltas(elenco[row].getFaltas());

              elenco.inserirJogador(novo);
              ui->tab_geral->setItem(row,3,new QTableWidgetItem(QString::number(novo.getRebotes())));
              }
   }
      }
        else if(column==4){
        bool ok;
        QMessageBox::StandardButton editar = QMessageBox::question(this, "Editar: ", "Deseja alterar FALTAS?");
        if(editar==QMessageBox::Yes){
            QString nome = QInputDialog::getText(this, "Alterar falta: ", "Faltas: ", QLineEdit::Normal,"",&ok);
            if(ok && !nome.isEmpty()){
             novo.setFaltas(nome.toInt());
             novo.setPontos(elenco[row].getPontos());
             novo.setNome(elenco[row].getNome());
             novo.setAssist(elenco[row].getAssist());
             novo.setRebotes(elenco[row].getRebotes());

            elenco.inserirJogador(novo);
            ui->tab_geral->setItem(row,4,new QTableWidgetItem(QString::number(novo.getFaltas())));
            }
 }
    }
}

void MainWindow::on_Limpar_clicked()
{
    for(int i=0;i<elenco.size();i++){
            ui-> tab_geral->removeRow(i);}
}

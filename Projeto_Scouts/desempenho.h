#ifndef DESEMPENHO_H
#define DESEMPENHO_H

#include <QObject>
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include "jogador.h"


class desempenho
{
private:


public:
    desempenho();
    double obterMediaPontos();
    double obterMediaReb();
    double obterMediaAssist();
    void inserirJogador(jogador A);
    QString status(double pontos, double rebotes, double assist);
    QVector <jogador> total;
    bool salvarTime(QString arquivo);
    bool carregarTime(QString arquivo);
    int size();
    jogador operator[](int i);
    void ordenarPorNome();
    void ordenarPorPontos();
    void ordenarPorFaltas();
    void ordenarPorAssist();
    void ordenarPorRebotes();

};
bool compararPorPontos(jogador a, jogador b);
bool compararPorNome(jogador a, jogador b);
bool compararPorFaltas(jogador a, jogador b);
bool compararPorRebotes(jogador a, jogador b);
bool compararPorAssist(jogador a, jogador b);

#endif // DESEMPENHO_H

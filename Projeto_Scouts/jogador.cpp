#include "jogador.h"
#include <QVector>
#include <cstring>
#include "desempenho.h"


jogador::jogador()
{
    nome = "Add jogador";
    pontos=0;
    assist = 0 ;
    rebotes=0;
    faltas=0;
}

QString jogador::getNome() const
{
    return nome;
}

void jogador::setNome(const QString &value)
{
    for(int i=0; i<value.size(); i++)
    {
        if(value[i].isDigit())
        return ;
    }
        nome=value;
    ;
}

int jogador::getPontos() const
{
    return pontos;
}

void jogador::setPontos(int value)
{
    pontos = value;
}

int jogador::getAssist() const
{
    return assist;
}

void jogador::setAssist(int value)
{
    assist = value;
}

int jogador::getRebotes() const
{
    return rebotes;
}

void jogador::setRebotes(int value)
{
    rebotes = value;
}

int jogador::getFaltas() const
{
    return faltas;
}

void jogador::setFaltas(int value)
{
    if(value<=5){
        faltas = value;}
    else{
            faltas = 5;
        }
}

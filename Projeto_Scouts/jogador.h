#ifndef JOGADOR_H
#define JOGADOR_H
#include <QString>

class jogador
{
public:
    jogador();
    QString getNome() const;
    void setNome(const QString &value);

    int getPontos() const;
    void setPontos(int value);

    int getAssist() const;
    void setAssist(int value);

    int getRebotes() const;
    void setRebotes(int value);

    int getFaltas() const;
    void setFaltas(int value);

private:

    QString nome;
    int pontos;
    int assist;
    int rebotes;
    int faltas;

};

#endif // JOGADOR_H

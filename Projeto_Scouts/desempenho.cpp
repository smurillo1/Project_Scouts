#include "desempenho.h"

desempenho::desempenho()
{


}

double desempenho::obterMediaPontos()
{
     int soma_pontos= 0, i = 0;
    for(i=0; i<total.size(); i++){
        soma_pontos+=total[i].getPontos();
    }
    return soma_pontos/total.size();
}

double desempenho::obterMediaReb()
{
    int soma_reb= 0, i = 0;
   for(i=0; i<total.size(); i++){
       soma_reb   += total[i].getRebotes();
   }
   return soma_reb/total.size();
}

double desempenho::obterMediaAssist()
{
    int soma_assist= 0, i = 0;
   for(i=0; i<total.size(); i++){
       soma_assist   += total[i].getAssist();
   }
   return soma_assist/total.size();
}

void desempenho::inserirJogador(jogador A)
{
    total.push_back(A);
}

QString desempenho::status(double pontos, double rebotes, double assist )
{
    int flag = 0;
    if(pontos==obterMediaPontos()&&rebotes==obterMediaReb()&&assist==obterMediaAssist())
        return "NA MÉDIA";
    if(pontos>obterMediaPontos()){
        flag++;
    }
    if(rebotes>obterMediaReb()){
        flag++;
    }
    if(assist>obterMediaAssist()){
        flag++;
    }
    if(flag>= 2){
        return "ACIMA";
    }else return "ABAIXO";
}

bool desempenho::salvarTime(QString arquivo)
{
    QFile file(arquivo);
    QString linha;
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream out(&file);
    for(jogador a:total){
        out<<a.getNome()<<","<<a.getPontos()<<","<<a.getAssist()<<","
          <<a.getRebotes()<<","<<a.getFaltas()<<","<<endl;

    }
}

bool desempenho::carregarTime(QString arquivo)
{
    QFile file(arquivo);
        if(!file.open(QIODevice::ReadOnly))
            return false;

        QString linha;
        jogador a;
        while(!file.atEnd()){
            linha = file.readLine();
            QStringList dados = linha.split(",");
            a.setNome(dados[0]);
            a.setPontos(dados[1].toDouble());
            a.setAssist(dados[2].toDouble());
            a.setRebotes(dados[3].toDouble());
            a.setFaltas(dados[4].toDouble());
            inserirJogador(a);}
}

int desempenho::size()
{
    return total.size();
}

jogador desempenho::operator[](int i)
{
    return total[i];
}


bool compararPorPontos(jogador a, jogador b)
{
    return a.getPontos()>b.getPontos();
}

bool compararPorNome(jogador a, jogador b)
{
    return a.getNome()<b.getNome();
}


bool compararPorFaltas(jogador a, jogador b)
{
    return a.getFaltas()>b.getFaltas();
}


bool compararPorRebotes(jogador a, jogador b)
{
    return a.getRebotes()>b.getRebotes();
}


bool compararPorAssist(jogador a, jogador b)
{
    return a.getAssist()>b.getAssist();
}
void desempenho::ordenarPorNome()
{
    std::sort(total.begin(),total.end(),compararPorNome);
}

void desempenho::ordenarPorPontos()
{
    std::sort(total.begin(),total.end(),compararPorPontos);
}

void desempenho::ordenarPorFaltas()
{
     std::sort(total.begin(),total.end(),compararPorFaltas);
}

void desempenho::ordenarPorAssist()
{
    std::sort(total.begin(),total.end(),compararPorAssist);
}

void desempenho::ordenarPorRebotes()
{
    std::sort(total.begin(),total.end(),compararPorRebotes);
}

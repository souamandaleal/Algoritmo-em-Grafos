#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> listaAdj;
bool mobileBom = true;

int mFuncao(int nohAtual)
{
    int numFilhos, peso, atual, total;

    numFilhos = listaAdj[nohAtual].size();
    //cout << "O tamanho da minha lista eh " << cont << endl;
    total = 1;

    for (int i = 0; i < numFilhos; i++)
    {
        atual = mFuncao(listaAdj[nohAtual][i]);

        //cout << "Estou consultando esse noh " << listaAdj[nohAtual][i] << endl;
        if (i == 0)
        {
            /*cout << "Entrei aqui nesse noh " << listaAdj[nohAtual][i] << endl;
            cout << "E o atual dele eh " << atual << endl;*/
            peso = atual;
        }
        else if (atual != peso)
        {
            /*cout << "Entrei aqui nesse noh " << listaAdj[nohAtual][i] << endl;
            cout << "O meu atual eh " << atual << endl;
            cout << "O meu peso " << peso << endl;*/
            mobileBom = false;
        }
        total = total + atual;
    }
    return (total);
}

int main()
{
    int numVertices, verticePai, verticeFilho;

    cin >> numVertices;

    listaAdj.resize(numVertices + 1);

    //inicializando a minha estrutura de lista
    for (int i = 0; i < numVertices; i++)
    {
        cin >> verticeFilho >> verticePai;
        listaAdj[verticePai].push_back(verticeFilho);
    }
    mFuncao(0);

    if (mobileBom)
    {
        cout << "bem" << endl;
    }
    else
    {
        cout << "mal" << endl;
    }

    return 0;
}
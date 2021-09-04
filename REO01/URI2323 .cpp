/*
Caio Vinicius Rodrigues da Costa
Iorrana Maria do Nascimento
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> listaAdj;
bool mobileBom = true;

int percorrerLista(int nohAtual);

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

    //vou iniciar o percorrimento do meu grafo no primeiro vertice
    percorrerLista(0);

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

int percorrerLista(int nohAtual)
{
    int numFilhos, nivelAnterior, nivelAtual;
    //busco o tamanho do vetor que esta nessa posicao
    numFilhos = listaAdj[nohAtual].size();

    int totalVertice = 1;

    for (int i = 0; i < numFilhos; i++)
    {
        //chamo recursivamente o proximo vertice no meu vetor
        nivelAtual = percorrerLista(listaAdj[nohAtual][i]);

        //Se eu sou o primeiro filho
        if (i == 0)
        {
            nivelAnterior = nivelAtual;
        }
        //se eu não sou o primeiro filho
        else if (nivelAtual != nivelAnterior)
        {
            mobileBom = false;
        }

        totalVertice = totalVertice + nivelAtual;
    }

    return (totalVertice);
}
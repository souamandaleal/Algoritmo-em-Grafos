/*
Caio Vinicius Rodrigues da Costa
Iorrana Maria do Nascimento
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

//defino o maximo de vertices e arestas do problema
#define MAXIMO_BYTELAND 200000

using namespace std;

//defino a estrutura da minha lista de arestas
typedef pair<int, int> lista_arestas;

//defino o meu grafo
vector<lista_arestas> mGrafo[MAXIMO_BYTELAND];

bool verticeVisitado[MAXIMO_BYTELAND];

int numVertices, numArestas;

int algoritmoPrim(int verticeOrigem);

int main()
{
    cin >> numVertices >> numArestas;
    int vertice1, vertice2, pesoAresta, gastoTotalByteland;

    //controlando a parada do meu algoritmo
    while (numVertices != 0 || numArestas != 0)
    {

        //limpo o vector antes de uma nova execucao
        for (int i = 0; i <= numVertices; i++)
        {
            mGrafo[i].clear();
        }

        gastoTotalByteland = 0;

        //preenchendo o meu grafo
        for (int i = 0; i < numArestas; i++)
        {
            cin >> vertice1 >> vertice2 >> pesoAresta;

            //adiciona a cada vértice do grafo o vértice e aresta que ele está conectado
            mGrafo[vertice1].push_back(lista_arestas(vertice2, pesoAresta));
            mGrafo[vertice2].push_back(lista_arestas(vertice1, pesoAresta));

            gastoTotalByteland = gastoTotalByteland + pesoAresta;
        }
        cout << gastoTotalByteland - algoritmoPrim(0) << endl;

        cin >> numVertices >> numArestas;
    }

    return 0;
}

int algoritmoPrim(int verticeOrigem)
{
    int menorValorByteland = 0;

    //minHeap para priorizar os vertices
    priority_queue<lista_arestas, vector<lista_arestas>, greater<lista_arestas>> minHeap;

    //marco todos os vertices como nao visitado
    for (int i = 0; i <= numArestas; i++)
    {
        verticeVisitado[i] = false;
    }

    //coloca na minnHeap o vertice origem e os seus vizinhos
    for (int i = 0; i < mGrafo[verticeOrigem].size(); i++)
    {
        minHeap.push(lista_arestas(mGrafo[verticeOrigem][i].second, mGrafo[verticeOrigem][i].first));
        verticeVisitado[verticeOrigem] = true;
    }

    while (!minHeap.empty())
    {
        lista_arestas lista_auxiliar = minHeap.top();
        minHeap.pop();

        int mPeso = lista_auxiliar.first;
        int mVertice = lista_auxiliar.second;

        //se o topo da minHeap nao foi visitado
        if (!verticeVisitado[mVertice])
        {

            menorValorByteland = menorValorByteland + mPeso;
            verticeVisitado[mVertice] = true;

            //visito os vizinhos do vertice contado
            for (int i = 0; i < mGrafo[mVertice].size(); i++)
            {
                //se o vizinho nao foi visitado adiciono ele na fila pra visitar
                if (!verticeVisitado[mGrafo[mVertice][i].first])
                    minHeap.push(lista_arestas(mGrafo[mVertice][i].second, mGrafo[mVertice][i].first));
            }
        }
    }
    return menorValorByteland;
}

/*
Caio Vinicius Rodrigues da Costa
Iorrana Maria do Nascimento
*/

#include <iostream>
#include <vector>
#include <queue>

#define INFINITO 1000000
#define MAXCIDADES 10000

using namespace std;

// defino a estrutura da minha lista de adjacencia
typedef pair<int, int> listaAdj;

vector<listaAdj> mGrafo[MAXCIDADES];
vector<listaAdj> mGrafoAux[MAXCIDADES];

int distancia[MAXCIDADES];
bool visited[MAXCIDADES];

int numVertices, numArestas;

int doDijkstra(int verticeOrigem, int verticeDestino);
void inicializar(int mOrigem);
void transformarGrafo();

int main()
{
    cin >> numVertices >> numArestas;

    int vertice1, vertice2, pesoAresta;

    // criando o grafo
    for (int i = 0; i < numArestas; i++)
    {
        cin >> vertice1 >> vertice2 >> pesoAresta;
        mGrafo[vertice1 - 1].push_back(make_pair(vertice2 - 1, pesoAresta));
        mGrafo[vertice2 - 1].push_back(make_pair(vertice1 - 1, pesoAresta));
    }

    // somo o pesos das arestas adjacentes e cria um novo grafo
    transformarGrafo();

    // passo a origem definida como 0 e a orgiem como o numero de vertices, iterando em cima do grafo auxiliar criado na função anterior
    int menorCusto = doDijkstra(0, numVertices - 1);

    if (menorCusto == INFINITO)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << menorCusto << endl;
    }

    return 0;
}

int doDijkstra(int verticeOrigem, int verticeDestino)
{
    // crio minha fila de prioridade
    priority_queue<listaAdj, vector<listaAdj>, greater<listaAdj>> minHeap;

    // adicionando na fila de prioridades o vertice origem e a sua distancia
    minHeap.push(make_pair(distancia[verticeOrigem], verticeOrigem));

    // inicializo os vértices do grafo
    inicializar(verticeOrigem);

    while (!minHeap.empty())
    {
        // crio uma lista auxiliar que recebeo o meu elemento que esta em cima
        listaAdj listaAux = minHeap.top();
        int umVertice = listaAux.second;
        // retiro ele da minha fila
        minHeap.pop();

        // verifico se ele tem antecessor
        if (visited[umVertice] == false)
        {
            visited[umVertice] = true;
            for (vector<listaAdj>::iterator i = mGrafoAux[umVertice].begin(); i != mGrafoAux[umVertice].end(); i++)
            {
                int mVertice = i->first;
                int mPesoAresta = i->second;

                // tento relaxar a aresta
                if (distancia[mVertice] > (distancia[umVertice] + mPesoAresta))
                {
                    distancia[mVertice] = distancia[umVertice] + mPesoAresta;
                    // adiciono ele na minha fila
                    minHeap.push(make_pair(distancia[mVertice], mVertice));
                }
            }
        }
    }
    return distancia[verticeDestino];
}

void inicializar(int mOrigem)
{
    for (int i = 0; i < numVertices; i++)
    {
        distancia[i] = INFINITO;
        visited[i] = false;
    }
    distancia[mOrigem] = 0;
}

void transformarGrafo()
{
    for (int i = 0; i < numVertices; i++)
    {
        vector<listaAdj>::iterator it;
        for (it = mGrafo[i].begin(); it != mGrafo[i].end(); it++) // pego a posicao da coluna
        {
            int verticeAdj = it->first;
            int custoVerticeAdj = it->second;

            vector<listaAdj>::iterator it2;
            bool tamanhoListaAdj = mGrafo[verticeAdj].size();

            if (tamanhoListaAdj > 0)
            {                                                                                  // se houver elementos na lista
                for (it2 = mGrafo[verticeAdj].begin(); it2 != mGrafo[verticeAdj].end(); it2++) // pego as posições na linha
                {
                    int mVerticeAdj = it2->first;
                    int mCustoVerticeAdj = it2->second;

                    // populo o novo grafo
                    mGrafoAux[i].push_back(make_pair(mVerticeAdj, mCustoVerticeAdj + custoVerticeAdj));
                    mGrafoAux[mVerticeAdj].push_back(make_pair(i, mCustoVerticeAdj + custoVerticeAdj));
                }
            }
        }
    }
}
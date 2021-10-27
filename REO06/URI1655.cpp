/*
Caio Vinicius Rodrigues da Costa
Iorrana Maria do Nascimento

Algoritmo de Dijkstra adaptado do REO anterior para atender o problema
*/

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

#define MAXVERTICES 100

using namespace std;

// defino a estrutura da minha lista de adjacencia
typedef pair<double, int> listaAdj;

vector<listaAdj> mGrafo[MAXVERTICES];
double distancia[MAXVERTICES];
int numVertices, numArestas;

double doDijkstra(int verticeOrigem, int verticeDestino);
void inicializar(int mVerticeOrigem);

int main()
{
	int pontoA, pontoB, pesoAresta;

	cin >> numVertices;

	while (numVertices != 0) // criterio de parada do programa
	{
		cin >> numArestas;

		// limpo o vector antes de uma nova execucao
		for (int i = 0; i <= numVertices; i++)
		{
			mGrafo[i].clear();
		}

		// criando o meu grafo
		for (int i = 0; i < numArestas; i++)
		{
			cin >> pontoA >> pontoB >> pesoAresta;
			mGrafo[pontoA - 1].push_back(listaAdj((double)pesoAresta / 100, pontoB - 1));
			mGrafo[pontoB - 1].push_back(listaAdj((double)pesoAresta / 100, pontoA - 1));
		}

		double melhorCaminho = doDijkstra(0, numVertices - 1);

		// formatando o output
		cout << fixed << setprecision(6);
		cout << melhorCaminho * 100 << " percent" << endl;

		// tento uma nova execucao
		cin >> numVertices;
	}

	return 0;
}

double doDijkstra(int verticeOrigem, int verticeDestino)
{
	// crio minha fila de prioridade
	priority_queue<listaAdj, vector<listaAdj>, greater<listaAdj>> minHeap;

	// adicionando na fila de prioridades o vertice origem e a sua distancia
	minHeap.push(listaAdj(1.0, verticeOrigem));

	// inicializo os vértices do grafo
	inicializar(verticeOrigem);

	while (!minHeap.empty())
	{
		// crio uma lista auxiliar que recebeo o meu elemento que esta em cima
		listaAdj listaAux = minHeap.top();
		//// retiro ele da minha fila
		minHeap.pop();

		int umVertice = listaAux.second;
		double umPesoAresta = listaAux.first;

		// verifico se ele ja foi visitado
		if (umPesoAresta <= distancia[umVertice])
		{
			for (vector<listaAdj>::iterator i = mGrafo[umVertice].begin(); i != mGrafo[umVertice].end(); i++)
			{
				int mVertice = i->second;
				double mPesoAresta = i->first;

				// tento relaxar a aresta (adaptado para atender o problema)
				if (distancia[mVertice] < distancia[umVertice] * mPesoAresta)
				{
					distancia[mVertice] = distancia[umVertice] * mPesoAresta;
					// adiciono ele na minha fila
					minHeap.push(listaAdj(distancia[mVertice], mVertice));
				}
			}
		}
	}
	return distancia[verticeDestino];
}

void inicializar(int mVerticeOrigem)
{
	for (int i = 0; i <= numVertices; i++)
	{
		distancia[i] = -1;
	}
	distancia[mVerticeOrigem] = 1.0;
}
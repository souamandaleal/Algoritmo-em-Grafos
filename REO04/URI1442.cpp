#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

// cada vértice tem o seu componente
vector<int> listaVerticesComponentes;
int numVertices, numArestas, componente;
bool atravessei;

class Grafo
{
private:
    int V;
    list<int> *adj;
    bool orientado;

    void preenche(int v, bool visitados[], stack<int> &pilha)
    {
        visitados[v] = true;

        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if (visitados[*i] == false)
                preenche(*i, visitados, pilha);
        }
        pilha.push(v);
    }

    void DFS(int v, bool visitados[])
    {
        visitados[v] = true;

        if (orientado)
            listaVerticesComponentes[v] = componente;

        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if (visitados[*i] == false)
                DFS(*i, visitados);
        }
    }

public:
    Grafo(int V, bool orientado = true)
    {
        this->V = V;
        adj = new list<int>[V];
        this->orientado = orientado;
    }

    void adicionarAresta(int i, int j)
    {
        adj[i].push_back(j);
    }

    Grafo obterGrafoTransposto()
    {
        Grafo grafo_transposto(V);

        for (int v = 0; v < V; v++)
        {
            list<int>::iterator i;
            for (i = adj[v].begin(); i != adj[v].end(); i++)
                grafo_transposto.adj[*i].push_back(v);
        }

        return grafo_transposto;
    }

    int obterComponentes()
    {
        int qte_componentes = 0;
        stack<int> pilha;
        bool *visitados = new bool[V];

        for (int i = 0; i < V; i++)
            visitados[i] = false;

        for (int i = 0; i < V; i++)
        {
            if (visitados[i] == false)
                preenche(i, visitados, pilha);
        }

        Grafo gt = obterGrafoTransposto();

        for (int i = 0; i < V; i++)
            visitados[i] = false;

        while (!pilha.empty())
        {
            int v = pilha.top();

            pilha.pop();

            if (visitados[v] == false)
            {
                gt.DFS(v, visitados);
                qte_componentes++;

                if (orientado)
                    componente++;
            }
        }

        return qte_componentes;
    }

    bool ehConectado()
    {
        bool *visitados = new bool[V];

        for (int i = 0; i < V; i++)
            visitados[i] = false;

        DFS(0, visitados);

        for (int i = 0; i < V; i++)
        {
            if (!visitados[i])
                return false;
        }

        return true;
    }

    void bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[])
    {
        if (atravessei == false)
        {
            static int time = 0;

            visited[u] = true;

            disc[u] = low[u] = ++time;

            list<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;

                if (!visited[v])
                {
                    parent[v] = u;
                    bridgeUtil(v, visited, disc, low, parent);

                    low[u] = min(low[u], low[v]);

                    // vértices que formam a ponte
                    if (low[v] > disc[u])
                    {
                        /*
							verifica se os vértices estão em componentes
							separados no grafo original
						*/
                        if (listaVerticesComponentes[v] != listaVerticesComponentes[u])
                        {
                            atravessei = true;
                            break;
                        }
                    }
                }
                else if (v != parent[u])
                    low[u] = min(low[u], disc[v]);
            }
        }
    }

    void bridge()
    {
        bool *visited = new bool[V];
        int *disc = new int[V];
        int *low = new int[V];
        int *parent = new int[V];

        for (int i = 0; i < V; i++)
        {
            parent[i] = -1;
            visited[i] = false;
        }

        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                bridgeUtil(i, visited, disc, low, parent);
    }
};

int main()
{

    while (cin >> numVertices)
    {
        componente = 1;
        listaVerticesComponentes.clear();
        atravessei = false;

        for (int i = 0; i < numVertices; i++)
            listaVerticesComponentes.push_back(0);

        cin >> numArestas;
        Grafo g(numVertices);         // grafo original
        Grafo g2(numVertices, false); // grafo não orientado
        int A, B, T;

        cin >> A >> B >> T;

        for (int i = 1; i < numArestas; i++)
        {
            cin >> A >> B >> T;

            if (T == 1)
            {
                g.adicionarAresta(A - 1, B - 1);
            }
            else
            {
                g.adicionarAresta(A - 1, B - 1);
                g.adicionarAresta(B - 1, A - 1);
            }

            // grafo não orientado: adiciona a ida e a volta
            g2.adicionarAresta(A - 1, B - 1);
            g2.adicionarAresta(B - 1, A - 1);
        }

        int ssc = g.obterComponentes();

        // se for 1, então não precisa mudar direção alguma, imprime "-"
        if (ssc == 1)
        {
            cout << "-";
        }
        else if (ssc > 1)
        {
            /*
				se for maior que 1, verifica se o grafo não orientado
				é conectado, se não for imprime "*"
			*/

            if (!g2.ehConectado())
                cout << "*";
            else
            {
                g2.bridge();

                if (atravessei == false)
                    cout << "1";
                else
                    cout << "2";
            }
        }

        cout << endl;
    }

    return 0;
}
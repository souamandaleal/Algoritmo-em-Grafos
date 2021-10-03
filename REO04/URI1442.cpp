/*
Caio Vinicius Rodrigues da Costa
Iorrana Maria do Nascimento

Códigos checados e adaptados dos seguintes links:
https://www.geeksforgeeks.org/bridge-in-a-graph/
https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
*/

#include <iostream>
#include <vector>

#define MAXVERTICES 1000

using namespace std;

int numVertices, numArestas, indiceDisc, contador, mPontes, componente;

vector<int> grafoOrigem[MAXVERTICES];      //lista com os vertices a
vector<int> grafoDestino[MAXVERTICES];     //lista com os vertices b
vector<int> grafoComponentes[MAXVERTICES]; //lista com as componentes encontradas

int mDiscovery[MAXVERTICES], listaComponentes[MAXVERTICES];
bool visited[MAXVERTICES];

int dfs_discovery[MAXVERTICES], dfs_low[MAXVERTICES], dfs_parent[MAXVERTICES]; // tarjan

void inicializa();                       //funcao para inicializar
void DFS(int mVertice);                  //DFS que vai calcular os valores de discovery em G
void DFS(int mVertice, int mComponente); //DFS que vai montar o garfo auxiliar das componentes fortemente conexas
void doTarjan(int mVertice);

int main()
{
    componente = 0;

    int verticeOrigem, verticeDestino, sentidoRua;

    while (cin >> numVertices >> numArestas)
    {

        //limpa a execucao anterior
        inicializa();

        // leio as arestas iniciais
        cin >> verticeOrigem >> verticeDestino >> sentidoRua;

        for (int i = 1; i < numArestas; i++)
        {
            cin >> verticeOrigem >> verticeDestino >> sentidoRua;

            grafoOrigem[verticeOrigem - 1].push_back(verticeDestino - 1);
            grafoDestino[verticeDestino - 1].push_back(verticeOrigem - 1);

            if (sentidoRua == 2) //se o sentido da rua eh dupla adiciona nas duas listas
            {
                grafoOrigem[verticeDestino - 1].push_back(verticeOrigem - 1);
                grafoDestino[verticeOrigem - 1].push_back(verticeDestino - 1);
            }
        }

        //descobrir o tempo de discovery de cada vertice
        for (int i = 0; i < numVertices; i++)
        {
            if (visited[i] == false)
            {
                DFS(i);
            }
        }

        //descobrir as componentes fortemente conexas
        for (int i = numVertices - 1; i >= 0; i--)
        {
            if (listaComponentes[mDiscovery[i]] == -1)
            {
                DFS(mDiscovery[i], componente++);
            }
        }

        //caso tenha apenas uma componente entao implica em fortemente conexa
        if (componente == 1)
        {
            cout << "-" << endl;
            continue;
        }

        //vou procurar por pontes no grafo das componentes
        contador = 0;
        dfs_parent[0] = 0;
        doTarjan(0);

        //verifico se o grafo das componentes eh conexo
        int j;
        for (j = 0; j < componente; j++)
        {
            if (dfs_parent[j] == -1)
            {
                break;
            }
        }

        if (j < componente)
        {
            cout << "*" << endl;
        }
        else if (mPontes)
        {
            cout << "2" << endl;
        }
        else
        {
            cout << "1" << endl;
        }
    }

    return 0;
}

void inicializa()
{
    for (int i = 0; i < numVertices; i++)
    {
        grafoOrigem[i].clear();
        grafoDestino[i].clear();
        grafoComponentes[i].clear();
        dfs_parent[i] = -1;
        dfs_discovery[i] = -1;
        dfs_low[i] = -1;
        listaComponentes[i] = -1;
        visited[i] = false;
        mDiscovery[i] = -1;
        mPontes = 0;
        indiceDisc = 0;
        componente = 0;
    }
}

void DFS(int mVertice)
{
    visited[mVertice] = true;

    vector<int>::iterator i;
    for (i = grafoOrigem[mVertice].begin(); i != grafoOrigem[mVertice].end(); i++)
    {
        if (visited[*i] == false)
            DFS(*i);
    }
    mDiscovery[indiceDisc++] = mVertice;
}

void DFS(int mVertice, int mComponente)
{
    listaComponentes[mVertice] = mComponente;

    vector<int>::iterator i;
    for (i = grafoDestino[mVertice].begin(); i != grafoDestino[mVertice].end(); i++)
    {
        if (listaComponentes[*i] == -1)
        {

            DFS(*i, mComponente);
        }
        else if (listaComponentes[*i] != listaComponentes[mVertice])
        {
            grafoComponentes[listaComponentes[*i]].push_back(listaComponentes[mVertice]);
            grafoComponentes[listaComponentes[mVertice]].push_back(listaComponentes[*i]);
        }
    }
}

void doTarjan(int mVertice)
{
    int umVertice;
    dfs_discovery[mVertice] = contador++;
    dfs_low[mVertice] = dfs_discovery[mVertice];
    vector<int>::iterator i;
    for (i = grafoComponentes[mVertice].begin(); i != grafoComponentes[mVertice].end(); i++)
    {
        if (dfs_discovery[umVertice = (*i)] == -1)
        {
            dfs_parent[umVertice] = mVertice;
            doTarjan(umVertice);
            if (dfs_low[mVertice] > dfs_low[umVertice])
            {
                dfs_low[mVertice] = dfs_low[umVertice];
            }

            // testo ponte a existencia de uma ponte
            else if (dfs_low[umVertice] == dfs_discovery[umVertice] && mPontes == 0)
            {
                int q = 0;
                vector<int>::iterator i;
                for (i = grafoComponentes[mVertice].begin(); i != grafoComponentes[mVertice].end(); i++)
                {
                    if ((*i) == umVertice)
                    {
                        q++;
                    }

                    if (q > 1) //encontrei um arco paralelo
                    {
                        break;
                    }
                }

                if (q == 1)
                {
                    mPontes++;
                }
            }
        }
        else if (umVertice != dfs_parent[mVertice] && dfs_low[mVertice] > dfs_discovery[umVertice])
        {
            dfs_low[mVertice] = dfs_discovery[umVertice];
        }
    }
}
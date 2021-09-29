#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#define pb push_back
#define MAXV 1010

using namespace std;

typedef vector<int> vi;

vi S;
int V, E, dfs_parent[MAXV], dfs_low[MAXV], dfs_num[MAXV], visited[MAXV];
int ans, counter, flag, ok;

vector<vector<int>> directed(MAXV), undirected(MAXV);

struct no
{
    int pai, rank;
};

typedef struct no UJoin;

UJoin pset[MAXV];

void initialize()
{
    for (int i = 0; i < V; ++i)
    {
        pset[i].pai = i;
        pset[i].rank = visited[i] = 0;
        dfs_parent[i] = dfs_low[i] = dfs_num[i] = 0;
        directed[i].clear();
        undirected[i].clear();
    }
}

/*void link(int x, int y)
{
    if (pset[x].rank > pset[y].rank)
        pset[y].pai = x;
    else
    {
        pset[x].pai = y;
        if (pset[x].rank == pset[y].rank)
            pset[y].rank = pset[y].rank + 1;
    }
}*/

int findSet(int x)
{
    while (pset[x].pai != x)
        x = pset[x].pai;
    return x;
}

/*void unionSet(int x, int y)
{
    link(findSet(x), findSet(y));
}*/

bool isSameSet(int x, int y)
{
    return findSet(x) == findSet(y);
}

void tarjan(int u)
{
    dfs_low[u] = dfs_num[u] = counter++;
    S.pb(u);
    visited[u] = true;
    vi::iterator li;
    for (li = directed[u].begin(); li != directed[u].end(); ++li)
    {
        if (!dfs_num[*li])
            tarjan(*li);
        if (visited[*li])
            dfs_low[u] = min(dfs_low[u], dfs_low[*li]);
    }
    if (dfs_low[u] == dfs_num[u])
    {
        int resp = 0;
        while (true)
        {
            int vertex = S.back();
            S.pop_back();
            resp++;
            if (u == vertex)
                break;
        }
        if (resp == V)
            flag = true;
    }
}

void PointBridge(int u)
{
    vi::iterator i;
    dfs_low[u] = dfs_num[u] = counter++;
    for (i = undirected[u].begin(); i != undirected[u].end(); ++i)
    {
        if (!dfs_num[*i])
        {
            ans++;
            dfs_parent[*i] = u;
            PointBridge(*i);
            if (dfs_low[*i] > dfs_num[u])
                if (isSameSet(u, *i))
                    ok = true;
            dfs_low[u] = min(dfs_low[u], dfs_low[*i]);
        }
        else if (*i != dfs_parent[u])
            dfs_low[u] = min(dfs_low[u], dfs_num[*i]);
    }
}

int main()
{
    int a, b, t;
    while (!cin.eof())
    {
        cin >> V >> E;

        initialize();
        ans = counter = flag = ok = counter = 0;
        for (int i = 0; i < E; i++)
        {
            cin >> a >> b >> t;

            if (t == 1)
            {
                directed[a - 1].push_back(b - 1);
            }
            else
            {
                directed[a - 1].push_back(b - 1);
                directed[b - 1].push_back(a - 1);
            }

            //no grafo nao direcionado eu adicio ida e volta
            undirected[a - 1].push_back(b - 1);
            undirected[b - 1].push_back(a - 1);
        }
        tarjan(0);
        if (flag)
            printf("-\n");
        else
        {
            for (int i = 0; i < V; ++i)
                dfs_low[i] = dfs_num[i] = 0;
            counter = 0;
            PointBridge(0);
            if (ans != V)
                printf("*\n");
            else
            {
                if (ok)
                    printf("2\n");
                else
                    printf("1\n");
            }
        }
    }
    return 0;
}
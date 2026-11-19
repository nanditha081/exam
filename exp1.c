#include <stdio.h>
#include <stdlib.h>

int comparator(const void *p1, const void *p2)
{
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] =
        findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskalAlgo(int vertices, int edgesCount, int edge[][3])
{
    qsort(edge, edgesCount, sizeof(edge[0]), comparator);

    int parent[vertices];
    int rank[vertices];

    makeSet(parent, rank, vertices);

    int minCost = 0;

    printf("Following are the edges in the constructed MST\n");

    for (int i = 0; i < edgesCount; i++) {

        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if (v1 != v2) {

            unionSet(v1, v2, parent, rank);

            minCost += wt;

            printf("%d -- %d == %d\n",
                   edge[i][0],
                   edge[i][1],
                   wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main()
{
    int edge[][3] = {
        {0, 1, 2},
        {2, 3, 2},
        {1, 2, 4},
        {0, 3, 6}
    };

    int vertices = 4;
    int edgesCount = 4;

    kruskalAlgo(vertices, edgesCount, edge);

    return 0;
}

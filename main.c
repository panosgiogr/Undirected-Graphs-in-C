/*  Author : Panagiotis Giovanos
       SDI : *******
    Lesson : K08 - Data Structures and Programming Techniques
  Question : *                                                */

#include <stdio.h>
#include "ST.h"

int main()
{
    Graph G;
    Initialize(&G);
    int e; scanf("%d", &e);
    for (int i = 0; i < e ; ++i) {
        int S,D;
        scanf("%d-%d", &S, &D);
        InsertEdge(S,D,&G); //Insert Edge in Undirected Graph
    }
    printf("Vertex X : Adjacency List\n");
    Print(&G);
    BreadthFirst(G,1);
    ConnectedComponents(&G,1);
    IsConnected(&G,1);
    ShortestPaths(1,5);
    return  0;
}

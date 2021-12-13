/*  Author : Panagiotis Giovanos
       SDI : *******
    Lesson : K08 - Data Structures and Programming Techniques
  Question : *                                                */

#include <stdio.h>
#include <stdlib.h>
#include "GraphTypes.h"

int intArray[MAXVERTEX];
int itemCount = 0;

int isEmpty() {
    return itemCount == 0;
}

int isFull() {
    return itemCount == MAXVERTEX;
}

int size() {
    return itemCount;
}

void insert(int data) {
    intArray[itemCount++] = data;
}

void removeData() {
    for (int i = 0; i < itemCount ; ++i) {
        intArray[i] = intArray[i+1];
    }
    if(itemCount>0)itemCount--;
}

int removeData_Re() {
    int return_int = intArray[0];
    for (int i = 0; i < itemCount ; ++i) {
        intArray[i] = intArray[i+1];
    }
    if(itemCount>0)itemCount--;
    return return_int;
}
void Insert(Vertex V){
    insert(V);
}

void Remove(){
    removeData();
}

int Remove_R(){
    return removeData_Re();
}

int Empty()
{
    return isEmpty();
}

void Visit(Vertex V)
{
    printf("%d ",V);
}

void print_queue()
{
    printf("Queue : ");
    for (int i = 0; i < itemCount; ++i) {
        printf("%d ",intArray[i]);
    }
}
int not_in_q(Vertex v)
{
    int found =1;
    for (int i = 0; i < itemCount; ++i) {
        if (intArray[i]==v) found = 0;
    }
    return found;
}
void BreadthFirst(Graph G, int V)
{
    printf("BFS : \n");
    Boolean visited[MAXVERTEX];
    Vertex u, w;
    Edge *curedge;
    //initialize values
    for (int v = 0; v < MAXVERTEX; v++) {
        Edge *temp = G.firstedge[v];
        if(temp!=NULL) {
            visited[v]=FALSE;
        }
    }

    for (u = 0; u < MAXVERTEX; u++) {
        if(G.firstedge[u]!=NULL) {
            if (!visited[u]) {
                insert(u);
                do {
                    removeData();
                    if (!visited[u]) {
                        visited[u] = TRUE;
                        Visit(u);
                        removeData();
                    }
                    curedge = G.firstedge[u]; // curedge is a pointer to the first edge (v,_) of V
                    while (curedge) {
                        w = curedge->endpoint; // w is a successor of v and (v,w) is the current edge
                        if (!visited[w]) {
                            insert(w);
                            visited[w] = TRUE;
                            Visit(w);
                        }
                        curedge = curedge->nextedge; //curedge is a pointer to the next edge (v,_) of V
                    }
                } while (!Empty());
            }
        }
    }
    printf("\n");
}

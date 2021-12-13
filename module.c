/*  Author : Panagiotis Giovanos
       SDI : *******
    Lesson : K08 - Data Structures and Programming Techniques
  Question : *                                                */

#include <stdio.h>
#include <stdlib.h>
#include "GraphTypes.h"

static Edge head;
typedef struct edge* link;
int adj[MAXVERTEX][MAXVERTEX]; //Adjacency Matrix
int p[MAXVERTEX];   //predecessor of each vertex in sortest path
int Path_Lenght[MAXVERTEX];
int VISITED[MAXVERTEX];
int Is_Connected_Status = -1;  //-1 = haven't run
int Connected_Components = -1; //-1 = haven't run
int intArray2[MAXVERTEX];
int Queue_Item_Count = 0;


// Print the graph
void Print(Graph *graph) {
    int v;
    for (v = 0; v < MAXVERTEX; v++) {
        Edge *temp = graph->firstedge[v];
        if(temp!=NULL) {
            printf("Vertex %d : ", v);
            while (temp) { //While temp->nextedge != NULL
                printf("%d", temp->endpoint);
                temp = temp->nextedge;
                if(temp!=NULL) printf(" *-> ");
            }
            printf("\n");
        }
    }
}

void SortAdj(Graph *G,int S)
{
    Edge *edge=G->firstedge[S];
    Edge *temp = NULL;
    int tempvar;//temp variable to store node data
    //temp = node;//temp node to hold node data and next link
    while(edge != NULL)
    {
        temp=edge;
        while (temp !=NULL)//travel till the second last element
        {
            if(temp->endpoint > temp->nextedge->endpoint)// compare the data of the nodes
            {
                tempvar = temp->endpoint;
                temp->endpoint = temp->nextedge->endpoint;// swap the data
                temp->nextedge->endpoint = tempvar;
            }
            temp = temp->nextedge;    // move to the next element
        }
        edge = edge->nextedge;    // move to the next node
    }
    G->firstedge[S] = edge;
}
//sortList() will sort nodes of the list in ascending order
void sortList(Graph *G,int S) {
    //Node c will point to head
    Edge *c = G->firstedge[S], *index = NULL;
    int temp;
    while(c != NULL) {
        //Node index will point to node next to c
        index = c->nextedge;
        while(index != NULL) {
            //If c node'S data is greater than index'S node data, swap the data between them
            if(c->endpoint > index->endpoint) {
                temp = c->endpoint;
                c->endpoint = index->endpoint;
                index->endpoint = temp;
            }
            index = index->nextedge;
        }
        c = c->nextedge;
    }
}
void Initialize(Graph *G) {
    G->n=0;
    for (int i = 0; i < MAXVERTEX; ++i) {
        G->firstedge[i] = malloc(sizeof(Edge));
        G->firstedge[i] = NULL;
    }
}

link new_edge(int dst) {
    Edge *edge = (link) malloc(sizeof(Edge));

    edge->endpoint = dst;
    edge->nextedge = NULL;
    return edge;
}
int V[MAXVERTEX];

void count_V(Graph *G){
    int Count=0;
    int v;
    for (v = 0; v < MAXVERTEX; v++) {
        Edge *temp = G->firstedge[v];
        if(temp!=NULL) { Count++; temp = temp->nextedge;}
    }
    G->n = Count;
}

void InsertEdge(Vertex S, Vertex D, Graph *G) {
    Edge *New_Edge = new_edge(D);
    New_Edge->nextedge = G->firstedge[S];
    G->firstedge[S] = New_Edge;
    sortList(G,S);

    //undirected
    New_Edge = new_edge(S);
    New_Edge->nextedge = G->firstedge[D];
    G->firstedge[D] = New_Edge;
    sortList(G,D);
    //Update G->n
    count_V(G);

    //used for connected components , connected graph and shortest path algorithm
    adj[S][D]=1;
    adj[D][S]=1;
}

int Queue_isEmpty() {
    return Queue_Item_Count == 0;
}


void Queue_insert(int data) {
    intArray2[Queue_Item_Count++] = data;
}

int Queue_removeData() {
    int return_int = intArray2[0];
    for (int i = 0; i < Queue_Item_Count ; ++i) {
        intArray2[i] = intArray2[i+1];
    }
    if(Queue_Item_Count>0)Queue_Item_Count--;
    return return_int;
}


int n; //keeps G.n value

void BFS(int v);
void BF_Traversal(Graph *G,int Start)
{
    int v, cc = 0; // Connected Components
    for(v=0;v<n;v++)
        VISITED[v] = 1;

    cc++;
    BFS(Start); // start BFS from given vertex/Start

    for(v=Start; v<n; v++) {
        if(VISITED[v] == 1) {
            cc++; BFS(v);
        }
    }

    Connected_Components = cc;
    if(cc == 1)
        Is_Connected_Status = 0; //Not Connected Graph
    else
        Is_Connected_Status = 1; //Connected Graph

}

void BFS(int v) {
    Queue_insert(v);
    VISITED[v] = 2;
    while(!Queue_isEmpty()) {
        v = Queue_removeData();
        VISITED[v] = 3;
        for(int i=0; i<n; i++) {
            if( adj[v][i] == 1 && VISITED[i] == 1) {
                Queue_insert(i);
                VISITED[i] = 2;
            }
        }
    }
}

//Returns temporary vertex with minimum value of path cost
int min_temp() {
    int i;
    int min = 99999;
    int k = -1;
    for(i=0;i<n;i++) {
        if(VISITED[i] == 0 && Path_Lenght[i] < min) {
            min = Path_Lenght[i]; k = i;
        }
    } return k;
}

void Shortest_Path_Source(int S)
{
    //Dijkstra's Algorithm
    int i,c;

    //Make all leghts infinity 
    for(i=0; i<n; i++) {
        p[i] =  -1;
        Path_Lenght[i] = 99999;
        VISITED[i] = 0;
    }
    
    Path_Lenght[S] = 0;

    while(1) //for ever until 
    {
        c = min_temp(); //current == -1
        if(c == -1) return;
        VISITED[c] = 1;

        for(i=0; i<n; i++) {
            if ( adj[c][i] !=0 && VISITED[i] == 0 ) {
                if (Path_Lenght[c] + adj[c][i] < Path_Lenght[i]) {
                    p[i] = c; Path_Lenght[i] = Path_Lenght[c] + adj[c][i];
                }
            }
        }
    }
}

void ShortestPaths(int S, int D)
{
    int i,u;
    //shortest shortest_path
    int shortest_path[MAXVERTEX];
    int shortest_path_cost = 0;     
    int count = 0;
    int D_Temp = D;

    //Run Dijkstra's algorithm for Shortest shortest_path finding
    Shortest_Path_Source(S);

    //Fill shortest_path array
    while(D != S) {
        count++;
        shortest_path[count] = D; u = p[D];
        shortest_path_cost  += adj[u][D]; D = u;
    }
    count++;
    shortest_path[count]=S;

    printf("\nShortest Path from Vertex %d to Vertex %d is   : ",S,D_Temp);
    for(i=count; i>=1; i--) {
        printf("%d ", shortest_path[i]);
        if(i-1!=0) printf(" *-> ");
    }
    printf("\nYou have to traver %d Nodes to reach Vertex %d :      ", shortest_path_cost,D_Temp);
    for(i=count; i>=2; i--)
        printf("*-^    ");
    printf("\n");
}

void IsConnected(Graph *G,int Start) {
    if(Is_Connected_Status==-1) {
        n = G->n; BF_Traversal(G,Start);
    }
    if(Is_Connected_Status == 0)
        printf("Connected Graph\n");
    else
        printf("Not a Connected Graph\n");
}

void ConnectedComponents(Graph *G,int Start) {
    if(Connected_Components==-1) {
        n = G->n; BF_Traversal(G,Start);
    }
    printf("Connected Components = %d\n",Connected_Components);
}
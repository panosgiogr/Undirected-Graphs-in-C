#pragma once //Fixes Include Warnings in Linking
#include "GraphTypes.h"
void Initialize(Graph*);
void InsertEdge(Vertex, Vertex, Graph*);
void Print(Graph*);
void BreadthFirst(Graph,Vertex);
void ShortestPaths(int, int);
void ConnectedComponents(Graph *,int);
void IsConnected(Graph *G,int);

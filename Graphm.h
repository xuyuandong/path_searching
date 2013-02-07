#ifndef GRAPHM_H
#define GRAPHM_H

#define unvisited 0
#define visited 1
#define INFINITY_G 9999

#include<iostream>
using namespace std;

#include "Edge.h"


class Graphm
{
 public:
  int numVertex;
  int numEdge;
  int *Mark;
  int **matrix;

  Graphm(int numVert);
  Graphm(int numVert,int* matrix_temp);
  ~Graphm()
    {
      for(int i=0;i<numVertex;i++)
	delete[]matrix[i];
      delete []matrix;
      delete []Mark;
    }
  bool IsEdge(Edge OneEdge);
  Edge FirstEdge(int oneVertex);
  Edge NextEdge(Edge preEdge);
  void setEdge(int from,int to,int weight);
  void delEdge(int from,int to);
}; 
#endif
   




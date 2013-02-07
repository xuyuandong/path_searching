#ifndef SHOTESTPATH_H
#define SHOTESTPATH_H
#include<iostream>
using namespace std;

#include "MinHeap.h"
#include "Graphm.h"
#include "Distance.h"
#include "Edge.h"
#include <vector>

class ShortestPath
{
 public:
  void Dijkstra(Graphm& G, int s,int &length,int* &path ,int ep);
};
#endif


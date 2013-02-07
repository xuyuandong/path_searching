#include<iostream>
using namespace std;

#include"Distance.h"

class MinHeap
{
 private:
  Distance * HeapArray;
  int CurrentSize;
  int MaxSize;
  void BuildHeap();
  void swap(int  position1,int  position2);
 public:
  MinHeap(const int n);
  ~MinHeap(){delete []HeapArray;};
  Distance RemoveMin();
  bool Insert(Distance & NewNode);
  void SiftUp(int position);
  void SiftDown(int left);
  bool empty();
};

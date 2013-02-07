#include "Graphm.h"

Graphm::Graphm(int numVert)
{
      int i,j;
      numVertex=numVert;
      numEdge=0;
      Mark=new int[numVertex];
      for(i=0;i<numVertex;i++)
	{
	  Mark[i]=unvisited;
	}
      matrix=(int**)new int *[numVertex];
      for(i=0;i<numVertex;i++)
	matrix[i]=new int[numVertex];
      for(i=0;i<numVertex;i++)
	for(j=0;j<numVertex;j++)
	  matrix[i][j]=0;
}

Graphm::Graphm(int numVert,int* matrix_temp)
{
      int i,j;
      //matrix_temp=new int[numVert*numVert];
      numVertex=numVert;
      numEdge=0;
      Mark=new int[numVertex];
      for(i=0;i<numVertex;i++)
	{
	  Mark[i]=unvisited;
	}
      matrix=(int**)new int *[numVertex];
      for(i=0;i<numVertex;i++)
	matrix[i]=new int[numVertex];
      for(i=0;i<numVertex;i++)
	for(j=0;j<numVertex;j++)
	  {
	    matrix[i][j]=matrix_temp[numVertex*i+j];
	    if(matrix[i][j]!=0)
	      numEdge++;
	  }

}

bool Graphm::IsEdge(Edge OneEdge)
{
     if(OneEdge.weight>0 && OneEdge.weight<INFINITY_G && OneEdge.to>=0)
	return true;
      else
	return false;
}

Edge Graphm:: FirstEdge(int oneVertex)
{
    Edge myEdge;
    myEdge.from=oneVertex;
    myEdge.to=-1;
    for(int i=0;i<numVertex;i++)
      {
	if(matrix[oneVertex][i]!=0)
	  {
	    myEdge.to=i;
	    myEdge.weight=matrix[oneVertex][i];
	    break;
	  }
      }
    return myEdge;
}

Edge Graphm::NextEdge(Edge preEdge)
{
    Edge myEdge;
    myEdge.from=preEdge.from;
    myEdge.to=-1;
    for(int i=preEdge.to+1;i<numVertex;i++)
      {
	if (matrix[preEdge.from][i]!=0)
	  {
	    myEdge.to=i;
	    myEdge.weight=matrix[preEdge.from][i];
	    break;
	  }
      }
    return myEdge;
}

void Graphm::setEdge(int from,int to,int weight)
{
    if(matrix[from][to]<=0)
	numEdge++;
    matrix[from][to]=weight;
}

void Graphm::delEdge(int from,int to)
{
    if(matrix[from][to]>0)
      numEdge--;
    matrix[from][to]=0;
}

#include "ShortestPath.h"


void ShortestPath::Dijkstra(Graphm& G, int s,int &length,int * & path,int ep)//int s:startpoint,int ep:end point
{
  Distance* D=new Distance[G.numVertex];
  int i;
  for(i=0;i<G.numVertex;i++)
    {
      G.Mark[i]=unvisited;
      D[i].index=i;
      D[i].length=INFINITY_G;
      D[i].pre=s;
    }
  D[s].length=0;
  MinHeap H(G.numEdge);
  H.Insert(D[s]);
  for(i=0;i<G.numVertex;i++)
    {
      bool found=false;
      Distance d;
      while (!H.empty())
	{
	  d=H.RemoveMin();
	  if(G.Mark[d.index]==unvisited)
	    {
	      found=true;
	       break;
	    }
	}
      
      if(!found)
	break;

      int v=d.index;
      G.Mark[v]=visited;

      for (Edge e=G.FirstEdge(v);G.IsEdge(e);e=G.NextEdge(e))
	{
	  if(D[e.to].length>(D[v].length+e.weight) && G.Mark[e.to]==unvisited)
	    {
	      D[e.to].length = D[v].length+e.weight;
	      D[e.to].pre = v;
	      H.Insert(D[e.to]);
	    }
	}
    }

  

	for(i=0;i<G.numVertex;i++)
	{
		if(D[i].index==ep)
			break;
	}
  //int* path_temp = new int [G.numVertex];
  vector<int> path_temp;
  //for(i=0;i<G.numVertex-1;i++)
     // path_temp[i]=-1;
  path_temp.push_back(ep);
 for(;i>=0 && D[i].pre!=s;)
    {
    	path_temp.push_back(D[i].pre);
	i=D[i].pre;
    }
 path_temp.push_back(D[i].pre);
 length=path_temp.size();
  for(int j=0;j<length;j++)
    {
      i=length-1-j;
      path[j]=path_temp[i];
    }

}
  




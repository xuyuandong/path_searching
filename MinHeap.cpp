#include"MinHeap.h"

void MinHeap::BuildHeap()
{
  for(int i=CurrentSize/2-1;i>=0;i--)
    SiftDown(i);
}

void MinHeap::swap(int position1, int position2)
{
  Distance  temp;
  temp=HeapArray[position1];
  HeapArray[position1]=HeapArray[position2];
  HeapArray[position2]=temp;
}

MinHeap::MinHeap(const int n)
{
  if(n<=0)
    return;
  CurrentSize=0;
  MaxSize=n;
  HeapArray=new Distance[MaxSize];
  BuildHeap();
}

Distance MinHeap::RemoveMin()
{
  int temp=0; 
  if(CurrentSize==0)
    {
      cout<<"cann't delete"<<endl;
      exit(1);
    }
  else
    {     
      CurrentSize=CurrentSize-1;
      swap(0,CurrentSize);
      if(CurrentSize>1)
	SiftDown(0);
      return HeapArray[CurrentSize];
    }
}

bool MinHeap::Insert(Distance & NewNode)
{
  if(CurrentSize==MaxSize)
    return false;
  HeapArray[CurrentSize]=NewNode;
  SiftUp(CurrentSize);
  CurrentSize++;
  return true;
}

void MinHeap::SiftUp(int position)
{
  int position_temp=position;
  Distance temp=HeapArray[position_temp];
  while ((position_temp>0)&&(HeapArray[(position_temp-1)/2].length>temp.length))
			   {
			     HeapArray[position_temp]=HeapArray[(position_temp-1)/2];
			     position_temp=(position_temp-1)/2;
			   }
  HeapArray[position_temp]=temp;
}

void MinHeap::SiftDown(int left)
{
  int i=left;
  int j=2*i+1;
  Distance temp=HeapArray[i];
  while (j<CurrentSize)
    {
      if((j<CurrentSize-1)&&(HeapArray[j].length>HeapArray[j+1].length))
	j++;
      if(temp.length>HeapArray[j].length)
	{
	  HeapArray[i]=HeapArray[j];
	  i=j;
	  j=2*j+1;
	}
      else
	break;
    }
  HeapArray[i]=temp;
}

bool MinHeap::empty()
{
  if(CurrentSize==0)
    return 1;
  else
    return 0;
}

#pragma warning(disable:4996)
#include<fstream>
#include<iostream>
#include<ctime>
using namespace std;

struct Bridge
{
	int city1;
	int city2;
	int cost;
};
int numIslands,numBridges;
int cities[3];
Bridge *bridges;
int way[3];
int *cost;
bool *mark;

void dijkstra(int start, int end1, int d);
//void dijkstra(int start, int end1, int end2);

void input(char fileName[])
{
	FILE * file=0;
	file = fopen(fileName, "r");
	if(!file)
	{
		cout<<"File "<<fileName<<" not found!"<<endl;
		system("pause");
		exit(1);
	}
	fscanf(file, "%d%d", &numIslands, &numBridges);
	mark = new bool[numIslands];
	cost = new int[numIslands];
	bridges = new Bridge[numBridges];
	for(int i = 0; i < numIslands; i++)
	{	
		cost[i] = INT_MAX;
		mark[i] = true;
	}
	int city1,city2,tempCost;
	for(int i = 0; i < numBridges; i++)
	{
		fscanf(file, "%d%d%d", &city1, &city2, &tempCost);
		if(city1 < city2)
		{
			bridges[i].city1 = city1;
			bridges[i].city2 = city2;
			bridges[i].cost = tempCost;
		}
		else
		{
			bridges[i].city1 = city2;
			bridges[i].city2 = city1;
			bridges[i].cost = tempCost;
		}
	}
	way[0] = way[1] = way[2] = -1;
	fscanf(file, "%d%d%d", &cities[0], &cities[1], &cities[2]);
	fclose(file);
}

int changeCurrentCity()
{
	int min=INT_MAX;
	int minIndex=-1;
	for(int i=0;i<numIslands;i++)
	{
		if( (mark[i])  && (cost[i] < min) )
		{
			min = cost[i];
			minIndex = i;
		}
	}
	return minIndex;
}

//void dijkstra(int start, int end1, int end2)
//{
//	int currentCity = start;
//	mark[currentCity]=false;
//	cost[currentCity] = 0;
//	while( ( (way[0] < 0) || (way[1] < 0) ) && (currentCity > -1) )
//	{
//		for (int i = 0; i < numBridges; i++)
//		{
//
//			if( (bridges[i].city1 == currentCity) && mark[bridges[i].city2] &&  ( (cost[currentCity] + bridges[i].cost) < cost[bridges[i].city2]) )
//			{
//				cost[bridges[i].city2] = cost[currentCity] + bridges[i].cost;
//				//way[i] = currentCity; 
//			}
//			if( (bridges[i].city2 == currentCity) && mark[bridges[i].city1] && ( (cost[currentCity] + bridges[i].cost) < cost[bridges[i].city1]) )
//			{
//				cost[bridges[i].city1] = cost[currentCity] + bridges[i].cost;
//				//way[i] = currentCity; 
//			}
//
//		}
//		currentCity = changeCurrentCity();
//		if(currentCity!=-1)
//			mark[currentCity] = false;
//		if(currentCity == end1)
//			way[0] = cost[currentCity];
//		if(currentCity == end2)
//			way[1] = cost[currentCity];
//	}
//	for(int i = 0; i < numIslands; i++)
//	{	
//		cost[i] = INT_MAX;
//		mark[i] = true;
//	}
//}

void dijkstra(int start, int end1, int d)
{
	int currentCity = start;
	mark[currentCity]=false;
	cost[currentCity] = 0;
	while( ( way[2] < 0) && (currentCity > -1) )
	{
		for (int i = 0; i < numBridges; i++)
		{

			if( (bridges[i].city1 == currentCity) && mark[bridges[i].city2] &&  ( (cost[currentCity] + bridges[i].cost) < cost[bridges[i].city2]) )
			{
				cost[bridges[i].city2] = cost[currentCity] + bridges[i].cost;
				//way[i] = currentCity; 
			}
			if( (bridges[i].city2 == currentCity) && mark[bridges[i].city1] && ( (cost[currentCity] + bridges[i].cost) < cost[bridges[i].city1]) )
			{
				cost[bridges[i].city1] = cost[currentCity] + bridges[i].cost;
				//way[i] = currentCity; 
			}

		}
		currentCity = changeCurrentCity();
		if(currentCity!=-1)
			mark[currentCity] = false;
		if(currentCity == end1)
			way[d] = cost[currentCity];
	}
	for(int i = 0; i < numIslands; i++)
	{	
		cost[i] = INT_MAX;
		mark[i] = true;
	}
}

int min()
{
	if( way[0] < way[1])
	{
		return way[0] + (way[1]<way[2]?way[1]:way[2]);
	}
	else
	{
		return way[1] + (way[0]<way[2]?way[0]:way[2]);
	}
}

int main()
{
	input("input.txt");
	dijkstra(cities[0], cities[1], 0);
	dijkstra(cities[1], cities[2], 1);
	dijkstra(cities[0], cities[2], 2);
	//dijkstra(cities[1], cities[2]);
	ofstream out("output.txt");
	out<<min()<<endl;
	out.close();
	delete cost;
	delete mark;
	delete bridges;
	system("pause");
	return 0;
}
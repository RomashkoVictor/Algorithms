#pragma warning(disable:4996)
#include<fstream>
#include<iostream>
#include<ctime>
using namespace std;

int numIslands,numBridges;
int cities[3];
int **bridges;
int way[3];
int *cost;
bool *mark;

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
	bridges = new int*[numIslands];
	for(int i = 0; i < numIslands; i++)
		bridges[i] = new int[numIslands];
	for(int i = 0; i < numIslands; i++)
	{	
		for( int j = 0; j < numIslands; j++)
			bridges[i][j] = -1;
		bridges[i][i] = 0;
		cost[i] = INT_MAX;
		mark[i] = true;
	}
	int city1,city2,tempCost;
	for(int i = 0; i < numBridges; i++)
	{
		fscanf(file, "%d%d%d", &city1, &city2, &tempCost);
		bridges[city1][city2] = tempCost;
		bridges[city2][city1] = tempCost;
	}
	way[0] = way[1] = way[2] = -10;
	fscanf(file, "%d%d%d", &cities[0], &cities[1], &cities[2]);
	fclose(file);
}

int changeCurrentCity()
{
	int min=-1;
	for(int i=0;i<numIslands;i++)
	{
		if((mark[i])&&(cost[i]!=INT_MAX))
		{
			min=i;
			for (; i < numIslands; i++)
				if( (mark[i]) && (cost[i] < cost[min]) )
					min=i;
		}
	}
	return min;
}

void dijkstra(int start, int end1, int end2)
{
	int currentCity = start;
	cost[currentCity] = 0;
	while( ( (way[0] < 0) || (way[1] < 0) ) && (currentCity > -1) )
	{
		for (int i = 0; i < numIslands; i++)
		{
			if (mark[i])
			{
				if ( (bridges[currentCity][i] > 0) && ( (cost[currentCity] + bridges[currentCity][i]) < cost[i]) )
				{
					cost[i] = cost[currentCity] + bridges[currentCity][i];
					//way[i] = currentCity; 
				}
			}
		}
		currentCity = changeCurrentCity();
		if(currentCity!=-1)
			mark[currentCity] = false;
		if(currentCity == end1)
			way[0] = cost[currentCity];
		if(currentCity == end2)
			way[1] = cost[currentCity];
	}
	for(int i = 0; i < numIslands; i++)
	{	
		cost[i] = INT_MAX;
		mark[i] = true;
	}
}

void dijkstra(int start, int end1)
{
	int currentCity = start;
	cost[currentCity] = 0;
	while( (way[2] < 0) && (currentCity > -1) )
	{
		for (int i = 0; i < numIslands; i++)
		{
			if (mark[i])
			{
				if ( (bridges[currentCity][i] > 0) && ( (cost[currentCity] + bridges[currentCity][i]) < cost[i]) )
				{
					cost[i] = cost[currentCity] + bridges[currentCity][i];
					//way[i] = currentCity; 
				}
			}
		}
		currentCity = changeCurrentCity();
		if(currentCity!=-1)
			mark[currentCity] = false;
		if(currentCity == end1)
			way[2] = cost[currentCity];
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
	dijkstra(cities[0], cities[1], cities[2]);
	dijkstra(cities[1], cities[2]);
	ofstream out("output.txt");
	out<<min()<<endl;
	out.close();
	delete cost;
	delete mark;
	for(int i = 0; i < numIslands; i++)
		delete bridges[i];
	delete bridges;
	system("pause");
	return 0;
}
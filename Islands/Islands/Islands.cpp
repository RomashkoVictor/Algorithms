#pragma warning(disable:4996)
#include<fstream>
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

struct Bridges
{
	int *last;
	int *city1;
	int *city2;
	int *cost;
	int *pred;
	int numBridges;
	int numIslands;
}bridges;

long long **islands;
int cities[3];
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
	fscanf(file, "%d%d", &bridges.numIslands, &bridges.numBridges);
	islands = new long long*[bridges.numIslands];
	for(int i = 0; i < bridges.numIslands; i++)
	{
		islands[i] = new long long[3];
		islands[i][0] = islands[i][1] = islands[i][2] = LLONG_MAX;
	}
	mark = new bool[bridges.numIslands];
	for(int i = 0; i < bridges.numIslands; i++)
		mark[i] = true;
	bridges.last = new int[bridges.numIslands];
	bridges.cost = new int[bridges.numBridges*2];
	bridges.city1 = new int[bridges.numBridges*2];
	bridges.city2 = new int[bridges.numBridges*2];
	bridges.pred = new int[bridges.numBridges*2];
	for(int i = 0; i < bridges.numIslands; i++)
		bridges.last[i] = -1;
	int city1,city2,tempCost;
	for(int i = 0; i < bridges.numBridges; i++)
	{
		fscanf(file, "%d%d%d", &city1, &city2, &tempCost);
		bridges.city1[2*i] = city1;
		bridges.city2[2*i] = city2;
		bridges.cost[2*i] = tempCost;
		bridges.city1[2*i+1] = city2;
		bridges.city2[2*i+1] = city1;
		bridges.cost[2*i+1] = tempCost;
		if( bridges.last[city1] == -1)
		{
			bridges.last[city1] = 2*i;
			bridges.pred[2*i] = -1;
		}
		else
		{
			bridges.pred[2*i] = bridges.last[city1];
			bridges.last[city1] = 2*i;
		}
		if( bridges.last[city2] == -1)
		{
			bridges.last[city2] = 2*i+1;
			bridges.pred[2*i+1] = -1;
		}
		else
		{
			bridges.pred[2*i+1] = bridges.last[city2];
			bridges.last[city2] = 2*i+1;
		}
	}
	fscanf(file, "%d%d%d", &cities[0], &cities[1], &cities[2]);
	fclose(file);
}

void solve(int start, int time)
{
	vector<int> newIslands;
	vector<int> current;
	current.push_back(start);
	mark[start]=false;
	islands[start][time] = 0;
	for(int i = 1; i < bridges.numIslands; i++)
	{
		int j = 0;
		while( current.size() != j )
		{
			int temp = bridges.last[ current[j] ];
			while(temp != -1)
			{
				long long t = (long long)bridges.cost[ temp ] + islands[current[j]][time];
				if(islands[ bridges.city2[ temp ] ][time] > t)
					islands[ bridges.city2[ temp ] ][time] = t;
				if(mark[ bridges.city2[ temp ] ])
				{
					newIslands.push_back(bridges.city2[ temp ]);
					mark[ bridges.city2[ temp ] ] = false;
				}
				temp = bridges.pred[ temp ];
			}
			j++;
		}
		current = newIslands;
		newIslands.clear();
	}
	for(int i = 0; i < bridges.numIslands; i++)
		mark[i] = true;
}

long long min()
{
	long long min = LLONG_MAX;
	for(int i = 0; i < bridges.numIslands; i++)
	{
		if(islands[i][0] + islands[i][1] + islands[i][2] < min)
			min = islands[i][0] + islands[i][1] + islands[i][2];
	}
	return min;
}
int main()
{
	input("input.txt");
	solve(cities[0],0);
	solve(cities[1],1);
	solve(cities[2],2);
	ofstream out("output.txt");
	out<<min()<<endl;
	out.close();
	delete bridges.last;
	delete bridges.city1;
	delete bridges.city2;
	delete bridges.cost;
	delete bridges.pred;
	system("pause");
	return 0;
}
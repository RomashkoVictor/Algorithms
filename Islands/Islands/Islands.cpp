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
	bridges = new Bridge[numBridges];
	for(int i = 0; i < numBridges; i++)
		fscanf(file, "%d%d%d", &bridges[i].city1, &bridges[i].city2, &bridges[i].cost);
	fscanf(file, "%d%d%d", &cities[0], &cities[1], cities[2]);
	fclose(file);
}

void dijkstra(int start)
{

}

int main()
{
	input("input.txt");

	delete bridges;
	system("pause");
	return 0;
}
#include<fstream>
#include<iostream>
#include<ctime>
using namespace std;
#pragma warning(disable:4996)

int n,m,k,l;
int **array;
bool **mark;

void input(char fileName[])
{
	FILE * file=0;
	file = fopen (fileName , "r");
	if(!file)
	{
		cout<<"File "<<fileName<<" not found!"<<endl;
		system("pause");
		exit(1);
	}
	fscanf(file,"%d%d%d%d",&n,&m,&k,&l);
	array = new int* [n];
	mark = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		array[i] = new int [m];
		mark[i] = new bool [m];
		for (int j = 0; j < m; j++)
			fscanf(file,"%d",&array[i][j]);
	}
}
void output(char fileName[])
{
	FILE * file=0;
	file = fopen (fileName , "w");
	if (!file)
	{
		cout<<"File "<<fileName<<" not created!"<<endl;
		system("pause");
		exit(1);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			fscanf(file,"%d",&array[i][j]);
	}
	for (int i = 0; i < n; i++)
	{
		delete array[i];
		delete mark[i];
	}
	delete array;
	delete mark;
}
int main()
{
	int start=clock();
	input("floodit.in");
	int input=clock();
	output("floodit.out");
	int output=clock();
	cout<<"time: "<< clock()-start<<" input: "<<input-start<<" output: "<<output-input<<endl;
	system("pause");
	return 0;
}
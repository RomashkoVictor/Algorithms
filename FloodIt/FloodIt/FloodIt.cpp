#include<fstream>
#include<iostream>
#include<ctime>
#include<list>
using namespace std;
#pragma warning(disable:4996)

struct Element
{
	bool mark;
	int colour;
	int i;
	int j;
};

int n,m,k,l;
Element *array;



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
	array = new Element [n*m];
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fscanf(file,"%d",&temp);
			array[i*n+j].colour=temp;
			array[i*n+j].mark=false;
			array[i*n+j].i=i;
			array[i*n+j].j=j;
		}
	}
	fclose(file);
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
		{
			fprintf(file,"%d ",array[i*n+j].colour);
		}
		fprintf(file,"\n");
	}
	fclose(file);
	delete array;
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
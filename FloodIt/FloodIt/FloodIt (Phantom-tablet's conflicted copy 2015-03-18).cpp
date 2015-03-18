#pragma warning(disable:4996)
#include<fstream>
#include<iostream>
#include<ctime>
#include<set>
#include<vector>
#pragma comment(linker, "/STACK:64777216")
using namespace std;

struct Element
{
	int colour;
	int i;
	int j;
	bool inBorder;
	bool operator < (const Element &obj)const
	{
		return colour<obj.colour;
	}
	bool operator >(const Element &obj)const
	{
		return colour>obj.colour;
	}
	bool operator ==(const Element &obj)const
	{
		return colour == obj.colour;
	}
	bool operator !=(const Element &obj)const
	{
		return colour != obj.colour;
	}
};

int n,m,k,l;
Element **array;
multiset<Element> border;
int *colours;

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
	colours = new int [l+1];
	array = new Element* [n+2];
	for (int i = 0; i < n+2; i++)
		array[i] = new Element[m+2];
	for (int i = 1; i < n+1; i++)
	{
		for (int j = 1; j < m+1; j++)
		{
			fscanf(file,"%d",&array[i][j].colour);
			array[i][j].i = i;
			array[i][j].j = j;
			array[i][j].inBorder = false;
		}
	}
	for (int j = 1; j < l+1; j++)
		fscanf(file,"%d",&colours[j]);
	for (int i = 0; i < n+2; i++)
	{
		array[i][0].colour = array[i][m+1].colour = -1;
		array[i][0].i = i;
		array[i][0].inBorder = false;
		array[i][m+1].i = i;
		array[i][m+1].j = m+1;
		array[i][m+1].inBorder = false;
	}
	for (int i = 0; i < m+2; i++)
	{
		array[0][i].colour = array[n+1][i].colour = -1;
		array[0][i].j = i;
		array[0][i].inBorder = false;
		array[n+1][i].j = i;
		array[n+1][i].i = n+1;
		array[n+1][i].inBorder = false;
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
	for (int i = 1; i < n+1; i++)
	{
		for (int j = 1; j < m+1; j++)
		{
			if(array[i][j].colour == -1)
				fprintf(file,"%d ",colours[l]);
			else
				fprintf(file,"%d ",array[i][j].colour);
		}
		fprintf(file,"\n");
	}
	fclose(file);
	delete colours;
	for (int i = 0; i < n+2; i++)
		delete array[i];
	delete array;
}
void addElementToBorder(Element& obj, int colour)
{
	obj.colour = -1;
	array[obj.i][obj.j].colour = -1;
	obj.inBorder = false;
	array[obj.i][obj.j].inBorder = false;
	if (array[obj.i][obj.j-1].colour == colour)
		addElementToBorder(array[obj.i][obj.j-1],colour);
	else
	{
		if ( (array[obj.i][obj.j-1].colour != -1) && (!array[obj.i][obj.j-1].inBorder) )
		{
			array[obj.i][obj.j-1].inBorder = true;
			border.insert(array[obj.i][obj.j-1]);
		}
	}
	if (array[obj.i][obj.j+1].colour == colour)
		addElementToBorder(array[obj.i][obj.j+1],colour);
	else
	{
		if ( (array[obj.i][obj.j+1].colour != -1) && (!array[obj.i][obj.j+1].inBorder) )
		{
			array[obj.i][obj.j+1].inBorder = true;
			border.insert(array[obj.i][obj.j+1]);
		}
	}
	if (array[obj.i-1][obj.j].colour == colour)
		addElementToBorder(array[obj.i-1][obj.j],colour);
	else
	{
		if ( (array[obj.i-1][obj.j].colour != -1) && (!array[obj.i-1][obj.j].inBorder) )
		{
			array[obj.i-1][obj.j].inBorder = true;
			border.insert(array[obj.i-1][obj.j]);
		}
	}
	if (array[obj.i+1][obj.j].colour == colour)
		addElementToBorder(array[obj.i+1][obj.j],colour);
	else
	{
		if ( (array[obj.i+1][obj.j].colour != -1) && (!array[obj.i+1][obj.j].inBorder) )
		{
			array[obj.i+1][obj.j].inBorder = true;
			border.insert(array[obj.i+1][obj.j]);
		}
	}
}
void algorithm()
{
	colours[0]=array[1][1].colour;
	array[1][1].colour=-1;
	border.insert(array[1][2]);
	border.insert(array[2][1]);
	array[1][2].inBorder = true;
	array[2][1].inBorder = true;
	Element temp;
	vector<Element> currentEl;
	for (int j = 0; j < l+1; j++)
	{
		temp.colour = colours[j];
		multiset<Element>::iterator it= border.lower_bound(temp);
		if(it != border.end())
		{
			for (;(it != border.end()) && ((*it).colour == colours[j]); it++)
			{
				currentEl.push_back(*it);
			}
			border.erase(temp);
			for (int i = 0; i < currentEl.size(); i++)
			{
				addElementToBorder(currentEl[i],colours[j]);
			}
			currentEl.clear();
		}
	}
}
int main()
{
	int start=clock();
	input("floodit3.in");
	int input=clock();
	algorithm();
	int alg=clock();
	output("floodit.out");
	int output=clock();
	cout<<"time: "<< clock()-start<<" input: "<<input-start<<" output: "<<output-alg<<" alg: "<<alg-input<<endl;
	system("pause");
	return 0;
}
#pragma warning(disable:4996)
#include <fstream>
int domino1[6];
int domino2[6];
int dominoRot[6];
int sum;
int num;
int count;
int minSolve;
void input()
{
	FILE * file;
	file = fopen ("in.txt" , "r");
	fscanf(file,"%d",&num);
	int tempInputVal1=0,tempInputVal2=0;
	for(int i=0;i<num;i++)
	{
		fscanf(file,"%d",&tempInputVal1);
		fscanf(file,"%d",&tempInputVal2);
		int temp=tempInputVal1-tempInputVal2;
		if(temp<0)
			domino2[-temp-1]++;
		else if(temp>0)
			domino1[temp-1]++;
		sum+=temp;
	}
	minSolve=sum;
}
int abs(int a)
{
	return (a>0?a:-a);
}
int countRotations()
{
	for(int i=5;i>=0;i--)
	{
		if(domino1[i]*(i+1)*2<=sum)
		{
			sum-=domino1[i]*(i+1)*2;
			dominoRot[i]=domino1[i];
			count+=domino1[i];
			domino1[i]=0;
		}
		else
		{
			int temp=sum/((i+1)*2);
			domino1[i]-=temp;
			sum-=temp*(i+1)*2;
			dominoRot[i]+=temp;
			count+=temp;
		}
	}
	return 0;
}
int main()
{
	FILE * file;
	file = fopen ("in.txt" , "r");
	if (file == NULL) 
	{
		perror ("Error opening file");
		return 0;
	}
	input();
	if(sum<0)
	{
		sum=-sum;
		int temp;
		for(int i=0;i<6;i++)
		{
			temp=domino1[i];
			domino1[i]=domino2[i];
			domino2[i]=temp;
		}
	}
	fclose(file);
	std::ofstream out("out.txt");
	out<<countRotations()<<std::endl;
	out.close();
	return 0;
}
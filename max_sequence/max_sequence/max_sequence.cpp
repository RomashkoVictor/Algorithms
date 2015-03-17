#include <fstream>
#pragma warning(disable:4996)
int *mass = 0;
int *latestNum=0;
int input()
{
	FILE * file;
	file = fopen ("input.txt" , "r");
	int n = 0;
	int i=0;
	char buf = 0;
	int tempNumber = 0;
	bool existNumber = false;
	if (file == NULL) 
	{
		perror ("Error opening file");
		return 0;
	}
	else
	{ 
		fscanf(file,"%d",&n);
		mass=new int[n];
		for(int i=0;i<n;i++)
			fscanf(file,"%d",&mass[i]);
		fclose (file);
	}
	return n;
}
int binarySearch(int start, int end,int num)
{
	int temp=(end-start)/2+start;
	int start2=start;
	int end2=end;
	while(start2<=end2)
	{
		temp=(end2+start2)/2;
		if(num>latestNum[temp] && num<=latestNum[temp+1])
			return temp+1;
		else
			if(latestNum[temp]<num)
				start2=temp+1;
			else
				end2=temp-1;
	}
	return -1;
}
int findMaxWay( int num)
{
	int j=0;
	for(int i = 0; i < num; i++ )
	{
		j=binarySearch(0,i,mass[i]);
		latestNum[j] = mass[i];
	}
	j=binarySearch(0,num,INT_MAX-1);
	return j-1;
}
int main()
{
	int num = input();
	latestNum = new int[num+2];
	for( int i = 0; i < num+2; i++)
		latestNum[i] = INT_MAX;
	latestNum[0]=INT_MIN;
	std::ofstream out("output.txt");
	out<<findMaxWay( num );
	out.close();
	return 0;
}
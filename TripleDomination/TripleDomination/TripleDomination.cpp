#include<fstream>
#include<iostream>
#include<ctime>
#include<vector>
#include<queue>
#pragma warning(disable:4996)
using namespace std;
struct Team{
	int x;
	int y;
	int z;
};
bool sortX (Team obj1,Team obj2) { return (obj1.x < obj2.x); }
int counter;
int num;
vector<Team> teamsSortedX;
vector<Team> dominatedTeams;
struct sectionMin
{
	int miny;
	int minz;
}*tree;
int min(int a,int b)
{
	return (a<b?a:b);
}
int max(int a,int b)
{
	return (a>b?a:b);
}
void build (vector<Team> &a, int v, int tl, int tr) {
	if (tl == tr)
	{
		tree[v].miny = a[tl].y;
		tree[v].minz = a[tl].z;
	}
	else {
		int tm = (tl + tr) / 2;
		build (a, v*2, tl, tm);
		build (a, v*2+1, tm+1, tr);
		tree[v].miny = min(tree[v*2].miny,tree[v*2+1].miny);
		tree[v].minz = min(tree[v*2].minz,tree[v*2+1].minz);
	}
}
bool min(int v, int tl, int tr, int l, int r,sectionMin m) {
	//counter++;
	if ((l > r)||(tree[v].miny>=m.miny)||(tree[v].minz>=m.minz))
	{
		return false;
	}
	if (l == tl && r == tr)
	{
		if(l==r)
		{
			if((tree[v].miny<m.miny)&&(tree[v].minz<m.minz))
			{
				return true;
			}
			return false;
		}
	}
	int tm = (tl + tr) / 2;
	return ((min (v*2, tl, tm, l, min(r,tm),m)) || (min (v*2+1, tm+1, tr, max(l,tm+1), r,m)));
}
void dominated()
{
	for(int i=0;i<num;i++)
	{
	//	counter++;
		sectionMin t;
		t.miny=teamsSortedX[i].y;
		t.minz=teamsSortedX[i].z;
		if(!min(1,0,num-1,0,i,t))
			dominatedTeams.push_back(teamsSortedX[i]);
	}
}
void input()
{
	FILE * file;
	file = fopen ("input.txt" , "r");
	fscanf(file,"%d",&num);
	Team temp;
	for(int i=0;i<num;i++)
	{

		fscanf(file,"%d",&temp.x);
		fscanf(file,"%d",&temp.y);
		fscanf(file,"%d",&temp.z);
		teamsSortedX.push_back(temp);
	}
	sort(teamsSortedX.begin(),teamsSortedX.end(),sortX);
}

int main()
{
	//int time=clock();
	input();
	tree=new  sectionMin[num*4];
	//int tbild=clock();
	build(teamsSortedX,1,0,num-1);
	//int tbild2=clock();
	dominated();
	ofstream out("output.txt");
	out<<dominatedTeams.size()<<endl;
	//cout<<"time "<<clock()-time<<" tbild "<<tbild2-tbild<<" alg "<<clock()-tbild2<<endl;
	//cout<<"c "<<counter<<endl;
	//system("pause");
	return 0;
}


//#include<iostream>
//struct tq
//{
//	int min;
//	int max;
//};
//tq t[4*4]; 
//int min(int a,int b)
//{
//	return (a<b?a:b);
//}
//int max(int a,int b)
//{
//	return (a>b?a:b);
//}
//void build (int a[], int v, int tl, int tr) {
//	if (tl == tr)
//	{
//		t[v].min = a[tl];
//		t[v].max = a[tl];
//	}
//	else {
//		int tm = (tl + tr) / 2;
//		build (a, v*2, tl, tm);
//		build (a, v*2+1, tm+1, tr);
//		t[v].min = min(t[v*2].min,t[v*2+1].min);
//		t[v].max = max(t[v*2].max,t[v*2+1].max);
//	}
//}
//int min (int v, int tl, int tr, int l, int r) {
//	if (l > r)
//		return INT_MAX;
//	if (l == tl && r == tr)
//	{
//		return t[v].min;
//	}
//	int tm = (tl + tr) / 2;
//	return min(min (v*2, tl, tm, l, min(r,tm)), min (v*2+1, tm+1, tr, max(l,tm+1), r));
//}
//int main()
//{
//	int a[4];
//	for( int i=0; i<4;i++)
//		a[i]=i+1;
//	build(a,1,0,3);
//	int k=min(1,0,3,2,2);
//}

//#include<iostream>
//int t[12][12];
//int a[3][3];
//int m=4;
//int min(int a,int b)
//{
//	return (a<b?a:b);
//}
//int max(int a,int b)
//{
//	return (a>b?a:b);
//}
//int sum_y (int vx, int vy, int tly, int try_, int ly, int ry) {
//	if (ly > ry)
//		return 0;
//	if (ly == tly && try_ == ry)
//		return t[vx][vy];
//	int tmy = (tly + try_) / 2;
//	return sum_y (vx, vy*2, tly, tmy, ly, min(ry,tmy))
//		+ sum_y (vx, vy*2+1, tmy+1, try_, max(ly,tmy+1), ry);
//}
//
//// int sum (int v, int tl, int tr, int l, int r) {
////	if (l > r)
////		return 0;
////	if (l == tl && r == tr)
////		return t[v];
////	int tm = (tl + tr) / 2;
////	return sum (v*2, tl, tm, l, min(r,tm))
////		+ sum (v*2+1, tm+1, tr, max(l,tm+1), r);
////}
//int sum_x (int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
//	if (lx > rx)
//		return 0;
//	if (lx == tlx && trx == rx)
//		return sum_y (vx, 1, 0, m-1, ly, ry);
//	int tmx = (tlx + trx) / 2;
//	return sum_x (vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry)
//		+ sum_x (vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry);
//}
//void build_y (int vx, int lx, int rx, int vy, int ly, int ry) {
//	if (ly == ry)
//		if (lx == rx)
//			t[vx][vy] = a[lx][ly];
//		else
//			t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
//	else {
//		int my = (ly + ry) / 2;
//		build_y (vx, lx, rx, vy*2, ly, my);
//		build_y (vx, lx, rx, vy*2+1, my+1, ry);
//		t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
//	}
//}
// 
//void build_x (int vx, int lx, int rx) {
//	if (lx != rx) {
//		int mx = (lx + rx) / 2;
//		build_x (vx*2, lx, mx);
//		build_x (vx*2+1, mx+1, rx);
//	}
//	build_y (vx, lx, rx, 1, 0, m-1);
//}
//
//int main()
//{
//	for( int i=0; i<3;i++)
//		for(int j=0;j<3;j++)
//		a[i][j]=i+j+1;
//		build_x(1,0,2);
//	for( int i=0; i<3;i++)
//		for(int j=0;j<3;j++)
//		{
//			int res=sum_x(1,0,2,0,i,0,j);
//			std::cout<<res<<std::endl;
//		}
//
//	system("pause");
//}

//#include<iostream>
//int t[12][12];
//int a[3][3];
//int m=4;
//int min(int a,int b)
//{
//	return (a<b?a:b);
//}
//int max(int a,int b)
//{
//	return (a>b?a:b);
//}
//int min_y (int vx, int vy, int tly, int try_, int ly, int ry) {
//	if (ly > ry)
//		return INT_MAX;
//	if (ly == tly && try_ == ry)
//		return t[vx][vy];
//	int tmy = (tly + try_) / 2;
//	return min(min_y (vx, vy*2, tly, tmy, ly, min(ry,tmy)), min_y (vx, vy*2+1, tmy+1, try_, max(ly,tmy+1), ry));
//}
//
//int min_x (int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
//	if (lx > rx)
//		return INT_MAX;
//	if (lx == tlx && trx == rx)
//		return min_y (vx, 1, 0, m-1, ly, ry);
//	int tmx = (tlx + trx) / 2;
//	return min(min_x (vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry), min_x (vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry));
//}
//
////void build (vector<Team> &a, int v, int tl, int tr) {
////	if (tl == tr)
////	{
////		tree[v].min = a[tl].y;
////		tree[v].max = a[tl].z;
////	}
////	else {
////		int tm = (tl + tr) / 2;
////		build (a, v*2, tl, tm);
////		build (a, v*2+1, tm+1, tr);
////		tree[v].min = min(tree[v*2].min,tree[v*2+1].min);
////		tree[v].max = max(tree[v*2].max,tree[v*2+1].max);
////	}
////}
//void build_y (int vx, int lx, int rx, int vy, int ly, int ry) {
//	if (ly == ry)
//		if (lx == rx)
//			t[vx][vy] = a[lx][ly];
//		else
//			t[vx][vy] = min(t[vx*2][vy], t[vx*2+1][vy]);
//	else {
//		int my = (ly + ry) / 2;
//		build_y (vx, lx, rx, vy*2, ly, my);
//		build_y (vx, lx, rx, vy*2+1, my+1, ry);
//		t[vx][vy] = min(t[vx][vy*2], t[vx][vy*2+1]);
//	}
//}
// 
//void build_x (int vx, int lx, int rx) {
//	if (lx != rx) {
//		int mx = (lx + rx) / 2;
//		build_x (vx*2, lx, mx);
//		build_x (vx*2+1, mx+1, rx);
//	}
//	build_y (vx, lx, rx, 1, 0, m-1);
//}
//
//int main()
//{
//	for( int i=0; i<3;i++)
//		for(int j=0;j<3;j++)
//		a[i][j]=1;
//		build_x(1,0,2);
//	for( int i=0; i<3;i++)
//		for(int j=0;j<3;j++)
//		{
//			int res=min_x(1,0,2,0,i,0,j);
//			std::cout<<res<<std::endl;
//		}
//
//	system("pause");
//}

//#include<fstream>
//#include<iostream>
//#include<ctime>
//#include<vector>
//#include<queue>
//#pragma warning(disable:4996)
//using namespace std;
//struct Team{
//	int x;
//	int y;
//	int z;
//};
//bool sortX (Team obj1,Team obj2) { return (obj1.x < obj2.x); }
//int counter;
//int num;
//vector<Team> teamsSortedX;
//vector<Team> teamsSortedY;
//vector<Team> teamsSortedZ;
//vector<Team> dominatedTeams;
//struct minMax
//{
//	int min;
//	int max;
//}*tree;
//int min(int a,int b)
//{
//	return (a<b?a:b);
//}
//int max(int a,int b)
//{
//	return (a>b?a:b);
//}
//int min_y (int vx, int vy, int tly, int try_, int ly, int ry) {
//	if (ly > ry)
//		return INT_MAX;
//	if (ly == tly && try_ == ry)
//		return t[vx][vy];
//	int tmy = (tly + try_) / 2;
//	return min(min_y (vx, vy*2, tly, tmy, ly, min(ry,tmy)), min_y (vx, vy*2+1, tmy+1, try_, max(ly,tmy+1), ry));
//}
//
//int min_x (int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
//	if (lx > rx)
//		return INT_MAX;
//	if (lx == tlx && trx == rx)
//		return min_y (vx, 1, 0, m-1, ly, ry);
//	int tmx = (tlx + trx) / 2;
//	return min(min_x (vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry), min_x (vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry));
//}
//void build_y (int vx, int lx, int rx, int vy, int ly, int ry) {
//	if (ly == ry)
//		if (lx == rx)
//			t[vx][vy] = a[lx][ly];
//		else
//			t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
//	else {
//		int my = (ly + ry) / 2;
//		build_y (vx, lx, rx, vy*2, ly, my);
//		build_y (vx, lx, rx, vy*2+1, my+1, ry);
//		t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
//	}
//}
// 
//void build_x (int vx, int lx, int rx) {
//	if (lx != rx) {
//		int mx = (lx + rx) / 2;
//		build_x (vx*2, lx, mx);
//		build_x (vx*2+1, mx+1, rx);
//	}
//	build_y (vx, lx, rx, 1, 0, m-1);
//}
//void dominated()
//{
//	for(int i=0;i<num;i++)
//	{
//		counter++;
//		int tmin=min(1,0,num-1,0,i);
//		if(tmin>=teamsSortedX[i].y)
//			dominatedTeams.push_back(teamsSortedX[i]);
//	}
//}
//void input()
//{
//	FILE * file;
//	file = fopen ("input5.txt" , "r");
//	fscanf(file,"%d",&num);
//	Team temp;
//	for(int i=0;i<num;i++)
//	{
//		
//		fscanf(file,"%d",&temp.x);
//		fscanf(file,"%d",&temp.y);
//		teamsSortedX.push_back(temp);
//	}
//	sort(teamsSortedX.begin(),teamsSortedX.end(),sortX);
//}
//
//int main()
//{
//	int time=clock();
//	input();
//	tree=new  minMax[num*4];
//	int tbild=clock();
//	build(teamsSortedX,1,0,num-1);
//	int tbild2=clock();
//	dominated();
//	ofstream out("output.txt");
//	out<<dominatedTeams.size()<<endl;
//	cout<<"time "<<clock()-time<<" tbild "<<tbild2-tbild<<" alg "<<clock()-tbild2<<endl;
//	cout<<"c "<<counter<<endl;
//	system("pause");
//	return 0;
//}
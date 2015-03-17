#include <fstream>
#include <string>
#include <vector>
#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:16777216")
using namespace std;
bool prov=true;
class Tree;
Tree *badtree=0;
vector<Tree*> suspiciousTrees;
class Tree
{
	int* value;
	int lchilds;
	int rchilds;
	Tree* ltree;
	Tree* rtree;
public:
	Tree():value(0),ltree(0),rtree(0),lchilds(0),rchilds(0){}
	~Tree()
	{
		delete value;
		value=0;
		delete ltree;
		ltree=0;
		delete rtree;
		rtree=0;
	}
	Tree& operator =(const Tree& ob)
	{
		if(this==&ob)
			return *this;
		if(value)
			clear();
		if(ob.value)
		{
			value=new int;
			*value=*ob.value;
		}
		if(ob.ltree)
		{
			Tree* ltree=new Tree();
			*ltree=*ob.ltree;
		}
		if(ob.rtree)
		{
			Tree* rtree=new Tree();
			*rtree=*ob.rtree;
		}
		return *this;
	}
	Tree(const Tree& ob)
	{
		if(ob.value)
		{
			value=new int;
			*value=*ob.value;
		}
		if(ob.ltree)
		{
			Tree* ltree=new Tree();
			*ltree=*ob.ltree;
		}
		if(ob.rtree)
		{
			Tree* rtree=new Tree();
			*rtree=*ob.rtree;
		}
	}
	int getlchilds(){return lchilds;}
	int getrchilds(){return rchilds;}
	Tree* getltree(){return ltree;}
	Tree* getrtree(){return rtree;}
	void clear()
	{
		delete value;
		value=0;
		delete ltree;
		ltree=0;
		delete rtree;
		rtree=0;
		lchilds=0;
		rchilds=0;
	}
	void insert(int num)
	{
		Tree* temp=this;
		if(!temp->value)
		{
			temp->value=new int;
			*value=num;
		}
		for(;temp->value;)
		{	
			if(*(temp->value)==num)
				break;
			if(*(temp->value)<num)
			{
				if(temp->rtree)
					temp=temp->rtree;
				else
				{
					temp->rtree=new Tree();
					temp->rtree->value=new int;
					*(temp->rtree->value)=num;
				}
			}
			if(*(temp->value)>num)
			{
				if(temp->ltree)
					temp=temp->ltree;
				else
				{
					temp->ltree=new Tree();
					temp->ltree->value=new int;
					*(temp->ltree->value)=num;
				}
			}
		}
	}
	void removeRight(int num)
	{
		Tree* temp=this,*tempPrev=0;
		for(;temp;)
		{	
			if(*(temp->value)>num)
			{
				tempPrev=temp;
				temp=temp->ltree;
			}
			if(*(temp->value)<num)
			{
				tempPrev=temp;
				temp=temp->rtree;
			}
			if(*(temp->value)==num)
			{
				Tree *deletedElement=0;
				if((temp->ltree)&&(temp->rtree))
				{
					deletedElement=temp;
					tempPrev=temp;
					temp=temp->rtree;
					while(temp->ltree)
					{
						tempPrev=temp;
						temp=temp->ltree;
					}
					*(deletedElement->value)=*(temp->value);
					deletedElement=0;
				}
				if(temp->ltree)
				{
					deletedElement=temp->ltree;
					*(temp->value)=*(temp->ltree->value);
					temp->rtree=temp->ltree->rtree;
					temp->ltree=temp->ltree->ltree;
					deletedElement->rtree=0;
					deletedElement->ltree=0;
					delete deletedElement;
					break;
				}
				if(temp->rtree)
				{
					deletedElement=temp->rtree;
					*(temp->value)=*(temp->rtree->value);
					temp->ltree=temp->rtree->ltree;
					temp->rtree=temp->rtree->rtree;
					deletedElement->rtree=0;
					deletedElement->ltree=0;
					delete deletedElement;
					break;
				}
				if(!(temp->ltree)&&(!temp->rtree))
				{
					if(tempPrev)
					{
						deletedElement=temp;
						if(tempPrev->ltree==temp)
						{
							tempPrev->ltree=0;
						}
						else
						{
							tempPrev->rtree=0;
						}
						delete deletedElement;
						break;
					}
					else
					{
						temp->value=0;
						break;
					}
				}
			}
		}
	}
	void removeLeft(int num)
	{
		Tree* temp=this,*tempPrev=0;
		for(;temp;)
		{	
			if(*(temp->value)>num)
			{
				tempPrev=temp;
				temp=temp->ltree;
			}
			if(*(temp->value)<num)
			{
				tempPrev=temp;
				temp=temp->rtree;
			}
			if(*(temp->value)==num)
			{
				Tree *deletedElement=0;
				if((temp->ltree)&&(temp->rtree))
				{
					deletedElement=temp;
					tempPrev=temp;
					temp=temp->ltree;
					while(temp->rtree)
					{
						tempPrev=temp;
						temp=temp->rtree;
					}
					*(deletedElement->value)=*(temp->value);
					deletedElement=0;
				}
				if(temp->ltree)
				{
					deletedElement=temp->ltree;
					*(temp->value)=*(temp->ltree->value);
					temp->rtree=temp->ltree->rtree;
					temp->ltree=temp->ltree->ltree;
					deletedElement->rtree=0;
					deletedElement->ltree=0;
					delete deletedElement;
					break;
				}
				if(temp->rtree)
				{
					deletedElement=temp->rtree;
					*(temp->value)=*(temp->rtree->value);
					temp->ltree=temp->rtree->ltree;
					temp->rtree=temp->rtree->rtree;
					deletedElement->rtree=0;
					deletedElement->ltree=0;
					delete deletedElement;
					break;
				}
				if(!(temp->ltree)&&(!temp->rtree))
				{
					if(tempPrev)
					{
						deletedElement=temp;
						if(tempPrev->ltree==temp)
						{
							tempPrev->ltree=0;
						}
						else
						{
							tempPrev->rtree=0;
						}
						delete deletedElement;
						break;
					}
					else
					{
						temp->value=0;
						break;
					}
				}
			}
		}
	}
	int countChild(int counter)
	{
		if(value)
		{
			lchilds=0;
			rchilds=0;
			if(ltree)
				lchilds=ltree->countChild(counter);
			if(rtree)
				rchilds=rtree->countChild(counter);
			return lchilds+rchilds+1;
		}
		else return 0;
	}
	void compareTree(Tree& ob)
	{
		if(&ob==NULL)
		{
			if(!badtree)
			{
				badtree=this;
				if(lchilds!=0)
					ltree->compareTree(ob);
				if(rchilds!=0)
					rtree->compareTree(ob);
			}
			else
			{
				prov=false;
				return;
			}
		}
		else
		{
			if(getlchilds()==ob.getlchilds())
			{
				if(getlchilds()!=0)
					ltree->compareTree(*ob.getltree());
			}
			else
			{
				if(getlchilds()-ob.getlchilds()==1)
				{
					suspiciousTrees.push_back(this);
					if(getlchilds()!=0)
						ltree->compareTree(*ob.getltree());
				}
				else
				{
					if(!badtree)
					{
						badtree=this;
						if(lchilds!=0)
							ltree->compareTree(ob);
						if(rchilds!=0)
							rtree->compareTree(ob);
					}
					else
					{
						prov=false;
						return;
					}
				}
			}
			if(this!=badtree)
			{
				if(getrchilds()==ob.getrchilds())
				{
					if(getrchilds()!=0)
						rtree->compareTree(*ob.getrtree());
				}
				else
				{
					if(getrchilds()-ob.getrchilds()==1)
					{
						suspiciousTrees.push_back(this);
						if(getrchilds()!=0)
							rtree->compareTree(*ob.getrtree());
					}
					else
					{
						if(!badtree)
						{
							badtree=this;
							if(lchilds!=0)
								ltree->compareTree(ob);
							if(rchilds!=0)
								rtree->compareTree(ob);
						}
						else
						{
							prov=false;
							return;
						}
					}
				}
			}
		}
	}
	void output(ofstream& out)
	{
		if(value)
		{
			out<<*value<<"\n";
			if(ltree)
				ltree->output(out);
			if(rtree)
				rtree->output(out);
		}
	}
	int findDeleted()
	{
		Tree* maxTree=badtree;
		Tree* prevTree=badtree,*currentTree=0;
		int index=suspiciousTrees.size()-1;
		bool out=true;
		if(!badtree)
			return *value;
		if(index>=0)
		{
			currentTree=suspiciousTrees[index];
			index--;
		}
		else
			return *value;
		if(badtree->ltree)
		{
			if(currentTree->ltree==prevTree)
			{
				bool prov=true;
				while(out)
				{
					if((currentTree->ltree==prevTree)&&!(currentTree->rtree))
					{
						if(*(maxTree->value)<*(currentTree->value))
						{
							maxTree=currentTree;
						}
						if(index>=0){
							prevTree=currentTree;
							currentTree=suspiciousTrees[index];
							index--;
						}
						else
						{
							out=false;
							break;
						}
					}
					else
						break;
				}
				if((currentTree->rtree)&&(currentTree->ltree==prevTree))
				{
					prov=false;
					if(*(maxTree->value)<*(currentTree->value))
					{
						maxTree=currentTree;
					}
					while(out)
					{
						if(currentTree->ltree==prevTree)
						{
							if(index>=0){
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
							{
								out=false;
								break;
							}
						}
						else
							break;
					}
				}
				while(out)
				{
					if(currentTree->rtree==prevTree)
					{
						if(index>=0){
							prevTree=currentTree;
							currentTree=suspiciousTrees[index];
							index--;
						}
						else
						{
							out=false;
							break;
						}
					}
					else
						break;
				}
				if(prov)
				{
					if((currentTree->ltree==prevTree)&&(currentTree->rtree))
						if(*(maxTree->value)<*(currentTree->value))
						{
							maxTree=currentTree;
						}
				}
			}
			else
			{
				while(out)
				{
					if((currentTree->rtree==prevTree))
					{
						if(index>=0){
							prevTree=currentTree;
							currentTree=suspiciousTrees[index];
							index--;
						}
						else
						{
							out=false;
							break;
						}
					}
					else
						break;
				}
				if((currentTree->ltree==prevTree)&&(currentTree->rtree))
					if(*(maxTree->value)<*(currentTree->value))
					{
						maxTree=currentTree;
					}
			}
		}
		else
			if(badtree->rtree)
			{
				if(currentTree->rtree==prevTree)
				{
					bool prov=true;
					while(out)
					{
						if((currentTree->rtree==prevTree)&&!(currentTree->ltree))
						{
							if(*(maxTree->value)<*(currentTree->value))
							{
								maxTree=currentTree;
							}
							if(index>=0){
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
							{
								out=false;
								break;
							}
						}
						else
							break;
					}
					if((currentTree->ltree)&&(currentTree->rtree==prevTree))
					{
						prov=false;
						if(*(maxTree->value)<*(currentTree->value))
						{
							maxTree=currentTree;
						}
						while(out)
						{
							if(currentTree->rtree==prevTree)
							{
								if(index>=0){
									prevTree=currentTree;
									currentTree=suspiciousTrees[index];
									index--;
								}
								else
								{
									out=false;
									break;
								}
							}
							else
								break;
						}
					}
					while(out)
					{
						if(currentTree->ltree==prevTree)
						{
							if(index>=0){
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
							{
								out=false;
								break;
							}
						}
						else
							break;
					}
					if(prov)
					{
						if((currentTree->rtree==prevTree)&&(currentTree->ltree))
							if(*(maxTree->value)<*(currentTree->value))
							{
								maxTree=currentTree;
							}
					}
				}
				else
				{
					while(out)
					{
						if((currentTree->ltree==prevTree))
						{
							if(index>=0){
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
							{
								out=false;
								break;
							}
						}
						else
							break;
					}
					if((currentTree->rtree==prevTree)&&(currentTree->ltree))
						if(*(maxTree->value)<*(currentTree->value))
						{
							maxTree=currentTree;
						}
				}
			}
			else
			{
				if(currentTree->ltree==prevTree)
				{
					bool prov=true;
					while(out)
					{
						if((currentTree->ltree==prevTree)&&!(currentTree->rtree))
						{
							if(*(maxTree->value)<*(currentTree->value))
							{
								maxTree=currentTree;
							}
							if(index>=0){
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
							{
								out=false;
								break;
							}
						}
						else
							break;
					}
					if((currentTree->rtree)&&(currentTree->ltree==prevTree))
					{
						prov=false;
						if(*(maxTree->value)<*(currentTree->value))
						{
							maxTree=currentTree;
						}
						while(index>=0)
						{
							if(currentTree->ltree==prevTree)
							{
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
								break;
						}
					}
					if((currentTree->rtree==prevTree)&&(currentTree->ltree))
					{
						if(*(maxTree->value)<*(currentTree->value))
						{
							maxTree=currentTree;
						}
					}
					while(out)
					{
						if(currentTree->rtree==prevTree)
						{
							if(index>=0){
								prevTree=currentTree;
								currentTree=suspiciousTrees[index];
								index--;
							}
							else
							{
								out=false;
								break;
							}
						}
						else
							break;
					}
					if(prov)
					{
						if((currentTree->ltree==prevTree)&&(currentTree->rtree))
							if(*(maxTree->value)<*(currentTree->value))
							{
								maxTree=currentTree;
							}
					}
				}
				else
				{
					if(currentTree->rtree==prevTree)
					{
						bool prov=true;
						while(out)
						{
							if((currentTree->rtree==prevTree)&&!(currentTree->ltree))
							{
								if(*(maxTree->value)<*(currentTree->value))
								{
									maxTree=currentTree;
								}
								if(index>=0){
									prevTree=currentTree;
									currentTree=suspiciousTrees[index];
									index--;
								}
								else
								{
									out=false;
									break;
								}
							}
							else
								break;
						}
						if((currentTree->ltree)&&(currentTree->rtree==prevTree))
						{
							prov=false;
							if(*(maxTree->value)<*(currentTree->value))
							{
								maxTree=currentTree;
							}
							while(index>=0)
							{
								if(currentTree->rtree==prevTree)
								{
									prevTree=currentTree;
									currentTree=suspiciousTrees[index];
									index--;
								}
								else
									break;
							}
						}
						if((currentTree->ltree==prevTree)&&(currentTree->rtree))
						{
							if(*(maxTree->value)<*(currentTree->value))
							{
								maxTree=currentTree;
							}
						}
						while(out)
						{
							if(currentTree->ltree==prevTree)
							{
								if(index>=0){
									prevTree=currentTree;
									currentTree=suspiciousTrees[index];
									index--;
								}
								else
								{
									out=false;
									break;
								}
							}
							else
								break;
						}
						if(prov)
						{
							if((currentTree->rtree==prevTree)&&(currentTree->ltree))
								if(*(maxTree->value)<*(currentTree->value))
								{
									maxTree=currentTree;
								}
						}
					}
				}
			}
			return *(maxTree->value);
	}
};
void input(Tree& tree1,Tree& tree2)
{
	FILE * file;
	file = fopen ("tst.in" , "r");
	Tree* choisenTree=&tree1;
	char buf=0;
	int tempNumber=0;
	bool existNumber=false;
	if (file == NULL) 
		perror ("Error opening file");
	else
	{
		while(!feof(file))
		{
			while(((47>buf)||(buf>58))&&(!feof(file)))
			{
				fread(&buf,sizeof(char),1,file);
				if(buf=='*')
					choisenTree=&tree2;
			}
			while(((47<buf)&&(buf<58))&&(!feof(file)))
			{
				tempNumber=tempNumber*10+(buf-48);
				fread(&buf,sizeof(char),1,file);
				existNumber=true;
			}
			if(existNumber)
			{
				choisenTree->insert(tempNumber);
				tempNumber=0;
				existNumber=false;
			}
		}
		fclose (file);
	}
}
void output(int num,bool prov)
{
	ofstream out("tst.out");
	if(prov)
	{
		out<<"YES"<<endl;
		out<<num<<endl;
	}
	else
	{
		out<<"NO"<<endl;
	}
}
int main()
{
	Tree firstTree,secondTree;
	input(firstTree,secondTree);
	int n1=firstTree.countChild(0);
	int n2=secondTree.countChild(0);
	if(n1-n2==1)
		firstTree.compareTree(secondTree);
	else
		if(n2-n1==1)
			secondTree.compareTree(firstTree);
		else
			prov=false;
	if(!prov)
		output(0,false);
	else
	{
		int deleted=0;
		if(n1-n2==1)
			deleted=firstTree.findDeleted();
		else
			deleted=secondTree.findDeleted();
		output(deleted,true);
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Tree{
	int count;
	struct Node{
		int data;
		int halfPath;
		int countPath;
		Node* left;
		Node* right;
		Node* father;
	}*root;

	bool costyl(vector<Node*> &tempPoints, Node* obj)
	{
		for(int i=0; i<tempPoints.size(); i++)
		{
			if(tempPoints[i] == obj)
				return true;
		}
		return false;
	}
	Node* promotka(Node* obj, vector<Node*> &tempPoints);
    Node* Path(Node *obj, vector<Node*> &tempPoints, Node *lastNode, bool flag);
	//void* Path(Node *obj, vector<Node*> &tempPoints, bool flag);
public:	vector<Node*> roots;
		Tree() {root = 0; count = 0; }
		~Tree(){
		}
		int getSize() {return count;}
		Node* getRoot() {return root;}

		void addNode(int item);	
		void inputTree(istream& input);

		Node* receiveAdress(int item);

		void halfPathDefine(Node *obj);
		void createRootsVector(Node* obj);

		void deleteNodeRight(Node *obj);
		void deleteNodeMax(Node* obj);
		int deleteRight(Node *obj);

		void createMarkedNodes();
		void print(ofstream& out, Node* obj);

		void Tree::path2(Node* obj,Node* root);
		void Tree::increase(Node* current,Node* root);
};

void Tree :: addNode(int item){

	count++;
	if(root == 0)
	{
		root = new Node();
		root->data = item;
		root->left = 0;
		root->right = 0;
		root->father = 0;
		root->countPath = 0;
		return;
	}
	Node *temp = root;
	Node *prev = root;
	while(true)
	{
		if( item > temp->data )
		{
			prev = temp;
			if(temp->right == 0)
			{
				temp->right = new Node();
				temp->right->data = item;
				temp->right->halfPath = 0;
				temp->right->father = prev;
				break;
			}
			else {
				//prev = temp;
				temp = temp->right;		
			}
		}
		else if( item < temp->data )
		{
			prev = temp;
			if(temp->left == 0)
			{
				temp->left = new Node();
				temp->left->data = item;
				temp->left->countPath = 0;
				temp->left->father = prev;
				break;
			}
			else {
				//prev = temp;
				temp = temp->left;		
			}
		}
		else if(item == temp->data)
			break;
	}
	return;
}
void Tree :: inputTree(istream& input)
{
	int number;
	while(!input.eof())
	{
		input>>number;
		addNode(number);
	}
}

Tree :: Node* Tree :: receiveAdress(int item)
{
	Node* temp = root;

	while( (temp->left!= 0 && temp->right!=0) || temp->data != item)
	{
		if(temp->data < item)
			temp = temp->right;
		else if(temp->data > item)
			temp = temp->left;
		else if (temp->data == item)
			return temp;
	}
	if (temp->data == item)
		return temp;
	else return 0;
}

void Tree :: halfPathDefine(Node *obj) // или у корня -1 сделать?
{
	if(obj != NULL)
	{
		halfPathDefine((obj->right));
		halfPathDefine(obj->left);

		if(obj->left == 0 && obj->right ==0)
		{
			obj->halfPath = 0;
		}
		else if(obj->left !=0 && obj->right !=0)
			obj->halfPath= (obj->left->halfPath > obj->right->halfPath ? obj->left->halfPath: obj->right->halfPath) +1;
		else if(obj->left !=0 )
			obj->halfPath = obj->left->halfPath +1;
		else 
			obj->halfPath = obj->right->halfPath +1;

	}
}

int countGlobal = 0;
int maximum = 1;
void Tree :: createRootsVector(Node* obj)
{
	if(obj != NULL)
	{
		createRootsVector((obj->right));
		createRootsVector(obj->left);

		//лист пропускаем
		if(obj->left != 0 && obj->right != 0) //два сына
		{
			if(obj->left->halfPath + obj->right->halfPath + 2 > countGlobal)
			{
				roots.clear();
				countGlobal = obj->left->halfPath + obj->right->halfPath + 2;
				roots.push_back(obj);
			}
			else if(obj->left->halfPath + obj->right->halfPath + 2 == countGlobal)
				roots.push_back(obj);
		}
		else if( obj->left != 0 && obj->right==0)
		{
			if(obj->left->halfPath + 1 > countGlobal)
			{
				roots.clear();
				countGlobal = obj->left->halfPath +1;
				roots.push_back(obj);
			}
			else if(obj->left->halfPath + 1 == countGlobal)
				roots.push_back(obj);
		}
		else if( obj->left == 0 && obj->right!=0)
		{
			if(obj->right->halfPath + 1 > countGlobal)
			{
				roots.clear();
				countGlobal = obj->right->halfPath + 1;
				roots.push_back(obj);
			}
			else if(obj->right->halfPath + 1 == countGlobal)
				roots.push_back(obj);
		}
	}
}


void Tree :: deleteNodeRight(Node *obj)
{
	if(obj->left == 0 && obj->right ==0)
	{
		//list

		if(obj == obj->father->left)
			obj->father->left = NULL;
		else
			obj->father->right = NULL;
		delete obj;
	}
	else if(obj->left != 0 && obj->right == 0)
	{
		if(obj->father == NULL)
		{
			root = obj->left;
		}
		else{
			if(obj == obj->father->left)
				obj->father->left = obj->left;
			else
				obj->father->right = obj->left;
			obj->left->father = obj->father;
		}

		delete obj;

	}
	else if(obj->right !=0 && obj->left == 0)
	{
		if(obj->father == NULL)
		{
			root = obj->right;
		}
		else{

			if(obj == obj->father->left)
				obj->father->left = obj->right;
			else
				obj->father->right = obj->right;
			obj->right->father = obj->father;
		}
		delete obj;
	}
	else{
		Node *temp = obj->right;
		obj->data = deleteRight(temp);
	}

}
int Tree::deleteRight(Node *obj)
{
	Node *temp=obj;
	int data;
	while(temp->left!=0)
		temp=temp->left;

	data = temp->data;
	deleteNodeRight (temp);

	return data;
}
void Tree :: deleteNodeMax(Node* obj)
{
	if(obj!=NULL)
	{
		deleteNodeMax(obj->left);
		deleteNodeMax(obj->right);
		if(obj->countPath == maximum)
			deleteNodeRight(obj);
		/*if(obj->data % 2 == 0)
		{
		deleteNodeRight(obj);
		}*/
	}
}
void Tree :: print(ofstream &out, Node* obj)
{
	if(obj!=NULL)
	{
		out<<obj->data<<endl;
		print(out, obj->left);
		print(out, obj->right);

		

	}
}
//realization 4
int globalLeft = 0;
int globalRight =0;
int numberOfRec=0;
int counted=0;
bool flag = false;
void Tree :: createMarkedNodes()
{
	//vector<Node* > tempPoints;
	for (int i=0; i<roots.size(); i++)
	{
		counted=1;
		numberOfRec=0;
		if(roots[i]->left)
			path2(roots[i]->left,roots[i]);
		int leftRec=numberOfRec;
		numberOfRec=0;
		if(roots[i]->right)
			path2(roots[i]->right,roots[i]);
		int rightRec=numberOfRec;
		if(rightRec>0 && leftRec>0)
			roots[i]->countPath+=rightRec*leftRec;
		else
		{
			if(rightRec>0)
				roots[i]->countPath+=rightRec;
			if(leftRec>0)
				roots[i]->countPath+=leftRec;
		}
	//	roots[i]->countPath+=rightRec*leftRec;
		if(roots[i]->countPath>maximum)
			maximum=roots[i]->countPath;
		if(leftRec-1>0)
		{
			counted=leftRec-1;
			if(roots[i]->right)
				path2(roots[i]->right,roots[i]);
		}
		if(rightRec-1>0)
		{
			counted=rightRec-1;
			if(roots[i]->left)
				path2(roots[i]->left,roots[i]);
		}
		
	}
}
void Tree::path2(Node*obj,Node* root)
{
	if((obj->left)&&(obj->right))
	{
		if((obj->left->halfPath>obj->right->halfPath))
			this->path2(obj->left,root);
		if((obj->left->halfPath<obj->right->halfPath))
			this->path2(obj->right,root);
		if((obj->left->halfPath==obj->right->halfPath))
		{
			this->path2(obj->left,root);
			this->path2(obj->right,root);
		}
		return;
	}
	if(obj->right)
	{
		this->path2(obj->right,root);
	}
	if(obj->left)
	{
		this->path2(obj->left,root);
	}
	if(((!obj->left)&&(!obj->right)))
	{
		numberOfRec++;
		this->increase(obj,root);
	}
}
void Tree::increase(Node* current,Node* root)
{
	while(current!=root)
	{
		current->countPath+=counted;
		if(current->countPath>maximum)
			maximum=current->countPath;
		current=current->father;
	}
}

Tree :: Node* Tree :: Path(Node *obj, vector<Node*> &tempPoints, Node *lastNode, bool flag)
{
	Node* temp = NULL;
	if(obj!=0)
	{

		//sdelat naredshestvennika
		while(lastNode!=obj)
		{
			if(obj->left == 0 && obj->right==0)
			{
				tempPoints.push_back(obj);
				break;
			}
			else if(obj->left == 0 && obj->right !=0)
			{
				tempPoints.push_back(obj);
				obj = obj->right;
			}
			else if(obj->left != 0 && obj->right ==0)
			{
				tempPoints.push_back(obj);
				obj = obj->left;
			}
			else {
				if(obj->left->halfPath > obj->right->halfPath)
				{
					tempPoints.push_back(obj);
					obj = obj->left;
				}
				else if(obj->left->halfPath < obj->right->halfPath)
				{
					tempPoints.push_back(obj);
					obj = obj->right;
				}
				else{
					tempPoints.push_back(obj);

					Path(obj->left, tempPoints, lastNode, true);
					Path(obj->right, tempPoints, lastNode, false);
					lastNode = obj;
				}
			}
		}
	}
	return obj;
}


int main(){

	Tree tree;
	ifstream input("in.txt");

	tree.inputTree(input);

	//написание значений полупутей
	tree.halfPathDefine(tree.getRoot());

	//создание массива узлов-корней
	tree.createRootsVector(tree.getRoot());

	//попытка реализации пометки тех вершин, которые надо удалить
	tree.createMarkedNodes();

	//удаление countPath
	tree.deleteNodeMax(tree.getRoot());

	ofstream out("out.txt");
	tree.print(out, tree.getRoot());
	out.close();
		return 0;
}
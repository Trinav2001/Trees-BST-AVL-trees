#include<iostream>
using namespace std;

class Node
{
	public:
		Node *lchild;
		int data;
		Node*rchild;
};

class BST
{
	private:
		Node *root;
	public:
		BST(){
			root = NULL;
		}
		void insert(int key);
		Node *getroot(){
			return root;
		}
		Node *search(int key);
		void inorder(Node *p);
};

void BST :: insert(int key)
{
	Node *r = NULL;
	Node *p, *t = root;
	if(root==NULL)
	{
		p = new Node;
		p->data = key;
		p->lchild = p->rchild = NULL;
		root = p;
		return ;
	}
	while(t!=NULL)
	{
		r = t;
		if(key<t->data)
		{
			t = t->lchild;
		}
		else if(key>t->data)
		{
			t = t->rchild;
		}
		else
		{
			return;
		}
	}
	p = new Node;
	p->data = key;
	p->lchild = p->rchild = NULL;
	if(key<r->data)
	{
		r->lchild = p;
	}
	else
	{
		r->rchild = p;
	}
	return;
}

void BST :: inorder(Node *p)
{
	if(p)
	{
		inorder(p->lchild);
		cout<<p->data<<" ";
		inorder(p->rchild);
	}
}

Node * BST :: search(int key)
{
	Node *r = root;
	while(r!=NULL)
	{
		if(key==r->data)
		{
			return r;
		}
		else if(key<r->data)
		{
			r = r->lchild;
		}
		else
		{
			r = r->rchild;
		}
	}
}

int main()
{
	BST bst;
	bst.insert(10);
	bst.insert(5);
	bst.insert(20);
	bst.insert(8);
	bst.insert(19);
	
	bst.inorder(bst.getroot());
	cout<<endl;
	
	Node *temp = bst.search(20);
	if(temp!=NULL)
	{
		cout<<"Element found "<<temp->data;
	}
	else
	{
		cout<<"Element not found";
	}
	return 0;
}

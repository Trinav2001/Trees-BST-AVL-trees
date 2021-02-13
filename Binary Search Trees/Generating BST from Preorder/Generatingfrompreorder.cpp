#include<iostream>
using namespace std;

class Node
{
	public:
		Node *lchild;
		int data;
		Node *rchild;
};

class BST
{
	private:
		Node *root;
	public:
		BST(){
			root = NULL;
		}
		Node * getroot(){
			return root;
		}
		void Iinsert(int key);
		void Inorder(Node *p);
		Node * Isearch(int key);
		Node * Rinsert(Node *p,int key);
		Node * Rsearch(Node *p,int key);
		Node * Delete(Node *p,int key);
		int Height(Node *p);
		Node * InPre(Node *p);
		Node * InSucc(Node *p);
		void Createfrompreorder(int pre[],int n);
};

void BST :: Iinsert(int key)
{
	Node *p,*r=NULL;
	Node *t=root;
	if(root==NULL)
	{
		p = new Node;
		p->data = key;
		p->lchild = p->rchild = NULL;
		root = p;
		return;
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
	else if(key>r->data)
	{
		r->rchild = p;
	}
	return;
}

void BST :: Inorder(Node *p)
{
	if(p)
	{
		Inorder(p->lchild);
		cout<<p->data<<" ";
		Inorder(p->rchild);
	}
}

Node * BST :: Isearch(int key)
{
	Node *p = root;
	while(p!=NULL)
	{
		if(key==p->data)
		{
			return p;
		}
		else if(key<p->data)
		{
			p = p->lchild;
		}
		else
		{
			p = p->rchild;
		}
	}
}

Node * BST :: Rinsert(Node *p,int key)
{
	Node *t;
	if(p==NULL)
	{
		t = new Node;
		t->lchild = t->rchild = NULL;
		return t;
	}
	if(key<p->data)
	{
		p->lchild = Rinsert(p->lchild,key);
	}
	else if(key>p->data)
	{
		p->rchild = Rinsert(p->rchild,key);
	}
	return p;
}

Node * BST :: Rsearch(Node *p, int key)
{
	if(p==NULL)
	{
		return NULL;
	}
	if(p->data==key)
	{
		return p;
	}
	else if(p->data>key)
	{
		Rsearch(p->lchild,key);
	}
	else
	{
		Rsearch(p->rchild,key);
	}
}

Node * BST :: Delete(Node *p,int key)
{
	Node *q;
	if(p==NULL)
	{
		return NULL;
	}
	
	if(p->lchild==NULL && p->rchild==NULL)
	{
		if(p==root)
		{
			root = NULL;
		}
		delete p;
		return NULL;
	}
	
	if(key<p->data)
	{
		p->lchild = Delete(p->lchild,key);
	}
	else if(key>p->data)
	{
		p->rchild = Delete(p->rchild,key);
	}
	else
	{
		if(Height(p->lchild)>Height(p->rchild))
		{
			q = InPre(p->lchild);
			p->data = q->data;
			p->lchild = Delete(p->lchild,q->data);
		}
		else
		{
			q = InSucc(p->rchild);
			p->data = q->data;
			p->rchild = Delete(p->rchild,q->data);
		}
	}
	return p;
}

int BST :: Height(Node *p)
{
	int x,y;
	if(p==NULL)
	{
		return NULL;
	}
	x = Height(p->lchild);
	y = Height(p->rchild);
	return x>y?x+1:y+1;
}

Node * BST :: InPre(Node *p)
{
	while(p && p->lchild!=NULL)
	{
		p = p->lchild;
	}
	return p;
}

Node * BST :: InSucc(Node *p)
{
	while(p && p->rchild!=NULL)
	{
		p = p->rchild;
	}
	return p;
}

void BST :: Createfrompreorder(int *pre,int n)
{
	Node *t;
	int i=0;
	root = new Node;
	root->data = pre[i++];
	root->lchild = root->rchild = NULL;
	Node *p=root;
	while(i<n)
	{
		if(pre[i]<p->data)
		{
			t = new Node;
			t->data = pre[i++];
			t->lchild = t->rchild = NULL;
			p->lchild = t;
			stk.push(p);
			p = t;
		}
		else
		{
			if(pre[i]>p->data && pre[i]<stk.stackTop())
			{
				t = new Node;
				t->lchild = t->rchild = NULL;
				p->rchild = t;
				p  = t;
			}
			else
			{
				p = stk.stackTop();
				stk.pop();
			}
		}
	}
}

int main()
{
	BST bst;
	
	bst.Iinsert(10);
	bst.Iinsert(5);
	bst.Iinsert(20);
	bst.Iinsert(8);
	bst.Iinsert(30);
	
	bst.Inorder(bst.getroot());
	cout<<endl;
	bst.Rinsert(root,10);
	bst.Rinsert(root,5);
	bst.Rinsert(root,20);
	bst.Rinsert(root,8);
	bst.Rinsert(root,30);
	cout<<endl;
	bst.Inorder(bst.getroot());
	cout<<endl<<"Generating BST from Preorder\n";
	
	int pre[] = {30,20,10,15,25,40,50,45};
	int n = sizeof(pre)/sizeof(pre[0]);
	
	BST b;
	
	b.Createfrompreorder(pre,n);
	b.Inorder(b.getroot());
	return 0;
}

#include<iostream>
using namespace std;

class Node
{
	public:
		Node *lchild;
		int data;
		int height;
		Node *rchild;
};

class AVL
{
	public:
		Node *root;
		AVL()
		{
			root = NULL;
		}
		int Height(Node *p);
		Node * Rinsert(Node *p,int key);
		Node * Delete(Node *p,int key);
		Node * LLRotation(Node *p);
		Node * LRRotation(Node *p);
		Node * RRRotation(Node *p);
		Node * RLRotation(Node *p);
		Node * InPre(Node *p);
		Node * InSucc(Node *p);
		void Inorder(Node *p);
		void Preorder(Node *p);
};

void AVL :: Inorder(Node *p)
{
	if(p)
	{
		Inorder(p->lchild);
		cout<<p->data<<" ";
		Inorder(p->rchild);
	}
}

void AVL :: Preorder(Node *p)
{
	if(p)
	{
		cout<<p->data<<" ";
		Preorder(p->lchild);
		Preorder(p->rchild);
	}
}

Node * AVL :: InPre(Node *p)
{
	while(p && p->rchild!=NULL)
	{
		p = p->rchild;
	}
	return p;
}

Node * AVL :: InSucc(Node *p)
{
	while(p && p->lchild!=NULL)
	{
		p = p->lchild;
	}
	return p;
}

int AVL :: Height(Node *p)
{
	int x=0,y=0;
	if(!p)
	{
		return 0;
	}
	x = Height(p->lchild);
	y = Height(p->rchild);
	return x>y?x+1:y+1;
}

Node * AVL :: LLRotation(Node *p)
{
	Node *pl=p->lchild;
	p->lchild = pl->rchild;
	pl->rchild = p;
	int lh,rh;
	lh = Height(p->lchild)+1;
	rh = Height(p->rchild)+1;
	p->height = lh-rh;
	lh = Height(pl->lchild);
	rh = Height(pl->rchild);
	pl->height = lh-rh;
	if(root==p)
	{
		root = pl;
	}
	return pl;
}

Node * AVL :: LRRotation(Node *p)
{
	Node *pl=p->lchild,*plr=pl->rchild;
	p->lchild = plr->rchild;
	pl->rchild = plr->lchild;
	plr->lchild = pl;
	plr->rchild = p;
	int lh,rh;
	lh = Height(p->lchild)+1;
	rh = Height(p->rchild)+1;
	p->height = lh-rh;
	lh = Height(pl->lchild)+1;
	rh = Height(pl->rchild)+1;
	pl->height = lh-rh;
	if(root==p)
	{
		root = plr;
	}
	return plr;
}

Node * AVL :: RRRotation(Node *p)
{
	Node *pr=p->rchild;
	p->rchild = pr->lchild;
	pr->lchild = p;
	int lh,rh;
	lh = Height(p->lchild)+1;
	rh = Height(p->rchild)+1;
	p->height = lh-rh;
	lh = Height(pr->lchild);
	rh = Height(pr->rchild);
	pr->height = lh-rh;
	if(root==p)
	{
		root = pr;
	}
	return pr;
}

Node * AVL :: RLRotation(Node *p)
{
	Node *pr=p->rchild,*prl=pr->lchild;
	p->rchild = prl->lchild;
	pr->lchild = prl->rchild;
	prl->lchild = p;
	prl->rchild = pr;
	int lh,rh;
	lh = Height(p->lchild)+1;
	rh = Height(p->rchild)+1;
	p->height = lh-rh;
	lh = Height(pr->lchild)+1;
	rh = Height(pr->rchild)+1;
	pr->height = lh-rh;
	if(root==p)
	{
		root = prl;
	}
	return prl;
}

Node * AVL :: Rinsert(Node *p,int key)
{
	Node *t=NULL;
	if(p==NULL)
	{
		t = new Node;
		t->data = key;
		t->lchild = t->rchild = NULL;
		t->height = 1;
		return t;
	}
	
	if(p->data>key)
	{
		p->lchild = Rinsert(p->lchild,key);
	}
	else if(p->data<key)
	{
		p->rchild = Rinsert(p->rchild,key);
	}
	int lh,rh;
	lh = Height(p->lchild)+1;
	rh = Height(p->rchild)+1;
	p->height = lh-rh;
	if(p->height==2 && p->lchild->height==1)
	{
		return LLRotation(p);
	}
	if(p->height==2 && p->lchild->height==-1)
	{
		return LRRotation(p);
	}
	if(p->height==-2 && p->rchild->height==-1)
	{
		return RRRotation(p);
	}
	if(p->height==-2 && p->rchild->height==1)
	{
		return RLRotation(p);
	}
	return p;
}

Node * AVL :: Delete(Node *p,int key)
{
	if(p==NULL)
	{
		return 0;
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
	
	if(p->data>key)
	{
		p->lchild = Delete(p->lchild,key);
	}
	else if(p->data<key)
	{
		p->rchild = Delete(p->rchild,key);
	}
	else
	{
		Node *q;
		if(Height(p->lchild)<Height(p->rchild))
		{
			q = InSucc(p->rchild);
			p->data = q->data;
			p->rchild = Delete(p->rchild,q->data);
		}
		else
		{
			q = InPre(p->lchild);
			p->data = q->data;
			p->lchild = Delete(p->lchild,q->data);
		}
	}
	
	p->height = Height(p);
	
	if(p->height==2 && p->lchild->height==1)         //L1-Rotation
	{
		return LLRotation(p);
	}
	else if(p->height==2 && p->lchild->height==-1)        //L-1 Rotation
	{
		return LRRotation(p);
	}
	else if(p->height==-2 && p->rchild->height==-1)       //R-1 Rotation
	{
		return RRRotation(p);
	}
	else if(p->height==-2 && p->rchild->height==1)        //R1-Rotation
	{
		return RLRotation(p);
	}
	else if(p->height==-2 && p->rchild->height==0)           //R0-Rotation
	{
		return RRRotation(p);
	}
	else if(p->height==2 && p->lchild->height==0)            //L0-Rotation
	{
		return LLRotation(p);
	}
	return p;
}

int main() 
{
    AVL tree;
 
    int A[] = {10,5,20,15,25};
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
        tree.root = tree.Rinsert(tree.root, A[i]);
    }
 
    tree.Preorder(tree.root);
    cout << endl;
 
    tree.Delete(tree.root, 5);
   
    tree.Inorder(tree.root);
    cout << endl;
 
    return 0;
}

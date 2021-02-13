#include<stdio.h>
#include<stdlib.h>

struct Node
{
	struct Node *lchild;
	int data;
	int height;
	struct Node *rchild;
}*root=NULL;

struct Node * LLRotation(struct Node *p)
{
	printf("LL\n");
	struct Node *pl=p->lchild;
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

struct Node * LRRotation(struct Node *p)
{
	printf("LR\n");
	struct Node *pl=p->lchild,*plr=pl->rchild;
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

struct Node * RRRotation(struct Node *p)
{
	printf("RR\n");
	struct Node *pr=p->rchild;
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

struct Node * RLRotation(struct Node *p)
{
	printf("RL\n");
	struct Node *pr=p->rchild,*prl=pr->lchild;
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


int Height(struct Node *p)
{
	int x=0,y=0;
	if(p==NULL)
	{
		return 1;
	}
	x = Height(p->lchild);
	y = Height(p->rchild);
	return x>y?x+1:y+1;
}

struct Node * RInsert(struct Node *p,int key)
{
	struct Node *t=NULL;
	int lh,rh;
	if(p==NULL)
	{
		t = (struct Node *)malloc(sizeof(struct Node));
		t->data = key;
		t->lchild = t->rchild = NULL;
		t->height = 1;
		return t;
	}
	
	if(key<p->data)
	{
		p->lchild = RInsert(p->lchild,key);
	}
	else if(key>p->data)
	{
		p->rchild = RInsert(p->rchild,key);
	}
	
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

void Preorder(struct Node *p)
{
	if(p!=NULL)
	{
		printf("%d ",p->data);
		Preorder(p->lchild);
		Preorder(p->rchild);
	}
}

int main()
{
	root = RInsert(root,10);
	RInsert(root,15);
	RInsert(root,12);
	Preorder(root);
	return 0;
}

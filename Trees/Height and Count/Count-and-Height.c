#include<stdio.h>

struct Queue
{
	int size;
	int front;
	int rear;
	struct Node **Q;
};

struct Node
{
	struct Node *lchild;
	int data;
	struct Node *rchild;
};

struct Node *root = NULL;

void Treecreate()
{
	struct Queue q;
	struct Node *p,*t;
	int x;
	create(&q,100);
	printf("Enter root value : ");
	scanf("%d",&x);
	root = (struct Node *)malloc(sizeof(struct Node));
	root->data = x;
	root->lchild = root->rchild = NULL;
	enqueue(&q,root);
	while(!isEmpty(q))
	{
		p = dequeue(&q);
		printf("Enter left child of %d ", p->data);
		scanf("%d",&x);
		if(x!=-1)
		{
			t = (struct Node *)malloc(sizeof(struct Node));
			t->data = x;
			t->lchild = t->rchild = NULL;
			p->lchild = t;
			enqueue(&q,t);
		}
		printf("Enter right child of %d ", p->data);
		scanf("%d",&x);
		if(x!=-1)
		{
			t = (struct Node *)malloc(sizeof(struct Node));
			t->data = x;
			t->lchild = t->rchild = NULL;
			p->rchild = t;
			enqueue(&q,t);
		}
	}
}

void create(struct Queue *q,int size)
{
	q->size = size;
	q->front = q->rear = 0;
	q->Q = (struct Node **)malloc(q->size*sizeof(struct Node *));
}

int isEmpty(struct Queue q)
{
	return q.front==q.rear;
}

int dequeue(struct Queue *q)
{
	int x = -1;
	if(q->front==q->rear)
	{
		printf("Queue is empty!");
	}
	else
	{
		q->front = (q->front+1)%q->size;
		x = q->Q[q->front];
	}
	return x;
}

void enqueue(struct Queue *q,int x)
{
	if((q->rear+1)%q->size==q->front)
	{
		printf("Queue is full!");
	}
	else
	{
		q->rear = (q->rear+1)%q->size;
		q->Q[q->rear] = x;
	}
}

int count(struct Node *root)
{
	int x=0,y=0;
	if(root!=NULL)
	{
		x = count(root->lchild);
		y = count(root->rchild);
		return x+y+1;
	}
	return 0;
}

int height(struct Node *root)
{
	int x=0,y=0;
	if(root!=NULL)
	{
		x = height(root->lchild);
		y = height(root->rchild);
		if(x>y)
		{
			return x+1;
		}
		else
		{
			return y+1;
		}
	}
	return 0;
}

int main()
{
	Treecreate();
	printf("count = %d",count(root));
	printf("\nheight = %d",height(root));
}

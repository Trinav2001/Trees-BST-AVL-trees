#include<stdio.h>
#include<stdlib.h>

struct Node
{
	struct Node *lchild;
	int data;
	struct Node *rchild;
};

struct Node *root = NULL;

struct Queue
{
	int size;
	int front;
	int rear;
	struct Node **Q;
};

struct Stack
{
	int size;
	int top;
	struct Node **s;
};

void Treecreate()
{
	struct Node *p,*t;
	int x;
	struct Queue q;
	create(&q,100);
	printf("Enter root value ");
	scanf("%d",&x);
	root = (struct Node *)malloc(sizeof(struct Node));
	root->data = x;
	root->lchild = root->rchild = NULL;
	enqueue(&q,root);
	while(!isEmpty(q))
	{
		p = dequeue(&q);
		printf("Enter left child of %d",p->data);
		scanf("%d",&x);
		if(x!=-1)
		{
			t = (struct Node *)malloc(sizeof(struct Node));
			t->data = x;
			t->lchild = t->rchild = NULL;
			p->lchild = t;
			enqueue(&q,t);
		}
		printf("Enter right child of %d",p->data);
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

void create(struct Queue *q, int size)
{
	q->size = size;
	q->front = q->rear = 0;
	q->Q = (struct Node **)malloc(q->size*sizeof(struct Node *) );
}

void enqueue(struct Queue *q, struct Node *x)
{
	if(q->front==(q->rear+1)%q->size)
	{
		printf("Queue is full !\n");
	}
	else
	{
		q->rear = (q->rear+1)%q->size;
		q->Q[q->rear] = x;
	}
}

int dequeue(struct Queue *q)
{
	int x = -1;
	if(q->front==q->rear)
	{
		printf("Queue is empty !\n");
	}
	else
	{
		q->front = (q->front+1)%q->size;
		x = q->Q[q->front];
	}
	return x;
}

int isEmpty(struct Queue q)
{
	return q.front==q.rear;
}

void Stackcreate(struct Stack *stk, int size)
{
	stk->size = size;
	stk->top = -1;
	stk->s = (struct Node **)malloc(stk->size*sizeof(struct Node *));
}

void push(struct Stack *stk, struct Node *x)
{
	if(stk->top==stk->size-1)
	{
		printf("Stack is full !\n");
	}
	else
	{
		stk->top++;
		stk->s[stk->top] = x;
	}
}

int pop(struct Stack *stk)
{
	int x = -1;
	if(stk->top==-1)
	{
		printf("Stack is empty !\n");
	}
	else
	{
		x = stk->s[stk->top];
		stk->top--;
	}
	return x;
}

int isEmptyStack(struct Stack stk)
{
	return stk.top==-1;
}

void IPreorder(struct Node *p)
{
	struct Stack stk;
	Stackcreate(&stk,100);
	while(p!=NULL || !isEmptyStack(stk))
	{
		if(p!=NULL)
		{
			printf("%d ",p->data);
			push(&stk,p);
			p = p->lchild;
		}
		else
		{
			p = pop(&stk);
			p = p->rchild;
		}
	}
	printf("\n\n");
}

void IInorder(struct Node *p)
{
	struct Stack stk;
	Stackcreate(&stk,100);
	while(p!=NULL || !isEmptyStack(stk))
	{
		if(p!=NULL)
		{
			push(&stk,p);
			p = p->lchild;
		}
		else
		{
			p = pop(&stk);
			printf("%d ",p->data);
			p = p->rchild;
		}
	}
	printf("\n\n");
}

void IPostorder(struct Node *p)
{
	struct Stack stk;
	long int temp;
	while(p!=NULL || !isEmptyStack(stk))
	{
		if(p!=NULL)
		{
			push(&stk,p);
			p = p->lchild;
		}
		else
		{
			temp = pop(&stk);
			if(temp>0)
			{
				push(&stk,-temp);
				p = ((struct Node *)temp)->rchild;
			}
			else
			{
				printf("%d ",((struct Node *)temp)->data);
				p = NULL;
			}
		}
	}
}

int main()
{
	Treecreate();
	IPreorder(root);
	IInorder(root);
	return 0;
}

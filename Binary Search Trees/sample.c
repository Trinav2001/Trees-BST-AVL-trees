#include<stdio.h>
#include<stdlib.h>

struct Node
{
	struct Node *lchild;
	int data;
	struct Node *rchild;
};

struct Node *root=NULL;

void Insert(int key) {
 
    struct Node *t = root;
    struct Node *p;
    struct Node *r;
 
    // root is empty
    if (root == NULL){
        p = (struct Node *)malloc(sizeof(struct Node));
        p->data = key;
        p->lchild = NULL;
        p->rchild = NULL;
        root = p;
        return;
    }
 
    while(t != NULL){
        r = t;
        if (key < t->data){
            t = t->lchild;
        } else if (key > t->data){
            t = t->rchild;
        } else {
            return;
        }
    }
 
    // Now t points at NULL and r points at insert location
    p = (struct Node *)malloc(sizeof(struct Node));
    p->data = key;
    p->lchild = NULL;
    p->rchild = NULL;
 
    if (key < r->data){
        r->lchild = p;
    } else {
        r->rchild = p;
    }
 
}

struct Node *InPre(struct Node *p) {
    while (p && p->rchild != NULL){
        p = p->rchild;
    }
    return p;
}
 
struct Node *InSucc(struct Node *p) {
    while (p && p->lchild != NULL){
        p = p->lchild;
    }
    return p;
}
void Preorder(struct Node *p)
{
	if(p)
	{
		printf("%d ",p->data);
		Preorder(p->lchild);
		Preorder(p->rchild);
	}
}

int Height(struct Node *root)
{
 	int x=0,y=0;
 	if(root==0)
 	return 0;
 	x=Height(root->lchild);
 	y=Height(root->rchild);
 	if(x>y)
 		return x+1;
 	else
 		return y+1;
} 

struct Node *Delete(struct Node *p,int key)
{
	struct Node *q;
if (p == NULL){
        return NULL;
    }
 
    if (p->lchild == NULL && p->rchild == NULL){
        if (p == root){
            root = NULL;
        }
        free(p);
        return NULL;
    }
 
    if (key < p->data){
        p->lchild = Delete(p->lchild, key);
    } else if (key > p->data){
        p->rchild = Delete(p->rchild, key);
    } else {
        if (Height(p->lchild) > Height(p->rchild)){
            q = InPre(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        } else {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
    return p;
}

int minValue(struct Node* node)  
{  
	struct Node* current = node;  
  
	while (current->lchild != NULL)  
	{  
    		current = current->lchild;  
	}  
	int x=current->data;
	Delete(root,current->data); 
	return x;
}  

int maxValue(struct Node* node) 
{    
    struct Node* current = node; 
    while (current->rchild != NULL)  
        current = current->rchild; 
    int y=current->data;	
    Delete(root,current->data);
    return y; 
} 

int main()
{
	Insert(10);
    Insert(5);
    Insert(20);
    Insert(8);
    Insert(30);    //(a)
	Preorder(root);   //(b)
	printf("First minimum value = %d\n",minValue(root));    //(c)
	printf("Second minimum value = %d\n",minValue(root));   //(c)
	printf("First maximum value = %d\n",maxValue(root));	//(d)
	printf("Second maximum value = %d\n",maxValue(root));	//(d)
	return 0;
}



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct treenode{
	int info;
	struct treenode *parent;
	struct treenode *lchild;
	struct treenode *rchild;
};

typedef struct treenode *NODEPTR;

NODEPTR getNode(int x){
	NODEPTR p;
	p = (NODEPTR) malloc(sizeof(struct treenode));
	p->info = x;
	p->lchild = NULL;
	p->rchild = NULL;
	p->parent = NULL;
	return p;
}

struct tree{
	NODEPTR root;
};
typedef struct tree *TREEPTR;

TREEPTR createTree(){
	TREEPTR tp;
	tp = (TREEPTR) malloc(sizeof(struct tree));
	tp->root = NULL;
	return tp;
}

NODEPTR addlchild(NODEPTR p, int x){
	NODEPTR cp = getNode(x);
	if(p->lchild != NULL) return;
	p->lchild = cp;
	cp->parent = p;
	return cp;
}

NODEPTR addrchild(NODEPTR p, int x){
	NODEPTR cp = getNode(x);
	if(p->rchild != NULL) return;
	p->rchild = cp;
	cp->parent = p;
	return cp;
}

void preorder(NODEPTR tree){
	if(tree == NULL) return;
	printf("%d  ",tree->info);
	preorder(tree->lchild);
	preorder(tree->rchild);
}

void inorder(NODEPTR tree){
	if(tree== NULL) return;
	inorder(tree->lchild);
	printf("%d  ",tree->info);
	inorder(tree->rchild);
}


int main(){
	TREEPTR tp;
	NODEPTR root,lc, rc, lc1, lc2;
	tp = createTree();
	root = getNode(0);

	tp->root = root;
	lc = addlchild(root, 1);
	rc = addrchild(root, 2);
	lc1 = addlchild(lc, 3);
	lc2 = addrchild(lc, 4);

	printf("preorder: ");
	preorder(tp->root);
	printf("\n");
	printf("inorder:  ");
	inorder(tp->root);
	printf("\n");

	return 0;
}

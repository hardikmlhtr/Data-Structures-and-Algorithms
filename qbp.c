#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct treenode{
	int info;
	int level;
	char* operands;
	struct treenode *parent;
	struct treenode *lchild;
	struct treenode *rchild;
};

typedef struct treenode *NODEPTR;

NODEPTR getNode(int x){
	NODEPTR p;
	p = (NODEPTR) malloc(sizeof(struct treenode));
	p->info = x;
	p->level = -1;
	p->operands = NULL;
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
	tp->root = getNode(-1);
	tp->root->level = 0;
	tp->root->operands = "";
	return tp;
}

NODEPTR addlchild(NODEPTR p, int x){
	NODEPTR cp = getNode(x);
	if(p->lchild != NULL) return;
	cp->level = p->level + 1;
	cp->operands = (char*)malloc(strlen(p->operands) +1);
	strcpy(cp->operands, p->operands);
	strcat(cp->operands,"0");
	p->lchild = cp;
	cp->parent = p;
	return cp;
}

NODEPTR addrchild(NODEPTR p, int x){
	NODEPTR cp = getNode(x);
	if(p->rchild != NULL) return;
	cp->level = p->level + 1;
	cp->operands = (char*)malloc(strlen(p->operands) +1);
	strcpy(cp->operands, p->operands);
	strcat(cp->operands,"1");
	p->rchild = cp;
	cp->parent = p;
	return cp;
}

int isOperand(char ch)
{
    if ((ch >= 'A' && ch <= 'Z'))
    return 1;
    return 0;
}

int height(char* exp){
	int h = 0, i=0, ch = 0 ;
	while(exp[i] != '\0'){
		if(isOperand(exp[i])){
			if(exp[i] > ch){
				ch = exp[i];
				h = ch - 'A' + 1;
			}
		}
		i++;
	}
	return h;
}

int isLeaf(NODEPTR p){
	return (p->lchild == NULL && p->rchild == NULL);
}

void buildtree(NODEPTR root, char *s){
	NODEPTR cpl, cpr;
	if(root->level < height(s)){
		cpl = addlchild(root,-1);
		cpr = addrchild(root,-1);
		buildtree(cpl, s);
		buildtree(cpr, s);
	}
	else{
		root->info = evalString(s,root->operands);
	}
}

int evalNode(NODEPTR root){
	if(isLeaf(root)) {
		return root->info;
	}
	else{
		if((root->level) % 2 == 0) {
			root->info = evalNode(root->lchild) | evalNode(root->rchild);
		}
		else if((root->level) % 2 == 1) {
			root->info = evalNode(root->lchild) & evalNode(root->rchild);
		}
	}
	return root->info;
}

void preorder(NODEPTR tree){
	if(tree == NULL) return;
	printf("%d",tree->info);
	preorder(tree->lchild);
	preorder(tree->rchild);
}

int evalString(char* s, char* operands){
	int i, j;
	
	int valCopy[height(s)];

	j = 0;
	for(j;j<height(s);j++){
		valCopy[j] = operands[j] - '0';
	}
	i=0;
/*
	while(s[i] != '\0'){
		if(s[i] == '-'){
			if(valCopy[s[i+1] - 'A'] == 0) valCopy[s[i+1] - 'A'] = 1;
			else if(valCopy[s[i+1] - 'A'] == 1) valCopy[s[i+1] - 'A'] = 0;
		}
		i++;
	}
*/
	i = 0;

	while(s[i] != '\0'){
		int in,resOR;
		if(s[i] == '('){
			in=1;	
			resOR=0;
			int k=0;
			while(s[i+k] != ')'){
				if(s[i+k] == '-'){
					if(valCopy[s[i+k+1] - 'A'] == 0) valCopy[s[i+k+1] - 'A'] = 1;
					else if(valCopy[s[i+k+1] - 'A'] == 1) valCopy[s[i+k+1] - 'A'] = 0;
				}
				k++;
			} 
		}
		if(isOperand(s[i])){
			if (in == 1 && valCopy[s[i]- 'A'] == 1) resOR = 1;
		}

		if(s[i] == ')'){
			if(resOR == 0) return 0;
			in=0;
			j = 0;
			for(j;j<height(s);j++){
				valCopy[j] = operands[j] - '0';
			}
		} 
		i++;
	}
	
	return 1;

}


int main(int argc, char** argv){
	char* s;
	s = (char*)malloc(500*sizeof(char));
	int h;
	scanf("%s", s);
	h = height(s);

	TREEPTR tp;
	tp = createTree();
	buildtree(tp->root, s);
	evalNode(tp->root);
	preorder(tp->root);
	printf("\n");
	return 0;

}

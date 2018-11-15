#include<stdio.h>

struct No{
	int number;
	struct No * left;
	struct No * right;
};

typedef struct No No;

int main(int argc, char const *argv[])
{
	





	return 0;
}
void addnode(No * root, int number){
	if(root == NULL){
		root = (No *) malloc(sizeof(No));
		root->right = NULL;
		root->left = NULL;
		return;
	}else if( number > root->number){
		if(root->right == NULL){
			root->right = (No *) malloc(sizeof(No));
			root->right->number = number;
			root->right->right = NULL;
			root->right->left = NULL;
			return;
		}else{
			addnode(root->right , number);
			return;
		}

	}



}

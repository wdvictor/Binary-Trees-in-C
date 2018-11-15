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
	//check if exist some root node
	if(root == NULL){
		root = (No *) malloc(sizeof(No));
		root->right = NULL;
		root->left = NULL;
		return;
	}else if( number < root->number){
		if(root->left == NULL){
			//if the right node is empty, just put the value there
			root->left = (No *) malloc(sizeof(No));
			root->left->number = number;
			root->left->right = NULL;
			root->left->left = NULL;
			return;
		}else{
			//other wise repeat the step
			addnode(root->left , number);
			return;
		}

	}else{
		//go to right subtree if the number is greater or equal than root value
		if(root->right == NULL){
			//if the right node is empty, just put the value there
			root->right = (No *) malloc(sizeof(No));
			root->right->number = number;
			root->right->right = NULL;
			root->right->left = NULL;
			return;
		}else{
			//other wise repeat the step
			addnode(root->right , number);
			return;
		}

	}



}

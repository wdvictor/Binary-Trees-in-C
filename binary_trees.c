/********************************************************************************************
| > TRABALHO 5																				|
|-------------------------------------------------------------------------------------------|
|	# ALUNO(S):																				|
|		- JULIO CESAR LITWIN LIMA	| MATRÍCULA: 16/0129443									|
|		- VICTOR HUGO 				| MATRÍCULA: 17/0063844									|
|		- KAIQUE HENRIQUE BORGES 	| MATRÍCULA: 17/0014771									|
|																							|
********************************************************************************************/

/* Include's */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//to compile this use -lm parameter

/* Define's */
#define FILE_NAME			"./BSTs/bst%d.txt"		

/* Struct's */
struct No 
{
	int number;

	struct No * left;
	struct No * right;
};



typedef struct No No;


/* Functions */
void menu(No* node);

char* getFileName(int index);
No* loadTreeFromFile(char* fileName, int* error);
No* removeValue(No * root , int value);
No* initNode(int number);
No* addNode(No * root, int number);
int getHeight(No * node);
No* find_node(No * node, int number);
void isFull(No * node, int size_of_tree);
void printInOrder(No * root);
void printPreOrder(No * root);
void printPostOrder(No * root);
void freeTree(No * root);
void showTree(No * root);
int count_tree_nodes(No * root);
int search_value(No * root , int value, No * father);

int main(int argc, char const *argv[])
{
	int error = 0;

	// TODO : Add option for choice what index will be to loaded.
	char* fileName = getFileName(1);

	// Read file.
	No* node = loadTreeFromFile(fileName, &error);
	if (error != 0 || node == NULL)
	{
		switch (error)
		{
		case -1:
			printf("Failed to read %s file.\n", fileName);
			break;
		case -2:
			printf("Failed to load file, size is 0.\n");
			break;
		case -3:
			printf("Failed to alloc buffer.\n");
			break;
		case -4:
			printf("Buffer is null.\n");
			break;
		case -5:
			printf("Failed to alloc buffer in node.\n");
			break;
		case -6:
			printf("Failed to read %s file.\n", fileName);
			break;
		case -7:
			printf("Failed to alloc buffer.\n");
			break;
		default:
			printf("Unknown error.\n");
			break;
		}

		// TODO : add for choice again other bst file to load.

		// Exit, because don't laoded with success.
		return -1;
	}

	// Show menu.
	menu(node);

	return 0;
}

void menu(No* node)
{
	int option = -1, input_number;

	printf("##################################################################\n");
	printf("# -------------------------------------------------------------- #\n");
	printf("# [OPTIONS]:                                                     #\n");
	printf("# -------------------------------------------------------------- #\n");
	printf("#                                                                #\n");
	printf("# [1]. Show Tree.                                                #\n");
	printf("# [2]. Add value.                                                #\n");
	printf("# [3]. remove value.                                             #\n");
	printf("# [4]. Search value.                                             #\n");
	printf("# [5]. See if tree is full.                                      #\n");
	printf("# [6]. Tree height.                                              #\n");
	printf("# [9]. Quit                                                      #\n");
	printf("#                                                                #\n");
	printf("##################################################################\n");

	do
	{
		printf("> ");

		scanf("%d", &option);

		printf("\n");

		switch (option)
		{
		case 1:
			showTree(node);
			break;
		case 2:
			printf("Enter with the value\n");
			scanf("%d", &input_number);
			node = addNode(node , input_number);
			break;
		case 3:
			printf("Enter with the value to remove\n");
			scanf("%d", &input_number);
			node = removeValue(node , input_number);
			break;
		case 4:
			printf("Enter with the value to search\n");
			int n, temp;
			scanf("%d", &n);
			No * father = NULL;
			temp = search_value(node , n, father);
			printf("Level : %d\n", temp);
			break;
		case 5:
			isFull(node, count_tree_nodes(node));
			break;
		case 6:
			printf("tree height = %d\n", getHeight(node));
			break;
		case 9:
			exit(1);
		default:
			printf("Unknown command, please try again.\n");
			break;
		}

		printf("\n");

	} while (option != 9);
}

char* getFileName(int index)
{
	int len = strlen(FILE_NAME);
	char* fileName = (char*)malloc(sizeof(char) * (len - 1));

	sprintf(fileName, FILE_NAME, index);
	return fileName;
}

No* loadTreeFromFile(char* fileName, int* error)
{
	// Load file.
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		*error = -1;
		return NULL;
	}

	// Let to put position in last character for get size of the file.
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	if (fileSize == 0)
	{
		fclose(file);

		*error = -2;
		return NULL;
	}

	// Now let to return for initial position.
	fseek(file, 0, SEEK_SET);

	// Let to process the buffers.
	char* buffer = (char*)malloc(fileSize);
	if (buffer == NULL)
	{
		fclose(file);

		*error = -3;
		return NULL;
	}

	char* currentToken = NULL;
	int currentBuffer = 0;
	int i = 0;
	int k = 0;

	// Get buffer of the file.
	fread(buffer, 1, fileSize, file);
	if (buffer == NULL)
	{
		fclose(file);

		*error = -4;
		return NULL;
	}

	// BST.
	No* node = NULL;

	char* tmpBuffer = NULL;
	int currentValue = 0;

	int position = 0;
	int diff = 0;

	// Get count of spaces.
	for (i = 0; i <= fileSize; i++)
	{
		char c = buffer[i];

		if (buffer[i] == '\n' && buffer[i + 1] == ' ')
		{
			// Update next start position from next value.
			position = (i + 1);
			continue;
		}
		else if (buffer[i] == ' ' || (buffer[i] == '\n' && buffer[i + 1] != ' ') || i == fileSize)
		{
			diff = (i - position) - 1;
			if (diff < 0)
			{
				// Update next start position from next value.
				position = (i + 1);
				continue;
			}

			// Alloc memory for tmp buffer.
			tmpBuffer = (char*)malloc(sizeof(char) * diff);
			if (tmpBuffer == NULL)
			{
				*error = -6;
				return NULL;
			}

			// Ignore rest of 
			if (tmpBuffer[diff + 1] != NULL)
			{
				tmpBuffer[diff + 1] = '\0';
			}

			// Copy values in string.
			for(k = 0; k <= diff; k++)
			{
				tmpBuffer[k] = buffer[position + k];
			}

			// Now convert this value in string to int.
			currentValue = atoi(tmpBuffer);
			
			// Let to add value in our tree.
			node = addNode(node, currentValue);

			// Update next start position from next value.
			position = (i + 1);
		}
	}

	// Let to close file.
	fclose(file);

	*error = 0;
	return node;
}

No* initNode(int number)
{
	No* node = (No*)malloc(sizeof(No));
	if (node == NULL)
	{
		printf("Failed to alloc node.\n");
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
	node->number = number;

	return node;
}

No* addNode(No * root, int number) 
{
	// Check if root is already initialized, if not, let to init.
	if (root == NULL)
	{
		No* tmp = initNode(number);
		return tmp;
	}
	else
	{
		// Our root is already initialized, then let to compare values in bst and check where we'll to add.
		if (number < root->number)
		{
			root->left = addNode(root->left, number);
		}
		else
		{
			root->right = addNode(root->right, number);
		}
	}

	return root;
}

No * find_node(No * node, int number)
{
	No * temp = NULL;
	if (node == NULL)
	{
		printf("Element not found in the tree or the tree is empty\n");
		return NULL;
	}
	else if (number == node->number)
	{
		return node;
	}
	else if (number < node->number)
	{
		temp = find_node(node->left, number);
	}
	else if (number > node->number)
	{
		temp = find_node(node->right, number);
	}
	else
	{
		printf("There are no such element in the tree\n");
	}
	return temp;
}


int getHeight(No * node)
{
	if (node == NULL)
		return 0;

	int leftheight = getHeight(node->left);
	int rightheight = getHeight(node->right);

	if (leftheight > rightheight)
	{
		return leftheight + 1;
	}
	else
	{
		return rightheight + 1;
	}
}

void showTree(No * root)
{
	if (root != NULL)
	{
		printf("%d\n", root->number);
		showTree(root->right);
		showTree(root->left);
	}
}

void printInOrder(No * root)
{
	if (root == NULL)
		return;

	printInOrder(root->left);
	printf("%d ", root->number);
	printInOrder(root->right);
}

void printPreOrder(No * root)
{
	if (root == NULL)
		return;

	printf("%d ", root->number);
	printPreOrder(root->left);
	printPreOrder(root->right);
}

void printPostOrder(No * root)
{
	if (root == NULL)
		return;

	printPostOrder(root->left);
	printPostOrder(root->right);
	printf("%d ", root->number);
}

void freeTree(No * root)
{
	if (root == NULL)
		return;

	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

No* removeValue(No * root , int value)
{
	
	if(root == NULL)
	{
		printf("Element not found or the tree is empty\n");
		return NULL;
	}
	else if(value < root->number)
	{
		root->left = removeValue(root->left, value);
	}
	else if(value > root->number)
	{
		root->right = removeValue(root->right, value);
	}
	else
	{
		
		if(root->left == NULL && root->right == NULL)
		{//leaf		
			free(root);
			root = NULL;
		}
		else if( root->left == NULL)
		{//in case of right children		
			root = root->right;		
		}
		else if(root->right == NULL)
		{//in case of left children	
			root = root->left;	
		}
		else
		{//in case of both children exist
			No * temp = root->left;
			while(temp->right != NULL) temp = temp->right;
			root->number = temp->number;
			root->left = removeValue(root->left , root->number);
			free(temp);
		}

	}
	return root;
	
}

void isFull(No * node, int tree_total_elements)
{
	/*
		the tatic where is use the mathematic fuction to see if the tree is full
		the Sn = (2^h - 1)
	*/
	int total_elements = (pow(2, getHeight(node)) - 1);
	if(total_elements == tree_total_elements)
	{
		printf("Is full\n");
	}
	else
	{
		printf("Is not full\n");
	}
	
}

int count_tree_nodes(No * root)
{
	/*
		the count must start with 1 because the recursive fuction jump
	the mian root node
	*/
	int total = 1;
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		total += count_tree_nodes(root->left);
		total += count_tree_nodes(root->right);
		return total;
	}
}

int search_value(No * root , int value, No * father)
{
	
	int level = 1;

	if(root->number == value)
	{
		if(father != NULL)
		{
			printf("################################\n" );
			printf("# Father number %d\n", father->number);
			if(father->right == root && father->left != NULL)
			{
				printf("# Brother Status : Exist\n");
				printf("# Brother Value : %d\n", father->left->number);
				printf("################################\n" );
			}
			else if (father->left == root && father->right != NULL)
			{
				printf("# Brother Status : Exist\n");
				printf("# Brother Value : %d\n", father->right->number);
				printf("################################\n" );
			}
			else
			{
				printf("# Brother Status : None   \n");
				printf("################################\n" );
			}

		}
		return level;
	}
	else if(value < root->number)
	{
		level += search_value(root->left, value, root);
		return level;
	}
	else if( value > root->number)
	{			
		level += search_value(root->right, value, root);
		return level;
	}
	else
	{
		printf("Value not found in the tree\n");
		return 0;
	}
	
}

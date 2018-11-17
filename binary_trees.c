/********************************************************************************************
| > TRABALHO 5																				|
|-------------------------------------------------------------------------------------------|
|	# ALUNO(S):																				|
|		- JULIO CESAR LITWIN LIMA	| MATRÍCULA: 16/0129443									|
|		- VICTOR HUGO 				| MATRÍCULA: 17/0063844								    |
|		- KAIQUE HENRIQUE BORGES 	| MATRÍCULA: 17/0014771								    |
|																							|
********************************************************************************************/

/* Include's */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define's */
#define FILE_NAME "./BSTs/bst%d.txt"		

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

int getHeight(No * node);
char* getFileName(int index);
No* loadTreeFromFile(char* fileName, int* error);
No* initNode(int number);
int getHeight(No * node);
void searchvalue(No * node , int number);
No * addNode(No * root, int number);
void printInOrder(No * root);
void printPreOrder(No * root);
void printPostOrder(No * root);
void freeTree(No * root);

void showTree(No * root);

int main(int argc, char const *argv[])
{
	int error = 0;

	// TODO : Add option for choice what index will be to loaded.
	char* fileName = getFileName(1);

	// Read file.
	No* node = loadTreeFromFile(fileName, &error);
	if (error != 0 || (node == NULL && error != 0))
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

	free(fileName);
	freeTree(node);
	node = NULL;

	return 0;
}

void menu(No* node)
{
// 	int option = -1;

// 	do
// 	{
// /*
// 		// Clear console output.
// #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
// 		system("clear");
// #endif

// #if defined(_WIN32) || defined(_WIN64)
// 		system("cls");
// #endif
// */
// //(victor) i had to comment on this because after selecting an option, the output
// //was clean and could no see the results 

// 		printf("##################################################################\n");
// 		printf("# -------------------------------------------------------------- #\n");
// 		printf("# [OPTIONS]:                                                     #\n");
// 		printf("# -------------------------------------------------------------- #\n");
// 		printf("#                                                                #\n");
// 		printf("# [1]. Add new Node.                                             #\n");
// 		printf("# [2]. Delete node.                                              #\n");
// 		printf("# [3]. Show Tree.                                                #\n");
// 		printf("# [4]. Search value.                                             #\n");
// 		printf("# [5]. Print in order.                                           #\n");
// 		printf("# [6]. Print pre order.                                          #\n");
// 		printf("# [7]. Print post order.                                         #\n");
// 		printf("# [9]. Quit                                                      #\n");
// 		printf("#                                                                #\n");
// 		printf("##################################################################\n");

// 		scanf("%d", &option);
// 		int number;
// 		switch (option)
// 		{
// 		case 1:
// 			printf("Enter a new number:");
// 			scanf("%d", &number);
// 		 	node = addNode(node , number);
// 		 	/*
// 		 	(victor)
// 		 		the number added in the tree are added two times, or maybe the showtree
// 		 		function are showing the option twice
// 		 		i belive there second option are more real
// 		 	*/
// 			break;
// 		case 3:
// 			showTree(node);
// 			break;
// 		case 4:
// 			printf("Enter with the value to search\n");
// 			scanf("%d", &number);
// 			searchvalue(node , number);
// 			break;
// 		case 5:
// 			printInOrder(node);
// 			printf("\n");
// 			break;
// 		case 6:
// 			printPreOrder(node);
// 			printf("\n");
// 			break;
// 		case 7:
// 			printPostOrder(node);
// 			printf("\n");
// 			break;
// 		default:
// 			printf("Unknown command, please try again.\n");
// 			break;
// 		}
// 	} while (option != 9);
}

char* getFileName(int index)
{
	int len = strlen(FILE_NAME);
	char* fileName = (char*)malloc(sizeof(char) * len);

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

	No* node = (No *) calloc(1, sizeof(No));
	if (node == NULL)
	{
		*error = -7;
	}

	char* tmpBuffer = NULL;
	int currentValue = 0;

	int position = 0;
	int diff = 0;

	// Get count of spaces.
	for (i = 0; i < fileSize; i++)
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
			for(k = 0; k < diff; k++)
			{
				tmpBuffer[k] = buffer[position + k];
			}

			// Now convert this value in string to int.
			currentValue = atoi(tmpBuffer);

			// Let to add value in our tree.
			node = addNode(node, currentValue);

			// Update next start position from next value.
			position = (i + 1);

			free(tmpBuffer);
		}
	}

	// Let to close file.
	fclose(file);

	*error = 0;
	free(buffer);
	return node;
}

No* initNode(int number)
{
	No* node = (No*)malloc(sizeof(No));
	if (node == NULL)
	{
		printf("Failed to initialize node.\n");
		return NULL;
	}
	node->number = number;
	node->left = NULL;
	node->right = NULL;

	return node;
}


No * addNode(No * root, int number) 
{
	if(root == NULL)
	{			
		No * tmp = initNode(number);
		return tmp;
	}else
	{
		if(number < root->number)
		{
			root->left = addNode(root->left, number);
		}else
		{		
			root->right = addNode(root->right , number);
		}
	}
	return root;
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

void searchvalue(No * node , int number)
{
	if(node == NULL)
	{
		printf("There are no elements in the tree\n");
		return;
	}
	else if(number == node->number)
	{
		printf("%d\n", node->number);
		return;
	}
	else if(number < node->number)
	{
		searchvalue(node->left , number);
	}
	else if(number > node->number)
	{
		searchvalue(node->right , number);
	}
	else
	{
		printf("There are no such element in the tree\n");
	}
}

int getHeight(No * node)
{

	if(node == NULL)
	{
		return 0;
	}
	else
	{
		
		int leftheight = getHeight(node->left);
		int rightheight = getHeight(node->right);
		if(leftheight > rightheight){
			return leftheight + 1;
		}else{
			return rightheight + 1;
		}

	}

}

void printInOrder(No * root)
{
	if(root == NULL){
		return;
	}

	printInOrder(root->left);
	printf("%d ", root->number);
	printInOrder(root->right);
}

void printPreOrder(No * root)
{
	if(root == NULL){
		return;
	}

	printf("%d ", root->number);
	printPreOrder(root->left);
	printPreOrder(root->right);
}

void printPostOrder(No * root)
{
	if(root == NULL){
		return;
	}

	printPostOrder(root->left);
	printPostOrder(root->right);
	printf("%d ", root->number);
}

void freeTree(No * root)
{
	if(root == NULL){
		return;
	}

	freeTree(root->left);
	freeTree(root->right);
	free(root);
}
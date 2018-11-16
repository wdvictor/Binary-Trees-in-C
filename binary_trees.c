/********************************************************************************************
| > TRABALHO 5																				|
|-------------------------------------------------------------------------------------------|
|	# ALUNO(S):																				|
|		- JULIO CESAR LITWIN LIMA	| MATRÍCULA: 16/0129443									|
|		- VICTOR HUGO 				| MATRÍCULA: 00/0000000									|
|																							|
********************************************************************************************/

/* Include's */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

No* initNode();
void addNode(No * root, int number);

void showTree(No * root);

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
	int option = -1;

	do
	{
		// Clear console output.
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
		system("cls");
#endif

		printf("##################################################################\n");
		printf("# -------------------------------------------------------------- #\n");
		printf("# [OPTIONS]:                                                     #\n");
		printf("# -------------------------------------------------------------- #\n");
		printf("#                                                                #\n");
		printf("# [1]. Show Tree.                                                #\n");
		printf("# [9]. Quit                                                      #\n");
		printf("#                                                                #\n");
		printf("##################################################################\n");

		scanf("%d", &option);

		switch (option)
		{
		case 1:
			showTree(node);
			break;
		default:
			printf("Unknown command, please try again.\n");
			break;
		}
	} while (option != 9);
}

char* getFileName(int index)
{
	int len = strlen(FILE_NAME);
	char* fileName = (char*)malloc(sizeof(char) * len - 1);

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

	No* node = initNode();
	if (node == NULL)
	{
		*error = -7;
	}

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
			addNode(node, currentValue);

			// Update next start position from next value.
			position = (i + 1);
		}
	}

	// Let to close file.
	fclose(file);

	*error = 0;
	return node;
}

No* initNode()
{
	No* node = (No*)malloc(sizeof(No));
	if (node == NULL)
	{
		printf("Failed to initialize node.\n");
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;

	return node;
}

void addNode(No * root, int number) 
{
	//check if exist some root node
	if (root == NULL) 
	{
		root = (No *)malloc(sizeof(No));
		root->right = NULL;
		root->left = NULL;
		root->number = number;
		return;
	}
	else if (number < root->number)
	{
		if (root->left == NULL)
		{
			//if the right node is empty, just put the value there
			root->left = (No *)malloc(sizeof(No));
			root->left->number = number;
			root->left->right = NULL;
			root->left->left = NULL;
			return;
		}
		else 
		{
			//other wise repeat the step
			addNode(root->left, number);
			return;
		}
	}
	else 
	{
		//go to right subtree if the number is greater or equal than root value
		if (root->right == NULL)
		{
			//if the right node is empty, just put the value there
			root->right = (No *)malloc(sizeof(No));
			root->right->number = number;
			root->right->right = NULL;
			root->right->left = NULL;
			return;
		}
		else 
		{
			//other wise repeat the step
			addNode(root->right, number);
			return;
		}
	}
}

void showTree(No * root) 
{
	if (root != NULL) 
	{ 
		//printf the right subtree
		printf("%d\n", root->number);
		showTree(root->right);
	}

	if (root != NULL) 
	{ 
		//printf the left subtree
		printf("%d\n", root->number);
		showTree(root->left);
	}

}
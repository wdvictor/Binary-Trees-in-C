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
#define MAX_BST_QUANTITY	6

/* Struct's */
struct No
{
	int number;

	struct No * left;
	struct No * right;
};



typedef struct No No;


/* Functions */
char* menuFile();
void menu(No* node);

char* getFileName(int index);
No* loadTreeFromFile(char* fileName, int* error);
No* removeValue(No * root, int value);
No* initNode(int number);
No* addNode(No * root, int number);
int getHeight(No * node);
No* find_node(No * node, int number);
void isFull(No * node, int size_of_tree);
void printInOrder(No * root);
void printPreOrder(No * root);
void printPostOrder(No * root);
void freeTree(No * root);
No* balanceTree(No* root);
void showTree(No * root);
int count_tree_nodes(No * root);
int search_value(No * root, int value, No * father);



int main(int argc, char const *argv[])
{
	int error = 0;

	//char* fileName = getFileName(1);
	char* fileName = menuFile();

	// Read file.
	No* node = loadTreeFromFile(fileName, &error);
	if (error != 0 || node == NULL)
	{
		switch (error)
		{
		case -1:
			printf("File [%s] not found.\n", fileName);
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

		// Exit, because don't laoded with success.
		return -1;
	}

	// Show menu.
	menu(node);

	return 0;
}

char* menuFile()
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
	printf("# [OPTION FOR LOAD BST FILE]:                                    #\n");
	printf("# -------------------------------------------------------------- #\n");
	printf("#                                                                #\n");
	printf("# [1]. Choice number between [1 ~ %d]                             #\n", MAX_BST_QUANTITY);
	printf("# [2]. Custom file.                                              #\n");
	printf("# [9]. Quit program.                                             #\n");
	printf("#                                                                #\n");
	printf("##################################################################\n\n");

	int option = -1;

	do
	{
		printf("> ");
		scanf("%d", &option);
		printf("\n");

		switch (option)
		{
		case 1:
		{
			int number;
			int valid = 0;

			printf("# Choice number between [1 ~ %d]                                  #\n", MAX_BST_QUANTITY);

			do
			{
				printf("> ");
				scanf("%d", &number);
				printf("\n");

				valid = (number >= 1 && number <= MAX_BST_QUANTITY) ? 1 : 0;

			} while (valid == 0);

			return getFileName(number);
		}
		case 2:
		{
			char* name = (char*)malloc(sizeof(char) * _MAX_PATH);
			printf("# Digit name of file. (example: ./BSTs/customBSTFile.txt)        #\n");

			printf("> ");
			scanf(" %[^\n]s", name);
			printf("\n");

			return name;
		}
		default:
			printf("Unknown command, please try again.\n");
			break;
		}

		printf("\n");

	} while (option != 9);

	return NULL;
}

void menu(No* node)
{
	int option = -1, input_number;

	printf("##################################################################\n");
	printf("# -------------------------------------------------------------- #\n");
	printf("# [OPTIONS]:                                                     #\n");
	printf("# -------------------------------------------------------------- #\n");
	printf("# [0]. Show Tree.                                                #\n");
	printf("# [1]. Add value.                                                #\n");
	printf("# [2]. Remove value.                                             #\n");
	printf("# [3]. Search value.                                             #\n");
	printf("# [4]. See if tree is full.                                      #\n");
	printf("# [5]. Tree height.                                              #\n");
	printf("# [6]. Print In Order.                                      	 #\n");
	printf("# [7]. Print Pre Order.                                          #\n");
	printf("# [8]. Print Post Order.                                         #\n");
	printf("# [9]. Pega na minha e balança.                                  #\n");
	printf("# [10]. Quit                                                     #\n");
	printf("#                                                                #\n");
	printf("##################################################################\n");

	do
	{
		printf("> ");

		scanf("%d", &option);

		printf("\n");

		switch (option)
		{
		case 0:
			showTree(node);
			break;
		case 1:
			printf("Enter with the value\n");
			scanf("%d", &input_number);
			node = addNode(node, input_number);
			break;
		case 2:
			printf("Enter with the value to remove\n");
			scanf("%d", &input_number);
			node = removeValue(node, input_number);
			break;
		case 3:
		{
			printf("Enter with the value to search\n");
			int n, temp;
			scanf("%d", &n);
			No * father = NULL;
			temp = search_value(node, n, father);
			printf("Level : %d\n", temp);
			printf("################################\n");
		}
		break;
		case 4:
			isFull(node, count_tree_nodes(node));
			break;
		case 5:
			printf("tree height = %d\n", getHeight(node));
			break;
		case 6:
			printInOrder(node);
			break;
		case 7:
			printPreOrder(node);
			break;
		case 8:
			printPostOrder(node);
			break;
		case 9:
			node = balanceTree(node);
			break;
		case 10:
			exit(1);
			break;
		default:
			printf("Unknown command, please try again.\n");
			break;
		}

		printf("\n");

	} while (option != 10);
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
			for (k = 0; k <= diff; k++)
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
	{
		return 0;
	}

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

typedef struct sPRINT_POSITION_TREE
{
	int x;
	int y;

	char text[256];
} PrintPositionTree, *PrintPositionTreePtr;

typedef struct sLIST
{
	PrintPositionTreePtr data;

	struct sLIST* prev;
	struct sLIST* next;
} List, *ListPtr;

void printSpaces(int count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		printf(" ");
	}
}

ListPtr CreateList(PrintPositionTreePtr data)
{
	ListPtr lst = (ListPtr)malloc(sizeof(List));
	if (lst == NULL)
	{
		printf("Failed to alloc!\n");
		return NULL;
	}

	lst->data = data;
	lst->prev = NULL;
	lst->next = NULL;

	return lst;
}

void Push(ListPtr* current, PrintPositionTreePtr data)
{
	ListPtr lst = CreateList(data);

	lst->next = (*current);
	lst->prev = NULL;

	if ((*current) != NULL)
		(*current)->prev = lst;

	(*current) = lst;
}

ListPtr Pop(ListPtr* current, ListPtr lstDelete)
{
	if ((*current) == NULL ||
		lstDelete == NULL)
	{
		printf("Failed to remove.\n");
		return NULL;
	}

	if ((*current) == lstDelete)
	{
		(*current) = lstDelete->next;
	}

	if (lstDelete->next != NULL)
	{
		lstDelete->next->prev = lstDelete->prev;
	}

	if (lstDelete->prev != NULL)
	{
		lstDelete->prev->next = lstDelete->next;
	}

	free(lstDelete);

	return (*current);
}

void generateTreeListText(No *root, ListPtr* lst, int h, int H, int mid)
{
	if (root == NULL)
		return;

	PrintPositionTreePtr data = NULL;

	int x = mid, i;
	int y = 1 + (H*(H + 1)) / 2 - (h*(h + 1)) / 2;

	data = (PrintPositionTreePtr)malloc(sizeof(PrintPositionTree));

	data->x = x;
	data->y = y;

	sprintf(data->text, "%d", root->number);

	Push(&(*lst), data);

	if (root->right != NULL)
	{
		for (i = 1; i <= (h - 1); i++)
		{
			data = (PrintPositionTreePtr)malloc(sizeof(PrintPositionTree));
			data->x = mid + i;
			data->y = y + i;

			sprintf(data->text, "\\");

			Push(&(*lst), data);
		}

		generateTreeListText(root->right, lst, h - 1, H, mid + (h));
	}

	if (root->left != NULL)
	{
		for (i = 1; i <= (h - 1); i++)
		{
			data = (PrintPositionTreePtr)malloc(sizeof(PrintPositionTree));
			data->x = mid - i;
			data->y = y + i;

			sprintf(data->text, "/");

			Push(&(*lst), data);
		}

		generateTreeListText(root->left, lst, h - 1, H, mid - (h));
	}

}

ListPtr SortByY(ListPtr current)
{
	ListPtr auxLst = NULL;

	while (current != NULL)
	{
		ListPtr nextLst = current->next;

		current->prev = NULL;
		current->next = NULL;

		if (auxLst == NULL)
		{
			auxLst = current;
		}
		else if (auxLst->data->y >= current->data->y)
		{
			current->next = auxLst;
			current->next->prev = current;

			auxLst = current;
		}
		else
		{
			ListPtr tmpLst = auxLst;

			while (tmpLst->next != NULL && tmpLst->next->data->y < current->data->y)
				tmpLst = tmpLst->next;

			current->next = tmpLst->next;

			if (tmpLst->next != NULL)
				current->next->prev = current;

			tmpLst->next = current;
			current->prev = tmpLst;
		}

		current = nextLst;
	}

	return auxLst;
}

ListPtr SortByX(ListPtr current)
{
	ListPtr auxLst = NULL;

	while (current != NULL)
	{
		ListPtr nextLst = current->next;

		current->prev = NULL;
		current->next = NULL;

		if (auxLst == NULL)
		{
			auxLst = current;
		}
		else if (auxLst->data->x >= current->data->x)
		{
			current->next = auxLst;
			current->next->prev = current;

			auxLst = current;
		}
		else
		{
			ListPtr tmpLst = auxLst;

			while (tmpLst->next != NULL && tmpLst->next->data->x < current->data->x)
				tmpLst = tmpLst->next;

			current->next = tmpLst->next;

			if (tmpLst->next != NULL)
				current->next->prev = current;

			tmpLst->next = current;
			current->prev = tmpLst;
		}

		current = nextLst;
	}

	return auxLst;
}

ListPtr getListByPositionY(ListPtr current, int Y)
{
	ListPtr tmpList = NULL;

	while (current != NULL)
	{
		if (current->data->y == Y)
		{
			Push(&tmpList, current->data);
		}

		current = current->next;
	}

	return tmpList;
}

void displayTree(ListPtr list)
{
	if (list == NULL)
		return;

	int i;
	for (i = 0; i < 1000; i++)
	{
		ListPtr lstY = getListByPositionY(list, i);
		lstY = SortByX(lstY);

		if (lstY == NULL)
		{
			continue;
		}
		else
		{
			int i = 0;
			int space = 0;
			int strLen = 0;

			while (lstY != NULL)
			{
				if (lstY->prev == NULL)
				{
					printSpaces(lstY->data->x);
				}
				else
				{
					strLen = strlen(lstY->data->text) - 1;
					space = ((lstY->data->x - lstY->prev->data->x) - i / 2) - strLen;
					printSpaces(space);
				}

				printf("%s", lstY->data->text);

				if (lstY->next == NULL)
				{
					printf("\n");
				}

				i++;
				lstY = lstY->next;
			}
		}
	}
}

void showTree(No * root)
{
	ListPtr list = NULL;
	int h = getHeight(root);
	generateTreeListText(root, &list, h, h, h*(h + 1) / 2);

	list = SortByY(list);

	displayTree(list);
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

No * findLeft(No* root)
{
	return (root == NULL) ? NULL : (root->left == NULL) ? root : findLeft(root->left);
}

No* removeValue(No * root, int value)
{


	if (root == NULL) return NULL;

	if (value < root->number)
	{
		root->left = removeValue(root->left, value);
	}
	else if (value > root->number)
	{
		root->right = removeValue(root->right, value);
	}
	else if (root->left && root->right)
	{
		No * auxNode = findLeft(root->right);

		root->number = auxNode->number;
		root->right = removeValue(root->right, root->number);
	}
	else
	{
		No * auxNode = root;
		if (root->left == NULL)
		{
			root = root->right;
		}
		else if (root->right == NULL)
		{
			root = root->left;
		}

		free(auxNode);
	}

	return root;

	//if (root == NULL)
	//{
	//	printf("Element not found or the tree is empty\n");
	//	return NULL;
	//}
	//else if (value < root->number)
	//{
	//	root->left = removeValue(root->left, value);
	//}
	//else if (value > root->number)
	//{
	//	root->right = removeValue(root->right, value);
	//}
	//else
	//{
	//
	//	if (root->left == NULL && root->right == NULL)
	//	{//leaf		
	//		free(root);
	//		root = NULL;
	//	}
	//	else if (root->left == NULL)
	//	{//in case of right children		
	//		root = root->right;
	//	}
	//	else if (root->right == NULL)
	//	{//in case of left children	
	//		root = root->left;
	//	}
	//	else
	//	{//in case of both children exist
	//		No * temp = root->left;
	//		while (temp->right != NULL) temp = temp->right;
	//		root->number = temp->number;
	//		root->left = removeValue(root->left, root->number);
	//		free(temp);
	//	}
	//
	//}
	//return root;

}

void isFull(No * node, int tree_total_elements)
{
	/*
	the tatic where is use the mathematic fuction to see if the tree is full
	the Sn = (2^h - 1)
	*/
	int total_elements = (pow(2, getHeight(node)) - 1);
	if (total_elements == tree_total_elements)
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
	if (root == NULL)
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

int search_value(No * root, int value, No * father)
{

	int level = 1;

	if (root->number == value)
	{
		if (father != NULL)
		{
			printf("################################\n");
			printf("# Father number %d\n", father->number);
			if (father->right == root && father->left != NULL)
			{
				printf("# Brother Status : Exist\n");
				printf("# Brother Value : %d\n", father->left->number);

			}
			else if (father->left == root && father->right != NULL)
			{
				printf("# Brother Status : Exist\n");
				printf("# Brother Value : %d\n", father->right->number);
			}
			else
			{
				printf("# Brother Status : None   \n");
			}

		}
		return level;
	}
	else if (value < root->number)
	{
		level += search_value(root->left, value, root);
		return level;
	}
	else if (value > root->number)
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

int treeIsBalanced(No* root)
{
	if (root == NULL)
		return 1;

	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
	int difference = leftHeight - rightHeight;

	return (difference < -1 || difference > 1) ? 0 : treeIsBalanced(root->left) *
		treeIsBalanced(root->right);
}

No* rotationTree(No* root, No* father, No* currentRoot)
{
	if (root == NULL || treeIsBalanced(root))
		return currentRoot;

	currentRoot = rotationTree(root->left, root, currentRoot);
	if (treeIsBalanced(root))
		return currentRoot;

	currentRoot = rotationTree(root->right, root, currentRoot);
	if (treeIsBalanced(root))
		return currentRoot;

	int leftHeight = getHeight(root->left);
	int rightHegiht = getHeight(root->right);
	No* tmpNode = NULL;

	if (leftHeight > rightHegiht)
	{
		tmpNode = root->left;
		if (father == NULL)
		{
			root->left = tmpNode->right;
			tmpNode->right = root;

			currentRoot = tmpNode;
		}
		else
		{
			if (father->left == root)
				father->left = tmpNode;
			else
				father->right = tmpNode;

			root->left = tmpNode->right;
			tmpNode->right = root;
		}

		return currentRoot;
	}
	else
	{
		tmpNode = root->right;
		if (father == NULL)
		{
			root->right = tmpNode->left;
			tmpNode->left = root;

			currentRoot = tmpNode;
		}
		else
		{
			if (father->left == root)
				father->left = tmpNode;
			else
				father->right = tmpNode;

			root->right = tmpNode->left;
			tmpNode->left = root;
		}

		return currentRoot;
	}
}

No* balanceTree(No* root)
{
	if (root == NULL)
		return NULL;

	if (treeIsBalanced(root))
	{
		printf("Binary tree is already balanced.\n");
		return root;
	}

	do
	{
		root = rotationTree(root, NULL, root);
	} while (!treeIsBalanced(root));

	return root;
}
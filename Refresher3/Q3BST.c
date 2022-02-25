#include <stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node *left, *right;
};

void printMenu(){
	printf("MENU:\n");
	printf("1. Insert an element in BST.\n");
	printf("2. Delete an element from BST.\n");
	printf("3. Print the BST.");
	printf("\nAny other number to terminate the program.\n");
}

void inorderBST(struct Node *node){
	if(node == NULL){
		return;
	}
	inorderBST(node->left);
	printf("%d\t", node->data);
	inorderBST(node->right);
}

struct Node* insert(struct Node *node, int val){
	if(node == NULL){
		struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
		temp->data = val;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}

	if(val > node->data){
		node->right = insert(node->right, val);
		return node;
	}
	else if(val < node->data){
		node->left = insert(node->left, val);
		return node;
	}
	return node;	// There shouldn't be any repetetive elements in the BST
}

struct Node* delete(struct Node *node, int val){
	if(node == NULL){
		printf("\nElement not found!!\n");
		return node;
	}

	if(val > node->data){
		node->right = delete(node->right, val);
		return node;
	}
	else if (val < node->data)
	{
		node->left = delete(node->left, val);
	}
	else{
            
            if((node->left == NULL) && (node->right == NULL)){
            	struct Node *tr = node;
            	free(tr);
                return NULL;
            }
            
            if(node->left == NULL){
            	struct Node *tr = node;
            	struct Node *tx = node->right;
            	free(tr);
                return tx;
            }
            
            if(node->right == NULL){
                struct Node *tr = node;
            	struct Node *tx = node->left;
            	free(tr);
                return tx;
            }
            
            struct Node *temp = node->right;
            
            while(temp->left != NULL){
                temp = temp->left;
            }
            
            node->data = temp->data;
            
            node->right = delete(node->right, temp->data);
            
            return node;
            
        }
        
        return node;
}


int main()
{
	int opt, x;
	printMenu();

	struct Node *root = NULL;

	while(1){
		printf("\nChoose an option: ");
		scanf("%d", &opt);
		if(opt == 1){
			printf("Enter the number(integer) to be inserted: ");
			scanf("%d", &x);
			root = insert(root, x);
		}
		else if (opt == 2)
		{
			printf("Enter the number(integer) to be deleted: ");
			scanf("%d", &x);
			root = delete(root, x);
		}
		else if (opt == 3)
		{
			printf("The inorder traversal of BST is: ");
			inorderBST(root);
		}
		else{
			exit(0);
		}
	}
	return 0;
}
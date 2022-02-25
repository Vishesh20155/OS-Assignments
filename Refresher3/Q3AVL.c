#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *left, *right;
	int ht;
};

void printMenu(){
	printf("MENU:\n");
	printf("1. Insert an element in AVL Tree.\n");
	printf("2. Delete an element from AVL Tree.\n");
	printf("3. Print the AVL Tree.");
	printf("\nAny other number to terminate the program.\n");
}

void inorderBST(struct Node *node){
	if(node == NULL){
		return;
	}
	inorderBST(node->left);
	printf("%d ", node->data);
	inorderBST(node->right);
}

int NodeHt(struct Node* node)
{
	if(node == NULL)
		return 0;
	return node->ht;
}

int  findMax(int a, int b){
	if (a>b)
	{
		return a;
	}
	return b;
}

struct Node* rotateLeft(struct Node* node)
{
	struct Node *temp1 = node->right;
	struct Node *temp2 = node->right->left;
	node->right = temp2;
	temp1->left = node;
	node->ht = findMax(NodeHt(node->right), NodeHt(node->left)) + 1;
	temp1->ht = findMax(NodeHt(temp1->right), NodeHt(temp1->left)) + 1;
	return temp1;
}

struct Node* rotateRight(struct Node* node)
{
	struct Node *temp1 = node->left;
	struct Node *temp2 = node->left->right;
	node->left = temp2;
	temp1->right = node;
	node->ht = findMax(NodeHt(node->right), NodeHt(node->left)) + 1;
	temp1->ht = findMax(NodeHt(temp1->right), NodeHt(temp1->left)) + 1;
	return temp1;
}

int BalanceFactor(struct Node* node)
{
	return (NodeHt(node->right) - NodeHt(node->left));
}

struct Node* insert(struct Node* node, int val)
{
	if(node == NULL){
		struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
		temp->data = val;
		temp->ht = 1;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}

	if(val > node->data){
		node->right = insert(node->right, val);
	}
	else{
		node->left = insert(node->left, val);
	}
	node->ht = findMax(NodeHt(node->right), NodeHt(node->left)) + 1;

	if((BalanceFactor(node)<= -2) && (BalanceFactor(node->left)<= 0)){
		return rotateRight(node);
	}

	if((BalanceFactor(node)<= -2) && (BalanceFactor(node->left)> 0)){
		node->left = rotateLeft(node->left);
    	return rotateRight(node);
	}

	if((BalanceFactor(node)>=2) && (BalanceFactor(node->right)>= 0)){
		return rotateLeft(node);
	}

	if((BalanceFactor(node)>= 2) && (BalanceFactor(node->right)< 0)){
		node->left = rotateRight(node->left);
    	return rotateLeft(node);
	}	

	return node;

}

struct Node* delete(struct Node* node, int val)
{
	if(node == NULL){
		printf("\nElement not found!!\n");
		return node;
	}

	if(val > node->data){
		node->right = delete(node->right, val);
	}
	else if (val < node->data)
	{
		node->left = delete(node->left, val);
	}
	else{
            
            if((node->left == NULL) && (node->right == NULL)){
            	struct Node *tr = node;
                node = NULL;
                free(tr);
            }
            
            else if(node->left == NULL){
            	struct Node *tr = node;
                node = node->right;
                free(tr);
            }
            
            else if(node->right == NULL){
            	struct Node *tr = node;
                node = node->left;
                free(tr);
            }
            else{
	            struct Node *temp = node->right;
	            
	            while(temp->left != NULL){
	                temp = temp->left;
	            }
	            
	            node->data = temp->data;
	            
	            node->right = delete(node->right, temp->data);
            }
            
        }

   	if(node == NULL)
    	return NULL;

    node->ht = findMax(NodeHt(node->right), NodeHt(node->left)) + 1;

	if((BalanceFactor(node)<= -2) && (BalanceFactor(node->left)<= 0)){
		return rotateRight(node);
	}

	if((BalanceFactor(node)<= -2) && (BalanceFactor(node->left)> 0)){
		node->left = rotateLeft(node->left);
    	return rotateRight(node);
	}

	if((BalanceFactor(node)>=2) && (BalanceFactor(node->right)>= 0)){
		return rotateLeft(node);
	}

	if((BalanceFactor(node)>= 2) && (BalanceFactor(node->right)< 0)){
		node->left = rotateRight(node->left);
    	return rotateLeft(node);
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
			printf("The inorder traversal of AVL Tree is: ");
			inorderBST(root);
		}
		else{
			exit(0);
		}
	}
	return 0;
}


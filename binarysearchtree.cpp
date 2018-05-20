#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node *left, *right;
};

/**
 *  A utility function to create a new BST node
 * @brief newNode
 * @param item
 * @return
 */
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

/**
 *  A utility function to do inorder traversal of BST
 * @brief inorder
 * @param root
 */
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

/**
 * A utility function to insert a new node with given key in BST
 * @brief insert
 * @param node
 * @param key
 * @return
 */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

/**
 * Given a non-empty binary search tree, return the node with minimum key value found in that tree. Note that the entire tree does not
need to be searched.
 * @brief minValueNode
 * @param node
 * @return
 */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

/**
 * Given a binary search tree and a key, this function deletes the key and returns the new root
 * @brief deleteNode
 * @param root
 * @param key
 * @return
 */
struct node* deleteNode(struct node* root, int key)
{

    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);


    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = minValueNode(root->right);

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

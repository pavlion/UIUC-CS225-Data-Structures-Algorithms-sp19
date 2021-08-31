/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <iostream>
using namespace std;
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
	Node* y = t->right;
	t->right = y->left;
	y->left = t;
	t = y;
	//updateHeight();
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
	Node* y = t->left;
	t->left = y->right;
	y->right = t;
	t = y;
	//updateHeight();
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
	
    rotateRight(t->right);
	rotateLeft(t);
}

// Added helper function!
template <class K, class V>
int AVLTree<K, V>::findBalanceFactor(Node*& subtree){
	if (subtree == NULL) 
	    return 0;
	int leftHeight  = -1;
	int rightHeight = -1;
	if (subtree->left != NULL)
		leftHeight  = subtree->left->height;
	if (subtree->right != NULL)
		rightHeight = subtree->right->height;
	
	return (rightHeight - leftHeight);
}

// Added function!
template <class K, class V>
void AVLTree<K, V>::updateHeight(){
	updateHeight(root);
}

// Added helper function!
template <class K, class V>
int AVLTree<K, V>::updateHeight(Node* subtree){
	if (subtree == NULL) return -1;
	
	subtree->height = 1 + max(updateHeight(subtree->left), updateHeight(subtree->right));
	return subtree->height;
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	if (subtree == NULL) 
	    return;
    
    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	//cout<<"b="<<b<<", "<<subtree->key<<endl;
	if ( b == -2 ) {
		// calculatin the left subtree
		// b is negative, so the left subtree must not be NULL!
		int bLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
		if (bLeft == -1) rotateRight(subtree);
		else rotateLeftRight(subtree);
	}
	else if ( b == 2 ) {
		// calculatin the right subtree
		// caution: different from left side!
		int bLeft = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if (bLeft == -1) rotateRightLeft(subtree); // caution: different from left side!
		else rotateLeft(subtree);
	}
	
	//subtree->height = 1 + max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
	updateHeight();
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
	if (subtree == NULL) {
		subtree = new Node(key, value);		
	}
	else if (key < subtree->key) insert(subtree->left, key, value);
	else if (key > subtree->key) insert(subtree->right, key, value);
	updateHeight();
	rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
		remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
		remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
			delete subtree;
			subtree = NULL;
		} 
		else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here 
			Node *IOPParent = NULL;
			Node *IOP = findIOP(subtree, IOPParent);
			
			// reconnect the tree!
			//if (IOPParent != NULL)
				//IOPParent->right = IOP->left;
			// replace root of subtree with the IOP's content
			swap(subtree, IOP);
			remove(subtree->left, key);
			
        } 
		else {
            /* one-child remove */
            // your code here
			Node *temp = subtree->left ? subtree->left : subtree->right; 
			delete subtree;
			subtree = temp;
        }
        // your code here
    }
	
	rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findIOP(Node*& n, Node*& IOPParent)
{
    Node* curr = n->left; // must not be NULL: it's the two-children's case
	while(curr->right != NULL){
		IOPParent = curr;
		curr = curr->right;
	}
	
	return curr;
}

/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 *  helping mirror()
 */
template <typename T>
void BinaryTree<T>::_mirror_helper(Node* subRoot)
{
     //your code here
     if (subRoot == NULL)
         return;

     Node* temp = subRoot->right;
     subRoot->right = subRoot->left;
     subRoot->left = temp;

     // Modify left subtree
     _mirror_helper(subRoot->left);

     // Print right subtree
     _mirror_helper(subRoot->right);


}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    _mirror_helper(root);

}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
	InorderTraversal<T> iot(root);
	bool retval = true;
    //cout<<"Inorder Traversal:  ";
	TreeTraversal<int>::Iterator it = iot.begin();	
	T lastElement = (*it)->elem;
    for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        //cout<<(*it)->elem<<" ";
		if( (*it)->elem < lastElement){
			//cout<<"occur"<<endl;
			retval = false;
		}
		lastElement = (*it)->elem;
    }
    //cout<<endl;
	
    return retval;
}
/**
 *  helping isOrderedRecursive()
 */
 
////problem: only recursively check the relationship between left, subRoot, right
//// which didn't follow the InOrder ordering to check.
//// so we need to store the min and the max (representing the value of its previous and next one)
template <typename T>
bool BinaryTree<T>::_isOrderedRecursive_helper(Node* subRoot, T min, T max) const
{
    // your code here
	if(subRoot == NULL) 
		return true;
	
	if(min > subRoot->elem || max < subRoot->elem)
		return false;
	else
		return  _isOrderedRecursive_helper(subRoot->left,  min, subRoot->elem)
			  &&_isOrderedRecursive_helper(subRoot->right, subRoot->elem, max);	
	
	/*
	if(subRoot == NULL) 
		return true;
	
	if(subRoot->left != NULL){
		if(subRoot->left->elem > subRoot->elem)
			return false;
	}
	
	if(subRoot->right != NULL){
		if(subRoot->elem > subRoot->right->elem)
			return false;
	}
	
	bool retval = _isOrderedRecursive_helper(subRoot->left) &&
				  _isOrderedRecursive_helper(subRoot->right);
				
    return retval;
	*/
}
template <typename T>
T max(T a, T b){ 
	return (a > b) ? a : b;
}

template <typename T>
T min(T a, T b){ 
	return (a < b) ? a : b;
}

template <typename T>
T BinaryTree<T>::maxOfLeft(Node* subRoot) const
{
	if(subRoot->left == NULL&&subRoot->right == NULL)
		return subRoot->elem;		
	
	else if (subRoot->left == NULL && subRoot->right != NULL)
		return(max(subRoot->elem, maxOfLeft(subRoot->right)));
	
	else if (subRoot->left != NULL && subRoot->right == NULL)
		return(max(subRoot->elem, maxOfLeft(subRoot->left)));
	
	else 
		return(max(subRoot->elem, max(maxOfLeft(subRoot->left), maxOfLeft(subRoot->right))));
}

template <typename T>
T BinaryTree<T>::minOfLeft(Node* subRoot) const
{
	if(subRoot->left == NULL&&subRoot->right == NULL)
		return subRoot->elem;		
	
	else if (subRoot->left == NULL && subRoot->right != NULL)
		return min(subRoot->elem, minOfLeft(subRoot->right));
	
	else if (subRoot->left != NULL && subRoot->right == NULL)
		return min(subRoot->elem, minOfLeft(subRoot->left));
	
	else 
		return min(subRoot->elem, min(minOfLeft(subRoot->left), minOfLeft(subRoot->right)));
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
	return _isOrderedRecursive_helper(root, minOfLeft(root), maxOfLeft(root));
}

template <typename T>
void BinaryTree<T>::_getPaths_helper(Node* subRoot, 
									 std::vector<std::vector<T>> &totalPaths, 
									 std::vector<T> currPath) const
{
    // your code here
	if(subRoot == NULL) return;
	else if(subRoot->left == NULL && subRoot->right == NULL){
		currPath.push_back(subRoot->elem);
		totalPaths.push_back(currPath);
		return;
	}/*
	else if(subRoot->left == NULL && subRoot->right != NULL){		
		currPath.push_back(subRoot->elem);
		_getPaths_helper(subRoot->right, totalPaths, currPath);
	}
	else if(subRoot->left != NULL && subRoot->right == NULL){
		currPath.push_back(subRoot->elem);
		_getPaths_helper(subRoot->left, totalPaths, currPath);
	}
	else{
		currPath.push_back(subRoot->elem);
		_getPaths_helper(subRoot->left, totalPaths, currPath);
		_getPaths_helper(subRoot->right, totalPaths, currPath);
	}*/
	currPath.push_back(subRoot->elem);
	_getPaths_helper(subRoot->left, totalPaths, currPath);
	_getPaths_helper(subRoot->right, totalPaths, currPath);
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
 
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
	std::vector<T> temp;
	temp.push_back(root->elem);
	_getPaths_helper(root->left, paths, temp);
	_getPaths_helper(root->right, paths, temp);
}

/**
 * helping sumDistances() 
 */

template <typename T>
void BinaryTree<T>::_sumDistances_helper(int currDistance, Node* subRoot, int &sum) const
{
	++currDistance;
	sum += currDistance;
	if(subRoot->left != NULL)
		_sumDistances_helper(currDistance, subRoot->left, sum);
	if(subRoot->right != NULL)
		_sumDistances_helper(currDistance, subRoot->right, sum);
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
	int sum = 0;    
	_sumDistances_helper(-1,root,sum);
	return  sum;
}

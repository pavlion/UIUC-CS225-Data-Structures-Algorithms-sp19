#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
	if(root == NULL) return 0;
	else {
		return getValue(root);
	}
}

double AbstractSyntaxTree::getValue(AbstractSyntaxTree::Node* node) const{
	if(node == NULL) return 0;
	else if(node->left == NULL && node->right == NULL){
		return std::stod(node->elem);
	}
	else {
		if(node->elem == "+") return getValue(node->left) + getValue(node->right);
		else if(node->elem == "-") return getValue(node->left) - getValue(node->right);
		else if(node->elem == "*") return getValue(node->left) * getValue(node->right);
		else if(node->elem == "/") return getValue(node->left) / getValue(node->right);
		else return 0;
	}
	
}
bool AbstractSyntaxTree::isOperator(AbstractSyntaxTree::Node* node){
	return (node->elem=="+")&&(node->elem=="-")&&(node->elem=="*")&&(node->elem=="/");
}


#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include "LinkedList.h"

using namespace std;

template <typename T>	// allow an AVL tree for any data type

class AVLTree {
  public:
    class Node {
    public:
        Node():left(NULL), right(NULL), height(1) {}

        T value;	// the node itself
        Node* left;	// left child of the node
        Node* right;	// right child of the node
        int height;	// how tall the AVL tree is
    };
    
    Node* root;
    int size;
    
    AVLTree():root(NULL){}
    
    // add a value to the tree
    Node* add(const T& value, Node* node){
        if (node == NULL){
            node = new Node;
            node->value = value;
            return node;
        }
        else if (value < node->value){
            node->left = add(value, node->left);
            node = balance(node);
        }
        else if (value >= node->value){
            node->right = add(value, node->right);
            node = balance(node);
        }
        
        node->height = getHeight(node);
        
        return node;
    }
    // balance the tree
    Node* balance(Node* toBalance){
        int cDiff = findDiff(toBalance);
	// right side too heavy
        if (cDiff < -1){
            if (findDiff(toBalance->right) > 0)
                toBalance = doubLeftRot(toBalance);
            else
                toBalance = leftRot(toBalance);
            if(toBalance->left != NULL)
                toBalance->left->height = getHeight(toBalance->left);
            toBalance->height = getHeight(toBalance);
        }
	// left side too heavy
        else if (cDiff > 1){
            if (findDiff(toBalance->left) < 0)
                toBalance = doubRightRot(toBalance);
            else
                toBalance = rightRot(toBalance);
            
            if(toBalance->right != NULL)
                toBalance->right->height = getHeight(toBalance->right);
            toBalance->height = getHeight(toBalance);

        }
        return toBalance;
    }
    
    // find height difference between left side and right side of a given node
    int findDiff(Node* temp){
        if (temp == NULL)
            return 0;
        int leftHeight = getHeight(temp->left);
        int rightHeight = getHeight(temp->right);
        return (leftHeight - rightHeight);
    }
    // find the height of a given node
    int getHeight(Node* node){
        if (node == NULL)
            return 0;
        else if (getHeight(node->right) >= getHeight(node->left))
	    return (getHeight(node->right) + 1);
	else
            return (getHeight(node->left) + 1);
    }
    // do a right rotation
    Node* rightRot(Node* node){
        Node* childL;
        childL = node->left;
        
        node->left = childL->right;
        
        childL->right = node;
        
        return childL;
    }
    // do a double right rotation
    Node* doubRightRot(Node* node) {
        Node* childL = node->left;
        Node* childLR = childL->right;
        node->left = childLR;
        childL->right = childLR->left;
        childLR->left = childL;
        node->left = childLR->right;
        childLR->right = node;
        node->height = getHeight(node);
        childL->height = getHeight(childL);
        childLR->height = getHeight(childLR);
        return childLR;
    }
    // do a left rotation
    Node* leftRot(Node* node){
        Node* childR;
        childR = node->right;
        node->right = childR->left;
        childR->left = node;
        return childR;
    }
    // do a double left rotation
    Node* doubLeftRot(Node* node){
        Node* childR = node->right;
        Node* childRL = childR->left;
        childR->left = childRL->right;
        node->right = childRL;
        childRL->right = childR;
        node->right = childRL->left;
        childRL->left = node;
        node->height = getHeight(node);
        childR->height = getHeight(childR);
        childRL->height = getHeight(childRL);
        return childRL;
    }
   
   // remove(1) removes the root
   void remove(const T& value){
       root = remove(value, root);
   }
   
   // remove(2) pops a given node
   Node* remove(const T& value, Node* node)
   {
       if (node == NULL)
           return NULL;
       if (value < node->value)
           node->left = remove(value, node->left);
       else if (value > node->value)
           node->right = remove(value, node->right);
       else {
           Node* L = node->left;
           Node* R = node->right;
           if (L) {
		if (R) {
	 	    node->value = CTR(node->right);    //Findmin(current->right) (goes all the way left)
		    node->right = remove(node->value, node->right);
		}
		else {
		    delete node;
		    return L;
		}
           }
            
           else if(R){
               delete node;
               return R;
           }
            
           else{
               delete node;
               return NULL;
           }
       }
       node->height = getHeight(node);
       return balance(node);
    }
    // handle a case where you remove a node with two children
    Node* twoChildHandler(T value, Node* node){
        Node* L = node->left;
        Node* R = node->right;
        if(!L && !R){
            delete node;
            return NULL;
        }
        
	// if children on both sides
        else if(L && R){
            node->value = CTR(node->right);
            node->right = remove(node->value, node->right);
        }
        // if a child on the right
        else if(R){
            delete node;
            return R;
        }
	// else a child on the left
        else {
            delete node;
            return L;
        }
    }
    // find the leftmost node
    T CTR(Node* node){
        if (node->left == NULL)
            return node->value;
        else
            return CTR(node->left);
    }
    // find(1) returns the root
    bool find(const T& value){
        return find(value, root);
    }
    // find(2) will find a node based on its value
    bool find(const T& value, Node* node){
        if (node == NULL)
            return false;
        
        else if (node->value == value)
            return true;
        
        else if (value < node->value)
            return (find(value, node->left));
        
        else
            return (find(value, node->right));
    }
    // output the AVL tree
    void print(ofstream &writer){
        writer << "print" << endl;
        if (root == NULL)
            return;
        LinkedList<AVLTree::Node*> queue;
        queue.insert(queue.getSize(), root);

        int level = 0;
        int linefill = 0;
        while (queue.getSize() != 0){
            AVLTree::Node* temp;
            writer << "level " << level << ": ";
            linefill = 0;
            for (int levelsize = queue.getSize(); levelsize > 0; levelsize--) {
                temp = queue.getNode(0);
                queue.remove(0);
                if (linefill >= 8){
                    writer << endl << "level " << level << ": ";
                    linefill = 0;
                }
                writer << temp->value << "(" << temp->height << ") ";
                if (temp->left != NULL)
                    queue.insert(queue.getSize(), temp->left);
                if (temp->right != NULL)
                    queue.insert(queue.getSize(), temp->right);
                linefill++;
            }
            level++;
            writer << endl;
        }
    }
    // delete the AVL tree
    void clear(){
        while(root != NULL)
            remove(root->value);
    }
    ~AVLTree(){
        clear();
    }
};

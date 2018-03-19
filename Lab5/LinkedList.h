#pragma once

#include <fstream>

using namespace std;

template <typename T>	// Allow linked lists for any data type

class LinkedList {
    
    struct Node {
        Node(){
            next = NULL;
            prev = NULL;
        }
        
        T value;
        Node* next;
        Node* prev;
    };
    
    
    Node* head;
    Node* tail;
    int size;
    
public:
    // returns the number of elements in the linked list
    int getSize() const {
        return size;
    }
    
    // add [value] to the linked list at [index]
    void insert(int index, const T& value){
        Node* newNode = new Node();
        newNode->value = value;
        
	// no linked list yet
        if (size == 0){
            head = newNode;
            tail = newNode;
        }
        
	// insert at head
        else if (index == 0){
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
            
        }
        
	// insert at tail
        else if (index >= size){
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            
        }
        
	// insert somewhere in the middle
        else {
            Node* node = head;
	    // move through until you find the index right before the index to insert at
            for (int i = 0; i < (index - 1); i++)
                node = node->next;
	    newNode->next = node->next;		// next of the current node is now the next of the new node
	    newNode->prev = node;		// previous of new node is the current node
	    newNode->next->prev = newNode;	// the previous of the next node is the new node
	    node->next = newNode;		// the next of the current node is the new node
        }
        
        size++;
    }
    // delete from the linked list at [index]
    T remove(int index){
        Node* node = head;
	// go through linked list until the index of the node to delete
        for (int i = 0; i < index; i++)
            node = node->next;
        // if there's only one element in the list, just set everything to NULL
        if (size == 1){
            head = NULL;
            tail = NULL;
        }
        // delete the head
        else if (index == 0){
            head = node->next;
            node->next->prev = NULL;
        }
        // delete the tail
        else if (index == (size - 1)){
            tail = node->prev;
            node->prev->next = NULL;
        }
        // delete somewhere in the middle
        else {
            node->next->prev = node->prev;	// this node's next's previous is now this node's previous
            node->prev->next = node->next;	// this nodes' previous's next is now this node's next
        }
        size--;
        T nodeValue = node->value;
        delete node;
        return nodeValue;
    }
    // find the index of an element in the linked list based on the value
    int find(const T& value){
        Node* node = head;
        for (int i = 0; i < size; i++){
            if (node->value == value)
                return i;
            node = node->next;
	}
        return -1;
    }
    // delete the whole list
    void clear(){
        while(size != 0)
            remove(0);
    }
    // get the element at [index]
    T at(int index){
        Node* node = head;
        
        for (int i = 0; i < index; i++)
            node = node->next;
        
        return node->value;
    }
    // constructor
    LinkedList(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    // deconstructor
    ~LinkedList(){
        clear();
    }
};

#pragma once

#include <fstream>

using namespace std;

template <typename T>

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
    
    int getSize() const {
        return size;
    }
    
    void insert(int index, const T& value){
        Node* newNode = new Node();
        newNode->value = value;
        
        if (size == 0){
            head = newNode;
            tail = newNode;
        }
        
        else if (index == 0){
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
            
        }
        
        else if (index >= size){
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            
        }
        
        else {
            Node* node = head;
            for (int i = 0; i < (index - 1); i++)
                node = node->next;
            
			newNode->next = node->next;
			newNode->prev = node;
			newNode->next->prev = newNode;
			node->next = newNode;
        }
        
        size++;
    }
    
    T remove(int index){
        Node* node = head;
        
        for (int i = 0; i < index; i++)
            node = node->next;
        
        if (size == 1){
            head = NULL;
            tail = NULL;
        }
        
        else if (index == 0){
            head = node->next;
            node->next->prev = NULL;
        }
        
        else if (index == (size - 1)){
            tail = node->prev;
            node->prev->next = NULL;
        }
        
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        
        size--;
        
        T nodeValue = node->value;
        
        delete node;
        
        return nodeValue;
    }
    
    int find(const T& value){
        Node* node = head;
        
        for (int i = 0; i < size; i++){
            if (node->value == value)
                return i;
            
            node = node->next;
        }
		
        return -1;
    }
    
    void clear(){
        while(size != 0)
            remove(0);
    }
    
    T at(int index){
        Node* node = head;
        
        for (int i = 0; i < index; i++)
            node = node->next;
        
        return node->value;
    }

    LinkedList(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    
    
    ~LinkedList(){
        clear();
    }
};

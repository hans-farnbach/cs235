#pragma once
#include "LinkedList.h"

template <typename T>	// allow any data type to be a hash table

class HashSet
{
private:
    LinkedList<T>* table;
    int setSize;
    int size;
    
public:
    HashSet(){
        setSize = 0;
        size = 0;
        table = new LinkedList<T>[setSize];
    }
    
    ~HashSet(){
        clear();
        delete [] table;
    }
    // cut hash table size in half
    void sizeDown(){
        int oldSize = setSize;
        setSize = setSize >> 1;
        LinkedList<T> * oldTable = table;
        table = new LinkedList<T>[setSize];
        for(int i = 0; i < oldSize; i++){
            for(int j = 0; j < oldTable[i].getSize(); j++)
                table[hash(oldTable[i].at(j))].push_back(oldTable[i].at(j));
        }
        delete [] oldTable;
    }
    // increase the hash table size by one
    void sizeUp(){
        int oldSize = setSize;
        setSize = (setSize << 1) + 1;
        LinkedList<T> * oldTable = table;
        table = new LinkedList<T>[setSize];
        for(int i = 0; i < oldSize; i++){
            for(int j = 0; j < oldTable[i].getSize(); j++)
                table[ hash(oldTable[i].at(j)) ].push_back(oldTable[i].at(j));
        }
        delete [] oldTable;
    }
    
    void add(const T& value) {
        if(find(value))
            return;
        size++;
        if(size > setSize)
            sizeUp();
        table[hash(value)].insert(table[hash(value)].getSize(), value);
    }
    // delete something from the hash table
    void remove(const T& value){
        if(!find(value))
            return;
        size--;
        if(size > 0){
            if((double)size / (double)setSize < 0.5)
                sizeDown();
        }
        for(int i = 0; i < table[hash(value)].getSize(); i++){
            if (table[hash(value)].at(i) == value){
                table[hash(value)].remove(i);
                return;
            }
        }
    }
    // hash function
    unsigned hash(string value) {
        unsigned hashed = 0;
        for(int i = 0; i < value.length(); i++)
            hashed = hashed * 31 + value.at(i);
        hashed = hashed % setSize;
        return hashed;
    }
    // if [value] is found in the hash table
    bool find(const T& value) {
        if(setSize == 0)
            return false;
        for(int i = 0; i < table[hash(value)].getSize(); i++)
            if (table[hash(value)].at(i) == value)
                return true;
        return false;
        
    }
    // delete the hash table
    void clear() {
        for (int index = 0; index < setSize; index++)
            table[index].clear();
        size = 0;
        setSize = 0;
        LinkedList<T> * oldTable = table;
        table = new LinkedList<T>[setSize];
        delete [] oldTable;
    }
    // size of the set	
    int getSetSize() {
	return setSize;
    }
    // output the hash table
    void print(ofstream& writer){
        if (size == 0)
            return;
        for(int i = 0; i < setSize; i++){
            int linefill = 0;
            writer << "hash " << i << ":";
            for(int j = 0; j < table[i].getSize(); j++){
                if(linefill >= 8){
                    writer << endl << "hash " << i << ":";
                    linefill = 0;
                }
                linefill++;
                writer << " " << table[i].at(j);
            }
            writer << endl;
        }
    }
};

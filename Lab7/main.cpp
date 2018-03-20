// Implementation of a hash table; reads queries from a file
#include <iostream>
#include <string>
#include "HashSet.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream reader(argv[1]);	// query file
    ofstream writer(argv[2]);	// output file
    
    string command;
    
    HashSet<string> hashSet;
    
    while (reader >> command){
        if (command == "find"){
            string value;
            reader >> value;
            
            writer << "find " << value << " " << boolalpha << hashSet.find(value) << endl;
        }
        
        else if (command == "add"){
            string toAdd;
            reader >> toAdd;
            
            writer << "add " << toAdd << endl;
            
            hashSet.add(toAdd);
        }
        
        else if (command == "remove"){
            string toRemove;
            reader >> toRemove;
            
            writer << "remove " << toRemove << endl;
            
            hashSet.remove(toRemove);
        }
        else if (command == "clear"){
            writer << "clear" << endl;
            hashSet.clear();
        }
        else if (command == "print"){
            writer << "print" << endl;
            hashSet.print(writer);
		}
	}
	return 0;
}

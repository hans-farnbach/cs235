#include <iostream>
#include <fstream>
#include <string>

#include "AVLTree.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, const char * argv[]){
    ifstream reader(argv[1]);
    ofstream writer(argv[2]);
    
    string input;
    
    AVLTree<string> tree;
    
    while (reader >> input)
    {
        if (input == "print")
            tree.print(writer);
        
        else if (input == "clear"){
            writer << "clear" << endl;
            tree.clear();
        }
        
        else if (input == "find"){
            string target;
            reader >> target;
            
			writer << "find " << target << " " << boolalpha << tree.find(target) << endl;
        }
        
        else if (input == "add") {            
            string toAdd;
            reader >> toAdd;
            
            writer << "add " << toAdd << endl;
            
            if(!(tree.find(toAdd)))
				tree.root = tree.add(toAdd, tree.root);
        }
        
        else if (input == "remove"){
            string toRemove;
            reader >> toRemove;
            
            writer << "remove " << toRemove << endl;
            
            tree.remove(toRemove);
        }
    }
    reader.close();
	writer.close();
    return 0;
}
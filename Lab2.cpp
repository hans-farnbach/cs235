// "Spell-checker", using a given list of words, find any words in a file that aren't on that list
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include <list>

using namespace std;


string toLowerCase(string word){
    for (int i = 0; i < word.length(); i++){
        if (word[i] >= 'A' && word[i] <= 'Z')	// If it's a capital letter
            word[i] += 'a' - 'A';		// shift it up the ASCII chart to the lower case portion
        else if (!(word[i] >= 'a' && word[i] <= 'z') && !(word[i] == ' '))	// If it's not a lower case letter or a space
            word[i] = '\0';							// delete it
    }
    return word;
}

int main(int argc, const char* argv[]){
    ifstream reader;
    ofstream writer(argv[3]);	// output file

    reader.open(argv[1]); 	// dictionary file

    string line;
    
    set<string> dict;

    // go through the entire dictionary and lowercase it for easy comparisons
    while (getline(reader, line)){
        line = toLowerCase(line);            
        dict.insert(line);
    }
    
    reader.close();
    
    map<string, list<int>> misspelled;
	
    reader.open(argv[2]); 	// thing to spellcheck

    string word;
    stringstream wordReader;
    
    int lineNum = 1;		// have to keep track of which line a misspelled word appeared on
    
    while (getline (reader, line)){
        wordReader.clear();	// empty the buffer
        wordReader.str("");
        
        line = toLowerCase(line);
        
        wordReader << line;

	// go through each word on the line and check if it's in the dictionary
        while (wordReader >> word)
            if (!dict.count(word))
                misspelled[word].push_back(lineNum);	// push ones that aren't in the dictionary with a line number
	lineNum++;
    }

    // output it all
    for(map<string, list<int>>::iterator iMap = misspelled.begin(); iMap != misspelled.end(); iMap++){
        writer << iMap->first << ":";
        for (list<int>::iterator iList = iMap->second.begin(); iList != iMap->second.end(); iList++)
            writer << " " << *iList;
        
        writer << endl;
    }    
    return 0;
}

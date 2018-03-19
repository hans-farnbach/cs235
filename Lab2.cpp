#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include <list>

using namespace std;


string toLowerCase(string word){
    for (int i = 0; i < word.length(); i++){
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 'a' - 'A';
        else if (!(word[i] >= 'a' && word[i] <= 'z') && !(word[i] == ' '))
            word[i] = '\0';
    }
    return word;
}

int main(int argc, const char* argv[]){
    ifstream reader;
    ofstream writer(argv[3]);

    reader.open(argv[1]);

    string line;
    
    set<string> dict;

    while (getline(reader, line)){        
        for (int i = 0; i < line.length(); i++){
            if (line[i]>= 'A' && line[i] <= 'Z')
                line[i] += 'a' - 'A';
        }
            
        dict.insert(line);
    }
    
    reader.close();
    
    map<string, list<int>> misspelled;
	
	reader.open(argv[2]);

    string word;
    stringstream wordReader;
    
    int lineNum = 1;
    
    while (getline (reader, line)){
        wordReader.clear();
        wordReader.str("");
        
        line = toLowerCase(line);
        
        wordReader << line;

        while (wordReader >> word)
            if (!dict.count(word))
                misspelled[word].push_back(lineNum);
		lineNum++;
    }

    for(map<string, list<int>>::iterator iMap = misspelled.begin(); iMap != misspelled.end(); iMap++){
        writer << iMap->first << ":";
        for (list<int>::iterator iList = iMap->second.begin(); iList != iMap->second.end(); iList++)
            writer << " " << *iList;
        
        writer << endl;
    }    
    return 0;
}
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <math.h>

using namespace std;

set<string> found;

string toLowerCase(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 'a' - 'A';
		else if (!(str[i] >= 'a' && str[i] <='z')) {
			str.erase(str.begin() + i);
			i--;
		}
	}
	return str;
}

vector<vector<string>> buildBoard(const char* file) {
	ifstream boardReader;
	boardReader.open(file);
	vector<string> charList;
	vector<vector<string>> board;
	string letters;
	string letter;
	while (boardReader >> letters) {
		letters = toLowerCase(letters);
		for (int i = 0; i < letters.size(); i++) {
			letter = letters[i];
			if (letters[i] == 'q' && letters[i + 1] == 'u')
				letter = letters[i] + letters[++i];
			charList.push_back(letter);
		}
	}

	int square = sqrt(charList.size());
	
	for (int row = 0; row < square; row++) {
		vector<string> rows;
		for (int element = 0; element < square; element++)
			rows.push_back(charList[element + (row*square)]);
		board.push_back(rows);
	}

	boardReader.close();
	return board;
}

bool flagNabIt(string word, set<string> dictionary, int row, int column, vector<vector<bool>> urAFlagit) {
	if (urAFlagit[row][column])
		return true;
	string prefix = word;
	prefix[prefix.length() - 1]++;

	if (dictionary.lower_bound(word) == dictionary.lower_bound(prefix))
		return true;

	return false;
}

void boggleMyMind(set<string> dictionary, vector<vector<string>> board, int row, int column, string word, vector<vector<bool>> urAFlagit) {
	if (row < 0 || row >= board.size() || column < 0 || column >= board.size())
		return;

	string newWord = word + board[row][column];
	if (flagNabIt(newWord, dictionary, row, column, urAFlagit))
		return;

	if (dictionary.count(newWord) && newWord.length() >= 4)
		found.insert(newWord);
	
	urAFlagit[row][column] = true;

	boggleMyMind(dictionary, board, row, (column-1), newWord, urAFlagit);
	boggleMyMind(dictionary, board, row, (column+1), newWord, urAFlagit);
	boggleMyMind(dictionary, board, (row-1), column, newWord, urAFlagit);
	boggleMyMind(dictionary, board, (row-1), (column-1), newWord, urAFlagit);
	boggleMyMind(dictionary, board, (row-1), (column+1), newWord, urAFlagit);
	boggleMyMind(dictionary, board, (row+1), column, newWord, urAFlagit);
	boggleMyMind(dictionary, board, (row+1), (column-1), newWord, urAFlagit);
	boggleMyMind(dictionary, board, (row+1), (column+1), newWord, urAFlagit);

	urAFlagit[row][column] = false;
}

int main(int argc, const char* argv[]) {

	// Build dictionary
	ifstream dictReader;
	dictReader.open(argv[1]);
	set<string> dict;
	string word;
	while (getline(dictReader, word))
		dict.insert(dict.end(), toLowerCase(word));
	dictReader.close();

	// Build board
	vector<vector<string>> board;
	board = buildBoard(argv[2]);
	int max = board.size();
	
	// Build the boolean board to keep track of used letters
	vector<vector<bool>> flagalicious;
	for (int row = 0; row < max; row++) {
		vector<bool> rows;
		for (int column = 0; column < max; column++)
			rows.push_back(false);
		flagalicious.push_back(rows);
	}

	// Biggle boogle boggle while outputting board to file
	ofstream resultWriter;
	resultWriter.open(argv[3]);
	word = "";
	for (int row = 0; row < max; row++){
		for (int column = 0; column < max; column++) {
			resultWriter << board[row][column] << " ";
			boggleMyMind(dict, board, row, column, word, flagalicious);
		}
		resultWriter << endl;
	}
		
	resultWriter << endl;

	for (set<string>::iterator i = found.begin(); i != found.end(); i++)
		resultWriter << *i << endl;

	resultWriter.close();
	
	return 0;
}

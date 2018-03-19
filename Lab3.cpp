// Boggle. Accepts a board file and a dictionary file, then recursively searches the board for those words.

#include <fstream>	// read a file
#include <iostream>	// 
#include <string>
#include <set>
#include <vector>
#include <math.h>

using namespace std;

set<string> found;

// converts a string to all lowercase letters
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

// creates the actual board by making a square and padding the edges with 0s
// 0 0 0 0 0
// 0 e x a 0
// 0 m p l 0
// 0 e b o 0
// 0 0 0 0 0
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
			if (letter == 'q' && letters[i + 1] == 'u') // keep "qu" together
				letter = letters[i] + letters[++i];
			charList.push_back(letter);
		}
	}

	int square = sqrt(charList.size());	// figure out the dimensions for the board, keeping it square
	
	// create each row
	for (int row = 0; row < square; row++) {
		vector<string> rows;
		for (int element = 0; element < square; element++)
			rows.push_back(charList[element + (row*square)]);
		board.push_back(rows);
	}

	boardReader.close();
	return board;
}

// keep track of letters we've visited and if they are valid paths to follow
bool flagNabIt(string word, set<string> dictionary, int row, int column, vector<vector<bool>> Flagit) {
	if (Flagit[row][column])
		return true;
	string prefix = word;
	prefix[prefix.length() - 1]++;

	if (dictionary.lower_bound(word) == dictionary.lower_bound(prefix))
		return true;

	return false;
}

// run the game
void boggleMyMind(set<string> dictionary, vector<vector<string>> board, int row, int column, string word, vector<vector<bool>> Flagit) {
	if (row < 0 || row >= board.size() || column < 0 || column >= board.size())
		return;

	string newWord = word + board[row][column];
	if (flagNabIt(newWord, dictionary, row, column, Flagit))
		return;

	if (dictionary.count(newWord) && newWord.length() >= 4)	// Don't allow words less than 4 characters long
		found.insert(newWord);
	
	Flagit[row][column] = true;	// Flag the current block as a visited one

	boggleMyMind(dictionary, board, row, (column-1), newWord, Flagit);	// Left
	boggleMyMind(dictionary, board, row, (column+1), newWord, Flagit);	// Right
	boggleMyMind(dictionary, board, (row-1), column, newWord, Flagit);	// Down
	boggleMyMind(dictionary, board, (row-1), (column-1), newWord, Flagit);	// Down left
	boggleMyMind(dictionary, board, (row-1), (column+1), newWord, Flagit);	// Down right
	boggleMyMind(dictionary, board, (row+1), column, newWord, Flagit);	// Up
	boggleMyMind(dictionary, board, (row+1), (column-1), newWord, Flagit);	// Up left
	boggleMyMind(dictionary, board, (row+1), (column+1), newWord, Flagit);	// Up right

	Flagit[row][column] = false;	// Unflag it
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

	// Do the Boggle and output board to file
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

	// output the words found
	for (set<string>::iterator i = found.begin(); i != found.end(); i++)
		resultWriter << *i << endl;

	resultWriter.close();
	
	return 0;
}

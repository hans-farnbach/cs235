// Implentation of a linked list, accepting additions and deletions from queries in a file
#include "LinkedList.h"
#include <fstream>
#include <sstream>

int main(int argc, const char* argv[]) {
	ifstream commandReader;
	ofstream resultWriter;
	string commandLine = "";
	string command = "";
	LinkedList<string> list;

	commandReader.open(argv[1]);	// Queries
	resultWriter.open(argv[2]);	// Results

	// Go through each query and execute commands
	while (getline(commandReader, commandLine)) {
		istringstream commandSplitter(commandLine);
		commandSplitter >> command;

		if (command == "clear") {
			list.clear();
			resultWriter << command << endl;
		}
		else if (command == "print") {
			resultWriter << "print" << endl;
			for (int i = 0; i < list.getSize(); i++)
				resultWriter << "node " << i << ": " << list.at(i) << endl;
		}
		else if (command == "find") {
			commandSplitter >> command;
			resultWriter << "find " << command << " " << list.find(command) << endl;
		}
		else if (command == "insert") {
			commandSplitter >> command;
			int index = stoi(command);
			commandSplitter >> command;
			list.insert(index, command);
			resultWriter << commandLine << endl;
		}
		else if (command == "remove") {
			commandSplitter >> command;
			int index = stoi(command);
			resultWriter << "remove " << index << " " << list.remove(index) << endl;
		}
	}
	commandReader.close();
	resultWriter.close();
}

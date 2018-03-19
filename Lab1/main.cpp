//#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "Student.h"
#include "Grade.h"

using namespace std;

// Calculates GPA for each student
void CalcGPA(vector<Student>& students, vector<Grade>& grades){
	// Go through each student
    for ( int i = 0; i < students.size(); i++){
        int count = 0;
        double total = 0;
		// Go through each class
        for ( int j = 0; j < grades.size(); j++){
			// Matching IDs
            if(students[i].getID() == grades[j].getID()){
                count++;
                total += grades[j].getNumberGrade();
            }
        }
		// If there are classes, actually do the math
        if (count > 0)
			students[i].setGPA(total/(double)count);
		// Otherwise just set it to 0 and move on
        else
			students[i].setGPA(0.00);
    }
}

// Prints the results of the queries
void printQueries( vector<Student>& students, vector<string>& queryIDs, ofstream& writer, const char* argv[]){
	// Go through each ID being queried
    for (int i = 0; i < queryIDs.size(); i++){
		// Go through each student and see if their ID is the same one being queried
        for (int j = 0; j < students.size(); j++){
            if ((queryIDs[i] == students[j].getID())){
                writer << students[j].getID() << "\t" << fixed << setprecision(2) << setfill('0') << students[j].getGPA() << "\t" << students[j].getName() << endl;
                break;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ofstream writer;
    writer.open(argv[4]);	// Outfile
    
    vector<string> gradeLet = { "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "E" };
    vector<double> gradeNum = { 4.0, 3.7,  3.4,  3.0, 2.7,  2.4,  2.0, 1.7,  1.4,  1.0, 0.7,  0.0 };
    
    ifstream reader;
    reader.open(argv[1]);	// Student information file
    
    vector<Student> students;
    
    string sID, sName, sAddress, sPhone;
    
	// Go through the information file and create Student objects
    while (getline(reader, sID)) {
        getline(reader, sName);
        getline(reader, sAddress);
        getline(reader, sPhone);
        
        Student newStudent(sID, sName, sAddress, sPhone);
        students.push_back(newStudent);
    }
        
    reader.close();
    
    sort(students.begin(), students.end());
    
	// Output everything we just read to the file
    for (int i = 0; i < students.size(); i++){
        writer << students[i].getName() << endl;
        writer << students[i].getID() << endl;
        writer << students[i].getPhone() << endl;
		writer << students[i].getAddress() << endl;
	}
    writer << endl;
    
    reader.open(argv[2]);	// Grade file, containing student IDs, the letter grade, 
    
    string gCourse, gLetter;
    
    vector<Grade> grades;
    
	// Go through the grades file and create Grade objects
    while (getline(reader, gCourse)){
        getline(reader, sID);
        getline(reader, gLetter);
        Grade newGrade(gCourse, sID, gLetter, gradeLet, gradeNum);
        grades.push_back(newGrade);
    }
    
    reader.close();
    
    sort(grades.begin(), grades.end());
    
	// Output grade information
    for( int i = 0; i < grades.size(); i++)
		writer << grades[i].getID() << "\t" << grades[i].getLetterGrade() << "\t" << grades[i].course << endl;
    
    writer << endl;
    
    reader.open(argv[3]);	// Query file, containing the student IDs for which we need to caluclate GPA
    vector<string> queryIDs;
    string qID;

	while (getline(reader, qID))
		queryIDs.push_back(qID);

    reader.close();
    
    CalcGPA(students, grades);
    
    printQueries(students, queryIDs, writer, argv);

    writer.close();
    
    return 0;
}



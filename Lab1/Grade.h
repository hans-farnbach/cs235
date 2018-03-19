#ifndef Lab_1_Grade_h
#define Lab_1_Grade_h

#include <string>
#include <vector>

using namespace std;

class Grade{
public:
    string course;
    string ID;
    string letter;
    double number;

    Grade(string gCourse, string gID, string gLetter, vector<string> gLet, vector<double> gNum){
        course = gCourse;
        ID = gID;
        letter = gLetter;
		// Translate letter of a grade into a number of a grade, e.g. A = 4.0
        for (int i = 0; i < gLet.size(); i++){
			if (letter == gLet[i]){
                number = gNum[i];
				break;
			}
        }
    }
    
    string getID(){
        return ID;
    }
    
    string getLetterGrade(){
        return letter;
    }
    
    double getNumberGrade(){
        return number;
    }
    
	// Compare Grades
    bool operator < (Grade g) const{
        return (ID < g.ID) ||	// If the student ID comes first
        (ID == g.ID && course < g.course) ||	// If the student ID is the same but the course name comes first
        (ID == g.ID && course == g.course && letter < g.letter);	// If the ID and course name are the same but the letter grade is better
    }
};

#endif

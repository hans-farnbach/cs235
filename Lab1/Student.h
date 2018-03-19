#ifndef Lab_1_Student_h
#define Lab_1_Student_h

#include <string>

using namespace std;

class Student {
public:
    string ID;
    string name;
    string address;
    string phone;
    double GPA;
	
    Student(string sID, string sName, string sAddress, string sPhone){
        ID = sID;
        name = sName;
        address = sAddress;
        phone = sPhone;
    }
    
    
    string getID(){
        return ID;
    }
	
    string getName(){
        return name;
    }
	
    string getAddress(){
        return address;
    }
	
    string getPhone(){
        return phone;
    }
    
    double getGPA(){
        return GPA;
    }
    
    void setGPA( double GPA ){
        this->GPA = GPA;
    }

	// Compare Student objects by looking at IDs
    bool operator < (Student x) const {
        return ID < x.ID;
    }
    
};


#endif

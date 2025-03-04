#pragma once
#ifndef USERREPORT
#define USERREPORT

#include <string>
#include <vector>

using namespace std;

//template<class T>
class UserReport
{
public:

	int id;
	string name;
	string username;
	string date_time_found;//will prompt the user if you enter "1" as a answer it will do the current date
	string subject;
	string error_code;
	string description;
	string type_of_error;//list of errors thatt are common will be shown to the user

	//will be mentioned that if nothing here applies pressing enter as an answer skips
	string listOfCommonErrors;


	static void SaveToXML(const string& filename, const vector<UserReport>& reports);
	static vector<UserReport> LoadFromXML(const string& filename);
	
private:
	


};
 void EditReport(vector<UserReport>& reports, const string& filename);



#endif


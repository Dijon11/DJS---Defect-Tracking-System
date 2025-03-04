#include <iostream>
#include <vector>

#include <ShlObj.h>
#include <string>
#include <Windows.h>

#include "UserReport.h"
#include "TimeManager.h"

using namespace std;


static string GetDocumentsPath()
{
	char path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path)))
	{
		return string(path) + "\\UserReports.xml";
	}
	return "";
}


void AddRecord(vector<UserReport>& reports, const string& filename);
void ViewRecords(const vector<UserReport>& reports);
//void EditReport(vector<UserReport>& reports, const string& filename);

int main()
{
	//string currentTime = TimeManager::GetCurrentTime1();
	string filename = GetDocumentsPath();
	cout << "Using XML file: " << filename << endl;

	vector<UserReport> reports = UserReport::LoadFromXML(filename);

	while (true) {
		int choice = 0;
		cout << "\n1. Add a report | 2. View reports | 3. Edit report | 4. Exit" << endl;
		cout << ">> "; cin >> choice;
		cin.ignore();  // Prevents issues with `getline()`

		if (choice == 1) {
			AddRecord(reports, filename);
		}
		else if (choice == 2) 
		{
			ViewRecords(reports);
		}
		else if (choice == 3) 
		{
			EditReport(reports,filename);
		}
		else if (choice == 4) {
			cout << "Exiting program.\n";
			break;
		}
		else {
			cout << "Invalid choice! Please enter 1, 2, 3, 4.\n";
		}
	}
	
	





	return 0;
}

void AddRecord(vector<UserReport>& reports, const string& filename)
{
	UserReport newReport;
	int nextID = reports.empty() ? 1 : reports.back().id + 1;


	newReport.id = nextID;
	newReport.listOfCommonErrors = "0. None, 1. AI Issue, 2. Movement Issue, 3. Cosmetic Issue, \n4. Feature Issue, 5. Save Issue, 6. Collider Issue, \n7. Hitbox Issue, 8. Map Issue, 9. Other \n";


	cout << "\n\n\nName: ";
	getline(cin, newReport.name); cout << endl;

	cout << "Username: ";
	getline(cin, newReport.username); cout << endl;

	cout << "(Enter 0 for current date and time)" << endl;
	cout << "Date/time found: ";
	getline(cin, newReport.date_time_found); cout << endl;

	if (newReport.date_time_found == "0")
	{
		newReport.date_time_found = TimeManager::GetCurrentTime1();
	}


	cout << "Subject: ";
	getline(cin, newReport.subject); cout << endl;

	cout << "(Enter 0 for not known)";
	cout << "Error code: ";
	getline(cin, newReport.error_code); cout << endl;


	cout << "Description: ";
	getline(cin, newReport.description); cout << endl;

	cout << newReport.listOfCommonErrors << "\n\n";
	cout << "Type of error (number): ";
	cin >> newReport.type_of_error; cout << endl;

	cin.ignore();


	reports.push_back(newReport);
	UserReport::SaveToXML(filename, reports);
}
void ViewRecords(const vector<UserReport>& reports) {
	if (reports.empty()) {
		cout << "\nNo reports found.\n";
		return;
	}

	cout << "\n--- All Reports ---\n";
	for (const auto& report : reports) {
		cout << "ID: " << report.id << "\n";
		cout << "Name: " << report.name << "\n";
		cout << "Username: " << report.username << "\n";
		cout << "Date Found: " << report.date_time_found << "\n";
		cout << "Subject: " << report.subject << "\n";
		cout << "Error Code: " << report.error_code << "\n";
		cout << "Description: " << report.description << "\n";
		cout << "Type of Error: " << report.type_of_error << "\n";
		cout << "----------------------\n";
	}
}
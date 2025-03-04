#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "UserReport.h"
#include "TimeManager.h"
//#include "main.cpp"

using namespace std;

static bool FileExists(const string& filename)
{
	ifstream file(filename);
	return file.good();
}
void UserReport::SaveToXML(const string& filename, const vector<UserReport>& reports) 
{
	ofstream file(filename);
	if (!file)
	{
		cerr << "Error opening file for writing: " << filename << "\n";
		return;
	}


	file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	file << "<UserReports>\n";

	for (const auto& report : reports) {
		file << "    <UserReport>\n";
		file << "        <ID>" << report.id << "</ID>\n";
		file << "        <Name>" << report.name << "</Name>\n";
		file << "        <Username>" << report.username << "</Username>\n";
		file << "        <DateTimeFound>" << report.date_time_found << "</DateTimeFound>\n";
		file << "        <Subject>" << report.subject << "</Subject>\n";
		file << "        <ErrorCode>" << report.error_code << "</ErrorCode>\n";
		file << "        <Description>" << report.description << "</Description>\n";
		file << "        <TypeOfError>" << report.type_of_error << "</TypeOfError>\n";
		file << "    </UserReport>\n";
	}

	file << "</UserReports>\n"; 

	file.close();
	cout << "Data saved to " << filename << " successfully.\n";



}
vector<UserReport> UserReport::LoadFromXML(const string& filename) 
{
	if (!FileExists(filename)) {
		cerr << "File not found! Creating new XML file: " << filename << endl;

		// Create a new XML file with a root element because the XML that gets created is entirely empty
		ofstream newFile(filename);
		if (!newFile) {
			cerr << "Error: Unable to create file " << filename << endl;
			return {};
		}

		newFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		newFile << "<UserReports>\n</UserReports>\n";
		newFile.close();

		return {};  // Return an empty list
	}

	
	ifstream file(filename);//by this point the filename reference to the xml should exist now in documents folder
	vector<UserReport> reports;
	string line;
	UserReport tempReport;

	while (getline(file, line)) {
		if (line.find("<ID>") != string::npos) {
			try {
				size_t start = line.find("<ID>") + 4;  // 4 = length of "<ID>"
				size_t end = line.find("</ID>");

				if (end == string::npos || start >= end) {
					throw invalid_argument("Malformed <ID> entry in XML.");
				}
				string value = line.substr(start, end - start);

				// Trim spaces or newlines or returns from extracted value inbetween the xml tags
				value.erase(0, value.find_first_not_of(" \t\n\r"));
				value.erase(value.find_last_not_of(" \t\n\r") + 1);

				// Ensure value contains only digits
				if (value.empty() || value.find_first_not_of("0123456789") != string::npos) {
					throw invalid_argument("Invalid numeric format in <ID>.");
				}
				tempReport.id = stoi(value);
				
			}
			catch (const invalid_argument& e) {
				cerr << "Error: Invalid ID value in XML! Using default ID = 0.\n";
				tempReport.id = 0;
			}
		}
		else if (line.find("<Name>") != string::npos) {
			size_t start = line.find("<Name>") + 6;  //anytime here a number has a plus on the end of the start statement is the thing we are findings' length
			size_t end = line.find("</Name>");

			if (end == string::npos || start >= end) {
				throw invalid_argument("Malformed <Name> entry in XML.");
			}

			tempReport.name = line.substr(start, end - start);
			tempReport.name.erase(0, tempReport.name.find_first_not_of(" \t\n\r"));
			tempReport.name.erase(tempReport.name.find_last_not_of(" \t\n\r") + 1);

		}
		else if (line.find("<Username>") != string::npos) {
			size_t start = line.find("<Username>") + 10;
			size_t end = line.find("</Username>");

			if (end == string::npos || start >= end) throw invalid_argument("Malformed <Username> entry in XML.");
			

			tempReport.username = line.substr(start, end - start);
			tempReport.username.erase(0, tempReport.username.find_first_not_of(" \t\n\r"));
			tempReport.username.erase(tempReport.username.find_last_not_of(" \t\n\r") + 1);
		}
		else if (line.find("<DateTimeFound>") != string::npos) {
			size_t start = line.find("<DateTimeFound>") + 15;
			size_t end = line.find("</DateTimeFound>");
			if (end == string::npos || start >= end) throw invalid_argument("Malformed <DateTimeFound> entry in XML.");
			tempReport.date_time_found = line.substr(start, end - start);
			tempReport.date_time_found.erase(0, tempReport.date_time_found.find_first_not_of(" \t\n\r"));
			tempReport.date_time_found.erase(tempReport.date_time_found.find_last_not_of(" \t\n\r") + 1);
		}
		else if (line.find("<Subject>") != string::npos) {
			size_t start = line.find("<Subject>") + 9;
			size_t end = line.find("</Subject>");
			if (end == string::npos || start >= end) throw invalid_argument("Malformed <Subject> entry in XML.");
			tempReport.subject = line.substr(start, end - start);
			tempReport.subject.erase(0, tempReport.subject.find_first_not_of(" \t\n\r"));
			tempReport.subject.erase(tempReport.subject.find_last_not_of(" \t\n\r") + 1);
		}
		else if (line.find("<ErrorCode>") != string::npos) {
			size_t start = line.find("<ErrorCode>") + 11;
			size_t end = line.find("</ErrorCode>");
			if (end == string::npos || start >= end) throw invalid_argument("Malformed <ErrorCode> entry in XML.");
			tempReport.error_code = line.substr(start, end - start);
			tempReport.error_code.erase(0, tempReport.error_code.find_first_not_of(" \t\n\r"));
			tempReport.error_code.erase(tempReport.error_code.find_last_not_of(" \t\n\r") + 1);
		}
		else if (line.find("<Description>") != string::npos) {
			size_t start = line.find("<Description>") + 13;
			size_t end = line.find("</Description>");
			if (end == string::npos || start >= end) throw invalid_argument("Malformed <Description> entry in XML.");
			tempReport.description = line.substr(start, end - start);
			tempReport.description.erase(0, tempReport.description.find_first_not_of(" \t\n\r"));
			tempReport.description.erase(tempReport.description.find_last_not_of(" \t\n\r") + 1);
		}
		else if (line.find("<TypeOfError>") != string::npos) {
			try {
				size_t start = line.find("<TypeOfError>") + 13; // Length of "<TypeOfError>"
			    size_t end = line.find("</TypeOfError>");

				if (end == string::npos || start >= end) {
					throw invalid_argument("Malformed <TypeOfError> entry in XML.");
				}

			    string value = line.substr(start, end - start);

				// Trim whitespace or newlines
				value.erase(0, value.find_first_not_of(" \t\n\r"));
				value.erase(value.find_last_not_of(" \t\n\r") + 1);

				// Ensure it's a valid number
				if (value.empty() || value.find_first_not_of("0123456789") != string::npos) {
					throw invalid_argument("Invalid numeric format in <TypeOfError>.");
				}

				tempReport.type_of_error = stoi(value);
				cout << "Converted TypeOfError: " << tempReport.type_of_error << "\n";
			}
			catch (const invalid_argument& e) {
				cerr << "Error: Invalid TypeOfError value in XML! Using default = 0.\n";
				tempReport.type_of_error = "0";//"0"
			}
		}
		else if (line.find("</UserReport>") != string::npos)
			reports.push_back(tempReport);
	}

	file.close();
	cout << "Loaded " << reports.size() << " reports from XML successfully.\n";
	return reports;
}
void EditReport(vector<UserReport>& reports, const string& filename) {
	if (reports.empty()) {
		cout << "There are no reports to edit\n";
		return;
	}

	int reportID;
	cout << "\n\nEnter the ID of the report to edit: ";
	cin >> reportID;
	cin.ignore();

	// Find the report with the matching ID
	auto reportEdit = find_if(reports.begin(), reports.end(), [&](const UserReport& r) {
		return r.id == reportID;
	});

	if (reportEdit == reports.end()) {
		cout << "Error: Report with ID " << reportID << " not found.\n";
		return;
	}

	UserReport& report = *reportEdit;  // Reference to the selected report

	while (true) {
		int fieldChoice;
		cout << "\nEditing Report ID: " << report.id << endl;
		cout << "1. Name: " << report.name << endl;
		cout << "2. Username: " << report.username << endl;
		cout << "3. Date Found: " << report.date_time_found << endl;
		cout << "4. Subject: " << report.subject << endl;
		cout << "5. Error Code: " << report.error_code << endl;
		cout << "6. Description: " << report.description << endl;
		cout << "7. Type of Error: " << report.type_of_error << endl;
		cout << "8. Save and Exit\n";
		cout << "Select a field to edit (1-8): ";
		cin >> fieldChoice;
		cin.ignore();  // Avoid getline issues

		if (fieldChoice == 1) {
			cout << "Enter new Name: ";
			getline(cin, report.name);
		}
		else if (fieldChoice == 2) {
			cout << "Enter new Username: ";
			getline(cin, report.username);
		}
		else if (fieldChoice == 3) {
			cout << "Enter new Date Found (or 0 for current time): ";
			getline(cin, report.date_time_found);
			if (report.date_time_found == "0") {
				report.date_time_found = TimeManager::GetCurrentTime1();
			}
		}
		else if (fieldChoice == 4) {
			cout << "Enter new Subject: ";
			getline(cin, report.subject);
		}
		else if (fieldChoice == 5) {
			cout << "Enter new Error Code: ";
			getline(cin, report.error_code);
		}
		else if (fieldChoice == 6) {
			cout << "Enter new Description: ";
			getline(cin, report.description);
		}
		else if (fieldChoice == 7) {
			cout << "Enter new Type of Error (number): ";
			cin >> report.type_of_error;
			cin.ignore();
		}
		else if (fieldChoice == 8) {
			break;  // Exit edit menu
		}
		else {
			cout << "Invalid choice! Try again.\n";
		}
	}

	// Save updated reports back to XML
	UserReport::SaveToXML(filename, reports);
	cout << "Changes saved successfully!\n";
}


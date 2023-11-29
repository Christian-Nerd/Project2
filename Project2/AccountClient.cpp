//*****************************************************************
//
// Programmer: Trey Davis
// Instructor: B.J Streller
// Course: CS121
// Date Created: 11/29/23
// Date Modified: 11/29/23
// Input Files; File storing account listing in the form as shown in the pdf, File for transaction history
// Output Files: monthly_report.txt stores monthly report
// Modules: idk
// Purpose: Finds account number of user then returns their transaction history
//*****************************************************************
#include "Account.h"

//*****************************************************************
// Function Name: GetAccountFile
// Purpose: Gets Account filepath from user and error checks if it's right then opens it
// Parameters:
//		Input: Account File
//		Input & Output: None
//		Output: None
// Return Value: None
// Non-local Variables Used: None
// Functions Called: std::string::push_back(), std::string::getline(), 
//*****************************************************************
void GetAccountFile(fstream File) 
{
	string FileName; // Stores file name
	while (!File)
	{
		cout << "Please input account file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str());
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
			File.clear();
		}
	}
	/*
	char CurrentStreamCharacter = cin.get(); // Current Character in the input stream
	while (CurrentStreamCharacter == '\n') 
	{
		FileName.push_back(CurrentStreamCharacter); // Adds character to file name
	    CurrentStreamCharacter = cin.get(); // Current Character in the input stream
	}
	*/
	
}

//*****************************************************************
// Function Name: GetTransactionHistoryFile
// Purpose: Gets Transaction History filepath from user and error checks if it's right then opens it
// Parameters:
//		Input: Account File
//		Input & Output: None
//		Output: None
// Return Value: None
// Non-local Variables Used: None
// Functions Called: std::string::push_back(), std::string::getline(),  std::c_str(), fstream::open()
//*****************************************************************
void GetTransactionHistoryFile(fstream File) 
{
	string FileName; // Stores file name
	// Error Checking loop
	while (!cin)
	{
		cout << "Please input transaction history file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str());
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
			File.clear();
		}
	}
	/*
	char CurrentStreamCharacter = cin.get(); // Current Character in the input stream
	while (CurrentStreamCharacter == '\n') 
	{
		FileName.push_back(CurrentStreamCharacter); // Adds character to file name
	    CurrentStreamCharacter = cin.get(); // Current Character in the input stream
	}
	*/
	cout << endl;
	
}

//*****************************************************************
// Function Name: GetAccountNumber
// Purpose: Gets & returns account number from account file
// Parameters:
//		Input: Account File, and Account Number
//		Input & Output: None
//		Output: None
// Return Value: Account Number
// Non-local Variables Used: None
// Functions Called: 
//*****************************************************************
string GetAccountName(fstream AccountFile, int AccountNumber, ) 
{
		
}
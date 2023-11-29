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
//		Input: Account File, and Account Number, and Array of Previously Used account numbers, How many used numbers in array
//		Input & Output: None
//		Output: None
// Return Value: Account Number
// Non-local Variables Used: None
// Functions Called: std::find, std::number_limits<streamsize>::max, std::isdigit
//*****************************************************************
int GetAccountNumber(fstream AccountFile, int UsedAccountNumbers[], int &NoOfNumsUsed) 
{
	//Initilizes Variables
	int AccountNumber; // Potential Account Number
	char CurrentStreamCharacter = AccountFile.get();
	// Until end of file checks for an unused account number
	while (!AccountFile.eof())
	{
		// Checks if account number already processed if so you ignore 
		if (CurrentStreamCharacter == '\n' && isdigit(cin.peek()))
		{
			if (find(std::begin(UsedAccountNumbers), std::end(UsedAccountNumbers + NoOfNumsUsed), NoOfNumsUsed) != NoOfNumsUsed)
			{
				AccountFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores line completely
				continue;
			}
			else
			{
				AccountFile >> AccountNumber;
				UsedAccountNumbers[NoOfNumsUsed++]; // Iterate Number of Numbers used & add AccountNumber to UsedAccountNumbers before 
				// NoOfNumbers is iterated
				return AccountNumber;
			}
		}
	}
	return -1;
}

//*****************************************************************
// Function Name: LinearSearch
// Purpose: Gets & returns Element in an array if it's not there returns -1
// Parameters:
//		Input: Array, Size of array, and key
//		Input & Output: None
//		Output: None
// Return Value: Where key element is in there(-1 if not)
// Non-local Variables Used: None
// Functions Called: None
//*****************************************************************
int LinearSearch() 
{
	
}

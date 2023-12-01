//*****************************************************************
//
// Programmer: Trey Davis
// Instructor: B.J Streller
// Course: CS121
// Date Created: 12/1/23
// Date Modified: 12/1/23
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
void GetAccountFile(fstream& File) 
{
	string FileName; // Stores file name
	do
	{
		File.clear(); // When the file isn't opened and the loop runs again this allows operations to happen.
		cout << "Please input account file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str(), ios::in);
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
			continue;
		}
	} while (!File);
	
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
void GetTransactionHistoryFile(fstream& File) 
{
	string FileName; // Stores file name
	// Error Checking loop
	do
	{
		File.clear(); // When the file isn't opened and the loop runs again this allows operations to happen.
		cout << "Please input transaction history file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str(), ios::in);
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
			continue;
		}
	} 
	while (!File);
	cout << endl;
	
}

//*****************************************************************
// Function Name: GetOutputFile
// Purpose: Gets Output File filepath from user and error checks if it's right then opens it
// Parameters:
//		Input: Output File
//		Input & Output: None
//		Output: None
// Return Value: None
// Non-local Variables Used: None
// Functions Called: std::string::push_back(), std::string::getline(),  std::c_str(), fstream::open()
//*****************************************************************
void GetOutputFile(ofstream& File) 
{
	string FileName; // Stores file name
	// Error Checking loop
	do
	{
		File.clear(); // When the file isn't opened and the loop runs again this allows operations to happen.
		cout << "Please input output file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str(), ios::out);
		if (!File)
		{
			cerr << "Invalid File Path!" << endl;
			continue;
		}
	} while (!File);
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
// Functions Called: std::number_limits<streamsize>::max, std::isdigit
//*****************************************************************
int GetAccountNumber(fstream& AccountFile, int UsedAccountNumbers[], int &NoOfNumsUsed) 
{
	//Initilizes Variables
	int CurrentAccountNumber = -1; // Potential Account Number
	char CurrentStreamCharacter = AccountFile.get(); // Finds current stream character
	// Until end of file checks for an unused account number
	while (!AccountFile.fail())
	{
		// If the next string is an account number...
		if (CurrentStreamCharacter == '\n' && isdigit(AccountFile.peek()))
		{
			AccountFile >> CurrentAccountNumber; // Gets current account number
			// Checks if account number already processed if so you ignore 
			if (LinearSearch(UsedAccountNumbers, NoOfNumsUsed, CurrentAccountNumber) >= 0)
			{
				CurrentAccountNumber = -1;
				AccountFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores line completely
				AccountFile.putback('\n');
				continue;
			}
			else
			{
				UsedAccountNumbers[NoOfNumsUsed++] = CurrentAccountNumber; // Iterate Number of Numbers used  
				// & add AccountNumber toUsedAccountNumbers before 
				// NoOfNumbers is iterated
				AccountFile.seekg(ios::beg); // Set stream back to beginning
				return CurrentAccountNumber; // Returns the account number 
				// since it the most recent one not previously used
			}
		}
	    CurrentStreamCharacter = AccountFile.get(); // Finds next current stream character
	}
	AccountFile.seekg(ios::beg); // Set stream back to beginning
	return -1;
}

//*****************************************************************
// Function Name: GetAccountNumber
// Purpose: Gets & returns account name from account file
// Parameters:
//		Input: Account File, and Account Number
//		Input & Output: None
//		Output: None
// Return Value: Account Name
// Non-local Variables Used: None
// Functions Called: std::isdigit
//*****************************************************************
string GetAccountName(fstream& AccountFile, int AccountNumber) 
{
	// Initilizes Variables
	string AccountName; // Account name assoicated with user
	char CurrentStreamCharacter = AccountFile.get(); // Finds current stream character
	// Searchs account file for account number and then finds
	while (!AccountFile.eof()) 
	{
		int CurrentAccountNumber; // Current Account Number
		// If next string account number
		if (CurrentStreamCharacter == '\n' && isdigit(AccountFile.peek())) 
		{
			AccountFile >> CurrentAccountNumber; // Assign Current Account Number to CurrentAccountNumber
			// If our Account Number found then get the account name
			if (CurrentAccountNumber == AccountNumber)
			{
				AccountFile >> AccountName;
				AccountFile.seekg(ios::beg); // Set stream back to beginning
				return AccountName;
			}
		}
		CurrentStreamCharacter = AccountFile.get(); // Finds next current stream character
	}
	AccountFile.seekg(ios::beg); // Set stream back to beginning
	return ""; // If account name not found return empty string.
}

//*****************************************************************
// Function Name: GetPreviousAccountBalance
// Purpose: Gets & returns previous account balance assoicated with a user in the Account File
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Number of deposits assoicated with users
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear
//*****************************************************************
float GetPreviousAccountBalance(fstream& TransactionHistory, int AccountNumber) 
{
	// Initialize Variables
	float PreviousAccountBalance; // Previous Account Balance
	char CurrentStreamCharacter = TransactionHistory.get(); // Finds current stream character
	int CurrentAcccountNumber; // Checks for current account number to see if it's out account number
	while (!TransactionHistory.eof()) 
	{
		// If the next string is the account number
		if (CurrentStreamCharacter == '\n' || TransactionHistory.tellg() == 1 && isdigit(TransactionHistory.peek()))
		{
			if (TransactionHistory.tellg() == 1)
			{
				TransactionHistory.putback(CurrentStreamCharacter);
				TransactionHistory >> CurrentAcccountNumber; // Finds Current Account Number and puts it in a variable
			}
			else
				TransactionHistory >> CurrentAcccountNumber; // Finds Current Account Number and puts it in a variable

			if (CurrentAcccountNumber == AccountNumber) 
			{
				TransactionHistory >> PreviousAccountBalance; // Assigns previous account balance to a variable
				TransactionHistory.seekg(ios::beg); // Returns stream to beginning
				return PreviousAccountBalance;
			}
		}
		CurrentStreamCharacter = TransactionHistory.get(); // Finds next current stream character
	}
	TransactionHistory.seekg(ios::beg); // Returns stream to beginning
	TransactionHistory.clear(); // Clear stream of errors
	return -1;
}

//*****************************************************************
// Function Name: GetNumberOfDeposits
// Purpose: Gets & returns the of all deposits assoicated with a user in the Transaction File
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Number of deposits assoicated with users
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::string::compare, istream::peek
//*****************************************************************
int GetNumberOfDeposits(fstream& TransactionHistory, int AccountNumber) 
{
	// Initilizes Variables
	string Dummy; // string variable to clear Previous Account Balance 
	string CurrentAccountNumber; // Stores current account number
	float NumOfDeposits = 0;
	// and check if you find account number from stream
	char CurrentStreamCharacter = ' '; // Finds current stream character
	char NextStreamCharacter; // Debugging variable
	while((CurrentStreamCharacter = TransactionHistory.get()) && TransactionHistory) 
	{
		NextStreamCharacter = TransactionHistory.peek(); // Puts next character into NextStreamCharacter
		if ((CurrentStreamCharacter == '\n' || TransactionHistory.tellg() == 1) && (isdigit((unsigned char)TransactionHistory.peek())))
		{
			if (TransactionHistory.tellg() == 1) 
			{
				TransactionHistory.putback(CurrentStreamCharacter);
				TransactionHistory >> CurrentAccountNumber;
			}
			else
				TransactionHistory >> CurrentAccountNumber;
		}
		if (CurrentAccountNumber.compare(to_string(AccountNumber)) == 0)
		{
 			switch (tolower(CurrentStreamCharacter))
			{
				case 'd':
					NumOfDeposits++;
					break;
				default:
					break;
			}
		}
	}
	TransactionHistory.clear(); // Clears any errors
	TransactionHistory.seekg(ios_base::beg); // Returns stream to beginning
	return NumOfDeposits;
}


//*****************************************************************
// Function Name: GetSumOfDeposits
// Purpose: Gets & returns the sum of all deposits associated with a user in the Transaction File
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Sum of all deposits 
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::string::compare, istream::peek
//*****************************************************************
float GetSumOfDeposits(fstream& TransactionHistory, int AccountNumber) 
{
	// Intitilize Variables
	string CurrentAccountNumber = ""; // Current account number gotten
	char CurrentStreamCharacter = ' '; // Current Character in the stream
	string Dummy = ""; // Dummy variable to clear Previous Balance
	float CurrentDeposite = 0; // Current Deposite in stream
	float SumOfDeposits = 0; // Sum of all deposits
	// Goes thru to find deposits as long as input/stream is valid

	while ((CurrentStreamCharacter = TransactionHistory.get()) && TransactionHistory) 
	{
		// If account number found assign it to currentaccountnumber and get rid of the previous balance from stream
		if ((CurrentStreamCharacter == '\n' || TransactionHistory.tellg() == 1) && isdigit((unsigned char)TransactionHistory.peek()))
		{
			if (TransactionHistory.tellg() == 1)
			{
				TransactionHistory.putback(CurrentStreamCharacter); // Put the first digit of account number 
				// back in stream
				TransactionHistory >> CurrentAccountNumber;	// Get current account number
			}
			else
				TransactionHistory >> CurrentAccountNumber;	// Get current account number
			TransactionHistory >> Dummy; // Get rid of previous balance from stream
		}
		// Check for deposits and add it to the sum if the current account number is the inputted one
		if (CurrentAccountNumber.compare(to_string(AccountNumber)) == 0) 
		{
			switch (tolower(CurrentStreamCharacter))
			{
				case 'd':
					TransactionHistory >> CurrentDeposite;
					SumOfDeposits += CurrentDeposite;
					break;

				default: 
					continue;
			}
			if (TransactionHistory.peek() == '\n')
			{
				return SumOfDeposits;
			}
		}

	}
	TransactionHistory.clear(); // Clears any errors
	TransactionHistory.seekg(ios::beg); // Returns stream to beginning
	return SumOfDeposits;
}

//*****************************************************************
// Function Name: GetNumberOfWithdrawls
// Purpose: Gets the number of withdrawls a user made
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Number of Withdrawls a user made 
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::tolower, std::string::compare, istream::peek
//*****************************************************************
int GetNumberOfWithdrawls(fstream& TransactionHistory, int AccountNumber) 
{
	// Initilizes Variables
	string Dummy; // string variable to clear Previous Account Balance 
	int NumOfWithdrawls = 0;
	string CurrentAccountNumber = ""; // Current account number gotten
	// and check if you find account number from stream
	char CurrentStreamCharacter = ' '; // Finds current stream character
	while ((CurrentStreamCharacter = TransactionHistory.get()) && TransactionHistory)
	{
		// If next string account number
		if ((CurrentStreamCharacter == '\n' || TransactionHistory.tellg() == 1) && isdigit((unsigned char)TransactionHistory.peek()))
		{
			if (TransactionHistory.tellg() == 1)
			{
				TransactionHistory.putback(CurrentStreamCharacter);
				TransactionHistory >> CurrentAccountNumber;	// Get current account number
			}
			else
				TransactionHistory >> CurrentAccountNumber;	// Get current account number

			TransactionHistory >> Dummy; // Puts Previous Balance into dummy variable
		}
		// Checks if current account number is our account number
		if (CurrentAccountNumber.compare(to_string(AccountNumber)) == 0)
		{
				switch (tolower(CurrentStreamCharacter))
				{
					case 'w':
						NumOfWithdrawls++; // Adds 1 to Number of deposits
						TransactionHistory >> Dummy; // Skips to next word;							
						break;
					default:
						// CurrentStreamCharacter = TransactionHistory.get(); 
						continue;
				}
		}
	}
	TransactionHistory.clear(); // Clears any errors
	TransactionHistory.seekg(ios_base::beg); // Returns stream to beginning
	return NumOfWithdrawls;
}


//*****************************************************************
// Function Name: GetSumOfWithdrawls
// Purpose: Gets the sum of withdrawls a user made
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Sum of all withdrawls 
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::tolower, std::string::compare, istream::peek
//*****************************************************************
float GetSumOfWithdrawls(fstream& TransactionHistory, int AccountNumber)
{
	// Initilizes Variables
	string Dummy = ""; // string variable to clear Previous Account Balance 
	string CurrentAccountNumber = ""; // Stores current account number
	float CurrentWithdrawl = 0; // Current withdrawl number 
	float SumOfWithdrawls = 0; // Sum of Withdrawls 
	char CurrentStreamCharacter = ' '; // Finds current stream character
	while((CurrentStreamCharacter = TransactionHistory.get()) && TransactionHistory) 
	{
		if ((CurrentStreamCharacter == '\n' || TransactionHistory.tellg() == 1) && isdigit((unsigned char)TransactionHistory.peek())) 
		{
			if (TransactionHistory.tellg() == 1) 
			{
				TransactionHistory.putback(CurrentStreamCharacter); // Add First digit of account number 
				// back into stream
				TransactionHistory >> CurrentAccountNumber; // Gets current account number
				TransactionHistory >> Dummy; // Clears Previous Balance
			}
			else
				TransactionHistory >> CurrentAccountNumber;
		}
		if (CurrentAccountNumber.compare(to_string(AccountNumber)) == 0) 
		{
			switch (tolower(CurrentStreamCharacter)) 
			{
				case 'w':
					TransactionHistory >> CurrentWithdrawl;
					SumOfWithdrawls += CurrentWithdrawl;
					break;
				default:
					break;
			}
		}
	}
	TransactionHistory.clear(); // Clears any errors
	TransactionHistory.seekg(ios_base::beg); // Returns stream to beginning
	return SumOfWithdrawls;
}


//*****************************************************************
// Function Name: IsThereDifferentAccounts
// Purpose: Checks if there is any unused account numbers left in the inputted Account file
// Parameters:
//		Input: Account File, Array containing all previously used account numbers, along with it's size
//		Input & Output: None
//		Output: None
// Return Value: Whether or not there is any unused account numbers left in the inputted Account File
// Non-local Variables Used: None
// Functions Called: ios::clear, istream::seekg, istream::tellg, istream::putback, std::isdigit, istream::peek
//*****************************************************************
bool IsThereDifferentAccounts(fstream& AccountFile, int UsedAccountNumbers[], int NoOfUsedAccountNumbers) 
{
	// Initilize Variables 
	char CurrentStreamCharacter = ' '; // The current character in the stream
	int CurrentAccountNumber = -2; // Number that represents the current account number(set to a default that won't screw everything up)
	// Checks for unused account numbers while AcconutFile is still good
	// While the file is still good and input is valid check if there are any different account numbers
	while ((CurrentStreamCharacter = AccountFile.get()) && AccountFile)
	{
		if ((CurrentStreamCharacter == '\n' || AccountFile.tellg() == 1) && isdigit((unsigned char)AccountFile.peek())) 
		{
			if (AccountFile.tellg() == 1)
			{
				AccountFile.putback(CurrentStreamCharacter);
				AccountFile >> CurrentAccountNumber;
			}
			else
				AccountFile >> CurrentAccountNumber;
		}
		// Checks if CurrentAccountNumber in list and returns it if so
		if ((LinearSearch(UsedAccountNumbers, NoOfUsedAccountNumbers, CurrentAccountNumber) == -1)) 
		{
			AccountFile.clear(); // Clears any errors
			AccountFile.seekg(ios::beg); // Sends string to the beginning
			return true;
		}

	}
	if ((LinearSearch(UsedAccountNumbers, NoOfUsedAccountNumbers, CurrentAccountNumber) > -1))
	{
		AccountFile.clear(); // Clears any errors		
		AccountFile.seekg(ios::beg); // Sends string to the beginning
		return false;
	}
	return false;
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
int LinearSearch(int List[], int Size, int Key) 
{
	// Searches array and returns the index where the array was found
	for (int i = 0; i < Size; i++) 
	{
		if (List[i] == Key)
			return i;
	}
	return -1; // If key not found return -1
}


//*****************************************************************
// Function Name: OutputAccountHistory
// Purpose: Outputs monthly report of user's transactions 
// Parameters: 
//      Input: Account Number, Account Name, Beginning Balance, Number Of Deposits, Deposits, Number Of Withdrawls, Withdrawls
//		Input & Output: None 
//		Output: File which stores the output
// Return Value: None
// Non-local Variables Used: None
// Functions Called: None
//*****************************************************************
void OutputAccountHistory(int AccountNumber, string AccountName, int BeginningBalance, int NumberOfDeposits, int Deposits, int NumberOfWithdrawls, int Withdrawls, ofstream& Report) 
{
	// Sets flags on output streams
	cout << setprecision(2) << fixed;
	Report << setprecision(2) << fixed;
	// Outputs monthly report
	cout << "Name : " << AccountName << endl;
	Report << "Name : " << AccountName << endl;
	cout << "Account Number : " << AccountNumber << endl;
	Report << "Account Number : " << AccountNumber << endl;
	cout << "Beginning Balance : " << BeginningBalance << endl;
	Report << "Beginning Balance : " << BeginningBalance << endl;
	cout << "Ending Balance : " << (BeginningBalance - Withdrawls + Deposits) << endl;
	Report << "Ending Balance : " << (BeginningBalance - Withdrawls + Deposits) << endl;
	cout << "Amount Deposited : " << Deposits << endl;
	cout << "Number of Deposits : " << NumberOfDeposits << endl;
	Report << "Number of Deposits : " << NumberOfDeposits << endl;
	cout << "Amount Withdrawn : " << Withdrawls << endl;
	Report << "Amount Withdrawn : " << Withdrawls << endl;
	cout << "Number of Withdrawls : " << NumberOfWithdrawls << endl;
	Report << "Number of Withdrawls : " << NumberOfWithdrawls << endl;
	cout << endl;
	Report << endl;
}
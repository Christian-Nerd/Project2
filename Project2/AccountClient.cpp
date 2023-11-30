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
void GetAccountFile(fstream& File) 
{
	string FileName; // Stores file name
	do
	{
		cout << "Please input account file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str(), ios::in);
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
			File.clear();
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
		cout << "Please input transaction history file path : ";
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str(), ios::in);
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
			File.clear();
			continue;
		}
	} 
	while (!File);
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
	while (!AccountFile.eof())
	{
		// If the next string is an account number...
		if (CurrentStreamCharacter == '\n' && isdigit(cin.peek()))
		{
			// Checks if account number already processed if so you ignore 
			if (LinearSearch(UsedAccountNumbers, NoOfNumsUsed, CurrentAccountNumber) >= 0)
			{
				AccountFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores line completely
				continue;
			}
			else
			{
				AccountFile >> CurrentAccountNumber;
				UsedAccountNumbers[NoOfNumsUsed++]; // Iterate Number of Numbers used  
				// & add AccountNumber tosedAccountNumbers before 
				// NoOfNumbers is iterated
				AccountFile.seekg(ios::beg); // Set stream back to beginning
				return CurrentAccountNumber; // Returns the account number 
				// since it the most recent one not previously used
			}
		}
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
// Functions Called: None
//*****************************************************************
int GetPreviousAccountBalance(fstream& TransactionHistory, int AccountNumber) 
{
	// Initialize Variables
	int PreviousAccountBalance; // Previous Account Balance
	char CurrentStreamCharacter = TransactionHistory.get(); // Finds current stream character
	int CurrentAcccountNumber; // Checks for current account number to see if it's out account number
	while (!TransactionHistory.eof()) 
	{
		// If the next string is the account number
		if (CurrentStreamCharacter == '\n' && isdigit(TransactionHistory.peek())) 
		{
			TransactionHistory >> CurrentAcccountNumber; // Finds Current Account Number and puts it in a variable
			if (CurrentAcccountNumber == AccountNumber) 
			{
				TransactionHistory >> PreviousAccountBalance; // Assigns previous account balance to a variable
				TransactionHistory.seekg(ios::beg); // Returns stream to beginning
				return PreviousAccountBalance;
			}
		}
	}
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
// Functions Called: None
//*****************************************************************
int GetNumberOfDeposits(fstream& TransactionHistory, int AccountNumber) 
{
	// Initilizes Variables
	string Dummy; // string variable to clear Previous Account Balance 
	int NumOfDeposits = 0;
	// and check if you find account number from stream
	char CurrentStreamCharacter = TransactionHistory.get(); // Finds current stream character
	while (!TransactionHistory.eof())
	{
		// If next string account number
		if (CurrentStreamCharacter == '\n' && isdigit(TransactionHistory.peek()))
		{
			TransactionHistory >> Dummy; // Puts account name into dummy variable
			// Checks if current account number is our account number
			if (Dummy.compare(to_string(AccountNumber)) == 0)
			{
				TransactionHistory >> Dummy; // Gets rid of current account balance
				while (CurrentStreamCharacter != '\n' && !TransactionHistory.eof())
				{
					switch (tolower(CurrentStreamCharacter))
					{
						case 'd':
							NumOfDeposits++; // Adds 1 to Number of deposits
							TransactionHistory >> Dummy; // Skips to next word;
							break;
						default:
							CurrentStreamCharacter = TransactionHistory.get(); 
							continue;
					}
				}
			}
		}
	    CurrentStreamCharacter = TransactionHistory.get(); 
	}
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
// Functions Called: None
//*****************************************************************
int GetSumOfDeposits(fstream& TransactionHistory, int AccountNumber) 
{
	// Initilizes Variables
	string Dummy = ""; // string variable to disgard Previous Account Balance 
	// and check if you find account number from stream
	char CurrentStreamCharacter = TransactionHistory.get(); // Finds current stream character
	int CurrentNumber = 0; // Current Deposit number
	int SumOfDeposits = 0; // Sum of all deposits associated with user
	while (!TransactionHistory.eof())
	{
		// If next string account number
		if (CurrentStreamCharacter == '\n' && isdigit(TransactionHistory.peek()))
		{
			TransactionHistory >> Dummy; // Puts account name into dummy variable
			// Checks if current account number is our account number
			if (Dummy.compare(to_string(AccountNumber)) == 0)
			{
				TransactionHistory >> Dummy; // Gets rid of current account balance
				while (TransactionHistory.peek() != '\n' && !TransactionHistory.eof())
				{
					switch (tolower(CurrentStreamCharacter))
					{
						case 'd':
							TransactionHistory >> CurrentNumber;
							SumOfDeposits += CurrentNumber;
							break;
						default:
							CurrentStreamCharacter = TransactionHistory.get(); 
							continue;
					}
				}
			}
		}
	    CurrentStreamCharacter = TransactionHistory.get(); 
	}
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
// Functions Called: None
//*****************************************************************
int GetNumberOfWithdrawls(fstream& TransactionHistory, int AccountNumber) 
{
	// Initilizes Variables
	string Dummy; // string variable to clear Previous Account Balance 
	int NumOfWithdrawls = 0;
	// and check if you find account number from stream
	char CurrentStreamCharacter = TransactionHistory.get(); // Finds current stream character
	while (!TransactionHistory.eof())
	{
		// If next string account number
		if (CurrentStreamCharacter == '\n' && isdigit(TransactionHistory.peek()))
		{
			TransactionHistory >> Dummy; // Puts account name into dummy variable
			// Checks if current account number is our account number
			if (Dummy.compare(to_string(AccountNumber)) == 0)
			{
				TransactionHistory >> Dummy; // Gets rid of current account balance
				while (CurrentStreamCharacter != '\n' && !TransactionHistory.eof())
				{
					switch (tolower(CurrentStreamCharacter))
					{
						case 'w':
							NumOfWithdrawls++; // Adds 1 to Number of deposits
							TransactionHistory >> Dummy; // Skips to next word;
							break;
						default:
							CurrentStreamCharacter = TransactionHistory.get(); 
							continue;
					}
				}
			}
		}
	    CurrentStreamCharacter = TransactionHistory.get(); 
	}
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
// Functions Called: None
//*****************************************************************
int GetSumOfWithdrawls(fstream& TransactionHistory, int AccountNumber)
{
	// Initilizes Variables
	string Dummy; // string variable to clear Previous Account Balance 
	int CurrentWithdrawl; // Current withdrawl number 
	int SumOfWithdrawls = 0; // Sum of Withdrawls 
	char CurrentStreamCharacter = TransactionHistory.get(); // Finds current stream character
	while (!TransactionHistory.eof())
	{
		// If next string account number
		if (CurrentStreamCharacter == '\n' && isdigit(TransactionHistory.peek()))
		{
			TransactionHistory >> Dummy; // Puts account name into dummy variable
			// Checks if current account number is our account number
			if (Dummy.compare(to_string(AccountNumber)) == 0)
			{
				TransactionHistory >> Dummy; // Gets rid of current account balance
				while (CurrentStreamCharacter != '\n' && !TransactionHistory.eof())
				{
					switch (tolower(CurrentStreamCharacter))
					{
						case 'w':
							TransactionHistory >> CurrentWithdrawl; // Skips to next word;
							break;
						default:
							CurrentStreamCharacter = TransactionHistory.get(); 
							continue;
					}
				}
			}
		}
	    CurrentStreamCharacter = TransactionHistory.get(); 
	}
	return 0;
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
//		Output: None
// Return Value: None
// Non-local Variables Used: None
// Functions Called: None
//*****************************************************************
void OutputAccountHistory(int AccountNumber, string AccountName, int BeginningBalance, int NumberOfDeposits, int Deposits, int NumberOfWithdrawls, int Withdrawls) 
{
	ofstream Report;
	string FileName = "monthly_report.txt";
	Report.open(FileName.c_str(), ios::in);
	cout << "Name : " << AccountName << endl;
	cout << "Account Number : " << AccountNumber << endl;
	cout << "Beginning Balance : " << BeginningBalance << endl;
	cout << "Ending Balance : " << (BeginningBalance - Withdrawls + Deposits) << endl;
	cout << "Amount Deposited : " << Deposits << endl;
	cout << "Number of Deposits : " << NumberOfDeposits << endl;
	cout << "Amount Withdrawn : " << Withdrawls << endl;
	cout << "Number of Withdrawls : " << NumberOfWithdrawls << endl;
}
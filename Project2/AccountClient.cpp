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
// Functions Called:  std::string::getline(), ios::clear, iostream::open
//*****************************************************************
void GetAccountFile(fstream& File) 
{
	string FileName; // Stores file name
	do
	{
		File.clear(); // When the file isn't opened and the loop runs again this allows operations to happen.
		cout << "Please input account file path : " << flush;
		getline(cin, FileName); // Gets File Path from user
		File.open(FileName.c_str(), ios::in);
		if(!File)
		{
			cerr << "Invalid File Path!" << endl;
            FileName = ""; // When streams loops again because failure make FileName empty
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
// Functions Called: std::string::getline(),  std::c_str(), fstream::open()
//*****************************************************************
void GetTransactionHistoryFile(fstream& File) 
{
	string FileName; // Stores file name
	// Error Checking loop
	do
	{
		File.clear(); // When the file isn't opened and the loop runs again this allows operations to happen.
		cout << "Please input transaction history file path : " << flush;
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
// Purpose: Gets Output File from code and opens it
// Parameters:
//		Input: Output File
//		Input & Output: None
//		Output: None
// Return Value: None
// Non-local Variables Used: None
// Functions Called: std::string::c_str
//*****************************************************************
void GetOutputFile(ofstream& File) 
{
	// Initializes Filename
	string FileName = "monthly_report.txt"; // Hardcoded filename
	File.open(FileName.c_str(), ios::out);
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
// Functions Called: std::std::number_limits<streamsize>::max, std::isdigit, istream::peek, istream::putback, istream::fail, istream::seekg
//*****************************************************************
int GetAccountNumber(fstream& AccountFile, int UsedAccountNumbers[], int &NoOfNumsUsed) 
{
	//Initializes Variables
	int CurrentAccountNumber = -1; // Potential Account Number
	char CurrentStreamCharacter; // Finds current stream character
    bool AtBeginningOfStream = true; // Checks if you're at the start of the stream
	// Until end of file checks for an unused account number
	while (!AccountFile.fail())
	{
		//int Extract = AccountFile.gcount(); // Number of characters extracted from stream used to check if at beginning of file
		// If the next string is an account number...
		if((CurrentStreamCharacter == '\n' || AtBeginningOfStream) && isdigit((unsigned char)AccountFile.peek()))
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
	    CurrentStreamCharacter = (char)AccountFile.get(); // Finds next current stream character
        AtBeginningOfStream = false;
	}
    // Clears errors and put file back to the beginning
    AccountFile.clear();
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
// Functions Called: std::isdigit, fstream::fail, std::stoi, istream::clear, istream::seekg, string::at
//*****************************************************************
string GetAccountName(fstream& AccountFile, int AccountNumber) 
{
	// Initializes Variables
	string AccountName; // Account name associated with user
	//char CurrentStreamCharacter = AccountFile.get(); // Finds current stream character
	// Searches account file for account number and then finds it
	while (!AccountFile.fail()) 
	{
		int CurrentAccountNumber; // Current Account Number
		// If next string account number
		//int Position = AccountFile.tellg(); // Gets position to check if at beginning of stream

			AccountFile >> CurrentAccountNumber; // Assign Current Account Number to CurrentAccountNumber
            AccountFile >> AccountName; // If our Account Number found then get the account name
            // If an account number has no account name adjust variables
            if (isdigit((unsigned char)AccountName.at(0)))
            {
                CurrentAccountNumber = stoi(AccountName);
                AccountFile >> AccountName; // If our Account Number found then get the account name
            }
			if (CurrentAccountNumber == AccountNumber)
			{
				AccountFile.clear(); // Clears any errors in case of eof
				AccountFile.seekg(ios::beg); // Set stream back to beginning
				return AccountName;
			}
		//CurrentStreamCharacter = AccountFile.get(); // Finds next current stream character
	}
    // Clears errors and put file back to the beginning
	AccountFile.clear(); // Clears any errors
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
// Functions Called: fstream::fail, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear
//*****************************************************************
float GetPreviousAccountBalance(fstream& TransactionHistory, int AccountNumber) 
{
	// Initialize Variables
	float PreviousAccountBalance; // Previous Account Balance
	char CurrentStreamCharacter; // Finds current stream character
    bool AtBeginningOfStream = true; // Checks if you're at the start of the stream
	int CurrentAcccountNumber; // Checks for current account number to see if it's out account number
    // Iterates through list and gets previous account balance
	while (!TransactionHistory.fail())
	{
		// If the next string is the account number
		if ((CurrentStreamCharacter == '\n' || AtBeginningOfStream) && isdigit(TransactionHistory.peek()))
		{
			TransactionHistory >> CurrentAcccountNumber; // Finds Current Account Number and puts it in a variable
			if (CurrentAcccountNumber == AccountNumber)
			{
				TransactionHistory >> PreviousAccountBalance; // Assigns previous account balance to a variable
				TransactionHistory.seekg(ios::beg); // Returns stream to beginning
				return PreviousAccountBalance;
			}
		}
        CurrentStreamCharacter = (char)TransactionHistory.get(); // Finds next current stream character
        AtBeginningOfStream = false;
	}
    TransactionHistory.clear(); // Clear stream of errors
	TransactionHistory.seekg(ios::beg); // Returns stream to beginning
	return -1;
}

//*****************************************************************
// Function Name: GetNumberOfDeposits
// Purpose: Gets & returns the of all deposits associated with a user in the Transaction File
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Number of deposits associated with users
// Non-local Variables Used: None
// Functions Called: fstream::fail, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::string::compare, istream::peek, stringstream::str
//*****************************************************************
int GetNumberOfDeposits(fstream& TransactionHistory, int AccountNumber) 
{
    // Initialize Variables
    string CurrentLine = " "; // Initialized to space to eliminate errors
    stringstream CurrentLineStream; // Current Line represented as a string
    int CurrentAccountNumber; // Current Account Number
    float CurrentDeposite; // Current Deposite
    int NumsOfDeposits = 0; // Sum of all deposits
    bool AtBeginningOfStream = true; // Checks if you're at the start of the stream
    char CurrentStreamCharacter; // Current Stream Character
    // Iterate thru list as long as Stream is valid and not at eof of CurrentLine
    while(TransactionHistory)
    {
        // If next string is account number put it in CurrentAccountNumber
        if((AtBeginningOfStream || CurrentStreamCharacter == '\n') && isdigit(TransactionHistory.peek()))
        {
            TransactionHistory >> CurrentAccountNumber;
        }
        // Get the name line into Currentline and put it into a stringstream
        // if CurrentAccount NUmber is the inputted account number
        if(CurrentAccountNumber == AccountNumber)
        {
            getline(TransactionHistory, CurrentLine);
            CurrentLineStream.str(CurrentLine);
        }
        // Checks current line if current account number is the same as the inputted account number
        for(; CurrentLineStream && (CurrentAccountNumber == AccountNumber); CurrentStreamCharacter = (char)CurrentLineStream.get())
        {
            if(CurrentStreamCharacter == 'd')
            {
                CurrentLineStream >> CurrentDeposite;
                NumsOfDeposits++;
            }
            if(CurrentLineStream.fail())
                CurrentLine = "end";
        }
        if(CurrentLine == "end")
            break;
        CurrentStreamCharacter = (char)TransactionHistory.get();
        AtBeginningOfStream = false;
    }
    TransactionHistory.clear(); // Clear stream of errors
    TransactionHistory.seekg(ios::beg); // Returns stream to beginning
    return NumsOfDeposits;
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
    // Initialize Variables
    string CurrentLine = " "; // Initialized to space to eliminate errors
    stringstream CurrentLineStream; // Current Line represented as a string
    int CurrentAccountNumber; // Current Account Number
    float CurrentDeposite; // Current Deposite
    float SumOfDeposits = 0; // Sum of all deposits
    bool AtBeginningOfStream = true; // Checks if you're at the start of the stream
    char CurrentStreamCharacter; // Current Stream Character
    // Iterate thru list as long as Stream is valid and not at eof of CurrentLine
    while(TransactionHistory)
    {
        // If next string is account number put it in CurrentAccountNumber
        if((AtBeginningOfStream || CurrentStreamCharacter == '\n') && isdigit(TransactionHistory.peek()))
        {
            TransactionHistory >> CurrentAccountNumber;
        }
        // Get the name line into Currentline and put it into a stringstream
        // if CurrentAccount NUmber is the inputted account number
        if(CurrentAccountNumber == AccountNumber)
        {
            getline(TransactionHistory, CurrentLine);
            CurrentLineStream.str(CurrentLine);
        }
        // Checks current line if current account number is the same as the inputted account number
        for(; CurrentLineStream && (CurrentAccountNumber == AccountNumber); CurrentStreamCharacter = (char)CurrentLineStream.get())
        {
            if(CurrentStreamCharacter == 'd')
            {
                CurrentLineStream >> CurrentDeposite;
                SumOfDeposits += CurrentDeposite;
            }
            if(CurrentLineStream.fail())
                CurrentLine = "end";
        }
        if(CurrentLine == "end")
            break;
        CurrentStreamCharacter = (char)TransactionHistory.get();
        AtBeginningOfStream = false;
    }
    TransactionHistory.clear(); // Clear stream of errors
    TransactionHistory.seekg(ios::beg); // Returns stream to beginning
    return SumOfDeposits;
}

//*****************************************************************
// Function Name: GetNumberOfWithdrawals
// Purpose: Gets the number of withdrawls a user made
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Number of Withdrawals a user made
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::tolower, std::string::compare, istream::peek
//*****************************************************************
int GetNumberOfWithdrawals(fstream& TransactionHistory, int AccountNumber)
{
    // Initialize Variables
    string CurrentLine = " "; // Initialized to space to eliminate errors
    stringstream CurrentLineStream; // Current Line represented as a string
    int CurrentAccountNumber; // Current Account Number
    float CurrentWithdrawals; // Current Withdrawals
    int NumsOfWithdrawals = 0; // Sum of all deposits
    bool AtBeginningOfStream = true; // Checks if you're at the start of the stream
    char CurrentStreamCharacter; // Current Stream Character
    // Iterate thru list as long as Stream is valid and not at eof of CurrentLine
    while(TransactionHistory)
    {
        // If next string is account number put it in CurrentAccountNumber
        if((AtBeginningOfStream || CurrentStreamCharacter == '\n') && isdigit(TransactionHistory.peek()))
        {
            TransactionHistory >> CurrentAccountNumber;
        }
        // Get the name line into Currentline and put it into a stringstream
        // if CurrentAccount NUmber is the inputted account number
        if(CurrentAccountNumber == AccountNumber)
        {
            getline(TransactionHistory, CurrentLine);
            CurrentLineStream.str(CurrentLine);
        }
        // Checks current line if current account number is the same as the inputted account number
        for(; CurrentLineStream && (CurrentAccountNumber == AccountNumber); CurrentStreamCharacter = (char)CurrentLineStream.get())
        {
            if(CurrentStreamCharacter == 'w')
            {
                CurrentLineStream >> CurrentWithdrawals;
                NumsOfWithdrawals++;
            }
            if(CurrentLineStream.fail())
                CurrentLine = "end";
        }
        if(CurrentLine == "end")
            break;
        CurrentStreamCharacter = (char)TransactionHistory.get();
        AtBeginningOfStream = false;
    }
    TransactionHistory.clear(); // Clear stream of errors
    TransactionHistory.seekg(ios::beg); // Returns stream to beginning
    return NumsOfWithdrawals;
}


//*****************************************************************
// Function Name: GetSumOfWithdrawals
// Purpose: Gets the sum of withdrawls a user made
// Parameters:
//		Input: Transaction File, Account Number
//		Input & Output: None
//		Output: None
// Return Value: Sum of all withdrawls 
// Non-local Variables Used: None
// Functions Called: fstream::eof, istream::tellg, istream:: putback, istream::seekg, istream:::get, std::isdigit, ios::clear, std::tolower, std::string::compare, istream::peek
//*****************************************************************
float GetSumOfWithdrawals(fstream& TransactionHistory, int AccountNumber)
{
    // Initialize Variables
    string CurrentLine = " "; // Initialized to space to eliminate errors
    stringstream CurrentLineStream; // Current Line represented as a string
    int CurrentAccountNumber; // Current Account Number
    float CurrentWithdrawl; // Current Deposite
    float SumOfWithdrawals = 0; // Sum of all deposits
    bool AtBeginningOfStream = true; // Checks if you're at the start of the stream
    char CurrentStreamCharacter; // Current Stream Character
    // Iterate thru list as long as Stream is valid and not at eof of CurrentLine
    while(TransactionHistory)
    {
        // If next string is account number put it in CurrentAccountNumber
        if((AtBeginningOfStream || CurrentStreamCharacter == '\n') && isdigit(TransactionHistory.peek()))
        {
            TransactionHistory >> CurrentAccountNumber;
        }
        // Get the name line into Currentline and put it into a stringstream
        // if CurrentAccount NUmber is the inputted account number
        if(CurrentAccountNumber == AccountNumber)
        {
            getline(TransactionHistory, CurrentLine);
            CurrentLineStream.str(CurrentLine);
        }
        // Checks current line if current account number is the same as the inputted account number
        for(; CurrentLineStream && (CurrentAccountNumber == AccountNumber); CurrentStreamCharacter = (char)CurrentLineStream.get())
        {
            if(CurrentStreamCharacter == 'w')
            {
                CurrentLineStream >> CurrentWithdrawl;
                SumOfWithdrawals += CurrentWithdrawl;
            }
            if(CurrentLineStream.fail())
                CurrentLine = "end";
        }
        if(CurrentLine == "end")
            break;
        CurrentStreamCharacter = (char)TransactionHistory.get();
        AtBeginningOfStream = false;
    }
    TransactionHistory.clear(); // Clear stream of errors
    TransactionHistory.seekg(ios::beg); // Returns stream to beginning
    return SumOfWithdrawals;
}


//*****************************************************************
// Function Name: IsThereDifferentAccounts
// Purpose: Checks if there is any unused account numbers left in the inputted Account file
// Parameters:
//		Input: Account File, Array containing all previously used account numbers, along with its size
//		Input & Output: None
//		Output: None
// Return Value: Whether there is any unused account numbers left in the inputted Account File
// Non-local Variables Used: None
// Functions Called: istream::clear, istream::seekg, istream::putback, std::isdigit, istream::peek
//*****************************************************************
bool IsThereDifferentAccounts(fstream& AccountFile, int UsedAccountNumbers[], int NoOfUsedAccountNumbers) 
{
	// Initialize Variables
	char CurrentStreamCharacter; // The current character in the stream
	int CurrentAccountNumber = -2; // Number that represents the current account number(set to a default that won't screw everything up)
    bool IsAtBeginningOfStream = true; // Stores if you're at beginning of stream
	// Checks for unused account numbers while AccountFile is still good
	// While the file is still good and input is valid check if there are any different account numbers
	while ((CurrentStreamCharacter = (char)AccountFile.get()) && AccountFile)
	{
		if ((CurrentStreamCharacter == '\n' || IsAtBeginningOfStream) && isdigit((unsigned char)AccountFile.peek()))
		{
			if (IsAtBeginningOfStream)
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
        IsAtBeginningOfStream = false; // Is at beginning of stream is now false
	}
    // Checks if the account number isn't in the list
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
int LinearSearch(int const List[], int Size, int Key)
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
//      Input: Account Number, Account Name, Beginning Balance, Number Of Deposits, Deposits, Number Of Withdrawals, Withdrawals
//		Input & Output: None 
//		Output: File which stores the output
// Return Value: None
// Non-local Variables Used: None
// Functions Called: None
//*****************************************************************
void OutputAccountHistory(int AccountNumber, string AccountName, float BeginningBalance, int NumberOfDeposits, float Deposits, int NumberOfWithdrawals, float Withdrawals, ofstream& Report)
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
	cout << "Ending Balance : " << (BeginningBalance - Withdrawals + Deposits) << endl;
	Report << "Ending Balance : " << (BeginningBalance - Withdrawals + Deposits) << endl;
	cout << "Amount Deposited : " << Deposits << endl;
	cout << "Number of Deposits : " << NumberOfDeposits << endl;
	Report << "Number of Deposits : " << NumberOfDeposits << endl;
	cout << "Amount Withdrawn : " << Withdrawals << endl;
	Report << "Amount Withdrawn : " << Withdrawals << endl;
	cout << "Number of Withdrawals : " << NumberOfWithdrawals << endl;
	Report << "Number of Withdrawals : " << NumberOfWithdrawals << endl;
	cout << endl;
	Report << endl;
}
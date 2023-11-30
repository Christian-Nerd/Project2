//*****************************************************************
//
// Programmer: Trey Davis
// Instructor: B.J Streller
// Course: CS121
// Date Created: 11/29/23
// Date Modified: 11/29/23
// Input Files; File storing account listing in the form as shown in the pdf, File for transaction history
// Output Files: monthly_report.txt stores monthly report
// Modules Used: idk
// Purpose: Finds account number of user then returns their monthly transaction history
//*****************************************************************
#include "Account.h"
int main() 
{
	// Initilize Variables
	fstream AccountFile;  // File stream storing accounts
	fstream TransactionFile; // File stream storing transactions
	int UsedAccountNumbers[static_cast<int>(1e4)];
	int AccountNumber = -1; // Account Number
	string AccountName = ""; // Account Name
	int NoOfUsedAccountNumbers = 0; // Number of used account numbers
	int SumOfDeposits; // Sum of all Deposits
	int NumberOfDeposits; // Number of Deposits in user account
	int SumOfWithdrawls; // Sum of all Withdrawls
	int NumberOfWithdrawls; // Number of Withdrawls in user account
	int PreviousAccountBalance; // Starting balance at beginning of month
	// Initilizing with functions
	GetAccountFile(AccountFile); // Putting account file in the stream
	GetTransactionHistoryFile(TransactionFile); // Putting transactions file in the stream
	AccountNumber = GetAccountNumber(AccountFile, UsedAccountNumbers, NoOfUsedAccountNumbers);
	cout <<  "" << !AccountFile; 
	cout << "" << !TransactionFile;
	AccountName = GetAccountName(AccountFile, AccountNumber);
	PreviousAccountBalance = GetPreviousAccountBalance(TransactionFile, AccountNumber);
	NumberOfDeposits = GetNumberOfDeposits(TransactionFile, AccountNumber);
	cout << endl << "Number 0 : " << TransactionFile.fail() << endl;
	SumOfDeposits = GetSumOfDeposits(TransactionFile, AccountNumber);
	NumberOfWithdrawls = GetNumberOfWithdrawls(TransactionFile, AccountNumber);
	SumOfWithdrawls = GetSumOfWithdrawls(TransactionFile, AccountNumber);
	AccountFile.close();
	TransactionFile.close();
	OutputAccountHistory(AccountNumber, AccountName, PreviousAccountBalance, NumberOfDeposits, SumOfDeposits, NumberOfWithdrawls, SumOfWithdrawls);
	return 0;
}

//*****************************************************************
//
// Programmer: Trey Davis
// Instructor: B.J Streller
// Course: CS121
// Date Created: 11/30/23
// Date Modified: 11/30/23
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
	ofstream Report; // Output File
	string FileName = "monthly_report.txt"; 
	Report.open(FileName.c_str(), ios::out); 
	int UsedAccountNumbers[static_cast<int>(2e3)];
	int AccountNumber = -1; // Account Number
	string AccountName = ""; // Account Name
	int NoOfUsedAccountNumbers = 0; // Number of used account numbers
	int SumOfDeposits; // Sum of all Deposits
	int NumberOfDeposits; // Number of Deposits in user account
	int SumOfWithdrawls; // Sum of all Withdrawls
	int NumberOfWithdrawls; // Number of Withdrawls in user account
	int PreviousAccountBalance; // Starting balance at beginning of month
	// Initilizing values with functions and outputting the report for each user
	GetAccountFile(AccountFile); // Putting account file in the stream
	while (IsThereDifferentAccounts(AccountFile, UsedAccountNumbers, NoOfUsedAccountNumbers))
	{
		if(!AccountFile.is_open())
			GetAccountFile(AccountFile); // Putting account file in the stream again for user
		if(!TransactionFile.is_open())
			GetTransactionHistoryFile(TransactionFile); // Putting transactions file in the stream
		AccountNumber = GetAccountNumber(AccountFile, UsedAccountNumbers, NoOfUsedAccountNumbers);
		AccountName = GetAccountName(AccountFile, AccountNumber);
		PreviousAccountBalance = GetPreviousAccountBalance(TransactionFile, AccountNumber);
		NumberOfDeposits = GetNumberOfDeposits(TransactionFile, AccountNumber);
		SumOfDeposits = GetSumOfDeposits(TransactionFile, AccountNumber);
		NumberOfWithdrawls = GetNumberOfWithdrawls(TransactionFile, AccountNumber);
		SumOfWithdrawls = GetSumOfWithdrawls(TransactionFile, AccountNumber);
		OutputAccountHistory(AccountNumber, AccountName, PreviousAccountBalance, NumberOfDeposits, SumOfDeposits, NumberOfWithdrawls, SumOfWithdrawls);
	}
	AccountFile.close();
	TransactionFile.close();
	return 0;
}

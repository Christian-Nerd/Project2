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
	// Initialize Variables
	fstream AccountFile;  // File stream storing accounts
	fstream TransactionFile; // File stream storing transactions
	ofstream Report; // Output File
	int UsedAccountNumbers[static_cast<int>(2e3)]; // Array that stores previously used account numbers
    Account Accounts[static_cast<int>(2e3)]; // Array that stores users
	int NoOfUsedAccountNumbers = 0; // Number of used account numbers
	float SumOfDeposits; // Sum of all Deposits
	int NumberOfDeposits; // Number of Deposits in user account
	float SumOfWithdrawals; // Sum of all Withdrawals
	int NumberOfWithdrawals; // Number of Withdrawals in user account
	float PreviousAccountBalance; // Starting balance at beginning of month
	// Initializing values with functions and outputting the report for each user
	GetAccountFile(AccountFile); // Putting account file in the stream
	GetOutputFile(Report); // Opens output file
	// Outputs the report for each user looping as long as there are different account numbers
	while (IsThereDifferentAccounts(AccountFile, UsedAccountNumbers, NoOfUsedAccountNumbers))
	{
        Account User = Accounts[NoOfUsedAccountNumbers]; // This variable is an alias for Accounts[NoOfUsedAccountNumbers]
        User.acct_num = -1; // User's account number initialized to impossible value
        User.name.clear(); // Makes string empty initially
		if(!AccountFile.is_open())
			GetAccountFile(AccountFile); // Putting account file in the stream again for user
		if(!TransactionFile.is_open())
			GetTransactionHistoryFile(TransactionFile); // Putting transactions file in the stream
		User.acct_num = GetAccountNumber(AccountFile, UsedAccountNumbers, NoOfUsedAccountNumbers); // Sets user account num to
		User.name = GetAccountName(AccountFile, User.acct_num); // Sets user's name
		PreviousAccountBalance = GetPreviousAccountBalance(TransactionFile, User.acct_num); // Finds user's previous account balance
		NumberOfDeposits = GetNumberOfDeposits(TransactionFile, User.acct_num); // Counts the number of deposits
		SumOfDeposits = GetSumOfDeposits(TransactionFile, User.acct_num); // Counts sum of withdrawals
		NumberOfWithdrawals = GetNumberOfWithdrawals(TransactionFile, User.acct_num); // Counts number of withdrawals
		SumOfWithdrawals = GetSumOfWithdrawals(TransactionFile, User.acct_num); // Counts sum of withdrawals
		// If there's no account name continue else Output the report
		if (User.name.empty())
			continue;
		else
			OutputAccountHistory(User.acct_num, User.name, PreviousAccountBalance, NumberOfDeposits, SumOfDeposits, NumberOfWithdrawals, SumOfWithdrawals, Report);
	}
	// Closes all files used and exists program
	AccountFile.close();
	TransactionFile.close();
	Report.close();
	return 0;
}

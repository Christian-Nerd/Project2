//********************************************************
//
// Programmer: Trey Davis
// Instructor: B.J. Streller
// Course: CS121
// Date: 11/28/23
// Program Name: Account.h
// Input Files: None
// Output Files: None
// Modules Used: 
// Purpose: Define Functions and Struct for project 2
// 
//********************************************************
#include <string> // For actual strings
#include<fstream> // For file manipulation
#include<iostream> // For regular i/o manipulations
#include<stdio.h> // Streller you said include this
#ifndef Account.h
#define Account
using namespace std;
struct Account
{
	int acct_num; // Account Number
	string name; // Name of person with account
	int acct_val; // Current net account value
};
string GetAccountFile(fstream File); // Finds account file name and error checks if it's accurate
string GetTransactionHistoryFile(fstream File); // Finds Transaction History file name and error checks if it's accurate
int GetAccountNumber(fstream AccountFile /*File where account information is*/); // Gets account number
string GetAccountName(fstream AccountFile, // File where account information is
					  string AccountName // Name associated with account number
					 );
int GetDeposits(fstream TransactionHistory, // Finds Transaction History
				int AccountNumber // Account Number of user
				); // Returns sum of all withdrawls for a user
int GetNumberOfDeposits(fstream TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number of user
						  ); // Returns Number of Deposits
int GetSumOfDeposits(fstream TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number
						  ); // Returns Sum of Deposits
int GetNumberOfWithdrawls(fstream TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number of user
						  ); // Returns Number of Withdrawls
int GetSumOfWithdrawls(fstream TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number
						  ); // Returns Sum of Withdrawls
void OutputAccountHistory(int AccountNumber, // Account Number of user
						  string AccountName, // Account name assoicated with user
					      int NumberOfDeposits, // Number of Deposits by user 
						  int Deposits, // Sum of all deposits
						  int NumberOfWithdrawls, // Number of Deposits
						  int Withdrawls // Sum of withdrawls
						  );
					      

#endif
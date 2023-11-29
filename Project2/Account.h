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
#include<iostream> // For regular i/o manipulation
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
void GetAccountFile(fstream File); // Finds account file name and error checks if it's accurate then opens it
void GetTransactionHistoryFile(fstream File); // Finds Transaction History file name and error checks if it's accurate then opens it
int GetAccountNumber(fstream AccountFile, // File where account information is
				   	  int UsedAccountNumbers[], // Previously used account numbers
				  	  int &NoOfNumsUsed // How many used numbers in array
					); // Gets account number
string GetAccountName(fstream AccountFile, // File where account information is
					  int AccountNumber // The account number assoicated with user
					  );
int GetPreviousAccountBalance(fstream TransactionHistory, // Finds Transaction History
					  		 int AccountNumber // Account Number of user
							 ); // Returns Previous account Transaction History
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
						  ); // Outputs the monthly report
int LinearSearch(int List[], // Array we are searching
				int Size, // Size of Array
				int Key // Key value we are searching for 
				); // Searchs array for key value
#endif
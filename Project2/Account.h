//********************************************************
//
// Programmer: Trey Davis
// Instructor: B.J. Streller
// Course: CS121
// Date: 11/29/23
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
#include<iomanip> // For setprecision
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
void GetAccountFile(fstream& File); // Finds account file name and error checks if it's accurate then opens it
void GetTransactionHistoryFile(fstream& File); // Finds Transaction History file name and error checks if it's accurate then opens it
int GetAccountNumber(fstream& AccountFile, // File where account information is
				   	  int UsedAccountNumbers[], // Previously used account numbers
				  	  int &NoOfNumsUsed // How many used numbers in array
					); // Gets account number
string GetAccountName(fstream& AccountFile, // File where account information is
					  int AccountNumber // The account number assoicated with user
					  );
float GetPreviousAccountBalance(fstream& TransactionHistory, // Finds Transaction History
					  		 int AccountNumber // Account Number of user
							 ); // Returns Previous account Transaction History
int GetNumberOfDeposits(fstream& TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number of user
						  ); // Returns Number of Deposits
float GetSumOfDeposits(fstream& TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number
						  ); // Returns Sum of Deposits
int GetNumberOfWithdrawls(fstream& TransactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number of user
						  ); // Returns Number of Withdrawls
float GetSumOfWithdrawls(fstream& TrathnsactionHistory, // Finds Transaction History
						  int AccountNumber // Account Number
						  ); // Returns Sum of Withdrawls assoicated with user
void OutputAccountHistory(int AccountNumber, // Account Number of user
						  string AccountName, // Account name assoicated with user
						  int BeginningBalance, // Balance at start of month
					      int NumberOfDeposits, // Number of Deposits by user 
						  int Deposits, // Sum of all deposits
						  int NumberOfWithdrawls, // Number of Deposits
						  int Withdrawls, // Sum of withdrawls
						  ofstream Report // Monthly report file to output to
						  ); // Outputs the monthly report
bool IsThereDifferentAccounts(fstream& AccountFile, // File containing account numbers
						      int UsedAccountNumbers[], // Array containing all used account numbers
							  int NoOfUsedAccountNumbers // Size of array
							); // Checks if there are any used account numbers
int LinearSearch(int List[], // Array we are searching
				int Size, // Size of Array
				int Key // Key value we are searching for 
				); // Searchs array for key value
#endif
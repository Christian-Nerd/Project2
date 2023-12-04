//********************************************************
//
// Programmer: Trey Davis
// Instructor: B.J. Streller
// Course: CS121
// Date: 12/4/23
// Program Name: Account.h
// Input Files: None
// Output Files: None
// Modules Used: 
// Purpose: Define Functions and Struct for project 2
// 
//********************************************************
#include <string> // For actual strings
#include<sstream>
#include<fstream> // For file manipulation
#include<iostream> // For regular i/o manipulation
#include<iomanip> // For setprecision
#include<stdio.h> // Streller you said include this
#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
using namespace std;
// Represents each user's account
struct Account
{
	int acct_num = 0; // Account Number
	string name = ""; // Name of person with account
	int acct_val = 0; // Current net account value
};
void GetAccountFile(fstream& File // IN: Account File
				    ); // Finds account file name and error checks if it's accurate then opens it
void GetTransactionHistoryFile(fstream& File // IN: Transaction File
							   ); // Finds Transaction History file name and error checks if it's accurate then opens it
void GetOutputFile(ofstream& File // IN: Output File
				   ); // Finds Output File Name than error checks if it's accurate then opens it.
int GetAccountNumber(fstream& AccountFile, // IN: File where account information is
				   	  int UsedAccountNumbers[], // IN: Previously used account numbers
				  	  int &NoOfNumsUsed // IN: How many used numbers in array
					); // Gets account number
string GetAccountName(fstream& AccountFile, // IN: File where account information is
					  int AccountNumber // IN: The account number assoicated with user
					  );
float GetPreviousAccountBalance(fstream& TransactionHistory, // IN: Finds Transaction History
					  		 int AccountNumber // IN: Account Number of user
							 ); // Returns Previous account Transaction History
int GetNumberOfDeposits(fstream& TransactionHistory, // IN: Finds Transaction History
						  int AccountNumber // IN: Account Number of user
						  ); // Returns Number of Deposits
float GetSumOfDeposits(fstream& TransactionHistory, // IN: Finds Transaction History
						  int AccountNumber // IN: Account Number
						  ); // Returns Sum of Deposits
int GetNumberOfWithdrawals(fstream& TransactionHistory, // IN: Finds Transaction History
						  int AccountNumber // IN: Account Number of user
						  ); // Returns Number of Withdrawls
float GetSumOfWithdrawals(fstream& TransactionHistory, // IN: Finds Transaction History
						  int AccountNumber // IN: Account Number
						  ); // Returns Sum of Withdrawls assoicated with user
void OutputAccountHistory(int AccountNumber, // IN: Account Number of user
						  string AccountName, // IN: Account name assoicated with user
						  float BeginningBalance, // IN: Balance at start of month
					      int NumberOfDeposits, // IN: Number of Deposits by user
						  float Deposits, // IN: Sum of all deposits
						  int NumberOfWithdrawls, // IN: Number of Deposits
						  float Withdrawls, // IN: Sum of withdrawls
						  ofstream& Report // OUT: Monthly report file to output to
						  ); // Outputs the monthly report
bool IsThereDifferentAccounts(fstream& AccountFile, // IN: File containing account numbers
						      int UsedAccountNumbers[], // IN: Array containing all used account numbers
							  int NoOfUsedAccountNumbers // IN: Size of array
							); // Checks if there are any used account numbers
int LinearSearch(int const List[], // Array we are searching
				int Size, // Size of Array
				int Key // Key value we are searching for 
				); // Searchs array for key value
#endif
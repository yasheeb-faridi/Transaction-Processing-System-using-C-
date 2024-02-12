// ClientData class Constructor file
// All the methods of ClientData.h header file is defined here.

#include <iostream>
#include "ClientData.h"
using namespace std;

// default ClientData constructor
ClientData::ClientData(int accountNumberValue, string firstNameValue, string lastNameValue, double balanceValue)
{
    setAccountNum(accountNumberValue);
    setFirstName(firstNameValue);
    setLastName(lastNameValue);
    setBalance(balanceValue);
}
// get account number value
int ClientData::getAccountNum() const
{
    return accountNum;
}
// set account number value
void ClientData::setAccountNum(int accountNumberValue)
{
    accountNum = accountNumberValue;
}
// get first-name value
string ClientData::getFirstName() const
{
    return firstName;
}
// set first-name value
void ClientData::setFirstName(string firstNameString)
{
    // copy at most 10 chars
    int length = firstNameString.size();
    length = (length < 15 ? length : 14);
    firstNameString.copy(firstName, length);
    firstName[length] = '\0'; // appending null char
}

string ClientData::getLastName() const
{
    return lastName;
}

void ClientData::setLastName(string lastNameString)
{
    int length = lastNameString.size();
    length = (length < 15 ? length : 14); // for copying at most 15 chars
    lastNameString.copy(lastName, length);
    lastName[length] = '\0'; // appending null character
}

double ClientData::getBalance() const
{
    return balance;
}

void ClientData::setBalance(double balanceValue)
{
    balance = balanceValue;
}

// it does not contain main() function. it only defines class method
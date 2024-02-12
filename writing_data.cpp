// Writing to a random-access file.
#include <iostream>
using std::cerr;
using std::cin;
using std::cout; 
using std::endl;
using std::ios;
#include <iomanip> 
using std::setw;
#include <fstream>
using std::fstream; 
#include <cstdlib>
using std::exit;                 // exit function prototype
#include "ClientData.h"         // ClientData class definition

int main(){
   int accountNum;
   char firstName[15];
   char lastName[15];
   double balance;
   fstream outCredit( "credit.dat", ios::in | ios::out | ios::binary );

   // exit program if fstream cannot open file 
   if ( !outCredit ){
      cerr << "File could not be opened." << endl; 
      exit( 1 );
   }

   cout << "Enter account number: (1 to 100, 0 to end input):\n? ";

   // require user to specify account number 
   ClientData client;
   cin >> accountNum;

   // user enters information, which is copied into file 
   while (accountNum > 0 && accountNum <= 100)
   {
      cout << "Enter firstname, lastName, balance\n? ";
      cin >> setw(15) >> firstName;
      cin >> setw(15) >> lastName;
      cin >> balance;
      client.setAccountNum(accountNum);
      client.setFirstName(firstName);
      client.setLastName(lastName);
      client.setBalance(balance);

      // seek position in file of user-specified record    
      outCredit.seekp((client.getAccountNum() - 1) * sizeof(ClientData));

      // write user-specified information in file                   
      outCredit.write(reinterpret_cast< const char * >( &client ),sizeof(ClientData));

      // enable user to enter another account 
      cout << "Enter account number\n? "; 
      cin >> accountNum; 
   }
   return 0; 
}
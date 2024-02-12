// This program reads a random-access file sequentially, updates data previously written to the file,
// creates data to be placed in the file and deletes data previously stored in the file.

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ios;
using std::left;
using std::right;
using std::showpoint;
#include <fstream> 
using std::ofstream;
using std::ostream; 
using std::fstream; 
#include <iomanip>
using std::setw;
using std::setprecision;
#include <cstdlib>
using std::exit;            // exit function prototype
#include "ClientData.h"     // ClientData class definition

int enterChoice();
void createTextFile(fstream& );
void updateRecord(fstream& );
void newRecord(fstream& );
void deleteRecord(fstream& );
void outputLine(ostream&, const ClientData & );
int getAccount(const char * const);

enum Choices { PRINT = 1, UPDATE, NEW, DELETE, END };
int main()
{
        // open file for reading and writing 
    fstream inOutCredit( "credit.dat", ios::in | ios::out | ios::binary);
        // exit program if fstream cannot open file
    if ( !inOutCredit){
        cerr << "File could not be opened." << endl;
        exit (1);
    }

    int choice;          // store user choice
                        // enable user to specify action
    while ( ( choice = enterChoice() ) != END )
    {
        switch ( choice )
        {
            case PRINT:         // create text file from record file
                createTextFile( inOutCredit );
                break;
            case UPDATE:
                updateRecord( inOutCredit );
                break;
            case NEW:        // create Record
                newRecord( inOutCredit );
                break;
            case DELETE:
                deleteRecord( inOutCredit );
                break;
            default:            // display error if user does not select valid choice
                cerr << "Incorrect choice" << endl;
                break;
        }     // end switch
        inOutCredit.clear();        // reset end-of-file indicator
    }       // end while
    return 0;
}

// enable user to input menu choice using funtion enterChoice
int enterChoice(){
                 // display available options
    cout << "\nEnter your choice" << endl
        << "1 - store a formatted text file of accounts" << endl
        << " called \"print.txt\" for printing" << endl
        << "2 - update an account" << endl
        << "3 - add a new account" << endl
        << "4 - delete an account" << endl
        << "5 - end program\n? ";

    int menuChoice;
    cin >> menuChoice;          // input menu selection from user
    return menuChoice;
}

// create formatted text file for printing
void createTextFile(fstream &readFromFile )
{
    // create text file 
    ofstream outPrintFile( "print.txt", ios::out );
    // exit program if ofstream cannot create file
    if ( !outPrintFile ){
        cerr << "File could not be created." << endl;
        exit(1);
    }else{
        cout << "****`print.txt` file created.*****" << endl;
    }
    
    outPrintFile << left << setw( 10 ) << "Account: " << setw( 16 )
        << "First Name" << setw( 11 ) << "Last Name" << right << setw( 15 ) << "Balance" << endl; 
        // set file-position pointer to beginning of readFromFile
    readFromFile.seekg( 0 );

    // read first record from record file
    ClientData client;
    readFromFile.read(reinterpret_cast< char * >( &client),sizeof(ClientData));

    // copy all records from record file into text file
    while ( !readFromFile.eof()){
                // write single record to text file
        if (client.getAccountNum() != 0) {
            outputLine( outPrintFile, client );          // skip empty records
        } 
        readFromFile.read(reinterpret_cast< char * >( &client), sizeof(ClientData)); // read next record from record file
    }
}       // end function createTextFile

// update balance in record
void updateRecord(fstream &updateFile){
    // obtain account number to update
    int accountNum = getAccount( "Enter account to update: ");
    // move file-position pointer to correct record in file 
    updateFile.seekg((accountNum - 1) * sizeof(ClientData));
    ClientData client;
    updateFile.read(reinterpret_cast< char * >( &client),sizeof(ClientData)); 
    // update record
    if (client.getAccountNum() != 0 ){
        outputLine(cout, client);
        
        // request user to specify transaction
        cout << "\nEnter Credit (+) or payment (-): ";
        double transaction;                             // charge or payment
        cin >> transaction;
        // update record balance
        double oldBalance = client.getBalance();
        client.setBalance(oldBalance + transaction);
        outputLine(cout, client);
        
        // move file-position pointer to correct record in file 
        updateFile.seekp( ( accountNum - 1 ) * sizeof( ClientData ) );

        // write updated record over old record in file 
        updateFile.write( reinterpret_cast< const char * >( &client ),sizeof( ClientData ) );
    }else{
        cerr << "Account #" << accountNum << " has no information." << endl; //display error if account doesn't exist
    }
}

// create and insert record
void newRecord(fstream &insertInFile){
        // obtain number of account to create
    int accountNum = getAccount( "Enter new account number: ");
        // move file-position pointer to correct record in file
    insertInFile.seekg( (accountNum - 1) * sizeof(ClientData));
    ClientData client;
    insertInFile.read(reinterpret_cast< char * >( &client),sizeof(ClientData)); 
        // create record, if record does not previously exist
    if (client.getAccountNum() == 0){
        char firstName[15];
        char lastName[15];
        double balance;

        cout << "Enter firstname, lastname, balance:\n? ";
        cin >> setw(15) >> firstName;
        cin >> setw(15) >> lastName;
        cin >> balance;

        //  use values to populate account data
        client.setFirstName(firstName);
        client.setLastName(lastName);
        client.setBalance(balance);
        client.setAccountNum(accountNum);

        // move file-position pointer to correct record in file
        insertInFile.seekp((accountNum - 1) * sizeof(ClientData));
        insertInFile.write(reinterpret_cast< const char * >( &client ),sizeof(ClientData));
    }else{
        cerr << "Account #" << accountNum << " already contains information." << endl;  //  display error if account already exists
    }
}

void deleteRecord( fstream &deleteFromFile )
{
    // obtain number of account to delete
    int accountNum = getAccount( "Enter account to delete: " );
    // move file-position pointer to correct record in file 
    deleteFromFile.seekg((accountNum - 1) * sizeof(ClientData));

    ClientData client;
    deleteFromFile.read( reinterpret_cast< char * >( &client ),sizeof(ClientData)); 
    // delete record, if record exists in file
    if (client.getAccountNum() != 0){
        ClientData blankClient;             // create blank record
        deleteFromFile.seekp( (accountNum - 1) * sizeof(ClientData)); 
        // replace existing record with blank record 
        deleteFromFile.write(reinterpret_cast< const char * >( &blankClient),sizeof(ClientData));
        cout << "Account #" << accountNum << " deleted.\n";
    }else{
        cerr << "Account #" << accountNum << " is empty.\n";    // if record doesn't exist
    }
}

void outputLine( ostream &output, const ClientData &record )
{
    output << left << setw(10) << record.getAccountNum()
    << setw(16) << record.getFirstName() << setw(16) << record.getLastName()
    << setw(10) << setprecision(2) << right << fixed << showpoint << record.getBalance() << endl;
}
    
// obtain account-number value from user
int getAccount( const char * const prompt ){
    int accountNum;
    
    do{
    cout << prompt << " (1 - 100): ";
    cin >> accountNum;
    } while ( accountNum < 1 || accountNum > 100 );
    return accountNum;
}
// creating randomly accessible file credit.dat
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ClientData.h"
using namespace std;

int main()
{

    ofstream outCredit ("credit.dat", ios::out | ios::binary);
    if (!outCredit){
        cerr << "File could not be opened." << endl;
        exit(1);
    }
    
    ClientData blankClient;         // constructor zeros out each data member
                                    // output 100 blank records to file
    for (int i=0; i<100; i++){
        outCredit.write(reinterpret_cast < const char * > (&blankClient),sizeof(ClientData));
    }
}
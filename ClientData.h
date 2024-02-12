#ifndef CLIENTDATA_H
#define CLIENTDATA_H
#include <string>
using namespace std;

class ClientData{
    public:
    ClientData(int = 0, string = " ", string = " ", double = 0.0);
    
    void setAccountNum(int);
    int getAccountNum() const;
    void setFirstName(string);
    string getFirstName() const;
    void setLastName(string);
    string getLastName() const;
    void setBalance(double);
    double getBalance() const;

    private:
    int accountNum;
    char firstName[15];
    char lastName[15];
    double balance;
};

#endif
#pragma once
#include <iostream>
#include<string>
#include "clsPerson.h"
#include "clsString.h"
#include<vector>
#include<fstream>
using namespace std;

class clsBankClient:public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1,AddMode=2 };
    
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDeleted = false;

    static clsBankClient _ConverLineToRecord(string line, string seperator = "#//#")
    {
        
      vector <string> vClientData;
      vClientData = clsString::Split(line, seperator);
      return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "" ,"", "", "", "", 0);
    }


    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }
    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConverLineToRecord(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(vClients);
    }
    void _AddNew()
    {
       _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }
    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);//overwrite
       if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }
    
    void  _RegisterTransferLog(float Amount, clsBankClient Destinationclient, string UserName)
    {
        string DataLine = _PrepareTransferLog(Amount, Destinationclient, UserName);
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);//overwrite
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }
    string  _PrepareTransferLog(float Amount, clsBankClient Destinationclient,string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord +=AccountNumber() + Seperator;
        TransferLogRecord += Destinationclient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord +=to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(Destinationclient.AccountBalance) + Seperator;
        TransferLogRecord += UserName ;
        return TransferLogRecord;
    }

    struct stTransferLogRecord;
   static stTransferLogRecord _ConverTransferLogToRecord(string line,string Seperator="#//#")
    {
       stTransferLogRecord TransferLogRecord;
       vector<string> vTransferLogRecord = clsString::Split(line, Seperator);
       TransferLogRecord.DateTime = vTransferLogRecord[0];
       TransferLogRecord.SourceAccountNumber= vTransferLogRecord[1] ;
       TransferLogRecord.DestinationAccountNumber = vTransferLogRecord[2];
       TransferLogRecord.Amount =stof( vTransferLogRecord[3]);
       TransferLogRecord.SourceBalanceAfter =stof(vTransferLogRecord[4]);
       TransferLogRecord.DestinationBalanceAfter = stof(vTransferLogRecord[5]);
       TransferLogRecord.UserName = vTransferLogRecord[6];
       return TransferLogRecord;
    }
public:

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
        :clsPerson(FirstName, LastName, Email, Phone)
    {
        _AccountNumber= AccountNumber ;
        _PinCode = PinCode;
        _AccountBalance=AccountBalance ;
        _Mode = Mode;
    }
   
    bool  IsEmpty()
    {
        return(_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDeleted;
    }
    //Property Get 
    string AccountNumber()
    {
        return _AccountNumber;
    }
   
    //Property Set
    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    //Property Get
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    //Property Set
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    //Property Get
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    /* void Print()
    {
        cout << "\nClient Card:";
        cout << "\n_______";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n_______\n";

    }
    */
    


    static clsBankClient Find(string AccountNumber)
    {

        fstream myfile;
        myfile.open("Clients.txt", ios::in);
        if (myfile.is_open())
        {
            string line;
            while (getline(myfile, line))
            {
              clsBankClient client = _ConverLineToRecord(line);
              if (client._AccountNumber == AccountNumber)
              {
                  myfile.close();
                  return client;
              }
            }
            myfile.close();
        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber,string PinCode)
    {

        fstream myfile;
        myfile.open("Clients.txt", ios::in);
        if (myfile.is_open())
        {
            string line;
            while (getline(myfile, line))
            {
                clsBankClient client = _ConverLineToRecord(line);
                if (client._AccountNumber == AccountNumber && client.PinCode == PinCode)
                {
                    myfile.close();
                    return client;
                }
            }
            myfile.close();
        }
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient client1 = clsBankClient::Find(AccountNumber);
        return(!client1.IsEmpty());
    }

    enum enSaveResults  {svFaildEmptyObject=0,svSaveSucceeded,svFailedAccountNumberExists};
 
    enSaveResults Save()
    {
        switch (_Mode)
        {

          case clsBankClient::EmptyMode:
              if (IsEmpty())
              {
                  return enSaveResults::svFaildEmptyObject;
              }
          case clsBankClient::UpdateMode:
              _Update();
              return enSaveResults::svSaveSucceeded;
          case clsBankClient::AddMode:
              if (IsClientExist(_AccountNumber))
              {
                  return enSaveResults::svFailedAccountNumberExists;
              }
              else
              {
                  _AddNew();
                  _Mode = enMode::UpdateMode;
                  return enSaveResults::svSaveSucceeded;
              }
        }
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
    }
    bool Delete()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient & C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C._MarkedForDeleted = true;
                break;
            }
        }
        _SaveCleintsDataToFile(vClients);

        *this = _GetEmptyClientObject();
        return true;
    }
    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }
    static float GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;

    }

    void Deposit(float Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(float Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
        }
    }
    bool Transfer(float Amount ,clsBankClient & Destinationclient, string UserName)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        Withdraw(Amount);
        Destinationclient.Deposit(Amount) ;
        _RegisterTransferLog(Amount, Destinationclient,UserName);
        return true;
    }
    
    struct stTransferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float SourceBalanceAfter;
        float DestinationBalanceAfter;
        string UserName;
    };
    static vector<stTransferLogRecord> GetTransferLogFromFile()
    {
        fstream myfile;
        vector <stTransferLogRecord> vTransferLogRecord;
        myfile.open("TransferLog.txt", ios::in);
        if (myfile.is_open())
        {
            string line;
            while (getline(myfile, line))
            {
                stTransferLogRecord TransferRecord = _ConverTransferLogToRecord(line);
                vTransferLogRecord.push_back(TransferRecord);
            }
            myfile.close();
        }
        return vTransferLogRecord;
    }
    
};


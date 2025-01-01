#pragma once
#include <iostream>
#include"clsInputValidate.h";
#include"clsBankClient.h";
#include"clsScreen.h"
using namespace std;

class clsAddNewClientScreen:protected clsScreen
{
private:

   static void  _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }

   static void _PrintClient(clsBankClient Client)
   {
       cout << "\nClient Card:";
       cout << "\n____________________";
       cout << "\nFirstName   : " << Client.FirstName;
       cout << "\nLastName    : " << Client.LastName;
       cout << "\nFull Name   : " << Client.FullName();
       cout << "\nEmail       : " << Client.Email;
       cout << "\nPhone       : " << Client.Phone;
       cout << "\nAcc. Number : " << Client.AccountNumber();
       cout << "\nPassword    : " << Client.PinCode;
       cout << "\nBalance     : " << Client.AccountBalance;
       cout << "\_____________________\n";

   }

public:

  static  void AddClient()
    {
      if (!CheckAccessPermission(clsUser::enPermissionOption::AddPermission))
      {
          return;
      }
        _DrawScreenHeader("\t Add New Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is already used, please enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::svSaveSucceeded:
            cout << "\nAccount Update Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        case clsBankClient::svFaildEmptyObject:
            cout << "\nError account was not saved because its empty";
            break;
        case clsBankClient::svFailedAccountNumberExists:
            cout << "\nError account was not saved because account number is used! \n";
            break;
        }
    }

};







#pragma once
#include <iostream>
#include"clsInputValidate.h";
#include"clsUser.h";
#include"clsScreen.h"
using namespace std;

class clsFindUserScreen :protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n_______";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n_______\n";

    }
public:

    static void ShowFindUserScreen()
    {
       
        _DrawScreenHeader("\t Find Client Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (! clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found,please enter another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);

        if (!User.IsEmpty())
        {
            cout << "\nUser is Found :-)\n";
            _PrintUser(User);
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }
    }
};


#pragma once
#include <iostream>
#include"clsInputValidate.h";
#include"clsUser.h";
#include"clsScreen.h"
using namespace std;

class clsUpdateUserScreen :protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionToSet();
    }
    static int _ReadPermissionToSet()
    {
        int Permission = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full aaccess? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give aaccess to: \n";
        cout << "show client list? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::ShowPermission;
        }

        cout << "add new client ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::AddPermission;
        }

        cout << "delete client ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::DelPermission;
        }

        cout << "Update client ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::UpdatePermission;
        }

        cout << "Find client ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::FindPermission;
        }

        cout << "Transactions ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::TransPermission;
        }

        cout << "Manage Users ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::ManageUserPermission;
        }
        cout << "Login Register Users ? y/n : ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permission += clsUser::enPermissionOption::LoginRegisterPermission;
        }
        return Permission;
    }
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

    static void ShowUpdateUserScreen()
    {
        
        _DrawScreenHeader("\t Update User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found,please enter another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nAre you sure you want to Update this User y/n ? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {

            cout << "\nUpdate User Info:";
            cout << "\n-------------------\n";
            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResult;
            SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUser::svFaildEmptyObject:
                cout << "\nError account was not saved because its empty";
                break;
            case clsUser::svSucceeded:
                cout << "\nAccount Update Successfully :-)\n";
                _PrintUser(User);
                break;
            }
        }
    }
};






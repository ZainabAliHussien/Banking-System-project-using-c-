#pragma once
#include <iostream>
#include "clsUser.h"
#include <iomanip>
#include "clsScreen.h"

class clsLoginRegisterScreen :protected clsScreen
{
private:

    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    }
public:

    static void ShowLoginRegisterUser()
    {
        if (!CheckAccessPermission(clsUser::enPermissionOption::LoginRegisterPermission))
        {
            return;
        }
        _DrawScreenHeader("\t Find Client Screen");


        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "\t Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") User(s)";
        _DrawScreenHeader(Title, SubTitle);

       
        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t___________";
        cout << "_________\n" << endl;


        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord User : vLoginRegisterRecord)
            {

                _PrintLoginRegisterRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t___________";
        cout << "_________\n" << endl;

    }
};

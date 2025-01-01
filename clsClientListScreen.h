#pragma once
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"

class clsClientListScreen:protected clsScreen
{
private:

    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }
public:

   static void ShowClientsList()
    {
       if (!CheckAccessPermission(clsUser::enPermissionOption::ShowPermission))
       {
           return;
       }
       vector <clsBankClient> vClients = clsBankClient::GetClientsList();

       string Title = "\t Client List Screen";
       string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s)";
       _DrawScreenHeader(Title, SubTitle);


        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n___________";
        cout << "_________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n___________";
        cout << "_________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                _PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n___________";
        cout << "_________\n" << endl;

    }
};


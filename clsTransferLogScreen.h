#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
using namespace std;

class clsTransferLogScreen:protected clsScreen
{
private:
    static void  _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord  Record)
    {
        cout << setw(8) << left << "" << "| " << left << setw(23) << Record.DateTime ;
        cout << "| " << left << setw(8) << Record.SourceAccountNumber;
        cout << "| " << left << setw(8) << Record.DestinationAccountNumber;
        cout << "| " << left << setw(8) << Record.Amount;
        cout << "| " << left << setw(10) << Record.SourceBalanceAfter;
        cout << "| " << left << setw(10) << Record.DestinationBalanceAfter;
        cout << "| " << left << setw(8) << Record.UserName;
        
    }
public:
	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogFromFile();

        string Title = "\t Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") User(s)";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________\n" << endl;


        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfer  Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t________________________________________________________________________________________\n" << endl;


	}
};


#pragma once
#include<iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersScreen:protected clsScreen
{
private:
	enum enManageUsersMenueOptions {eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,eUpdateUser = 4, eFindUser = 5, eMainMenue = 6};

	static short _ReadManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}
	static void _GoBackToMangeUsersMenue()
	{
		cout << "\n\npress any key to go back to Main Users Menue....." << endl;
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		//cout << "\nList Users Screen Will Be Here.\n";
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "\nAdd New User Screen Will Be Here.\n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "\nDelete User Screen Will Be Here.\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		//cout << "\nUpdate User Screen Will Be Here.\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		//cout << "\nFind User Screen Will Be Here.\n";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
	{
		switch (ManageUsersMenueOption)
		{
		case enManageUsersMenueOptions::eListUsers:
			system("cls");
			_ShowListUsersScreen() ;
			_GoBackToMangeUsersMenue();
			break;
		case enManageUsersMenueOptions::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen() ;
			_GoBackToMangeUsersMenue();
			break;
		case enManageUsersMenueOptions::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen() ;
			_GoBackToMangeUsersMenue();
			break;
		case enManageUsersMenueOptions::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToMangeUsersMenue();
			break;
		case enManageUsersMenueOptions::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToMangeUsersMenue();
			break;
		case enManageUsersMenueOptions::eMainMenue:
			//do nothing here the main screen handle it
			break;
		}
	}
public:
	static void ShowManageUsersMenue()
	{
		
		if (!CheckAccessPermission(clsUser::enPermissionOption::ManageUserPermission))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("\t\tManage User Screen");

		cout << setw(37) << left << "" << "==================================================\n";
		cout << setw(55) << left << "" << "Manage User Menue " << endl;
		cout << setw(37) << left << "" << "==================================================\n";
		cout << setw(37) << left << "" << "[1] List Users." << endl;
		cout << setw(37) << left << "" << "[2] Add New User." << endl;
		cout << setw(37) << left << "" << "[3] Delete User." << endl;
		cout << setw(37) << left << "" << "[4] Updatte User." << endl;
		cout << setw(37) << left << "" << "[5] Find User ." << endl;
		cout << setw(37) << left << "" << "[6] Main Menue ." << endl;
		cout << setw(37) << left << "" << "==================================================\n";
		_PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());

	}
};

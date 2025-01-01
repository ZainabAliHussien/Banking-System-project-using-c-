#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsLoginScreen:protected clsScreen
{
private:
	static bool  _Login()
	{
		bool LoginFailed =false ;
		string UserName ="";
		string PassWord="";
		short AttemptsNumber = 3;
		do {
			  if (LoginFailed)
			   {
				  cout << "\nInvalid UserName/Password! \n";
				  cout << "You have " << --AttemptsNumber << " Trials to Login\n\n"; 
			   }
			  if (AttemptsNumber == 0)
			  {
				  cout << "You are locked after 3 failed trails ";
				  return false ;
			  }
			  cout << "Enter UserName? ";
			  cin >> UserName;
			  cout << "Enter Password? ";
			  cin >> PassWord ;
			  CurrentUser = clsUser::Find(UserName,PassWord);
			  LoginFailed = CurrentUser.IsEmpty();
		   } while (LoginFailed);
		 CurrentUser.RegisterLoginInfo() ;
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:

	static bool ShowLoginScreen()
	{
		system("cls");
	    clsScreen::_DrawScreenHeader("\t Login Screen");
	    return _Login();
	}

	
};


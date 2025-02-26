#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include<vector>
#include<fstream>
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsUser:public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode=2};
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;


     string _ConverLoginRegisterUserToLine( string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += clsDate::GetSystemDateTimeString() + Seperator;
        UserRecord += UserName + Seperator;
        UserRecord +=clsUtil::EncryptText(Password) + Seperator;
        UserRecord += to_string(Permissions);

        return UserRecord;
    }
   static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser( vUserData[0], vUserData[1], vUserData[2],
            vUserData[3],enMode::UpdateMode, vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
        
    }
   struct stLoginRegisterRecord;
   static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
   {
       vector<string> vUserData;
       vUserData = clsString::Split(Line, Seperator);
       stLoginRegisterRecord LoginRegisterRecord;
       LoginRegisterRecord.DateTime = vUserData[0];
       LoginRegisterRecord.UserName = vUserData[1];
       LoginRegisterRecord.Password = clsUtil::DecryptText(vUserData[2]);
       LoginRegisterRecord.Permissions = stoi(vUserData[3]);
       return LoginRegisterRecord;
   }
   static clsUser _GetEmptyUserObject()
   {
       return clsUser( "", "", "", "", enMode::EmptyMode, "", "", 0);
   }
   static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
   {

       string UserRecord = "";
       UserRecord += User.FirstName + Seperator;
       UserRecord += User.LastName + Seperator;
       UserRecord += User.Email + Seperator;
       UserRecord += User.Phone + Seperator;
       UserRecord += User.UserName + Seperator;
       UserRecord += clsUtil::EncryptText( User.Password) + Seperator;
       UserRecord += to_string(User.Permissions);

       return UserRecord;

   }
   static  vector <clsUser> _LoadUsersDataFromFile()
   {

       vector <clsUser> vUsers;

       fstream MyFile;
       MyFile.open("Users.txt", ios::in);//read Mode

       if (MyFile.is_open())
       {

           string Line;


           while (getline(MyFile, Line))
           {

               clsUser User = _ConvertLinetoUserObject(Line);

               vUsers.push_back(User);
           }

           MyFile.close();

       }

       return vUsers;

   }
   static void _SaveUsersDataToFile(vector <clsUser> vUsers)
   {

       fstream MyFile;
       MyFile.open("Users.txt", ios::out);//overwrite

       string DataLine;

       if (MyFile.is_open())
       {

           for (clsUser U : vUsers)
           {
               if (U.MarkedForDeleted() == false)
               {
                   //we only write records that are not marked for delete.  
                   DataLine = _ConverUserObjectToLine(U);
                   MyFile << DataLine << endl;

               }

           }

           MyFile.close();

       }

   }
   void _AddDataLineToFile(string  stDataLine)
   {
       fstream MyFile;
       MyFile.open("Users.txt", ios::out | ios::app);

       if (MyFile.is_open())
       {

           MyFile << stDataLine << endl;

           MyFile.close();
       }

   }
   
   void _Update()
   {
       vector <clsUser> _vUsers;
       _vUsers = _LoadUsersDataFromFile();

       for (clsUser& U : _vUsers)
       {
           if (U.UserName == UserName)
           {
               U = *this;
               break;
           }

       }

       _SaveUsersDataToFile(_vUsers);

   }
   void _AddNew()
   {
       _AddDataLineToFile(_ConverUserObjectToLine(*this));
   }

   
public:
    clsUser(string FirstName, string LastName, string Email, string Phone, enMode Mode, string UserName, string Password, int Permissions)
           :clsPerson(FirstName, LastName, Email, Phone)
    {
         _Mode= Mode;
         _UserName= UserName;
         _Password= Password;
         _Permissions= Permissions;
    }
    

    string GetUserName()
    {
        return _UserName;
    }
     void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    bool MarkedForDeleted()
    {
        return _MarkedForDelete ;
    }


    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }
    
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser( "", "", "", "", enMode::AddNewMode, UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    
    enum enPermissionOption { AllPermission = -1, ShowPermission = 1, AddPermission = 2, DelPermission = 4, UpdatePermission = 8, FindPermission = 16, TransPermission = 32, ManageUserPermission = 64,LoginRegisterPermission=128 };

    
     bool CheckAccessPermission(enPermissionOption permission)
    {
        if (this->Permissions == enPermissionOption::AllPermission)
        {
            return true;
        }
        if ((this->Permissions & permission) == permission)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
     
      void RegisterLoginInfo()
     {
         
         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::out | ios::app );//overwrite

         string DataLine;

         if (MyFile.is_open())
         {

                     //we only write records that are not marked for delete.  
                    DataLine = _ConverLoginRegisterUserToLine("#//#");
                     MyFile << DataLine << endl;

             MyFile.close();

         }
     }
      struct stLoginRegisterRecord
      {
          string DateTime;
          string UserName;
          string Password;
          int Permissions;
      };
      static vector <stLoginRegisterRecord> GetLoginRegisterList()
      {
          vector<stLoginRegisterRecord> vLoginRegisterRecord;

          fstream MyFile;
          MyFile.open("LoginRegister.txt", ios::in);//read Mode

          if (MyFile.is_open())
          {
              string Line;
              while (getline(MyFile, Line))
              {
                  stLoginRegisterRecord User = _ConvertLoginRegisterLineToRecord(Line);
                  vLoginRegisterRecord.push_back(User);
              }
              MyFile.close();
          }
          return vLoginRegisterRecord;
      }
};


#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdlib>
using namespace std;

void login();
void registration();
void forgot();

int main(){

    int c;
    printf("\n\n");
    cout<<"\t\t\t ________________________________\n\n";
    cout<<"\t\t\t|___  Welcome To Login Page  ____|\n\n";
    cout<<"\t\t\t|__________    MENU     _________|\n\n";
    cout<<"\t\t\t|_|_|_|_|_|_|_|_**_|_|_|_|_|_|_|_|\n\n";
    cout<<"\t\t\t| Press 1 to LOGIN               |\n\n";
    cout<<"\t\t\t| Press 2 to REGISTER            |\n\n";
    cout<<"\t\t\t| Press 3 to if forgot password  |\n\n";
    cout<<"\t\t\t| Press 4 to EXIT                |\n\n";
    cout<<"\t\t\t| Enter your Choice: ";
    cin>>c;
    cout<<"\t\t\t|________________________________|\n\n";
    
    cout<<endl;

    switch(c){
        case 1:
            login();
            break;
        case 2:
            registration();
            break;
        case 3:
            forgot();
            break;
        case 4:
            cout<<"\t\t\t|EXITING !!!    _________________|\n\n";
            break;
        default:
            system("cls");
            cout<<"\t\t\t|WRONG OPTION   _________________|\n\n";
            main();

    }
}

void login(){
    int count;
    string userId, password,id ,pass;
    system("cls");
    cout<<"\t\t\t ________________________________\n\n";
    cout<<"\t\t\t|__ Enter Username & Password  __|\n\n"; 
    cout<<"\t\t\t| USERNAME: ";   
    cin>>userId;
    cout<<"\n\n";
    cout<<"\t\t\t| PASSWORD: ";
    cin>>password;
    cout<<"\n\n";

    ifstream input("records.txt");

    while (input>>id>>pass){
        if(id==userId && pass==password){
            count=1;
            system("cls");
        }
    } input.close();

    if(count==1){
        cout<<"\t\t\t ________________________________\n";
        cout<<"\t\t\t !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout<<"\t\t\t  "<<userId<<" Your Login is Successfull\n";
        cout<<"\t\t\t !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout<<"\t\t\t ________________________________\n";
        cout<<"\t\t\t|___  Thanks for Logging In   ___|\n";
        cout<<"\t\t\t|$ # $ # $ # $ # __ $ # $ # $ # $|\n";
        cout<<"\t\t\t ________________________________\n\n";
        main();
    }
    else{
        cout<<"\t\t\t ________________________________\n";
        cout<<"\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout<<"\t\t\t  "<<userId<<" LOGIN ERROR!!! \n\t\t\t Check Your Username And Password. \n";
        cout<<"\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout<<"\t\t\t ________________________________\n";

        main();
    }
}

void registration(){
    string ruserId, rpassword, rid, rpass;
    system("cls");
    cout<<"\t\t\t ________________________________\n\n";
    cout<<"\t\t\t| Enter USERNAME: ";   
    cin>>ruserId;
    cout<<"\n\n";
    cout<<"\t\t\t| Enter PASSWORD: ";
    cin>>rpassword;
    cout<<"\n\n";

    ofstream f1("records.txt", ios::app);
    f1<<ruserId<<" "<<rpassword<<endl;
    system("cls");
    cout<<"\n\t\t\t|__  Registration Succesful!!  __|";
    cout<<"\t\t\t ________________________________\n\n";
    main();
}

void forgot() {
    int option;
    cout << "\t\t\t|________________________________|\n\n";
    cout << "\t\t\t|____  Password Forgotten .  ____|\n\n";
    cout << "\t\t\t| Press 1 to search with username|\n\n";
    cout << "\t\t\t| Press 2 to go back to main menu|\n\n";
    cout << "\t\t\t| Enter your Choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            int count = 0;
            string suserId, sId, spass;
            cout << "\t\t\t ________________________________\n\n";
            cout << "\t\t\t| Enter remembered USERNAME: ";
            cin >> suserId;

            ifstream f2("records.txt");
            while (f2 >> sId >> spass) {
                if (sId == suserId) {
                    count = 1;
                    break;
                }
            }
            f2.close();

            if (count == 1) {
                cout << "\t\t\t|________________________________|\n\n";
                cout << "\t\t\t|____ Your account is found  ____|\n\n";
                cout << "\t\t\t|_ Password is: " << spass << " _|\n\n";
            } else {
                cout << "\t\t\t|__  Sorry! Account Not Found ___|\n\n";
                main();
            }
            break;
        }
        case 2:
            main();
            break;
        default:
            cout << "\t\t\t|WRONG CHOICE   _________________|\n\n";
            forgot();
            break;
    }
}

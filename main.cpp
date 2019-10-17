#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include<cctype>
using namespace std;

int no_menu(int menu,int llimit);
void showtime();
int encode(int p);
int rangenerator();
void writeup(string &user,string &pin,double &eWallet,double &eWallet_limit);
void signup(string &user,string &pin,double &eWallet,double &eWallet_limit);
bool finder(string user,string pin,double &eWallet,double &eWallet_limit);
void Deposit_menu(double &eWallet,double &eWallet_limit);
void display_eWallet(double eWallet);
bool change_limit(double limit,double &eWallet_limit);
bool using_eWallet(double intake,double &eWallet,double &eWallet_limit);
void main_menu(string &user,string &pin,double &eWallet,double &eWallet_limit);
void purchase_menu(double &eWallet,double &eWallet_limit);
void transaction_menu(bool showall,double eWallet);
void changepin(string &user,string &pin,double &eWallet,double &eWallet_limit);
void writepurchase(string item, double price,double pricesst,int no_item,double total_price);
string gettime();
string pin_itos(int pinno);
int decode(int p);
void exiting(string &user,string &pin, double &eWallet,double &eWallet_limit);

int main()
{
    string user,pin;
    double eWallet, eWallet_limit;
do{
                    system("cls");
                    showtime();
                    cout << "Welcome to Intelligent Vending Machine!"<< flush << endl ;
                    int menu_no;
                            cout << "Login Page" <<endl;
                            cout << "Press 1 to login."<<endl;
                            cout << "Press 2 to create new account."<<endl;
                            cout << "Press 3 to exit."<<endl;
                            menu_no=no_menu(3,1); //Get number of menu
                    if (menu_no==2)
                    {
                        eWallet=0;
                        eWallet_limit=1000;
                        signup(user,pin,eWallet,eWallet_limit);
                        main_menu(user,pin,eWallet,eWallet_limit);
                    }
                         else if(menu_no==1)
                            {
                            cout << "Account name: ";
                            cin.ignore();
                            getline(cin,user);
                            cout << "Account pin number: ";
                            cin.clear();
                            pin = pin_itos(encode(no_menu(999999,0))); //encode and convert pin into string because it is easier to compare with the string get from file.
                            if(finder(user,pin,eWallet,eWallet_limit))
                            { cin.clear();cin.ignore();
                            cin.get();
                            main_menu(user,pin,eWallet,eWallet_limit);}}
                            else if(menu_no=3) return 0;
                            }while(true);
}

int no_menu(int menu,int llimit) //Get the number from user within the range that is set.
{
    int nomenu;
    cin >> nomenu;
    while (!(llimit<=nomenu && nomenu<=menu) || cin.fail())
    {
        cin.clear();
        cin.sync(); //Try delete this line and type character in selecting menu. Avoid bug or infinite loop of  the cout forehand and skipping cin afterward.
        cout<<"Good try. Please try again with valid number.\n";
        cin >> nomenu;
    }
    return nomenu;
}

void showtime()
{
//Display time
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"Now it's %I:%M%p. %x",timeinfo );

    cout << buffer << flush << endl ;



}

//------------------------------------------------------------------------------------------
//main menu
 void main_menu(string &user,string &pin,double &eWallet,double &eWallet_limit)
 {
     ofstream writepur;
    writepur.open("Transaction.txt",ios::trunc);
    writepur.close();
    clock_t t;
    t = clock();
     do
    {
     system("cls");
     showtime();
     cout << "Main Menu"<<endl;
     cout << "Welcome back,"<<user<<endl;
     display_eWallet(eWallet);
     cout << " Please choose one of the following menu."<< endl;
     cout << "1) eWallet"<<endl;
     cout << "2) Purchase Item"<<endl;
     cout << "3) Transaction History"<<endl;
     cout << "4) Pin Number Setting"<<endl;
     cout << "5) Exit"<<endl;
     int menu = no_menu(5,1);
     if (menu==1)
     { Deposit_menu(eWallet,eWallet_limit);writeup(user,pin,eWallet,eWallet_limit);}
     else if(menu==2)
     { purchase_menu(eWallet,eWallet_limit);writeup(user,pin,eWallet,eWallet_limit);}
     else if(menu==3)
     {transaction_menu(true,eWallet);}
     else if(menu==4)
     {changepin(user,pin,eWallet,eWallet_limit);}
     else if(menu==5)
     {
       exiting(user,pin,eWallet,eWallet_limit);
       t = clock() - t;
        cout<< "You have spend "<<((int)t)/CLOCKS_PER_SEC<<" seconds."<<endl;
        cout<<endl<<"Press any key to go back to main menu.\n";
        cin.clear();cin.ignore();
        cin.get();
         return;}
    }while(true);
 }


//-------------------------------------------------------------------------------------------

//Login
//-----------------------------------------------------------------



//sign up menu
void signup(string &user,string &pin,double &eWallet,double &eWallet_limit)
{
    system("cls");
    int pinno;
    cout << "Sign up menu\n";
    cout << "Key in your account name: ";
    cin.clear();cin.ignore();
    getline(cin,user);
    pinno = rangenerator();
    pin=pin_itos(pinno);
    system ("cls");
    cout << "Your user name : "<<user <<endl;
    cout << "This is your pin number. Please remember it or write it down somewhere.\n";
    cout <<"Pin Number: "<<pin;
    pin=pin_itos(encode(pinno));
    writeup(user,pin,eWallet,eWallet_limit);
    cin.clear();
    cin.get();

}
//find user & secret code in file
bool finder(string user,string pin,double &eWallet,double &eWallet_limit)
{
    ifstream readf("database.txt",ios::in);
    string line1,secrete_code,eWalletf,eWallet_limitf;
    if(!readf)
        {
            cout<< "Error! Cannot open the file for writing.\n";
        }
        else
            {
        getline(readf,line1);
        getline(readf,secrete_code);
        if (user==line1)
        {
            if (pin==secrete_code)
            {
                cout << "Congratulation you have logged in successfully."<<endl;
                getline(readf,eWalletf);
                getline(readf,eWallet_limitf);
                eWallet=stod(eWalletf);
                eWallet_limit=stod(eWallet_limitf);
                return true;
            }
                    else
            {cout << "The pin number is incorrect."<<endl;

            cin.get();
            readf.close();
            return false;
            }
        }
        else
            {cout << "The user name or pin number is incorrect."<<endl;

            cin.get();
            readf.close();
            return false;
            }
    }

}
//write code into the file
void writeup(string &user,string &pin,double &eWallet,double &eWallet_limit)
{
        ofstream writef("database.txt");
        if(!writef)
        {
            cout<< "Error! Cannot open the file for writing.\n";
        }
        else
        {
            writef<<user<<endl;
            writef << pin<<endl;
            writef<<eWallet<<endl;
            writef<<eWallet_limit<<endl;
        }
        writef.close();
}
//Convert int to string for pin
string pin_itos(int pinno)
{
                            stringstream ss;
                            ss <<setfill('0') << setw(6)<< pinno;
                            return ss.str();
}


//random generator for pin number
int rangenerator()
{
    srand(time(0)) ;
    return (rand()*rand())%1000000; //rand() does not generate big number.
}
//encryption into secrete code
int encode(int p)
{
    int result=0,digit=0;
    for(int c=0; c<=5;c++)
    {
        digit=p %10;
        p=p/10;
        if((digit % 2)>=0.5){digit=(digit+7)%10;} //Find Odd number
        else {digit=(digit+11)%10;}//Find even number
        result=(result*10)+digit;
    }
    return result;
}

//decode the pin number.
int decode(int p)
{
    int result=0,digit=0;
    for(int c=0; c<=5;c++)
    {
        digit=p %10;
        p=p/10;
        if((digit % 2)>=0.5){digit=(digit-1)%10;} //Find Odd number
        else {digit=(digit+3)%10;}//Find even number
        result=(result*10)+digit;
    }
    return result;
}

//End Login;
//-------------------------------------------------------------------------------------------
//eWallet
//-------------------------------------------------------------------------------------------
 //Deposit eWallet

    void Deposit_menu(double &eWallet,double &eWallet_limit)
    {
        system("cls");
        showtime();
        cout << "This is the deposit menu.\n ";
        display_eWallet(eWallet);
        cout << "Press 1 for depositing into eWallet.\n";
        cout << "Press 2 for changing the eWallet limit.\n";
        cout << "Press 3 to exit.\n";
        int menu_no = no_menu(3,1);
        if (menu_no==1)
        {
            cout << "Amount you want added to the eWallet: RM";
            double deposit;
            bool success=false;
            do
            {
                cin.clear();
                cin.sync();
                cin>>deposit;
                if (deposit < 0)
                {
                    cout << "Are you want to get back the money? Sorry you can't because the function for getting back money is not added.\n";
                }
                else if (deposit >= 0)
                {success = using_eWallet(deposit,eWallet,eWallet_limit);}
                else
                {
                    cout << "Why you type in character at here.\n";
                }
                if (!success)
                {
                    cout<<"Please try again.\n";
                }
            }
            while(!success); //avoid user entering other than number.
            cin.clear();cin.ignore();
            cin.get();
        }
        else if (menu_no==2)
            {
                cout << "Change eWallet limit.\n";
                cout << "The limit you want to change to RM ";
                double limit; bool fail = true;
                do
                       {
                           cin.clear();cin.sync();
                            cin>>limit;
                            if (limit>0)
                           {
                               if (limit>=100&&limit>=eWallet)
                                {
                                    eWallet_limit=limit;
                                    cout<<"You have successfully change your eWallet limit."<<endl;
                                    fail=false;
                                    continue;

                               }
                               else if(eWallet<=100)
                                {
                                    cout << "The lowest limit is RM100. Any lower than this will not be accepted."<<endl;
                                }
                                else{cout << "The lowest limit is RM"<<eWallet<<". Any lower than this will not be accepted."<<endl;}
                                }
                            else
                           {cout << "Can you try to input positive numbers?\n";}
                           cout<<"Please try again.\n";
                       }while(fail);
                       cin.clear();cin.ignore();
                        cin.get();
                       Deposit_menu(eWallet,eWallet_limit);
                }
    }


//Display eWallet value
    void display_eWallet(double eWallet)
    {
        cout<<fixed<<showpoint<<setprecision(2);
        cout << "Your eWallet have RM "<< eWallet<<endl;
    }




//Change in value
    bool using_eWallet(double intake,double &eWallet,double &eWallet_limit)
    {
        if (eWallet + intake > eWallet_limit)
        {
            cout << "Don't try to excess the limit which is RM"<< eWallet_limit<< " .\n";
            return false;
        }
        else if (eWallet+intake < 0)
        {
            cout << "Insufficient in eWallet. Please deposit for further transaction."<<endl;
            return false;
        }
        else
        {
            eWallet=eWallet + intake;
            if (intake>0)
            cout << "Successfully add the amount you have put in into eWallet. \n";
            else
            cout << "Successfully reduce the amount from your eWallet.\n";
            return true;
        }
    }
//-------------------------------------------------------------------------------------------
//Purchase Menu
    void purchase_menu(double &eWallet,double &eWallet_limit)
    {
        string item; double price,pricesst; int no_item;int menu_no;
        system("cls");
        showtime();
        if ( eWallet<0)
            {cout << "Please deposit more in order to buy more great staff. (Press 1)";
                cout << "Please press \' enter \' to continue.\n";
                cin.clear();cin.ignore();cin.get(); } //check for the eWallet so that the user have some money in the eWallet before buying.
                else if (eWallet==0)
                {cout<<"Please deposit first in order to proceed! (Press 1) \n";
                  cout << "Please press \' enter \' to continue.\n";
                  cin.clear();cin.ignore();cin.get();}
                else
                    {
                        cout << " Here are the HOT item that are in sale right now. \n";    //showing best seller.
                        cout << "-Apple Macbook Pro\n";
                        cout << "-Seagate 250G SSD\n";
                        cout << "-MSI Gaming Laptop\n";
                        cout <<"-Cosiaer Gaming Mouse\n";
                        cout <<"-Dell XPS 15\n";
                        cout << "\nYou can buy almost anything except things that are impossible to buy like time and life. \n\n";
                        cout << "Please don't buy things that are prohibited under the law.\nFollow the rule of law.\n";
                        cout << "You can buy only one thing at a time. \n";
                        cin.clear();cin.ignore();                      //for clearing the cin
                        getline(cin, item);   //get item name from user
                        srand(time(0)) ;        //randomize the prize
                        price= 1000+(rand()%5530);
                        price=price/100;
                        system("cls");
                        cout << "The price of  one "<< item <<" is RM"<<price<<".\n";
                        if(price>25.95)
                        {
                            pricesst=price*1.06;
                            cout << "The price of one item after Sales and Service Tax (SST) is RM"<<pricesst<<endl;
                        }
                        else
                        {
                            pricesst=price;
                            cout << "Sales and Service Tax (SST) is not imposed for this item."<<endl;
                        }
                        cout << "Key in the number of item you wanted: ";
                        no_item=no_menu(100,0); //get no of item
                        double total_price=pricesst*no_item;
                        total_price = (round(total_price * 20))/20; //round off to 5cent.
                        system("cls");
                        cout <<"The item you want to buy is "<<item<<".\n";
                        cout <<"The total price is RM"<<total_price<<".\n";
                        cout <<"Are you sure to buy it?\n"<<"Press 1 to confirm.\n"<<"Press 2 to cancel.\n";
                        menu_no=no_menu(2,1);
                        if(menu_no==1)
                        {

                            if(using_eWallet(-total_price,eWallet,eWallet_limit)==true)
                                {writepurchase(item,price,pricesst,no_item,total_price); //write to the transaction file.
                                }
                        cin.clear();cin.ignore();
                        cin.get();
                        }

                        }
    }

void writepurchase(string item, double price,double pricesst,int no_item,double total_price)
{
    ofstream writepur;
    writepur.open("Transaction.txt",ios::app);
    if(!writepur)
        cout << "Open transaction.txt file error!";
    else
    {
    writepur<<gettime()<<endl;
    writepur<<fixed<<showpoint<<setprecision(2);
    writepur<<item<<endl;
    writepur<<price<<endl;
    writepur<<pricesst<<endl;
    writepur<<no_item<<endl;
    writepur<<total_price<<endl;
    }
    writepur.close();
}

string gettime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%x %I:%M%p.",timeinfo );
    return buffer;
}
//End Purchase Menu
//-------------------------------------------------------------------------------------------
//Transaction Activity Menu
void transaction_menu(bool showall,double eWallet)
{
    if (showall)
    system("cls");
    showtime();

    string time, item, price, pricesst, no_item, total_price;
    ifstream readpur;
    readpur.open("transaction.txt");
    if(!readpur)
    {
        cout << "transaction.txt file not found."<<endl;
        cin.clear();cin.sync();
        cin.get();
        readpur.close();
    }
    else{
            display_eWallet(eWallet);
        cout <<"These are the transaction history."<<endl;

        cout.flags(ios::left);
        if (showall){
        cout<<setw(20)<<"Time transaction"<<setw(30)<<"Item Name"<<setw(20)<<"Price without SST"<<setw(16)<<"Price with SST"<<setw(16)<<"No. of item"<<setw(16)<<"Total Price"<<endl;
        while(!readpur.eof())
        {

            getline(readpur,time);
            getline(readpur,item);
            getline(readpur,price);
            getline(readpur,pricesst);
            getline(readpur,no_item);
            getline(readpur,total_price);
            if(!readpur.eof())
            {
            cout<<setw(20)<<time<<setw(30)<<item<<setw(20)<<"RM"+price<<setw(16)<<"RM"+pricesst<<setw(16)<<no_item<<setw(16)<<"RM"+total_price<<endl;
            }
        }
        }
        else {
            cout<<setw(30)<<"Item Name"<<setw(16)<<"Total Price"<<endl;
        while(!readpur.eof())
        {

            getline(readpur,time);
            getline(readpur,item);
            getline(readpur,price);
            getline(readpur,pricesst);
            getline(readpur,no_item);
            getline(readpur,total_price);
            if(!readpur.eof())
            {
            cout<<setw(30)<<item<<setw(16)<<"RM"+total_price<<endl;
            }
        }
        }
         readpur.close();
    }


}
//End Transaction Activity Menu
//-------------------------------------------------------------------------------------------
//Change Pin No
void changepin(string &user,string &pin,double &eWallet,double &eWallet_limit)
{
    system("cls");
    showtime();
    cout<<"Pin No Setting Menu"<<endl;
    cout << "1. Change Pin No."<<endl;
    cout << "2. Display Pin No."<<endl;
    cout<<"3. Exit"<<endl;
    int menuno=no_menu(3,1);
    if (menuno==1)
        {

        cout << "Please enter your pin number: ";

        string pin1 = pin_itos(encode(no_menu(999999,0)));  //encode and convert pin into string because it is easier to compare with the string get from file.
        if(finder(user,pin1,eWallet,eWallet_limit))
        {
        system("cls");
        cout << "Key in 6 integers: ";
        int pinno,pinno2;
        pinno=encode(no_menu(999999,0));
        system("cls");
        cout << "This is your new pin no: "<<pin_itos(pinno)<<endl;
        cout<<"Please remember this newly generated pin no."<<endl;
        cin.clear();cin.ignore();
        cin.get();
        system("cls");
        cout<<"Please key in the newly generated pin  no.\n";
        for(int i=3;i>=0;i--)
        {
        pinno2=no_menu(999999,0);
        if(pinno==pinno2)
        {
            pin=pin_itos(encode(pinno));
            writeup(user,pin,eWallet,eWallet_limit);
            cout << "You have successfully change your pin no.\n";
            cin.clear();cin.ignore();
            cin.get();
            break;
        }
        else
        {
            cout << "Sorry the pin no you entered is not matched with the pin no. generated."<<endl;
            cout << "You have "<<i<<" times left to try. Please try again."<<endl;
            cin.clear();cin.ignore();
        }
        }
        }
        else {cout << "Your pin no entered is wrong."<<endl;
        cin.clear();cin.ignore();
        cin.get();
        }
        }
    else if(menuno==2)
    {
        system("cls");
        cout<<"Your Current Pin No. is ";
        cout<<pin_itos(decode(stoi(pin)))<<endl;
        cin.clear();cin.ignore();
        cin.get();
    }
}

void exiting(string &user,string &pin, double &eWallet,double &eWallet_limit)
{
    system("cls");
    showtime();
    cout << "Thank you for using me, "<<user<<". \n";
    cout << "Your pin no is "<< decode(stoi(pin))<<". \n";
    display_eWallet(eWallet);
    cout<<"Your eWallet limit is RM"<<eWallet_limit<<".\n";
    cout << "The list of item brought and its prices(include SST)."<<endl;
    transaction_menu(false,eWallet);
    writeup(user,pin,eWallet,eWallet_limit);
}

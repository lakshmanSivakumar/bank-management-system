//                   BANK MANAGMENT SYSTEM
//                 Done by Lakshman Sivakumar

// HEADER FILES

#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>

// CLASS STARTS HERE

class account
{
char name[50];
int  deposit,withdraw;
char type;
public:
int acno;
void create_account()
{
 cout<<"\nEnter The account Number: ";
 cin>>acno;
 cout<<"\n\nEnter The Name of The account Holder: ";
 gets(name);
 cout<<"\nEnter Type of The account (C/S): ";
 cin>>type;
 cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current): ";
 cin>>deposit;
}

void show_account()
{
 cout<<"\nAccount Number: "<<acno;
 cout<<"\nAccount Holder Name: ";
 puts(name);
 cout<<"\nType of Account: "<<type;
 cout<<"\nBalance amount: "<<deposit;
}

void modify_account()
{
 cout<<"\nAccount No. : "<<acno;
 cout<<"\nModify Account Holder Name: ";
 gets(name);
}
void dep(int x)
{deposit+=x;}

void draw(int x)
{ deposit-=x;}

void report()
{
 cout<<"  "<<acno;
 cout<<setw(25)<<name;
 type=toupper(type);
 cout<<"\t\t\t "<<type;
 cout<<"\t\t\t "<<deposit<<"\n";
}

int  retacno()
{return acno;}

float retdeposit()
{return deposit;}

char rettype()
{return type;}

}; // CLASS ENDS HERE

// GLOBAL DECLARATION FOR STREAM OBJECT AND OBJECT

fstream fp;
account ac;

// FUNCTION TO WRITE IN FILE

void write_account()
{
fp.open("account.dat",ios::out|ios::app);
ac.create_account();
if(((ac.rettype()=='s')||(ac.rettype()=='S'))&&(ac.retdeposit()>=500))
  {
   fp.write((char*)&ac,sizeof(account));
   fp.close();
   cout<<"\n\nACCOUNT CREATED.";
  }
else if(((ac.rettype()=='c')||(ac.rettype()=='C'))&&(ac.retdeposit()>=1000))
  {
   fp.write((char*)&ac,sizeof(account));
   fp.close();
   cout<<"\n\nACCOUNT CREATED.";
  }
else
  {

   cout<<"\n\nAccount is not created, since the initial  amount is not sufficient.\n";
   cout<<"\nPress any key to go back to main menu, to create a new account.";
  }
}

// FUNCTION TO READ SPECIFIC RECORD FROM FILE

void display_sp(int n)
{
clrscr();
cout<<"\n\t\t\t\t BALANCE DETAILS\n";
int flag=0;
fp.open("account.dat",ios::in);
while(fp.read((char*)&ac,sizeof(account)))
   {
 if(ac.retacno()==n)
   {
    ac.show_account();
    flag=1;
   }
   }
fp.close();
if(flag==0)
cout<<"\n\nACCOUNT NUMBER DOES NOT EXIST.";
getch();
}

// FUNCTION TO MODIFY RECORD OF FILE

void modify_account()
{
int no,found2;
clrscr();
cout<<"\n\n"<<setw(53)<<"MODIFY ACCOUNT HOLDER NAME";
cout<<"\n\nEnter the account no. of your account: ";
cin>>no;
fp.open("account.dat",ios::in|ios::out);
while(fp.read((char*)&ac,sizeof(account)))
   {
    if(ac.retacno()==no)
      {
     ac.show_account();
     cout<<"\n\n\t\t\tENTER THE NEW DETAILS OF       ACCOUNT"<<endl;
     ac.modify_account();
 int pos=-1*sizeof(ac);
     fp.seekp(pos,ios::cur);
 fp.write((char*)&ac,sizeof(account));
   cout<<"\n\nRECORD UPDATED.";

}

   }
fp.close();
if(ac.retacno()!=no)
cout<<"\n\nRECORD NOT FOUND.";
getch();
}

// FUNCTION TO DELETE RECORD OF FILE

void delete_account()
{
int no;
clrscr();
cout<<"\n\n\n\t\t\t\t DELETE RECORD";
cout<<"\n\nEnter the account no. of the customer you want to delete: ";
cin>>no;
if(ac.retacno()==no)
  {
   fp.open("account.dat",ios::in|ios::out);
   fstream fp2;
   fp2.open("Temp.dat",ios::out);
   fp.seekg(0,ios::beg);
   while(fp.read((char*)&ac,sizeof(account)))
    {
     if(ac.retacno()!=no)
       {
        fp2.write((char*)&ac,sizeof(account));
       }
    }
   fp2.close();
   fp.close();
   remove("account.dat");
   rename("Temp.dat","account.dat");
   cout<<"\nRECORD DELETED.";
  }
else
cout<<"\nRECORD NOT FOUND.";
getch();
}

// FUNCTION TO DISPLAY ALL ACCOUNTS DEPOSIT LIST

void display_all()
{
clrscr();
fp.open("account.dat",ios::in);
if(!fp)
 {
  cout<<"\n\nTHE PREVIOUS ACCOUNT IS NOT ARE CREATED\n\n\nPLEASE GO TO MAIN MENU TO CREATE A NEW ACCOUNT";
   getch();
   return;
 }
cout<<"\n\n\t\t\t\tACCOUNT HOLDER LIST\n\n";
cout<<"================================================================================";
cout<<" A/c no.\t\tNAME\t\t\tType\t\t\tBalance\n";
cout<<"================================================================================\n";

while(fp.read((char*)&ac,sizeof(account)))
   {
 ac.report();
   }
 fp.close();
}

// FUNCTION TO DEPOSIT AND WITHDRAW AMOUNTS

void deposit_withdraw(int option)
{
int no,found=0,amt;
clrscr();
cout<<"\n\n"<<setw(56)<<"CURRENT DETAIL OF ACCOUNT HOLDER";
cout<<"\n\nEnter the account Number: ";
cin>>no;
fp.open("account.dat",ios::in|ios::out);
while(fp.read((char*)&ac,sizeof(account)) && found==0)
   {
    if(ac.retacno()==no)
   {
  ac.show_account();
     if(option==1)
    {
     cout<<"\n\n"<<setw(50)<<"TO DEPOSITE AMOUNT ";
     cout<<"\n\nEnter the amount to be deposited(min. 500): ";
     cin>>amt;
     if(amt>=500)
     {ac.dep(amt);
     found=2;}
     else
     {
     cout<<"\n\nCANNOT DEPOSIT.";
     cout<<"\n\nPLEASE GO BACK TO MAIN MENU TO REDEPOSIT AMOUNT.";
     delay(200);
     found=3;
     }
    }
     if(option==2)
       {
      cout<<"\n\n"<<setw(50)<<"TO WITHDRAW AMOUNT";
      cout<<"\n\nEnter the amount to be withdraw(min. 1000): ";
      cin>>amt;
      if(amt>=1000)
      {
        int bal=ac.retdeposit()-amt;
        if(bal>0)
        {
         ac.draw(amt);
         found=2;
        }
        else
        {
         cout<<"\nINSUFFICENT BALANCE TO WITHDRAW.";
         found=3;
        }
      }
      else
        {
         cout<<"\nMINIMUN 1000 SHOULD BE WITHDRAWN.";
         found=3;
        }
       }
if(found==2)
{
int pos=-1*sizeof(ac);
fp.seekp(pos,ios::cur);
fp.write((char*)&ac,sizeof(account));
cout<<"\nRECORD UPDATED.";
found=1;
}
if(found==3)
{
cout<<"\n\nRECORD CANNOT UPDATE.";
found=1;
}
      }
   }
fp.close();
if(found==0)
cout<<"\n\nRECORD NOT FOUND.";

getch();
}

// INTRODUCTION FUNCTION

void intro()
{
int i,n,x,j,y,z,m;
n=7,x=1,j=30;
clrscr();
while(x<3)
{
for(i=0;i<n;i++)
{
gotoxy(j,i+9);
delay(25);
cout<<".";
endl;
}
if(i==7)
j+=20;
x+=1;
}
y=1,z=21,m=8;
while(y<3)
{
for(i=0;i<z;i++)
{
gotoxy(i+30,m);
delay(25);
cout<<".";
}
if(i==21)
m+=8;
y+=1;
}
gotoxy(38,10);
cout<<"BANK";
gotoxy(35,12);
cout<<"MANAGEMENT";
gotoxy(37,14);
cout<<"SYSTEM";
gotoxy(37,19);
delay(500);
cout<<"WELCOME";
gotoxy(25,21);
delay(400);
cout<<"PRESS ANY KEY TO GO TO MAIN MENU";
getch();

}

// THE MAIN FUNCTION OF PROGRAM

void main()
{
char ch;
intro();
do
  {
   clrscr();
   cout<<"\n\n\n\t MAIN MENU";
   cout<<"\n\n\t 1. NEW ACCOUNT";
   cout<<"\n\n\t 2. DEPOSIT AMOUNT";
   cout<<"\n\n\t 3. WITHDRAW AMOUNT";
   cout<<"\n\n\t 4. BALANCE ENQUIRY";
   cout<<"\n\n\t 5. ALL ACCOUNT HOLDER LIST";
   cout<<"\n\n\t 6. CLOSE AN ACCOUNT";
   cout<<"\n\n\t 7. MODIFY ACCOUNT HOLDER NAME";
   cout<<"\n\n\t 8. EXIT";
   cout<<"\n\n\t Select Your Option (1-8): ";
   ch=getche();
   switch(ch)
     {
     case '1': clrscr();
           write_account();
           getch();
           break;
   case '2': clrscr();
           deposit_withdraw(1);
           break;
   case '3': clrscr();
           deposit_withdraw(2);
           getch();
           break;
   case '4': int num;
           clrscr();
           cout<<"\n\nEnter the account number: ";
           cin>>num;
           display_sp(num);
           break;
   case '5': clrscr();
           display_all();
           getch();
           break;
   case '6': delete_account();
           break;
   case '7': clrscr();
           modify_account();
           getch();
           break;
   case '8': clrscr();
    gotoxy(31,13);
    cout<<"T H A N K Y O U ! !";
    delay(500);
    exit(0);
   default : cout<<"\a";
     }
   }while(ch!='8');
}

//    			     END OF PROJECT

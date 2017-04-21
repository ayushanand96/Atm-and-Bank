#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
struct account
{
char am[30];
long int an;
long int ab;
};
void input(account &a)
{
cout<<"\n\n\n\t\tEnter account holder's name:\t";
gets(a.am);
cout<<"\n\t\tEnter account no.:\t";
cin>>a.an;
cout<<"\n\t\tEnter balance:\t";
cin>>a.ab;
}
void display (account a)
{
cout<<"\n\n\n\n\n\t\tBalance ammount:\t";
cout<<a.ab;
}
void deposite(account &a)
{
cout<<"\n\n\n\t\tEnter ammount:\t";
long int b;
cin>>b;
a.ab+=b;
cout<<"\n\n\t\tTotal money in your account:\t"<<a.ab;
}
void withdraw(account &a)
{
cout<<"\n\n\t\tEnter ammount:\t";
long int c;
cin>>c;
if (a.ab-c>=500)
{
a.ab-=c;
cout<<"\n\n\t\tTotal money in your account:\t"<<a.ab;
}
else
{
clrscr();
cout<<"\n\n\n\n\n\n\n\t\tYOU CANNOT WITHDRAW THIS MICH MONEY FROM YOUR ACCOUNT !!!";
}
}
void main()
{
clrscr();
account a[50];
int n;
cout<<"\n\n\n\n\t\tEnter no. of acoounts:\t";
cin>>n;
for(int i=0;i<n;i++)
{clrscr();
cout<<"\n\t\t\tEnter details of account holder "<<i+1<<":\t";
input(a[i]);
}
char q;
do
{
clrscr();
account z;
cout<<"\n\n\n\n\n\t\tEnter account no.:\t";
cin>>z.an;
char b;
do
{
clrscr();
for(i=0;i<n;i++)
if(z.an==a[i].an)
cout<<"\n\n\t\t\tWELCOME. . . ."<<a[i].am;
int p;
cout<<"\n\n\n\t\tEnter choice:\n\n\n\t\t1.Balance ammount!!\n\n\t\t2.Deposite money!!\n\n\t\t3.Withdraw money!!\n\n\t\t";
cin>>p;
clrscr();
switch(p)
{
case 1: {
	for(i=0;i<n;i++)
	if(z.an==a[i].an)
	display(a[i]);
	break;
	}
case 2: {
	for(i=0;i<n;i++)
	if(z.an==a[i].an)
	deposite(a[i]);
	break;
	}
case 3: {
	for(i=0;i<n;i++)
	if(z.an==a[i].an)
	withdraw(a[i]);
	break;
	}
default:cout<<"\n\n\n\t\tWrong Entry";
}
cout<<"\n\n\tGo back to main menu(Y/N):\t";
cin>>b;
}while(b=='y' || b=='Y');
clrscr();
cout<<"\n\n\n\n\n\n\n\n\n\n\t\tPress Y to enter account no.\n\t\telse press any other key to exit\n\t\t:\t";
cin>>q;
}while(q=='y'||q=='Y');
exit(0);

getch();
}
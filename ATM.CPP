#include<stdlib.h>
#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>
class account
{
char am[30];  //account name
char aad[200];    //account address
char at[30];      //account type
long int an;      //account number
long int ab;      //account balance
int ap;          //atm pin
public:
account()      //constructor to input default values
	{
	strcpy(am,"a");
	strcpy(aad,"a");
	strcpy(at,"a");
	an=0;
	ab=ap=an;
	}
void newbal(long a)          //change balance ammount
	{
	ab=a;
	}
long accountbal()            // return account balance
	{
	return ab;
	}
void updatepin(int p)        //update atm pin
	{
	ap=p;
	}
account(account &a)          //copy constructor to copy onr obj to another
	{
	an=a.an;
	ab=a.ab;
	ap=a.ap;
	strcpy(am,a.am);
	strcpy(aad,a.aad);
	strcpy(at,a.at);
	}
long accountno()            //return account number
	{
	return an;
	}
char* accounttype()         //return account number
	{
	return at;
	}
char* accountname()         //return account holders name
	{
	return am;
	}
int accountpin()            //return pin
	{
	return ap;
	}
void inup()                 //input for updating details
	{
	cout<<"\n\n\n\t\tEnter account holder\'s name:\t";
	gets(am);
	cout<<"\n\t\tEnter your address:\t";
	gets(aad);
	}
void input()                //input for new account
	{
	cout<<"\n\n\n\t\tEnter account holder\'s name:\t";
	gets(am);
	cout<<"\n\t\tEnter your address:\t";
	gets(aad);
	cout<<"\n\t\tEnter account type (CURRENT / SAVINGS):\t";
	gets(at);
	cout<<"\n\t\tEnter account no.:\t";
	cin>>an;
	cout<<"\n\t\tEnter balance:\t";
	cin>>ab;
	clrscr();
	int t1,t2;
	cout<<"\n\n\n\t\tNow enter a new (4 DIGIT) pin:\t";
	cin>>t1;
	cout<<"\n\t\tConfirm pin:\t";
	cin>>t2;
	if(t1==t2)
		ap=t1;
	else                     //auto generation of pin in case
		{                //of wrong entries
		randomize();
		ap=random(9999);
		cout<<"\n\n\t\tPins do not match\n\t\tYour pin is:  "<<ap;
		cout<<"\n\n\t\t\t(visible for 7 sec)";
		delay(7000);
		}
	}
void dispup()              //display updated entries
	{
	cout<<"\n\n\t\tAccount holder\'s name:\t"<<am;
	cout<<"\n\t\tAccount holder\'s address:\n\t\t\t\t"<<aad;
	cout<<"\n\t\tAccount type:\t"<<at;
	cout<<"\n\t\tAccount no.:\t"<<an;
	}
void display ()            //display all details
	{
	cout<<"\n\n\t\tAccount holder\'s name:\t"<<am;
	cout<<"\n\t\tAccount holder\'s address:\n\t\t\t\t"<<aad;
	cout<<"\n\n\t\tAccount type:\t"<<at;
	cout<<"\n\t\tAccount no.:\t"<<an;
	cout<<"\n\t\tBalance ammount:\t"<<ab<<endl;
	}
};
void sort()        //sorting entries in file accourding to account no.
{
long int a=0,x[200],b=0;
account s;
ifstream fin("bank.dat",ios::binary);
while(fin.read((char*)&s,sizeof(s)))
	{
	x[a]=s.accountno();
	a++;
	}
fin.close();
for(int i=0;i<a;i++)
	{
	for(int j=i;j<a;j++)
	if(x[i]>x[j])
		{
		int c=x[j];
		x[j]=x[i];
		x[i]=c;
		}
	}
ofstream fout("temp.dat",ios::binary);
for(i=0;i<a;i++)
	{
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
		{
		if(s.accountno()==x[b])
			{
			fout.write((char*)&s,sizeof(s));
			b++;
			}
		}
	fin.close();
	}
fout.close();
remove("bank.dat");
rename("temp.dat","bank.dat");
}
void add()            //adding new account
{
int n;
clrscr();
cout<<"\n\n\n\n\n\t\t\tEnter no. of account details\n\t\t\tyou want to add( 0 if none):\t";
cin>>n;
int x[200];
ofstream fout("bank.dat",ios::binary|ios::app);
for(int i=0;i<n;i++)
	{
	account a;
	int o=0;
	for(int y=0;o==0;y++)
		{
		clrscr();
		account x;
		int ac=0;
		cout<<"\n\n\t\tEnter details of account "<<i+1<<" :\t";
		ifstream fn("bank.dat",ios::binary);
		while(fn.read((char*)&x,sizeof(x)))
			{
			ac++;
			}
		fn.close();
		if(ac!=0)
		{
		ifstream fin("bank.dat",ios::binary);
		a.input();
		while(fin.read((char*)&x,sizeof(x)))
			{
			if(a.accountno()==x.accountno())
				{
				clrscr();
				cout<<"\n\n\n\n\n\n\n\t\t\t\tAccount with this account no. Already exist\n\t\t\t\tTry Another Account No.";
				delay(1500);
				o=0;
				break;
				}
			else
				o=1;
			}
		fin.close();
		}
		else
			{
			a.input();
			o=1;
			}
		}
	fout.write((char*)&a,sizeof(a));
	}
fout.close();
clrscr();
if(n==1)
cout<<"\n\n\n\t\tAccount Added";
else if(n>1)
cout<<"\n\n\n\t\tAccounts Added";
sort();
}
void delent()          //deleting accounts
{
clrscr();
int v=0;
cout<<"\n\n\n\n\n\t\tHow many accounts to be deleted: ";
cin>>v;
if(v==1)
{
clrscr();
int n;
cout<<"\n\n\n\n\n\n\t\tEnter account no. of the account you want to delete:\n\t\t\t";
cin>>n;
ifstream fin("bank.dat",ios::binary);
ofstream fout("temp.dat",ios::binary);
account a;
int m=0;
while (fin.read((char*)&a,sizeof(a)))
{
if (a.accountno()!=n)
	{
	fout.write((char*)&a,sizeof(a));
	}
else
	m=1;
}
fin.close();
fout.close();
remove("bank.dat");
rename("temp.dat","bank.dat");
if(!m)
	{
	clrscr();
	cout<<"\n\n\n\n\n\t\t\tAccount does\'t exist!!\n\n\t\t";
	}
else
	{
	clrscr();
	cout<<"\n\n\n\n\n\t\t\t\tAccount Removed\n\n\t\t";
	}
}
else if(v>1)
{
int n[100],b=0,m=0;
cout<<"\n\n\n\n\n\n";
for(int i=0;i<v;i++)
{
clrscr();
cout<<"\n\n\t\tEnter account no. of account "<<i+1<<" to be deleted:\n\t\t\t";
cin>>n[i];
ifstream fin("bank.dat",ios::binary);
ofstream fout("temp.dat",ios::binary);
account a;
while (fin.read((char*)&a,sizeof(a)))
{
if (a.accountno()!=n[i])
	{
	fout.write((char*)&a,sizeof(a));
	}
else
	{
	m=1;
	b++;
	}
}
if(!m)
	{
	clrscr();
	cout<<"\n\n\n\n\n\t\t\tAccount does\'t exist!!\n\n\t\t";
	delay(500);
	}
fin.close();
fout.close();
remove("bank.dat");
rename("temp.dat","bank.dat");
}
if(b!=0)
	{
	clrscr();
	cout<<"\n\n\n\n\n\t\t\t\tAccounts Removed\n\n\t\t";
	}
else
	{
	clrscr();
	cout<<"\n\n\n\n\n\n\t\t\t\tNo Accounts Deleted";
	}
}
}
void searchda()         //see details of all accounts
{
clrscr();
int x=0;
account a;
ifstream fn("bank.dat",ios::binary);
while(fn.read((char*)&a,sizeof(a)))
	{
	x++;
	}
fn.close();
if (x==0)
	{
	cout<<"\n\n\n\n\n\t\tNo Accouts in the Database!!!\n";
	}
else
	{
	char sd;
	cout<<"\n\n\n\n\t\tWhat way you want to see through accounts:\n\n\n\t\t1. Change automatically in 5 sec\n\t\t2. Change automatically in 10 sec\n\t\t3. Change Manually\n\n\t\t";
	sd=getch();
	if(sd=='1')    //details change automatically in 5 sec
		{
		int i=1;
		clrscr();
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\tThere Are "<<x<<" accounts:\t";
		delay(2000);
		ifstream fin("bank.dat",ios::binary);
		while(fin.read((char*)&a,sizeof(a)))
			{
			clrscr();
			cout<<"\n\n\n";
			cout<<"\n\n\t\t1 entry stays for 5 sec.:\n\n\t\t";
			if(x==1)
				{
				cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
				a.display();
				cout<<"\n\n\t\t\t\tThe only Entry";
				}
			else if(i==x)
				{
				delay(100);
				cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
				a.display();
				cout<<"\n\n\t\t\t\tLast Entry!";
				i++;
				}
			else
				{
				delay(100);
				cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
				a.display();
				i++;
				delay(5000);
				}
			}
		fin.close();
		}
	else if(sd=='2')      //details change automatically in 10 sec
		{
		int i=1;
		clrscr();
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\tThere Are "<<x<<" accounts:\t";
		delay(2000);
		ifstream fin("bank.dat",ios::binary);
		while(fin.read((char*)&a,sizeof(a)))
				{
				clrscr();
				cout<<"\n\n\n";
				cout<<"\n\n\t\t1 entry stays for 10 sec.:\n\n\t\t";
				if(x==1)
					{
					cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
					a.display();
					cout<<"\n\n\t\t\t\tThe only Entry!!";
					}
				else if(i==x)
					{
					delay(100);
					cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
					a.display();
					cout<<"\n\n\t\t\t\tLast Entry!";
					i++;
					}
				else
					{
					delay(100);
					cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
					a.display();
					i++;
					delay(10000);
					}
				}
		fin.close();
		}
	else if(sd=='3')        //details change manually
		{
		int i=1;
		clrscr();
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\tThere Are "<<x<<" accounts:\t";
		char a1;
		cout<<"\n\n\n\t\tEnter (1) to continue:\t";
		a1=getch();
		if(a1=='1')
			{
			ifstream fin("bank.dat",ios::binary);
			while(fin.read((char*)&a,sizeof(a)))
				{
				char a2='n';
				clrscr();
				cout<<"\n\n\n";
				if(x==1)
					{
					cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
					a.display();
					cout<<"\n\n\t\t\t\tThe only Entry";
					}
				else if(i==x)
					{
					delay(100);
					cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
					a.display();
					cout<<"\n\n\t\t\t\tLast Entry!";
					i++;
					}
				else
					{
					delay(100);
					if(a2=='n'||a2=='N')
						{
						cout<<"\n\t\t\t\tDetails of account no.:\t"<<a.accountno()<<"\n";
						a.display();
						i++;
						}
					else
						{
						clrscr();
						cout<<"\n\n\n\n\n\n\t\t\t\t\tWrong Entry!!!";
						break;
						}
					cout<<"\n\n\n\t\tEnter (N) for next:\t";
					a2=getch();
					}
				}
			fin.close();
			}
		else
			{
			clrscr();
			cout<<"\n\n\n\n\n\n\t\tWrong Entry!!!";
			}
		}
	else
		{
		clrscr();
		cout<<"\n\n\n\n\n\n\t\tWrong Entry!!!";
		}
	}
}
int search(account &b)       //search for any account
{
clrscr();
int t,x=1;
cout<<"\n\n\n\n\t\tEnter account no.:\t";
cin>>t;
account a;
ifstream fin("bank.dat",ios::binary|ios::in);
while(fin.read((char*)&a,sizeof(a)))
	{
	if(a.accountno()==t)
		{
		int t1;
		cout<<"\n\t\tEnter Pin:\t";
		cin>>t1;
		if(t1==a.accountpin())
			{
			clrscr();
			b=a;
			x=0;
			break;
			}
		else
			x=2;
		break;
		}
	else
		{
		x=1;
		}
	}
fin.close();
return x;
}

void deposit(account &a)       //deposit money in account
	{
	cout<<"\n\n\n\t\tEnter ammount:\t";
	long int b;
	cin>>b;
	long c1=a.accountbal()+b;
	a.newbal(c1);
	cout<<"\n\n\t\tTotal money in your account:\t"<<c1;
	ifstream fin("bank.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	account c;
	while(fin.read((char*)&c,sizeof(c)))
		{
		if(a.accountno()!=c.accountno())
		fout.write((char*)&c,sizeof(c));
		else
		fout.write((char*)&a,sizeof(a));
		}
	fin.close();
	fout.close();
	remove("bank.dat");
	rename("temp.dat","bank.dat");
	}
void withdraw(account &a)            //withdraw money from account
	{
	cout<<"\n\n\t\tEnter ammount:\t";
	long int c1;
	cin>>c1;
	if (a.accountbal()-c1>=500)
		{
		long d=a.accountbal()-c1;
		a.newbal(d);
		cout<<"\n\n\t\tTotal money in your account:\t"<<d;
		}
	else
		{
		clrscr();
		cout<<"\n\n\n\n\n\n\n\t\tINSUFFICIENT BALANCE IN YOUR ACCOUNT !!!";
		}
	ifstream fin("bank.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	account c;
	while(fin.read((char*)&c,sizeof(c)))
		{
		if(a.accountno()!=c.accountno())
		fout.write((char*)&c,sizeof(c));
		else
		fout.write((char*)&a,sizeof(a));
		}
	fin.close();
	fout.close();
	remove("bank.dat");
	rename("temp.dat","bank.dat");
	}
void update(account &a)           //update account details
{
clrscr();
account s,s1;
s=a;
cout<<"\n\n\n\t\tEnter new details:\t";
s.inup();
ifstream fin("bank.dat",ios::binary);
ofstream fout("temp.dat",ios::binary);
while (fin.read((char*)&s1,sizeof(s1)))
{
if (s1.accountno()!=a.accountno())
fout.write((char*)&s1,sizeof(s1));
else
fout.write((char*)&s,sizeof(s));
}
fin.close();
fout.close();
remove("bank.dat");
rename("temp.dat","bank.dat");
clrscr();
cout<<"\n\n\t\tNew Details are as follows:\n";
s.dispup();
a=s;
}
void updpin(account &a)           //change pin
{
clrscr();
account s,s1;
s=a;
int x,y,z;
cout<<"\n\n\n\t\tEnter old pin:\t";
cin>>x;
cout<<"\n\t\tEnter new pin:\t";
cin>>y;
cout<<"\n\t\tConfirm new pin:\t";
cin>>z;
if(x==a.accountpin()&&y==z)
    {
	s.updatepin(y);
	ifstream fin("bank.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	while (fin.read((char*)&s1,sizeof(s1)))
		{
		if (s1.accountno()!=a.accountno())
		fout.write((char*)&s1,sizeof(s1));
		else
		fout.write((char*)&s,sizeof(s));
		}
	fin.close();
	fout.close();
	remove("bank.dat");
	rename("temp.dat","bank.dat");
	clrscr();
	cout<<"\n\n\n\n\n\n\t\t\tPIN UPDATED!!!";
    }
else
    {
    clrscr();
    cout<<"\n\n\n\n\n\n\n\t\t\tWrong Entries!!";
    }
a=s;
}
void main()
{
clrscr();
char ch;
do
{
clrscr();
cout<<"\n\t\t\t\tBank of FAS\n\n\n\n\t\tSelect Task:\t\n\t\tA. Add Accouts\n\t\tB. Delete Accounts\n\t\tC. Details of all Accounts\n\t\tD. Deposit/Withdraw/Update\n\t\t(wrong entry terminates program!)\n\n\t\tOr press (E) to exit\t\t";
char q;
q=getch();
switch (q)                      //bank use
{
case 'A': {
	  add();
	  cout<<"\n\n\t\tGo to main menu (M) or press (E) to exit\t\t";
	  ch=getch();
	  break;
	  }
case 'a': {
	  add();
	  cout<<"\n\n\t\tGo to main menu (M) or press (E) to exit\t\t";
	  ch=getch();
	  break;
	  }
case 'B': {
	  delent();
	  cout<<"\n\n\t\tGo to main menu (M) or press (E) to exit\t\t";
	  ch=getch();
	  break;
	  }
case 'b': {
	  delent();
	  cout<<"\n\n\t\tGo to main menu (M) or press (E) to exit\t\t";
	  ch=getch();
	  break;
	  }
case 'C': {
	  searchda();
	  cout<<"\n\n\t\tGo to main menu (M) or press (E) to exit\t\t";
	  ch=getch();
	  break;
	  }
case 'c': {
	  searchda();
	  cout<<"\n\n\t\tGo to main menu (M) or press (E) to exit\t\t";
	  ch=getch();
	  break;
	  }
case 'd': {
	  account a;
	  ch='y';
	  int x=search(a);
	  if(x==1)
		{
		clrscr();
		cout<<"\n\n\n\n\t\t\t\tAccount Does\'t Exist!\n\n\t\tPress (M) for main menu or (E) to exit:\t";
		ch=getch();
		}
	  else if(x==2)
		{
		clrscr();
		cout<<"\n\n\n\n\t\t\t\tWront pin Entered!\n\n\t\tPress (M) for main menu or (E) to exit:\t";
		ch=getch();
		}
	  else
	  {
	  char z='y';
	  while(z=='y'||z=='Y')
	  {
	  clrscr();
	  cout<<"\n\n\t\t\t\tWelcome "<<a.accountname();
	  cout<<"\n\n\n\n\t\tSelect Task:\n\t\t1. Balance Enquiry\n\t\t2. Deposit\n\t\t3. Withdrawal\n\t\t4. Update details\n\t\t5. Change pin\n\t\t6. Get account details\n\t\t";
	  char i;
	  i=getch();
	  switch(i)              //user screen or atm
		{
			case '1': {
				clrscr();
				cout<<"\n\n\n\t\tBalance in your account is:\t"<<a.accountbal();
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '2': {
				clrscr();
				deposit(a);
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '3': {
				clrscr();
				withdraw(a);
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '4': {
				clrscr();
				update(a);
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '5': {
				clrscr();
				updpin(a);
				cout<<"\n\n\t\tGo Back(Y/N):\t";
				z=getch();
				break;
				}
			case '6': {
				clrscr();
				a.display();
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			default:{
				clrscr();
				cout<<"\n\n\n\t\tWrong entry!!";
				z='n';
				}
		}
	  }
	  cout<<"\n\n\t\tPress (M) for main menu or (E) to exit:\t";
	  ch=getch();
	  }
	  break;
	  }
case 'D': {
	  account a;
	  ch='y';
	  int x=search(a);
	  if(x==1)
		{
		clrscr();
		cout<<"\n\n\n\n\t\t\t\tAccount Does\'t Exist!\n\n\t\tPress (M) for main menu or (E) to exit:\t";
		ch=getch();
		}
	  else if(x==2)
		{
		clrscr();
		cout<<"\n\n\n\n\t\t\t\tWront pin Entered!\n\n\t\tPress (M) for main menu or (E) to exit:\t";
		ch=getch();
		}
	  else
	  {
	  char z='y';
	  while(z=='y'||z=='Y')
	  {
	  clrscr();
	  cout<<"\n\n\t\t\t\tWelcome "<<a.accountname();
	  cout<<"\n\n\n\n\t\tSelect Task:\n\t\t1. Balance Enquiry\n\t\t2. Deposit\n\t\t3. Withdrawal\n\t\t4. Update details\n\t\t5. Change pin\n\t\t6. Get account details\n\t\tWrong Entry takes you to main page!!";
	  char i;
	  i=getch();
	  switch(i)                //user screen or atm
		{
			case '1': {
				clrscr();
				cout<<"\n\n\n\t\tBalance in your account is:\t"<<a.accountbal();
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '2': {
				clrscr();
				deposit(a);
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '3': {
				clrscr();
				withdraw(a);
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '4': {
				clrscr();
				update(a);
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			case '5': {
				clrscr();
				updpin(a);
				cout<<"\n\n\t\tGo back(Y/N):\t";
				z=getch();
				break;
				}
			case '6': {
				clrscr();
				a.display();
				cout<<"\n\n\tWant another transaction (Y/N):\t";
				z=getch();
				break;
				}
			default:{
				clrscr();
				cout<<"\n\n\n\n\t\t\t\tWrong Entry!!";
				z='n';
				}
		}
	  }

	  cout<<"\n\n\t\tPress (M) for main menu or (E) to exit:\t";
	  ch=getch();
	  }
	  break;
	  }
default: ch='e';
}
}while(ch=='m'||ch=='M');
exit(0);
getch();
}
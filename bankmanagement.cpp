#include<iostream>	// input and output stream classes,
#include<fstream>	//working with files
#include<cctype>	// working with characters and character classification[toupper() etc.]
#include<iomanip>	//controlling the format of numbers, text alignment, and other formatting options
using namespace std;



class account		//class
{
	//class data members
	int acno;		
	char name[50];
	int deposit;
	char type;
public:
	//class methods

	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;	//const member function of the account class. function won't change any of the member variables of that instance.
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};

void account::create_account()
{
	system("CLS");	//to clear the console screen or terminal
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>acno;
	cout<<"\n\n\t\t\tEnter the Name of the Account holder : ";
	cin.ignore();	//input buffer is clean and ready for fresh input
	cin.getline(name,50);
	cout<<"\n\t\t\tEnter Type of the Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\t\t\tAccount Created..";
}

void account::show_account() const
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tType of Account : "<<type;
	cout<<"\n\t\t\tBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify Balance amount : ";
	cin>>deposit;
}

//deposit more money in account
void account::dep(int x)	
{
	deposit+=x;
}
//Withdraw money from account
void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<"   "<<deposit<<endl;
}
/*
setw(10): This is a part of the <iomanip> library and is used to set the width of the field for the output. 
In this case, it sets the width to 10 characters.
This means that the following data will be displayed in a field that is 10 characters wide.
If the data is shorter than 10 characters, it will be right-aligned within the field.
*/
// to get account no.
int account::retacno() const
{
	return acno;
}
//to get deposit value
int account::retdeposit() const
{
	return deposit;
}
//to get type of account
char account::rettype() const
{
	return type;
}



void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
	char ch;
	int num;	//accnt.no
	do
	{
	system("CLS");
	cout<<"\n\n\t\t\t\t======================\n";
	cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t======================\n";

		cout<<"\t\t\t\t    ::MAIN MENU::\n";
		cout<<"\n\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout<<"\n\t\t\t\t8. EXIT";
		cout<<"\n\n\t\t\t\tSelect Your Option (1-8): ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
		 	system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
		 	system("CLS");
			cout<<"\n\n\t\t\tBrought To You By code-projects.org";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}


void write_account()
{
	account ac;
	ofstream outFile;	//output file stream named outFile. It's used to open and write data to the "account.dat" file.
	outFile.open("account.dat",ios::binary|ios::app);	//open the "account.dat" file in binary mode (ios::binary) and with the append mode (ios::app)
	ac.create_account();
	//stream_name.write(reinterpret_cast<char *>(&data), sizeof(data));
	//stream_name.open("filename", mode);
	//reinterpret_cast<char*>(&ac)this expression treats the binary memory layout of the ac object as a sequence of characters (bytes)
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));	//The reinterpret_cast is used to reinterpret the memory occupied by the ac object as a char* pointer, allowing you to write its raw memory representation to the file. sizeof(account) specifies the number of bytes to write, which is typically the size of the account class object.
	outFile.close();
}

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)	 //if infile not opens[account.dat] or permission issues
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
	//reads data from the file into the ac object. 
	//The reinterpret_cast is used to reinterpret the binary data read from the file as an account object.
    //sizeof()-> size of the data to read
		while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)	//account no equal to the accnt no. passed
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}

//size_of(account)->gives size in bytes of account object

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account)); //casting unsigned size of account into signed value and then multiplying it by -1 to make it negative offset
			//seekp()->move the put (output) file pointer within the file.
			//it moves the file pointer backward by sizeof(account) bytes from its current position.
			// This is done to position the file pointer at the start of the record that needs to be updated.
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));	//writes the updated binary representation of the ac object back into the file.
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}



void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	//ifstreamObject.seekg(offset, direction);
	inFile.seekg(0,ios::beg);	//This line positions the get (input) file pointer at the beginning of the "account.dat" file.
	// It ensures that data will be read from the start of the file.
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) //read the data from obj as char bytes
	{
		if(ac.retacno()!=n)	//this means this account must not be deleted
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));	//write account.dat data to outfile temp.dat
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nRecord Deleted ..";
}


void display_all()
{
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.    NAME        Type       Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);	//open account.dat in binary mode and allow both input and output
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\t DEPOSIT AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\t\t\t WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;	//check for negative balance
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}


#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
//functions for varios operations
void menu();
void Add_Number();
void Display_Records();
void search_Records();
void delete_Record();
//class declaration
class PhoneBook
{
	private:
		int sr_no;
		char name[15];
		char mobile_no[10];
		char email_id[20];
		char group_id[10];
	public:
		int get_serial_no()
		{
			return sr_no;	
		}
		void get_details();
		void show_details();
}m;


//member funtion defination
void PhoneBook::get_details()
{
	cout << "\n-------Create New PhoneBook Record---------\n";
	cout << "\n Enter Serial Number: "; cin >> sr_no;
	cout << "\n Enter the Contact Name:";
	cin >> name;
	cout << "\n Enter the Contact Number: ";
	cin >> mobile_no;
	cout << "\n Enter the Contact Email ID: ";
	cin >> email_id;
	cout << "\n Enter the Contact Group ID: ";
	cin >> group_id;

}

//member funtion defination
void PhoneBook::show_details()
{
	
	cout << sr_no << "\t" << name << "\t" << mobile_no << "\t" << email_id << "\t" << group_id << endl;
}

//create new record in phonebook
void Add_Number()
{
	//PhoneBook m;
	char op;
	ofstream fout;
	fout.open("Phonebook.dat",ios::out|ios::binary|ios::app);
	do
	{
		m.get_details();
		fout.write((char *)&m,sizeof(m));
		cout << "\n One Record Added.\n";
		cout << "\n Add More Contacts [y/n]: ";
		cin >> op;
	} while(op == 'y' || op == 'Y');
	fout.close();
}

// Display the records in the phonebook
void Display_Records()
{
	//PhoneBook m;
	ifstream fin;
	fin.open("Phonebook.dat",ios::out|ios::binary);
	cout <<"\n -------PhoneBook----------\n";
	cout << "S.No." << "\t" << "Name" << "\t" << "Mob_Num" << "\t" << "Email" << "\t" << "Group" << endl;
	cout << "...................................................\n";
	while(fin.read((char *)&m,sizeof(m)))
	{
		m.show_details();
	}
	fin.close();
}


//Search operation in phonebook by serial number
void search_Records()
{
	//PhoneBook m;
	ifstream fin;
	int n, flag = 0;
	fin.open("Phonebook.dat", ios::out|ios::binary|ios::app);
	cout << "\n-----Search by Serial Number-------\n";
	cout << "Enter the serial Number: ";
	cin >> n;
	while(fin.read((char *)&m,sizeof(m)))
	{
		if(n == m.get_serial_no())
		{
			m.show_details();
			flag++;
			cout << "Record Foud and Displayed";
		}
	}
	fin.close();
	if(flag == 0)
		cout << "\nSerial Number Not Found";
}

// starting menu
void menu()
{
	int ch;
	do
	{
		cout<<"\n----------PHONEBOOK MANAGEMENT-------------\n";
		cout << "\n...........Program Menu.............\n";
		cout << "1 - Add Number" << endl;
		cout << "2 - Display Records" << endl;
		cout << "3 - Search Record" << endl;
		cout << "4 - Delete Record" << endl;
		cout << "0 - Exit" << endl;
		cout <<"\n Enter Menu choice: ";
		cin >> ch;
		switch(ch)
		{
			case 1:
				Add_Number();
				break;
			case 2:
				Display_Records();
				break;
			case 3:
				search_Records();
				break;
			case 4:
				delete_Record();
				break;
			}	
	}while(ch);
}

// delete record in the phonebook by serial number
void delete_Record()
{
	//PhoneBook m;
	ifstream fin;
	ofstream fout;
	int n, flag = 0;
	fin.open("Phonebook.dat",ios::out|ios::binary|ios::app);
	fout.open("temp.dat",ios::out|ios::binary);
	cout <<"\n Enter the serial no of record to delete: ";
	cin >>n;
	while(fin.read((char *)&m,sizeof(m)))
	{
		if(n == m.get_serial_no())
		{
			cout << "\n......The Following Record deleted.....\n";
			m.show_details();
			flag++;
		}
		else
			fout.write((char *)&m,sizeof(m));
	}
	fin.close();
	fout.close();
	if(flag == 0)
		cout << "The record of serial no " << n << " is not found";
	remove("Phonebook.dat");
	rename("temp.dat","Phonebook.dat");
}


int main()
{
	//PhoneBook m ;
	menu();
	
}
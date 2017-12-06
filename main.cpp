#include <iostream.h>
#include <string.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream.h>
#include <ctype.h>
#include <stdio.h>
#define ArraySize(array)	sizeof(array)/sizeof(array[0])
long speedglobal=4500;
void callmainmenu();
int checkIDexist(int);
void mainmenu();
void searchID();
void searchname();
void memberMainMenu();
void searchMembers();
void displayMembers();
void addmembers();
void addBooks();
void displayBooks();
void searchbooks();
void searchBookID();
void searchBookname();
void searchBookauthor();
void issueBook(long);
//************************************************************************************************
//Display Functions
//************************************************************************************************

//Creates horizontal line
void hr(int i,char ch)
{
	for(int j=0;j<80;j++)
	{
		gotoxy(j,i);
		cout<<ch;
	}
}
//Creates vertical line
void vr(int i,char ch)
{
	for(int j=0;j<25;j++)
	{
		gotoxy(i,j);
		cout<<ch;
	}
}

//Creates borders
void borders()
{
	char ch = '*';
	hr(0,ch);
	hr(25,ch);
	vr(0,ch);
	vr(81,ch);
}

//Center Functions
void center(char* word,int y=12.5)
{
	int length = strlen(word);
	gotoxy(40.5 - length/2,y);
	cout<<word;
}

//Simplified gotoxy to align text
void align(char* text,int x=30,int y=12.5)
{
	gotoxy(x,y);
	cout<<text;
}
//Creates a menu with the given heading and the elements passed through the array
void createMenu(char* word,char array[50][50]=NULL,int size=0,int step=3,int start=6)
{
	clrscr();
	borders();
	hr(4,'*');
	center(word,2);
	for(int i=0;i<size;i++)
	{
		char word[50] = {i+49,'.'};				//Makes the list of items numbered
		for(int j = 2; array[i][j-2]!='\0';j++)
		{
			word[j]=array[i][j-2];
		}
	align(word,30,start+(i*step));
	}
}
//Can be called to create a simple error screen
void delay(long i)
{
	for(long a=0;a<i;a++)
	{
		cout<<"";
	}
}


void errormsg(char* error="null")
{
	clrscr();
	borders();
	clrscr();
	borders();
	createMenu("ERROR");
	if(strcmp(error,"null"))
		center(error);
	center("Press any key to continue...",17);
	getche();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void callmainmenu()
{
	mainmenu();
}

void main()
{
	mainmenu();
	exit(1);
}
void memberMainMenu()
{	start:
	clrscr();
	char membermainmenu[][50]={"ADD NEW MEMBERS","SEARCH MEMBERS","DISPLAY MEMBERS","EXIT"};
	createMenu("MEMBER ADMINISTRATION",membermainmenu,ArraySize(membermainmenu));
	align("CHOOSE AN OPTION ABOVE: ",30,20);
	int option;
	cin>>option;
	char wait;
	switch(option)
	{
		case 1:
			clrscr();
			addmembers();
			break;
		case 2:
			clrscr();
			searchMembers();
			break;
		case 3:
			clrscr();
			displayMembers();
			break;
		case 4:
			return;
		default:
			errormsg("Invalid option");
			goto start;


	}
}

class Member                   //Basic class for MEMBERS of the system
{
public:
	char Name[20];
	long Telno ;
	long borrowedBooks[10];
	int bbIndex;
	float fee;
	float payment;
	int MemID;
	void getmembers();
	void showmembers();

};

void addmembers()                        //Function to Add new members
{
	char ch;
	ofstream fout;
	Member m;
	fout.open("members.dat",ios::binary|ios::app);
	m.getmembers();
	fout.write((char*)&m,sizeof(m));
	createMenu("Enter Details");
	center("Member Added",8);
	fout.close();
	start:
	center("Do you want to add more members?(Y/N)",10);
	cin>> ch;
	if(ch=='Y' || ch=='y')
		addmembers();
	else if (ch=='N'||ch=='n')
		memberMainMenu();
	else
	{
		errormsg("Invalid operation");
		createMenu("Enter Details");
		goto start;
	}

}
int checkIDexist(int ID)
{
	ifstream fin;
	fin.open("members.dat",ios::binary|ios::in);
	fin.seekg(0,ios::beg);
	Member m;
	while(fin.read((char*)&m,sizeof(m)));
	{
		if(ID==m.MemID)
		{
			createMenu("Enter Details");
			center("ID Number Exists Please try a different ID no:");
			center("Press any key to try again",20);
			getch();
			return 1;
		}

	}
	fin.close();
	return 0;
}
void Member :: getmembers()              //Member Function to obtain intial details of members
{       start1:
	createMenu("Enter Details");
	align("Enter Member ID ",19,6);
	cin>>MemID;
	int i;
	i=checkIDexist(MemID);
	if(i==1)
	       goto start1;
	align("Enter NAME: ",19,8);
	gets(Name);
	align("Enter Telephone number ",19,10);
	cin>> Telno;
	start:
	align("Membership Package",19,12);
	align("BD-5/month (3 books/week)",19,13);
	align("BD-3/month(2 books/week)",19,14);
	align("BD-1/month(1 books/week)",19,15);
	align("enter the price of the package required BD: ",19,16);
	cin>>fee;
	if (fee!=5 && fee!=3 && fee!=1)
		{
			errormsg("Package not available");
			createMenu("Enter Details");
			goto start;

		}
	bbIndex=-1;
}
void Member :: showmembers()            //Member Function to show intial details of members
{
	createMenu("Member Details");
	align("Member ID: ",19,6);
	cout<<MemID;
	align("Name: ",19,8);
	cout<<Name;
	align("Telephone Number: ",19,10);
	cout<<Telno;
	align("Membership package: BD-",19,12);
	cout<<fee;
}
void displayMembers()
{
	clrscr();
	ifstream fin;
	fin.open("members.dat",ios::binary|ios::in);
	Member M;
	fin.seekg(0,ios::end);
	int count=fin.tellg()/sizeof(M),i=0;
	fin.seekg(0);
	while(fin.read((char*)&M,sizeof(M)))
	{
		M.showmembers();
		align("Member ",19,14);
		cout<<++i<<" of "<<count;
		getch();
	}
	fin.close();
	cout<<endl;
	align("ENTER any key to continue: ",19,16);
	getch();
	memberMainMenu();
}

void searchMembers()
{	start:
	int op;
	char searchmember[][50]={"By Member ID","By Name","Exit"};
	createMenu("Search Member",searchmember,ArraySize(searchmember));
	align("CHOOSE AN OPTION ABOVE: ",30,20);
	cin>>op;
	switch(op)
	{
	case 1:
		clrscr();
		searchID();
		break;
	case 2:
		clrscr();
		searchname();
		break;
	case 3:
		clrscr();
		memberMainMenu();
		break;
	default:
		errormsg("invalid option");
		goto start;

	}
}
void searchID()
{
	ifstream fin;
	fin.open("members.dat",ios::binary|ios::in);
	Member S;
	int j=0;
	char wait;
	int ID;
	createMenu("Search by ID");
	align("Enter the Member ID ",20,6);
	cin>>ID;
	while(fin.read((char*)&S,sizeof(S)) )
		if(ID==S.MemID)
		{
			S.showmembers();
			j=1;
		}
	if(j==0)
	{
		createMenu("Search by ID");
		center("DOES NOT EXIST");
		center("ENTER any key to continue:",20);
		getch();
		searchMembers();
	}
	else
	{
		center("ENTER any key to continue:",20);
		getch();
		searchMembers();
	}
}
void searchname()
{
	char wait;
	int j=0;
	ifstream fin;
	fin.open("members.dat",ios::binary|ios::in);
	Member S;
	char name[20];
	createMenu("Search by Name");
	align("Enter the Member Name ",20,6);
	gets(name);
	while(fin.read((char*)&S,sizeof(S)))
		if(strcmp(S.Name,name)==0)
		{
			S.showmembers();
			j=1;
		}
	if(j==0)
	{
		createMenu("Search by Name");
		center("DOES NOT EXIST");
		center("ENTER any key to continue:",20);
		getch();
		searchMembers();
	}
	else
	{
		center("ENTER any key to continue:",20);
		getch();
		searchMembers();
	}
}



class Book
{
public:
	long bookID;
	char Title[50];
	char Author[50];	float price;
	int Qty;
	int Qtyavailable;
	void getbookdata();
	void showbookdata();

};
void Book:: getbookdata()				 //Member Function to obtain intial details of books
{
	createMenu("Enter Details");

	align("Enter Book ID: ",19,6);
	cin>>bookID;
	align("Enter NAME: ",19,8);
	gets(Title);
	align("Enter Author's name: ",19,10);
	gets(Author);
	align("Enter price of this book ",19,12);
	cin>>price;
	align("Enter the no of this book the library owns ",19,14);
	cin>>Qty;
	Qtyavailable=Qty;
}

void Book :: showbookdata()            //Member Function to show intial details of books
{
	createMenu("Book Details");
	align("Book ID ",19,6);
	cout<<bookID;
	align("Name: ",19,8);
	cout<<Title;
	align("Author",19,10);
	cout<<Author;
	align("Price of this book: ",19,12);
	cout<<"BD-"<<price;
	align("Quantity of this book the library owns: ",19,14);
	cout<<Qty;
	align("Quantity of the book available: ",19,16);
	cout<<Qtyavailable;

}
void bookmainmenu()
{
	start:
	int option;
	char bookmainmenu [][50]={"ADD NEW BOOKS","SEARCH BOOKS","Display details of all books","EXIT"};
	createMenu("Book Administration",bookmainmenu,ArraySize(bookmainmenu));
	align("CHOOSE AN OPTION ABOVE: ",30,20);
	cin>>option;
	char wait;
	switch(option)
	{
	case 1:
		clrscr();
		addBooks();
		break;
	case 2:
		clrscr();
		searchbooks();
		break;
	case 3:
		clrscr();
		displayBooks();
		break;
	case 4:
		return;
	default:
		errormsg("Invalid Option");
		goto start;

	}
}

void addBooks()                        //Function to Add new members
{
	char ch;
	ofstream fout;
	Book b;
	fout.open("books.dat",ios::binary|ios::app);
	b.getbookdata();
	fout.write((char*)&b,sizeof(b));
	createMenu("Enter Details");
	center("Book Added",8);
	fout.close();
	start:
	center("Do you want to add more books?(Y/N)",10);
	cin>> ch;
	if(ch=='Y' || ch=='y')
		addBooks();
	else if (ch=='N'|| ch=='n')
		bookmainmenu();
	else
	{
		errormsg("Invalid operation");
		createMenu("Enter Details");
		goto start;
	}
}

void displayBooks()
{
	clrscr();
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book b;
	fin.seekg(0,ios::end);
	int count=fin.tellg()/sizeof(b),i=0;
	fin.seekg(0);
	while(fin.read((char*)&b,sizeof(b)))
	{
		b.showbookdata();
		align("Book ",19,18);
		cout<<++i<<" of "<<count;
		getch();
	}
	fin.close();
	cout<<endl;
	align("ENTER any key to continue: ",19,20);
	getch();
	bookmainmenu();
}

void searchbooks()
{
start:
	char searchbook[][50]={"BY BOOK ID","BY NAME","BY AUTHOR","EXIT"};
	createMenu("SEARCH BOOK",searchbook,ArraySize(searchbook));
	align("CHOOSE AN OPTION ABOVE: ",30,20);
	int op;
	cin>>op;
	switch(op)
	{
	case 1:
		clrscr();
		searchBookID();
		break;
	case 2:
		clrscr();
		searchBookname();
		break;
	case 3:
		clrscr();
		searchBookauthor();
		break;
	case 4:
		clrscr();
		bookmainmenu();
		break;
	default:
		errormsg("invalid option");
		goto start;
	}
}
void searchBookID()
{
	createMenu("SEARCH");
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book B;
	int j=0;
	char wait;
	int ID;
	cout<<"Enter the Book ID "<<endl;
	cin>>ID;
	while(fin.read((char*)&B,sizeof(B)) )
	if(ID==B.bookID)
	{
		B.showbookdata();
		gotoxy(15,23);
		cout<<"Press 2 to issue book:  ";
		cin>>j;

	}
	fin.close();
	if(j==0)
	{
		clrscr();
		cout<<ID;
		cout<<" "<<"DOES NOT EXIST"<<endl;
		cout<<endl;
		cout<<"ENTER any key to continue:"<<" ";
		cin>>wait;
		bookmainmenu();
	}
	else if(j==2)
	{
		issueBook(B.bookID);
		bookmainmenu();
	}
	else
	{
		if(j==2)
			issueBook(B.bookID);
		gotoxy(55,23);
		cout<<"ENTER any key to continue:"<<" ";
		cin>>wait;
		bookmainmenu();
	}
}
void searchBookname()
{
	char wait;
	int j=0;
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book B;
	char name[20];
	cout<<"Enter the Book's name:"<<" ";
	gets(name);
	cout<<endl;
	while(fin.read((char*)&B,sizeof(B)))
		if(strcmp(B.Title,name)==0)
		{
			B.showbookdata();
			gotoxy(15,23);
			cout<<"Press 2 to issue book:  ";
			cin>>j;
		}
	fin.close();
	if(j==0)
	{
		clrscr();
		cout<<name<<" "<<"IS NOT OWNED BY US"<<endl;
		cout<<endl;
		cout<<"ENTER any key to continue:"<<" ";
		cin>>wait;
		bookmainmenu();
	}
	else
	{
		if(j==2)
			issueBook(B.bookID);
		gotoxy(55,23);
		cout<<"ENTER any key to continue: ";
		cin>>wait;
		memberMainMenu();
	}
}
void searchBookauthor()
{
	char wait;
	int j=0;
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book B;
	char name[20];
	cout<<"Enter the Author's name "<<endl;
	gets(name);
	while(fin.read((char*)&B,sizeof(B)))
		if(strcmp(B.Author,name)==0)
		{
			B.showbookdata();
			gotoxy(15,23);
			cout<<"Press 2 to issue book..";
			cin>>j;
		}
	fin.close();
	if(j==0)
	{
		clrscr();
		cout<<name<<"'s"<<" " <<"IS NOT OWNED BY US"<<endl;
		cout<<endl;
		cout<<"ENTER any key to continue:"<<" ";
		cin>>wait;
		bookmainmenu();
	}
	else
	{
		if(j==2)
			issueBook(B.bookID);
		gotoxy(55,23);
		cout<<"ENTER any key to continue:"<<" ";
		cin>>wait;
		bookmainmenu();
	}
}

void issueBook(long bookId)
{
	int j=0;
	Book B;
	ifstream bookfile("books.dat", ios::in|ios::binary);
	while(bookfile.read((char*)&B, sizeof(B)))
		if(B.bookID == bookId)
			j=1;
	bookfile.close();

	Member M;
	clrscr();
	gotoxy(20,5);
	cout<<"Enter member id: ";
	int memId;
	cin>>memId;

	ofstream outfile("members.dat", ios::app|ios::binary);
	ifstream infile("members.dat", ios::in|ios::binary);

	while(infile.read((char*)&M, sizeof(M)))
		if(M.MemID==memId && j==1)
		{
			M.borrowedBooks[++M.bbIndex]=bookId;
			int loc= infile.tellg() - sizeof(Book);
			outfile.seekp(loc, ios::beg);
			outfile.write((char*)&M, sizeof(M));
		}
	outfile.close();
	infile.close();
}

void mainmenu()
{
start:
	borders();
	char menu[][50]={"MEMBER ADMINISTRATION","BOOK ADMINISTRATION","EXIT"};
	createMenu("LIBRARY MENU",menu,ArraySize(menu));
	align("CHOOSE AN OPTION ABOVE: ",30,20);
	int option;
	cin>>option;
	char wait;
	switch(option)
	{
	case 1:
		clrscr();
		memberMainMenu();
		break;
	case 2:
		clrscr();
		bookmainmenu();
		break;
	case 3:
		clrscr();
		return;
		break;

	default:
	    errormsg("Invalid option");
		goto start;

	}
	goto start;
}

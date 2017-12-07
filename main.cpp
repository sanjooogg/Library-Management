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
int checkbookIDexist(int);
void addBooks();
void displayBooks();
void searchbooks();
void searchBookID();
void searchBookname();
void searchBookauthor();
void issueBook(long);
void returnbook();
void addUser();
char* getpass();
void login();
char* encrypt(char pass[]);
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
int checkmemberIDexist(int ID)
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
	i=checkmemberIDexist(MemID);
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
{	start:
	createMenu("Enter Details");
	align("Enter Book ID: ",19,6);
	cin>>bookID;
	int i;
	i=checkbookIDexist();
	if(i==1)
		goto start;
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
	char bookmainmenu [][50]={"ADD NEW BOOKS","SEARCH BOOKS","Display details of all books","Issue Book","EXIT"};
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
		clrscr();
		searchbooks();
	case 5:
		return;
	default:
		errormsg("Invalid Option");
		goto start;

	}
}
int checkbookIDexist(int ID)
{
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
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
	int j;
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
		center("Press 2 to issue book press any other key and hit enter to continue :  ",18);
		cin>>j;
		if(j==2)
	{
		issueBook(b.bookID);
	}
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
	createMenu("Search by ID");
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book B;
	int j=0,k;
	char wait;
	int ID;
	align("Enter the Book ID ",20,6);
	cin>>ID;
	while(fin.read((char*)&B,sizeof(B)) )
	if(ID==B.bookID)
	{
		B.showbookdata();
		center("Press 2 to issue book press any other key and hit enter to continue :  ",18);
		cin>>k;
		j=1;
	}
	fin.close();
	if(j==0)
	{
		createMenu("Search by ID");
		center("DOES NOT EXIST");
		center("ENTER any key to continue:",20);
		getch();
		searchbooks();
	}
	if(k==2)
	{
		issueBook(B.bookID);
		searchbooks();
	}
}
void searchBookname()
{
	char wait;
	createMenu("Search by Name");
	int j=0,k;
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book B;
	char name[20];
	align("Enter the Book's Name ",20,6);
	gets(name);
	while(fin.read((char*)&B,sizeof(B)))
		if(strcmp(B.Title,name)==0)
		{
			B.showbookdata();
			center("Press 2 to issue book press any other key and hit enter to continue :  ",18);
			cin>>k;
			j=1;
		}
	fin.close();
	if(j==0)
	{
		createMenu("Search by Name");
		center("We don't own that book");
		center("ENTER any key to continue:",20);
		getch();
		searchbooks();
	}
	if(k==2)
	{	
		issueBook(B.bookID);
		searchbooks();
	}
}
void searchBookauthor()
{
	char wait;
	createMenu("Search by Author");
	int j=0,k;
	ifstream fin;
	fin.open("books.dat",ios::binary|ios::in);
	Book B;
	char name[20];
	align("Enter the Author's Name ",20,6);
	gets(name);
	while(fin.read((char*)&B,sizeof(B)))
		if(strcmp(B.Author,name)==0)
		{
			B.showbookdata();
			center("Press 2 to issue book press any other key and hit enter to continue :  ",18);
			cin>>k;
			j=1;
		}
	fin.close();
	if(j==0)
	{
		createMenu("Search by Name");
		center("We don't own that Author's books");
		center("ENTER any key to continue:",20);
		getch();
		searchbooks();
	}
	if(k==2)
	{
	issueBook(B.bookID);
	searchbooks();		
	}
}

void issueBook(long bookId)
{	
	createMenu("Book issueing");
	int j=0;
	Book B;
	ofstream bookfile1("books.dat", ios::app|ios::binary);
	ifstream bookfile("books.dat", ios::in|ios::binary);
	while(bookfile.read((char*)&B, sizeof(B)))
		if(B.bookID == bookId)
		{	if(B.Qtyavailable>=1)
			{
				j=1;
				B.Qtyavailable-=1;
				int loc= bookfile.tellg() - sizeof(B);
				bookfile1.seekp(loc, ios::beg);
				bookfile1.write((char*)&B, sizeof(B));
			}
			else
			{
				center("Book currently not available");
				return;
			}
		}
	bookfile.close();
	

	Member M;
	align("Enter member id: ",19,6);
	int memId;
	cin>>memId;

	ofstream outfile("members.dat", ios::app|ios::binary);
	ifstream infile("members.dat", ios::in|ios::binary);

	while(infile.read((char*)&M, sizeof(M)))
		if(M.MemID==memId && j==1)
		{
			M.borrowedBooks[++M.bbIndex]=bookId;
			int loc= infile.tellg() - sizeof(M);
			outfile.seekp(loc, ios::beg);
			outfile.write((char*)&M, sizeof(M));
		}
	outfile.close();
	infile.close();
	createMenu("Book issueing");
	center("The Book is borrowed");
	center("ENTER any key to continue: ",20);
	getch();

}

void returnbook()
{	
	Book B;
	ofstream bookfile1("books.dat", ios::app|ios::binary);
	ifstream bookfile("books.dat", ios::in|ios::binary);
	ifstream fin;
	fin.open("members.dat",ios::binary|ios::in);
	Member S;
	int j=0,k;
	char wait;
	int ID;
	createMenu("Return Book");
	align("Enter the Member ID ",20,6);
	cin>>ID;
	while(fin.read((char*)&S,sizeof(S)) )
		if(ID==S.MemID)
		{
			S.showmembers();
			j=1;
			align("ENTER any key to continue: ",19,20);
			getch();
		}
	if(j==0)
	{
		createMenu("Search by ID");
		center("DOES NOT EXIST");
		center("ENTER any key to continue:",20);
		getch();
		returnbook();
	}
	else
	{
		int l=0,a[10],b=0;
		a[0]=S.bbIndex;
		for(int i=0;i<S.bbIndex;i++)
			while(bookfile.read((char*)&B, sizeof(B)))
				if(B.bookID == S.borrowedBooks[i])
					{   
						B.showbookdata();
						align("Book ",19,18);
						cout<<++l<<" of "<<bbIndex-1;
						center("Press 2 to return book press any other key and hit enter to continue checking borrowed :  ",20);
						cin>>k;
						if(k==2)
						{	
							a[b]=i;
							b++;
							B.Qtyavailable+=1;
							int loc= bookfile.tellg() - sizeof(B);
							bookfile1.seekp(loc, ios::beg);
							bookfile1.write((char*)&B, sizeof(B));
							createMenu("Return Book");
							center("Book Returned");
						}
					}
		if(a[0]!=S.bbIndex)
			{	for(j=0;j<b;j++)
					{
						for(i=a[j];i<S.bbIndex;i++)
							S.borrowedBooks[i]=S.borrowedBooks[i+1];
						S.bbIndex-=1;
					}
			}
	}

}
char* encrypt(char pass[])
{
	int i=0;
	for(i=0;pass[i]!='\0';i++)
		pass[i]+=strlen(pass);
	return pass;
}


char* getpass()
{
	char pass[200];
	int i=0;
	while(1)
	{
	pass[i] = getch();
	if(pass[i]==13)
	{
		pass[i]='\0';
		break;
	}
	else if(i>=1 && pass[i]==8)  //Checks for backspace
	{
		i--;
		gotoxy(46+i,12);
		cout<<" ";
		gotoxy(46+i,12);
	}
	else
	{
		cout<<'*';
		i++;
	}
	}
	return pass;
}
class user
{
	char uname[200];
	char pass[200];
public:
  void input()
  {
	align("Enter Username: ",30,10);
	gets(uname);
	align("Enter Password: ",30,12);
	strcpy(pass,getpass());
	strcpy(pass,encrypt(pass));
  }
  int access(char ename[],char epass[])
  {
	int x=((strcmp(epass,pass)==0 && strcmp(ename,uname)==0)?1:0);
	return x;
  }
};
void addUser()
{
	user U;
	U.input();
	ofstream file;
	file.open("users.dat",ios::app|ios::binary);
	file.write((char*)&U,sizeof(U));
	file.close();
}
void login()
{
 char uname[200],pass[200];
 login:
	 borders();
	 align("LOGIN",36,7);
	 align("Enter Username: ",30,10);
	 gets(uname);
	 align("Enter Password: ",30,12);
	 strcpy(pass,getpass());
	 strcpy(pass,encrypt(pass));
	 ifstream file;
	 file.open("users.dat",ios::in|ios::binary);
	 user U;
	 while(!file.eof())
	 {
		file.read((char*)&U,sizeof(U));
		if(U.access(uname,pass))
	  {
		main_menu();
	  }
		else
	  {
		errormsg("Incorrect username or password");
		clrscr();
		goto
		login;
	  }
	 }
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

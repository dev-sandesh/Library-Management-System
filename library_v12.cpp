//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<iostream.h>
#include<cstring>
#include<windows.h>
#include<string>
#include <time.h>

void sort_stuindex(int cnt);
void create_stuindex();
void displayspecificstudentbyname();
void sort_bookindex(int cntbook);
void sort_issueindex(int cntissue);
void create_bookindex();
void displayspecificbookbyname();
int main();
int main_menu();
void admin_menu_book();
void admin_menu_student();
void error(int error_type);
void view_index();
void modify_student();
void deposit();
void timeis();
int passcheck2(char a[],char b[]);
void passcheck();

using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

int cnt,cntbook,cntissue,modify_stutoken=0,modify_bktoken=0,delete_stutoken=0;
int error_type,usntoken,book_idtoken;


struct indexstu										//index student struct def
{
	string usn,name;
	int addr;
}i1[1000],found[1000],temp;

struct indexbook										//index book struct def
{
	string book_id,bname;
	int address;
}i2[1000],found2[1000],temp2;

struct indexissue
{
	string usn;
	int addr;
}i3[1000],temp3,found3[1000];

void error(int error_type)										// function error
{
	cout<<"\n\n-------------------------------------\n";
	switch(error_type)
	{
		case 1: cout<<"\n\n ERROR";
  			 cout<<"\n\n Cannot Open File";
  			 break;
	 	case 2: cout<<"\n ERROR";
	 		 cout<<"\n USN Already in record";
	 		 break;
	 	case 3: cout<<"\n ERROR";
		 	 cout<<"\n BOOK Already in record";
			 break;
		case 4: cout<<"\n NO RECORD FOUND";
			 break;
		case 5: cout<<"\n EXCEEDS LIMIT! RETURN PREVIOUSLY ISSUED BOOKS";
			 break;
		case 6: cout<<"\n BOOK LIMIT EXCEEDED!";
			 break;
	}
	cout<<"\n\n-------------------------------------\n";
}

void create_bookindex()										//index function for book
{
	fstream fp;
	int pos,i;
	string seg,book_idbuf,bnamebuf;
	cntbook=-1;
	fp.open("book2.txt",ios::in);
	if(!fp)
	{	error_type=1;
		error(error_type);
		getch();
		return;
	}
	while(fp)
	{
		book_idbuf.erase();
		bnamebuf.erase();
		pos=fp.tellg();
		getline(fp,book_idbuf,'|');
		getline(fp,bnamebuf,'|');
		getline(fp,seg);
		if(book_idbuf[0]=='*'||book_idbuf.length()==0||bnamebuf.length()==0)
			continue;
		cntbook++;
		i2[cntbook].book_id=book_idbuf;
		i2[cntbook].bname=bnamebuf;
		i2[cntbook].address=pos;

	}
	fp.close();
	sort_bookindex(cntbook);

}


void sort_bookindex(int cntbook)								//sort function for book index
{
	for(int i=0;i<=cntbook;i++)
	{
		for(int j=i+1;j<=cntbook;j++)
		{
			if(i2[i].book_id>i2[j].book_id)
			{
				temp2.book_id=i2[i].book_id;
				temp2.bname=i2[i].bname;
				temp2.address=i2[i].address;

				i2[i].book_id=i2[j].book_id;
				i2[i].bname=i2[j].bname;
				i2[i].address=i2[j].address;

				i2[j].book_id=temp2.book_id;
				i2[j].bname=temp2.bname;
				i2[j].address=temp2.address;
			}
		}
	}
}

void create_stuindex()										// create student index
{
	fstream fp;
	int pos,i;
	string seg,usnbuf,namebuf;
	cnt=-1;
	fp.open("student2.txt",ios::in);
	if(!fp)
	{	error_type=1;
		error(error_type);
		getch();
		return;
	}
	while(fp)
	{
		usnbuf.erase();
		namebuf.erase();
		pos=fp.tellg();
		getline(fp,usnbuf,'|');
		getline(fp,namebuf,'|');
		getline(fp,seg);
		if(usnbuf[0]=='*'||usnbuf.length()==0||namebuf.length()==0)
			continue;
		cnt++;
		i1[cnt].usn=usnbuf;
		i1[cnt].name=namebuf;
		i1[cnt].addr=pos;

	}
	fp.close();
	sort_stuindex(cnt);
}


void sort_stuindex(int cnt)									//function sort for student index
{
	for(int i=0;i<=cnt;i++)
	{
		for(int j=i+1;j<=cnt;j++)
		{
			if(i1[i].usn>i1[j].usn)
			{
				temp.usn=i1[i].usn;
				temp.name=i1[i].name;
				temp.addr=i1[i].addr;

				i1[i].usn=i1[j].usn;
				i1[i].name=i1[j].name;
				i1[i].addr=i1[j].addr;

				i1[j].usn=temp.usn;
				i1[j].name=temp.name;
				i1[j].addr=temp.addr;
			}
		}
	}

}


void create_issueindex()										//index function for book
{
	fstream fp;
	int pos,i;
	string seg,usn_issuebuf;
	cntissue=-1;
	fp.open("issue2.txt",ios::in);
	if(!fp)
	{	error_type=1;
		error(error_type);
		getch();
		main_menu();
	}
	while(fp)
	{
		usn_issuebuf.erase();
		pos=fp.tellg();
		getline(fp,usn_issuebuf,'|');
		getline(fp,seg);
		if(usn_issuebuf[0]=='*'||usn_issuebuf.length()==0 || usn_issuebuf[0]==' ')
			continue;
		cntissue++;
		
		i3[cntissue].usn=usn_issuebuf;
		i3[cntissue].addr=pos;

	}
	fp.close();
	sort_issueindex(cntissue);

}


void sort_issueindex(int cntissue)									//function sort for student index
{
	for(int i=0;i<=cntissue;i++)
	{
		for(int j=i+1;j<=cntissue;j++)
		{
			if(i3[i].usn>i3[j].usn)
			{
				temp.usn=i3[i].usn;
				temp.addr=i3[i].addr;

				i3[i].usn=i3[j].usn;
				i3[i].addr=i3[j].addr;

				i3[j].usn=temp.usn;
				i3[j].addr=temp.addr;
			}
		}
	}

}


char bin_srch_book(string book_id_srch)							//function binary search for book
{
	int l=0,h=cntbook,mid;
	while(l<=h)
	{
		mid=(l+h)/2;
		if(i2[mid].book_id==book_id_srch)
		{
				book_idtoken=1;
				return mid;

		}

		if(i2[mid].book_id < book_id_srch)
			l=mid+1;
		if(i2[mid].book_id > book_id_srch)
			h=mid-1;
	}

	return -1;
}
char bin_srch_issue(string usnissue_srch)							//function binary search for book
{
	int l=0,h=cntissue,mid;
	while(l<=h)
	{
		mid=(l+h)/2;
		if(i3[mid].usn==usnissue_srch)
		{
			//	usnissue_token=1;
				return mid;

		}

		if(i3[mid].usn < usnissue_srch)
			l=mid+1;
		if(i3[mid].usn > usnissue_srch)
			h=mid-1;
	}

	return -1;
}

int x,y;


string timebuf,stringtime;
char chartime[1000];

void timeis() 
{
   	long timei;
	time_t now = time(0);
	int year,month,day,hour,min,sec;
	string syear,smonth,sday,shour,smin,ssec;
	char cyear[3000],cmonth[10],cday[10],chour[10],cmin[10],csec[10];
	
	
	tm *ltm = localtime(&now);
	
	year = ltm->tm_year+1900;
	itoa(year,cyear,10);
	syear=cyear;

   	month = ltm->tm_mon+1;
	itoa(month,cmonth,10);
	smonth=cmonth;
	int smx=atoi(smonth.c_str());
	if(smx<10)
	{
		smonth='0'+smonth;
	}

		
   	day  = ltm->tm_mday;
 	itoa(day,cday,10);
	sday=cday;
	int sdx=atoi(sday.c_str());
	if(sdx<10)
	{
		sday='0'+sday;
	}

 	
 	hour = ltm->tm_hour;
	itoa(hour,chour,10);
	shour=chour;
	int shx=atoi(shour.c_str());
	if(shx<10)
	{
		shour='0'+shour;
	}

  	
  	min = ltm->tm_min;
 	itoa(min,cmin,10);
 	smin=cmin;
	int smix=atoi(smin.c_str());
	if(smix<10)
	{
		smin='0'+smin;
	}
	
	
	timebuf = syear+smonth+sday+shour+smin;
}


class issuebook
{
	public:
	string usn,book1,book2,book3,time1,time2,time3;

	void unpackissue();
	void packissue();


}issueb,issueb1[1000];

class book
{	public:
	string book_id;
	string bname;
	string aname;
	string pname;
	string year;
	string copies;

  public:
	void create_book()
	{
		string x2;
		cout<<"\nNEW BOOK ENTRY\n";
		getline(std::cin,x2);
		cout<<"\nEnter BookID:  ";
		cin>>book_id;
		cout<<"\nEnter Book Name: ";
		getline(std::cin,bname);
		cout<<"\nEnter Author's Name: ";
		getline(std::cin,aname);
		cout<<"\nEnter Publication House: ";
		getline(std::cin,pname);
		cout<<"\nEnter year: ";
		cin>>year;

		int x=atoi(year.c_str());

		while((x < 1900)||(x > 2018))
		  {
  			cout<<"\nInvalid\n";
  			year='0';
  			cout<<"\nEnter year: ";
  			getline(std::cin,year);
  			x=atoi(year.c_str());
		  }

		cout<<"\nEnter copies: ";
		cin>>copies;

		int y=atoi(copies.c_str());

		while((y < 1)||(y > 50))
		  {
  			cout<<"\nInvalid";
  			copies='0';
  			cout<<"\nEnter Copies: ";
  			getline(std::cin,copies);
  			y=atoi(copies.c_str());
		  }

		bin_srch_book(book_id);
		if(book_idtoken==1)
		{
			error_type=3;
			error(error_type);
			book_idtoken=0;
			getch();
			admin_menu_book();

		}

	}

	void show_book()
	{
		cout<<"\n-------------------------------------\n";
		cout<<"\nBook id. : "<<book_id;
		cout<<"\nBook Name : "<<bname;
		cout<<"\nAuthor Name : "<<aname;
		cout<<"\nPublication Name : "<<pname;
		cout<<"\nYear : "<<year;
		cout<<"\nNumber of copies : "<<copies;
		cout<<"\n\n-------------------------------------";
	}
void unpackbook();
void packbook();
void show_book_m();
void modifyb();
};       							   					//class ends here

book bk,bk1[1000];


fstream fp,fp1;
fstream fpbook,fpstu;

	string emailstr1 ("@gmail.com");
	string emailstr2 ("@yahoo.com");
	string emailstr3 ("@hotmail.com");


void issuebook::unpackissue()
	{
		string seg;
		getline(fp,usn,'|');
		getline(fp,book1,'|');
		getline(fp,book2,'|');
		getline(fp,book3,'|');
		getline(fp,time1,'|');
		getline(fp,time2,'|');
		getline(fp,time3,'|');
		getline(fp,seg);
	}

void issuebook::packissue()
{
	string buf=issueb.usn+'|'+issueb.book1+'|'+issueb.book2+'|'+issueb.book3+'|'+issueb.time1+'|'+issueb.time2+'|'+issueb.time3+'|';
	fp<<buf<<endl;
}

char bin_srch(string usn_srch)								//function binary search for student
{
	int l=0,h=cnt,mid;
	while(l<=h)
	{
		mid=(l+h)/2;
		if(i1[mid].usn==usn_srch)
		{
				usntoken=1;
				return mid;

		}

		if(i1[mid].usn<usn_srch)
			l=mid+1;
		if(i1[mid].usn>usn_srch)
			h=mid-1;
	}

	return -1;
}

void book::unpackbook()
{
	string seg;
	getline(fp,book_id,'|');
	getline(fp,bname,'|');
	getline(fp,aname,'|');
	getline(fp,pname,'|');
	getline(fp,year,'|');
	getline(fp,copies,'|');
	getline(fp,seg);
}


void book::packbook()
{
	string buf=book_id+'|'+bname+'|'+aname+'|'+pname+'|'+year+'|'+copies+'|';
	fp<<buf<<endl;
}

class student												//class student
{
	public:
	string usn;
	string name;
	string email;
	string phone;
	string stbno;
	int token;

void create_student()
{
	string x2;
	usntoken=0;
	getline(std::cin,x2);
	cout<<"\nNEW STUDENT ENTRY...\n";
	cout<<"\nEnter The USN: ";
	cin>>usn;
 	cout<<"\nEnter The Name of The Student: ";
       getline(std::cin,name);
	cout<<"\nEnter Email: ";
	cin>>email;

	  // size_t at1 = email.find("@gmail.com");
	  // size_t at2 = email.find("@yahoo.com");
	 //  size_t at3 = email.find("@hotmail.com");

	  while((strstr(email.c_str(),emailstr1.c_str())==NULL) || (strstr(email.c_str(),emailstr2.c_str())) || (strstr(email.c_str(),emailstr3.c_str())) )
         {
   		cout << "\n\nInvalid Email";
 		cout << "\nEmail  not  accepted.\n";
		email='0';
		cout<<"\nEnter Email Again: ";
		cin>>email;
	 }

	  cout<<"\nEnter Phone Number: ";
	  cin>>phone;
	  long x=atoi(phone.c_str());

	while((x < 1000000000)||(x > 9999999999))
		  {
  			cout<<"\nInvalid\n";
  			phone='0';
  			cout<<"\nEnter Phone Again: ";
  			cin>>phone;
  			x=atoi(phone.c_str());
		  }

	stbno='0';
	bin_srch(usn);
	if(usntoken==1)
	{
		error_type=2;
		error(error_type);
		usntoken=0;
		getch();
		admin_menu_student();
	}
}


void show_student()
	{
		string stry,strm,strd,a;
		cout<<"\n-------------------------------------";
		cout<<"\n\nUSN : "<<usn;
		cout<<"\nStudent Name : "<<name;
		cout<<"\nStudent email : "<<email;
		cout<<"\nStudent phone : "<<phone;
		if(stbno[0]=='0')
		{
			cout<<"\n\nNo Book issued yet!\n";
		}
		else 
		{
			int z=bin_srch_issue(usn);
			int pos = i3[z].addr;
			
			fp.open("issue2.txt",ios::in);
			fp.seekg(pos,ios::beg);
			issueb.unpackissue();
			a='0';
			if(issueb.book1.compare(a)!=0)
			{
				cout<<"\n\n Book No. Issued: "<<issueb.book1;
				stry=issueb.time1.substr(0,4);
				strm=issueb.time1.substr(4,2);
				strd=issueb.time1.substr(6,2);
				cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;
			}
				
			if(issueb.book2.compare(a)!=0)
			{
				cout<<"\n\n Book No. Issued: "<<issueb.book2;
				stry=issueb.time2.substr(0,4);
				strm=issueb.time2.substr(4,2);
				strd=issueb.time2.substr(6,2);
				cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;
			}
			if(issueb.book3.compare(a)!=0)
			{
				cout<<"\n\n Book No. Issued: "<<issueb.book3;
				stry=issueb.time3.substr(0,4);
				strm=issueb.time3.substr(4,2);
				strd=issueb.time3.substr(6,2);
				cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;
			}	
				
			fp.close();	
		
		}
		cout<<"\n-------------------------------------";
	}




//	void pack();
	void unpack();
	void modify();
//	void modify_student();
	void pack();
	void unpackmods();
	void show_student_m();
}st,st1[1000];;         //class ends here


void student::show_student_m()
	{
		cout<<x;
		cout<<"\n-------------------------------------";
		cout<<"\n\nUSN : "<<st1[x].usn;
		cout<<"\nStudent Name : "<<st1[x].name;
		cout<<"\nStudent email : "<<st1[x].email;
		cout<<"\nStudent phone : "<<st1[x].phone;
		if(stbno[0]!='0')
		{
			cout<<"\n\nOne Book issued, ";
			cout<<"Book No: "<<st1[x].stbno;
		}

		else cout<<"\n\nNo Book issued yet!\n";
		cout<<"\n-------------------------------------";
	}

void student::unpack()
{
	string buf;
	getline(fp,usn,'|');
	getline(fp,name,'|');
	getline(fp,email,'|');
	getline(fp,phone,'|');
	getline(fp,stbno,'|');
	getline(fp,buf);
}



void student::pack()
{
	string buf=usn+'|'+name+'|'+email+'|'+phone+'|'+stbno+'|';
	fp<<buf<<endl;
}

void view_stuindex()
{
	fp.open("student2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		fp.close();
		getch();
		view_index();
	}
	cout<<"\n\n  INDEX\n";
	for(int i=0;i<=cnt;i++)
	{
		cout<<"\n "<<i1[i].usn<<"\t"<<i1[i].name;
	}
	fp.close();
	getch();
}

void view_bookindex()
{
	fp.open("book2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		fp.close();
		getch();
		view_index();
	}
	cout<<"\n\n  INDEX\n";
	for(int i=0;i<=cntbook;i++)
	{
		cout<<"\n "<<i2[i].book_id<<"\t"<<i2[i].bname;
	}
	fp.close();
	getch();
}

void view_issueindex()
{
	fp.open("issue2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		fp.close();
		getch();
		view_index();
	}
	cout<<"\n\n  INDEX\n";
	for(int i=0;i<=cntissue;i++)
	{
		cout<<"\n "<<i3[i].usn;
	}
	fp.close();
	getch();
}

void write_student()										//function write student
{
	fp.open("student2.txt",ios::out|ios::app);
	st.pack();
	cout<<"\n\nStudent Record Created";
	getch();
	fp.close();
	create_stuindex();
}

void write_book()										//function write book
{

	fp.open("book2.txt",ios::out|ios::app);
	string buf=(string)bk.book_id+'|'+bk.bname+'|'+bk.aname+'|'+bk.pname+'|'+bk.year+'|'+bk.copies+'|';
	fp<<buf<<endl;
	cout<<"\n\nBook Record Created";
	getch();
	fp.close();
	create_bookindex();
}

void display_sps()
{
	system("CLS");
	cout<<"\nSTUDENT DETAILS\n";

	string buf,usn_srch;
	cout<<"\nEnter USN to search: ";
	cin>>usn_srch;
	int pos=bin_srch(usn_srch);
	if(pos==-1)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_student();

	}
	cout<<"\nRecord found\n";
	fp.open("student2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		getch();
		admin_menu_student();
	}
	else
	{
		fp.seekg(i1[pos].addr,ios::beg);
		st.unpack();
		fp.close();
		st.show_student();
	}

	getch();
	usntoken=0;
}

int find_cnt=0;
int index_nums[1000];


int isname;


void display_spbook()
{	system("CLS");
	fp.open("book2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		getch();
		admin_menu_book();

	}
	cout<<"\nBOOK DETAILS\n";

	string buf,book_id_srch;

	cout<<"\nEnter book_id to search: ";
	cin>>book_id_srch;

	int pos=bin_srch_book(book_id_srch);
	if(pos==-1)
	{	error_type=4;
		error(error_type);
		fp.close();
		getch();
		admin_menu_book();

	}
	else
	{
		cout<<"\nRecord found\n";
		fp.seekg(i2[pos].address,ios::beg);
		getline(fp,bk.book_id,'|');
		getline(fp,bk.bname,'|');
		getline(fp,bk.aname,'|');
		getline(fp,bk.pname,'|');
		getline(fp,bk.year,'|');
		getline(fp,bk.copies,'|');
		getline(fp,buf);
		fp.close();
		bk.show_book();
	}

	book_idtoken=0;
	getch();
}
int find_cnt2=0;
int index_nums2[1000];


int isname2;
void ln_srchbook(string bname_srch)
{
	int i,j=0;
	for(i=0;i<=cntbook;i++)
	{
		if(i2[i].bname==bname_srch)
		{
			index_nums2[j++]=i;
			found2[find_cnt2].book_id=i2[i].book_id;
			found2[find_cnt2].bname=i2[i].bname;
			found2[find_cnt2].address=i2[i].address;
			find_cnt2++;
		}
	}
}

void ln_srch(string name_srch)
{
	int i,j=0;
	for(i=0;i<=cnt;i++)
	{
		if(i1[i].name==name_srch)
		{
			index_nums[j++]=i;
			found[find_cnt].usn=i1[i].usn;
			found[find_cnt].name=i1[i].name;
			found[find_cnt].addr=i1[i].addr;
			find_cnt++;
		}
	}
}

void displayspecificstudentbyname()
{
	int x;
	string name_srch,buf;
	system("CLS");
	cout<<"\nSTUDENT DETAILS\n";

	cout<<"\nEnter Name to search: ";
	cin>>name_srch;
	ln_srch(name_srch);
	if(find_cnt==0)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_student();
	}

	if(find_cnt==1)
	{
		isname=0;
		cout<<"\nRecord Found";
		find_cnt=0;
	}

	if(find_cnt>1)
	{	system("CLS");
		cout<<"\nMultiple Records!\n";
		for(int i=0;i<find_cnt;i++)
			cout<<"\n"<<i<<": usn: "<<found[i].usn<<endl;
		
		cout<<"\nEnter choice: ";
		std::cin>>isname;
		cout<<endl;
		if(isname>find_cnt)
		{
			cout<<"\nInvalid Value";
			find_cnt=0;
			getch();
			return;
		}
		find_cnt=0;
	}

	fp.open("student2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		getch();
		admin_menu_student();
	}

	else
	{
		fp.seekg(found[isname].addr,ios::beg);
		getline(fp,st.usn,'|');
		getline(fp,st.name,'|');
		getline(fp,st.email,'|');
		getline(fp,st.phone,'|');
		getline(fp,st.stbno,'|');
		getline(fp,buf);
		fp.close();
		st.show_student();
	}
	getch();
}


void displayspecificbookbyname()
{
	int x;
	string bname_srch,buf;
	system("CLS");
	cout<<"\nBOOK DETAILS\n";

	cout<<"\nEnter BOOK Name to search: ";
	cin>>bname_srch;
	ln_srchbook(bname_srch);
	if(find_cnt2==0)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_book();
	}

	if(find_cnt2==1)
	{
		isname2=0;
		cout<<"\nRecord Found";
		find_cnt2=0;
	}

	if(find_cnt2>1)
	{	system("CLS");
		cout<<"\nMultiple Records!\n";
		
		for(int i=0;i<find_cnt2;i++)
			cout<<"\n"<<i<<": book_id: "<<found2[i].book_id<<endl;
		cout<<"\nEnter choice: ";
		std::cin>>isname2;
		cout<<endl;
		if(isname2>find_cnt2)
		{
			cout<<"\nInvalid Value";
			getch();
			find_cnt2=0;
			return;
		}
		find_cnt2=0;
	}

	fp.open("book2.txt",ios::in);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		getch();
		admin_menu_book();
	}
	       fp.seekg(found2[isname2].address,ios::beg);
		getline(fp,bk.book_id,'|');
		getline(fp,bk.bname,'|');
		getline(fp,bk.aname,'|');
		getline(fp,bk.pname,'|');
		getline(fp,bk.year,'|');
		getline(fp,bk.copies,'|');
		getline(fp,buf);
		fp.close();
	bk.show_book();

	getch();
}


void modify_student()
{
	system("CLS");
	string usn_srch,seg;
	int i=0,srchflag=-1,modifyflag=-1,count;
	cout<<"\n\n\tEnter USN: ";
	cin>>usn_srch;
	fp.open("student2.txt",ios::in);
	srchflag=bin_srch(usn_srch);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		getch();
		admin_menu_student();
	}
	while(fp)
	{
		st1[i].unpack();
		if(st1[i].usn[0]=='*')
			continue;
		i++;
	}
	fp.close();

	if(srchflag==-1)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_student();
	}
	cout<<"\nRECORD FOUND";
	int pos = i1[srchflag].addr;
	fp.open("student2.txt",ios::in);
	fp.seekg(pos,ios::beg);
	getline(fp,st.usn,'|');
	getline(fp,st.name,'|');
	getline(fp,st.email,'|');
	getline(fp,st.phone,'|');
	getline(fp,st.stbno,'|');
	getline(fp,seg);
	fp.close();
	st.show_student();
	cout<<"\n\nDo you wish to modify?\n Enter 0 to cancel and 1 otherwise: ";
	cin>>modifyflag;
	if(modifyflag)
	{
		st.modify();
		fp.open("student2.txt",ios::out);
		if(!fp)
		{
			cout<<"\nERROR! cannot open file!";
		}
		for(i=0;i<=cnt;i++)
		{
			if (st1[i].usn==st.usn)
			{
				st.pack();

			}
			else
				st1[i].pack();
		}
		fp.close();
	}
	create_stuindex();
	usntoken=0;

}

void student::modify()
{
		int input,x;
		string x2;

    while(1) {
 		cout<<"\n\nEnter field to modify";
		cout<<"\n1. Name";
		cout<<"\n2. Email";
		cout<<"\n3. Phone Number";
		cout<<"\n4. Exit without changes?\n\nEnter choice: ";
		cin>>input;
			if((input>=1)&&(input<=4))
		{
		getline(std::cin,x2);
		switch(input)
		{
			case 1: cout<<"\nEnter New Name: ";
				 getline(std::cin,name);
				 break;
			case 2: cout<<"\nEnter New Email: ";
				 cin>>email;
				while((strstr(email.c_str(),emailstr1.c_str())==NULL) || (strstr(email.c_str(),emailstr2.c_str())) || (strstr(email.c_str(),emailstr3.c_str())) )
         			{
					cout << "\n\nInvalid Email";
 					cout << "\nEmail  not  accepted.\n";
					email='0';
					cout<<"\nEnter Email Again: ";
					cin>>email;
			       }
				 break;
			case 3: cout<<"\nEnter New Phone: ";
			     	 cin>>phone;
			     	 x=atoi(phone.c_str());

		  		 while((x < 1000000000)||(x > 9999999999))
				 {
  					cout<<"\nInvalid\n";
  					phone='0';
  					cout<<"\nEnter Phone Again: ";
  					cin>>phone;
  					x=atoi(phone.c_str());
				 }
				 break;
			default: return;
		}

		}

		else
		{
			cout<<"\n wrong input";
			modify_student();
		}
	}
}

void modify_book()
{
	system("CLS");
	string bookid_srch,seg;
	int i=0,srchflag=-1,modifyflag=-1,count;
	cout<<"\n\n\tEnter BOOKID: ";
	cin>>bookid_srch;
	fp.open("book2.txt",ios::in);
	srchflag=bin_srch_book(bookid_srch);
	if(!fp)
	{
		error_type=1;
		error(error_type);
		getch();
		admin_menu_book();
	}
	while(fp)
	{
		bk1[i].unpackbook();
		if(bk1[i].book_id[0]=='*')
			continue;
		i++;
	}
		if(bk1[i].book_id[0]=='*')
		 --i;
	fp.close();
	if(srchflag==-1)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_book();
	}
	cout<<"\nRECORD FOUND";
	int pos = i2[srchflag].address;
	fp.open("book2.txt",ios::in);
	fp.seekg(pos,ios::beg);
	getline(fp,bk.book_id,'|');
	getline(fp,bk.bname,'|');
	getline(fp,bk.aname,'|');
	getline(fp,bk.pname,'|');
	getline(fp,bk.year,'|');
	getline(fp,bk.copies,'|');
	getline(fp,seg);
	fp.close();
	bk.show_book();
	cout<<"\n\nDo you wish to modify?\n Enter 0 to cancel and 1 otherwise ";
	cin>>modifyflag;
	if(modifyflag)
	{
		bk.modifyb();
		fp.open("book2.txt",ios::out);
		if(!fp)
		{
			cout<<"\nERROR! cannot open file!";
		}
		for(i=0;i<=cntbook;i++)
		{
			if (bk1[i].book_id==bk.book_id)
			{
				bk.packbook();

			}
			else
				bk1[i].packbook();
		}
		fp.close();
	}
	create_bookindex();
//	bookid_token=0;

}

void book::modifyb()
{
		int input,x,y;
   while(1) {
 		cout<<"\n\nEnter field to modify";
		cout<<"\n1. book name";
		cout<<"\n2. Author Name";
		cout<<"\n3. Publication name";
		cout<<"\n4. Year";
		cout<<"\n5. No of copies";
		cout<<"\n6. Exit without changes?\n\nEnter choice: ";
		cin>>input;
	if((input>=1)&&(input<=6))
	{
		switch(input)
		{

			case 1: cout<<"\nEnter New bookname: ";
				 cin>>bname;
				 break;
			case 2: cout<<"\nEnter New authorname: ";
				 cin>>aname;
				 break;
			case 3: cout<<"\nEnter New Publication name: ";
				 cin>>pname;
				 break;
		       case 4: cout<<"\nEnter New year: ";
				 getline(std::cin,year);
				 x=atoi(year.c_str());
				 while((x < 1900)||(x > 2018))
		  		{
  				cout<<"\nInvalid\n";
  				year='0';
  				cout<<"\nEnter year: ";
  				getline(std::cin,year);
  				x=atoi(year.c_str());
				}
				 break;
			case 5: cout<<"\nEnter New copies: ";
				 cin>>copies;
				 y=atoi(copies.c_str());
				 while((y < 1)||(y > 50))
		  		{
  				cout<<"\nInvalid";
  				copies='0';
  				cout<<"\nEnter Copies: ";
  				getline(std::cin,copies);
  				y=atoi(copies.c_str());
				 }
				 break;
			default: return;
		}

	}

	else
	{
		cout<<"\n wrong input";
		modify_book();
	}
}

}


void delete_student()
{
	string usn_srch,a;
	string strd,strm,stry;
	system("CLS");
	cout<<"\nEnter USN of Student: ";
	cin>>usn_srch;

	int pos=bin_srch(usn_srch);
	if(pos==-1)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_student();
	}
	
	usntoken=0;
	
	int z=bin_srch_issue(usn_srch);
	if(z!=-1)
	{
		int posx = i3[z].addr;
		fp.open("issue2.txt",ios::in);
		fp.seekg(posx,ios::beg);
		issueb.unpackissue();
		a='0';
		if(issueb.book1.compare(a)!=0)
		{
			cout<<"\n\n Book No. Issued: "<<issueb.book1;
			stry=issueb.time1.substr(0,4);
			strm=issueb.time1.substr(4,2);
			strd=issueb.time1.substr(6,2);
			cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;
		}
				
		if(issueb.book2.compare(a)!=0)
		{
			cout<<"\n\n Book No. Issued: "<<issueb.book2;
			stry=issueb.time2.substr(0,4);
			strm=issueb.time2.substr(4,2);
			strd=issueb.time2.substr(6,2);
			cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;
		}
		if(issueb.book3.compare(a)!=0)
		{
			cout<<"\n\n Book No. Issued: "<<issueb.book3;
			stry=issueb.time3.substr(0,4);
			strm=issueb.time3.substr(4,2);
			strd=issueb.time3.substr(6,2);
			cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;
		}	

		if(issueb.book3.compare(a)!=0 || issueb.book2.compare(a)!=0 || issueb.book1.compare(a)!=0)
		{
			cout<<"\n\n PLEASE RETURN THESE BOOKS TO DELETE STUDENT RECORD!";
			fp.close();
			getch();
			admin_menu_student();	
		}
	}
	
	fp.close();	
	cout<<"\nRecord Found And Deleted";
	fp.open("student2.txt",ios::out|ios::in);
	fp.seekp(i1[pos].addr,ios::beg);
	fp.put('*');
	fp.close();
	for(int i=pos;i<=cnt;i++)
	{
		i1[i].usn=i1[i+1].usn;
		i1[i].addr=i1[i+1].addr;

	}
	cnt--;
	usntoken=0;
	create_stuindex();
	getch();
}

void delete_book()
{

	string bookid_srch;
	system("CLS");
	cout<<"\nEnter Book ID to search: ";
	cin>>bookid_srch;
	int pos=bin_srch_book(bookid_srch);
	if(pos==-1)
	{
		error_type=4;
		error(error_type);
		getch();
		admin_menu_book();
	}
	cout<<"\nRecord found and deleted";
	book_idtoken=0;
	fp.open("book2.txt",ios::out|ios::in);
	fp.seekp(i2[pos].address,ios::beg);
	fp.put('*');
	fp.close();
	for(int i=pos;i<=cntbook;i++)
	{
		i2[i].book_id=i2[i+1].book_id;
		i2[i].address=i2[i+1].address;

	}
	cnt--;
	create_bookindex();
	getch();
}

void display_alls()
{
	fstream fpd;
	int pos;
	system("CLS");
	fpd.open("student2.txt",ios::in);
		if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}
	cout<<"===============================================================================================\n";
		cout<<"\tUSN"<<setw(20)<<"\tName"<<setw(20)<<"Book Issued\n";
	cout<<"==============================================================================================\n";
	while(fpd)
	{	int pos;
		string seg;
		getline(fpd,st.usn,'|');
		getline(fpd,st.name,'|');
		getline(fpd,st.email,'|');
		getline(fpd,st.phone,'|');
		getline(fpd,st.stbno,'|');
		getline(fpd,seg);
		if(st.usn.length()>0&&st.usn[0]!='*')
			cout<<"\t"<<st.usn<<setw(15)<<st.name<<setw(15)<<st.stbno<<endl;


	}
	getch();
	//fpd.seekg(pos,ios::beg);
	fpd.close();
}


void display_allb()
{
	fstream fpd;
	int pos;
	system("CLS");
	fpd.open("book2.txt",ios::in);
		if(!fp)
	{
		cout<<"CANNOT OPEN FILE.";
		getch();
		return;
	}
	cout<<"===============================================================================================\n";
	cout<<"  BOOK_ID"<<setw(20)<<"\tBOOK Name"<<setw(20)<<"Author"<<setw(20)<<"No. of Books";
	cout<<"\n==============================================================================================\n";
	while(fpd)
	{	int pos;
		string seg;
		getline(fpd,bk.book_id,'|');
		getline(fpd,bk.bname,'|');
		getline(fpd,bk.aname,'|');
		getline(fpd,bk.pname,'|');
		getline(fpd,bk.year,'|');
		getline(fpd,bk.copies,'|');
		getline(fpd,seg);
		if(bk.book_id.length()>0 && bk.book_id[0]!='*')
			cout<<" "<<bk.book_id<<setw(20)<<bk.bname<<setw(25)<<bk.aname<<setw(20)<<bk.copies<<endl;
	}
	getch();
	//fpd.seekg(pos,ios::beg);
	fpd.close();
}



void issue()
{
	string usn_srch,bookid_srch;
	int i=0,j=0,k=0,x,y,z;
	cout<<"\n BOOK ISSUE ";
	cout<<"\n\nPlease Enter USN: ";
	cin>>usn_srch;

	x=bin_srch(usn_srch);
	if(x == -1)
	{
		error_type=4;
		error(error_type);
		getch();
		main_menu();
	}


	cout<<"\nPlease Enter BOOKID: ";
	cin>>bookid_srch;
	y=bin_srch_book(bookid_srch);
	if(y == -1)
	{
		error_type=4;
		error(error_type);
		getch();
		main_menu();
	}

	fp.open("issue2.txt",ios::in|ios::out);
	z=bin_srch_issue(usn_srch);
	while(fp)
	{

		issueb1[i].unpackissue();
		if(issueb1[i].usn[0]=='*')
			continue;
		i++;
	}

	if(issueb1[i].usn[0]=='*')
			i--;

	fp.close();
//issue close


//book open
	fp.open("book2.txt",ios::in|ios::out);

	while(fp)
	{
		string buf;
		getline(fp,bk1[k].book_id,'|');
		getline(fp,bk1[k].bname,'|');
		getline(fp,bk1[k].aname,'|');
		getline(fp,bk1[k].pname,'|');
		getline(fp,bk1[k].year,'|');
		getline(fp,bk1[k].copies,'|');
		getline(fp,buf);
		if(bk1[k].book_id[0]=='*')
			continue;
		k++;
	}
	if(bk1[k].book_id[0]=='*')
		--k;

	fp.close();
//book close

//student open
	fp.open("student2.txt",ios::in|ios::out);
	while(fp)
	{
		st1[j].unpack();
		if(st1[j].usn[0]=='*')
			continue;
		j++;
	}
	if(st1[j].usn[0]=='*')
	--j;

	fp.close();
//student close

	if(z == -1)
	{
		fp.open("issue2.txt",ios::app|ios::out);
		issueb.usn=i1[x].usn;
		issueb.time1='0';
		issueb.time2='0';
		issueb.time3='0';
		issueb.book1='0';
		issueb.book2='0';
		issueb.book3='0';
		string buf=issueb.usn+'|'+issueb.book1+'|'+issueb.book2+'|'+issueb.book3+'|'+issueb.time1+'|'+issueb.time2+'|'+issueb.time3+'|';
		fp<<buf<<endl;
		fp.close();
	}

//issue open
	fp.open("issue2.txt",ios::in|ios::out);
	i=0;
	while(fp)
	{

		issueb1[i].unpackissue();
		if(issueb1[i].usn[0]=='*'||issueb1[i].usn[0]==' ')
			continue;
		i++;
	}
	if(issueb1[i].usn[0]=='*'||issueb1[i].usn[0]==' ')
		--i;
	fp.close();

//issue close
	create_issueindex();
	z=bin_srch_issue(usn_srch);

	string a,b,c;
	a='0';
	int pos = i3[z].addr;
	int pos1 = i1[x].addr;
	int pos2 = i2[y].address;

//open file loc for issue
	fp.open("issue2.txt",ios::in);
	fp.seekg(pos,ios::beg);
	issueb.unpackissue();
	fp.close();

//open file loc for student
	fp.open("student2.txt",ios::in);
	fp.seekg(pos1,ios::beg);
	st.unpack();
	fp.close();

//open file loc for book
	fp.open("book2.txt",ios::in);
	fp.seekg(pos2,ios::beg);
	bk.unpackbook();
	fp.close();

//function for comparing

	int nb_flag=0,copies_flag=0;

	copies_flag=atoi(bk.copies.c_str());
	nb_flag=atoi(st.stbno.c_str());

	if(copies_flag==0)
	{
		cout<<"\n\n\tSORRY! NO MORE BOOKS LEFT!";
		getch();
		main_menu();
	}

	if(nb_flag>=3)
	{
		cout<<"\n\n\tPLEASE RETURN PREVIOUS BOOKS!";

		if (issueb.book1==i2[y].book_id ||issueb.book2==i2[y].book_id || issueb.book3==i2[y].book_id )
		{
			cout<<"\n\n\tBOOK ALREADY ISSUED!";
		}
		getch();
		main_menu();
	}
	
	if (issueb.book1==i2[y].book_id ||issueb.book2==i2[y].book_id || issueb.book3==i2[y].book_id )
	{
		cout<<"\n\n\tBOOK ALREADY ISSUED!";
		getch();
		main_menu();
	}
	timeis();
	if((issueb.book1).compare(a) == 0)
	{
		issueb.book1=i2[y].book_id;
		nb_flag+=1;
		copies_flag--;
		issueb.time1=timebuf;
	}
	else
	{
		if((issueb.book2).compare(a) == 0)
		{
			issueb.book2=i2[y].book_id;
			nb_flag+=1;
			copies_flag--;
			issueb.time2=timebuf;
		}
		else
		{
			if((issueb.book3).compare(a) == 0)
			{
			issueb.book3=i2[y].book_id;
			nb_flag+=1;
			copies_flag--;
			issueb.time3=timebuf;
			}
		}
	}
	timebuf='0';
	string buf;
	fp.open("issue2.txt",ios::in|ios::out);
	for(int l=0;l<=cntissue;l++)
	{
		if (issueb1[l].usn==issueb.usn)
		buf=issueb.usn+'|'+issueb.book1+'|'+issueb.book2+'|'+issueb.book3+'|'+issueb.time1+'|'+issueb.time2+'|'+issueb.time3+'|';
		else
		buf=issueb1[l].usn+'|'+issueb1[l].book1+'|'+issueb1[l].book2+'|'+issueb1[l].book3+'|'+issueb1[l].time1+'|'+issueb1[l].time2+'|'+issueb1[l].time3+'|';
		fp<<buf<<endl;
	}
	fp.close();
	
	char stringbook[100],stringstudent[100];

	itoa(copies_flag,stringbook,10);
	itoa(nb_flag,stringstudent,10);


	bk.copies=stringbook;
	st.stbno=stringstudent;

	fp.open("student2.txt",ios::in|ios::out);
	for(int l=0;l<=cnt;l++)
	{
		if (st1[l].usn==st.usn)
			st.pack();
		else
			st1[l].pack();
	}
	fp.close();

	fp.open("book2.txt",ios::in|ios::out);
	
	for(int l=0;l<=cntbook;l++)
	{
		if (bk1[l].book_id==bk.book_id)
			bk.packbook();
		else
			bk1[l].packbook();
	}
	fp.close();

	cout<<"\n BOOK ISSUED, RETURN WITHIN 14 DAYS!";

	create_issueindex();
	getch();

}


void deposit()
{

	string usn_srch,bookid_srch;
	int i=0,j=0,k=0,x,y,z;
	cout<<"\n BOOK DEPOSIT ";
	cout<<"\n\nPlease Enter USN: ";
	cin>>usn_srch;

	x=bin_srch(usn_srch);
	if(x == -1)
	{
		error_type=4;
		error(error_type);
		getch();
		main_menu();
	}

	cout<<"\nPlease Enter BOOKID: ";
	cin>>bookid_srch;
	y=bin_srch_book(bookid_srch);
	if(y == -1)
	{
		error_type=4;
		error(error_type);
		getch();
		main_menu();
	}

	fp.open("issue2.txt",ios::in|ios::out);
	z=bin_srch_issue(usn_srch);
	while(fp)
	{

		issueb1[i].unpackissue();
		if(issueb1[i].usn[0]=='*')
			continue;
		i++;
	}

	if(issueb1[i].usn[0]=='*')
			i--;

	fp.close();
//issue close


//book open
	fp.open("book2.txt",ios::in|ios::out);

	while(fp)
	{
		string buf;
		getline(fp,bk1[k].book_id,'|');
		getline(fp,bk1[k].bname,'|');
		getline(fp,bk1[k].aname,'|');
		getline(fp,bk1[k].pname,'|');
		getline(fp,bk1[k].year,'|');
		getline(fp,bk1[k].copies,'|');
		getline(fp,buf);
		if(bk1[k].book_id[0]=='*')
			continue;
		k++;
	}
	if(bk1[k].book_id[0]=='*')
		--k;

	fp.close();
//book close

//student open
	fp.open("student2.txt",ios::in|ios::out);
	while(fp)
	{
		st1[j].unpack();
		if(st1[j].usn[0]=='*')
			continue;
		j++;
	}
	if(st1[j].usn[0]=='*')
	--j;

	fp.close();
//student close

	if(z == -1)
	{
		fp.open("issue2.txt",ios::app|ios::out);
		issueb.usn=i1[x].usn;
		issueb.time1='0';
		issueb.time2='0';
		issueb.time3='0';
		issueb.book1='0';
		issueb.book2='0';
		issueb.book3='0';
		string buf=issueb.usn+'|'+issueb.book1+'|'+issueb.book2+'|'+issueb.book3+'|'+issueb.time1+'|'+issueb.time2+'|'+issueb.time3+'|';
		fp<<buf<<endl;
		fp.close();
	}

//issue open
	fp.open("issue2.txt",ios::in|ios::out);
	i=0;
	while(fp)
	{

		issueb1[i].unpackissue();
		if(issueb1[i].usn[0]=='*'||issueb1[i].usn[0]==' ')
			continue;
		i++;
	}
	if(issueb1[i].usn[0]=='*'||issueb1[i].usn[0]==' ')
		--i;
	fp.close();

//issue close
	create_issueindex();
	z=bin_srch_issue(usn_srch);

	string a,b,c;
	a='0';
	int pos = i3[z].addr;
	int pos1 = i1[x].addr;
	int pos2 = i2[y].address;

//open file loc for issue
	fp.open("issue2.txt",ios::in);
	fp.seekg(pos,ios::beg);
	issueb.unpackissue();
	fp.close();

//open file loc for student
	fp.open("student2.txt",ios::in);
	fp.seekg(pos1,ios::beg);
	st.unpack();
	fp.close();

//open file loc for book
	fp.open("book2.txt",ios::in);
	fp.seekg(pos2,ios::beg);
	bk.unpackbook();
	fp.close();

//function for comparing

	int nb_flag=0,copies_flag=0;
	string strm,strd,stry;
	copies_flag=atoi(bk.copies.c_str());
	nb_flag=atoi(st.stbno.c_str());

	if(nb_flag==0)
	{
		cout<<"\n\n\tNO BOOK TO DEPOSIT";
		getch();
		main_menu();
	}

	if (issueb.book1==i2[y].book_id || issueb.book2==i2[y].book_id || issueb.book3==i2[y].book_id)
	{


	if((issueb.book1).compare(i2[y].book_id) == 0)
	{
		issueb.book1=a;
		nb_flag--;
		copies_flag++;
	/*	stry=issueb.time1.substr(0,4);
		strm=issueb.time1.substr(4,2);
		strd=issueb.time1.substr(6,2);
		cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;  */
	}
	else
	{
		if((issueb.book2).compare(i2[y].book_id) == 0)
		{
			issueb.book2=a;
			nb_flag--;
			copies_flag++;
		/*	stry=issueb.time2.substr(0,4);
			strm=issueb.time2.substr(4,2);
			strd=issueb.time2.substr(6,2);
			cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;	*/
		}
		else
		{
			if((issueb.book3).compare(i2[y].book_id) == 0)
			{
				issueb.book3=a;
				nb_flag--;
				copies_flag++;
			/*	stry=issueb.time2.substr(0,4);
				strm=issueb.time2.substr(4,2);
				strd=issueb.time2.substr(6,2);
				cout<<"\n Issued On: "<<strd<<"/"<<strm<<"/"<<stry;	*/		
			}
		}
	}
/*	stry.clear();
	strm.clear();
	strd.clear();
*/	

	string buf;
	fp.open("issue2.txt",ios::in|ios::out);
	for(int l=0;l<=cntissue;l++)
	{
		if (issueb1[l].usn==issueb.usn)
			buf=issueb.usn+'|'+issueb.book1+'|'+issueb.book2+'|'+issueb.book3+'|'+issueb.time1+'|'+issueb.time2+'|'+issueb.time3+'|';
		else
			buf=issueb1[l].usn+'|'+issueb1[l].book1+'|'+issueb1[l].book2+'|'+issueb1[l].book3+'|'+issueb1[l].time1+'|'+issueb1[l].time2+'|'+issueb1[l].time3+'|';
		fp<<buf<<endl;
	}
	fp.close();

	char stringbook[100],stringstudent[100];

	itoa(copies_flag,stringbook,10);
	itoa(nb_flag,stringstudent,10);

	st.stbno=stringstudent;

	fp.open("student2.txt",ios::in|ios::out);
	for(int l=0;l<=cnt;l++)
	{
		if (st1[l].usn==st.usn)
			st.pack();
		else
			st1[l].pack();
	}
	fp.close();

	fp.open("book2.txt",ios::in|ios::out);
	bk.copies=stringbook;

	for(int l=0;l<=cntbook;l++)
	{
		if (bk1[l].book_id==bk.book_id)
			bk.packbook();
		else
			bk1[l].packbook();
	}
	fp.close();

	cout<<"\n\n\tBOOK RETURN SUCCESSFUL";
	}

	else
	{
		cout<<"\n\n\tSORRY! YOU HAVE NOT ISSUED THIS BOOK YET!";
		getch();
		main_menu();
	}


	create_issueindex();
	getch();

}


void intro()
{
	system("CLS");
	gotoxy(35,11);
	cout<<"LIBRARY";
	gotoxy(35,14);
	cout<<"MANAGEMENT";
	gotoxy(35,17);
	cout<<"SYSTEM";
	cout<<"\n\nMADE BY :\n\n 1.Abhishek Yadav \n\n 2.Obaid Ur Rehman \n\n 3.Sandesh Jain";

	getch();
	system("CLS");
}

//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu_student()
{
	system("CLS");
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1. CREATE STUDENT RECORD";
	cout<<"\n\n\t2. VIEW ALL STUDENTS RECORD";
	cout<<"\n\n\t3. VIEW SPECIFIC STUDENT BY USN ";
	cout<<"\n\n\t4. VIEW SPECIFIC STUDENT BY NAME";
	cout<<"\n\n\t5. MODIFY STUDENT RECORD";
	cout<<"\n\n\t6. DELETE STUDENT RECORD";
	cout<<"\n\n\t7. BACK TO MAIN MENU";
	cout<<"\n\n\t8. EXIT ";
	cout<<"\n\n\tPlease Enter Your Choice (1-8): ";
	std::cin>>ch2;
	switch(ch2)
	{
		case 1: system("CLS");
			 st.create_student();
		    	 write_student();break;
		case 2: display_alls();break;
		case 3: display_sps(); break;
		case 4: displayspecificstudentbyname();
     		        break;
		case 5: modify_student();break;
		case 6: delete_student();break;
		case 7: main_menu(); break;
		case 8: exit(0);
		default:admin_menu_student();
	}
	admin_menu_student();
}

void admin_menu_book()
{

	system("CLS");
	int ch2;
	cout<<"\n\n\t1. CREATE BOOK RECORD ";
	cout<<"\n\n\t2. VIEW ALL BOOKS ";
	cout<<"\n\n\t3. VIEW SPECIFIC BOOK BY ID";
	cout<<"\n\n\t4. VIEW SPECIFIC BOOK RECORD BY NAME";
	cout<<"\n\n\t5. MODIFY BOOK ";
	cout<<"\n\n\t6. DELETE BOOK ";
	cout<<"\n\n\t7. BACK TO MAIN MENU";
	cout<<"\n\n\t8. EXIT";
	cout<<"\n\n\tPlease Enter Your Choice (1-7): ";
	cin>>ch2;
	switch(ch2)
	{
		case 1: system("CLS");
		  	 bk.create_book();
			 write_book();
			 break;
		case 2: display_allb();break;
		case 3: display_spbook();break;
		case 4: displayspecificbookbyname();break;
		case 5: modify_book(); break;
		case 6: delete_book(); break;
		case 7: main_menu(); break;
		case 8: exit(0);
		default: admin_menu_book();
	}
	admin_menu_book();
}

void view_index()
{
	int ch;
	do{
		system("CLS");
		cout<<"\n\n\n\tINDEX";
		cout<<"\n\n\t1. VIEW STUDENT INDEX";
		cout<<"\n\n\t2. VIEW BOOK INDEX";
		cout<<"\n\n\t3. VIEW ISSUEING INDEX";
		cout<<"\n\n\t4. RETURN TO ADMIN";
		cout<<"\n\n\t5. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-4) ";
		ch=getche();
		switch(ch)
		{
			case '1': view_stuindex();
				   break;
			case '2': view_bookindex();
				   break;
		 	case '3': view_issueindex();
  				   break;
  			case '4': main_menu();
  				   break;
			case '5': exit(0);
			default : main_menu();
		}
	}while(ch<='5');

}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main_menu()
{
	char ch;
	do
	{
		system("CLS");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
		cout<<"\n\n\t03. STUDENT ADMIN";
		cout<<"\n\n\t04. BOOK ADMIN";
		cout<<"\n\n\t05. VIEW INDEXES";
		cout<<"\n\n\t06. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-5) ";
		ch=getche();
		switch(ch)
		{
			case '1': system("CLS");
				   issue();
				   break;
			case '2': system("CLS");
				   deposit();
				   break;
			case '3': admin_menu_student();
				   break;
		 	case '4': admin_menu_book();
       			   break;
		 	case '5': view_index();
       			   break;
			case '6': exit(0);
			default : exit(0);
		}
	}while(ch!='7');
	return 0;
}


void passcheck()
{
	system("CLS");
	char pwd[5],def[]="logic";
	int i=0,mycheck;
	gotoxy(35,11);
	cout<<"PLEASE ENTER PASSWORD: ";
	while(i<5)
	{
	pwd[i]=getch();
	cout<<"*";
	++i;
	}
	cout<<endl;
	mycheck=passcheck2(pwd,def);
	if (mycheck==1)
	{
		gotoxy(35,13);
		cout<<"ACCESS GRANTED"<<endl;
	}
	else
	{
 		gotoxy(35,13);
		cout<<"ACCESS DENIED"<<endl;
		getch();
		exit(0);	
	}
	getch();

}

int passcheck2(char a[5],char b[5])
{
	int i;
    for(i=0;i<5;i++)
    {
        if(a[i]!=b[i])
        {
        break;
        }
    }
    if(i==5)
    return 1;
    else
    return 0;
}

int main()
{
	passcheck();
	intro();
	create_stuindex();
	create_bookindex();
	create_issueindex();
	main_menu();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************

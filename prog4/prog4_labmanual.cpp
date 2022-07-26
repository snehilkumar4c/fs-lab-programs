#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<values.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
using namespace std;
fstream fp;
int n=0;
char fname[10],index[10];

class student
{
    private:
		     char name[15],usn[15],branch[5];
    public:
  	     void pack();
  	     void unpack(char[]);
  	     void display();
 	     void searchbyrrn();
};

void student::pack()
{
    char buffer[100];
    cout<<"Enter the student USN, Name and Branch:";
    cin>>usn>>name>>branch;
    strcpy(buffer,usn);
    strcat(buffer,"|");
    strcat(buffer,name);
    strcat(buffer,"|");
    strcat(buffer,branch);
    strcat(buffer,"|");
    index[n-1] = fp.tellg();
    fp<<buffer;
    fp<<"\n";
}

void student::unpack(char buffer[])
{
    cout<<buffer;
    char *t;
    t = strtok(buffer,"|");
    cout<<"\nUSN : "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"Name : "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"Branch :"<<t<<endl;
}

void student::display()
{
    char buffer[100];
    int i,j;
    cout<<"\nFile Contents are \n";
    fp.open(fname,ios::in);
    for(i=1;i<=n;i++)
    {
        fp>>buffer;
        unpack(buffer);
    }
    fp.close();
}

void student::searchbyrrn()
{
    int rrn;
    char buffer[30];
    cout << "\nEnter RRN of the record:";
    cin>>rrn;
    fp.open(fname,ios::in);
    if(rrn > n-1)
    {
        cout <<"Record with RRN "<<rrn<<" was not found..\n";
        fp.close();
        return;
    }
    fp.seekg(index[rrn],ios::beg);
    fp>>buffer;
    unpack(buffer);
    fp.close();
    return;
}

int main()
{
    int i,ch;
    student s1;
    cout<<"\nEnter the Filename:";
    cin>>fname;
    fp.open(fname,ios::out|ios::trunc);
    fp.close();
    for(;;)
    { 
        cout<<"\n 1.Insert \n 2.Display \n 3.Search By RRN \n 4.Exit \n";
        cout<<"Enter your Choice:";
        cin>>ch;
        switch(ch)
        {
	           case 1:
		           n++;
		           fp.open(fname,ios::out|ios::ate);
 	           s1.pack();
		           fp.close();
		           break;
	          case 2:
		           s1.display();
		           break;
	          case 3:
		           s1.searchbyrrn();
		           break;
	                       default:
	 	           exit(0);
        }
   }
   return 0;
}


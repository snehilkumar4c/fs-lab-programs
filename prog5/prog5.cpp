#include<iostream>
#include<process.h>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<stdio.h>

using namespace std;

fstream fp;
int recount = 0;
char fname[10];

class student {
    private: char usn[15], name[15], branch[5];
    public: void pack(char[]);
            void unpack(char[]);
            void display();
            void insrec();
            void delrec();
            int search(char[]);
};

struct memindex {
    char key[15];
    int offset;
};

memindex index[10];

void student::pack(char buffer[]) {
    // char buffer[100];

    cout<<"enter the usn, name and branch: \n";
    cin>>usn>>name>>branch;

    strcpy(buffer,usn);
    strcat(buffer,"|");
    strcat(buffer,name);
    strcat(buffer,"|");
    strcat(buffer,branch);
    strcat(buffer,"|");
}

void student::unpack(char buffer[]) {
    char *t;
    t = strtok(buffer, "|");
    cout<<"usn: "<<t<<endl;
    t = strtok(buffer, "|");
    cout<<"name: "<<t<<endl;
    t = strtok(buffer, "|");
    cout<<"branch: "<<t<<endl;
}

void student::insrec() {
    char buffer[50],tem[50];
    char *usn;
    int i,j;
    fp.open(fname,ios::out|ios::ate);
    pack(buffer);
}
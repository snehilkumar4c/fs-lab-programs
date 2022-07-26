#include<iostream>
#include<values.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>

using namespace std;

fstream fp;
int n = 0;
char fname[10], index[10];

class student {
    private: char usn[15], name[15], branch[5];
    public: void pack();
            void unpack(char[]);
            void display();
            void searchbyrrn();
};

void student::pack() {
    char buffer[100];

    cout<<"enter the usn, name and branch: \n";
    cin>>usn>>name>>branch;

    strcpy(buffer,usn);
    strcat(buffer,"|");
    strcat(buffer, name);
    strcat(buffer,"|");
    strcat(buffer, branch);
    strcat(buffer,"|");

    index[n-1] = fp.tellg();
    fp<<buffer;
    fp<<"\n";
}

void student::unpack(char buffer[]) {
    char *t;
    t = strtok(buffer,"|");
    cout<<"\n usn: "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"\n name: "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"\n branch: "<<t<<endl;
}

void student::display() {
    char buffer[100];
    int i;
    cout<<"file contents are: \n";
    fp.open(fname,ios::in);
    for(i = 0; i < n; i++) {
        fp>>buffer;
        unpack(buffer);
    }
    fp.close();
}

void student::searchbyrrn() {
    int rrn;
    char buffer[30];

    cout<<"enter rrn of record: \n";
    cin>>rrn;

    fp.open(fname, ios::in);
    if(rrn > n-1) {
        cout<<"record of rrn "<<rrn<<"was not found";
        fp.close();
        return;
    }
    fp.seekg(index[rrn],ios::beg);
    fp>>buffer;
    unpack(buffer);
    fp.close();
    return;
}

int main() {
    student s1;
    int i,ch;
    cout<<"enter the filename: "<<endl;
    cin>>fname;

    fp.open(fname, ios::out|ios::trunc);
    fp.close();
    for(;;) {
        cout<<"\n1.insert\n2.display\n3.search\n4.exit"<<endl;
        cout<<"enter choice: \n";
        cin>>ch;
        switch (ch)
        {
            case 1: n++;
                    fp.open(fname,ios::out|ios::ate);
                    s1.pack();
                     fp.close(); break;
            case 2: s1.display(); break;
            case 3: s1.searchbyrrn(); break;
            case 4: exit(0);        
            default: cout<<"invalid choice"; break;
        }
    }
}
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<process.h>

using namespace std;

fstream fp1,fp2;
int n = 0;
char fname[10];

class student {
    private: char usn[15], name[15], branch[5];
    public: void pack(int);
            void unpack(char[]);
            void display();
            void search();
};

void student::pack(int a) {
    char buffer[100];

    cout<<"enter usn, name, branch: \n";
    cin>>usn>>name>>branch;
    
    strcpy(buffer, usn);
    strcat(buffer, "|");
    strcat(buffer, name);
    strcat(buffer, "|");
    strcat(buffer, branch);
    strcat(buffer, "|");

    if(a == 1) {
        fp1<<buffer;
        fp1<<"\n";
    }
    else {
        fp2<<buffer;
        fp2<<"\n";
    }
}

void student::unpack(char buffer[]) {
    char *t;

    t = strtok(buffer,"|");
    cout<<"usn: "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"name: "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"branch: "<<t<<endl;
}

void student::display() {
    char buffer[100];

    cout<<"File contents are: "<<endl;
    fp1.open(fname, ios::in);

    for(int i = 1; i <= n; i++) {
        fp1>>buffer;
        unpack(buffer);
    }
    fp1.close();
}

void student::search(){
    char buffer[100], temp[100];
    char *usn;
    char key[15];
    int ch;

    cout<<"enter the usn to be searched: \n";
    cin>>key;

    fp1.open(fname,ios::in);
    fp2.open("out.txt",ios::out);

    for(int i = 1; i <= n; i++) {    //check for i = 0 also after execution
        fp1>>buffer;
        strcpy(temp, buffer);
        usn = strtok(buffer, "|");

        if(strcmp(usn, key) == 0) {
            cout<<"record found";
            unpack(buffer); 
            cout<<"want to modify"<<endl;
            cout<<"enter choice: \n1.yes \n2.no \n";
            cin>>ch;

            if(ch == 1) {
                pack(2);
                while(!fp1.fail()){
                    fp1>>buffer;
                    fp2<<buffer<<"\n";
                }
                fp1.close();
                fp2.close();
                remove(fname);
                rename("out.txt", fname);
                return;
            }
            else {
                fp1.close();
                fp2.close();
                remove("out.txt");
            }
        }
        else {
            fp2<<buffer<<"\n";
        }
    }
    cout<<"no records found";
    fp1.close();
    fp2.close();
    remove("out.txt");
}

int main() {
    student s1;
    int ch;

    cout<<"enter the filename: "<<endl;
    cin>>fname;

    fp1.open(fname, ios::out|ios::trunc);
    fp1.close();

    for(;;) {
        cout<<"\n1.insert\n2.display\n3.search\n4.exit"<<endl;
        cout<<"enter choice: "<<endl;
        cin>>ch;

        switch (ch)
        {
        case 1: n++;
                fp1.open(fname,ios::app);
                s1.pack(1);
                fp1.close();
            break;
        case 2: s1.display(); break;
        case 3: s1.search(); break;
        case 4: exit(0);        
        default: cout<<"invalid choice";
            break;
        }
    }
    return 0;
}
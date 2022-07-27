#include<iostream>
#include<string.h>
#include<process.h>
#include<conio.h>
#include<fstream>

using namespace std;

fstream fp;
int n = 0;
char fname[10];

class student {
    private: char usn[15], name[15], branch[5];
    public: void pack();
            void unpack(char[]);
            void display();
            void search();
};

void student::pack() {
    char buffer[100];
    cout<<"enter usn, name and branch: \n";
    cin>>usn>>name>>branch;
    strcpy(buffer,usn);
    strcat(buffer,"|");
    strcat(buffer,name);
    strcat(buffer,"|");
    strcat(buffer,branch);
    strcat(buffer,"|");

    int len = strlen(buffer);
    while(len < 27) {
        strcat(buffer, "#");
        len++;
    }

    buffer[27] = '\0';
    fp<<buffer<<"\n";
}

void student::unpack(char buffer[]) {
    char *t;
    t = strtok(buffer,"|");
    cout<<"usn: \n"<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"name: \n"<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"branch: \n"<<t<<endl;
}

void student::display() {
    char buffer[100];
    
    if(n == 0) {
        cout<<"no records";
        return;
    }
    cout<<"file contents: \n";
    fp.open(fname,ios::in);
    for(int i = 0; i < n; i++) {
        fp>>buffer;
        unpack(buffer);
        cout<<"\n";
    }
    fp.close();
}

void student::search() {
    char buffer[100], temp[100];
    char *usn;
    char key[15];
    int ch;

    cout<<"enter usn to search: \n";
    cin>>key;

    fp.open(fname,ios::in);
    for(int i = 0; i < n; i++) {
        fp>>buffer;
        strcpy(temp, buffer);
        usn = strtok(buffer, "|");
        if(strcmp(key, usn) == 0) {
            cout<<"record found";
            unpack(buffer);
            cout<<"want to modify?";
            cout<<"enter choice: \n1.yes\n2.no\n";
            cin>>ch;

            if(ch == 1) {
                fp.seekp(-27, ios::cur);
                pack();
            }
            fp.close();
            return;
        }
        cout<<"no records";
        fp.close();
        return;
    }
}

int main() {
    int i,ch;
    student s1;
    
    cout<<"Enter the filename: ";
    cin>>fname;

    fp.open(fname,ios::out|ios::trunc);
    fp.close();
    for(;;) {
        cout<<"\n1.Insert \n2.Display \n3.search and modify \n4.exit";
        cout<<"enter choice";
        cin>>ch;

        switch (ch)
        {
        case 1: n++;
                fp.open(fname,ios::app);
                s1.pack();
                fp.close();
                break;
        case 2: s1.display(); break;
        case 3: s1.search(); break;
        case 4: exit(0);
        default: cout<<"invalid input"; break;
        }
    }
}

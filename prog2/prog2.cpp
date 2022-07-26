#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<process.h>

using namespace std;

fstream fp;
int n = 0;
char fname[10];

class student {
    private: char usn[10], name[10], branch[15];
    public: void pack(); 
            void unpack(char[]);
            void display();
            void search();
};

void student::pack() {
    char buffer[28];
    cout<<"Enter usn, name, branch: ";
    cin>>usn>>name>>branch;
    strcpy(buffer, usn);
    strcat(buffer, "|");
    strcat(buffer, name);
    strcat(buffer, "|");
    strcat(buffer, branch);
    strcat(buffer, "|");
    
    int len = strlen(buffer);
    while(len < 27) {
        // hehhehehe
        strcat(buffer, "#");
        len++;
    }
    buffer[27] = '\0';
    fp<<buffer<<"\n";
}

void student::unpack(char buffer[]) {
    char *t;
    // char buffer[28];

    t = strtok(buffer,"|");
    cout<<"usn: "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"name: "<<t<<endl;
    t = strtok(NULL,"|");
    cout<<"branch: "<<t<<endl;
}

void student::display() {
    char buffer[28];

    if(n == 0) {
        cout<<"no records";
        return;
    }

    cout<<"file contents are: "<<endl;
    fp.open(fname, ios::in);
    for(int i = 0; i < n; i++) {
        fp>>buffer;
        unpack(buffer);
        cout<<"\n";
    }
    fp.close();
}

void student::search() {
    char buffer[28],temp[28];
    char *usn;
    char key[15];
    int choice;

    cout<<"enter the usn to be searched: ";
    cin>>key;

    fp.open(fname,ios::in);
    for(int i = 0; i < n; i++) {
        fp>>buffer;
        strcpy(temp,buffer);
        usn = strtok(buffer,"|");
        if(strcmp(key,usn) == 0) {
            cout<<"record found";
            unpack(buffer);
            cout<<"do you want to modify:"<<endl;
            cout<<"enter you choice: 1.yes 2.no"<<endl;
            cin>>choice;
            if(choice == 1) {
                fp.seekp(-27,ios::cur);
                pack();
            }
            fp.close();
            return;
        }
    }
    cout<<"Record not found"<<endl;
    fp.close();
    return;
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

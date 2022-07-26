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
    t = strtok(NULL, "|");
    cout<<"name: "<<t<<endl;
    t = strtok(NULL, "|");
    cout<<"branch: "<<t<<endl;
}

void student::insrec() {
    char buffer[50],tem[50];
    char *usn;
    int i,j;
    fp.open(fname,ios::out|ios::ate);
    pack(buffer);
    strcpy(tem, buffer);
    usn = strtok(tem, "|");
    int pos = search(usn);
    if(pos != 0) {
        cout<<"usn already exists"<<endl;
        fp.close();
        return;
    }

    recount++;
    strcpy(index[recount].key,usn);
    index[recount].offset = fp.tellg();
    fp<<buffer<<"\n";
    memindex temp;

    for(i = 0; i < recount; i++) {
        for(j = 0; j < recount; j++) {
            if(strcmp(index[j].key, index[j+1].key) > 0){
                strcpy(temp.key, index[j].key);
                temp.offset = index[j].offset;

                strcpy(index[j].key, index[j+1].key);
                index[j].offset = index[j+1].offset;

                strcpy(index[j+1].key, temp.key);
                index[j+1].offset = temp.offset;
            }
        }
    }
    fp.close();
}

void student::delrec() {
    char usn[15];
    int pos;
    fp.open(fname,ios::out|ios::ate);
    cout<<"enter the usn to be searched: \n";
    cin>>usn;

    pos = search(usn);
    if(pos == 0) {
        cout<<"record not found";
        fp.close();
        return;
    }
    fp.seekg(index[pos].offset,ios::beg);
    fp<<"*";
    fp.close();
    for(int i = pos; i < recount; i++) {
        strcpy(index[i].key, index[i+1].key);
        index[i].offset = index[i+1].offset;
    }
    cout<<"record deleted successfully"<<endl;
    recount--;
}

void student::display() {
    char buffer[50];
    
    if(recount == 0) {
        cout<<"no records to display"<<endl;
        return;
    }

    cout<<"\t------------"<<endl;
    cout<<"\t Primary Index"<<endl;
    cout<<"\t------------"<<endl;
    cout<<"\t key\t"<<"offset"<<endl;
    cout<<"\t-------------"<<endl;

    for(int i = 1; i <= recount; i++) {
        cout<<"\t"<<index[i].key<<"\t"<<index[i].offset<<endl;
    }
    cout<<"\n File contents are: \n"<<endl;
    fp.open(fname,ios::in);
    for(int i = 1; i <= recount; i++) {
        fp.seekg(index[i].offset, ios::beg);
        fp>>buffer;
        unpack(buffer);
        cout<<endl;
    }
    fp.close();
}   

int  student::search(char usn[]) {
    int low = 1, high = recount, mid;

    while(low <= high) {
        mid = (low + high) / 2;

        if(strcmp(index[mid].key, usn) == 0) {return mid;}
        if(strcmp(index[mid].key, usn) > 0) {high = mid -1;}
        else {low = mid + 1;}
    }
    return 0;
}

int main() {
    char buffer[50];
    int ch, i,pos;
    student s1;
    char usn[15];
    cout<<"enter the filename: \n";
    cin>>fname;
    fp.open(fname,ios::in);
    fp.close();
    for(;;) {
        cout<<"\n1.insert\n2.delete\n3.display\n4.search\n5.exit"<<endl;
        cout<<"enter choice: "<<endl;
        cin>>ch;

        switch (ch)
        {
        case 1: s1.insrec(); break;
        case 2: s1.delrec(); break;
        case 3: s1.display(); break;
        case 4: cout<<"enter the usn to be searched: \n";
                cin>>usn;
                pos = s1.search(usn);
                if(pos == 0) {
                    cout<<"record not present";
                    break;
                }
                fp.open(fname,ios::in);
                fp.seekg(index[pos].offset, ios::beg);
                fp>>buffer;
                s1.unpack(buffer);
                fp.close();
                break;
        case 5: exit(0); break;
        default: cout<<"invalid choice"; break;
        }
    }
    return 0;
}
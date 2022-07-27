#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<process.h>

using namespace std;

int main() {
    char name[20][20];
    fstream fp1;
    fstream fp[10];
    fp[1].open("n1.txt",ios::in);
    fp[2].open("n2.txt",ios::in);
    fp[3].open("n3.txt",ios::in);
    fp[4].open("n4.txt",ios::in);
    fp[5].open("n5.txt",ios::in);
    fp[6].open("n6.txt",ios::in);
    fp[7].open("n7.txt",ios::in);
    fp[8].open("n8.txt",ios::in);

    fp1.open("merge.txt",ios::out);
    for(int i = 0; i <= 8; i++) {
        fp[i]>>name[i];
    }

    for(;;) {
        int low = 1;
        for(int i = 0; i <= 8; i++) {
            if(strcmp(name[i], name[low]) < 0){
                low = i;
            }
        }
        if(strcmp(name[low], "~") == 0) {
            fp1.close();
            for(int i = 0; i <= 8; i++){
                fp[i].close();
            }
            exit(0);
        }
        else {
            fp1<<name[low]<<"\n";
            cout<<name[low]<<"\n";
            fp[low]>>name[low];
            if(fp[low].fail()) {
                strcpy(name[low],"~");
            }
        }
    }
}
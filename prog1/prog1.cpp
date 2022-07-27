#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<process.h>

using namespace std;

int main() {
    fstream fp1, fp2;
    char str[10], name[10][10];
    int ch, n, i;
    char fin[10],fout[10];

    for(;;) {
        cout<<"\n1.std input to output \n2.file to std output \n3.file to file\n";
        cout<<"enter choice: \n";
        cin>>ch;

        switch (ch)
        {
        case 1: cout<<"enter number of records: \n";
                cin>>n;
                cout<<"enter "<<n<<" names: \n";
                for(i = 0; i < n; i++) {
                    cin>>name[i];
                }
                cout<<"reversed names are: \n";
                for(i = 0; i < n; i++) {
                    strrev(name[i]);
                    cout<<name[i]<<"\n";
                }
            break;
        case 2: cout<<"enter the filename: \n";
                cin>>fin;
                fp1.open(fin,ios::in);
                while(!fp1.fail()) {
                    fp1>>str;
                    strrev(str);
                    cout<<str<<"\n";
                }
                fp1.close();
                break;
        case 3: cout<<"enter input filename: \n";
                cin>>fin;
                cout<<"enter output filename: \n";
                cin>>fout;
                fp1.open(fin,ios::in);
                fp2.open(fout,ios::out);
                while(!fp1.fail()) {
                    fp1>>str;
                    strrev(str);
                    fp2<<str<<"\n";
                }
                fp1.close();
                fp2.close();
                break;
        default: exit(0);
            break;
        }
    }
}
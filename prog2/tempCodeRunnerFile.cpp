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

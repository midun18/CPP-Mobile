//To create a Mobile.

#include<iostream>
#include<fstream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<dos.h>
#include<windows.h>

using namespace std;

class contacts;
class dialpad;
class log;
class message;
class clockk;
class music;
class player;

//used to store contacts
struct con_node{
    string name;
    string number;
    struct con_node *link;
};

class contacts{
    public:
        con_node *start;
        int opt;
        contacts(){
            opt=0;
            start=NULL;
        }
        int selMenu();
        void new_contact();
        void searchContact();
        void delContact();
        void displayCon();
};

int contacts :: selMenu(){
    static int it=0;
    int b=0;
    if(b==it){
        b=it;
        ifstream fout("contacts.txt",ios::in);
        string nam,num;
        while(!fout.eof()){
            it++;
            con_node *temp=new con_node;
            getline(fout,nam);
            cout<<nam;
            temp->name=nam;
            getline(fout,num);
            cout<<num;
            temp->number=num;
            if(start==NULL){
                temp->link=NULL;
                start=temp;
            }
            else{
                temp->link=start;
                start=temp;
            }
        }
        fout.close();
    }
    int i=1,i1=0;
    while(i!=0){
        system("cls");
        cout<<"1.Add Contact\n2.Search Contact\n3.Delete\n4.View Contacts\n5.Back\n";
        cout<<"Select : ";
        cin>>opt;
        switch(opt)
        {
            case 1:{
                new_contact();
                break;
            }
            case 2:{
                searchContact();
                break;
            }
            case 3:{
                delContact();
                break;
            }
            case 4:{
                displayCon();
                break;
            }
            case 5:{
                i1++;
                return 1;
            }
        }
        if(i1==0){
            cout<<"\nPress 1-Back : ";
            cin>>i;
        }
    }
}

void contacts :: new_contact(){
    con_node *temp=new con_node;
    system("cls");
    string a;
    string a1;
    cout<<"\nEnter Name : "<<endl;
    cin.ignore();
    getline(cin,a);
    temp->name=a;
    cout<<"\nEnter Number : "<<endl;
    cin>>a1;
    temp->number=a1;
    ofstream fin("contacts.txt",ios::app);
    fin<<a<<endl;
    fin<<a1<<endl;
    cout<<"\n::Contact Successfully Added::\n";
    temp->link=start;
    start=temp;
    fin.close();
}

void contacts :: searchContact(){
    system("cls");
    int option;
    string search;
    con_node *ptr=start;
    cout<<"\nSearch by \n1.Name\n2.Number\nSelect : ";
    cin>>option;
    if(option==1){
        cout<<"\nEnter Name : ";
        cin>>search;
        while(ptr!=NULL){
            if(ptr->name==search){
                break;
            }
            else{
                ptr=ptr->link;
            }
        }
        if(ptr!=NULL){
            cout<<"\n:: Contact Found ::\nName :: "<<ptr->name<<"\nNumber : "<<ptr->number;
        }
        else
            cout<<"\n::Contact Not Found::\n";
    }
    else if(option==2){
        cout<<"\nEnter Number : ";
        cin>>search;
        while(ptr!=NULL){
            if(ptr->number==search){
                break;
            }
            else{
                ptr=ptr->link;
            }
        }
        if(ptr!=NULL){
            cout<<"\n:: Contact Found ::\nNumber :: "<<ptr->number<<"\nName : "<<ptr->name;
        }
        else
            cout<<"\n::Contact Not Found::\n";
    }
}

void contacts :: delContact(){
    con_node *ptr=new con_node;
    ptr=start;
    con_node *prev=start;
    ofstream fout("contacts.txt",ios::out);
    system("cls");
    string search,comp;
    cout<<"\nEnter Name : ";
    cin>>search;
    while(ptr!=NULL){
        if(ptr->name==search){
            ptr=ptr->link;
        }
        else{
            fout<<endl<<ptr->name;
            fout<<endl<<ptr->number;
            ptr=ptr->link;
        }
    }
    ptr=start;
    while(ptr!=NULL){
        if(ptr->name==search){
            break;
        }
        else{
            prev=ptr;
            ptr=ptr->link;
        }
    }
    if(ptr!=NULL){
        prev->link=ptr->link;
        delete ptr;
        cout<<"\n::Contact Deleted::\n";
    }
    else{
        cout<<"\n::Contact Not Found::\n";
    }

}

void contacts :: displayCon(){
    char ch;
    system("cls");
    ifstream fout("contacts.txt");
    while(fout.get(ch)){
          cout<<ch;
    }
    fout.close();
}

class dialpad
{
    con_node *start;
    public:
        dialpad(){
            start=NULL;
        }
        int selMenu();
        void dialContact();
};

int dialpad :: selMenu(){
    int i=1,i1=0;
    while(i!=0){
        system("cls");
        int option;
        cout<<"\n1.Dial\n2.Back\nSelect : ";
        cin>>option;
        switch(option){
            case 1:{
                dialContact();
                break;
            }
            case 2:{
                i1++;
                return 1;
                break;
            }
        }
        if(i1==0){
            cout<<"Press 1-Previous Menu : ";
            cin>>i;
        }
    }
}

void dialpad :: dialContact(){
    static int it=0;
    int b=0;
    if(b==it){
        b=it;
        ifstream fout("contacts.txt",ios::in);
        string nam,num;
        while(!fout.eof()){
            it++;
            con_node *temp=new con_node;
            getline(fout,nam);
            temp->name=nam;
            getline(fout,num);
            temp->number=num;
            if(start==NULL){
                temp->link=NULL;
                start=temp;
            }
            else{
                temp->link=start;
                start=temp;
            }
        }
        fout.close();
    }
    system("cls");
    con_node *ptr=start;
    int option,opt,call;
    string search,num;
    cout<<"\nDial by \n1.Contact\n2.Number\nSelect : ";
    cin>>option;
    if(option==1){
        system("cls");
        cout<<"\nEnter Name : ";
        cin>>search;
        while(ptr!=NULL){
            if(ptr->name==search){
                break;
            }
            else{
                ptr=ptr->link;
            }
        }
        if(ptr!=NULL){
            cout<<"\n:: Contact Found ::\nName :: "<<ptr->name<<"\nNumber : "<<ptr->number;
            cout<<"\nPress 1-Call : ";
            cin>>opt;
        }
        else{
            cout<<"\n::Contact Not Found::\n";
        }
        if(opt==1){
            ofstream fout("log.txt",ios::app);
            string cal;
            cal="Calling";
            int i;
            for(i=0;i<7;i++){
                cout<<cal[i];
                Sleep(500);
            }
            clock_t t;
            t = clock();
            cout<<"\nConnected"<<endl;
            cout<<"\nOn Call"<<" with "<<ptr->name<<"  "<<ptr->number;
            fout<<ptr->name<<"  "<<ptr->number;
            cout<<"\nPress 1-End After Done : ";
            cin>>call;
            cout<<"\nCall Ended\n";
            t = clock() - t;
            double time_taken = ((double)t)/CLOCKS_PER_SEC;
            cout<<"\nTime Elapsed : "<<time_taken<<" seconds"<<endl;
            fout<<"  "<<time_taken<<" seconds"<<endl;
            fout.close();
        }
    }
    else if(option==2){
        ofstream fout("log.txt",ios::app);
        system("cls");
        cout<<"Enter the number\t";
        cin>>num;
        string cal;
        cal="Calling";
        int i;
        for(i=0;i<7;i++){
            cout<<cal[i];
            Sleep(500);
        }
        clock_t t;
        t = clock();
        cout<<"\nConnected"<<endl;
        cout<<"\nOn Call"<<" with "<<num;
        fout<<num<<"  ";
        cout<<"\nPress 1-End After Done : ";
        cin>>call;
        cout<<"\nCall Ended\n";
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        cout<<"\nTime Elapsed : "<<time_taken<<" seconds"<<endl;
        fout<<"  "<<time_taken<<" seconds"<<endl;
        fout.close();
    }
}

struct log_node{
    string logg;
    struct log_node *link;
};

class log{
    public:
        log_node *start;
        log(){
            start=NULL;
        }
        int selMenu();
        void displayLog();
        void delFile();
};

int log :: selMenu(){
    static int it=0;
    int b=0;
    if(b==it){
        b=it;
        ifstream fout("log.txt",ios::in);
        string nam;
        while(!fout.eof()){
            it++;
            log_node *temp=new log_node;
            getline(fout,nam);
            cout<<nam;
            temp->logg=nam;
            if(start==NULL){
                temp->link=NULL;
                start=temp;
            }
            else{
                temp->link=start;
                start=temp;
            }
        }
        fout.close();
    }
    int i=1,i1=0;
    while(i!=0){
        system("cls");
        int opt;
        cout<<"1.Display Log\n2.Delete All\n3.Back\nSelect : ";
        cin>>opt;
        switch(opt){
            case 1:{
                displayLog();
                break;
            }
            case 2:{
                delFile();
                break;
            }
            case 3:{
                i1++;
                return 1;
                break;
            }
        }
        if(i1==0){
                cout<<"\nPress 1-Previous Menu : ";
                cin>>i;
        }
    }
}

void log :: displayLog(){
    system("cls");
    log_node *ptr=start;
    if(ptr!=NULL){
        cout<<":: Call Log :: \n";
        while(ptr!=NULL){
            cout<<ptr->logg<<endl;
            ptr=ptr->link;
        }
    }
    else if(ptr==NULL){
        cout<<"\n::Log Empty::\n";
    }

}

void log :: delFile(){
    system("cls");
    if(start!=NULL){
        ofstream fin("log.txt",ios::out);
        fin.close();
        start=NULL;
        cout<<"\n::Log is Empty Now::\n";
        fin.close();
    }
    else{
        cout<<"\n::Log Already Empty::\n";
    }
}


struct mes_node{
    string mess;
    string recepient;
    struct mes_node *link;
};

class message{
    public:
        mes_node *start,*start1;
        message(){
            start=NULL;
            start1=NULL;
        }
        int selMenu();
        void compose();
        void inbox();
        void sent();
        void deleteMessage();
};

int message :: selMenu(){
    static int it=0,it1=0;
    int b=0,b1=0;
    if(b==it){
        b=it;
        ifstream fout("inbox.txt",ios::in);
        string nam,mes;
        while(!fout.eof()){
            it++;
            mes_node *temp=new mes_node;
            getline(fout,nam);
            temp->recepient=nam;
            getline(fout,mes);
            temp->mess=mes;
            if(start==NULL){
                temp->link=NULL;
                start=temp;
            }
            else{
                temp->link=start;
                start=temp;
            }
        }
        fout.close();
    }
    if(b1==it1){
        b1=it1;
        ifstream fout("sent.txt",ios::in);
        string nam,mes;
        while(!fout.eof()){
            it1++;
            mes_node *temp=new mes_node;
            getline(fout,nam);
            temp->recepient=nam;
            getline(fout,mes);
            temp->mess=mes;
            if(start1==NULL){
                temp->link=NULL;
                start1=temp;
            }
            else{
                temp->link=start1;
                start1=temp;
            }
        }
        fout.close();
    }
    int i=1,i1=0;
    while(i!=0){
        system("cls");
        int opt;
        cout<<"1.Compose\n2.Inbox\n3.Sent\n4.Delete Message\n5.Previous Menu\nSelect : ";
        cin>>opt;
        switch(opt){
            case 1:{
                compose();
                break;
            }
            case 2:{
                inbox();
                break;
            }
            case 3:{
                sent();
                break;
            }
            case 4:{
                deleteMessage();
                break;
            }
            case 5:{
                i1++;
                return 1;
                break;
            }
        }
        if(i1==0){
            cout<<"\nPress 1-Back : ";
            cin>>i;
        }
    }
}

void message :: compose(){
    mes_node *temp=new mes_node;
    system("cls");
    string a,b;
    cout<<"\nEnter Name : ";
    cin.ignore();
    getline(cin,a);
    temp->recepient=a;
    string numb;
    cout<<"\nEnter Message : ";
    getline(cin,b);
    temp->mess=b;
    ofstream fin("sent.txt",ios::app);
    fin<<a<<endl;
    fin<<b<<endl;
    cout<<"\n::Message Successfully Sent::\n";
    temp->link=start;
    start=temp;
    fin.close();
}

void message :: inbox(){
    system("cls");
    char ch;
    fstream in("inbox.txt",ios::in);
    while(in.get(ch)){
        cout<<ch;
    }
    in.close();
}

void message :: sent(){
    system("cls");
    char ch;
    fstream smsg("sent.txt",ios::in);
    while(smsg.get(ch)){
        cout<<ch;
    }
    smsg.close();
}

void message :: deleteMessage(){
    system("cls");
    int opt=0;
    cout<<"\n1.From Inbox\n2.From Sent\nSelect : ";
    cin>>opt;
    if(opt==1){
        mes_node *ptr=start;
        mes_node *prev=start;
        ofstream fout("inbox.txt",ios::out);
        system("cls");
        string search,comp;
        cout<<"\nEnter Name : ";
        cin>>search;
        while(ptr!=NULL){
            if(ptr->recepient==search){
                ptr=ptr->link;
            }
            else{
                fout<<endl<<ptr->recepient;
                fout<<endl<<ptr->mess;
                ptr=ptr->link;
            }
        }
        ptr=start;
        while(ptr!=NULL){
            if(ptr->recepient==search){
                break;
            }
            else{
                prev=ptr;
                ptr=ptr->link;
            }
        }
        if(ptr!=NULL){
            prev->link=ptr->link;
            delete ptr;
            cout<<"\n::Message Deleted::\n";
        }
        else{
            cout<<"\n::Message Not Found::\n";
        }
        fout.close();
    }
    else if(opt==2){
        mes_node *ptr=start1;
        mes_node *prev=start1;
        ofstream fout("sent.txt",ios::out);
        system("cls");
        string search,comp;
        cout<<"\nEnter Name : ";
        cin>>search;
        while(ptr!=NULL){
            if(ptr->recepient==search){
                ptr=ptr->link;
            }
            else{
                fout<<endl<<ptr->recepient;
                fout<<endl<<ptr->mess;
                ptr=ptr->link;
            }
        }
        ptr=start1;
        while(ptr!=NULL){
            if(ptr->recepient==search){
                break;
            }
            else{
                prev=ptr;
                ptr=ptr->link;
            }
        }
        if(ptr!=NULL){
            prev->link=ptr->link;
            delete ptr;
            cout<<"\n::Message Deleted::\n";
        }
        else{
            cout<<"\n::Message Not Found::\n";
        }
        fout.close();
    }
}

class security{
private:
    string password;
public:
    security();
    int display();
    bool validatepass();
    void setpass();
    void viewpass();
    void changepass();
    void removepass();
};

class volume{
private:
    int callv;
    int mediav;
    int alarmv;
public:
    volume();
    void display(int choice);
    void call_volume();
    void media_volume();
    void alarm_volume();
};

volume :: volume(){
    alarmv=callv=mediav=1;
}

void volume :: display(int choice){
    system("cls");
    switch(choice){
    case 1:
        call_volume();
        break;
    case 2:
        media_volume();
        break;
    case 3:
        alarm_volume();
        break;
    }
}

void volume :: call_volume(){
    system("cls");
    char ch;
    cout<<"+ : Increase the volume ";
    cout<<"\n- : Decrease the volume ";
    cout<<"Enter your option : ";
    cin>>ch;
    cout<<"\nThe current volume : "<<callv;
    if(ch=='+')
        callv++;
    else
        callv--;
}

void volume :: media_volume(){
    system("cls");
    char ch;
    cout<<"+ : Increase the volume ";
    cout<<"\n- : Decrease the volume ";
    cout<<"Enter your option : ";
    cin>>ch;
    cout<<"\nThe current volume : "<<mediav;
    if(ch=='+')
        mediav++;
    else
        mediav--;
}

void volume :: alarm_volume(){
    system("cls");
    char ch;
    cout<<"+ : Increase the volume ";
    cout<<"\n- : Decrease the volume ";
    cout<<"\nEnter your option : ";
    cin>>ch;
    cout<<"\nThe current volume : "<<alarmv;
    if(ch=='+')
        alarmv++;
    else
        alarmv--;
}

class settings{
public:
    security lock;
    volume sound;
public:
    int display();
    void factory_reset();
    void sound_settings();
    void security_settings();
};

void settings :: factory_reset(){
    system("cls");
    fstream cont,inb,mus,sent,pass;
    cont.open("contacts.txt",ios::out);
    inb.open("inbox.txt",ios::out);
    mus.open("music.txt",ios::out);
    sent.open("sent.txt",ios::out);
    pass.open("passwd.txt",ios::out);
    cont.close();
    inb.close();
    mus.close();
    sent.close();
    pass.close();
}

void settings :: sound_settings(){
    system("cls");
    int choice;
    cout<<"\nSOUND SETTINGS";
    cout<<"\n1.Caller Volume\n2.Media Volume\n3.Alarm Volume";
    cout<<"\nEnter the choice : ";
    cin>>choice;
    sound.display(choice);
}

int settings :: display(){
    system("cls");
    int choice,i=1,i1=0;
    cout<<"SETTINGS"<<endl;
    while(i!=0){
        cout<<endl<<"1.Factory Reset\n2.Sound Settings \n3.Security\n4.Back\n";
        cout<<"\nSelect : ";
        cin>>choice;
        switch(choice){
            case 1:{
                factory_reset();
                break;
            }
            case 2:{
                sound_settings();
                break;
            }
            case 3:{
                security_settings();
                break;
            }
            case 4:{
                i1++;
                return 1;
                break;
            }
            if(i1==0){
                cout<<"\nPress 1-Previous Menu : ";
                cin>>i;
            }
        }
    }
}

void settings :: security_settings(){
    int option;
    option = lock.display();
    switch(option){
    case 1:
        lock.validatepass();
        break;
    case 2:
        lock.setpass();
        break;
    case 3:
        lock.viewpass();
        break;
    case 4:
        lock.changepass();
        break;
    case 5:
        lock.removepass();
        break;
    }
}

security :: security(){
    string temp;
    fstream lck;
    temp='\0';
    lck.open("passwd.txt",ios::in);
    lck>>password;
    lck.close();
}

bool security :: validatepass(){
    string temp;
    cout<<"Enter Password : ";
    cin>>temp;
    if(temp==password){
        cout<<"\nCorrect password ";
        return 1;
    }
    else{
        cout<<"\nPassword Incorrect";
        return 0;
    }
}

void security :: setpass(){
    system("cls");
    fstream lck;
    lck.open("passwd.txt",ios::out);
    string temp1,temp2,a;
    a='\0';
    if(password==a){
        cout<<"\nEnter the new password : ";
        cin>>temp1;
        cout<<"\nEnter the password again : ";
        cin>>temp2;
        if(temp1==temp2){
            cout<<"\nPassword verified ";
            password=temp1;
            lck<<temp1;
        }
        else{
            cout<<"\nPassword mismatch, try again";
        }
    }
    else{
        cout<<"\nAlready there is a password , try to change the password";
    }
    lck.close();
}

void security :: viewpass(){
    system("cls");
    fstream lck;
    lck.open("passwd.txt",ios::in);
    string temp;
    lck>>temp;
    if(temp==password)
        cout<<"\nThe password is "<<password;
    lck.close();
}

void security :: changepass(){
    system("cls");
    string temp1,temp2;
    fstream lck;
    bool check;
    cout<<"\nTo change the password , you have to enter the current password";
    check=validatepass();
    if(check){
        lck.open("passwd.txt",ios::out);
        cout<<"\nEnter the new password : ";
        cin>>temp1;
        cout<<"\nEnter the password again : ";
        cin>>temp2;
        if(temp1==temp2){
            lck<<password;
            cout<<"\nPassword is changed ";
        }
        lck.close();
    }
    else
        cout<<"\nTry again";
}

void security ::removepass(){
    system("cls");
    bool check;
    cout<<"\nTo remove the password you have to enter the current password.";
    check=validatepass();
    if(check){
        fstream lck;
        lck.open("passwd.txt",ios::out);
        lck<<'\0';
        cout<<"\nPassword removed";
    }
    else
        cout<<"\nTry again";
}

int security :: display(){
    system("cls");
    int choice;
    cout<<"\nSECURITY";
    cout<<"\n1.Validate Password\n2.Set Password\n\t3.View Password\n4.Change Password\n5.Remove Password ";
    cout<<"\nEnter the choice : ";
    cin>>choice;
    return choice;
}

class clockk{
    public:
        int i1,i;
        int hh,mm,ss,ms;
        clock(){
            i1=0;
            i=1;
            hh=mm=ss=ms=0;
        }
        void show();
        void cancel();
        void inc();
        void title();
        int selMenu();
        void displayTime();
        void stopwatch();
};

void clockk :: show(){
    if(ms>9){
        ms=0;
        ss++;
    }
    else if(ss>59){
        ss=0;
        mm++;
    }
    else if(mm>59){
        mm=0;
        hh++;
    }
    cout<<mm<<":"<<ss<<":"<<ms;
}

void clockk :: inc(){
    ms++;
}

void clockk :: cancel(){
    hh=mm=ss=ms=0;
}

void clockk :: title(){
    cout<<"\n Press S-Start ";
    cout<<"\n Press T-Stop \nSelect : \n";
}

int clockk :: selMenu(){
    int i=1,i1=0;
    while(i!=0){
        system("cls");
        int opt;
        cout<<"1.Display time\n2.Stopwatch\n3.Back\nSelect : ";
        cin>>opt;
        switch(opt){
            case 1:{
                displayTime();
                break;
            }
            case 2:{
                stopwatch();
                break;
            }
            case 3:{
                i1++;
                return 1;
                break;
            }
            if(i1==0){
                cout<<"\nPress 1-Previous Menu : ";
                cin>>i;
            }
        }
    }
}

void clockk :: displayTime(){
    system("cls");
    cout<<__TIMESTAMP__<<endl;
    system("pause");
}

void clockk :: stopwatch(){
    char opt;
    system("cls");
    cout<<":: Stopwatch ::";
    title();
    opt=getch();
    if((opt=='s')||(opt=='S')){
        while(!kbhit()){
            system("cls");
            title();
            show();
            Sleep(50);
            inc();
        }
        opt=getch();
    }
    else if((opt=='t')||(opt=='T')){
        show();
        title();
    }
}

struct mus_node{
    string song;
    struct mus_node *left,*right;
};

class player{
    struct mus_node *start1;
    struct mus_node *now;
    public:
        player(mus_node *root){
            start1=root;
            now=root;
        }
        void nowPlay();
        void prev();
        void next();
};

void player :: nowPlay(){
    string songs;
    mus_node *ptr=start1;
    system("cls");
    cout<<"\n::List::\n";
    while(ptr!=NULL){
        cout<<ptr->song<<endl;
        ptr=ptr->right;
    }
    ptr=start1;
    cout<<"\nEnter a song : ";
    cin>>songs;
    while(ptr!=NULL){
        if(ptr->song==songs){
            break;
        }
        else{
            ptr=ptr->right;
        }
        now=ptr;
    }
    if(ptr!=NULL){
        cout<<"\nNow Playing : "<<ptr->song;
    }
    else{
        cout<<"\n::Song not listed::\n";
    }
}

void player :: prev(){
    system("cls");
    now=now->left;
    if(now!=NULL){
        cout<<"\nPrevious Song : "<<now->song<<endl;
        cout<<"\nNow Playing : "<<now->song<<endl;
    }
    else{
        cout<<"\n:: No Previous Song ::\n";
    }
}

void player :: next(){
    system("cls");
    now=now->right;
    if(now!=NULL){
        cout<<"\nNext Song : "<<now->song<<endl;
        cout<<"\nNow Playing : "<<now->song<<endl;
    }
    else{
        cout<<"\n:: No Next Song ::\n";
    }
}

class music{
    public:
        struct mus_node *start;
        int opt;
        music(){
            start=NULL;
            opt=0;
        }
        int selMenu();
        void now_playing();
        void dispSongs();
        void searchSongs();
};

int music :: selMenu(){
    static int it=0;
    int b=0;
    if(b==it){
        b=it;
        ifstream fout("music.txt",ios::in);
        string nam;
        while(!fout.eof()){
            it++;
            mus_node *temp=new mus_node;
            getline(fout,nam);
            cout<<nam;
            temp->song=nam;
            if(start==NULL){
                temp->left=NULL;
                temp->right=NULL;
                start=temp;
            }
            else{
                start->left=temp;
                temp->left=NULL;
                temp->right=start;
                start=temp;
            }
        }
        fout.close();
    }
    int i=1,i1=0;
    while(i!=0){
        system("cls");
        cout<<"1.Player\n2.Search Song\n3.View Songs\n4.Back\n";
        cout<<"Select : ";
        cin>>opt;
        switch(opt){
            case 1:{
                now_playing();
                break;
            }
            case 2:{
                searchSongs();
                break;
            }
            case 3:{
                dispSongs();
                break;
            }
            case 4:{
                i1++;
                return 1;
                break;
            }
        }
        if(i1==0){
            cout<<"\nPress 1-Previous Menu : ";
            cin>>i;
        }
    }
}

void music :: now_playing(){
    int i=1;
    player play(start);
        while(i!=0){
            system("cls");
            cout<<"\n1.Play\n2.Previous\n3.Next\n4.Back\nSelect : ";
            cin>>opt;
            switch(opt){
                case 1:{
                    play.nowPlay();
                    break;
                }
                case 2:{
                    play.prev();
                    break;
                }
                case 3:{
                    play.next();
                    break;
                }
                case 4:{
                    selMenu();
                    break;
                }
            }
        cout<<"\nPress 1-Previous Menu : ";
        cin>>i;
    }
}

void music :: dispSongs(){
    system("cls");
    mus_node *ptr=start;
    while(ptr!=NULL){
        cout<<ptr->song<<endl;
        ptr=ptr->right;
    }
}

void music :: searchSongs(){
    mus_node *ptr=start;
    system("cls");
    string search;
    cout<<"\nEnter Song : ";
    cin>>search;
    while(ptr!=NULL){
        if(ptr->song==search){
            break;
        }
        else{
            ptr=ptr->right;
        }
    }
    if(ptr!=NULL){
        cout<<"\n:: Song Found ::\nName :: "<<ptr->song;
    }
    else
        cout<<"\n::Song Not Found::\n";
}

class menu{
    public:
        int option;
        contacts con;
        message mes;
        clockk clk;
        music mus;
        dialpad dial;
        log loggg;
        settings sett;
    public:
        menu(){
            option=0;
        }
        void display();
};

void menu :: display(){
    system("cls");
    cout<<"1.Contacts\n2.Dial\n3.Call Log\n4.Messages\n5.Music\n6.Settings\n7.Clock\n8.Lock\n";
    cout<<"Select : ";
    cin>>option;
}

int main(){
    string s="::Switching ON::";
    int i,pass=0;
    for(i=0;i<16;i++){
        cout<<s[i];
        Sleep(250);
    }
    system("cls");
    menu men;
    while(pass==0){
        if(men.sett.lock.validatepass()){
        pass=1;
        int sel=1;
        while(sel==1){
            men.display();
            switch(men.option){
                case 1:{
                    sel=men.con.selMenu();
                    break;
                }
                case 2:{
                    sel=men.dial.selMenu();
                    break;
                }
                case 3:{
                    sel=men.loggg.selMenu();
                    break;
                }
                case 4:{
                    sel=men.mes.selMenu();
                    break;
                }
                case 5:{
                    sel=men.mus.selMenu();
                    break;
                }
                case 6:{
                    sel=men.sett.display();
                    break;
                }
                case 7:{
                    sel=men.clk.selMenu();
                    break;
                }
                case 8:{
                    system("cls");
                    cout<<"\n::Mobile Locked::\n";
                    exit(1);
                }
                }
            }
        }
        else {
            system("cls");
            cout<<"\nTry Again !\n";
        }
    }
}

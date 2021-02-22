#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include <stdio.h>
#include <time.h>

using namespace std;

int x,m;
string sname,status;
fstream list("List.txt",ios::app);

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void write(string name,float money,string status,float amount){
	list<<name<<","<<money<<","<<status<<","<<amount<<endl;
}

void importDataFromFile(string fn,vector<string> &names,vector<float> &moneys){
	fstream source("Bank.txt");
    string text;
    char name[100];
    char format[] = "%[^,],%f";
    while(getline(source,text)){
    	float money;
        char ctext[100];
        strcpy(ctext,text.c_str());
        sscanf(ctext,format,name,&money);
        names.push_back(name);
        moneys.push_back(money);
    }
    source.close();
}

void searchName(vector<string> &names,vector<float> &moneys,string key){
    int N = names.size();
    int stat = 0;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s moneys = " << moneys[i] << endl;
            stat = 1;
        }
    }
    if(stat != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void Deposit(vector<string> &names,vector<float> &moneys,string key){
    int N = names.size();
    int deposit;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
    cout <<"How much will you deposit? ";
        	cin>>deposit;
        	moneys[m]+=deposit;
            cout << sname << "'s balance = " << fixed << setprecision(2) << moneys[m] << endl;
            status = "add";
            write(sname,moneys[m],status,deposit);
    if(status != "add") cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}
void Withdraw(vector<string> &names,vector<float> &moneys,string key){
    int N = names.size();
    int withdraw;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
    cout <<"How much will you withdraw?";
        	cin>>withdraw;
        	if(moneys[m] >= withdraw){
			moneys[m]-=withdraw;
            cout << sname << "'s balance = " << fixed << setprecision(2) << moneys[m] << endl;
            status = "withdraw";}
            write(sname,moneys[m],status,withdraw);
    if(status != "withdraw") cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void Transfer(vector<string> &names,vector<float> &moneys,string key){
	int N = names.size();
    int transfer,t=0;
    string target,stat="false",tname;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
	cout <<"Transfer money to which account: ";
	do{
	cin>>target;
	cin.ignore();
	target=toUpperStr(target);
		for(int j = 0 ; j < N ; j++){
        	if(target == toUpperStr(names[j])){
        		tname=names[j];
        		t=j;
        	}
    	}
    	if(t!=0){
			stat="true";
			break;
    	}else cout<<"Cannot found. Plase input agian: "<<endl;
	}while(true);
    cout <<"How much will you transfer? ";
        	cin>>transfer;
        	if(moneys[m] >= transfer){
			moneys[m] -= transfer;
            cout << sname << "'s balance = " << fixed << setprecision(2) << moneys[m] << endl;
            status = "withdraw";}
            write(sname,moneys[m],status,transfer);
            moneys[t] += transfer;
            status = "deposit";
            write(tname,moneys[t],status,transfer);
    cout << "---------------------------------\n";
}

void Balance(vector<string> &names,vector<float> &moneys,string key){
	int N = names.size();
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Balance in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
    cout << "---------------------------------\n";
	
}

void receipt(){
		system("cls");
	time_t rawtime;
    struct tm * local;
    time(&rawtime);
    local = localtime(&rawtime);

			cout << "\n\n\t\t\t\t\t PRINTING RECEIPT . . .\n";
			system("cls");
			cout << endl <<"\n\n\t\t\t|\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2|";
			cout << "\n\t\t\t|\t\t\t\t\t      |"
				 << "\n\t\t\t|\t     ATM TRANSACTION RECORD\t      |"
				 << "\n\t\t\t|\t\t\t\t\t      |"
				 << "\n\t\t\t|DATE:\t\t\t    "<<local->tm_mday<<":"<<local->tm_mon<<":"<< local->tm_year <<"\t      |"
				 << "\n\t\t\t|TIME:\t\t\t    "<<local->tm_hour<<":"<<local->tm_min<<":"<< local->tm_sec <<"\t      |";
}

int main(){
    string filename = "Bank.txt";
    vector<string> names;
    vector<float> moneys;
    string key;
    importDataFromFile(filename, names, moneys);
    cout<<"Please input your name : ";
	getline(cin,key);
	key = toUpperStr(key);
	cout<<"Please select your order"<<endl;
	cout<<"1 : Deposit"<<"     "<<"2 : Withdraw"<<"     "<<"3 : Transfer"<<endl;
	cout<<"4 : View transaction history"<<"     "<<"5 : EXIT"<<endl;
	while(true){
		cout<<"Please select number(1-5) : ";
		cin>>x;
		if(x>0&&x<6) break;
		else cout<<"Please select again"<<endl;
	}
        if(x == 1) Deposit(names, moneys, key);
		if(x == 2) Withdraw(names, moneys, key);
		if(x == 3) Transfer(names, moneys, key);
        if(x == 4) searchName(names, moneys, key);
        if(x == 0) Balance(names, moneys, key);
        if(x == 5){
		system("cls");
		cout << "THANK YOU FOR CHOOSING US";
}

    return 0;
}

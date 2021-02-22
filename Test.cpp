#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main(){
	long int x,deposit,Withdraw,Transfer;
	string text,name,sdeposit,sWithdraw,sTransfer;
	fstream source;
	source.open("dest.txt");
	
	while(getline(source,text)){
		cout<<text<<endl;
	}
	cout<<"Please enter your name";
	cin>>name;
	cin.ignore();
	while(getline(source,text)){
		if(text==name){
			name=text;
			cout<<name;
		}
	}
	cout<<"Please select your order"<<endl;
	cout<<"1 : Deposit"<<"     "<<"2 : Withdraw"<<endl;
	cout<<"3 : Transfer"<<endl;
	while(true){
		cin>>x;
		if(x>0&&x<4) break;
		else cout<<"Please input again"<<endl;
	}
	switch(x){
		case 1:
			cout<<"Enter the amount of the deposit = ";
			cin>>deposit;
			break;
		case 2:
			cout<<"Enter the amount of the Withdraw = ";
			cin>>Withdraw;
			break;
		case 3:
			cout<<"Enter the amount of the Withdraw = ";
			cin>>Transfer;
			break;
	}
	
	source.close();
	return 0;
}

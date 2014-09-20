/*
	There should not be any space at the end of any line or before start of the line.
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<queue>
#include<stack>
#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<map>
#include<string.h>
#include<conio.h>
using namespace std;

class Item{
	private:
		string itemName;
		int itemCount;
		int itemId;
		
	public:
		Item(string name){
			setName(name);
		}

		Item operator=(Item &itm){
			Item *temp=new Item(itm.itemName );
			return *temp;
			
		}

		void setName(string name){
			itemName=name;
			itemCount=0;
			int len=name.length();
			int i=0;
			itemId=0;
			while(i<len){
				if(name[i]>=48 && name[i]<=57){
					itemId=itemId*10 + (name[i]-48);
				}
				i++;
			}
		}
		
		void incrementItemCount(){
			itemCount++;
		}
		
		void incrementItemCount(int incrementValue){
			itemCount=itemCount+incrementValue;
		}
		
		int getItemCount(){
			return itemCount;
		}
		
		string getItemName(){
			return itemName;
		}
		
		int getItemId(){
			return itemId;
		}
};

class FPgrowth{
	private:
		vector<vector<Item>> transaction;
		vector<vector<Item>> prunedTransaction;
		
		int *itemCounts;
	public:
		
		
		void readData(char *fName){
			ifstream reader;
			int i=0;
			string str;
			reader.open(fName);
			string line;
			
			getline(reader,str);//reading a line
			while(reader){
				int strlen=str.length();
				string tempstr="";
				int j=0;
				vector <Item> temp;
				while(j<=strlen){
					if(str[j]!=' ' && str[j]!='\n' && str[j]!='\0')
						tempstr.append(1,str[j]); //Adds 1 character to the string tempstr
					else{
						Item tempItem(tempstr);
						temp.push_back(Item(tempItem));
						tempstr="";//
				    }
					j++;
				}
				transaction.push_back(temp);
				getline(reader,str);//reading a line
				
			}
			
			cout<<endl<<"Transaction processed = "<<transaction.size()-1<<endl;
			
		}	
		
		
		vector<vector<Item>> getTransaction(){
			vector<vector<Item> > *temp;
			temp=new vector<vector<Item> >(transaction.size());
			for(int i=0;i<transaction.size();i++){
				for(int j=0;j<transaction[i].size();j++)
					(*temp)[i].push_back(Item(transaction[i][j].getItemName()));
			}
			return *temp;
		}
			
		void printTransactions(){
			for(int i=0;i<transaction.size();i++){
				for(int j=0;j<transaction[i].size();j++ )
					 cout<<(transaction[i])[j].getItemName()<<" "; //cout<<transaction[i].size();
				cout<<endl;
			}
		   cout<<endl;
		}
		
		//frequency calculation of each item
		void countItems(){
			itemCounts=new int[transaction[0].size()];
			for(int i=0;i<transaction[0].size();i++)
				itemCounts[i]=0;
			for(int i=1;i<transaction.size();i++){
				for(int j=0;j<transaction[i].size();j++){
					itemCounts[(transaction[i][j].getItemId() -1)]++; //Note: putting parenthesis is mportant otherwise inner item is reffered
			
				}
			}
			
			
		}	
		
		
		void printItemCount(){
			cout<<"Items\tCount"<<endl<<"------\t-------"<<endl;
			for(int i=0;i<transaction[0].size();i++){
				cout<<transaction[0][i].getItemName()<<"\t"<<itemCounts[i]<<endl; //<<" "<<transaction[0][i].getItemCount()<<endl;
			}
		}
		
		
		//Insertion Sort
		void sortTransactionItems(){
			for(int i=1;i<transaction.size();i++){
				
				for(int j=1;j<transaction[i].size();j++){
					
					int k=j;
					while(k>0 && ( itemCounts[ transaction[i][k].getItemId()-1]> itemCounts[(transaction[i][k-1]).getItemId()-1])){  ///Note -1 is necessary because indexing is from 0
					    string name1,name2;
					    name1=transaction[i][k].getItemName();
					    name2=transaction[i][k-1].getItemName();
					    transaction[i][k].setName(name2);
					    transaction[i][k-1].setName(name1);
						k--;
						
					}
				}
			}
		}
		
		
		int getMinSupport(){
			int n=0;
			cout<<"Enter Minimum support count ";
			cin>>n;
			return n;
		}
		
		void prune(int minSupport){
			prunedTransaction.push_back(transaction[0]);// Contanins names of all the items in the transaction.
			for(int i=1;i<transaction.size();i++){
				bool flag=true;
				for(int j=0;j<transaction[i].size() && flag;j++ ){
					if(itemCounts[transaction[i][j].getItemId()-1]>=minSupport )
						continue;
						else{
							flag=false;
						}
				}
				
				if(flag)
					prunedTransaction.push_back(transaction[i]);
			}
			
		}
		
		void printPrunedTransaction(){
			cout<<"After Prunning the transactions"<<endl;
			for(int i=0;i<prunedTransaction.size();i++){
				for(int j=0;j<prunedTransaction[i].size();j++){
					cout<<prunedTransaction[i][j].getItemName()<<" ";
				}
				cout<<endl;
			}
		}
		
		int getPTranLen(){
			return prunedTransaction.size();
		}
};

// main() is used for testing this module independently

/*
int main(){
	FPgrowth objf;
	objf.readData("data.txt");
	objf.printTransactions();
	objf.countItems();
	objf.printItemCount();
	objf.sortTransactionItems();
	cout<<endl<<"After sorted according to Item count"<<endl<<endl;
	objf.printTransactions();
	int count;
	count=objf.getMinSupport();
	objf.prune(count);
	objf.printPrunedTransaction();
	
}

*/

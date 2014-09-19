#include<string>
#include<iostream>
#include<cstring>
#include<fstream>
#include "fggrowth.cpp"
using namespace std;

class Node{
	Node **arr;
	bool flag;
	int count;
	int numberOfItems;
	public:
		Node(int numberOfItems){
			//int SIZE=26;
			this->numberOfItems=numberOfItems;
			count=0;
			arr=new Node*[numberOfItems];
			for(int i=0;i<numberOfItems;i++)
				arr[i]=nullptr;
			flag=false;
		}
	

		bool strinsert(vector<vector<Item> > transaction){
			
			if(arr==nullptr)
				arr=new Node*[numberOfItems];  //(numberOfItems);
			Node **tempArr;	
			for(int i=1;i<transaction.size();i++){
				tempArr=arr;
					for(int j=0;j<transaction[i].size();j++){
						
				// cout<<"("<<i<<","<<j<<")";//tempArr;
						if(tempArr[ transaction[i][j].getItemId() -1]==nullptr){
							    tempArr[ transaction[i][j].getItemId() -1 ]=new Node(numberOfItems);
							    (tempArr[ transaction[i][j].getItemId() -1 ])->count++;               //// BUG????
							    tempArr=tempArr[ transaction[i][j].getItemId() -1 ]->arr;
							
			    //	cout<<"inside";
				        }else{
				        	
			            		(tempArr[ transaction[i][j].getItemId() -1 ])->count++;               //// BUG????
			            		tempArr=tempArr[ transaction[i][j].getItemId() -1 ]->arr;
			            		
			            }
					}
				
			}
	///////////----------------------------------------------------------------------------------------------------------------------------------			
				
			//cout<<"Inserting"<<" "<<tranNumber<<endl;
		}
	//////////-----------------------------------------------------------------------------------------------------------------------------------		


		void traverseTree(){
			
			for(int i=0;i<numberOfItems;i++){
				if(arr[i]){
					cout<<" ( I"<<i+1<<" count:"<<arr[i]->count<<" ) ";
					(*arr[i]).traverseTree();
				}
			}
		}
			
				
		bool search(string str,int index=0){
			if(str[index]=='\0' && str.length()==index) //Returns only if length of search word equals word dictionary
				return flag;
			
			
		//	if(flag==true && str[index]!='\0')//Handles case when search string is bigger than stored & contains other special characters
		//		return false;
			if(str[index]>=65 && str[index]<=90 ){
			
				if(arr[str[index]-65]!=nullptr)
					return (true && arr[str[index]-65]->search(str,index+1));
			//	else
			//		return true;
						
			}
			
			if(str[index]>=97 && str[index]<=122 ){
				if(arr[str[index]-97]!=nullptr)
					return (true && arr[str[index]-97]->search(str,index+1));
			//	else
			//		return true;
		   }
			return false;///Handles those situation where a non Roman Alphabet is present in Search word eg..  "c88pp"
		}
			
};

class Dict{
	public:
		Node root;
};

int main(){
	///////////////////////////////////////////////////////////////////
		FPgrowth objf;
		objf.readData("data.txt");
		objf.printTransactions();
		objf.countItems();
		objf.printItemCount();
		objf.sortTransactionItems();
		cout<<endl<<"After sorted according to Item count"<<endl<<endl;
		objf.printTransactions();
	///////////////////////////////////////////////////////////////////
	Node n(10);
	n.strinsert(objf.getTransaction());
	cout<<"Traversing tree"<<endl;
	n.traverseTree();
}

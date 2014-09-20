#include<string>
#include<iostream>
#include<cstring>
#include<fstream>
#include "fpgrowth.cpp"
using namespace std;

class Node{
	Node **arr;
	bool flag;
	int count;
	int numberOfItems;
	public:
		Node(int numberOfItems){
			this->numberOfItems=numberOfItems;
			count=0;
			arr=new Node*[numberOfItems];
			for(int i=0;i<numberOfItems;i++)
				arr[i]=nullptr;
			flag=false;
		}
	

		bool strinsert(vector<vector<Item> > transaction){
			if(arr==nullptr)
				arr=new Node*[numberOfItems]; 
			Node **tempArr;	
			for(int i=1;i<transaction.size();i++){
				tempArr=arr;
					for(int j=0;j<transaction[i].size();j++){
						
						if(tempArr[ transaction[i][j].getItemId() -1]==nullptr){
							    tempArr[ transaction[i][j].getItemId() -1 ]=new Node(numberOfItems);
							    (tempArr[ transaction[i][j].getItemId() -1 ])->count++;               
							    tempArr=tempArr[ transaction[i][j].getItemId() -1 ]->arr;
							
				        }else{
				        	
			            		(tempArr[ transaction[i][j].getItemId() -1 ])->count++;               
			            		tempArr=tempArr[ transaction[i][j].getItemId() -1 ]->arr;
			            		
			            }
					}
				
			}

		}

		void traverseTree(){
			
			for(int i=0;i<numberOfItems;i++){	
				if(arr[i]){
					cout<<" ( I"<<i+1<<" count:"<<arr[i]->count<<" ) "<<endl;
					(*arr[i]).traverseTree();
				}
			}
		}
			
			
		//Mining Function;	
		void minePattern(Node *root,Item leaf,int count ){
			
			//1. Build Transaction list by traversing the tree with root
			//2. Add all Items n the path to Item leaf.
			//3. Find the count of each item in transaction.
			//4. Prune all those elements which donot meet the minimum count
			//5. Build Tree
			//6. Pass the tree to this function(Recursively)
			//7. Base case: Return if root null
			
		}		
						
};

class Dict{
	public:
		Node root;
};

int main(){
		FPgrowth objf;
		objf.readData("data.txt");
		objf.printTransactions();
		objf.countItems();
		objf.printItemCount();
		objf.sortTransactionItems();
		cout<< endl<<"After sorted according to Item count"<<endl<<endl;
		objf.printTransactions();
		int count;
		count=objf.getMinSupport();
		objf.prune(count);
		objf.printPrunedTransaction();
		Node n(objf.getPTranLen());
		cout<<endl<<"Building Tree"<<endl;
		n.strinsert(objf.getTransaction());
		cout<<endl<<"Traversing tree"<<endl;
		n.traverseTree();
}

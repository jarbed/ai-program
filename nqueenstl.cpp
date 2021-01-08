#include<iostream>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;
int order=8;
long int count=0,safe_states=1;
vector<pair<int,int>> board;
bool is_safe(int row,int col)
{
	int i=0,k=board.size();
	while(i<k)
	{
		if(board[i].second==col/*row check*/||abs(board[i].first-row)==abs(board[i].second-col/*diagonal check*/))
			return false;
		i++;
	}
	return true;
}
void print_board()
{
	int k=board.size()-1,f=0;
	for(int i=0;i<order;i++,f++){
		for(int j=0;j<order;j++,f++,k--){
			if(i==board[k].first&&j==board[k].second)
				cout<<"Q ";
			else if(f%2==0)
				cout<<"W ";
			else
				cout<<"B ";
		}
		cout<<endl;
	}
}
void put_queen(int n)
{
	if(n>0){
		vector<pair<int,int>> safe_loc;
		int row=n-1,col;
		for(col=order-1;col>=0;col--){
			if(is_safe(row,col)){	//safety check
				pair<int,int> p(row,col);
				safe_loc.push_back(p);	//pushing safety loc to vector
				safe_states++;
			}
		}
		safe_loc.shrink_to_fit();
		while(!safe_loc.empty()){
			int pivot=rand()%safe_loc.size();	//choose location randomly
			pair<int,int> p=safe_loc.at(pivot);
			board.push_back(p);	//push safe loc to board
			put_queen(row);		//recursive call
			board.pop_back();	//pop pivot location from vector
			vector<pair<int,int>>::iterator it=safe_loc.begin();	//set iterator to the begining of vector
			safe_loc.erase(it+pivot);	//delete loc from safe loc vector
			safe_loc.shrink_to_fit();
		}
	}
	else{
		count++;
		cout<<"board number "<<count<<endl;
		print_board();
	}
}
int main()
{
	srand(time(0));
	put_queen(order);
	cout<<"total no. of permutation : "<<count<<endl;
	cout<<"totai no. of safe states : "<<safe_states<<endl;
	return 0;
}

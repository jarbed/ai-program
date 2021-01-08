#include<iostream>
#include<vector>
using namespace std;
bool **graph;	//2d adjacent matrix;
int num;	//number of vertex in the graph
void print_graph()
{
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++)
			if(graph[i][j]==true)
				cout<<"1 ";
			else
				cout<<"0 ";
		cout<<endl;
	}
}
void setgraph()
{
	cout<<"enter no. of nodes :";
	cin>>num;
	graph=new bool*[num];	//creating adj mat for graph
	for(int i=0;i<num;i++)
	{
		graph[i]=new bool[num];
	}
	for(int i=0;i<num;i++)
		for(int j=0;j<num;j++)	//setting default as false
			graph[i][j]=false;
	char c='y';
	while(c=='y')
	{
		int s1,s2;
		cout<<"enter two states"<<endl;
		cin>>s1>>s2;
		if(s1<num&&s2<num)	//setting true for edge between s1 and s2
		{
			graph[s1][s2]=true;
			graph[s2][s1]=true;
		}
		else
			cout<<"wrong entry try again : "<<endl;
		cout<<"press y to continue : ";
		cin>>c;
	}
}
vector<int> get_successor(int pivot)
{
	vector<int> succ;
	for(int i=0;i<num;i++)
		if(graph[i][pivot])	//if a node is adjacent to pivot
			succ.push_back(i);	//push it to succesor
	return succ;
}
bool graph_search(int source,int dest)
{
	vector<int> frontier;	//array to store the vertex to be explored
	vector<int> path;
	bool *explored;
	explored=new bool[num];	//creating array for checking if a vertex is explored
	for(int i=0;i<num;i++)
		explored[i]=false;	//setting all vertex to faulse as default
	frontier.push_back(source);	//pushing source to frontier to be explored first
	while(!frontier.empty())
	{
		int pivot=frontier[frontier.size()-1];	//selecting last element of frontier for exploration
		frontier.pop_back();	//deleting last element of frontier
		vector<int> succ;	//temporary frontier for storing successors
		path.push_back(pivot);
		succ=get_successor(pivot);	//getting successor of pivot
		explored[pivot]=true;	//setting pivot as explored
		for(int i=0;i<succ.size();i++)	//loop to add new vertex to frontier for explorations
			if(!explored[succ[i]]){	//if a succesors isn't already explored
				if(succ[i]==dest){	//if a successor is the destination
					for(int j=0;j<path.size();j++)
						cout<<path[j]<<"->";
					cout<<dest<<endl;
					return true;	//return true as path is found
				}
				else{
					bool flag=false;	//flag to determine if a successor already in frontier or not set to false by default
					for(int j=0;j<frontier.size();j++)	//checking if a succesor is already in frontier
						if(frontier[j]==succ[i]){
							flag=true;	//if a successor is already in frontier set flag to true
							break;	//no need to search more 
						}
					if(!flag)	//if a successor not in frontier then add it to frontier
						frontier.push_back(succ[i]);
			}
		}
	}
	return false;	//return false as no path found
}
int main()
{
	setgraph();
	print_graph();
	cout<<"enter source and destination :"<<endl;
	int source,dest;
	cin>>source>>dest;
	if(graph_search(source,dest))
		cout<<"reachable"<<endl;
	else
		cout<<"unreachale"<<endl;
}

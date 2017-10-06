#include <iostream>
#include "Queue.h"
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
using namespace cop4530;
void menu(int x, vector<string> y, vector<vector<int>> z);
void bfs(vector<vector<int>> x, vector<string> y);
int main(int argc, char* argv[])
{
	//check if file opens
	int x;
	string s;
	string line;
	if (argv[1] == 0)
	{
		cout << "Usage: proj3.x airline_file" << endl;
		return 0;
	}
	ifstream myfile(argv[1]);
	if (myfile.is_open())
	{
		//get number of cities, make vector of that value and store city names in it
		myfile >> x;
		getline(myfile, line);
		//declare vectors
		vector<string> namevec(x);
		vector< vector <int> > matrix(x, vector<int>(x));
		for (int i = 0; i < x; i++)
		{
			getline (myfile, line);
			namevec[i] = line;
		}
	
		//nested for loops to parse matrix and store in a 2D array
		for (int i= 0; i < x; i++)
		{
			for (int j = 0; j < x; j++)
			{
				int temp;
				myfile >> temp;
				matrix[i][j] = temp;
			}
		}
		//close file, initialize menu
		myfile.close();
		menu(x, namevec, matrix);
		bool q = true;
		string answer;
		//keep prompting new source/dest unless terminated
		while (q)
		{
			bfs(matrix, namevec);
			cout << "Search another route? (Y/N)";
			cin >> answer;
			while (answer != "Y" && answer != "y" && answer != "N" && answer != "n")
			{
				cout << "Search another route? (Y/N)";
				cin >> answer;
			}
			if(answer == "N" || answer == "n")
				q = false;
		}
	}
	else 
		cout << "Usage: proj3.x airline_file" << endl;
	
	return 0;



}
//initial printing of cities and direct flights
void menu(int x, vector<string> y, vector<vector<int>> z)
{
	cout << x << " cities:" << endl;
	for (int i = 0; i < y.size(); i++)
		cout << '\t' << y[i] << endl;
	cout << endl;
	cout << "direct flights between cities" <<endl;
	cout << "-------------------------" << endl;
	for (int i = 0; i < z.size(); i++)
	{
		cout << y[i] << ":" << endl;
		for (int j = 0; j < z.size(); j++)
		{
			if (z[i][j] > 0)
				cout << '\t' << y[j] << ", $" << z[i][j] << endl;
			
		}
	}
	cout << "-------------------------" << endl;
	cout << endl;
}

void bfs (vector<vector<int>> x, vector<string> y)
{
	//declare variables
	string temp1, temp2;
	vector<int> vec1;
	vector<int> vec2;
	Queue<int> queue;
	cout << "Source city : ";

	//because input can be two words use getline
	cin >> ws;
	getline(cin, temp1);
	cout << "Destination city : ";
	cin >> ws;
	getline(cin, temp2);

	cout << "finding min_hop route..." << endl;
	//find the cities located in their vector, print otherwise
	auto it = find (y.begin(), y.end(), temp1);
	if (it == y.end())
	{
		cout << "\tpath not found, source city, "<< temp1 << ", not on the map" << endl;
		return;
	}
	auto it2 = find (y.begin(), y.end(), temp2);
	if (it2 == y.end())
	{
		cout << "\tpath not found, destination city, "<< temp2 << ", not on the map" << endl;
		return;
	}
	//convert iterators to ints for later use
	int d = distance(y.begin(), it2);
	int sc = distance (y.begin(), it);
	bool search = false;
	queue.push(sc);
	//actual bfs
	while (!queue.empty())
	{
		auto j = queue.front();
		for (int i = 0; i < y.size(); i++)
		{
			if(x[j][i] > 0)
			{
				vec1.push_back(j);
				vec2.push_back(i);
				queue.push(i);
				if (i == d)
				{
					search = true;
					break;
				}
			}
		}
		queue.pop();
		if (search)
			break;
	}
	//getting the path
	vector<int> path;
	search = false;
	path.push_back(d);
	auto j = find (vec2.begin(), vec2.end(), d);
	int s = distance(vec2.begin(), j); 
	if (vec1[s] == sc)
		path.push_back(vec1[s]);
	else
	{
		path.push_back(vec1[s]);
		while (!search)
		{
			auto k = find (vec2.begin(), vec2.end(), vec1[s]);
			s = distance (vec2.begin(), k);
			if (vec1[s] == sc)
			{
				path.push_back(vec1[s]);
				search = true;
			}
			else
			{
				path.push_back(vec2[s]);
				path.push_back(vec1[s]);
				continue;
			}
		}
	}
	//erase duplicates and reverse vector
	path.erase(unique (path.begin(), path.end()), path.end());
	reverse(path.begin(), path.end());
	int total = 0;
	cout << '\t';
	int i;
	for (i = 0; i < path.size() - 1 ; i++)
	{
		//calculate ticket prices 
		total+= x[path[i]][path[i+1]];
		cout << y[path[i]] << " -> ";
	}	
	cout << y[path[i]] <<", $" << total << endl;
}`

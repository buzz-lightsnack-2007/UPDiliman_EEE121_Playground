# include <iostream>
# include <iomanip>
# include <vector>
using namespace std;



int main(){
	srand(2346);
	for(int i = 0; i < 5; i++){
		cout << rand()%3 << "|";
	};

	cout << endl;
	vector< vector<int> > container;
	vector<int> temp;
	cout << "Initializaing" << endl;
	for(int i = 0; i < 5; i++){
		temp = vector<int>{0,0,0,0,0,0,0};
		container.push_back(temp);
	};

	cout << "Dropping" << endl;
	for(int j = 0; j < 5; j++){
		for(int k = 0; k < 7; k++){
			cout << setw(3) <<setfill('0') << container[j][k] << "|";
		}
		cout << endl;
	}
}
# include <iostream>
using namespace std;
# include <vector>

vector <vector <int>> allb;

void bingen(vector <int> bin ,int n){
	if(bin.size() == n){
		allb.push_back(bin);
	}else{
		for(int i = 0; i < 2; i++){
			bin.push_back(i);
			bingen(bin, n);
			bin.pop_back();
		}
	}
}

int main(){
	vector <int> empty;
	bingen(empty,4);
	for(int i = 0; i < allb.size(); i++){
		for(int j = 0; j < allb[i].size(); j++){
			cout << allb[i][j] << "|";
		}
		cout << endl;
	}
}

# include <iostream>
using namespace std;
# include <vector>

vector <vector <int>> allb;

/**
 * Generates 3-ary numbers of length n. 
 * 
 * @param bin (vector<int>) binary
 * @param n (int) size
 */
void bingen(vector <int> bin ,int n){
	if(bin.size() == n){
		allb.push_back(bin);
	}else{
		// Each entry can have any integer from 0 to 3; loop it through
		for(int i = 0; i < 3; i++){ // Take this! 
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

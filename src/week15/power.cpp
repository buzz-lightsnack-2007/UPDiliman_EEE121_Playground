# include <iostream>
# include <vector>
# include <map>
using namespace std;

class Power_Solution {
	public: 
		map<int, int> results;

		/**
		 * Test if a number is stored into cache. 
		 * 
		 * @param number (int) - the query number
		 * @return true - if cached
		 * @return false - otherwise
		 */
		bool cached(int number) {
			auto cursor = this->results.find(number); 
			return (cursor != this->results.end()); 
		};
		int count; 

		/**
		 * Clear solution data
		 */
		void reset() {
			this->results.clear(); 
			this->results[0] = 1; 
			this->count = 0;
		};
		
		Power_Solution() {
			this->reset(); 
		}; 

		int memoize(int m, int n) {
			this->count++; 

			vector<int>ps;
			int p; int temp;
			
			if (this->cached(n)) {
				return this->results[n]; 
			}; 

			for(int i = 0; i < 4; i++){
				ps.push_back(memoize(m,n/4));
			}; 

			int result; 
			if(n%4==0){
				p = 1;
				for(int i = 0; i < 4;i++){
					p = p*ps[i];
				}
				result = p; 
			} else {
				temp = 1;
				for(int i = 0 ;i < n%4;i++){
					temp = temp*m;
				}
				p = 1;
				for(int i = 0; i < 4;i++){
					p = p*ps[i];
				}; 
				result = p*temp; 
			}; 

			this->results[n] = result; 
			return result; 
		};

		/**
		 * Run the tabulated function. 
		 * 
		 * @param m 
		 * @param n 
		 * @return int 
		 */
		int tabulate(int m, int n) {
			this->reset(); 
			this->count++; 
			
			int rounds = n / 4;
			for (int iteration = 0; iteration < rounds; iteration++) {
				int p; 
				int ps; // The power solution

				ps = this->results[iteration * 4]; 
				// Always a multiple of 4
				for(int i = 0; i < 4;i++){
					ps *= m; 
				};

				this->results[(iteration + 1) * 4] = ps; 
			};

			if (n % 4) {
				int temp = 1; // Temporary value

				for(int i = 0; i < (n % 4); i++){
					temp *= m;
					this->results[rounds * 4 + i + 1] = this->results[rounds * 4] * temp; 
				}; 

				this->results[n] = this->results[rounds * 4] * temp; 
			}; 

			return this->results[n]; 
		};
	
		/**
		 * The 'default' power solution
		 * 
		 * @param m 
		 * @param n 
		 * @return int 
		 */
		int def(int m,int n){
			this->count++; 
			vector<int>ps;
			int p;
			int temp;

			if(n == 0){
				return 1;
			}

			for(int i = 0; i < 4; i++){
				ps.push_back(this->def(m,n/4));
			}

			if(n%4==0){
				p = 1;
				for(int i = 0; i < 4;i++){
					p = p*ps[i];
				}
				return p;
			}else{
				temp = 1;
				for(int i = 0 ;i < n%4;i++){
					temp = temp*m;
				}
				p = 1;
				for(int i = 0; i < 4;i++){
					p = p*ps[i];
				}
				return p*temp;
			}
		};
};

int main(){
	Power_Solution solution; 

	cout << "\033[1m" << "Default: " << "\033[0m"; 
	for(int i = 0; i<10;i++){
		solution.reset(); 
		cout << solution.def(4,i) << " (" << solution.count << ")"; 

		if (i < 9) {
			cout << ", "; 
		} else {
			cout << endl; 
		}; 
	};

	cout << "\033[1m" << "Memoized: " << "\033[0m"; 
	for(int i = 0; i<10;i++){
		solution.reset(); 
		cout << solution.memoize(4,i) << " (" << solution.count << ")"; 

		if (i < 9) {
			cout << ", "; 
		} else {
			cout << endl; 
		}; 
	}; 

	int num = 4; 
	int result = solution.tabulate(num, num + 3);
	cout << result << endl; 
	for (int index = 0; index < num + 5; index++) {
		cout << index << "\t"; 
		if (solution.cached(index)) {
			cout << solution.results[index]; 
		} else {
			cout << "N/A"; 
		}; 
		cout << endl; 
	};
}

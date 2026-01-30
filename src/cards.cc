# include <iostream>

using namespace std; 

class Card {
	private: 
		int cinfo[2] = {0, 0}; 
	
		/**
		 * Add two numbers. 
		 * @param original (int) - the number to add to
		 * @param increment (int) - the number to increment by (default: 13)
		 * @return (int) the new number
		 */
		int add(int original, int increment = 13) {
			return original + increment; 
		};

		/**
		 * Add a number to the original variable. 
		 * @param original (int*) - the original value to be updated
		 * @param increment (int) - the number to increment by (default: 13)
		 * @return (int) the new number; original variable would be updated 
		 */
		int add(int* original, int increment = 13) {
			*original = *original + increment; 
			return *original; 
		};

	public: 
		/**
		 * Constructs a new Card object
		 * 
		 * @param face (int) - the face value
		 * @param suit (int) - the suit number
		 */
		Card(int face, int suit) {
			face = abs(face); // Coerce them to be positive
			suit = abs(suit); 
			
			// Then validate the inputs
			if (face && face <= 13) {this->cinfo[0] = face;}; 
			if (suit && suit <= 4) {this->cinfo[1] = suit; };
		};

		/**
		 * The card's face value
		 * 
		 * @return int 
		 */
		int face() {
			return this->cinfo[0]; 
		};

		/**
		 * The card's suit ID
		 * 
		 * @return int 
		 */
		int suit() {
			return this->cinfo[1]; 
		};

		/**
		 * Get the higher card among this instance and the higher one. If there is a tie, the suit will be used as a fallback. 
		 * 
		 * @param other (Card) - the other card
		 * @return Card 
		 */
		Card swaphigher(Card other) {
			int faces[2] = {this->cinfo[0], other.face()}; // The face values for comparison
			int suits[2] = {this->cinfo[1], other.suit()}; // The suit IDs for comparison

			int difference = faces[1] - faces[0]; // The difference

			// Fallback case: when face values are the same
			if (!difference) {
				difference = suits[1] - suits[0]; // Compare the suits instead
			};
			
			if (difference > 0) {
				return other; 
			} else if (difference < 0) {
				Card returnable(this->face(), this->suit()); // Create a copy of this card
				return returnable; 
			};
		};

		/**
		 * Display the card. 
		 */
		void printcard() {
			cout << this->cinfo[0] << "\t" << this->cinfo[1];
		};

		int plus13pbv(int original) {
			return this->add(original);
		}; 

		int plus13pbr(int* original) {
			return this->add(original);
		};
};

Card who_is_higher(Card card_1, Card card_2, bool verbose = false) {
	Card *cards[2] = {&card_1, &card_2};
	if (verbose) {
		cout << "Cards:" << endl;
		for (int index = 0; index < 2; index++) {
			cout << index +1 << "、\t"; 
			(*cards[index]).printcard();
			cout << endl;
		};
	};

	Card result = (*cards[0]).swaphigher((*cards[1])); 
	cout << "Higher: \t"; result.printcard(); cout << endl;

	return result; 
};

bool addition_testing(Card card_1) {
	int numbers[2] = {99, 99}; 
	numbers[0] = card_1.plus13pbv(numbers[0]);
	card_1.plus13pbr((numbers + 1));
	bool ok = !(*(numbers) - *(numbers + 1)); 

	cout << "\033[3"; 
	if (ok) {cout << "2";} else {cout << "1";}
	cout << "mAddition "; 
	if (!ok) {cout << "not ";}; 
	cout << "OK. " << "\033[0m" << "Got ";

	if (ok) {cout << "both " << numbers[0]; 
	} else {cout << numbers[0] << " and " << numbers[1]; }; 
	cout << endl;

	return ok;
};

int main() {
	Card c_1{13, 3}; 
	Card c_2{13, 4}; 
	Card c_3{10, 4}; 
	Card c_4{4, 2}; 

	who_is_higher(c_1, c_2, true);
	who_is_higher(c_2, c_3, true);
	who_is_higher(c_1, c_3, true);
	who_is_higher(c_4, c_3, true);

	addition_testing(c_1);
};


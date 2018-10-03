/*
	This program finds all possible solutions in a round of boggle.
	Additionally, it will display a histogram of the frequency in 
	word size and top 10 top scoring words.

	Eventually, it will be expanded to keep track of the "paths" that
	the program had to take to find each word and display that to the
	user as well.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Forward Declarations

void build_board(string row_input, int row_number);
void print_board();
void start_location();
void crawler(int row_start, int col_start, string building_charachters);
bool part_of_word(string building_characters);
bool move_permission(int check_row, int check_column);
void word_found(string found_word);

// Global Counters



// Global Boggle Array (This does not get modified)
string boggle_board [4][4] = {""};

// Global board array that keeps track of whether a position is being occupied by the crawler.
bool occupied_spaces[4][4] = {false};

// Global Variables
int found_count = 0;

int main()
{

	// Get row user input
	string row_input;

	cout << "Welcome to the Boggle Solver!\n\n";
	cout << "This program will compute every possible word on the board\n\n";
	cout << "Please enter the letters on the rows (Qu is q)\n";

	cout << "First Row: ";
	cin >> row_input;
	build_board(row_input, 0);

	cout << "Second Row: ";
	cin  >> row_input;
	build_board(row_input, 1);

	cout << "Third Row: ";
	cin >> row_input;
	build_board(row_input, 2);

	cout << "Fourth Row: ";
	cin >> row_input;
	build_board(row_input, 3);

	cout << "Test \n";
	print_board();

	start_location();
	cout << endl;
	cout << found_count << (found_count != 1 ? " words " : " word ") << "found this round!" << endl;
	print_board();
	cout << endl;
}

/*
*	This function takes the user input for each row and puts it into the main 
*	boggle board array. It also filters user input so the program wont crash.
*	If a user inputs 'q', it will add a 'u' after it.
*
*	Parameters:
*		string - input from the given row
*		int - the row that the input is coming from.
*
*	Returns: none
*/

void build_board(string row_input, int row_number)
{
	for(int i = 0; i < row_input.length(); i++)
	{
		boggle_board[row_number][i] = row_input[i];
		if(row_input[i] == 'q')
			boggle_board[row_number][i] += 'u';
	}
}

/*
*	This function simply prints the board to the screen. This is mostly for 
*	testing purposes.
*
*	No parameters or returns.
*/

void print_board()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			cout << boggle_board[i][j] << " ";
		cout << endl;
	}
}

/*
*	This function acts as a guide for the crawler, giving it a starter location
*
*	No Parameters
*
*
*/

void start_location()
{
	for(int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			cout << "\nNow at " << row << " " << column << endl << endl;
			
			string seed = boggle_board[row][column];
			crawler(row, column, seed);
		}
	}
}

/*
*	This function is meant to start at a start location on the board and check
*	around that location for places to possibly move. Will start by checking the above
*	square, if no permission, move clockwise, but it is possitive, the function will call
*	itself in that new location
*
*	Parameters:
*		int - row component that the function will start at and look around 
*		int - column component that the function will start at and look around
*
*	No returns.
*/

void crawler(int row_start, int col_start, string building_characters)
{
	//This marks the location where the crawler is sitting as occupied.
	cout << building_characters << endl;

	occupied_spaces[row_start][col_start] = true;

	int surrounding_locations[2][8] = {0};

	surrounding_locations[0][0] = row_start - 1;
	surrounding_locations[0][1] = row_start - 1;
	surrounding_locations[0][2] = row_start;
	surrounding_locations[0][3] = row_start + 1;
	surrounding_locations[0][4] = row_start + 1;
	surrounding_locations[0][5] = row_start + 1;
	surrounding_locations[0][6] = row_start;
	surrounding_locations[0][7] = row_start - 1;

	surrounding_locations[1][0] = col_start;
	surrounding_locations[1][1] = col_start + 1;
	surrounding_locations[1][2] = col_start + 1;
	surrounding_locations[1][3] = col_start + 1;
	surrounding_locations[1][4] = col_start;
	surrounding_locations[1][5] = col_start - 1;
	surrounding_locations[1][6] = col_start - 1;
	surrounding_locations[1][7] = col_start - 1;

	for (int next_location = 0; next_location < 8; next_location++)
		{
			if(!move_permission(surrounding_locations[0][next_location], surrounding_locations[1][next_location]))
				continue;

			building_characters += boggle_board[surrounding_locations[0][next_location]][surrounding_locations[1][next_location]];
			//cout << " *" << building_characters << "* ";
			if(!part_of_word(building_characters))
			{
				building_characters.erase(building_characters.size() - 1);
				continue;
			}

			crawler(surrounding_locations[0][next_location], surrounding_locations[1][next_location], building_characters);

			building_characters.erase(building_characters.size() - 1);
			}

	occupied_spaces[row_start][col_start] = false;

}

/*
*	This function is meant to make sure that a crawler move is legal
*	so that it does not move to a square that is already being used
*	or is off the 4x4 grid.
*
*	Parameters:
*		int - the row that is being checked
*		int - the row that is beign checked
*
*	Returns:
*		bool - true if aloud to move to the square and false if not.
*/

bool move_permission(int check_row, int check_column)
{

	// Checks if the crawler is within the boundaries
	
	if((check_row < 0 || check_row > 3) || (check_column < 0 || check_column > 3))
		return false;

	// Check if the crawler is currently occupying that space
	
	if(occupied_spaces[check_row][check_column] == true)
		return false; 

	//cout << "^";
	// Checks to see if the

return true;
}

/*
*	This function recieves built text from the crawler and checks to
*	see if there are any words that start with that built text.
*	this program will also check to see if a whole word can be made,
*	in which case it will send the whole word to another function to be
*	stored.
*
*	Parameters:
*		string - the built text from crawler
*
*	Return:
*		bool - true if the built text is at the beginning of some word.
*/

bool part_of_word(string building_characters)
{
	//cout << ")";
	ifstream dictionary("words.txt");

	while(true)
	{
		bool match = true;
		string word;
		dictionary >> word;

		if(dictionary.fail())
		{
			//cout << "!";
			return false;
		}
		if(word.length() < building_characters.length())
			continue;

		for(int pos = 0; pos < building_characters.length(); pos++)
			if(word[pos] != building_characters[pos])
			{
				match = false;
				break;
			}
		if(match == false)
			continue;

		if(building_characters == word)
			word_found(building_characters);
		
		dictionary.close();
		return true;
	}
}


/*
*	This function takes a completed word that was found and checks to
*	make sure it has not already been found. If the made word is 
*	already found or is smaller than 3 characters, the program will not
*	save it.
*	
*	Parameters:
*		string - the completed word that the part_of_word found.
*
*	No Returns
*/
ofstream save_found("found.txt");
void word_found(string found_word)
{
	bool match = false;
	ifstream found_words("found.txt");

	while(true)
	{
		string already_found;
		found_words >> already_found;

		if(found_words.fail())
			break;
		if(found_word == already_found)
			return;
	}

	cout << "Found a word!!  : " << found_word << endl;
	found_word += "\t";
	found_count++;
	save_found << found_word << endl;

return;
}

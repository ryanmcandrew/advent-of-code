#include <iostream> 
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

char alphabet [] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z'
};
int twice, thrice = 0;

vector<string> ParseLetterCount( string file );
void PrintLetterMap( vector<string> strings );

bool LevenshteinDistance( int distance, string str, string str2 );
void FindPair( vector<string> strings );

int main( ) {
	
	vector<string> list = ParseLetterCount("input.io");
	PrintLetterMap(list);
	cout << endl << endl;
	FindPair(list);


	// PrintLetterMap(); 


	return 0;
}

void FindPair( vector<string> strings ) {

	bool found = false;
	
	struct matches {
		string left = "";
		string right = "";
	} matches;

	for ( int i = 0; i < strings.size() && !found; i++ ) {

		for ( int j = 0; j < strings.size() && !found; j++ ) {

			if ( LevenshteinDistance( 1, strings[i], strings[j] ) ) {
				found = true;
				matches.left = strings[i];
				matches.right = strings[j];
			}

		}

	}

	cout << "results: " << endl << "\ta: -" << matches.left;
	cout << endl << "\tb: -" << matches.right << endl << endl;

}

bool LevenshteinDistance( int distance, string str, string str2 ) {

	bool isDistance = true;
	int isOfDistance = 0;

	if ( str.length() == str2.length() ) {
		for ( int i = 0; i < str.length() && isDistance; i++ ) {
			if ( str[i] != str2[i] ) {
				isOfDistance++;
			}
			if ( isOfDistance > distance ) {
				isDistance = false;
			}
			if ( i == str.length() - 1 ) {
				if ( isOfDistance < distance ) {
					isDistance = false;
				}
			}
		}
	}

	return isDistance;
}

vector<string> ParseLetterCount( string file ) {

	ifstream input;
	string data;
	map<char, int> result;
	vector<string> output;
	bool foundTwo, foundThree = false;

	input.open( file.c_str() );

	while ( !input.eof() ) {
		input >> data;
		output.push_back(data);
		if ( data != "" ) {
			for ( int i = 0; i < data.length(); i++ ) {
				result[ data[i] ]++;
			}

			for ( int i = 0; i < 26; i++ ) {
				if ( result[ alphabet[i] ] == 2 && !foundTwo ) {
					twice++;
					foundTwo = true;
				}
				else if ( result[ alphabet[i] ] == 3 && !foundThree ) {
					thrice++;
					foundThree = true;
				}
			}
			foundTwo = foundThree = false;
			result.clear();
		}
	}

	return output;
}

void PrintLetterMap( vector<string> strings ) {

	for ( vector<string>::iterator i = strings.begin(); i != strings.end(); i++  ) {
		cout << *i << endl;
	}

	cout << endl << endl;

	cout << "________________________________________________________________________" << endl;

	cout << endl << endl;
	cout << "Twos counted: " << twice << endl;
	cout << "Threes counted: " << thrice << endl;
	cout << "Checksum: " << twice * thrice << endl;

	
}

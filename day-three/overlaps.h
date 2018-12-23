#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <cstdlib>
#include <climits>

namespace DayThree {

	const std::string DB_NAME = "data.io";

	struct LineFormat {
		//#1 @ 1,3: 4x6
		//0123456789
		int id;
		char amp;
		bool intersects = false;
		int aBounds[ 2 ]; //aBounds[0] = 1 aBounds[1] = 4 in above format example
		int bBounds[ 2 ]; //bBounds[0] = 3 bBounds[1] = 6 in above format example

	};

	struct FileRepresentation {
		int max, min;
		std::vector<LineFormat> entries;
	};

	void ExecuteApp();
	//pre:
	//post:

	std::vector<LineFormat> Load( std::string file, FileRepresentation & db );
	//pre:
	//post:

	LineFormat ParseLine( std::string line );
	//pre:
	//post:

	void PrintArray( std::vector<LineFormat> arr );
	//pre:
	//post:
	//#1 @ 1,3: 4x6
	//#1309 @ 116,813: 26x21

	int Intersections(int max, std::vector<LineFormat> & entries );
	//pre:
	//post:
	//

	LineFormat search( std::vector<LineFormat> entries );
	//pre:
	//post:
	//

	void ExecuteApp() {

		FileRepresentation db;
		LineFormat res;

		std::cout << "beginning app..." << std::endl;

		db.min = INT_MAX;
		db.max = INT_MIN;
		db.entries = Load( DB_NAME, db );


		std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "min:" << db.min << std::endl;
		std::cout << "max:" << db.max;
		std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << std::endl << Intersections(1001, db.entries) << std::endl;

		res = search(db.entries);

		PrintArray(db.entries);
		// if ( res.intersects == false ) {
		// 	std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		// 	std::cout << "id of claim with no overlaps:" << res.id << std::endl;
		// 	std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		// }

		std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 

	}

	LineFormat search( std::vector<LineFormat> entries ) {

		LineFormat result;
		result.intersects = true;
		std::vector<LineFormat>::iterator i = entries.begin();
		bool found = false;

		for ( i; i != entries.end() && !found; i++ ) {

			if ( ! i->intersects ) {
				result = *i;
				std::cout << "id of claim with no overlaps:" << i->id << std::endl;
				found = true;
			}
		}

		return result;

	}

	int Intersections(int max, std::vector<LineFormat> & entries ) {

		bool visited[max][max];
		bool visitedTwice[max][max];
		std::vector<LineFormat>::iterator i = entries.begin();
		int result = 0;

		for ( int i = 0; i < max; i++ ) {

			for ( int j = 0; j < max; j++ ) {

				visited[i][j] = false;
				visitedTwice[i][j] = false;

			}

		}

		//#1 @ 1,3: 4x6
		//aBounds[0] = 1 aBounds[1] = 4 in above format example
		//bBounds[0] = 3 bBounds[1] = 6 in above format example

		for ( i; i != entries.end(); i++ ) {

			for ( int m = 0; m < i->aBounds[1]; m++ ) {

				for ( int n = 0; n < i->bBounds[1]; n++ ) {

					
					if ( !visited[ i->aBounds[0] + m ][ i->bBounds[0] + n ] ) {
						visited[ i->aBounds[0] + m ][ i->bBounds[0] + n ] = true;
					}
					else {

						if ( !visitedTwice[ i->aBounds[0] + m ][ i->bBounds[0] + n ] ) {
					// std::cout << std::endl << i->aBounds[0] + m << " " << i->bBounds[0] + n << std::endl;
							result++;
							i->intersects = true;
							std::vector<LineFormat>::iterator j = entries.begin();

							for ( j; j != i; j++ ) {
								if ( i->aBounds[0] >= j->aBounds[0] && i->aBounds[0] <= ( j->aBounds[0] + j->aBounds[1] )
									&& i->bBounds[0] >= j->bBounds[0] && i->bBounds[0] <= ( i->bBounds[0] + j->bBounds[1] )
									) {
									j->intersects = true;
								std::cout << std::endl << "here" << std::endl;
								}
							}

							visitedTwice[ i->aBounds[0] + m ][ i->bBounds[0] + n ] = true;
						}

					}

				}

			}

		}

		return result;
	}

	std::vector<LineFormat> Load( std::string file, FileRepresentation & db ) {

		std::vector<LineFormat> result;
		std::ifstream filectx;
		std::string junk;

		filectx.open(file.c_str());
		while ( !filectx.eof() ) {
			LineFormat data;
			getline(filectx, junk);
			data = ParseLine(junk);
			if ( data.aBounds[0] < db.min ) {
				db.min = data.bBounds[0];
			}

			if ( data.bBounds[0] < db.min ) {
				db.min = data.bBounds[0];
			}

			if ( data.aBounds[0] > db.max ) {
				db.max = data.aBounds[0];
			}

			if ( data.bBounds[0] > db.max ) {
				db.max = data.bBounds[0];
			}

			result.push_back(data);
		}

		return result;

	}

	LineFormat ParseLine( std::string line ) {
	//#1 @ 1,3: 4x6
	//#1309 @ 116,813: 26x21

		LineFormat result;
		std::string data;

		result.id = atoi(line.substr(1,  line.find("@") - 1 ).c_str());
		result.aBounds[0] = atoi( line.substr( line.find("@") + 2 , line.find(",") - 1 ).c_str() );
		result.bBounds[0] = atoi( line.substr( line.find(",") + 1, line.find(":") - 1 ).c_str()  );
		result.aBounds[1] = atoi( line.substr(line.find(":") + 2, line.find("x") - 1 ).c_str() );
		result.bBounds[1] = atoi( line.substr(line.find("x") + 1, std::string::npos).c_str() );

		return result;

	}

	void PrintArray( std::vector<LineFormat> arr ) {

		std::vector<LineFormat>::iterator i;

		for ( i = arr.begin(); i != arr.end(); i++ ) {
			std::cout << "id: " << i->id << std::endl;
			std::cout << "intersects: " << i->intersects << std::endl;
			std::cout << "aBounds[0]: "<< i->aBounds[0] << std::endl;
			std::cout << "aBounds[1]: " << i->aBounds[1] << std::endl;
			std::cout << "bBounds[0]: " << i->bBounds[0] << std::endl;
			std::cout << "bBounds[1]: " << i->bBounds[1] << std::endl;
		}

	}

}
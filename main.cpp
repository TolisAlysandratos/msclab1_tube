#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

#include "tube.h"

int main() {

	/* This code illustrates the use of the pre-supplied helper functions and the
	 * functions that you are supposed to write. */

	cout << "============== Pre-supplied functions ==============" << endl << endl;

	char** map;
	int height, width;

	cout << "Loading tube map with load_map():";

	/* loads the map from the file "map.txt" and sets height and width */
	map = load_map("map.txt", height, width);
	assert(map);
	cout << " done (height = " << height << ", width = " << width
			 << ")." << endl << endl;
	cout << "Printing map with print_map():" << endl;

	/* prints the map with row and column numbers */
	print_map(map,height,width);
	cout << endl;

	
	cout << "====================== Question 1 ==================" << endl << endl;

	int r, c;
	bool success = get_symbol_position(map, height, width, 'T', r, c);
	cout << "The symbol 'T' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	success = get_symbol_position(map, height, width, '4', r, c);
	cout << "The symbol '4' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	success = get_symbol_position(map, height, width, 'z', r, c);
	cout << "The symbol 'z' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	// Additional tests for Question 1
	for (char symbol = 0; symbol < 127; symbol++)
	  {
	    success = get_symbol_position(map, height, width, symbol, r, c);
	    cout << "The symbol '" << symbol << "' is ";
	    if(success) {
	      cout << "found at (" << r << "," << c << ")";
	    } else {
	      cout << "not found.";
	    }
	    cout << endl << endl;
	  }

	cout << "====================== Question 2 ==================" << endl << endl;

	cout << "The symbol for Victoria station is '" <<
	  get_symbol_for_station_or_line("Victoria") << "'" << endl << endl;

	cout << "The symbol for Oxford Circus station is '" <<
	  get_symbol_for_station_or_line("Oxford Circus") << "'" << endl << endl;

	cout << "The symbol for the District Line is '" <<
	  get_symbol_for_station_or_line("District Line") << "'" << endl << endl;
       
	/* Birmingham station is not on the Tube map, so this should return ' ' */
	cout << "The symbol for Birmingham station is '"
	     << get_symbol_for_station_or_line("Birmingham") << "'" << endl << endl;

	// Additional tests for Question 2
	cout << "The symbol for the  District Line is '" <<
	  get_symbol_for_station_or_line(" District Line") << "'" << endl << endl;

	cout << "The symbol for the Edgware Road (Circle Line) is '" <<
	  get_symbol_for_station_or_line("Edgware Road (Circle Line)") << "'" << endl << endl;

	cout << "The symbol for the Edgware Road (Bakerloo Line) is '" <<
	  get_symbol_for_station_or_line("Edgware Road (Bakerloo Line)") << "'" << endl << endl;
	

	cout << "====================== Question 3 ==================" << endl << endl;

	char route[512];
	char destination[512] = "nowhere";
	
	/* valid route to Leicester Square with 1 line change */
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	int result = validate_route(
			map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of backtracking between stations */
	strcpy(route, "W,W,E,W,W,W");
	cout << "Starting at Sloane Square and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(
			map, height, width, "Sloane Square", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result
			<< " line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because route goes outside of map bounds */
	strcpy(route, "E,NE,SE,SE,SE");
	cout << "Starting at Marylebone and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Marylebone", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* Add more of your own tests here. */

	/* invalid because of start_station string */
	cout << "===invalid because of start_station string===" << endl;
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus  and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Oxford Circus ", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;
	
	/* invalid route because of route string error */
	cout << "===invalid because of route string error===" << endl;
	strcpy(route, "S,SE,S,S ,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of route string error */
	cout << "===invalid because of route string error===" << endl;
	strcpy(route, "S,SE,S,S,WE,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of route string error */
	cout << "===invalid because of route string error===" << endl;
	strcpy(route, "S,SE,S,S,EW,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of route string error */
	cout << "===invalid because of route string error===" << endl;
	strcpy(route, "S,SE,S,S,NS,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because route goes outside the map */
	cout << "===invalid because route goes outside the map===" << endl;
	strcpy(route, "E,E,NE,E");
	cout << "Starting at Marylebone and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Marylebone", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because route goes outside the map */
	cout << "===invalid because route goes outside the map===" << endl;
	strcpy(route, "E,E,SE,E");
	cout << "Starting at Southwark and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Southwark", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because route goes outside the map */
	cout << "===invalid because route goes outside the map===" << endl;
	strcpy(route, "S,S,E,E");
	cout << "Starting at Aldgate and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Aldgate", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;
	
	/* invalid route because route goes outside the line/track or station */
	cout << "===invalid because route goes outside the line/track or station===" << endl;
	strcpy(route, "E,E,S,SE,SE");
	cout << "Starting at Marylebone and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Marylebone", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of line hopping */
	cout << "===invalid because of line hopping===" << endl;
	strcpy(route, "E,E,E,NE");
	cout << "Starting at Baker Street and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Baker Street", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of backtracking between stations */
	cout << "===invalid route because of backtracking between stations===" << endl;
	strcpy(route, "W,E,W,W,W");
	cout << "Starting at Baker Street and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(
			map, height, width, "Baker Street", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result
			<< " line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;
	
	/* invalid route because endpoint not a station */
	cout << "===invalid route because endpoint is not a station (missing last direction)===" << endl;
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;	

	/* valid route to Waterloo with 0 line changes to check end station character limits */
	cout << "===valid route to Waterloo with 0 line changes to check end station character limits===" << endl;
	strcpy(route, "W,W,W,W,W,NW");
	cout << "Starting at Southwark and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Southwark", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* valid route to Holborn with 2 line changes */
	cout << "===valid route to Holborn with 3 line changes (including valid change of direction on same line i.e. at station)===" << endl;
	strcpy(route, "NE,E,E,E,E,E,E,E,E,E,E,SE,S,S,S,S,S,E,E,E,E,E,E,E,W,W,W,W,W,W,W,W,W,W,NW,NW,N,NW,W,NW,W,W,W,W,S,S,SW,S,S,S,S,S,S,SW");
	cout << "Starting at King's Cross and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Kings Cross", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* is_station test*/
	cout << "is_station('0'): " << is_station('0') << endl;	
	cout << "is_station('A'): " << is_station('A') << endl;
	cout << "is_station('Z'): " << is_station('Z') << endl;
	cout << "is_station('['): " << is_station('[') << endl;
	cout << "is_station('`'): " << is_station('`') << endl;
	cout << "is_station('a'): " << is_station('a') << endl;
	cout << "is_station('r'): " << is_station('r') << endl;	
	cout << "is_station('s'): " << is_station('s') << endl;
	cout << endl;
	
	/* is_line test */
	cout << "is_line('*'): " << is_line('*') << endl;
	cout << "is_line('/'): " << is_line('/') << endl;
	cout << "is_line('<'): " << is_line('<') << endl;
	cout << endl;

	/* get_name_for_symbol */
	cout << "get_name_for_symbol(\"stations.txt\", 'A'): " << get_name_for_symbol("stations.txt", 'A') << endl;
	cout << "get_name_for_symbol(\"stations.txt\", 'Z'): " << get_name_for_symbol("stations.txt", 'Z') << endl;
	cout << "get_name_for_symbol(\"stations.txt\", '0'): " << get_name_for_symbol("stations.txt", '0') << endl;
	cout << "get_name_for_symbol(\"stations.txt\", '9'): " << get_name_for_symbol("stations.txt", '9') << endl;
	cout << "get_name_for_symbol(\"stations.txt\", 'a'): " << get_name_for_symbol("stations.txt", 'a') << endl;
	cout << "get_name_for_symbol(\"stations.txt\", 'r'): " << get_name_for_symbol("stations.txt", 'r') << endl;
	//cout << "get_name_for_symbol(\"stations.txt\", 's'): " << get_name_for_symbol("stations.txt", 's') << endl;
	cout << "get_name_for_symbol(\"lines.txt\", '*'): " << get_name_for_symbol("lines.txt", '*') << endl;
	cout << "get_name_for_symbol(\"lines.txt\", '<'): " << get_name_for_symbol("lines.txt", '<') << endl;
	//cout << "get_name_for_symbol(\"lines.txt\", ')'): " << get_name_for_symbol("lines.txt", ')') << endl;
	//cout << "get_name_for_symbol(\"station.txt\", 'A'): " << get_name_for_symbol("station.txt", 'A') << endl;
	cout << endl;
	
	/* tailor_2D_array */
	cout << "===tailor_2D_array test===" << endl << endl;
	print_map(map, height, width);
	int half_rows = height / 2;
	char** half_map;
	half_map = tailor_2D_array(map, height, half_rows);
	print_map(half_map, half_rows, width);

	cout << endl << "===end of tailor_2D_array test===" << endl << endl;
	
	return 0;

}

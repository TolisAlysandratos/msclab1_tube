enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

/* error codes for Question 3 */
#define ERROR_START_STATION_INVALID -1
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

const int MAX_DIR_SIZE = 3;
const int MAX_FILENAME_SIZE = 80;
const int MAX_STR_SIZE = 256;
const int NUM_OF_LINES = 9;
const char LINE_SYMBOLS[NUM_OF_LINES + 1] = "*-#&$+|><";

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width);

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width);

/* pre-supplied helper function to describe errors for Question 3 */
const char* error_description(int code);

/* presupplied helper function for converting string to Direction enum */
Direction string_to_direction(const char* token);


/* Main functions */


/* Task 1 - Function which finds the coordinates of the first occurence 
   of a given symbol character in a 2D dynamic array (scanned in a row-by-row fashion);
   returns false if target symbol is not found and sets both position values to -1;
   returns true if target symbol is found and sets the variables r and c to its position */
bool get_symbol_position(char** m, int height, int width, char target, int& r, int& c);

/* Task 2 - Function which takes the name of a station or line
   as input and returns its corresponding map symbol character;
   returns the space charecter (' ') if name is not found */
char get_symbol_for_station_or_line(const char* name);

/* Task 3 - Function which runs checks on the route string (input);
   returns a descriptive error message if invalid, or the number of train changes if valid */
int validate_route(char** m, int height, int width,
		   const char* start_station, const char* route, char* destination);


/* Helper functions */


/* Helper function that checks if a symbol on the map corresponds a station,
   according to the "stations.txt" file; returns true if it finds it and false otherwise */
bool is_station(char symbol);

/* Helper function that checks if a symbol on the map corresponds a line,
   according to the "lines.txt" file; returns true if it finds it and false otherwise */
bool is_line(char symbol);

/* Helper function which searches for character symbol in "stations.txt" or "lines.txt"
   and returns the corresponding name string; if symbol is not found it throws an error
   message and exits the program */
char* get_name_for_symbol(const char* filename, char target);

/* Helper function which takes as input a 2D dynamic array, its number of rows and how many of
   these rows to copy to the new 2D dynamic array; returns the new array with the first
   'new_num_of_rows' copied to it after deallocating the old array */
char** tailor_2D_array(char** old_array, int old_num_of_rows, int new_num_of_rows);

/* Helper function which takes as input a route string containing directions and an output 
   parameter for the number of directions; 
   if route string is valid, it returns a 2D dynamic array containing a separate 
   direction on each row;
   if route string is invalid it sets numer_of_directions to zero and returns NULL */
char** route_str_to_directions(const char* route, int& number_of_directions);



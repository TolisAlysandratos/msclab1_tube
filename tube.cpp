#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own
	 function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char** allocate_2D_array(int rows, int columns) {
	char** m = new char* [rows];
	assert(m);
	for(int r=0; r<rows; r++) {
		m[r] = new char[columns];
		assert(m[r]);
	}
	return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char** m, int rows) {
	for(int r=0; r<rows; r++)
		delete [] m[r];
	delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char* filename, int& height, int& width) {
	char line[512];

	ifstream input(filename);

	height = width = 0;

	input.getline(line, 512);
	while(input) {
		if( (int) strlen(line) > width)
			width = strlen(line);
		height++;
		input.getline(line, 512);
	}

	if(height > 0)
		return true;
	return false;
}

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width) {

        bool success = get_map_dimensions(filename, height, width);

	if(!success) return NULL;

	char** m = allocate_2D_array(height, width);

	ifstream input(filename);

	char line[512];
	char space[] = " ";

	for(int r = 0; r<height; r++) {
		input.getline(line, 512);
		strcpy(m[r], line);
		while( (int) strlen(m[r]) < width ) {
			strcat(m[r], space);
		}
	}

	return m;
}

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width) {
	cout << setw(2) << " " << " ";
	for(int c=0; c<width; c++) {
		if(c && (c % 10) == 0) {
			cout << c/10;
		} else {
			cout << " ";
		}
	}

	cout << endl;
	cout << setw(2) << " " << " ";

	for(int c=0; c<width; c++) cout << (c % 10);

	cout << endl;

	for(int r=0; r<height; r++) {
		cout << setw(2) << r << " ";
		for(int c=0; c<width; c++) cout << m[r][c];
		cout << endl;
	}
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char* error_description(int code) {
	switch(code) {
	case ERROR_START_STATION_INVALID:
		return "Start station invalid";
	case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
		return "Route endpoint is not a station";
	case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
		return "Line hopping between stations not possible";
	case ERROR_BACKTRACKING_BETWEEN_STATIONS:
		return "Backtracking along line between stations not possible";
	case ERROR_INVALID_DIRECTION:
		return "Invalid direction";
	case ERROR_OFF_TRACK:
		return "Route goes off track";
	case ERROR_OUT_OF_BOUNDS:
		return "Route goes off map";
	}
	return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char* token) {
	const char* strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
	for(int n=0; n<8; n++) {
		if(!strcmp(token, strings[n])) return (Direction) n;
	}
	return INVALID_DIRECTION;
}

///////////////////////////////////////////////////////////////////

/* Helper Functions */

bool is_station(char symbol)
{
  if (isalnum(symbol) && symbol <= 'r')
    return true;
  return false;
}

bool is_line(char symbol)
{
  if (strchr(LINE_SYMBOLS, symbol) != NULL)
    return true;
  return false;
}

char* get_name_for_symbol(const char* filename, char target)
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
    {
      cout << "Error: \"" << filename << "\" could not be opened." << endl;
      exit(1);
    }

  char ch;
  char symbol;
  char* name_str = new char[MAX_STR_SIZE];
  assert(name_str);
  
  in_stream.get(ch);
  symbol = ch;
  while (!in_stream.eof())
    {
      if (ch == '\n')
	{
	  in_stream.get(ch);
	  symbol = ch;
	}
      in_stream.get(ch);
      in_stream.get(name_str, MAX_STR_SIZE, '\n');
      if (symbol == target)
	{
	  in_stream.close();
	  return name_str;
	}
      in_stream.get(ch);
    }
  in_stream.close();
  delete [] name_str;

  cout << "Error: symbol was not found in file \""
       << filename << "\". Program exited." << endl;
  exit(1);
}

char** tailor_2D_array(char** old_array, int old_num_of_rows, int new_num_of_rows)
{
  char** new_array = new char* [new_num_of_rows];
  assert(new_array);

  for (int r = 0; r < new_num_of_rows; r++)
    {
      new_array[r] = new char [strlen(old_array[r]) + 1];
      assert(new_array[r]);
      strcpy(new_array[r], old_array[r]);
    }
  deallocate_2D_array(old_array, old_num_of_rows);

  return new_array;
}

char** route_str_to_directions(const char* route, int& number_of_directions)
{
  int i = 0;
  int dir_i = 0;

  int temp_rows = strlen(route);
  int temp_cols = MAX_DIR_SIZE;
  char** temp_directions = allocate_2D_array(temp_rows, temp_cols);

  while (route[i] != '\0' && i < temp_rows)
    {      
      switch(route[i])
	{
	case('W'):
	case('E'):
	case('N'):
	case('S'):
	  {
	    switch(route[i+1])
	      {
	      case('\0'):
		{
		  temp_directions[dir_i][0] = route[i];
		  temp_directions[dir_i][1] = '\0';
		  dir_i++;
		  break;
		}
	      case(','):
		{
		  temp_directions[dir_i][0] = route[i];
		  temp_directions[dir_i][1] = '\0';
		  i++;
		  dir_i++;
		  break;
		}
	      case('W'):
	      case('E'):
		{
		  if (route[i] == 'W' || route[i] == 'E')
		    return NULL;
		  temp_directions[dir_i][0] = route[i];
		  i++;
		  temp_directions[dir_i][1] = route[i];
		  i++;
		  temp_directions[dir_i][2] = '\0';
		  dir_i++;
		  break;
		}
	      default:
		number_of_directions = 0;
		return NULL;
	      }
	    break;
	  }
	default:
	  number_of_directions = 0;
	  return NULL;
	}

      i++;
    }

  number_of_directions = dir_i;

  char** route_directions = tailor_2D_array(temp_directions, temp_rows, number_of_directions);
  
  return route_directions;
}

//////////////////////////////////////////////////////////////////

/* Task 1 */

bool get_symbol_position(char** m, int height, int width, char target, int& r, int& c)
{
  r = c = -1;

  for (int row = 0 ; row < height ; row++)
    {
      for (int col = 0 ; col < width ; col++)
	{
	  if (m[row][col] == target)
	    {
	      r = row;
	      c = col;
	      return true;
	    }
	}
    }
  
  return false;
}

///////////////////////////////////////////////////////////////////

/* Task 2 */

char get_symbol_for_station_or_line(const char* name)
{
  // Checks if name contains substring "Line" to decide which file to open ("stations.txt" or "lines.txt");
  // covers the case where keyword "Line" is used in "stations.txt" e.g. Edgware Road (Circle Line)
  char* filename = new char[MAX_FILENAME_SIZE];
  assert(filename);
  if (strstr(name, "Line") && !strstr(name, "("))
    strncpy(filename, "lines.txt", MAX_FILENAME_SIZE - 1);
  else
    strncpy(filename, "stations.txt", MAX_FILENAME_SIZE - 1);

  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
    {
      cout << "Error: \"" << filename << "\" could not be opened." << endl;
      exit(1);
    }

  char ch;
  char ans;
  char* name_str = new char[MAX_STR_SIZE];
  assert(name_str);

  in_stream.get(ch);
  ans = ch;
  while (!in_stream.eof())
    {
      if (ch == '\n')
	{
	  in_stream.get(ch);
	  ans = ch;
	}
      in_stream.get(ch);
      in_stream.get(name_str, MAX_STR_SIZE);
      if (!strcmp(name_str, name))
	{
	  in_stream.close();
	  delete [] filename;
	  delete [] name_str;
	  
	  return ans;
	}
      in_stream.get(ch);
    }
  in_stream.close();
  delete [] filename;
  delete [] name_str;
  
  return ' ';
}

///////////////////////////////////////////////////////////////////////////

/* Task 3 */

int validate_route(char** m, int height, int width,
		   const char* start_station, const char* route, char* destination)
{
  char current_line = '\0';
  int train_changes = 0;

  // Checks if the start_station string corresponds to a station
  if (!is_station(get_symbol_for_station_or_line(start_station)))
    return ERROR_START_STATION_INVALID;
 
  // Attempts to store the directions of the route string in the dynamic 2D array "directions";
  // If string is invalid, route_str_directions function sets num_of_directions to zero before returning
  int num_of_directions = 0;
  char** directions = route_str_to_directions(route, num_of_directions);
  if (num_of_directions == 0)
    return ERROR_INVALID_DIRECTION;
  
  // Initialise row and col (map position) variables to starting_station's position
  int previous_row, previous_col, current_row, current_col, next_row, next_col;
  get_symbol_position(m, height, width,
		      get_symbol_for_station_or_line(start_station), previous_row, previous_col);
  next_row = current_row = previous_row;
  next_col = current_col = previous_col;

  Direction dir;
  for (int i = 0 ; i < num_of_directions ; i++)
    {
      dir = string_to_direction(directions[i]);
      switch(dir)
	{
	case(N):
	  next_row = current_row - 1; break;
	case(S):
	  next_row = current_row + 1; break;
	case(W):
	  next_col = current_col - 1; break;
	case(E):
	  next_col = current_col + 1; break;
	case(NE):
	  next_row = current_row - 1;
	  next_col = current_col + 1; break;
	case(NW):
	  next_row = current_row - 1;
	  next_col = current_col - 1; break;
	case(SE):
	  next_row = current_row + 1;
	  next_col = current_col + 1; break;
	case(SW):
	  next_row = current_row + 1;
	  next_col = current_col - 1; break;
	default:
	  cout << "ERROR: Invalid direction type given to valid_route function." << endl;
	  exit(1);
	}

      // Checks if route strays ooutside the bounds of the map
      if ((next_row) >= height || (next_row) < 0 || (next_col) >= width || (next_col) < 0)
	return ERROR_OUT_OF_BOUNDS;

      // Checks if route strays off a station or line/track
      if (m[next_row][next_col] == ' ')
	return ERROR_OFF_TRACK;

      // Checks if route changes line between stations
      if (is_line(m[current_row][current_col]) && is_line(m[next_row][next_col])
	  && (m[current_row][current_col] != m[next_row][next_col]))
	return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
      
      // Checks if there is an attempt to retrace a journey step outside of a station
      if ((previous_row == next_row) && (previous_col == next_col))
	{
	  if (!is_station(m[current_row][current_col]))
	    return ERROR_BACKTRACKING_BETWEEN_STATIONS;
	  else
	    // If the journey is retraced at a station, it increments a line change
	    train_changes++;
	}
	
      // Increment line changes (if any) to train changes
      if (is_line(m[current_row][current_col]) && current_line != m[current_row][current_col])
	{
	  current_line = m[current_row][current_col];
	  train_changes++;
	}
      
      // Update position variables
      previous_row = current_row;
      previous_col = current_col;
      current_row = next_row;
      current_col = next_col;
      
    }  
  
  // Check if the endpoint of route is a station
  if (!is_station(m[current_row][current_col]))
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;

  // Assign end station to 'destination' variable
  char* temp_dest = get_name_for_symbol("stations.txt", m[current_row][current_col]);
  strncpy(destination, temp_dest, MAX_STR_SIZE - 1);
  delete [] temp_dest;

  deallocate_2D_array(directions, num_of_directions);
  
  // Return number of changes corrected by -1
  return (train_changes - 1);

}

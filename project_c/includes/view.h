/**
 @file view.h
 \brief Module where are defined functions that control what is printed
 */
#ifndef View
#define View

#include <glib.h>

#include "../includes/review.h"
#include "../includes/business.h"
#include "../includes/user.h"

/**
 * @brief Struct containing table information
*/
typedef struct table * TABLE;

/**
 * @brief Initializes a table
 * @param query Query
 * @return Table initialized
*/
TABLE init_table(int query);

/**
 * @brief gets query of a tavle
 * @param t Table
 * @return query number
*/ 
int get_table_query(TABLE t);

/**
 * @brief Gets number of columns on a table
 * @param t Table
 * @return number of columns
*/
int get_n_columns(TABLE t);

/**
 * @brief Adds a new element to the table
 * @param t Pointer to table
 * @param index Index
* @param new_element Pointer to new element
*/
void add_to_table(TABLE * t, int index, void * new_element);

/**
 * @brief Gets pointer of an array
 * @param t Table
 * @return Pointer of the array
*/
GPtrArray * get_ptr_array (TABLE t);

/**
 * @brief Sets pointer of an array
 * @param t Table
 * @param Pointer of an array
*/
void set_table_cont_parray (TABLE * t, GPtrArray * arr);

/**
 * @brief Sets top of a table
 * @param t Pointer to table
 * @param top Top
*/
void set_top (TABLE * t, int top);

/**
 * @brief Saves the longest word in the table (to format the table)
 * @param t Table
 * @param length Length of the word
 * @param col Index where to put it in the auxiliar array
*/
void set_longest_word(TABLE * t, int length, int col);

/**
 * @brief Creates an auxiliar array in order to print query 6
 * @param t Table
 * @param index Index of the array where to put the value
 * @param value Value
*/
void add_index_bus_per_city(TABLE * t, int index, int * value);


/**
 * @brief gets length of the content of the table
 * @param t Table
 * @return length of the table content
*/ 
int get_table_length(TABLE t);

/**
 * @brief gets data from the given index
 * @param t Table
 * @param index index of the data to return
 * @return data from the table content 
*/ 
void * lookup_data(TABLE t, int index);

/**
 * @brief Allows to print chars in an aesthetic way
 * @param n Times to be printed
 * @param c Char to be printed n times
 * @param new_line Indicates if it's supposed to go to a different line after printing or not
*/
void format_line(int n, char c, int new_line);

/**
 * @brief Prints a table
 * @param t Table
*/
void print_table(TABLE t);

/**
 * @brief Frees all memory used by a table
 * @param t Table
*/
void free_table(TABLE t);

/**
 * @brief prints content
 * @param content pointer for the content to be printed 
 * @param is_int if the content is an int
 * @param is_float if the content is a float
 * @param is_string if the content is a string
*/ 
void general_print(void * content, int is_int, int is_float, int is_string);

/**
 * @brief Prints a welcome message
*/
void greet_message();

/**
 * @brief Prints message of success (if success is 1) or of 
 * unsuccess (if not) of the sgr initialization
 * @param success Success/unsuccess of the sgr initialization
*/
void sgr_initialized_message(int success);

/**
 * @brief creates menu with the querires information 
*/
void queries_menu();

/**
 * @brief Prints message marking the end of the program
*/
void exit_message();

#endif
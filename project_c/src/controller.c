
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <glib.h>

#include "../includes/sgr.h"
#include "../includes/macro.h"
#include "../includes/controller.h"

/*
Struct that holds a pointer to some content that can be a string, a table, an sgr, an int ou a float
*/
struct variable {

    int is_string;
    int is_table;
    int is_sgr;
    int is_int;
    int is_float;

    void * content;

};

struct variable * init_variable() {

    struct variable * var = malloc(sizeof(struct variable));
    var->is_string = var->is_table = var->is_sgr = var->is_int = var->is_float = 0;

    return var;

}

void free_variable(struct variable * var) {

    // Adequates the free to the type of pointer held
    if (var->is_string || var->is_int || var->is_float) 
        free(var->content);
 
    else if (var->is_table) 
        free_table(var->content);
    
    else if (var->is_sgr) 
        free_sgr(var->content);
    
    free(var);

}

void show (char * var_name, GHashTable * variables) {

    if (variables) {
        
        // Searches the variable in the variables hashtable
        struct variable * var = g_hash_table_lookup(variables, var_name);

        // If the variable is found, print the content
        if (var) {

            // Adequate the print to the type of variable
            if (var->is_table) print_table(var->content);
            else general_print(var->content, var->is_int, var->is_float, var->is_string);

        }

    }

}

struct variable * indexation(TABLE t, int line, int col) {

    struct variable * new_var = init_variable();
    int n_query = get_table_query(t);
    int n_cols = get_n_columns(t);

    // Determines the position in the array that the element occurs
    int position = (line - 1) * n_cols + (col - 1);
    int table_length = get_table_length(t);

    // Separates the cases where the variable will be a string, an int or a float
    if ((n_query == 2 && position != (table_length - 1)) || (n_query == 3 && col >= 1 && col <= 3) || n_query == 4 
    || n_query == 5 || (n_query == 7 && position != (table_length - 1)) || (n_query == 8 && (col == 1 || col == 2)) || n_query == 9) 
        new_var->is_string = 1;
        
    else if (n_query == 2 || (n_query == 3 && col == 5) || n_query == 7) 
        new_var->is_int = 1;

    else
        new_var->is_float = 1;

    // Loads the content to the variable
    if (position < table_length && position >= 0 && col <= n_cols) 
        new_var->content = (new_var->is_string) ? strdup(lookup_data(t, position)) : lookup_data(t, position) ;
    else {

        free(new_var);
        new_var = NULL;

    }

    return new_var;

}


char * filter_special_chars(char * command) {

    for (int i = 0; command[i]; i++) {
        
        // Deletes these chars from the string
        if (command[i] == ' ' || command[i] == '"' || command[i] == '\'' || 
            command[i] == '(' || command[i] == ')')  {
            
            for (int j = i; command[j]; j++)
                command[j] = command[j+1];
            i--;
        }

    }

    return command;
}

int toCSV(TABLE t, char * delim, char * filepath) {

    int r = 1;

    //allocates memory for filepath
    char * filepath_with_termination = malloc(strlen(filepath) + 4);
    strcpy(filepath_with_termination, filepath);
    strcat(filepath_with_termination, ".csv");
    int query = get_table_query(t);

    //opens file
    FILE * f_write = fopen(filepath_with_termination, "wb");
    if (f_write) { //if the file opens successfully 
        
        // Creates string that will contain what will be writen in the file header
        char * header = malloc(BUFFER_SIZE);

        switch(query) {

            case 2: header = strcpy(header, "BUSINESS NAME\n");
                    break;
            case 3: header = strcpy(header, "NAME,CITY,STATE,STARS,STARS\n");
                    break;
            case 4: header = strcpy(header, "ID,BUSINESS NAME\n");
                    break;
            case 5: header = strcpy(header, "ID,BUSINESS NAME\n");
                    break;
            case 6: header = strcpy(header, "ID,BUSINESS NAME,STARS\n");
                    break;
            case 7: header = strcpy(header, "ID\n"); 
                    break;
            case 8: header = strcpy(header, "ID,BUSINESS NAME,STARS\n");
                    break;
            case 9: header = strcpy(header, "ID");
                    break;

        }

        // writes header
        fwrite(header, sizeof(char), strlen(header), f_write);
        free(header);
        r = 0;

        int query = get_table_query(t);
        int len = get_table_length(t);
        int i = 0;
        while(i < len) { // while there's still something to be written

            if (query == 2 || query == 7) {

                void * data;
                data = lookup_data(t, i);

                if (i == len - 1) { //writed total in the end of the file
                    int * total = (int *) data;
                    fprintf(f_write, "%d", *total);
                }    
                else { 
                    fwrite(data, sizeof(char), strlen(data), f_write);
                    fputs("\n", f_write);
                }

                i++;
                  
            }
            else if (query == 3) {

                // writes business name, city, state, average stars and total reviews

                void * data;
                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fwrite(delim, sizeof(char), strlen(delim), f_write);

                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fwrite(delim, sizeof(char), strlen(delim), f_write);
                
                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fwrite(delim, sizeof(char), strlen(delim), f_write);

                float * avg_stars = (float *) lookup_data(t, i++);
                fprintf(f_write, "%.1f", *avg_stars);
                fwrite(delim, sizeof(char), strlen(delim), f_write);

                long * total_rev = (long *) lookup_data(t, i++);
                fprintf(f_write, "%ld", *total_rev);

                fputs("\n", f_write);

            }  
            else if (query == 4 || query == 5) {

                // writes business id and name

                void * data;
                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fwrite(delim, sizeof(char), strlen(delim), f_write);

                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fputs("\n", f_write);

            }
            else if (query == 6 || query == 8) {

                // writes business id, name and stars

                void * data;
                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fwrite(delim, sizeof(char), strlen(delim), f_write);

                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);
                fwrite(delim, sizeof(char), strlen(delim), f_write);

                float * stars = (float *) lookup_data(t, i++);
                fprintf(f_write, "%.1f", *stars);

                fputs("\n", f_write);

            }
            else {

                // writes review id
                void * data;
                data = (char *) lookup_data(t, i++);
                fwrite(data, sizeof(char), strlen(data), f_write);

                fputs("\n", f_write);

            }

        }

    }

    free(filepath_with_termination);

    return r;
}

int controller() {

    char * buffer, * read, * var, * func_name, * arguments, * buffer_cp, * command;
    // Array of string that will organize multiple arguments received
    char ** arguments_organized;
    int flag = 0;
    int sgr_initialized = 0, sgr_reloaded = 0;
    GHashTable * variables = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_variable);
    TABLE t;

    system("clear");
    greet_message();

    // Attempts to loads sgr with predefined files
    SGR sgr = load_sgr(PREDEF_USERS, PREDEF_BUSINESSES, PREDEF_REVIEWS);
    if (sgr) sgr_initialized = 1;

    // Prints message if the sgr was initialized properly
    sgr_initialized_message(sgr_initialized);

    // Prints the options
    queries_menu();

    // Alocates memory to the buffer to read to
    command = malloc(BUFFER_SIZE);
    // Checks if anything was read
    read = fgets(command, BUFFER_SIZE, stdin);
    if (read) flag = 1;

    // Allocates memory for 5 strings
    arguments_organized = calloc(5, sizeof(char *));

    // Copies of the pointers: one to hold all the info, the other to manage smaller instructions
    buffer_cp = buffer = command; 

    int line, column; // For indexation purposes
    int n_arguments = 0; // For managing number of when a function is requested

    // Separates first command
    buffer = strtok(command, ";\n");
    while (flag) { // Allows to receive multiple commands followed by ";"
        
        // Has to be true for the queries to be able to work
        int valid_queries = sgr_initialized || sgr_reloaded;

        n_arguments = 0;

        var = strsep(&buffer, "="); // Tries to find format variable=something

        if (buffer) { // If it doesn't read the whole buffer, the format was found

            // Filter any spaces and other special chars from the var name
            var = filter_special_chars(var);

            buffer_cp = buffer; // Saves the buffer

            func_name = strsep(&buffer, "("); // Tries to find format of function with arguments

            if (buffer) { // If the buffer isn't NULL, the whole buffer wasn't read therefore it follows the format above

                // Creates a new variable
                struct variable * new_variable = init_variable();

                // Filter any spaces and other special chars from the function name
                func_name = filter_special_chars(func_name);

                arguments = strsep(&buffer, ")"); 

                if (var && func_name && arguments) {

                    new_variable->is_table = 1;

                    // Separate arguments
                    while (arguments && n_arguments < 6) 
                        arguments_organized[n_arguments++] = filter_special_chars(strsep(&arguments, ","));
 
                    if (!strcmp(func_name, QUERY_1) && n_arguments == 3) {
                        
                        new_variable->is_table = 0;
                        new_variable->is_sgr = 1;

                        free_sgr(sgr);

                        // Loads to the variable
                        new_variable->content = (SGR) load_sgr(arguments_organized[0], arguments_organized[1], arguments_organized[2]);
                        
                        if (sgr) sgr_reloaded = 1;
   
                    }
                    else if (valid_queries && !strcmp(func_name, QUERY_2) && n_arguments == 2) 
                        new_variable->content = (TABLE) businesses_started_by_letter(sgr, (char) *arguments_organized[1]);

                    else if (valid_queries && !strcmp(func_name, QUERY_3) && n_arguments == 2) 
                        new_variable->content = (TABLE) business_info(sgr, arguments_organized[1]);

                    
                    else if (valid_queries && !strcmp(func_name, QUERY_4) && n_arguments == 2) 
                        new_variable->content = (TABLE) businesses_reviewed(sgr, arguments_organized[1]);
                        
                    
                    else if (valid_queries && !strcmp(func_name, QUERY_5) && n_arguments == 3) 
                        new_variable->content = (TABLE) businesses_with_stars_and_city(sgr, atoi(arguments_organized[1]), arguments_organized[2]);

                    else if(valid_queries && !strcmp(func_name, QUERY_6) && n_arguments == 2) 
                        new_variable->content = (TABLE) top_businesses_by_city(sgr, atoi(arguments_organized[1]));

                    else if (valid_queries && !strcmp(func_name, QUERY_7) && n_arguments == 1) 
                        new_variable->content = (TABLE) international_users(sgr);

                    else if (valid_queries && !strcmp(func_name, QUERY_8) && n_arguments == 3) 
                        new_variable->content = (TABLE) top_businesses_with_category(sgr, atoi(arguments_organized[1]), arguments_organized[2]);

                    else if (valid_queries && !strcmp(func_name, QUERY_9) && n_arguments == 2) 
                        new_variable->content = (TABLE) reviews_with_word(sgr, arguments_organized[1]);

                    else if (!strcmp(func_name, READ_CSV) && n_arguments == 2) ;

                    else if (!strcmp(func_name, FILTER) && n_arguments == 4) ;
         
                    else if (!strcmp(func_name,  PROJECTION) && n_arguments == 2) ;
                    
                    g_hash_table_insert(variables, strdup(var), new_variable);

                }
         
            }   
            else { // Treats it as format of indexation instead

                // Gets the name of the table
                func_name = filter_special_chars(strsep(&buffer_cp, "[")); 

                // Searches for the struct variable that holds said table
                struct variable * tmp = g_hash_table_lookup(variables, func_name);

                // Determines the line and column to access
                line = atoi(filter_special_chars(strsep(&buffer_cp, "]")));
                strsep(&buffer_cp, "[");
                column = atoi(filter_special_chars(strsep(&buffer_cp, "]")));

                // Inserts the new variable to the hashtable to be printed later
                struct variable * new = indexation(tmp->content, line, column);
                if (new) {
                    g_hash_table_insert(variables, strdup(var), new);
                }

            }

        }
        else if (!strcmp(var, EXIT)) { // Finds format to leave program

            flag = 0;
            exit_message();

        }
        else if ((func_name = strsep(&var, "("))) { // Treats it as format without a "variable =""

            arguments = strsep(&var, ")");

            if (arguments) {

                while (arguments) 
                    arguments_organized[n_arguments++] = filter_special_chars(strsep(&arguments, ",)"));

                if (!strcmp(func_name, WRITE_CSV)) {

                    // Find the variable that holds the content to write to CSV
                    struct variable * tmp = g_hash_table_lookup(variables, arguments_organized[0]);
                    toCSV(tmp->content, arguments_organized[1], arguments_organized[2]);

                }
                else if (!strcmp(func_name, SHOW)) {

                    show(arguments_organized[0], variables); 
                    queries_menu();
                    
                }

            }
          
        }

        if (flag) {
            
            // Checks if more commands were inserted
            buffer = strtok(NULL, ";\n");

            // If no more comments were inserted, then request more commands from the user
            if (!buffer) {

                fgets(command, BUFFER_SIZE, stdin);
                buffer = strtok(command, ";\n");

            }
        }
        
    }

    // If sgr was initialized or loaded it must be freed
    if (sgr_initialized || sgr_reloaded) {

        free_sgr(sgr);

    }
    
    // Destroys table with the variables
    g_hash_table_destroy(variables);

    free(command);
    free(arguments_organized);

    return 0;
    
}   
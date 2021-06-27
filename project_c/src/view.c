#include <stdio.h>
#include <stdlib.h>

#include "../includes/view.h"
#include "../includes/macro.h"

#include "glib.h"

struct table {

    GPtrArray * content;
    int n_cols;
    int top; 
    int query;
    int longest_word[5];
    GPtrArray * index_bus_per_city;

};


TABLE init_table(int query) {

    TABLE new = malloc(sizeof(struct table));
    if (query != 2 && query != 4 && query != 7 && query != 9)
        new->content = g_ptr_array_new_full(0, g_free);
    new->query = query;
    new->index_bus_per_city = g_ptr_array_new_full(5, g_free);

    for (int i = 0; i < 5; i++)
        new->longest_word[i] = 13;

    if (query == 2 || query == 4 || query == 5 || query == 7 || query == 9) new->n_cols = 1;
    else if (query == 6 || query == 8) new->n_cols = 3;
    else if (query == 3) new->n_cols = 5;

    return new;
}

int get_table_query(TABLE t) {

    return t->query;

}

int get_n_columns(TABLE t) {

    return t->n_cols;

}

void add_to_table(TABLE * t, int index, void * new_element) {

    g_ptr_array_insert((*t)->content, index, new_element);

}

GPtrArray * get_ptr_array (TABLE t) {

    return t->content;

}

void set_table_cont_parray (TABLE * t, GPtrArray * arr) {

    (*t)->content = arr;

}

void set_top (TABLE * t, int top) {

    (*t)->top = top;

}

void set_longest_word(TABLE * t, int length, int col) {

    (*t)->longest_word[col] = length;

}

void add_index_bus_per_city(TABLE * t, int index, int * value) {

    g_ptr_array_insert((*t)->index_bus_per_city, index, value);

}

int get_table_length(TABLE t) {

    return t->content->len;

}

void * lookup_data(TABLE t, int index) {

    return g_ptr_array_index(t->content, index);

}

void format_line(int n, char c, int new_line) {

   
    for (int i = 0; i < n; i++)
        printf("%c", c);
        
    if (c == ' ') printf("|");
    
    if (new_line) putchar('\n');

}



void print_query2 (TABLE t, int page) {

    printf("\nBusinesses started by the requested letter\n\n");
    /* Calculates the index corresponding to the first item of the next page
       Index 0: Corresponds to the 1st element of the 1st page
       Index 1: Corresponds to the 1st elements of the 2nd page ...
    */
    int cmp = page * ITEMS_PER_PAGE;
    // Calculates the number of '-' to put before the header of the query
    int lines_first_side = (t->longest_word[0] - strlen("BUSINESS-NAME"))/2 + 1;
    format_line(lines_first_side, '-', 0);
    printf("BUSINESS-NAME");
    // Calculates the number of '-' to put after the header of the query
    format_line(t->longest_word[0] - lines_first_side - strlen("BUSINESS-NAME") + 4, '-', 1);

    // Loop that selects from the 1st item of said page to the last item or the second to last item of the page
    for (int i = (page - 1) * ITEMS_PER_PAGE; i < t->content->len - 1 && i < cmp; i++) {

        char * business_name = g_ptr_array_index(t->content, i);
        printf("| %s", business_name);
        // Calculates the number of spaces to leave for the right side of the table to be aligned
        format_line(t->longest_word[0] - strlen(business_name) + 1, ' ', 1);
        // Prints a separator for each line of the table
        format_line(t->longest_word[0] + 4, '-', 1);

    }

    // Access and printing of the total number of businesses, saved at the last index of the GPtrArray
    int * total_businesses = g_ptr_array_index(t->content, t->content->len - 1);
    printf("Total businesses presented: %d\n", *total_businesses);

}

void print_query3(TABLE t, int page) {

    printf("\nBusiness Information\n");
    int j = 0;

    // Getting the information necessary from the GPtrArray
    char * name = g_ptr_array_index(t->content, j++);
    char * city = g_ptr_array_index(t->content, j++);
    char * state = g_ptr_array_index(t->content, j++);
    float * av_stars = g_ptr_array_index(t->content, j++);
    long * n_reviews = g_ptr_array_index(t->content, j++);

    // Size for the line above and below the information, for framing purposes
    int line_size = strlen(name) + strlen(city) + strlen(state) + 10;
    format_line(line_size, '-', 1);

    // Printing information
    printf(" Name: %s\n", name);
    printf(" City: %s\n", city);
    printf(" State: %s\n", state);
    printf(" Stars: %.1f\n", *av_stars);
    printf(" Number of Reviews: %d\n", *n_reviews);

    format_line(line_size, '-', 1);

}

void print_query4or5(TABLE t, int page, int query) {

    if (query == 4) 
        printf("\nBusinesses reviewed by user\n\n");
    else 
        printf("\nBusinesses from city with over the requested stars\n\n");

    // Calculates the index corresponding to the first item of the next page
    int cmp = page * ITEMS_PER_PAGE * 2;

    // Each user-id has 22 characters: framing the table with 11 '-' + ID + 11 '-'
    format_line(11, '-', 0);
    printf("ID");
    format_line(11, '-', 0);

    // Calculates the number of '-' to put before the header of the query
    int lines_first_side = (t->longest_word[1] - strlen("BUSINESS-NAME"))/2 + 1;
    format_line(lines_first_side, '-', 0);
    printf("BUSINESS-NAME");
    // Calculates and places a number of '-' to put after the header of the query
    format_line(t->longest_word[1] - lines_first_side - strlen("BUSINESS-NAME") + 4, '-', 1);

    // Loop that selects from the 1st item of said page to the last item or the second to last item of the page    
    for (int i = (page - 1) * ITEMS_PER_PAGE * 2; i < t->content->len && i < cmp; i++) {
        char * business_id = g_ptr_array_index(t->content, i++);
        char * business_name = g_ptr_array_index(t->content, i);
        printf("| %s |", business_id);
        printf(" %s", business_name);
        format_line(t->longest_word[1] - strlen(business_name), ' ', 1);
        format_line(t->longest_word[1] + 2 + 26, '-', 1);
    }

}

void print_query6(TABLE t, int page) {

    // Gets the position where the businesses from that page start and also when the next one begins
    int * index = g_ptr_array_index(t->index_bus_per_city, page - 1);
    int * final_index = g_ptr_array_index(t->index_bus_per_city, page);

    if (page == t->index_bus_per_city->len) *final_index = t->content->len;

    // Gets the city corresponding, that is placed one index behind
    char * city = g_ptr_array_index(t->content, *index);

    printf("CITY : %s\n\n", city);

    format_line(11, '-', 0);
    printf("ID");
    format_line(11, '-', 0);

    // Calculates the number of '-' to put before the header of the query
    int lines_first_side = (t->longest_word[0] - strlen("BUSINESS-NAME"))/2 + 1;
    format_line(lines_first_side, '-', 0);
    printf("BUSINESS-NAME");
    // Calculates and places a number of '-' to put after the header of the query
    format_line(t->longest_word[0] - lines_first_side - strlen("BUSINESS-NAME") + 4, '-', 0);

    printf("STARS---\n");

    for (int i = *index + 1; i < *final_index; i++) {

        printf("| %s |", (char *) g_ptr_array_index(t->content, i++));

        char * business_name = g_ptr_array_index(t->content, i++);
        printf(" %s", business_name);
        format_line(t->longest_word[0] - strlen(business_name), ' ', 0);

        float * stars_p = g_ptr_array_index(t->content, i);
        printf("  %.1f  |\n", *stars_p); 
        format_line(t->longest_word[0] + 36, '-', 1);
    }
}

void print_query7or9(TABLE t, int page, int query) {

    if (query == 7) printf("\nInternational users\n\n");
    else printf("\nWord occurance in reviews\n\n");

    // Each user-id has 22 characters: framing the table with 12 '-' + ID + 12 '-'
    format_line(12, '-', 0);
    printf("ID");
    format_line(12, '-', 1);

    // Calculates the index corresponding to the first item of the next page
    int cmp = page * ITEMS_PER_PAGE;

    // Loop that selects from the 1st item of said page to the last item or the second to last item of the page
    for (int i = (page - 1) * ITEMS_PER_PAGE; i < t->content->len - 1 && i < cmp; i++) {
        printf("| %s |\n", (char *) g_ptr_array_index(t->content, i));
        format_line(26, '-', 1);
    }

    // Access and printing of the total number of international users, saved at the last index of the GPtrArray
    if (query == 7) {
        int * n_int_users = g_ptr_array_index(t->content, t->content->len - 1);
        printf("Total international users: %d\n", *n_int_users);
    }

}


void print_query8(TABLE t, int page) {

    printf("Top n businesses by category\n\n");

    // Each business-id has 22 characters: framing the table with 11 '-' + ID + 11 '-'
    format_line(11, '-', 0);
    printf("ID");
    format_line(11, '-', 0);

    // Calculates the number of '-' to put before the header of the query
    int lines_first_side = (t->longest_word[1] - strlen("BUSINESS-NAME"))/2 + 1;
    format_line(lines_first_side, '-', 0);
    printf("BUSINESS-NAME");

    // Calculates and places a number of '-' to put after the header of the query
    format_line(t->longest_word[1] - lines_first_side - strlen("BUSINESS-NAME") + 2, '-', 0);    

    printf("----STARS--\n");

    // Calculates the index corresponding to the first item of the next page
    int cmp = page * 12 * 3;

    // Loop that selects from the 1st item of said page to the last item or the second to last item of the page
    for (int i = (page - 1) * ITEMS_PER_PAGE * 3; i < t->content->len && i < cmp; i++) {

        printf("| %s |", (char *) g_ptr_array_index(t->content, i++));
        char * business_name = g_ptr_array_index(t->content, i++);
        printf(" %s", business_name);
        format_line(t->longest_word[1] - strlen(business_name) + 1, ' ', 0);
        float * stars_p = g_ptr_array_index(t->content, i);
        printf("  %.1f  |\n", *stars_p); 
        format_line(t->longest_word[1] + 37, '-', 1);
        
    }

}


void print_table(TABLE t) {

    int flag = 1;
    int page = 1;
    int n_cols;

    while (flag) {

        system("clear");
        switch(t->query) {

            case 2:
                n_cols = 1;
                print_query2(t, page);
                break;

            case 3: 
                print_query3(t, page);
                flag = 0;
                break;

            case 4:
                n_cols = 2;
                print_query4or5(t, page, 4);
                break;

            case 5: 
                n_cols = 2;
                print_query4or5(t, page, 5);
                break;

            case 6: 
                print_query6(t, page);
                break;

            case 7: 
                n_cols = 1;
                print_query7or9(t, page, 7);
                break;

            case 8: 
                n_cols = 3;
                print_query8(t, page);
                break;

            case 9: 
                n_cols = 1;
                print_query7or9(t, page, 9);
                break;
        }

        // Page management
        if (t->query != 3) {

            int x = (t->content->len%(ITEMS_PER_PAGE * n_cols) > 0) ? 1 : 0;

            int max_page = (t->query == 6) ? t->index_bus_per_city->len : t->content->len/(ITEMS_PER_PAGE * n_cols) + x;  
            printf("                                      Page %d/%d\n", page, max_page);
            puts(
                "Insert: \n"
                "\t -> next : for the next page\n"
                "\t -> prev : for the previous page\n"
                "\t -> P(Number) : go to the desired page\n"
                "\t -> last : go to the last page\n"
                "\t -> first : go the first page\n"
                "\t -> quit : to exit the table"
            );

            char * buffer = malloc(BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            char * command = strdup(strtok(buffer, "\n"));
            if (!strcmp("quit", command)) {
                flag = 0;
                system("clear");
            }
            else if (!strcmp("next", command) && page < max_page) {
                page++;
            }
            else if (!strcmp("prev", command) && page > 1) 
                page--;
            else if (!strcmp("first", command))
                page = 1;
            else if (!strcmp("last", command)) 
                page = max_page;
            else if (command[0] == 'P') {
                page = atoi(command + 1);
                if (page < 1) page = 1;
                else if (page > max_page) 
                    page = max_page;
            }

            free(buffer);
            free(command);

        }
    }
    
}

void free_table(TABLE t) {

    g_ptr_array_free(t->content, TRUE);
    g_ptr_array_free(t->index_bus_per_city, TRUE);
    free(t);

}

void general_print(void * content, int is_int, int is_float, int is_string) {

    if (is_int) {

        int * value = (int *) content;
        printf("Value: %d\n", *value);

    }
    else if (is_float) {

        float * value = (float *) content;
        printf("Value: %f\n", *value);

    }
    else {

        char * value = (char *) content;
        printf("Value: %s\n", value);

    }

}


void greet_message() {

    puts(
        "---------------------------------------------------------------------------\n"
        "|                                  WELCOME!                               |\n"
        "---------------------------------------------------------------------------\n\n"
        "Currently loading SGR from default files..."
    );

}

void sgr_initialized_message(int success) {

    if (success == 1)
        puts("\nSGR is now successfuly loaded.");
    else 
        puts("\nSGR unsuccessfuly loaded. Please manually load the necessary files");

}

void queries_menu() {

    puts(
        "----------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
        "You now have the following options\n                                                                                                                                   \n"
        " * Query 1: Manually load new .csv files. Ex: sgr=load_sgr(filepath1,filepath2,filepath3)                                                                              \n"
        " * Query 2: Load businesses started by a certain letter to a variable. Ex: x=businesses_started_by_letter(sgr,'A')                                                     \n"
        " * Query 3: Load a certain business information to a variable. Ex: x=business_info(sgr, \"c3ON_aKOvpGWVZAdPQstqg\")                                                    \n"
        " * Query 4: Load the businesses reviewed by a certain user to a variable. Ex : x=businesses_reviewed(sgr, \"YoVfDbnISlW0f7abNQACIg\")                                  \n"
        " * Query 5: Load the businneses in a certain city with over a certain number of stars to a variable. Ex: x=businesses_with_stars_and_city(sgr, 3.5, \"Austin\")        \n"
        " * Query 6: Load the top businesses by city to a certain variable. Ex: x=top_businesses_by_city(sgr, 5)                                                                \n"
        " * Query 7: Load all the international users to a variable. Ex: x=international_users(sgr)                                                                             \n"
        " * Query 8: Loads the top businesses from a certain category to a variable. Ex: x=top_businesses_with_category(sgr, 20, \"Food\")                                      \n"
        " * Query 9: Loads all the reviews that mention a certain word to a variable. Ex: x=reviews_with_word(sgr, \"and\")                                                     \n"     
        " * Show: Print a certain variable. Ex: show(x)                                                                                                                         \n"
        " * Indexation: Loads element in a certain position of the table to a variable. Ex: z = x[1][3]                                                                         \n"
        " * toCSV: Writes the content of a table to a .csv file. Ex: toCSV(x,'&',filename) -- the filename should not include .csv                                              \n"
        "----------------------------------------------------------------------------------------------------------------------------------------------------------------"
    );

}


void exit_message() {

    puts(
        "\n\n------------------------------\n"
              "Program ended sucessfully.\n"
            "------------------------------"
    );

}
#include <stdlib.h>

#include "../includes/macro.h"
#include "../includes/stats.h"
#include "../includes/reviews.h"


typedef struct reviews {

    GHashTable * review_table;
    long n_reviews;

};

REVIEWS init_reviews_struct() {

    REVIEWS reviews = malloc(sizeof(struct reviews));
    reviews->review_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_review_struct);

    return reviews;
}

void add_review (REVIEWS reviews, REVIEW new_review) {

    g_hash_table_insert(reviews->review_table, get_review_id(new_review), new_review);

}

REVIEW lookup_review (REVIEWS reviews, char * review_id) {

    return g_hash_table_lookup(reviews->review_table, review_id);

}

int validate_review(REVIEW r, USERS u, BUSINESSES b) {

    int v = 0;

    char* review_id = get_review_id(r);
    char* business_id = get_review_business_id(r);
    char* user_id = get_review_user_id(r);
    float stars = get_review_stars(r);
    int useful = get_review_useful(r);
    int funny = get_review_funny(r);
    int cool = get_review_cool(r);
    char* date = get_review_date(r);

    if(strlen(review_id) == ID_SIZE && strlen(business_id) == ID_SIZE 
       && strlen(user_id) == ID_SIZE && stars <= 5 && stars >= 1 
       && useful >= 0 && funny >= 0 && cool >= 0 && validate_review_date(date) 
       && contains_business(b, business_id) && contains_user(u, user_id)) {
           v = 1;
    }

    free(review_id);
    free(business_id);
    free(user_id);
    free(date);

    return v;
}


long get_n_reviews(REVIEWS reviews) {

    return reviews->n_reviews;

}

void set_n_reviews(REVIEWS reviews, long n_reviews) {
    
    reviews->n_reviews = n_reviews;

}

void count_stats_business(REVIEWS reviews, char * business_id, float * average_stars, int * n_reviews) {

    char * business_id_review;

    // iterator to cross an hashtable
    GHashTableIter iter;
    gpointer key, value;

    // Crossing the review hashtable
    g_hash_table_iter_init(&iter, reviews->review_table);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        REVIEW r = (REVIEW) value;
        business_id_review = (char *) get_review_business_id(r);

        // If it's the same id, collect the number of stars and increase the review count
        if (!strcmp(business_id, business_id_review)) {

            *average_stars += get_review_stars(r);
            (*n_reviews)++;
        }

        free(business_id_review);

    }

}

GPtrArray * collect_businesses_reviewed(REVIEWS reviews, BUSINESSES businesses, char * user_id, int * longest_name) {

    char * business_id, * business_name, * user_id_review;

    // GPtrArray that will hold all the businesses reviewed by the user
    GPtrArray * bus_rev = g_ptr_array_new_full(0, g_free);

    // Iterator that allows to cross a hashtable
    GHashTableIter iter;
    gpointer key, value;

    // Crossing the review hashtable
    g_hash_table_iter_init (&iter, reviews->review_table);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        REVIEW r = (REVIEW) value;
        user_id_review = get_review_user_id(r);

        // If the user id matches, add the business to the table
        if (!strcmp(user_id_review, user_id)) {

            // Adding business_id
            business_id = get_review_business_id(r);
            g_ptr_array_add(bus_rev, business_id);

            // Adding business_name
            BUSINESS b = lookup_business(businesses, business_id);
            business_name = get_business_name(b);
            g_ptr_array_add(bus_rev, business_name);

            // Check if the business name is longer than the previous ones
            if (strlen(business_name) > *longest_name) 
                *longest_name = strlen(business_name);

        }

        free(user_id_review);

    }

    return bus_rev;

}

void upd_stars_bus(REVIEWS reviews, GHashTable ** hasht_bus_stats, int query) {

    // If it's query 6, the table will be passed empty
    if (query == 6)  
        *hasht_bus_stats = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_bus_stats);

    char * business_id;

    // Iterator that allows to cross a hashtable
    GHashTableIter iter;
    gpointer key, value;

    // Selecting and crossing the reviews table
    g_hash_table_iter_init(&iter, reviews->review_table);
    while(g_hash_table_iter_next (&iter, &key, &value)) {

        REVIEW r = (REVIEW) value;
        business_id = get_review_business_id(r);

        BUS_STATS b = g_hash_table_lookup(*hasht_bus_stats, business_id);

        // If the business is already in the table with the stats from the businesses, update the stats
        if (b) {    
             
            add_review_bus_stats(&b);
            add_stars_bus_stats(&b, get_review_stars(r));

        }
        // If the business isn't in the hashtable and it's the query6, add it with their initialized stats from this review
        // For the query 5 there is no need to add, because we're limited to businesses on one city that were already selected
        else if (!b && query == 6) {// If it doesn't exist, generate it and insert it on the hashtable
            
            b = init_bus_stats();
            set_id_bus_stats(&b, business_id);
            add_stars_bus_stats(&b, get_review_stars(r));
            add_review_bus_stats(&b);
            g_hash_table_insert(*hasht_bus_stats, strdup(business_id), b);
            
        }

        free(business_id);

    }

}

GPtrArray * collects_int_users(REVIEWS reviews, BUSINESSES businesses, int * n_int_users) {

    // Iterator that allows to cross a hashtable
    GHashTableIter iter;
    gpointer key, value;

    GPtrArray * content = g_ptr_array_new_full(0, g_free);

    // Hashtable to manage which states has a user visited
    GHashTable * users_states = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_user_visits);

    // Crossing the review table
    g_hash_table_iter_init(&iter, reviews->review_table);
    while(g_hash_table_iter_next (&iter, &key, &value)) {

        REVIEW r = (REVIEW) value;

        char * user_id = get_review_user_id(r);
        char * business_id = get_review_business_id(r);
        BUSINESS b = lookup_business(businesses, business_id);
        char * city = get_business_city(b);

        // Looks up the user id in the user states hashtable
        USER_VISITS user_info = g_hash_table_lookup(users_states, user_id);
        char * state_visited = get_city_visited(user_info);
        int n_states = get_n_cities_user(user_info);

        // If the user already was added and he has been to 1 state and those are diferent then the users is considered "international"
        if (user_info && n_states == 1 && strcmp(city, state_visited)) {             
         
            add_n_city_to_user(&user_info);
            g_ptr_array_add(content, strdup(user_id));
            (*n_int_users)++;  

        }
        else if (!user_info) { // if the user doesn't exist, add it to the user states hashtable

            user_info = init_user();
            add_n_city_to_user(&user_info);
            set_city_visited(&user_info, city);
            set_id_user_visits(&user_info, user_id);

            g_hash_table_insert(users_states, strdup(user_id), user_info);    

        }

        free(user_id);
        free(city);
        free(business_id);
        if (state_visited) free(state_visited);

    }

    g_hash_table_destroy(users_states);

    return content;

}

GPtrArray * collects_reviews_with_word(REVIEWS reviews, char * word) {
    
    // Iterator that allows to cross a hashtable
    GHashTableIter iter;
    gpointer key, value;

    int i = 0;
    int l = 0;
    int flagaux;
    int dif;

    // array to save the review ids
    GPtrArray * reviews_ids = g_ptr_array_new_full(50, g_free);

    g_hash_table_iter_init(&iter, reviews->review_table);
    while(g_hash_table_iter_next (&iter, &key, &value)) {

        REVIEW r = (REVIEW) value;
        char * review_id = get_review_id(r);
        char * rev_text = get_review_text(r);
        flagaux = 0;
        dif = 0;

        //while the word wasnt found in the text
        while(!flagaux && dif<strlen(rev_text)) {

            char * exists_word = strstr(rev_text+dif, word);
            
            // if strstr returns a string
            if (exists_word) {

                int flag = 1;

                //if the word isn't in the beginning of the text
                if(strcmp(exists_word, rev_text)) {
                    
                    //if the character before the word isn't a space and a ponctuation mark
                    if(!ispunct(*(exists_word-1)) && *(exists_word-1) != ' ') {
                        flag = 0; //the word wasn't found
                    }
                }

                for (l = 0; l < strlen(word) && flag; l++) {
                    flag = exists_word[l] == word[l];
                }

                //if the character after the word is a ponctuation mark
                if (flag && (ispunct(exists_word[l]) || exists_word[l] == ' ' )) {

                    //the word was found and the review id is added to the array
                    flagaux = 1;
                    g_ptr_array_add(reviews_ids, strdup(review_id));
                }
                
                dif = exists_word - rev_text + 1;

            }
            else 
                flagaux = 1;
            
        }

        free(rev_text);
        free(review_id);
        
    }

    return reviews_ids;

}

void free_reviews_struct(REVIEWS reviews) {

    g_hash_table_destroy(reviews->review_table);
    free(reviews);

}


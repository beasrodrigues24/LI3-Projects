#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/sgr.h"
#include "../includes/stats.h"
#include "../includes/users.h"
#include "../includes/reviews.h"
#include "../includes/interface.h"
#include "../includes/businesses.h"


struct sgr {

    USERS users;
    REVIEWS reviews;
    BUSINESSES businesses;
    
};  

/*
QUERY 1
*/
SGR load_sgr(char * users, char * businesses, char * reviews) {

    SGR new = malloc(sizeof(SGR));

    // Loads each file
    new->users = load_user_file(users);
    new->businesses = load_business_file(businesses);
    new->reviews = load_review_file(reviews, new->businesses, new->users);

    // Checks the previous loading
    if (new->users && new->businesses && new->reviews) return new;
    else {
        if (new->users) free_users_struct(new->users);
        else if (new->businesses) free_businesses_struct(new->businesses);
        else if (new->reviews) free_reviews_struct(new->reviews);
        free(new);
        return NULL;
    }

}

/*
QUERY 2
*/
TABLE businesses_started_by_letter(SGR sgr, char letter) {
    
    // Initializes a table for query2
    TABLE t = init_table(2);

    int * total_businesses = malloc(sizeof(int)); 
    *total_businesses = 0;
    int longest = 0;
    
    // Array with all the businesses names
    GPtrArray * businesses_by_letter = collect_businesses_by_letter(sgr->businesses, letter, &longest, total_businesses);

    set_table_cont_parray(&t, businesses_by_letter);

    add_to_table(&t, *total_businesses, total_businesses);
    set_longest_word(&t, longest, 0);

    return t;

}

/*
QUERY 3
*/
TABLE business_info(SGR sgr, char * business_id) {

    // Initializes a table for query3
    TABLE t = init_table(3);
    int i = 0;

    // Looks up business by business id in the businesse hashtables
    BUSINESS b = lookup_business(sgr->businesses, business_id);

    if (b) {

        // Adding the name, city and state of the business to the table
        add_to_table(&t, i++, get_business_name(b));
        add_to_table(&t, i++, get_business_city(b));
        add_to_table(&t, i++, get_business_state(b));

        // Pointer to hold values to be stored in a GPointerArray
        float * average_stars = malloc(sizeof(float));
        *average_stars = 0;
        long * review_count = malloc(sizeof(long));
        *review_count = 0;

        count_stats_business(sgr->reviews, business_id, average_stars, review_count);

        // Calculate average stars and add values to the table
        *average_stars = (*review_count > 0) ? (*average_stars)/(*review_count) : 0;
        add_to_table(&t, i++, average_stars);
        add_to_table(&t, i++, review_count);
        
    }

    return t;
}

/*
QUERY 4
*/
TABLE businesses_reviewed(SGR sgr, char * user_id) {

    // Initializes a table for query4
    TABLE t = init_table(4);

    // Variable to store the largest word for formatting the table
    int longest_name = 0;

    // Array with all the businesses information
    GPtrArray * bus_rev = collect_businesses_reviewed(sgr->reviews, sgr->businesses, user_id, &longest_name);

    set_table_cont_parray(&t, bus_rev);

    set_longest_word(&t, longest_name, 1);

    return t;
}

/*
Query 5
*/
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char * city) { 

    // Initializes a table for query5
    TABLE t = init_table(5);

    int longest_name = 0;
    float total_stars;
    int n_reviews;
    char * business_id , * business_name;

    // Iterator to cross an hashtable
    GHashTableIter iter;
    gpointer key, value;

    int i = 0; // Variable to insert in table by index

    // Creates an auxiliar hashtable to hold all the businesses from that city and its stats
    GHashTable * hasht_businesses_from_city = collect_businesses_from_city(sgr->businesses, city);

    upd_stars_bus(sgr->reviews, &hasht_businesses_from_city, 5);

    // Crossing the businesses from city hashtable
    g_hash_table_iter_init(&iter, hasht_businesses_from_city);
    while(g_hash_table_iter_next (&iter, &key, &value)) {

        BUS_STATS tmp = (BUS_STATS) value;

        n_reviews = (int) get_n_review_bus_stats(tmp);
        total_stars = (float) get_stars_bus_stats(tmp);

        // Calculate average stars of said business
        float average_stars = (n_reviews > 0) ? total_stars/n_reviews : 0;
        // If the average is above the required, add to the table
        if (average_stars >= stars) {

            business_id = get_id_bus_stats(tmp);
            BUSINESS b = lookup_business(sgr->businesses, business_id);
            add_to_table(&t, i++, business_id);

            business_name = get_business_name(b);
            add_to_table(&t, i++, business_name);

            if (strlen(business_name) > longest_name)
                longest_name = strlen(business_name); 

        }

    }

    g_hash_table_destroy(hasht_businesses_from_city);

    set_longest_word(&t, longest_name, 1);

    return t;

}


/*
Query 6
*/
struct businesses_in_city {

    char * city;
    GPtrArray * businesses;

};

void free_business_in_city(struct businesses_in_city * s) {

    free(s->city);
    g_ptr_array_free(s->businesses, TRUE);
    free(s);

}

static gint compare_businesses (gconstpointer x, gconstpointer y) {

    const BUS_STATS b1 = *(BUS_STATS *) x;
    const BUS_STATS b2 = *(BUS_STATS *) y;

    float stars_b1 = get_stars_bus_stats(b1);
    float stars_b2 = get_stars_bus_stats(b2);
    int nrevs_b1 = get_n_review_bus_stats(b1);
    int nrevs_b2 = get_n_review_bus_stats(b2);

    float average1 = (nrevs_b1 > 0) ? stars_b1/nrevs_b1 : 0;
    float average2 = (nrevs_b2 > 0) ? stars_b2/nrevs_b2 : 0;

    return average2 >= average1;
}

char * to_uppercase(char * string) {

    for (int i = 0; string[i]; i++) 
        if (string[i] >= 'a' && string[i] <= 'z')
            string[i] -= 32;

    return string;

}

TABLE top_businesses_by_city(SGR sgr, int top) {

    // Initializes a table for query6
    TABLE t = init_table(6);
    // Adds the top value to the table struct
    set_top(&t, top);

    // Iterator to cross an hashtable
    GHashTableIter iter;
    gpointer key, value;

    int i = 0; // Variable to control inserting by index in the table
    int n_city = 0; // Variable to control number of cities
    int longest_name = 0;

    // Create auxiliar hashtable: this one connects one city to all of it's businesses
    GHashTable * businesses_by_city = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_business_in_city); 

    // Create auxiliar hashtable: this one connects one business to its stats
    GHashTable * businesses_stars = NULL;
    upd_stars_bus(sgr->reviews, &businesses_stars, 6);

    // Select the hashtable with the businesses and its stars information to cross
    g_hash_table_iter_init (&iter, businesses_stars);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        BUS_STATS tmp = (BUS_STATS) value;

        char * business_id = get_id_bus_stats(tmp);

        BUSINESS b = lookup_business(sgr->businesses, business_id);
        char * city = to_uppercase(get_business_city(b));
        
        // Searches for the city of the business in the hashtable with the businesses sorted by city
        struct businesses_in_city * in_city = g_hash_table_lookup(businesses_by_city, city); 

        // If it exists, add one new business to the struct
        if (in_city) {

            g_ptr_array_add(in_city->businesses, clone_bus_stats(tmp));
            free(city);

        }
        else { // If it doesn't exist, create the new city and add the business there

            in_city = malloc(sizeof(struct businesses_in_city));
            in_city->city = city;
            in_city->businesses = g_ptr_array_new_full(0, free_bus_stats);
            g_ptr_array_add(in_city->businesses, clone_bus_stats(tmp));
            g_hash_table_insert(businesses_by_city, strdup(city), in_city);

        }

        free(business_id);
 
    }

    // Select the hashtable with the businesses sorted by city to cross
    g_hash_table_iter_init (&iter, businesses_by_city);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        int j = 0; // Variable to control adding the "top" number of businesses for each city

        int * first = malloc(sizeof(int)); // Variable to hold where the first business of each city is placed
        *first = i;

        // Select a city
        struct businesses_in_city * city_businesses = (struct businesses_in_city *) value;
        // Sort the businesses by average number of stars
        g_ptr_array_sort(city_businesses->businesses, compare_businesses);
        // Add the city name to the table
        add_to_table(&t, i++, strdup(city_businesses->city));

        while(j < top && j < city_businesses->businesses->len) {

            // Selecting a business
            BUS_STATS tmp = g_ptr_array_index(city_businesses->businesses, j++);
        
            // Getting the necessary info and adding it to the table
            char * business_id = get_id_bus_stats(tmp);
            BUSINESS b = lookup_business(sgr->businesses, business_id);
            char * business_name = get_business_name(b);

            if (strlen(business_name) > longest_name)
                longest_name = strlen(business_name);

            // Calculate average stars 
            float * average_stars = malloc(sizeof(float));
            int n_revs = get_n_review_bus_stats(tmp);
            float t_stars = get_stars_bus_stats(tmp);
            *average_stars = (n_revs > 0) ? t_stars/n_revs : 0;

            add_to_table(&t, i++, business_id);
            add_to_table(&t, i++, business_name);
            add_to_table(&t, i++, average_stars);

        }

        add_index_bus_per_city(&t, n_city++, first);

    }

    // Destroy auxiliar tables
    g_hash_table_destroy(businesses_by_city);
    g_hash_table_destroy(businesses_stars);

    set_longest_word(&t, longest_name, 0);

    return t;

}

/*
Query 7
*/

TABLE international_users(SGR sgr) {

    // Initializes a table for query7
    TABLE t = init_table(7);

    int * n_int_users = malloc(sizeof(int));
    *n_int_users = 0;

    GPtrArray * content = collects_int_users(sgr->reviews, sgr->businesses, n_int_users);
    set_table_cont_parray(&t, content);

    // Adds the number of total international users
    add_to_table(&t, content->len, n_int_users);

    return t;

}

/*
Query 8
*/
TABLE top_businesses_with_category(SGR sgr, int top, char * category) {

    // Initializes a table for query8
    TABLE t = init_table(8);
    int longest_name = 0;

    // Iterator to cross hashtables
    GHashTableIter iter;
    gpointer key, value;

    // HashTable with all the businesses with said categroy
    GHashTable * businesses_categories = collects_businesses_by_category(sgr->businesses, category);

    // Create a GPtrArray that will be sorted afterwards by average stars 
    GPtrArray * sorted_businesses = g_ptr_array_new_full(0, free_bus_stats);
    
    upd_stars_bus(sgr->reviews, &businesses_categories, 8);

    // Crossing the businesses_cateogires hashtable to add the businesses to the GPtrArray *
    g_hash_table_iter_init(&iter, businesses_categories);
    while(g_hash_table_iter_next (&iter, &key, &value)) {

        BUS_STATS bs = (BUS_STATS) value;
        g_ptr_array_add(sorted_businesses, clone_bus_stats(bs));

    }

    // Sort the GPtrArray
    g_ptr_array_sort(sorted_businesses, (GCompareFunc) compare_businesses);

    // Add to the table the top businesses or the length of the GPtrArray if len < top
    for (int i = 0, j = 0; i < top && i < sorted_businesses->len; i++) {

        // Adds the business_id
        BUS_STATS tmp = g_ptr_array_index(sorted_businesses, i);
        char * business_id = get_id_bus_stats(tmp);
        add_to_table(&t, j++, business_id); // Adds id to table

        // Adds the business_name
        BUSINESS b = lookup_business(sgr->businesses, business_id);
        char * business_name = get_business_name(b);
        add_to_table(&t, j++, business_name);

        // Tracks the longer name for formatting the table afterwards
        if (strlen(business_name) > longest_name) 
            longest_name = strlen(business_name);

        // Calculates average stars
        float * av_stars_p = malloc(sizeof(float));
        int n_reviews = get_n_review_bus_stats(tmp);
        int total_stars = get_stars_bus_stats(tmp);
        *av_stars_p = (n_reviews > 0) ? total_stars/n_reviews : 0;
        add_to_table(&t, j++, av_stars_p);

    } 

    g_hash_table_destroy(businesses_categories);
    g_ptr_array_free(sorted_businesses, TRUE);

    set_longest_word(&t, longest_name, 1);

    return t;
    
}

/*
Query 9
*/
TABLE reviews_with_word(SGR sgr, char * word) {

    //initializes a table for query 9
    TABLE t = init_table(9);

    //array with all the reviews ids that have the word in their text
    GPtrArray * reviews_ids = collects_reviews_with_word(sgr->reviews, word);

    
    set_table_cont_parray(&t, reviews_ids);

    return t;
}

void free_sgr(SGR sgr) {

    free_users_struct(sgr->users);
    free_reviews_struct(sgr->reviews);
    free_businesses_struct(sgr->businesses);
    free(sgr);

}

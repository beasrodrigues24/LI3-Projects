#include <stdlib.h>

#include "../includes/stats.h"
#include "../includes/businesses.h"


typedef struct businesses {

    GHashTable * business_table;
    long n_businesses;

};

BUSINESSES init_businesses_struct () {

    BUSINESSES businesses = malloc(sizeof(struct businesses));
    businesses->business_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_business_struct);

    return businesses;

}

void add_business (BUSINESSES businesses, BUSINESS new_business) {

    g_hash_table_insert(businesses->business_table, get_business_id(new_business), new_business);

}

BUSINESS lookup_business (BUSINESSES businesses, char * business_id) {

    return g_hash_table_lookup(businesses->business_table, business_id);

}

int contains_business(BUSINESSES businesses, char * business_id) {

    return g_hash_table_contains(businesses->business_table, business_id);

}

long get_n_businesses (BUSINESSES businesses) {

    return businesses->n_businesses;

}

void set_n_businesses (BUSINESSES businesses, long n_businesses) {

    businesses->n_businesses = n_businesses;

}

GPtrArray * collect_businesses_by_letter(BUSINESSES businesses, char letter, int * longest_string, int * total_businesses) {

    // Array that will hold the content to be then added to the table
    GPtrArray * content = g_ptr_array_new_full(0, g_free);

    // Iterator to cross an hashtable
    GHashTableIter iter;
    gpointer key, value;

    // Crossing the business table
    g_hash_table_iter_init (&iter, businesses->business_table);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        BUSINESS b = (BUSINESS) value;
        char * business = get_business_name(b);

        // If the businesses start with the same letter, add it to the gptrarray
        if (toupper(business[0]) == toupper(letter)) {

            // Checks if this business name is longer than the longest saved yet
            int length_string = strlen(business);
            if (length_string > *longest_string)
                *longest_string = length_string;

            // Adding to the gptrarray
            g_ptr_array_add(content, business);  
            (*total_businesses)++;

        }
        else 
            free(business);
        
    }

    return content;

}

GHashTable * collect_businesses_from_city(BUSINESSES businesses, char * city) {

    // HashTable that will hold the businesses from that city
    GHashTable * hasht_businesses_from_city = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_bus_stats); 

    // Iterator to cross the table
    GHashTableIter iter;
    gpointer key, value;

    char * business_id;

    g_hash_table_iter_init (&iter, businesses->business_table);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        BUSINESS b = (BUSINESS) value;
        char * business_city = get_business_city(b);

        // If it's the correct city, add it to the auxiliar hashtable
        if (!strcasecmp(business_city, city)) {

            BUS_STATS tmp = init_bus_stats();

            business_id = get_business_id(b);
            set_id_bus_stats(&tmp, business_id);

            g_hash_table_insert(hasht_businesses_from_city, business_id, tmp);

        }

        free(business_city);

    }

    return hasht_businesses_from_city;

}

GHashTable * collects_businesses_by_category(BUSINESSES businesses, char * category) {

    GHashTableIter iter;
    gpointer key, value;

    // Auxiliar hashtable to hold the businesses with the category
    GHashTable * businesses_in_category = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_bus_stats);

    // Selects the table with the businesses to cross
    g_hash_table_iter_init(&iter, businesses->business_table);
    // Adding businesses with the category to the hashtable
    while(g_hash_table_iter_next (&iter, &key, &value)) {

        BUSINESS b = (BUSINESS) value;
        char * categories = get_business_categories(b);
        char * buffer = strtok(categories, ",");
        int flag = 1;
        while (buffer && flag) {
            
            // If the category if found add the business in a BUS_STATS struct to the businesses_categories hashtable
            if (!strcmp(buffer, category)) {

                BUS_STATS tmp = init_bus_stats();
                char * business_id = get_business_id(b);
                set_id_bus_stats(&tmp, business_id);
                g_hash_table_insert(businesses_in_category, business_id, tmp);
                flag = 0;

            }
            // Moves to the following category
            buffer = strtok(NULL, ",");
        }

        free(categories);
    }

    return businesses_in_category;

}

void free_businesses_struct (BUSINESSES businesses) {

    g_hash_table_destroy(businesses->business_table);
    free(businesses);

}
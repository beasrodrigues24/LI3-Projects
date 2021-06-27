/**
 @file businesses.h
 \brief Module where are defined functions that manipulate struct BUSINESSES
 */
#ifndef Businesses
#define Businesses

#include <glib.h>

#include "business.h"

/**
\brief Struct that holds multiple businesses information
*/
typedef struct businesses * BUSINESSES;

/**
\brief Function that initializes an businesses struct
 @return Businesses struct initialized
*/
BUSINESSES init_businesses_struct ();

/**
\brief Function that adds a new business to the businesses catalog
 @param businesses Struct with all the businesses information
 @param new_business New business to add
*/
void add_business (BUSINESSES businesses, BUSINESS new_business);

/**
\brief Searches a business in the struct businesses using the business-id
 @param businesses Struct with all the businesses information
 @param business_id Business-id of the business being searched for
 @return Corresponding business or NULL if there isn't one
*/
BUSINESS lookup_business (BUSINESSES businesses, char * business_id);

/**
\brief checks if there's a certain business
 @param businesses businesses struct
 @param business_id business id
*/ 
int contains_business(BUSINESSES businesses, char * business_id);

/**
\brief Function that allows to know the number of businesses contained in the struct businesses
 @param businesses Struct businesses
 @return Number of businesses that exist in the struct
*/
long get_n_businesses (BUSINESSES businesses);

/**
\brief Defines the number of businesses that exist in the struct
 @param businesses Struct businesses
 @param n_businesses Number of businesses that exist in the struct
*/
void set_n_businesses (BUSINESSES businesses, long n_businesses);

/**
\brief collects all the businesses started by one letter
 @param businesses struct businesses
 @param letter first letter of the businesses to be collected
 @param longest_string longest business name collected
 @param total_businesses number of businessses collected
 @return array with businesses names
*/ 
GPtrArray * collect_businesses_by_letter(BUSINESSES businesses, char letter, int * longest_string, int * total_businesses);

/**
\brief collects all the businesses from one city
 @param businesses struct businesses
 @param city city name
 @return hashtable with businesses and their stats
*/
GHashTable * collect_businesses_from_city(BUSINESSES businesses, char * city);


/**
\brief collects all the businesses with one category
 @param businesses struct businesses 
 @param category category name
 @return hashtable with businesses and their stats
*/
GHashTable * collects_businesses_by_category(BUSINESSES businesses, char * category);

/**
\brief Frees the businesses struct
 @param businesses Struct to be freed
*/
void free_businesses_struct (BUSINESSES businesses);

#endif
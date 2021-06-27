/**
 @file reviews.h
 \brief Module responsible for the struct REVIEWS
 */
#ifndef Reviews
#define Reviews

#include <glib.h>

#include "users.h"
#include "review.h"
#include "businesses.h"

/**
 * @brief Struct that holds multiple reviews information
*/
typedef struct reviews * REVIEWS;

/**
 * @brief Function that initializes a reviews struct
 * @return Reviews struct initialized
*/
REVIEWS init_reviews_struct();

/**
 * @brief Function that adds a new review to the reviews catalog
 * @param reviews Struct with all the reviews information
 * @param new_review New review to add
*/
void add_review (REVIEWS reviews, REVIEW new_review);

/**
 * @brief Searches a review in the struct reviews using the review-id
 * @param reviews Struct with all the reviews information
 * @param review_id Review-id of the review being searched for
 * @return Corresponding review or NULL if there isn't one
*/
REVIEW lookup_review (REVIEWS reviews, char * review_id);

/**
 * @brief Validates a review
 * @param r Review
 * @param u Struct with all the users information
 * @param b Struct with all the busiesses information
 * @return 1 if it is a valid review, 0 if it isn't
*/
int validate_review(REVIEW r, USERS u, BUSINESSES b);

/**
 * @brief Function that allows to know the number of reviews 
 * contained in the struct reviews
 * @param reviews Struct reviews
 * @return Number of reviews that exist in the struct
*/
long get_n_reviews(REVIEWS reviews);

/**
 * @brief Defines the number of reviews that exist in the struct
 * @param reviews Struct reviews
 * @param n_reviews Number of reviews that will exist in the struct
*/
void set_n_reviews(REVIEWS reviews, long n_reviews);

/**
 * @brief Collects the number of stars and increases the review count of a certain business
 * @param reviews Reviews struct
 * @param business_id Business-id
 * @param average_stars Stars
 * @param n_reviews Number of reviews
*/
void count_stats_business(REVIEWS reviews, char * business_id, float * average_stars, int * n_reviews);

/**
 * @brief Adds a business to a table
 * @param reviews Reviews struct
 * @param businesses Businesses struct
 * @param user_id User-id
 * @param longest_name Longest name of a business
 * @return Pointer array
*/
GPtrArray * collect_businesses_reviewed(REVIEWS reviews, BUSINESSES businesses, char * user_id, int * longest_name);

/**
 * @brief Updates de hashtable of business-stats
 * @param reviews Reviews struct
 * @param hasht_bus_stats Hashtable of business-stats
 * @param query Query
*/
void upd_stars_bus(REVIEWS reviews, GHashTable ** hasht_bus_stats, int query);

/**
 * @brief Collects users
 * @param reviews Reviews struct
 * @param businesses Businesses struct
 * @param int_users Longest name of a business
 * @return Pointer array
*/
GPtrArray * collects_int_users(REVIEWS reviews, BUSINESSES businesses, int * n_int_users);

/**
 * @brief colects reviews that have a given word in their text
 * @param reviews reviews struct
 * @param word word to look for in the reviews
 * @return array with review ids
*/
GPtrArray * collects_reviews_with_word(REVIEWS reviews, char * word);

/**
 * @brief Frees the reviews struct
 * @param reviews Struct to be freed
*/
void free_reviews_struct(REVIEWS reviews);

#endif
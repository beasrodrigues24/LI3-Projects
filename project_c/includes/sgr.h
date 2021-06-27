/**
 @file sgr.h
 \brief Module where are defined all the queries
 */
#ifndef Sgr
#define Sgr

#include "../includes/view.h"

/**
 * @brief Struct containing users, businesses 
 * and reviews information
*/
typedef struct sgr * SGR;

/**
 * @brief Initializes a sgr struct
 * @return SGR initialized
*/
SGR init_sgr();

/* query 1 */

/**
 * @brief Loads the sgr struct
 * @param users Users struct
 * @param businesses Businesses struct
 * @param reviews Reviews struct
 * @return SGR struct loaded
*/
SGR load_sgr(char * users, char * businesses, char * reviews);

/* query 2 */

/**
 * @brief Determines a list of business names and the total 
 * number of businesses started by a letter
 * @param sgr Sgr struct
 * @param letter First letter
 * @return List of business names
*/
TABLE businesses_started_by_letter(SGR sgr, char letter);

/* query 3 */

/**
 * @brief Determines the information of a business: name, city, 
 * state, stars and total number of reviews
 * @param sgr Sgr struct
 * @param business_id Business-id
 * @return Information of a business
*/
TABLE business_info(SGR sgr, char * business_id);

/* query 4 */

/**
 * @brief Determines a list of businesses reviewd 
 * by an user (business-id and business-name)
 * @param sgr Sgr struct
 * @param user_id User-id
 * @return List of businesses reviewed by the user
*/
TABLE businesses_reviewed(SGR sgr, char *user_id);

/* query 5 */

/**
 * @brief Determines a list of businesses with n or more stars in 
 * a city (business-id and business-name)
 * @param sgr Sgr struct
 * @param stars Number of stars
 * @param city City
 * @return List of businesses
*/
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char * city);

/* query 6 */

/**
 * @brief Determines a list of the top n businesses 
 * in each city (business-id, business-name and stars)
 * @param sgr Sgr struct
 * @param top Top n
 * @return List of the top n businesses
*/
TABLE top_businesses_by_city(SGR sgr, int top);

/* query 7 */

/**
 * @brief Determines a list of user-ids and the total 
 * number of users that reviewed businesses of different states
 * @param sgr Sgr struct
 * @return List of user-ids
*/
TABLE international_users(SGR sgr);

/* query 8 */

/**
 * @brief Determines a list of the top n businesses that belong in a certain 
 * category (business-id, business-name and stars)
 * @param sgr Sgr struct
 * @param top Top n
 * @param category Category
 * @return List of n businesses
*/
TABLE top_businesses_with_category(SGR sgr, int top, char * category);

/* query 9 */

/**
 * @brief Determines a list of review-ids that 
 * refer a certain word in the text field
 * @param sgr Sgr struct
 * @param word Word
 * @return List of review-ids
*/
TABLE reviews_with_word(SGR sgr, char * word);

/**
 * @brief Frees all memory used by struct sgr
 * @param sgr Sgr struct
*/
void free_sgr(SGR sgr);

#endif
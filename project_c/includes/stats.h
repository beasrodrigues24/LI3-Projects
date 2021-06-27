/**
 @file stats.h
 \brief Module where are defined functions that manipulate auxiliar structs
 */
#ifndef Stats
#define Stats

/**
 * @brief Struct containing business-id, number of reviews 
 * and total number of stars
*/
typedef struct business_stats * BUS_STATS;

/**
 * @brief Initializes a business-stats struct
 * @return Business-stats initialized
*/
BUS_STATS init_bus_stats();

/**
 * @brief Returns the business-id of a business-stats
 * @param bs Business-stats struct
 * @return String containing the business-id
*/
char * get_id_bus_stats(BUS_STATS bs);

/**
 * @brief Sets a business-id to a business-stats
 * @param bs Pointer to a business-stats
 * @param business_id String containing the new business-id
*/
void set_id_bus_stats(BUS_STATS * bs, char * business_id);

/**
 * @brief Returns the number of reviews of a business-stats
 * @param bs Business-stats struct
 * @return Number of reviews
*/
int get_n_review_bus_stats(BUS_STATS bs);

/**
 * @brief Sets a number of reviews to a business-stats
 * @param bs Pointer to a business-stats
 * @param n_rev New number of reviews
*/
void set_review_bus_stats(BUS_STATS * bs, int n_rev);

/**
 * @brief Function that increments the number of 
 * reviews of a business-stats
 * @param bs Pointer to a business-stats
*/
void add_review_bus_stats(BUS_STATS * bs);

/**
 * @brief Returns the total number of stars of a business-stats
 * @param bs Business-stats struct
 * @return Total number of stars
*/
int get_stars_bus_stats(BUS_STATS bs);

/**
 * @brief Function that adds stars to the total number of 
 * stars of a business-stats
 * @param bs Pointer to a business-stats
 * @param stars Stars
*/
void add_stars_bus_stats(BUS_STATS * bs, float stars);

/**
 * @brief Clones a business-stats struct
 * @param bs Business-stats struct
 * @return Cloned business-stats
*/
BUS_STATS clone_bus_stats(BUS_STATS bs);

/**
 * @brief Frees all memory used by 
 * struct business-stats
 * @param bs Business-stats struct
*/
void free_bus_stats(BUS_STATS bs);

/**
 * @brief Struct containing user-id, number of cities 
 * and the cities reviewed 
*/
typedef struct user_visits_info * USER_VISITS;

/**
 * @brief Initializes an user-visits struct
 * @return User-visits initialized
*/
USER_VISITS init_user_visits();

/**
 * @brief Returns the business-id of a business-stats
 * @param us User-visits struct
 * @return String containing the user-id
*/
char * get_id_user_visits(USER_VISITS us);

/**
 * @brief Sets a user-id to an user-visits
 * @param us Pointer to an user-visits
 * @param user_id String containing the new user-id
*/
void set_id_user_visits(USER_VISITS * us, char * user_id);

/**
 * @brief Returns the number of cities of an user-visits
 * @param us User-visits struct
 * @return Number of cities
*/
int get_n_cities_user(USER_VISITS us);

/**
 * @brief Function that increments the number of 
 * cities of an user-visits
 * @param us Pointer to an user-visits
*/
void add_n_city_to_user(USER_VISITS * us);

/**
 * @brief Returns the cities visited of an user-visits
 * @param us User-visits struct
 * @return String containing the cities visited
*/
char * get_city_visited(USER_VISITS us);

/**
 * @brief Sets a city visited to an user-visits
 * @param us Pointer to an user-visits
 * @param city String containing the new city visited
*/
void set_city_visited(USER_VISITS * us, char * city);

/**
 * @brief Frees all memory used by 
 * struct user-visits
 * @param us User-visits struct
*/
void free_user_visits(USER_VISITS us);

#endif
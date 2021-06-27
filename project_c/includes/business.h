/**
 @file business.h
 \brief Module where are defined functions that manipulate struct BUSINESS
 */
#ifndef Business
#define Business

/**
 * @brief Struct containing business information
*/
typedef struct business * BUSINESS;

/**
 * @brief Initializes a business
 * @return Business initialized
*/
BUSINESS init_business ();

/**
 * @brief Validates a business
 * @param business Business struct
 * @return 1 if it is a valid business, 0 if it isn't
*/
int validate_business (BUSINESS business);

/**
 * @brief Returns the id of one business
 * @param b Business
 * @return String containing the business-id
*/
char * get_business_id(BUSINESS b);

/**
 * @brief Sets an id to one business
 * @param b Pointer to a business
 * @param new_id String containing the new business-id
*/
void set_business_id(BUSINESS * b, char * new_id);

/**
 * @brief Returns the name of one business
 * @param b Business
 * @return String containing the business-name
*/
char * get_business_name(BUSINESS b);

/**
 * @brief Sets a name to one business
 * @param b Pointer to a business
 * @param new_name String containing the new business-name
*/
void set_business_name(BUSINESS * b, char * new_name);

/**
 * @brief Returns the city of one business
 * @param b Business
 * @return String containing the business-city
*/
char * get_business_city(BUSINESS b);

/**
 * @brief Sets a city to one business
 * @param b Pointer to a business
 * @param new_city String containing the new business-city
*/
void set_business_city(BUSINESS * b, char * new_city);

/**
 * @brief Returns the state of one business
 * @param b Business
 * @return String containing the business-state
*/
char * get_business_state(BUSINESS b);

/**
 * @brief Sets a state to one business
 * @param b Pointer to a business
 * @param new_state String containing the new business-state
*/
void set_business_state(BUSINESS * b, char * new_state);

/**
 * @brief Returns the categories of one business
 * @param b Business
 * @return String containing the business-categories
*/
char * get_business_categories(BUSINESS b);

/**
 * @brief Sets categories to one business
 * @param b Pointer to a business
 * @param new_categories String containing the new business-categories
*/
void set_business_categories(BUSINESS * b, char * new_categories);

/**
 * @brief Frees all memory used by struct business
 * @param businesses Business
*/
void free_business_struct (BUSINESS businesses);

#endif
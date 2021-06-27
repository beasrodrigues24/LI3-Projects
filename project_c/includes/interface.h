/**
 @file interface.h
 \brief Module responsible for loading the struct files
*/
#ifndef Interface
#define Interface

#include "../includes/users.h"
#include "../includes/reviews.h"
#include "../includes/businesses.h"

/**
 * @brief Loads the users file
 * @param path Path to the user file
 * @return Users struct loaded
*/
USERS load_user_file (char * path);

/**
 * @brief Loads the businesses file
 * @param path Path to the businesses file
 * @return Businesses struct loaded
*/
BUSINESSES load_business_file (char * path);

/**
 * @brief Loads the reviews file
 * @param path Path to the reviews file
 * @param businesses Struct with all the busiesses information
 * @param users Struct with all the users information
 * @return Reviews struct loaded
*/
REVIEWS load_review_file (char * path, BUSINESSES businesses, USERS users);

#endif
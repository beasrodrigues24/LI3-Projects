/**
 @file users.h
 \brief Module responsible for the struct USERS
 */
#ifndef Users
#define Users

#include <glib.h>

#include "user.h"

/**
\brief Struct that holds multiple users information
*/
typedef struct users * USERS;

/**
\brief Function that initializes an users struct
 @return Users struct initialized
*/
USERS init_users_struct();

/**
\brief Function that add a new user to the users catalog
 @param users Struct with all the users information
 @param user New user to adds
*/
void add_user (USERS users, USER user);

/**
\brief Searches a user in the struct users using the user-id
 @param users Struct with all the users information
 @param user_id User-id of the user being searched for
 @return Corresponding user or NULL if there isn't one
*/
USER lookup_user (USERS users, char * user_id);

/**
 * @brief Checks if there's a certain user
 * @param users Users struct
 * @param user_id User-id
*/
int contains_user (USERS users, char * user_id);

/**
\brief Function that allows to know the number of users contained in the struct users
 @param users Struct users
 @return Number of users that exist in the struct
*/
long get_n_users(USERS users);

/**
\brief Defines the number of users that exist in the struct
 @param users Struct users
 @param n_users Number of users that exist in the struct
*/
void set_n_users(USERS users, long n_users);

/**
\brief Frees the users struct
 @param users Struct to be freed
*/
void free_users_struct (USERS users);

#endif
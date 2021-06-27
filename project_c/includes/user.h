/**
 @file user.h
 \brief Module where are defined functions that manipulate struct USER
 */
#ifndef User
#define User

/**
 * @brief Struct containing user information
*/
typedef struct user * USER;

/**
 * @brief Initializes a user
 * @return User initialized
*/
USER init_user ();

/**
 * @brief Validates a user
 * @param user User struct
 * @return 1 if it is a valid user, 0 if it isn't
*/
int validate_user (USER user);

/**
 * @brief Returns the user-id of one user
 * @param u User 
 * @return String containing the user-id
*/
char * get_user_id (USER u);

/**
 * @brief Sets an user-id to one user
 * @param u Pointer to an user 
 * @param new_id String cointaining the new user-id
*/
void set_user_id (USER * u, char * new_id);

/**
 * @brief Returns the user-name of one user
 * @param u User 
 * @return String containing the user-name
*/
char * get_user_name (USER u);

/**
 * @brief Sets an user-name to one user
 * @param u Pointer to an user 
 * @param new_id String cointaining the new user name
*/
void set_user_name (USER * u, char * new_name);

/**
 * @brief Returns the friend list of one user
 * @param u User 
 * @return String containing the friend list
*/
char * get_friends (USER u);

/**
 * @brief Sets a friend list to one user
 * @param u Pointer to an user 
 * @param new_id String cointaining the new friend list
*/
void set_friends (USER * u, char * friends);

/**
 * @brief Frees all memory used by struct user
 * @param u User 
*/
void free_user_struct (USER u);

#endif
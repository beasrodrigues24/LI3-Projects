/**
 @file review.h
 \brief Module where are defined functions that manipulate struct REVIEW
 */
#ifndef Review
#define Review

/*
 * @brief Struct containing review information
*/
typedef struct review * REVIEW;

/**
 * @brief Initializes a review
 * @return Review initialized
*/
REVIEW init_review();

/**
 * @brief Validates a date
 * @param date String containing date
 * @return 1 if it is a valid date, 0 if it isn't
*/
int validate_review_date(char * date);

/**
 * @brief Returns the review-id
 * @param r review
 * @returns String containing the review-id 
*/
char * get_review_id(REVIEW r);

/**
 * @brief sets a review-id to the review
 * @param r pointer to a review
 * @param new_id String containing the new review-id 
*/
void set_review_id(REVIEW * r, char * new_id);

/**
 * @brief Returns the user-id of one review
 * @param r review
 * @returns String containing the user-id 
*/
char * get_review_user_id(REVIEW r);

/**
 * @brief sets a user-id to the review
 * @param r pointer to a review
 * @param new_id String containing the new user-id 
*/
void set_review_user_id(REVIEW * r, char * new_id);

/**
 * @brief Returns the business-id of one review
 * @param r review
 * @returns String containing the business-id 
*/
char * get_review_business_id(REVIEW r);

/**
 * @brief sets a business-id to the review
 * @param r pointer to a review
 * @param new_id String containing the new business-id 
*/
void set_review_business_id(REVIEW * r, char * new_id);

/**
 * @brief Returns the stars of one review
 * @param r review
 * @returns number of stars of the review 
*/
float get_review_stars(REVIEW r);

/**
 * @brief sets a number of stars to the review
 * @param r pointer to a review
 * @param new_stars float containing the new review stars 
*/
void set_review_stars(REVIEW* r, float new_stars);

/**
 * @brief Returns the useful of one review
 * @param r review
 * @returns useful of the review 
*/
int get_review_useful(REVIEW r);

/**
 * @brief sets a useful to the review
 * @param r pointer to a review
 * @param new_useful int containing the new review useful 
*/
void set_review_useful(REVIEW * r, int new_useful);

/**
 * @brief Returns the funny of one review
 * @param r review
 * @returns funny of the review 
*/
int get_review_funny(REVIEW r);

/**
 * @brief sets a funny to the review
 * @param r pointer to a review
 * @param new_funny int containing the new review funny 
*/
void set_review_funny(REVIEW * r, int new_funny);

/**
 * @brief Returns the cool of one review
 * @param r review
 * @returns cool of the review
*/
int get_review_cool(REVIEW r);

/**
 * @brief sets a cool to the review
 * @param r pointer to a review
 * @param new_cool int containing the new review cool 
*/
void set_review_cool(REVIEW * r, int new_cool);

/**
 * @brief Returns the date of one review
 * @param r review
 * @returns String containing the review date 
*/
char * get_review_date(REVIEW r);

/**
 * @brief sets a date to the review
 * @param r pointer to a review
 * @param new_date String containing the new date 
*/
void set_review_date(REVIEW * r, char * new_date);

/**
 * @brief Returns the text of one review
 * @param r review
 * @returns String containing the review text 
*/
char * get_review_text(REVIEW r);

/**
 * @brief sets a text to the review
 * @param r pointer to a review
 * @param new_text String containing the new text 
*/
void set_review_text(REVIEW * r, char * new_text);

/**
 * @brief Frees all memory used by struct review
 * @param r review 
*/
void free_review_struct(REVIEW r);

#endif
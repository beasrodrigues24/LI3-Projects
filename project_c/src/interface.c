#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/users.h"
#include "../includes/macro.h"
#include "../includes/reviews.h"
#include "../includes/businesses.h"


USERS load_user_file (char * path) {

    FILE * f_user = fopen(path, "rb"); // Opening file with the users
    USERS users = NULL;
    long n_users = 0;

    if (f_user) {

        users = init_users_struct();
        char * buffer = malloc(LINE_SIZE);

        while (fgets(buffer, LINE_SIZE, f_user)) { // Reads one line

            char * user_id = strtok(buffer, ";");
            char * user_name = strtok(NULL, ";");
            char * friends = strtok(NULL, ";");

            // Initializes a user
            USER user = init_user();
            set_user_id(&user, user_id);
            set_user_name(&user, user_name);
            //set_friends(&user, friends);

            // If the user is valid, add it to the hashtables
            if (validate_user(user) && friends != NULL) {

                add_user(users, user);
                n_users++;

            }
            else free_user_struct(user); // If it isn't , free it
            
        }

        if (users) 
            set_n_users(users, n_users);
        

        free(buffer);
        
        fclose(f_user);

    }

    return users;        
}

BUSINESSES load_business_file (char * path) {
    
    FILE * f_business = fopen(path, "rb"); // Opening file with the businesses
    long n_businesses = 0;
    BUSINESSES businesses = NULL;

    if (f_business) {

        businesses = init_businesses_struct();
        char * buffer = malloc(LINE_SIZE); // Buffer to contain the line read

        while (fgets(buffer, LINE_SIZE, f_business)) {

            BUSINESS business = init_business();
            // Loading the line information to a business struct
            set_business_id(&business, strtok(buffer, ";"));
            set_business_name(&business, strtok(NULL, ";"));
            set_business_city(&business, strtok(NULL, ";"));
            set_business_state(&business, strtok(NULL, ";"));
            set_business_categories(&business, strtok(NULL, ";"));

            // if the business is valid add it to the hashtable
            if(validate_business(business)) {

                add_business(businesses, business);
                n_businesses++;

            }

            else free_business_struct(business); //if it isn't free it

        }
        
        if(businesses) 
            set_n_businesses(businesses, n_businesses);

        

        free(buffer);

        fclose(f_business);

    }

    return businesses;
}

REVIEWS load_review_file (char * path, BUSINESSES businesses, USERS users) {

    FILE * f_review = fopen(path, "rb"); // open file with the reviews

    int n_reviews = 0;
    REVIEWS reviews = NULL;

    if(f_review) {
        reviews = init_reviews_struct();
        char * buffer = malloc(LINE_SIZE); // Buffer to contain the line read

        while(fgets(buffer, LINE_SIZE, f_review)) {
            //loading the line information to a review struct
            REVIEW review = init_review();
            set_review_id(&review, strtok(buffer, ";"));
            set_review_user_id(&review, strtok(NULL, ";"));
            set_review_business_id(&review, strtok(NULL, ";"));
            set_review_stars(&review, atof(strtok(NULL, ";")));
            set_review_useful(&review, atoi(strtok(NULL, ";")));
            set_review_funny(&review, atoi(strtok(NULL, ";")));
            set_review_cool(&review, atoi(strtok(NULL, ";")));
            set_review_date(&review, strtok(NULL, ";"));
            set_review_text(&review, strtok(NULL, ";"));

            //if the review is valid add it to the hashtable
            if(validate_review(review, users, businesses)) {

                add_review(reviews, review);
                n_reviews++;
            
            }
            else free_review_struct(review); //if it isn't free it
            
            
        }

        if(reviews) set_n_reviews(reviews, n_reviews);
        
        free(buffer);
        fclose(f_review);
    }

    return reviews;

}

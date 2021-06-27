#include <stdlib.h>
#include <string.h>

#include "../includes/macro.h"
#include "../includes/business.h"


struct business {

    char* business_id;
    char* name;
    char* city;
    char* state;
    char* categories;

};


BUSINESS init_business () {

    BUSINESS business = malloc(sizeof(struct business));
    
    return business;

}

int validate_business (BUSINESS business) {

    char * business_id = get_business_id(business);
    char * business_name = get_business_name(business);
    char * business_city = get_business_city(business);
    char * business_state = get_business_state(business);
    char * business_categories = get_business_categories(business);

    int r = strlen(business_id) == ID_SIZE 
            && business_name != NULL
            && business_city != NULL
            && business_state != NULL
            && business_categories != NULL;

    free(business_id);
    free(business_name);
    free(business_city);
    free(business_state);
    free(business_categories);

    return r;

}

char * get_business_id (BUSINESS b) {

    return strdup(b->business_id);

}

void set_business_id (BUSINESS * b, char * new_id) {

    (*b)->business_id = strdup(new_id);

}

char * get_business_name (BUSINESS b) {

    return strdup(b->name);

}

void set_business_name (BUSINESS * b, char * new_name) {

    (*b)->name = strdup(new_name);

}

char * get_business_city (BUSINESS b) {

    return strdup(b->city);

}

void set_business_city (BUSINESS * b, char * new_city) {

    (*b)->city = strdup(new_city);

}

char * get_business_state (BUSINESS b) {
    
    return strdup(b->state);

}

void set_business_state (BUSINESS * b, char * new_state) {

    (*b)->state = strdup(new_state);

}

char * get_business_categories (BUSINESS b) {

    return strdup(b->categories);

}

void set_business_categories (BUSINESS * b, char * new_categories) {

    (*b)->categories = strdup(new_categories);

}

void free_business_struct (BUSINESS b) {

    free(b->business_id);
    free(b->name);
    free(b->city);
    free(b->state);
    free(b->categories);
    free(b);

}
#include <stdlib.h>
#include <string.h>

#include "../includes/macro.h"
#include "../includes/review.h"


typedef struct review {

    char* review_id;
    char* user_id;
    char* business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    char* date;
    char* text;

};

REVIEW init_review() {

    REVIEW r = malloc(sizeof(struct review));
    return r;
    
}

int validate_review_date(char * date) {

    int v = 0;

    if(strlen(date) == DATE_SIZE) {
        int year = atoi(strtok(date, "-"));
        int month = atoi(strtok(NULL, "-"));
        int day = atoi(strtok(NULL, " "));
        int hour = atoi(strtok(NULL, ":"));
        int minutes = atoi(strtok(NULL, ":"));
        int seconds = atoi(strtok(NULL, ";"));

        if(year <= 2021 && month <= 12 && month >= 1 && day <= 31 && day >= 1 
          && hour <= 24 && minutes <= 59 && seconds <= 59) {
              v = 1;
          }
    }

    return v; 

}

char * get_review_id(REVIEW r) {

    return strdup(r->review_id);

}

void set_review_id(REVIEW * r, char * new_id) {

    (*r)->review_id = strdup(new_id);

}

char * get_review_user_id(REVIEW r) {

    return strdup(r->user_id);

}

void set_review_user_id(REVIEW * r, char * new_id) {

    (*r)->user_id = strdup(new_id);

}

char * get_review_business_id(REVIEW r) {

    return strdup(r->business_id);

}

void set_review_business_id(REVIEW * r, char * new_id) {

    (*r)->business_id = strdup(new_id);

}

float get_review_stars(REVIEW r) {

    return r->stars;

}

void set_review_stars(REVIEW * r, float new_stars) {

    (*r)->stars = new_stars;

}

int get_review_useful(REVIEW r) {

    return r->useful;

}

void set_review_useful(REVIEW * r, int new_useful) {

    (*r)->useful = new_useful;

}

int get_review_funny(REVIEW r) {

    return r->funny;

}

void set_review_funny(REVIEW * r, int new_funny) {

    (*r)->funny = new_funny;

}

int get_review_cool(REVIEW r) {

    return r->cool;

}

void set_review_cool(REVIEW * r, int new_cool) {

    (*r)->cool = new_cool;

}

char * get_review_date(REVIEW r) {

    return strdup(r->date);

}

void set_review_date(REVIEW * r, char * new_date) {

    (*r)->date = strdup(new_date);

}

char * get_review_text(REVIEW r) {

    return strdup(r->text);

}

void set_review_text(REVIEW * r, char * new_text) {

    (*r)->text = strdup(new_text);

}

void free_review_struct(REVIEW r) {

    free(r->review_id);
    free(r->user_id);
    free(r->business_id);
    free(r->date);
    free(r->text);
    free(r);

}

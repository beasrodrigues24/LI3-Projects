#include <string.h>
#include <stdlib.h>

#include "../includes/stats.h"

struct business_stats {

    char * business_id;
    int n_reviews;
    float total_stars;

};

BUS_STATS init_bus_stats() {

    BUS_STATS new = malloc(sizeof(struct business_stats));
    new->business_id = NULL;
    new->n_reviews = 0;
    new->total_stars = 0;

    return new;

}

char * get_id_bus_stats(BUS_STATS bs) {

    return strdup(bs->business_id);

}

void set_id_bus_stats(BUS_STATS * bs, char * business_id) {

    (*bs)->business_id = strdup(business_id);

}

int get_n_review_bus_stats(BUS_STATS bs) {

    return bs->n_reviews;

}

void set_review_bus_stats(BUS_STATS * bs, int n_rev) {

    (*bs)->n_reviews = n_rev;

}

void add_review_bus_stats(BUS_STATS * bs) {

    (*bs)->n_reviews++;

}

int get_stars_bus_stats(BUS_STATS bs) {

    return bs->total_stars;

}

void add_stars_bus_stats(BUS_STATS * bs, float stars) {

    (*bs)->total_stars += stars;

}

BUS_STATS clone_bus_stats(BUS_STATS bs) {

    char * id = get_id_bus_stats(bs);
    int n_rev = get_n_review_bus_stats(bs);
    float stars = get_stars_bus_stats(bs);

    BUS_STATS new = init_bus_stats();
    set_id_bus_stats(&new, id);
    set_review_bus_stats(&new, n_rev);
    add_stars_bus_stats(&new, stars);

    free(id);

    return new;

}

void free_bus_stats(BUS_STATS bs) {

    free(bs->business_id);
    free(bs);

}

struct user_visits_info {

    char * user_id;
    int n_cities;
    char * city_visited;

};

USER_VISITS init_user_visits() {

    USER_VISITS new = malloc(sizeof(struct user_visits_info));
    new->user_id = NULL;
    new->n_cities = 0;
    new->city_visited = NULL;

    return new;

}

char * get_id_user_visits(USER_VISITS us) {

    return us ? strdup(us->user_id) : NULL;

}

void set_id_user_visits(USER_VISITS * us, char * user_id) {

    (*us)->user_id = strdup(user_id);

}

int get_n_cities_user(USER_VISITS us) {

    return us ? us->n_cities : 0;

}

void add_n_city_to_user(USER_VISITS * us) {

    (*us)->n_cities++;

}

char * get_city_visited(USER_VISITS us) {

    return us ? strdup(us->city_visited) : NULL;

}

void set_city_visited(USER_VISITS * us, char * city) {

    (*us)->city_visited = strdup(city);

}

void free_user_visits(USER_VISITS us) {

    free(us->user_id);
    free(us->city_visited);
    free(us);

}
#include <stdlib.h>

#include "../includes/users.h"


typedef struct users {

    GHashTable * user_table;
    long n_users;

};

USERS init_users_struct() {

    USERS users = malloc(sizeof(struct users));
    users->user_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_user_struct); 

    return users;
}

void add_user (USERS users, USER new_user) {

    g_hash_table_insert(users->user_table, get_user_id(new_user), new_user);

}

USER lookup_user (USERS users, char * user_id) {

    return g_hash_table_lookup(users->user_table, user_id);

}

int contains_user (USERS users, char * user_id) {

    return g_hash_table_contains(users->user_table, user_id);

}

long get_n_users(USERS users) {

    return users->n_users;

}

void set_n_users(USERS users, long n_users) {

    users->n_users = n_users;

}

void free_users_struct (USERS users) {
    
    g_hash_table_destroy(users->user_table);
    free(users);

}
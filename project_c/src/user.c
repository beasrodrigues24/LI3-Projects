#include <stdlib.h>
#include <string.h>

#include "../includes/user.h"
#include "../includes/macro.h"


struct user {

    char* user_id;
    char* name;
    char* friends;

};


USER init_user () {

    USER u = malloc(sizeof(struct user));
    return u;

}

int validate_user (USER user) {
  
    char * user_id = get_user_id(user);
    char * user_name = get_user_name(user);

    int r = strlen(user_id) == ID_SIZE && user_name != NULL;

    free(user_id);
    free(user_name);

    return r;

}


char * get_user_id (USER u) {

    return strdup(u->user_id);

}

void set_user_id (USER * u, char * new_id) {

    (*u)->user_id = strdup(new_id);

}

char * get_user_name (USER u) {

    return strdup(u->name);

}

void set_user_name (USER * u, char * new_name) {

    (*u)->name = strdup(new_name);

}

char * get_friends (USER u) {

    return strdup(u->friends);

}

void set_friends (USER * u, char * friends) {

    (*u)->friends = strdup(friends);

}

void free_user_struct (USER u) {
    
    free(u->user_id);
    free(u->name);
    //free(u->friends);
    free(u);

}
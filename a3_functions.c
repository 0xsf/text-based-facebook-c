#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a3_nodes.h"
#include "a3_functions.h"



void print_menu() {
    printf("***********************************************\n");
    printf("                 MAIN MENU:\n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("3. Manage a user's posts (add/remove)\n");
    printf("4. Manage a user's friends (add/remove)\n");
    printf("5. Display a user's posts\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/

user_t *add_user(user_t *users, const char *username, const char *password) {
    // setting a new node for the user and initializing its data
    user_t *newuser = malloc(sizeof(user_t));
    assert(newuser !=NULL);
    strcpy(newuser->username , username);
    strcpy(newuser->password, password);
    newuser->friends = NULL;
    newuser->posts = NULL;
    newuser->next = NULL;

    // comparing down below alphabetically < 0

    if (users == NULL || strcmp(username, users->username) < 0) {
        newuser->next = users;
        return newuser;
    }

    user_t *curr = users;
    while (curr->next != NULL && strcmp(curr->next->username, username) < 0) {
        curr = curr->next;
    }

    newuser->next = curr->next;
    curr->next = newuser;

    return users;

}



user_t *find_user(user_t *users, const char *username) {

    user_t *curr = users;
    while (curr != NULL) {

        if (strcmp(curr->username , username ) == 0 ) {
            return curr;
        }
        curr = curr->next;

    }
    return NULL;

}



friend_t *create_friend(const char *username) {

    friend_t *newfriend = malloc(sizeof(friend_t));
    assert(newfriend !=NULL);
    strcpy(newfriend->username , username);
    newfriend->next = NULL;
    return newfriend;
}



void add_friend(user_t *user, const char *friend) {



    friend_t *newfriend = create_friend(friend);

    if (user->friends == NULL || strcmp(friend, user->friends->username) < 0) {
        newfriend->next = user->friends;
        user->friends = newfriend;
        return;
    }

    friend_t *curr = user->friends;
    while (curr->next != NULL && strcmp(curr->next->username, friend) < 0) {
        curr = curr->next;
    }

    newfriend->next = curr->next;
    curr->next = newfriend;
}
    
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


_Bool delete_friend(user_t *user, char *friend_name) {

    friend_t *curr = user->friends;
    friend_t *prev = NULL;


    if (curr == NULL)
        return false;


    if (strcmp(curr->username, friend_name) == 0) {
        user->friends = curr->next;
        free(curr);
        return true;
    }


    while (curr != NULL && strcmp(curr->username, friend_name) != 0) {
        prev = curr;
        curr = curr->next;
    }


    if (curr == NULL)
        return false;


    prev->next = curr->next;
    free(curr);
    return true;
}
    




post_t *create_post(const char *text) {

    post_t *newpost = malloc(sizeof(post_t));
    assert(newpost != NULL);

    strcpy(newpost->content, text);
    newpost->next = NULL;

    return newpost;
}



void add_post(user_t *user, const char *text) {

    post_t *newpost = create_post(text);
    newpost->next = user->posts;
    user->posts = newpost;
}



_Bool delete_post(user_t *user) {


    if (user->posts == NULL)
        return false;


    post_t *todelete = user->posts;
    user->posts = user->posts->next;
    free(todelete);

    return true;
}


void display_all_user_posts(user_t *user) {

    post_t *curr = user->posts;

    while (curr != NULL) {
        printf("%s\n", curr->content);
        curr = curr->next;
    }
}



void display_user_friends(user_t *user) {

    friend_t *curr = user->friends;

    while (curr != NULL) {
        printf("%s\n", curr->username);
        curr = curr->next;
    }
}



void display_posts_by_n(user_t *users, int number) {

    post_t *curr = users->posts;
    char choice;

    while (curr != NULL) {


        for (int i = 0; i < number && curr != NULL; i++) {
            printf("%s\n", curr->content);
            curr = curr->next;
        }


        if (curr == NULL)
            return;


        printf("Display more posts? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N')
            return;
    }
}


void teardown(user_t *users) {

    user_t *curr_user = users;

    while (curr_user != NULL) {


        post_t *p = curr_user->posts;
        while (p != NULL) {
            post_t *temp_p = p;
            p = p->next;
            free(temp_p);
        }


        friend_t *f = curr_user->friends;
        while (f != NULL) {
            friend_t *temp_f = f;
            f = f->next;
            free(temp_f);
        }

        user_t *temp_user = curr_user;
        curr_user = curr_user->next;
        free(temp_user);
    }
}






user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

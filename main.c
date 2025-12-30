#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a3_nodes.h"
#include "a3_functions.h"
#include <ctype.h>


int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }

    user_t *users = read_CSV_and_create_users(csv_file, 50);
    fclose(csv_file);

    int choice;
    char username[50], password[50], friendname[50], posttext[300];
    user_t *user = NULL;

    printf("Welcome to the User Management System!\n");

    while (1)
    {
        print_menu();
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter a username: ");
            scanf("%s", username);
            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            if (find_user(users, username) != NULL)
            {
                printf("User already exists. Try another username.\n");
                continue;
            }

            printf("Enter a password (min 8 chars): ");
            scanf("%s", password);
            while (strlen(password) < 8)
            {
                printf("Password too short. Enter again: ");
                scanf("%s", password);
            }

            users = add_user(users, username, password);
            printf("**** User Added! ****\n");
        }
        else if (choice == 2)
        {
            printf("Enter username: ");
            scanf("%s", username);
            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user = find_user(users, username);
            if (user == NULL)
            {
                printf("Invalid user.\n");
                continue;
            }

            char oldpass[50];
            printf("Enter old password: ");
            scanf("%s", oldpass);

            if (strcmp(oldpass, user->password) != 0)
            {
                printf("Incorrect password.\n");
                continue;
            }

            printf("Enter new password (min 8 chars): ");
            scanf("%s", password);
            while (strlen(password) < 8)
            {
                printf("Password too short. Enter again: ");
                scanf("%s", password);
            }

            strcpy(user->password, password);
            printf("**** Password changed! ****\n");
        }
        else if (choice == 3)
        {
            printf("Enter username: ");
            scanf("%s", username);
            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user = find_user(users, username);
            if (user == NULL)
            {
                printf("Invalid user.\n");
                continue;
            }

            int postchoice = 0;

            while (postchoice != 3)
            {
                printf("--------------------------------------------------\n");
                printf("Managing %s's posts\n", username);
                printf("--------------------------------------------------\n");

                if (user->posts == NULL)
                    printf("Note: No posts available for %s\n", username);

                printf("1. Add a new post\n");
                printf("2. Remove a post\n");
                printf("3. Return to main menu\n");
                printf("Enter your choice: ");
                scanf("%d", &postchoice);

                if (postchoice == 1)
                {
                    printf("Enter your post content: ");
                    getchar();
                    fgets(posttext, sizeof(posttext), stdin);
                    posttext[strcspn(posttext, "\n")] = 0;

                    add_post(user, posttext);

                    printf("--------------------------------------------------\n");
                    printf("%s's posts:\n", username);
                    display_all_user_posts(user);
                    printf("--------------------------------------------------\n");
                }
                else if (postchoice == 2)
                {
                    if (delete_post(user))
                    {
                        printf("Post deleted.\n");
                        display_all_user_posts(user);
                    }
                    else
                    {
                        printf("No posts to delete.\n");
                    }
                }
            }
        }
        else if (choice == 4)
        {
            printf("Enter username: ");
            scanf("%s", username);
            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user = find_user(users, username);
            if (user == NULL)
            {
                printf("Invalid user.\n");
                continue;
            }

            int friendchoice = 0;

            while (friendchoice != 3)
            {
                printf("--------------------------------------------------\n");
                printf("Managing %s's friends\n", username);
                printf("--------------------------------------------------\n");
                printf("1. Add a new friend\n");
                printf("2. Remove a friend\n");
                printf("3. Return to main menu\n");
                printf("Enter your choice: ");
                scanf("%d", &friendchoice);

                if (friendchoice == 1)
                {
                    printf("Enter friend's username: ");
                    scanf("%s", friendname);
                    for (int i = 0; friendname[i]; i++)
                        friendname[i] = tolower(friendname[i]);

                    add_friend(user, friendname);
                    printf("Friend added.\n");
                }
                else if (friendchoice == 2)
                {
                    printf("List of %s's friends:\n", username);
                    display_user_friends(user);

                    printf("Enter friend's name to delete: ");
                    scanf("%s", friendname);
                    for (int i = 0; friendname[i]; i++)
                        friendname[i] = tolower(friendname[i]);

                    if (delete_friend(user, friendname))
                    {
                        printf("Updated list:\n");
                        display_user_friends(user);
                    }
                    else
                    {
                        printf("Friend not found.\n");
                    }
                }
            }
        }
        else if (choice == 5)
        {
            printf("Enter username: ");
            scanf("%s", username);
            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user = find_user(users, username);
            if (user == NULL)
            {
                printf("Invalid user.\n");
                continue;
            }

            display_posts_by_n(user, 3);
        }
        else if (choice == 6)
        {
            printf("Bye.. Cleaning up\n");
            teardown(users);
            return 0;
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    teardown(users);
    return 0;
}
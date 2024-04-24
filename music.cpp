#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a node in the circular linked list
struct Node {
    char musicName[50];
    struct Node* next;
};

// Function prototypes
void insertNode(struct Node** head_ref, char music[]);
void insertSong(struct Node** head_ref, char music[]);
void deleteSong(struct Node** head_ref, char music[]);
void printSongs(struct Node* head, int start);

int main() {
    struct Node* head = NULL;

    int choice;
    char newSong[50], songToDelete[50];
    int startSong;

    // 15 Bollywood songs
    char musicNames[15][50] = {
        "Tum Hi Ho",
        "Chaiyya Chaiyya",
        "Gerua",
        "Mere Sapno Ki Rani",
        "Dil Diyan Gallan",
        "Tere Bina",
        "Kabhi Kabhi Aditi",
        "Ae Dil Hai Mushkil",
        "Jai Ho",
        "Tujhe Dekha Toh",
        "Kabira",
        "Kal Ho Naa Ho",
        "Naina Da Kya Kasoor",
        "Mere Haath Mein",
        "Raabta"
    };

    // Inserting music names into the circular linked list
    for (int i = 0; i < 15; i++) {
        insertNode(&head, musicNames[i]);
    }

    do {
        printf("\nCircular Linked List Operations Menu\n");
        printf("1. Insert a new song\n");
        printf("2. Delete a song\n");
        printf("3. Print the list of songs\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Clear input buffer
        while(getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter the name of the new song to insert: ");
                fgets(newSong, sizeof(newSong), stdin);
                newSong[strcspn(newSong, "\n")] = '\0'; // remove newline character if present
                insertSong(&head, newSong);
                break;
            case 2:
                printf("Enter the name of the song to delete: ");
                fgets(songToDelete, sizeof(songToDelete), stdin);
                songToDelete[strcspn(songToDelete, "\n")] = '\0'; // remove newline character if present
                deleteSong(&head, songToDelete);
                break;
            case 3:
                printf("Enter the starting song number (1-15): ");
                scanf("%d", &startSong);

                // Clear input buffer
                while(getchar() != '\n');

                printSongs(head, startSong);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to insert a node at the end of the circular linked list
void insertNode(struct Node** head_ref, char music[]) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    strcpy(new_node->musicName, music);
    new_node->next = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = *head_ref;
    } else {
        while (last->next != *head_ref) {
            last = last->next;
        }
        last->next = new_node;
    }
    printf("Song \"%s\" added successfully.\n", music);
}

// Function to insert a song at the end of the circular linked list
void insertSong(struct Node** head_ref, char music[]) {
    insertNode(head_ref, music);
}

// Function to delete a song from the circular linked list
void deleteSong(struct Node** head_ref, char music[]) {
    if (*head_ref == NULL) {
        printf("List is empty. No songs to delete.\n");
        return;
    }

    struct Node* current = *head_ref;
    struct Node* prev = NULL;

    // If the head node itself holds the song to be deleted
    if (strcmp(current->musicName, music) == 0) {
        while (current->next != *head_ref) {
            current = current->next;
        }
        current->next = (*head_ref)->next;
        free(*head_ref);
        *head_ref = current->next;
        printf("Song \"%s\" deleted successfully.\n", music);
        return;
    }

    // Search for the song to be deleted
    while (current->next != *head_ref) {
        if (strcmp(current->musicName, music) == 0) {
            prev->next = current->next;
            free(current);
            printf("Song \"%s\" deleted successfully.\n", music);
            return;
        }
        prev = current;
        current = current->next;
    }

    // Check if last node holds the song to be deleted
    if (strcmp(current->musicName, music) == 0) {
        prev->next = current->next;
        free(current);
        printf("Song \"%s\" deleted successfully.\n", music);
        return;
    }

    printf("Song \"%s\" not found in the list.\n", music);
}

// Function to print songs starting from a specified number
void printSongs(struct Node* head, int start) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* current = head;
    int count = 1;

    printf("Songs:\n");
    do {
        if (count >= start) {
            printf("%s\n", current->musicName);
        }
        current = current->next;
        count++;
    } while (current != head);
}

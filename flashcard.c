#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

struct Flashcard {
    char question[MAX];
    char answer[MAX];
};

void add_flashcard() {
    FILE *fp = fopen("flashcards.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Flashcard card;
    getchar(); 
    printf("Enter the question: ");
    fgets(card.question, MAX, stdin);
    printf("Enter the answer: ");
    fgets(card.answer, MAX, stdin);

    card.question[strcspn(card.question, "\n")] = 0;
    card.answer[strcspn(card.answer, "\n")] = 0;

    fprintf(fp, "%s\n%s\n", card.question, card.answer);
    fclose(fp);

    printf("Flashcard added successfully!\n");
}

void view_flashcards() {
    FILE *fp = fopen("flashcards.txt", "r");
    if (fp == NULL) {
        printf("No flashcards found.\n");
        return;
    }

    struct Flashcard card;
    int count = 0;
    while (fgets(card.question, MAX, fp) && fgets(card.answer, MAX, fp)) {
       
        card.question[strcspn(card.question, "\n")] = 0;
        card.answer[strcspn(card.answer, "\n")] = 0;

        printf("\nQ%d: %s\nPress Enter to show answer...", ++count, card.question);
        getchar(); 
        printf("A%d: %s\n", count, card.answer);
    }

    fclose(fp);

    if (count == 0)
        printf("No flashcards to show.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n Flashcard Learning Tool\n");
        printf("1. Add Flashcard\n");
        printf("2. View Flashcards\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_flashcard(); break;
            case 2:
                getchar(); 
                view_flashcards(); break;
            case 3: printf("Goodbye!\n"); exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

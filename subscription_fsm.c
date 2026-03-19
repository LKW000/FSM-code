#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1) Define our States and Events using Enums
typedef enum {
    BROWSING,
    TRIAL_STARTED,
    PAYMENT_SETUP,
    SUBSCRIBED,
    CANCELED
} State;

typedef enum {
    START_TRIAL,
    ADD_PAYMENT,
    CONFIRM,
    CANCEL,
    QUIT,
    INVALID
} Event;


Event stringToEvent(char* str) {
    if (strcmp(str, "start_trial") == 0) return START_TRIAL;
    if (strcmp(str, "add_payment") == 0) return ADD_PAYMENT;
    if (strcmp(str, "confirm") == 0) return CONFIRM;
    if (strcmp(str, "cancel") == 0) return CANCEL;
    if (strcmp(str, "quit") == 0) return QUIT;
    return INVALID;
}


void printState(State s) {
    switch (s) {
        case BROWSING:      printf("state = BROWSING\n"); break;
        case TRIAL_STARTED: printf("state = TRIAL_STARTED\n"); break;
        case PAYMENT_SETUP: printf("state = PAYMENT_SETUP\n"); break;
        case SUBSCRIBED:    printf("state = SUBSCRIBED\n"); break;
        case CANCELED:      printf("state = CANCELED\n"); break;
    }
}

int main() {
    State currentState = BROWSING;
    char input[50];
    bool running = true;

    printf("--- Subscription FSM Loaded ---\n");
    printState(currentState);

    while (running) {
        printf("> event: ");
        scanf("%s", input);
        Event event = stringToEvent(input);

        if (event == QUIT) {
            running = false;
            break;
        }

        // 4) The FSM Logic: Switch (State) -> Switch (Event)
        switch (currentState) {
            case BROWSING:
                if (event == START_TRIAL) currentState = TRIAL_STARTED;
                else if (event == CANCEL) currentState = CANCELED;
                break;

            case TRIAL_STARTED:
                if (event == ADD_PAYMENT) currentState = PAYMENT_SETUP;
                else if (event == CANCEL) currentState = CANCELED;
                break;

            case PAYMENT_SETUP:
                if (event == CONFIRM) currentState = SUBSCRIBED;
                else if (event == CANCEL) currentState = CANCELED;
                break;

            case SUBSCRIBED:
                if (event == CANCEL) currentState = CANCELED;
                break;

            case CANCELED:
                // Once canceled, the flow ends or stays canceled.
                break;
        }

        // 5) Print state after every event
        printState(currentState);
        
        if (currentState == CANCELED) {
            printf("Process ended.\n");
            running = false;
        }
    }

    return 0;
}
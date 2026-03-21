#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

struct guardd {
    int guard_id;
    bool is_active;
    char patrol_point[30];
    char shift[6];
};

void delete_guard(struct guardd guard[], int *size, int id) {
    int idx = -1;
    for (int i = 0; i < *size; i++) {
        if (guard[i].guard_id == id) {
            idx = i;
            break;
        }
    }
    if (idx < 0) {
        printf("Guard with ID %d not found.\n", id);
        return;
    }
    for (int j = idx; j < *size - 1; j++) {
        guard[j] = guard[j + 1];
    }
    (*size)--;
    printf("Guard with ID %d deleted.\n", id);
}

void guard(void) {
    struct guardd guard[20];
    int input = 0;
    int size = 0;

menu:
    printf("You're in security panel. What do you want to do?\n");
    printf("Enter details of a new guard -> 1\n");
    printf("Update guard details -> 2\n");
    printf("Delete a guard -> 3\n");
    printf("View all guard details -> 4\n");
    printf("Exit -> -1\n");
    scanf("%d", &input);

    switch (input) {
    case 1:
        add_guard(guard, &size);
        goto menu;
    case 2:
        update_guard(guard, size);
        goto menu;
    case 3:
        printf("Enter guard ID to delete: ");
        scanf("%d", &input);
        delete_guard(guard, &size, input);
        goto menu;
    case 4:
        display_guard(guard, size);
        goto menu;
    case -1:
        break;
    default:
        printf("Invalid input. Please try again.\n");
        Sleep(500);
        goto menu;
    }
}

// Function to add a new guard
void add_guard(struct guardd guard[], int *size) {
    printf("Enter guard ID: ");
    scanf("%d", &guard[*size].guard_id);
    printf("Enter active status (0-> not active, 1-> active): ");
    scanf("%d", (int*)&guard[*size].is_active);
    printf("Enter the patrol point: ");
    scanf("%29s", guard[*size].patrol_point);
    printf("Enter the shift time: ");
    scanf("%5s", guard[*size].shift);
    (*size)++;
    printf("Guard details saved successfully.\n");
}

// Function to update an existing guard
void update_guard(struct guardd guard[], int size) {
    int input;
    printf("Enter the guard ID to update: ");
    scanf("%d", &input);
    for (int i = 0; i < size; i++) {
        if (guard[i].guard_id == input) {
            int field = 0;
            printf("Update which detail?\n");
            printf("1 - active status\n");
            printf("2 - patrol point\n");
            printf("3 - shift time\n");
            printf("4 - all\n");
            scanf("%d", &field);
            switch (field) {
            case 1:
                printf("Enter new active status (0->not active, 1->active): ");
                scanf("%d", (int*)&guard[i].is_active);
                break;
            case 2:
                printf("Enter new patrol point: ");
                scanf("%29s", guard[i].patrol_point);
                break;
            case 3:
                printf("Enter new shift time: ");
                scanf("%5s", guard[i].shift);
                break;
            case 4:
                printf("Enter new active status (0->not active, 1->active): ");
                scanf("%d", (int*)&guard[i].is_active);
                printf("Enter new patrol point: ");
                scanf("%29s", guard[i].patrol_point);
                printf("Enter new shift time: ");
                scanf("%5s", guard[i].shift);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Guard details updated successfully.\n");
            return;  // Exit after updating
        }
    }
    printf("Guard with ID %d not found.\n", input);  // If not found
}

// Function to display all guards
void display_guard(struct guardd guard[], int size) {
    if (size == 0) {
        printf("No guards registered yet.\n");
    } else {
        printf("Guard details:\n");
        for (int i = 0; i < size; i++) {
            printf("ID: %d, Active: %s, Patrol: %s, Shift: %s\n",
                guard[i].guard_id,
                guard[i].is_active ? "Yes" : "No",
                guard[i].patrol_point,
                guard[i].shift);
        }
    }
}

int main(void) {
    guard();
    return 0;
}

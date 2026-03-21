#include "factory.h"

WarehouseItem *warehouse_head = NULL;

// Function to add a new item to the warehouse
void add_warehouse_item(int slot, char *mat, float stock)
{
    WarehouseItem *newNode = (WarehouseItem *)malloc(sizeof(WarehouseItem));
    newNode->slot_no = slot;
    strcpy(newNode->material_type, mat);
    newNode->stock_kg = stock;
    newNode->next = warehouse_head;
    newNode->prev = NULL;

    if (warehouse_head != NULL)
    {
        warehouse_head->prev = newNode;
    }
    warehouse_head = newNode;
    printf("Item added successfully to slot %d.\n", slot);
}

// Function to update stock in a specific slot
void update_warehouse_item(int slot, float new_stock)
{
    WarehouseItem *curr = warehouse_head;
    while (curr != NULL)
    {
        if (curr->slot_no == slot)
        {
            curr->stock_kg = new_stock;
            printf("Stock in slot %d updated to %.2f kg.\n", slot, new_stock);
            return;
        }
        curr = curr->next;
    }
    printf("Error: Slot %d not found.\n", slot);
}

// Function to delete an item from a specific slot
void delete_warehouse_item(int slot)
{
    WarehouseItem *curr = warehouse_head;
    while (curr != NULL)
    {
        if (curr->slot_no == slot)
        {
            if (curr->prev != NULL)
            {
                curr->prev->next = curr->next;
            }
            else
            {
                warehouse_head = curr->next;
            }
            if (curr->next != NULL)
            {
                curr->next->prev = curr->prev;
            }
            free(curr);
            printf("Slot %d deleted successfully.\n", slot);
            return;
        }
        curr = curr->next;
    }
    printf("Error: Slot %d not found.\n", slot);
}

// Function to display all warehouse items
void display_warehouse()
{
    WarehouseItem *curr = warehouse_head;
    if (curr == NULL)
    {
        printf("Warehouse is empty.\n");
        return;
    }
    printf("\n--- Main Warehouse Inventory (Doubly Linked List) ---\n");
    while (curr != NULL)
    {
        printf("Slot No: %d | Material: %s | Stock: %.2f kg\n",
               curr->slot_no, curr->material_type, curr->stock_kg);
        curr = curr->next;
    }
    printf("----------------------------------------------------\n");
}

// Function to search for an item in the warehouse
void search_warehouse_item(char *query)
{
    WarehouseItem *curr = warehouse_head;
    int found = 0;
    while (curr != NULL)
    {
        // Search by slot number (as string) or material type
        char slot_str[20];
        sprintf(slot_str, "%d", curr->slot_no);

        if (strstr(curr->material_type, query) != NULL || strcmp(slot_str, query) == 0)
        {
            if (!found)
            {
                printf("\n--- Search Results ---\n");
                found = 1;
            }
            printf("Slot No: %d | Material: %s | Stock: %.2f kg\n",
                   curr->slot_no, curr->material_type, curr->stock_kg);
        }
        curr = curr->next;
    }
    if (!found)
    {
        printf("No items found matching '%s'.\n", query);
    }
    else
    {
        printf("----------------------\n");
    }
}

// Function to sort warehouse items
void sort_warehouse_items(int criteria, int order)
{
    // Criteria: 1-Slot No, 2-Material Type, 3-Stock
    // Order: 1-Ascending, 2-Descending

    if (warehouse_head == NULL || warehouse_head->next == NULL)
    {
        return; // Empty or single item list, already "sorted"
    }

    int swapped;
    WarehouseItem *ptr1;
    WarehouseItem *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = warehouse_head;

        while (ptr1->next != lptr)
        {
            int compare = 0;
            switch (criteria)
            {
            case 1: // Slot No
                if (order == 1)
                    compare = (ptr1->slot_no > ptr1->next->slot_no);
                else
                    compare = (ptr1->slot_no < ptr1->next->slot_no);
                break;
            case 2: // Material Type
                if (order == 1)
                    compare = (strcmp(ptr1->material_type, ptr1->next->material_type) > 0);
                else
                    compare = (strcmp(ptr1->material_type, ptr1->next->material_type) < 0);
                break;
            case 3: // Stock
                if (order == 1)
                    compare = (ptr1->stock_kg > ptr1->next->stock_kg);
                else
                    compare = (ptr1->stock_kg < ptr1->next->stock_kg);
                break;
            }

            if (compare)
            {
                // Swap data instead of nodes for simplicity in this case
                int temp_slot = ptr1->slot_no;
                char temp_mat[30];
                strcpy(temp_mat, ptr1->material_type);
                float temp_stock = ptr1->stock_kg;

                ptr1->slot_no = ptr1->next->slot_no;
                strcpy(ptr1->material_type, ptr1->next->material_type);
                ptr1->stock_kg = ptr1->next->stock_kg;

                ptr1->next->slot_no = temp_slot;
                strcpy(ptr1->next->material_type, temp_mat);
                ptr1->next->stock_kg = temp_stock;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Warehouse list sorted successfully.\n");
}

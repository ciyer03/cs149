/**
 * Description: 7.6 LAB*: Program: Online shopping cart (Part 1)
 *              main.c - main() function
 * Author names: Chandramouli Iyer and Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu and safiullah.saif@sjsu.edu
 * Last modified date: 11/13/2023
 * Creation date: 11/13/2023
 **/

#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

int main(void) {

    ItemToPurchase item1, item2;

    makeItemBlank(&item1);
    makeItemBlank(&item2);

    printf("Item 1\n");
    printf("Enter the item name:\n");
    if (fgets(item1.itemName, MAX_ITEM_NAME_SIZE, stdin) == NULL) {
        printf("Reading input failed.\n");
        return 1;
    }

    printf("\nEnter the item price:\n");
    if (scanf("%d", &(item1.itemPrice)) == EOF) {
        printf("Reading input failed.\n");
        return 1;
    }

    printf("\nEnter the item quantity:\n");
    if (scanf("%d", &(item1.itemQuantity)) == EOF) {
        printf("Reading input failed.\n");
        return 1;
    }

    char c = getchar();
    while (c != '\n' && c != EOF) {
       c = getchar();
    }

    printf("\nItem 2\n");
    printf("Enter the item name:\n");
    if (fgets(item2.itemName, MAX_ITEM_NAME_SIZE, stdin) == NULL) {
        printf("Reading input failed.\n");
        return 1;
    }

    printf("\nEnter the item price:\n");
    if (scanf("%d", &(item2.itemPrice)) == EOF) {
        printf("Reading input failed.\n");
        return 1;
    }

    printf("\nEnter the item quantity:\n");
    if (scanf("%d", &(item2.itemQuantity)) == EOF) {
        printf("Reading input failed.\n");
        return 1;
    }

    item1.itemName[strlen(item1.itemName) - 1] = '\0';
    item2.itemName[strlen(item2.itemName) - 1] = '\0';

    printf("\nTOTAL COST\n");

    printItemCost(item1);
    printItemCost(item2);

    printf("Total: $%d\n", ((item1.itemQuantity * item1.itemPrice) + (item2.itemQuantity * item2.itemPrice)));
    
    return 0;
}

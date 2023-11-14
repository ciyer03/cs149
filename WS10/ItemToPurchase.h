/**
 * Description: 7.6 LAB*: Program: Online shopping cart (Part 1)
 *              ItemToPurchase.h - Struct definition and related function declarations
 * Author names: Chandramouli Iyer and Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu and safiullah.saif@sjsu.edu
 * Last modified date: 11/13/2023
 * Creation date: 11/13/2023
 **/

#define MAX_ITEM_NAME_SIZE 500

typedef struct ItemToPurchase {
    int itemPrice;
    int itemQuantity;
    char itemName[MAX_ITEM_NAME_SIZE];
} ItemToPurchase;

void makeItemBlank(ItemToPurchase *item);
void printItemCost(ItemToPurchase item);

/**
 * Description: Online shopping cart (Part 1)
 * Author names: Chandramouli Iyer, Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu and safiullah.saif@sjsu.edu
 * Last modified date: 11/13/2023
 * Creation date: 11/13/2023
 **/

#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

/**
* Sets all attributes of the passed in item to their starter values.
*
* Input: ItemToPurchase *item = THe pointer to item to be blanked.
**/
void makeItemBlank(ItemToPurchase *item) {
    strcpy(item->itemName, "none");
    item->itemPrice = 0;
    item->itemQuantity = 0;
}

/**
* Prints the name, quantity, individual price, and the total price based on the quantity and price.
*
* Input: item = The item whose values are to be printed.
**/
void printItemCost(ItemToPurchase item) {
    printf("%s %d @ $%d = $%d\n",
           item.itemName, item.itemQuantity, item.itemPrice, (item.itemQuantity * item.itemPrice));
}

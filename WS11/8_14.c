/**
 * Description: Used to create a Contact list for people along with their phone numbers.
 * Author names: Safiullah Saif and Chandramouli Iyer
 * Author emails: safiullah.saif@sjsu.edu and chandramouli.iyer@jsu.edu
 * Last modified date: 11/19/2023
 * Creation date: 11/19/2023
 **/

#include <stdio.h>
#include <string.h>

typedef struct ContactNode_struct
{
    /* Define ContactNode struct here. */

    char contactName[50];
    char contactPhoneNumber[50];
    struct ContactNode_struct *nextNodePtr;
} ContactNode;

/**
 * This function initializes the contact name and phone number, and set the next pointer of the node to null.
 * Input parameters: ContactNode node, name, phoneNumber
 * Returns: void
 **/
void InitializeContactNode(ContactNode *node, const char *name, const char *phoneNumber)
{
    strcpy(node->contactName, name);
    strcpy(node->contactPhoneNumber, phoneNumber);
    node->nextNodePtr = NULL;
}

/**
 * This function returns the node with the contact name from ContactNode.
 * Input parameters: ContactNode node
 * Returns: the contact name of ContactNode
 **/
const char *GetName(const ContactNode *node)
{
    return node->contactName;
}

/**
 * This function returns the node with the phone number from ContactNode.
 * Input parameters: ContactNode node
 * Returns: the phone number of ContactNode
 **/
const char *GetPhoneNumber(const ContactNode *node)
{
    return node->contactPhoneNumber;
}

/**
 * This function sets the new node and the pointer to the updated desired values.
 * Input parameters: ContactNode node, a new node
 * Returns: void
 **/
void InsertAfter(ContactNode *node, ContactNode *newNode)
{
    newNode->nextNodePtr = node->nextNodePtr;
    node->nextNodePtr = newNode;
}

/**
 * This function gets the next node.
 * Input parameters: ContactNode node
 * Returns: the next ContactNode
 **/
ContactNode *GetNext(const ContactNode *node)
{
    return node->nextNodePtr;
}

/**
 * This function prints out the person's information
 * Input parameters: ContactNode node, the nth person in the linked list
 * Returns: void
 **/
void PrintContactNode(const ContactNode *node, int personNumber)
{
    printf("Person %d: %s, %s\n", personNumber, GetName(node), GetPhoneNumber(node));
}

/**
 * This is the main function. this function takes input from the user, and uses the above functions to print out the desired output.
 **/
int main(void)
{
    ContactNode person1, person2, person3;

    // Input for person1
    printf("Enter name for Person 1: ");
    fgets(person1.contactName, sizeof(person1.contactName), stdin);
    person1.contactName[strcspn(person1.contactName, "\n")] = '\0'; // Remove newline character

    printf("Enter phone number for Person 1: ");
    scanf("%49s", person1.contactPhoneNumber); // Limit input to 49 characters to avoid overflow

    // Input for person2
    getchar(); // Consume the newline character
    printf("Enter name for Person 2: ");
    fgets(person2.contactName, sizeof(person2.contactName), stdin);
    person2.contactName[strcspn(person2.contactName, "\n")] = '\0'; // Remove newline character

    printf("Enter phone number for Person 2: ");
    scanf("%49s", person2.contactPhoneNumber); // Limit input to 49 characters to avoid overflow

    // Input for person3
    getchar(); // Consume the newline character
    printf("Enter name for Person 3: ");
    fgets(person3.contactName, sizeof(person3.contactName), stdin);
    person3.contactName[strcspn(person3.contactName, "\n")] = '\0'; // Remove newline character

    printf("Enter phone number for Person 3: ");
    scanf("%49s", person3.contactPhoneNumber); // Limit input to 49 characters to avoid overflow

    // Initialize contact nodes
    InitializeContactNode(&person1, person1.contactName, person1.contactPhoneNumber);
    InitializeContactNode(&person2, person2.contactName, person2.contactPhoneNumber);
    InitializeContactNode(&person3, person3.contactName, person3.contactPhoneNumber);

    // Build linked list
    InsertAfter(&person1, &person2);
    InsertAfter(&person2, &person3);

    // Output each contact
    PrintContactNode(&person1, 1);
    PrintContactNode(&person2, 2);
    PrintContactNode(&person3, 3);

    // Output linked list using a loop
    printf("\nCONTACT LIST\n");
    ContactNode *current = &person1;
    int personNumber = 1;

    while (current != NULL)
    {
        printf("\nName: %s\nPhone number: %s\n", GetName(current), GetPhoneNumber(current));
        current = GetNext(current);
        personNumber++;
    }

    return 0;
}

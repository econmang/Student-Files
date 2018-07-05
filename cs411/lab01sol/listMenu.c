/*
   listMenu.c: interactive test program for the list of items 
               data structure

   CS411 Lab 1 Solution
   Name: Kevin Sahr
   Date: 1/23/17
*/

#include "itemList.h"

// helper function
int getItemID (const char* prompt)
{
   int id;
   printf("%s: ", prompt);
   while (!scanf("%d", &id))
   {
      printf("ERROR: please enter an integer id: ");
      scanf("%*s");
   }

   return id;
}

int main (int argc, char* argv[])
{
   ItemList theList;
   initializeItemList(&theList);

   int again = 1;
   do {

      printf("\n** ITEM INVENTORY MENU **\n");
      printf("1. Add Item\n");
      printf("2. Remove Item\n");
      printf("3. Display Single Item\n");
      printf("4. Display Item List\n");
      printf("5. Quit\n");
      printf("* Enter your choice (1-5):  \n");

      int choice = -1;
      while (!scanf("%d", &choice))
      {
         scanf("%*s");
         printf("ERROR: please enter a number (1-5): \n");
      }

      switch (choice)
      {
         case 1: // add item 
         {
            int id;
            char name[MAX_ITEM_NAME_LEN + 1];
            float price;
            printf("Enter new item id, name, and price (without commas): ");
            if (scanf("%d %s %f", &id, name, &price) != 3)
            {
               printf("ERROR: invalid Item values.\n");
               exit(1);
            }

            Item* newItem = createItem(id, name, price);
            if (newItem)
            {
               if (insert(&theList, newItem))
                  destroyItem(&newItem);
            }

            break;
         }   
         case 2: // remove item
            delete(&theList, getItemID("Enter item id to remove"));
            break;

         case 3: /* display item */
         {
            int id = getItemID("Enter item id to display");
            Item* item = find(&theList, id);
            if (item)
               printItem(item);
            else
               printf("ERROR: Item ID %d not found.\n", id);

            break;
         }
         case 4: /* display list */
            printItemList(&theList);
            break;

         case 5: /* quit */
            printf("You have chosen QUIT\n");
            again = 0;
            break;

         default:
            printf("ERROR: only choices 1-5 are valid.\n");
            break;
      }

   } while (again);

   // we have a potential memory leak, since we have no function to
   // delete all of the items in the ItemList.

   return 0;
}


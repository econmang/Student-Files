/*
   itemList.c: functions for the list of items

   CS411 Lab 1 Solution
   Name: Kevin Sahr
   Date: 1/23/17
*/

#include "itemList.h"

// create and return an Item with the indicated values
Item* createItem(int id, const char* name, float price)
{
   // dynamically allocate the Item
   Item* newItem = malloc(sizeof(Item));
   if (!newItem)
      printf("ERROR: unable to allocate memory for Item.\n");
   else
   {
      // first make sure we have enough room to store the name 
      if (strlen(name) > MAX_ITEM_NAME_LEN)
      {
         printf("ERROR: Item name can not exceed %d characters.\n", 
                MAX_ITEM_NAME_LEN);
         destroyItem(&newItem); // will set newItem to NULL for return
      }
      else // fill-in the fields
      {
         newItem->id = id;
         strcpy(newItem->name, name);
         newItem->price = price;
      }
   }

   return newItem;
}

// output the item to stdout
void printItem(const Item* item)
{
   printf("ID: %d NAME: %s PRICE: $%.2f\n", item->id, item->name, 
          item->price);
}

// deallocate the Item indicated by the handle argument
void destroyItem(Item** item)
{
   free(*item);
   *item = NULL;
}

// sets all values in the ItemList to appropriate values
//   for a new empty item list.
// assumes the ItemList has never been previously used.
void initializeItemList(ItemList* items)
{
   items->numItems = 0;

   // this isn't really necessary for this lab, but a 
   // good habit in general
   int i;
   for (i = 0; i < MAX_ITEMS; i++)
      items->theItems[i] = NULL;
}

// output all items in the list to stdout, one-per-line
void printItemList(const ItemList* items)
{
   printf("THE CURRENT ITEM LIST:\n");
   int i;
   for (i = 0; i < items->numItems; i++)
      printItem(items->theItems[i]);
}

// insert theItem into the ItemList.
// return 0 if successful, 1 if unsuccessful.
// note that the ItemList should be ordered by Item ID
//   and that duplicates are not allowed.
int insert(ItemList* items, Item* theItem)
{
   // first check if there's room for another item
   if (items->numItems == MAX_ITEMS)
   {
      printf("ERROR: Unable to insert new Item; the Item List is full.\n");
      return 1;
   }

   // first find where the item goes
   int newNdx;
   for (newNdx = 0; newNdx < items->numItems; newNdx++)
   {
      if (items->theItems[newNdx]->id == theItem->id)
      {
         printf("ERROR: Unable to insert new Item; "
                "Item already exists in Item List\n");
         return 1;
      }
      else if (items->theItems[newNdx]->id > theItem->id)
         break;
   }

   // newNdx is now the index where we want to insert
   // shift the remaining items to the right
   int i;
   for (i = items->numItems - 1; i >= newNdx; i--)
      items->theItems[i + 1] = items->theItems[i]; 

   // now insert the new Item
   items->theItems[newNdx] = theItem;

   // update the number of items
   items->numItems++;

   return 0;
}

// find and return the Item with the specified id in list items.
//   returns a pointer to the Item or NULL if the Item is not found.
// must use a binary search
Item* find(ItemList* items, int id)
{
   int low = 0;
   int high = items->numItems - 1;

   while (low <= high)
   {
      int mid = (low + high) / 2;
      if (id == items->theItems[mid]->id)
         return items->theItems[mid];
      else if (id > items->theItems[mid]->id)
         low = mid + 1;
      else
         high = mid - 1;
   }

   return NULL;
}

// remove the Item with the specified id from list items
//   and deallocates the Item memory.
// if an Item with the specified id does not exist, do nothing.
void delete(ItemList* items, int id)
{
   // first find the item using linear search
   int found = 0;
   int i;
   for (i = 0; i < items->numItems; i++)
   {
      if (items->theItems[i]->id == id)
      {
         found = 1;
         break;
      }
      else if (items->theItems[i]->id > id)
         break; // item not found
   }

   if (found)
   {
      // remove the item
      destroyItem(&(items->theItems[i]));

      // shift remaining items to the left
      for (; i < items->numItems - 1; i++)
         items->theItems[i] = items->theItems[i + 1];

      // update the number of items
      items->numItems--;
   }
   else
      printf("ERROR: Item with ID %d does not exist.\n", id);
}


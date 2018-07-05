/*
	file: listDriver.c
	Created by: Evan Conley
	Date: 2/19/2017

	This is to test out different functionality in pieces
	I don't have an error, but something isn't working
	so I'm going to create Items/Nodes/ItemLists and work
	on them independently.
*/

#include "itemList.h"

int main(){
	Item* item = createItem(4,"tacos",2.12);

	if(item){
		printItem(item);
	}

	return 0;
}

/*
This is as far as my debugging had to go..
I left return NULL on createItem instead
of returning newItem. Everything works now,
and after hours of struggling with other functions,
I feel dumb, tired, but happy that it works haha.
*/
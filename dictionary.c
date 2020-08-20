#include "dictionary.h"
#include "balanced_tree_node.h"

enum PrimitiveType{__int, __float, __char, __bool};

Data* DataInitInt(int a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 1;
	variable->_int = a;
	// printf("saved %i\n", variable->_int);
	return variable;
}
Data* DataInitChar(char a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 2;
	variable->_char = a;
	return variable;
}

Data* DataInitFloat(float a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 3;
	variable->_float = a;
	return variable;

}
Data* DataInitBool(bool a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 4;
	variable->_bool = a;
	return variable;
}

void DataPrintData(Data* variable)
{
	// printf("here %i %i\n", variable->type_id, variable->_int);
	switch(variable->type_id)
	{
		case __int:
		{
			printf("%c", variable->_int);
			break;
		}
		case __float:
		{
			printf("%f", variable->_float);
			break;
		}
		case __char:
		{
			printf("%c", variable->_char);
			break;
		}
		case __bool:
		{
			printf("%i", variable->_bool);
			break;
		}
	}
	
}

enum ItemType{primitive, string, array, dictionary};

Item* ItemInitCollection(int type)
{
    if(type == primitive)
    {
        return NULL;
    }
    Item* my_item = (Item*) malloc(sizeof(Item));
    my_item->is_dictionary = type == dictionary? true: false;
    my_item->is_array = type == array? true: false;
    my_item->is_string = type == string? true: false;
    my_item->is_primitive = false;
    
    // this will be reset when the item as added to a vector
    my_item->id = 0;

    my_item->key_name = NULL;
    my_item->value = 0;

    if(type == dictionary || type == array || type == string)
    {
        my_item->children = VectorInitVector();
        if(type == dictionary)
        {
            BalancedTreeNode* empty_node = BalancedTreeNodeInit();
            VectorAppend(my_item->children, empty_node);

        }

    }

    my_item->primitive = NULL;

    return my_item;
}

// special method for just primitive
Item* ItemInitPrimitive(Data* primitive)
{
    Item* my_item = (Item*) malloc(sizeof(Item));

    my_item->is_dictionary = false;

    my_item->is_array = false;

    my_item->is_string = false;

    my_item->is_primitive = true;

    // this will be reset when the item as added to a vector
    my_item->id = 0;

    my_item->key_name = NULL;

    my_item->value = 0;

    my_item->children = NULL;

    my_item->primitive = primitive;

    return my_item;

}


Dictionary* DInit()
{
    Dictionary* my_dictionary = (Dictionary*) malloc(sizeof(Dictionary));

    my_dictionary->items = VectorInitVector();
    my_dictionary->start_item = -1;
    return my_dictionary;
}

Dictionary* DDictionaryFromString(char* my_string)
{

    /*
    x
        a, b, c, d, e
    a
    b
    c
    d
    e
    */
    Dictionary* my_container = DInit();

    Item* structure_item = ItemInitCollection(string);

    VectorAppend(my_container->items, structure_item);

    for(int i = 0; i < len(my_string); i++)
    {
        Item* my_int = ItemInitPrimitive(DataInitInt(my_string[i]));
        VectorAppend(structure_item->children, my_int);
        my_int->id = VectorGetPopulation(structure_item->children) - 1;

    }
    return my_container;
}

void DTransfer(Dictionary* my_array, Item* structure_item, Dictionary* my_container)
{
    // transfter the contents of my_array to my_container and structure_item
    // make structure_item->children connections
    // add each new item to my_container->items
        // make new item->children connections
    // add to items

    // use the new size as the offset to updating all the connections
    // all the links from each round assume we started at 0, hence why we need an offset as they are
    // all appened to a larger array that already has things in it

    // append all items
    for(int i = my_array->items->start; i < my_array->items->end; i++)
    {
        Item* item = (Item*) VectorGetItem(my_array->items, i);
        VectorAppend(my_container->items, item);
        item->id = VectorGetPopulation(my_container->items) - 1;

        if(structure_item->is_array || structure_item->is_string)
        {
            VectorAppendInt(structure_item->children, item->id);   
        }
        else if(structure_item->is_dictionary)
        {

            BalancedTreeNodeInsert( my_container->items, // items
                                    structure_item->children, // 234 tree
                                    0, // start node (root node)
                                    -1, // parent interval
                                    item->id);
        }


    }
    int new_size = VectorGetPopulation(my_container->items);
    for(int i = my_array->items->start; i < my_array->items->end; i++)
    {
        Item* item = (Item*) VectorGetItem(my_array->items, i); 
        if(item->is_array || item->is_string)
        {
            for(int j = item->children->start; j < item->children->end; j++)
            {
                int* x = (int*) item->children->values[j];
                (*x) += new_size;
            }
        }
        else if(item->is_dictionary)
        {
            BalancedTreeNodeDFTUpdateValue(item->children, 0, new_size);

        }
    }

}
Dictionary* DNestArray(	int number_of_items, ...)
{
    
    Dictionary* my_container = DInit();

    Item* structure_item = ItemInitCollection(array);

    VectorAppend(my_container->items, structure_item);
    structure_item->id = VectorGetPopulation(my_container->items) - 1;

    va_list ap;

    va_start(ap, number_of_items);

    for(int i = 0; i < number_of_items; i++)
    {
        Dictionary* my_array = va_arg(ap, Dictionary*);


        DTransfer(my_array, structure_item, my_container);
    }
    return my_container;
}
Dictionary* DMakeDict(	int number_of_items, ...)
{
    
    Dictionary* my_container = DInit();

    Item* structure_item = ItemInitCollection(dictionary);

    VectorAppend(my_container->items, structure_item);
    structure_item->id = VectorGetPopulation(my_container->items) - 1;

    va_list ap;

    va_start(ap, number_of_items);

    for(int i = 0; i < number_of_items; i++)
    {
        Vector* key_value_pair = va_arg(ap, Vector*);


        Vector* key_name = (Vector*) VectorGetItem(key_value_pair, 0);
        Item* key = ItemInitCollection(dictionary);
        key->key_name = key_name;
        VectorAppend(my_container->items, key);


        Dictionary* value_dict = (Dictionary*) VectorGetItem(key_value_pair, 1);
        Item* value = ItemInitCollection(dictionary);
        // what the value will be once it's added in
        key->value = VectorGetPopulation(my_container->items);
        VectorAppend(my_container->items, value);


        DTransfer(value_dict, value, my_container);
    }
    return my_container;
}
/*
test with array printout first

setup and access methods for each test
x1 = "a string"
get(x1, "i") -> Item*


x2 = ["a string"]
get(get(x2, "0"), "i") -> Item*

x3 = ["a string", "a second string"]
get(get(x3, "1"), "i") -> Item*

x4 = {"key": "a value"}
get(x4, "key") -> Item*
get(get(x4, "key"), "1") -> Item*

{"key1": ["a string"]}
get(get(get(x4, "key1"), "0"), "1") -> Item*

{"key2": ["a string", "a second string"]}

[{"key3": "a value"}]
[{"key4": ["a string", "a second string"]}]

[{"key5": "a value"},  {"key6": ["a string", "a second string"]}
]
*/

#ifndef DICTIONARY
#define DICTIONARY
#include "vector.h"
typedef struct Data
{
	int type_id; // enum
	/*
	1 => int
	2 => float
	3 => char
	4 => bool
	*/
	int _int;
	float _float;
	char _char;
	bool _bool;

}Data;
Data* DataInitInt(int a);

Data* DataInitChar(char a);

Data* DataInitFloat(float a);

Data* DataInitBool(bool a);

void DataPrintData(Data* variable);


typedef struct Item
{
    
    bool is_dictionary;
    
    bool is_array;
    bool is_string;

    bool is_primitive;


    int id;

    // this is only not null if it's type dictionary
    Vector* key_name;

    // this is only not null if it's type dictionary
    int value;
    // change to integer

    // 234 tree if this item is a dictionary type
    // array if this item is an array type or string type
    // null if this item is a primitive type
    Vector* children;

    // this is only not null if it's a primitive type
    Data* primitive;

}Item;
Item* ItemInitCollection(int type);

Item* ItemInitPrimitive(Data* primitive);


typedef struct Dictionary
{
    // this will hold all items
    Vector* items;

    // this will point to the current root
    int start_item;


}Dictionary;

Dictionary* DInit();

Dictionary* DDictionaryFromString(char* my_string);

Dictionary* DNestArray(	int number_of_items, ...);

#endif
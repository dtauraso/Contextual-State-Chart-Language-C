

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
    Item* value;

    // 234 tree if this item is a dictionary type
    // array if this item is an array type or string type
    // null if this item is a primitive type
    Vector* children;

    // this is only not null if it's a primitive type
    Data* primitive;

}Item;

typedef struct Dictionary
{
    // this will hold all items
    Vector* items;

    // this will point to the current root
    int start_item;


}Dictionary;
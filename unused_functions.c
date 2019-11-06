
char getHexLetter(int hex_value)
{
	switch(hex_value)
	{
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		case 10:
			return 'a';
		case 11:
			return 'b';
		case 12:
			return 'c';
		case 13:
			return 'd';
		case 14:
			return 'e';
		case 15:
			return 'f';
		default:

			return 'x';
	}
}
// the address of the object will be appended to end of object's name
// to enforce uniqueness in the hash table
char* convertAddressToCString(ContextState* item)
{
	// 0x2345fdeca => "2345fdeca"
	int value = (int) item;
	int size = 8;
	int i = 0;
	int address_size = sizeof(char) * size;
	char* address_string = malloc(address_size);
	memset(address_string, 1, address_size);

	address_string[size] = '\0';
	if(value == 0)
	{
		memset(address_string, 0, address_size);
		return address_string;
	}

	while(value != 0xffffffff)
	{

		int hex_value = value & 0x0000000f;

		address_string[size - 1 - i] = getHexLetter(hex_value);

		value = value >> 4;
		if(value == 0)
			break;
		i++;
	}
	return address_string;
}

char* combineNameAndObjectAddress(char* name, ContextState* address_in)
{
	char* address = convertAddressToCString(address_in);
	// x = name without surrounding quotes
	// returns '\"' + x + '_' + address + '\"'
	unsigned size_of_name = strlen(name);
	unsigned size_of_address = strlen(address);
	int new_size = size_of_name + size_of_address + 1;

	char* combined_name_and_object_address = malloc(sizeof(char) * new_size);

	// insert x
	memcpy(combined_name_and_object_address + 1,
		   name + 1,
		   sizeof(char) * (size_of_name - 2) );


	combined_name_and_object_address[0] = '\"';
	combined_name_and_object_address[size_of_name - 1] = '_';

	// insert address
	memcpy(combined_name_and_object_address + size_of_name,
		   address,
		   sizeof(char) * size_of_address);

	combined_name_and_object_address[new_size - 1] = '\"';
	combined_name_and_object_address[new_size] = '\0';

	return combined_name_and_object_address;





}
/*
int VectorSearchItem(Vector* container, void* element, int type)
{
	// needs to return wether item was found
	if(container != NULL)
	{
		int low = 0;
		int high = container->population;
		int mid = (low + high) / 2;
		//printf("%i, %i\n", integer, _string);
		while((low <= high) && (mid < container->population))
		{
			//printf("%i, %i, %i\n", low, high, mid);
			bool is_less_than = false;
			switch(type)
			{
				case integer:
				{
					// VectorIsEqualString( element,
									// ((objec*) dict_container->values[edges->values[mid]])->value)
					if(VectorIsEqualInt(element, container->values[mid]))
					{
						return mid;
					}
					is_less_than = VectorIsLessThanInt(element, container->values[mid]);
					//printf("here %i\n", is_less_than);

					break;
				}
				case _string:
				{
					if(VectorIsEqualString(element, container->values[mid]))
					{
						return mid;
					}
					is_less_than = VectorIsLessThanString(element, container->values[mid]);
					break;
				}
				default:
				{

				}
			}
			if(is_less_than)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
			mid = (low + high) / 2;


		}

		//printf("item not found %i\n", low);
		// item didn't get found
		/*
		if(low == container->population )
            return -1 * container->population;
        if(nums[low] < target) return -(low + 1);
        return -(low);
		
		if(low == container->population)
		{
			return -1 * container->population;
		}
		else if(low < container->population)
		{
			switch(type)
			{
				case integer:
				{
					if(VectorIsGreaterThanInt(element, container->values[low]))
					{
						return -1 * (low + 1);
					}
				}
				case _string:
				{
					if(VectorIsGreaterThanString(element, container->values[low]))
					{
						return -1 * (low + 1);
					}
				}
				default:
				{

				}
			}
		}

		return -1 * low;
	}
	return -200;
	
}
*/
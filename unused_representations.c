
typedef struct NeighborNames
{
	char** list_of_names;
	int number_of_names;
	int* start_names;
	int number_of_start_names;
}NeighborNames;

void printListOfListsOfStrings(NeighborNames* names)
{
	if(names != NULL)
	{
		if(names->number_of_names > 0)
		{
			printf("printing lists\n");
			for(int i = 0, j = 0; i < names->number_of_names; i++)
			{
				if(i == 0 && j == 0)
				{
					printf("start of list\n");
				}

				//printf("%i, %i\n", i, j);
				if(i != 0)
				{
					if(i == names->start_names[j + 1])
					{
						j++;
						printf("\nstart of list\n");

					}
				}
				printf("%s\n", names->list_of_names[i]);

			}
			printf("\n\n");
		}
		else
		{
			printf("empty list\n\n");
		}
	}
	else
	{
		printf("empty list\n");
		printf("\n\n");

	}
}
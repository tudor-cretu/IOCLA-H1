#include "structs.h"
#include "operations.h"

#define STRING_SIZE 100

int main(int argc, char const *argv[])
{
	char command[STRING_SIZE], file_name[STRING_SIZE];
	sensor *sensor = malloc(sizeof(sensor));
	FILE *file = NULL;
	scanf("%s", file_name);
	file = fopen(file_name, "r");
	if (file) {
		
	}
	while(1) {
		scanf("%s", command);
		if (strcmp(command, "print") == 0) {
			int index;
			if (index < 0 || index > sensor->num_sensors) 
				printf("Index not in range!\n")
			
		}
		if (strcmp(command, "exit") == 0) {
			break;
		}
	} 
	return 0;
}

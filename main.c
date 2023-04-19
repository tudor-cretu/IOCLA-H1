#include "structs.h"
#include "operations.h"

int main(int argc, char const *argv[])
{   
    FILE *fp = fopen(argv[1], "rb");
    DIE(!fp, "file open failed");

    unsigned int no_of_sensors; 
    fread(&no_of_sensors, sizeof(unsigned int), 1, fp);

    sensor **sensors = malloc(no_of_sensors * sizeof(sensor*));
    DIE(!sensors, "sensors allocation failed");

    for(unsigned int i = 0; i < no_of_sensors; i++)
        sensors[i] = read_sensors(fp);
    sort_sensors(sensors, no_of_sensors);
    
    char command[STRING_SIZE];
    int idx;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "print") == 0)
        {
            scanf("%d", &idx);
            if (idx < 0 || idx >= no_of_sensors)
                printf("Index not in range!\n");
            else print_sensors(sensors[idx]);
        }
        if(strcmp(command, "analyze") == 0)
        { 
            scanf("%d", &idx);
            if (idx < 0 || idx >= no_of_sensors)
                printf("Index not in range!\n");
            else 
                analyze_sensors(sensors, idx);
        }
        if(strcmp(command, "exit") == 0)
            break;
    }
    return 0;
}
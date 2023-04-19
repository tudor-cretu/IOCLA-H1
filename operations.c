#include "structs.h"
#include "operations.h"

// ------- DO NOT MODIFY ------- //

static void tire_pressure_status(void *data)
{
	tire_sensor *t = (tire_sensor *)data;
	if (t->pressure >= 21 && t->pressure <= 26) {
		printf("Tire has normal pressure.\n");
	} else if (t->pressure > 26 && t->pressure <= 28) {
		printf("Tire has high pressure.\n");
	} else if (t->pressure >= 19 && t->pressure < 21) {
		printf("Tire has low pressure.\n");
	} else {
		printf("Tire has abnormal pressure.\n");
	}
}

static void tire_temperature_status(void *data)
{
	tire_sensor *t = (tire_sensor *)data;
	if (t->temperature >= 0 && t->temperature <= 120) {
		printf("Tire has normal temperature.\n");
	} else {
		printf("Tire has abnormal temperature.\n");
	}
}

static void tire_wear_level_status(void *data)
{
	tire_sensor *t = (tire_sensor *)data;
	if (t->wear_level >= 0 && t->wear_level <= 20) {
		printf("Tire is new.\n");
	} else if (t->wear_level >= 20 && t->wear_level <= 40) {
		printf("Tire is slightly used.\n");
	} else if (t->wear_level >= 40 && t->wear_level <= 60) {
		printf("Tire is used. Consider a pit stop!\n");
	} else {
		printf("Tire is extremely used. Box this lap!\n");
	}
}

static void tire_performance_score(void *data)
{
	tire_sensor *t = (tire_sensor *)data;
	int score = 0;

	// Check pressure
	if (t->pressure >= 21 && t->pressure <= 26) {
		score += 4;
	} else if (t->pressure >= 19 && t->pressure < 21) {
		score += 2;
	} else if (t->pressure > 26 && t->pressure <= 28) {
		score += 3;
	} else {
		score -= 1;
	}

	// Check temperature
	if (t->temperature >= 80 && t->temperature <= 100) {
		score += 4;
	} else if (t->temperature >= 100 && t->temperature < 120) {
		score += 3;
	} else if (t->temperature > 60 && t->temperature <= 80) {
		score += 2;
	} else {
		score -= 1;
	}

	// Check wear level
	if (t->wear_level >= 0 && t->wear_level < 20) {
		score += 4;
	} else if (t->wear_level >= 20 && t->wear_level < 40) {
		score += 2;
	} else if (t->wear_level > 40 && t->wear_level < 60) {
		score -= 1;
	} else {
		score -= 2;
	}

	// Cap the score at 10
	if (score > 10) {
		score = 10;
	} else if (score < 1) {
		score = 1;
	}

	t->performace_score = score;
	printf("The tire performance score is: %d\n", score);
}

static void pmu_compute_power(void *data)
{
	power_management_unit *pmu = (power_management_unit *)data;
	float power = pmu->voltage * pmu->current;

	printf("Power output: %.2f kW.\n", power);
}

static void pmu_regenerate_energy(void *data)
{
	power_management_unit *pmu = (power_management_unit *)data;

	pmu->energy_storage += pmu->energy_regen;
	pmu->energy_regen = 0;

	// Cap the energy storage to 100%
	if (pmu->energy_storage > 100)
		pmu->energy_storage = 100;

	printf("Energy left in storage: %d\n", pmu->energy_storage);
}

static void pmu_get_energy_usage(void *data)
{
	power_management_unit *pmu = (power_management_unit *)data;
	float energy = pmu->power_consumption * pmu->current;

	printf("Energy usage: %.2f kW\n", energy);
}

static void pmu_is_battery_healthy(void *data)
{
	power_management_unit *pmu = (power_management_unit *)data;
	int ok = 0;

	if (pmu->voltage < 10 || pmu->voltage > 20) {
		printf("Battery voltage out of range: %.2fV\n", pmu->voltage);
		ok = 1;
	}

	if (pmu->current < -100 || pmu->current > 100) {
		printf("Battery current out of range: %.2fA\n", pmu->current);
		ok = 1;
	}

	if (pmu->power_consumption < 0 || pmu->power_consumption > 1000) {
		printf("Power consumption out of range: %.2f kW\n",
			   pmu->power_consumption);
		ok = 1;
	}

	if (pmu->energy_regen < 0 || pmu->energy_regen > 100) {
		printf("Energy regeneration out of range: %d%%\n", pmu->energy_regen);
		ok = 1;
	}

	if (pmu->energy_storage < 0 || pmu->energy_storage > 100) {
		printf("Energy storage out of range: %d%%\n", pmu->energy_storage);
		ok = 1;
	}

	if (ok == 1)
		return;

	printf("Battery working as expected!\n");
}

void get_operations(void **operations)
{
	operations[0] = tire_pressure_status;
	operations[1] = tire_temperature_status;
	operations[2] = tire_wear_level_status;
	operations[3] = tire_performance_score;
	operations[4] = pmu_compute_power;
	operations[5] = pmu_regenerate_energy;
	operations[6] = pmu_get_energy_usage;
	operations[7] = pmu_is_battery_healthy;
}

// ------- DO NOT MODIFY ------- //

sensor *read_sensors(FILE *fp)
{
    sensor *s = malloc(sizeof(sensor));
    DIE(!s, "sensor allocation failed");

    fread(&s->sensor_type, sizeof(enum sensor_type), 1, fp);
    if (!s->sensor_type)
    {
        tire_sensor *t = malloc(sizeof(tire_sensor));
        DIE(!t, "tire_sensor allocation failed");
        fread(&t->pressure, sizeof(float), 1, fp);
        fread(&t->temperature, sizeof(float), 1, fp);
        fread(&t->wear_level, sizeof(int), 1, fp);
        fread(&t->performace_score, sizeof(int), 1, fp);
		s->sensor_data = t;
    }
    else
    {
        power_management_unit *p = malloc(sizeof(power_management_unit));
        DIE(!p, "power_management_unit allocation failed");
        fread(&p->voltage, sizeof(float), 1, fp);
        fread(&p->current, sizeof(float), 1, fp);
        fread(&p->power_consumption, sizeof(float), 1, fp);
        fread(&p->energy_regen, sizeof(int), 1, fp);
        fread(&p->energy_storage, sizeof(int), 1, fp);
        s->sensor_data = p;
    } 
    fread(&s->nr_operations, sizeof(int), 1, fp);
    s->operations_idxs = malloc(s->nr_operations * sizeof(int));
    DIE(!s->operations_idxs, "operations_idxs allocation failed");
    for(int i = 0; i < s->nr_operations; i++)
	{
        fread(&s->operations_idxs[i], sizeof(int), 1, fp);
	}
    return s;
}

void sort_sensors(sensor **sensors, int no_of_sensors)
{
    sensor **p = malloc(no_of_sensors * sizeof(sensor*));
    sensor **t = malloc(no_of_sensors * sizeof(sensor*));
	DIE(!p, "PMU sensor allocation failed");
	DIE(!t, "Tire sensor allocation failed");
    int t_nr = 0, p_nr = 0;
    for(int i = 0; i < no_of_sensors; i++)
    {
        if (!sensors[i]->sensor_type)
            t[t_nr++] = sensors[i];
        else
            p[p_nr++] = sensors[i];
    }
    int idx = 0;
    for(int i = 0; i < p_nr; i++)
        sensors[idx++] = p[i];
    for(int i = 0; i < t_nr; i++)
        sensors[idx++] = t[i];
    free(p);
    free(t);
}

void print_sensors(sensor *sensors)
{
    if(!sensors)
    {
        printf("No sensors to print.\n");
        return;
    }
	if(!sensors->sensor_type)
	{
		tire_sensor *t = (tire_sensor *)sensors->sensor_data;
		printf("Tire Sensor\n");
		printf("Pressure: %.2f\n", t->pressure);
		printf("Temperature: %.2f\n", t->temperature);
		printf("Wear Level: %d%%\n", t->wear_level);
		if(!t->performace_score)
			printf("Performance Score: Not Calculated\n");
		else 
			printf("Performance Score: %d\n", t->performace_score);
	}
	else
	{
		power_management_unit *p = (power_management_unit *)sensors->sensor_data;
		printf("Power Management Unit\n");
		printf("Voltage: %.2f\n", p->voltage);
		printf("Current: %.2f\n", p->current);
		printf("Power Consumption: %.2f\n", p->power_consumption);
		printf("Energy Regen: %d%%\n", p->energy_regen);
		printf("Energy Storage: %d%%\n", p->energy_storage);
	}
}

void analyze_sensors(sensor **sensors, int idx)
{
	void **ops;
	int cmd_idx;
	ops = malloc(8 * sizeof(void *));
	DIE(!ops, "ops allocation failed");
	get_operations(ops);
	for (int i = 0; i < sensors[idx]->nr_operations; i++)
	{
		cmd_idx = sensors[idx]->operations_idxs[i];
		((void (*)(void *))ops[cmd_idx])(sensors[idx]->sensor_data);
	}
	free(ops);
}

void general_free(sensor **sensors, int no_of_sensors)
{
	for (int i = 0; i < no_of_sensors; i++)
	{
		free(sensors[i]->sensor_data);
		free(sensors[i]->operations_idxs);
		free(sensors[i]);	
	}
	free(sensors);
}

void clear_sensors(sensor **sensors, int *no_of_sensors)
{
	for (int i = 0; i < *no_of_sensors; i++)
	{
		short sem = 0;
		if (!sensors[i]->sensor_type)
		{
			tire_sensor *t = (tire_sensor *)sensors[i]->sensor_data;
			if (t->pressure > 28 || t->pressure < 19) 
				sem = 1;
			if (t->temperature > 120 || t->temperature < 0)
				sem = 1;
			if (t->wear_level > 100 || t->wear_level < 0)
				sem = 1;
		}
		else 
		{
			power_management_unit *p = (power_management_unit *)sensors[i]->sensor_data;
			if (p->voltage > 20 || p->voltage < 10)
				sem = 1;
			if (p->current > 100 || p->current < -100)
				sem = 1;
			if (p->power_consumption > 1000 || p->power_consumption < 0)
				sem = 1;
			if (p->energy_regen > 100 || p->energy_regen < 0)
				sem = 1;
			if (p->energy_storage > 100 || p->energy_storage < 0)
				sem = 1;
		}
		if (sem)
		{
			free(sensors[i]->sensor_data);
			free(sensors[i]->operations_idxs);
			free(sensors[i]);	
			for (int j = i; j < *no_of_sensors - 1; j++)
				sensors[j] = sensors[j + 1];
			sensors[*no_of_sensors - 1] = NULL;
			*no_of_sensors -= 1;
			i--;
		}
	}
}

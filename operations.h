#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRING_SIZE 20

// Macro for memory error handling (defensive programming)
#define DIE(assertion, call_description) \
	do {                                  \
		if (assertion) {                   \
			fprintf(stderr, "(%s, %d): ",   \
					  __FILE__, __LINE__);   \
			perror(call_description);         \
			exit(errno);                       \
		}                                       \
	} while (0)

static void tire_pressure_status(void *data);
static void tire_temperature_status(void *data);
static void tire_wear_level_status(void *data);
static void tire_performance_score(void *data);

static void pmu_compute_power(void *data);
static void pmu_regenerate_energy(void *data);
static void pmu_get_energy_usage(void *data);
static void pmu_is_battery_healthy(void *data);

void get_operations(void **operations);

sensor *read_sensors(FILE *fp);
void sort_sensors(sensor **sensors, unsigned int no_of_sensors);
void print_sensors(sensor *sensors);
void analyze_sensors(sensor **sensors, int idx);
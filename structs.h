#pragma once

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

enum sensor_type {
	TIRE, // 0
	PMU // 1
};

typedef struct {
	enum sensor_type sensor_type; // 0 for TIRE, 1 for PMU
	void *sensor_data; // TireSensor/PowerManagementUnit
	int nr_operations;
	int *operations_idxs;
} sensor;

typedef struct __attribute__((__packed__)) {
	float voltage; // voltage level of the battery; 10-20 volts
	float current; // current draw from the battery; -100 to 100 amps; negative values indicate energy regeneration during braking
	float power_consumption; // power consumption of the car; 0 to 1000 kilowatts
	int energy_regen; // energy regenerated during braking; between 0-100%
	int energy_storage; // amount of energy stored in the battery; between 0-100%
} power_management_unit;

typedef struct __attribute__((__packed__)) {
	float pressure; // 19-26 psi
	float temperature; // between 0-120C
	int wear_level; // interval between 0-100%;. 0% wear means new tire.
	int performace_score; // between 1-10; 1 low performance; 10 high performance
} tire_sensor;

#endif // _STRUCTS_H_


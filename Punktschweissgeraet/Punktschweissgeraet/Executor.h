/*
 * Executor.h
 *
 * Created: 05.05.2016 18:41:27
 *  Author: Oliver
 */ 


#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#ifndef MEASURE_DISCHARGE_CURVE
#define MEASURE_DISCHARGE_CURVE 1
#endif

#define CHECK_BIT(var,pos) ((var >> pos) & 1)

#define C1_FIRE PD7
#define C2_FIRE PD6
#define C3_FIRE PB4

#define CAP_HIGH_SIZE 0.206 //F


#include <stdint.h>

struct executionResult
{
	double ohmC1;
	double voltageUsedC1;
	double ampereC1;	
	double ohmC2;
	double voltageUsedC2;
	double ampereC2;
	double measuredCurve [26];
};

typedef struct executionResult ExecutionResult;

void execute (ExecutionResult *result, uint8_t executeCapacitor);


#endif /* EXECUTOR_H_ */
/*
 * ExecCount.h
 *
 * Created: 22.03.2016 00:33:17
 *  Author: Oliver
 */ 


#ifndef EXECCOUNT_H_
#define EXECCOUNT_H_

#include <stdint.h>


void initExecCount();
void addExecution ();
uint32_t getAllExecutions();
uint16_t getTodaysExections();



#endif /* EXECCOUNT_H_ */
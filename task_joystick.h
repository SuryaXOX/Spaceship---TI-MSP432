/*
 * task_print1.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Surya Santhan Thenarasu
 */

#ifndef TASK_JOYSTICK_H_
#define TASK_JOYSTICK_H_

#include "main.h"

#define VOLT_0P85  1229      // 0.99 /(3.3/4096)
#define VOLT_2P50  2867      // 2.31 /(3.3/4096)

 extern volatile bool PS2;

extern TaskHandle_t Task_Joystick_Handle;
extern TaskHandle_t Task_Joystick_Timer_Handle;

/******************************************************************************
* Configure the IO pins for BOTH the X and Y directions of the analog
* joystick.  The X direction should be configured to place the results in
* MEM[0].  The Y direction should be configured to place the results in MEM[1].
*
* After BOTH analog signals have finished being converted, a SINGLE interrupt
* should be generated.
*
* Parameters
*      None
* Returns
*      None
******************************************************************************/
 void Task_Joystick_Init(void);

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Joystick_Timer(void *pvParameters);

/******************************************************************************
* Helper Function for Check_Boundaries(int x, int y, int z)
* Return true if the circle is within the boundaries
******************************************************************************/
bool Check_Boundaries_Helper(int a, int b);

/******************************************************************************
* Depending on the ADC data, this function checks if the circle moves within the given boundaries
* Return true if the circle is within the boundaries
******************************************************************************/
bool Check_Boundaries(int x, int y, int z);

/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Joystick_Bottom_Half(void *pvParameters);



#endif /* TASK_JOYSTICK_H_ */

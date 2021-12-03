/*
 * task_space_ship.c
 *
 *  Created on: Nov 3, 2020
 *      Author: Surya Santhan Thenarasu
 */

#include <main.h>

#define SHIP_QUEUE_LEN  2

TaskHandle_t Task_Space_Ship_Handle;
QueueHandle_t Queue_Space_Ship;

/******************************************************************************
 * This function will initialize Queue_Space_Ship and initialize the LCD
 ******************************************************************************/
void Task_Space_Ship_Init(void)
{
    Queue_Space_Ship = xQueueCreate(SHIP_QUEUE_LEN,sizeof(SHIP_MSG_t));

    // ADD CODE to initialize the LCD
    Crystalfontz128x128_Init();
}


/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to SHIP_QUEUE_LEN
 ******************************************************************************/
void Task_Space_Ship(void *pvParameters)
{
    SHIP_MSG_t msg;
    BaseType_t status;
    int DELAY = 25;
    int x = 64;
    int y = 64;

    lcd_draw_image(
        x,
        y,
        space_shipWidthPixels,
        space_shipHeightPixels,
        space_shipBitmaps,
        LCD_COLOR_RED,
        LCD_COLOR_BLACK);


while(1)
{

    /* ADD CODE
     * wait until we receive a message in  Queue_Space_Ship
     */
    status = xQueueReceive(Queue_Space_Ship, &msg, 0);


    int value = 1;
    int dist = msg.value;
    int i;

    //decrypt the msg received from either the console or the joystick
    for(i=0;i<dist;i++)
    {
   if(msg.cmd == SHIP_CMD_CENTER)
    {

    }
    else if(msg.cmd == SHIP_CMD_LEFT)
    {
        if((x - value) > 27)
        {
        x = x - value;
        }
        else
        {
            msg.cmd = SHIP_CMD_CENTER;
        }
    }
    else if(msg.cmd == SHIP_CMD_RIGHT)
    {
        if((x + value) < 106)
        {
        x = x + value;
        }
        else
        {
            msg.cmd = SHIP_CMD_CENTER;
        }
    }
    else if(msg.cmd == SHIP_CMD_UP)
    {
        if((y - value) > 21)
        {
        y = y - value;
        }
        else
        {
            msg.cmd = SHIP_CMD_CENTER;
        }
    }
    else if(msg.cmd == SHIP_CMD_DOWN)
    {
        if((y + value) < 112)
        {
        y = y + value;
        }
        else
        {
            msg.cmd = SHIP_CMD_CENTER;
        }
    }
    else if(msg.cmd == SHIP_CMD_SPEED)
    {
        DELAY = msg.value;
    }



   lcd_draw_image(
       x,
       y,
       space_shipWidthPixels,
       space_shipHeightPixels,
       space_shipBitmaps,
       LCD_COLOR_RED,
       LCD_COLOR_BLACK);

   vTaskDelay(pdMS_TO_TICKS(DELAY));

    }





}
}



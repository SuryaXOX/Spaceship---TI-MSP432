/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Surya Santhan Thenarasu
 */
#include <main.h>
#include <ctype.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;
SemaphoreHandle_t Sem_Console;

extern volatile bool UPDATE = false;
#define RX_ARRAY_SIZE 10
#define NUM_ARRAY_SIZE 10

// Global variables used to store incoming data from RXBUF.
volatile char RX_ARRAY[RX_ARRAY_SIZE];
volatile uint16_t RX_INDEX=0;

volatile char NUM_ARRAY[NUM_ARRAY_SIZE];
volatile uint16_t NUM_INDEX=0;



/******************************************************************************
 * This function configures the eUSCI_A0 to be a UART that communicates at
 * 115200 8N1.
 *
 * The configuration should be identical to what you have done
 * in a previous ICE-08 EXCEPT that you will need to set the priority of the
 * eUSCI to be a value that is equal to 2
 ******************************************************************************/
static void console_hw_init(void)
{
    // Configure  the IO pins used for the UART
    // set 2-UART pin as secondary function
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;        // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST |        // Remain eUSCI in reset
                        EUSCI_B_CTLW0_SSEL__SMCLK; // Configure eUSCI clock source for SMCLK

    // Baud rate calculation
    // 24000000/(16*115200) = 13.020833333
    // Fractional portion = 0.020833333
    // UCBRFx = int ( (13.020833333-13)*16) = 0
    EUSCI_A0->BRW = 13;             // 24000000/16/115200

    // Set the fractional portion of the baud rate and turn
    // on oversampling
    EUSCI_A0->MCTLW = (0 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;

    // Enable eUSCI in UART mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

    // Clear any outstanding interrupts
    EUSCI_A0->IFG &= ~(EUSCI_A_IFG_RXIFG | EUSCI_A_IFG_TXIFG);

    // Enable Rx Interrupt
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;

    // Enable EUSCIA0 Interrupt and set priority to 2
    NVIC_EnableIRQ(EUSCIA0_IRQn);
    NVIC_SetPriority(EUSCIA0_IRQn,2);
}

/******************************************************************************
 * This function initializes the eUSCI_A0 hardware by calling console_hw_init().
 * It will also initialize Sem_Console.
 *
 * NOTE:  This function must be run prior to the FreeRTOS scheduler being
 * started.
 ******************************************************************************/
void Task_Console_Init(void)
{

    // Initialize the array used to hold UART data
    memset(RX_ARRAY,0,RX_ARRAY_SIZE);

    // Initialize UART
    console_hw_init();

    // Initialize the binary semaphore used to provide mutual exclusion to
    // the UART.
    Sem_Console = xSemaphoreCreateBinary();

}

/*****************************************************
 * Needed to get printf to work using polling when
 * transmitting characters.
 *****************************************************/
int fputc(int c, FILE* stream)
{
    // while UART is busy, wait
    while(EUSCI_A0->STATW & EUSCI_A_STATW_BUSY){};

    EUSCI_A0->TXBUF = c;

    return 0;
}

//****************************************************************************
// UART interrupt service routine
// ****************************************************************************/
void EUSCIA0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t status;

    // Check for Rx interrupts
    if( EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {

        char x = EUSCI_A0->RXBUF;

        if(x==0x0A || x==0x0D)
        {
            UPDATE = true;
        }
        else
        {

            // Reading from the RXBUF automatically
            // Clears the Rx Interrupt
            RX_ARRAY[RX_INDEX] = x;
            printf(&RX_ARRAY[RX_INDEX]);
            RX_INDEX++;

            if(isdigit(x))
            {
                NUM_ARRAY[NUM_INDEX] = x;
                NUM_INDEX++;
            }


        }


    }

    if(UPDATE)
    {
        UPDATE = false;
    /* ADD CODE
         * Send a task notification to Task_Console_Bottom_Half
         */
        vTaskNotifyGiveFromISR(
                Task_Console_Handle,
                        &xHigherPriorityTaskWoken
                );

                portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }


}

/******************************************************************************
* Task used to parse the commands received by the UART
*
* Command  |    Description
*
* L 10          Move Left by 10 pixels
* R 5           Move Right by 5 pixels
* U 20          Move Up by 20 pixels
* D 4           Move Down by 4 pixels
* S 1           Set Ship Speed to 1mS/Pixel
******************************************************************************/
void Task_Console_Bottom_Half(void *pvParameters)
{
    SHIP_MSG_t msg;
    BaseType_t status;
    msg.cmd = SHIP_CMD_CENTER;

while(1)
{
    status = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    printf("\n\r");

    // get the numerical value from the rx buffer
    int val = atoi(NUM_ARRAY);

     msg.value = val;

     //if-else loop used to parse the commands received by the UART
    if(RX_ARRAY[0] == 'L')
    {
        msg.cmd = SHIP_CMD_LEFT;
    }
    else if(RX_ARRAY[0] == 'R')
    {
        msg.cmd = SHIP_CMD_RIGHT;
    }
    else if(RX_ARRAY[0] == 'D')
    {
        msg.cmd = SHIP_CMD_DOWN;
    }
    else if(RX_ARRAY[0] == 'U')
    {
        msg.cmd = SHIP_CMD_UP;
    }
    else if(RX_ARRAY[0] == 'S')
    {
        msg.cmd = SHIP_CMD_SPEED;
    }
    else
    {
        msg.cmd = SHIP_CMD_CENTER;
    }

    memset(RX_ARRAY,0,RX_ARRAY_SIZE);
    RX_INDEX = 0;

    memset(NUM_ARRAY,0,NUM_ARRAY_SIZE);
    NUM_INDEX = 0;

    xQueueSend(Queue_Space_Ship, &msg, portMAX_DELAY);

    msg.cmd = SHIP_CMD_CENTER;

    xQueueSend(Queue_Space_Ship, &msg, portMAX_DELAY);



}

}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "cli_commands.h"
#include "debug.h"


void setGPIO(char *args)
{
    const char *gpioPort = strtok(NULL, " ");
    uint8_t pinnumber = atoi(strtok(NULL, " "));
    uint8_t status = atoi(strtok(NULL, " "));

    if (gpioPort == NULL || pinnumber == 0 || status >= 2)
    {
        LOG_Print("Missing argument(s)");
        return;
    }

    if(gpioPort[0] == 'A' || gpioPort[0] == 'a')
    	HAL_GPIO_WritePin(GPIOA, (1<<pinnumber), status);

    else if(gpioPort[0] == 'B' || gpioPort[0] == 'b')
    	HAL_GPIO_WritePin(GPIOB, (1<<pinnumber), status);

    else if(gpioPort[0] == 'C' || gpioPort[0] == 'c')
    	HAL_GPIO_WritePin(GPIOC, (1<<pinnumber), status);

    else if(gpioPort[0] == 'D' || gpioPort[0] == 'd')
    	HAL_GPIO_WritePin(GPIOD, (1<<pinnumber), status);
}


/* Includes */
#include "debug.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "sh_eeprom.h"

/* Defines */
extern UART_HandleTypeDef huart1;
#define LOGGER_UART &huart1

#define LOG_BUFFER_SIZE 255
/* Variables */
static const uint16_t USART_TIMEOUT = 3000;

static char buf[LOG_BUFFER_SIZE];

const char* suffix = { "\n" };

/* Functions */
void LOG_Print(const char* text, ...)
{
    if (text == NULL)
    {
        return;
    }

    va_list argptr;
    va_start(argptr, text);
    vsnprintf(buf, LOG_BUFFER_SIZE, text, argptr);
    va_end(argptr);

    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)buf, strlen(buf), USART_TIMEOUT);
}

void LOG_Info(const char* text, ...)
{
    if (text == NULL)
    {
        return;
    }

    va_list argptr;
    va_start(argptr, text);
    vsnprintf(buf, LOG_BUFFER_SIZE, text, argptr);
    va_end(argptr);

    char* prefix = { "[INFO]   " };
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)prefix, strlen(prefix) - 1, USART_TIMEOUT);
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)buf, strlen(buf), USART_TIMEOUT);
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)suffix, strlen(suffix), USART_TIMEOUT);
}

void LOG_Warning(const char* text, ...)
{
    if (text == NULL)
    {
        return;
    }

    va_list argptr;
    va_start(argptr, text);
    vsnprintf(buf, LOG_BUFFER_SIZE, text, argptr);
    va_end(argptr);

    char* prefix = { "[WARNING]   " };
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)prefix, strlen(prefix) - 1, USART_TIMEOUT);
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)buf, strlen(buf), USART_TIMEOUT);
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)suffix, strlen(suffix), USART_TIMEOUT);
}

void LOG_Error(const char* text, ...)
{
    if (text == NULL)
    {
        return;
    }

    va_list argptr;
    va_start(argptr, text);
    vsnprintf(buf, LOG_BUFFER_SIZE, text, argptr);

    va_end(argptr);

    char* prefix = { "[ERROR]   " };
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)prefix, strlen(prefix) - 1, USART_TIMEOUT);
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)buf, strlen(buf), USART_TIMEOUT);
    HAL_UART_Transmit(LOGGER_UART, (uint8_t*)suffix, strlen(suffix), USART_TIMEOUT);

}

void LOG_Header (const char* str)
{
  LOG_Print ("\n========================================================================================");
  LOG_Print ("\n%s", str);
  LOG_Print ("\n========================================================================================\n");
}

const char* DEBUG_GetTimestampStr (const time_t time)
{
  struct tm *timeinfo = localtime(&time);

  memset (buf, '\0', sizeof (buf));
  snprintf (buf, sizeof(buf), "%02u-%02u-20%02u %02u:%02u:%02u", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year - 100,
                                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  return buf;
}

const char* DEBUG_GetItemStr (uint16_t page, uint32_t address)
{
  EE_Item_t* pItem = SH_EEPROM_FindItem ((EE_Page_t)page, address);

  memset (buf, '\0', sizeof (buf));

  snprintf (buf, sizeof(buf), "%s", pItem->label);

  return buf;
}

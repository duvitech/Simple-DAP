/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <RTL.h>
#include "rl_usb.h"

#include "uart.h"


UART_Configuration UART_Config;


/** \brief  Vitual COM Port initialization

    The function inititalizes the hardware resources of the port used as
    the Virtual COM Port.

    \return             0        Function failed.
    \return             1        Function succeeded.
 */
int32_t USBD_CDC_ACM_PortInitialize (void) {
    return (uart_initialize ());
}


/** \brief  Vitual COM Port uninitialization

    The function uninititalizes/releases the hardware resources of the port used
    as the Virtual COM Port.

    \return             0        Function failed.
    \return             1        Function succeeded.
 */
int32_t USBD_CDC_ACM_PortUninitialize (void) {
    return (uart_uninitialize ());
}


/** \brief  Vitual COM Port reset

    The function resets the internal states of the port used
    as the Virtual COM Port.

    \return             0        Function failed.
    \return             1        Function succeeded.
 */
int32_t USBD_CDC_ACM_PortReset (void) {
    return (uart_reset ());
}


/** \brief  Virtual COM Port change communication settings

    The function changes communication settings of the port used as the
    Virtual COM Port.

    \param [in]         line_coding  Pointer to the loaded CDC_LINE_CODING structure.
    \return             0        Function failed.
    \return             1        Function succeeded.
 */
int32_t USBD_CDC_ACM_PortSetLineCoding (CDC_LINE_CODING *line_coding) {
    UART_Config.Baudrate    = line_coding->dwDTERate;
    UART_Config.DataBits    = (UART_DataBits) line_coding->bDataBits;
    UART_Config.Parity      = (UART_Parity)   line_coding->bParityType;
    UART_Config.StopBits    = (UART_StopBits) line_coding->bCharFormat;
    UART_Config.FlowControl = UART_FLOW_CONTROL_NONE;

    return (uart_set_configuration (&UART_Config));
}


/** \brief  Vitual COM Port retrieve communication settings

    The function retrieves communication settings of the port used as the
    Virtual COM Port.

    \param [in]         line_coding  Pointer to the CDC_LINE_CODING structure.
    \return             0        Function failed.
    \return             1        Function succeeded.
 */
int32_t USBD_CDC_ACM_PortGetLineCoding (CDC_LINE_CODING *line_coding) {
    if (uart_get_configuration (&UART_Config)) {
        line_coding->dwDTERate   = UART_Config.Baudrate;
        line_coding->bDataBits   = UART_Config.DataBits;
        line_coding->bParityType = UART_Config.Parity;
        line_coding->bCharFormat = UART_Config.StopBits;
        return (1);
    }

    return (0);
}


/** \brief  Virtual COM Port set control line state

    The function sets control line state on the port used as the
    Virtual COM Port.

    \param [in]         ctrl_bmp Control line settings bitmap (
                          0. bit - DTR state,
                          1. bit - RTS state).
    \return             0        Function failed.
    \return             1        Function succeeded.
 */
int32_t USBD_CDC_ACM_PortSetControlLineState (uint16_t ctrl_bmp) {
    return (1);
}

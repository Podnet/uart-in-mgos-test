#include "mgos.h"

int uart_no = 1;





/*! \mainpage UART in doc
 *
 * \section Documentation
 *
 * This a test app receieve data over UART port for ESP32.
 */





/**> Function to check UART connection. */ 
void check_uart(void *arg)
{
    if(mgos_uart_is_rx_enabled(uart_no)) {
        LOG(LL_INFO, ("RX is enabled on UART interface %d",uart_no));
    }
    int bytes_avail = mgos_uart_read_avail(uart_no);
    char buf[100];
    if (bytes_avail > 0)
    {
        mgos_uart_read(uart_no, buf, bytes_avail);
        LOG(LL_INFO, ("Received information: %s", buf));
    }
    else {
        LOG(LL_INFO, ("No information available."));
    }
    (void)arg;
}

/**> MongooseOS initialization function to setup UART. */
enum mgos_app_init_result mgos_app_init(void)
{
    LOG(LL_INFO, ("Preparing UART interface"));

    struct mgos_uart_config ucfg;
    mgos_uart_config_set_defaults(uart_no, &ucfg);

    ucfg.baud_rate = 9600;
    ucfg.rx_buf_size = 150;
    ucfg.tx_buf_size = 150;

    if (!mgos_uart_configure(uart_no, &ucfg))
    {
        LOG(LL_ERROR, ("Failed to configure UART%d", uart_no));
    }

    mgos_uart_set_rx_enabled(uart_no, true);

    // mgos_uart_set_dispatcher(uart_no, uart_msg_recv, NULL);
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, check_uart, NULL);
    LOG(LL_INFO, ("Handler set for receiving data via UART."));

    return MGOS_APP_INIT_SUCCESS;
}
//-------------------------------------------
// Name: vcnl_4040.c
// Author: Gregor Morrison
// Description: This driver file contains functions for communication
// with the proximity sensor over I2C.
//
// Referenced code: https://github.com/sparkfun/SparkFun_VCNL4040_Arduino_Library/blob/master/src/SparkFun_VCNL4040_Arduino_Library.cpp
//-------------------------------------------
#include "vcnl4040.h"

// Proximity sensor configuration register values
static uint8_t ps_conf1_data =	(0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (0 << 0);
static uint8_t ps_conf2_data =	(0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (1 << 3) | (0 << 2) | (0 << 1) | (0 << 0);
static uint8_t ps_conf3_data =	(0 << 7) | (0 << 6) | (0 << 5) | (1 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0);
static uint8_t ps_ms_data =		(0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
 
/* Indicates if operation on I2C has ended. */
volatile bool m_xfer_done = false;

/* TWI instance. */
const nrf_drv_twi_t twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Buffer for samples read from proximity sensor. */
static uint8_t m_sample_lsb;
static uint8_t m_sample_msb;
static uint16_t m_sample;

volatile uint16_t prox_val = 0;

/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    // Should specific errors occur in I2C communication (such as slave NACK),
    // corresponding error message is printed to serial
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            m_xfer_done = true;
            break;
        case NRF_DRV_TWI_EVT_DATA_NACK:
            NRF_LOG_INFO("\r\nDATA NACK ERROR");
            break;
        case NRF_DRV_TWI_EVT_ADDRESS_NACK:
            NRF_LOG_INFO("\r\nADDRESS NACK ERROR");
            break;
        default:
            break;
    }
}


/**
 * @brief Function for setting active mode on VCNL4040 proximity sensor
 */
void vcnl4040_config(void)
{	

    NRF_LOG_INFO("Configuring VCNL...");

	uint8_t reg1[3] = {VCNL4040_PS_CONF3, ps_conf3_data, ps_ms_data};
    m_xfer_done = false;
    nrf_drv_twi_tx(&twi, VCNL4040_ADDR, reg1, sizeof(reg1), false);
    while (m_xfer_done == false);
	
    uint8_t reg2[3] = {VCNL4040_PS_CONF1, ps_conf1_data, ps_conf2_data};
    m_xfer_done = false;
    nrf_drv_twi_tx(&twi, VCNL4040_ADDR, reg2, sizeof(reg2), false);
    while (m_xfer_done == false);
    NRF_LOG_INFO("VCNL CONFIG DONE")
}

/**
 * @brief initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;
    // Initializes the I2C connection to 400 kHz,
    // using the SDA and SCL pins for the board
    // (see README to change which board/platform is in use)

    const nrf_drv_twi_config_t twi_config = {
       .scl                = I2C_SCL,
       .sda                = I2C_SDA,
       .frequency          = NRF_DRV_TWI_FREQ_400K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&twi, &twi_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&twi);
}

/**
 * @brief Function for reading data from proximity sensor.
 * The proximity sensor gives relative data - that is, it
 * records a qualitative proximity magnitude compared to the
 * proximity it detects immediately when it is configured.
 * The proximity value:
 * - increases if an object is currently nearer to it than on configuration
 * - decreases if an object is currently farther from it than on configuration
 * 
 * In practice, this means that the device should start with nothing near the
 * sensor, and when it is in use/inserted, the proximity value increases and
 * a the threshold is met.
 */
void vcnl4040_read_sensor_data(void)
{
    m_xfer_done = false;

    while(prox_val <= PROX_THRESHOLD){
        uint8_t reg3[2] = {VCNL4040_PS_DATA, VCNL4040_ADDR};
        uint8_t reg4[2] = {m_sample_lsb, m_sample_msb};
        uint8_t *p_ret = reg4;


        // The descriptor below is used to properly handle the VCNL4040's read protocol
        // The device address is selected, the (16-bit) register to read is passed and the (16-bit) data is returned
        // See the nrf SDK reference guide for more information on nrf_drv_twi_xfer_desc_t
        nrf_drv_twi_xfer_desc_t const vcnl_desc = {NRFX_TWI_XFER_TXRX, VCNL4040_ADDR, sizeof(reg3), sizeof(reg4), reg3, p_ret};
        nrf_drv_twi_xfer(&twi, &vcnl_desc, false);
        while(nrf_drv_twi_is_busy(&twi) == true);

        m_sample_lsb = *p_ret; // the LSB of the returned data is stored
        p_ret++;               // the returned data pointer is incremented to point to the MSB data
        m_sample_msb = *p_ret; // the MSB of the returned data is stored

        m_sample = (((m_sample_msb) << 8) | (m_sample_lsb)); // the LSB and MSB of the data are concatenated to give full 16-bit data
        prox_val = m_sample;
        //NRF_LOG_INFO("Proximity: %d", m_sample);
    }

    uint8_t reg3[2] = {VCNL4040_PS_DATA, VCNL4040_ADDR};
    uint8_t reg4[2] = {m_sample_lsb, m_sample_msb};
    uint8_t *p_ret = reg4;
    nrf_drv_twi_xfer_desc_t const vcnl_desc = {NRFX_TWI_XFER_TXRX, VCNL4040_ADDR, sizeof(reg3), sizeof(reg4), reg3, p_ret};
    nrf_drv_twi_xfer(&twi, &vcnl_desc, false);
    while(nrf_drv_twi_is_busy(&twi) == true);
}

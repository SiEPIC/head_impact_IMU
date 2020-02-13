#ifndef MT25QL256ABA_H
#define MT25QL256ABA_H

#include "stdint.h"
#include "stdbool.h"

//Software Reset Option
#define MT25QL256ABA_RESET_ENABLE                            0x66
#define MT25QL256ABA_RESET_MEMORY                            0x99

//READ ID Operations
#define MT25QL256ABA_READ_ID                                 0x9E //or 0x9F

//READ MEMORY Operations
#define MT25QL256ABA_READ                                    0x03
#define MT25QL256ABA_FAST_READ                               0x0B

//WRITE Operations
#define MT25QL256ABA_WRITE_ENABLE                            0x06
#define MT25QL256ABA_WRITE_DISABLE                           0x04

//READ REGISTER Operations
#define MT25QL256ABA_READ_STATUS_REGISTER                    0x05
#define MT25QL256ABA_READ_FLAG_STATUS_REGISTER               0x70
#define MT25QL256ABA_NONVOLATILE_CONFIGURATION_REGISTER      0xB5
#define MT25QL256ABA_READ_VOLATILE_CONFIGURATION_REGISTER    0x85

//WRITE REGISTER Operations
#define MT25QL256ABA_WRITE_STATUS_REGISTER                   0x01
#define MT25QL256ABA_WRITE_NONVOLATILE_CONFIGURATION_REGISTER 0xB1
#define MT25QL256ABA_WRITE_VOLATILE_CONFIGURATION_REGISTER   0x81

//CLEAR FLAG STATUS REGISTER Operation
#define MT25QL256ABA_CLEAR_FLAG_STATUS_REGISTER          0x50

//PROGRAM Operations
#define MT25QL256ABA_PAGE_PROGRAM                        0x02

//ERASE Operations
#define MT25QL256ABA_ERASE_32KB_SUBSECTOR                0x52
#define MT25QL256ABA_ERASE_4KB_SUBSECTOR                 0x20
#define MT25QL256ABA_SECTOR_ERASE                        0xD8
#define MT25QL256ABA_BULK_ERASE                          0xC7 // or 0x60

#define MT25QL256ABA_LOW_128MBIT_SEGMENT_ADDRESS_START    0x00000000
#define MT25QL256ABA_LOW_128MBIT_SEGMENT_ADDRESS_END      0x00FFFFFF
#define MT25QL256ABA_HIGH_128MBIT_SEGMENT_ADDRESS_START   0x01000000
#define MT25QL256ABA_HIGH_128MBIT_SEGMENT_ADDRESS_END     0x01FFFFFF


int8_t mt25ql256aba_read_op(uint8_t command_code, uint8_t* address, uint8_t address_size, uint8_t* reg_data, uint8_t rx_num_bytes);
int8_t mt25ql256aba_write_op(uint8_t command_code, uint8_t* address, uint8_t address_size, uint8_t* data, uint8_t data_size);
int8_t mt25ql256aba_write_disable(void);
int8_t mt25ql256aba_write_enable(void);

#endif //MT25QL256ABA_H
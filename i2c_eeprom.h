#define false 0
#define true 1

//#define slaveF_SCL 100000 //100 Khz
#define slaveF_SCL 400000 //400 Khz

#define slaveAddressConst 0b1010 //Постоянная часть адреса ведомого устройства
#define slaveAddressVar 0b000 //Переменная часть адреса ведомого устройства

//Разряды направления передачи данных
#define READFLAG 1 //Чтение
#define WRITEFLAG 0 //Запись

void eeInit(void); //Начальная настройка TWI
uint8_t eeWriteByte(uint16_t address,uint8_t data); //Запись байта в модуль памяти EEPROM
uint8_t eeReadByte(uint16_t address); //Чтение байта из модуля памяти EEPROM

// TWSR values (not bits)
// (taken from avr-libc twi.h - thank you Marek Michalkiewicz)
// Master
#define TW_START                    0x08
#define TW_REP_START                0x10
// Master Transmitter
#define TW_MT_SLA_ACK               0x18
#define TW_MT_SLA_NACK              0x20
#define TW_MT_DATA_ACK              0x28
#define TW_MT_DATA_NACK             0x30
#define TW_MT_ARB_LOST              0x38
// Master Receiver
#define TW_MR_ARB_LOST              0x38
#define TW_MR_SLA_ACK               0x40
#define TW_MR_SLA_NACK              0x48
#define TW_MR_DATA_ACK              0x50
#define TW_MR_DATA_NACK             0x58
// Slave Transmitter
#define TW_ST_SLA_ACK               0xA8
#define TW_ST_ARB_LOST_SLA_ACK      0xB0
#define TW_ST_DATA_ACK              0xB8
#define TW_ST_DATA_NACK             0xC0
#define TW_ST_LAST_DATA             0xC8
// Slave Receiver
#define TW_SR_SLA_ACK               0x60
#define TW_SR_ARB_LOST_SLA_ACK      0x68
#define TW_SR_GCALL_ACK             0x70
#define TW_SR_ARB_LOST_GCALL_ACK    0x78
#define TW_SR_DATA_ACK              0x80
#define TW_SR_DATA_NACK             0x88
#define TW_SR_GCALL_DATA_ACK        0x90
#define TW_SR_GCALL_DATA_NACK       0x98
#define TW_SR_STOP                  0xA0
// Misc
#define TW_NO_INFO                  0xF8
#define TW_BUS_ERROR                0x00

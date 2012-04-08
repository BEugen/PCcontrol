#ifndef _CONFIGPIN_
#define _CONFIGPIN_
#include <ioavr.h>
 

/*#define INDICATOR_PORT           DDRC
#define INDICATOR_PORT_OUTPUT    PORTC
#define BUTTON_PORT              DDRA
#define BUTTON_PORT_PIN          PINA
#define BUTTON                   PA1*/

#define OUTPUT_PORT              DDRA
#define OUT_PORT_OUTPUT          PORTA
#define RESET_BIT                PA0
#define POWER_BIT                PA0
#define USB_BIT                  PA0
#define RELAY_BIT                PA0
#define TEST_BIT                 PA3

#define INP_INT_PORT             DDRD
#define OUT_INT_PORT             PORTD
#define IN_INT_PORT_PIN          PIND
#define FAN1                     PD2
#define FAN2                     PD3 

#define IN_POWER()                 (!(IN_INT_PORT_PIN  & (1<<FAN1)))
#define IN_POWER_GOOD()            (!(IN_INT_PORT_PIN  & (1<<FAN2)))



#define ON_RESET()      (OUT_PORT_OUTPUT  |=  (1<<RESET_BIT))
#define OFF_RESET()     (OUT_PORT_OUTPUT  &= ~(1<<RESET_BIT))
#define RESET()         (OUT_PORT_OUTPUT  & (1<<RESET_BIT))  
#define REVERSE_RESET() (RESET()?OFF_RESET():ON_RESET())

#define ON_POWER()      (OUT_PORT_OUTPUT  |=  (1<<POWER_BIT))
#define OFF_POWER()     (OUT_PORT_OUTPUT  &= ~(1<<POWER_BIT))
#define POWER()         (OUT_PORT_OUTPUT  & (1<<POWER_BIT))  
#define REVERSE_POWER() (POWER()?OFF_POWER():ON_POWER())

#define ON_USB()      (OUT_PORT_OUTPUT  |=  (1<<USB_BIT))
#define OFF_USB()     (OUT_PORT_OUTPUT  &= ~(1<<USB_BIT))
#define USB()         (OUT_PORT_OUTPUT  & (1<<USB_BIT))  
#define REVERSE_USB() (USB()?OFF_USB():ON_USB())

#define ON_RELAY()      (OUT_PORT_OUTPUT  |=  (1<<RELAY_BIT))
#define OFF_RELAY()     (OUT_PORT_OUTPUT  &= ~(1<<RELAY_BIT))
#define RELAY()         (OUT_PORT_OUTPUT  & (1<<RELAY_BIT))  
#define REVERSE_RELAY() (RELAY()?OFF_RELAY():ON_RELAY())

#define ON_TEST()      (OUT_PORT_OUTPUT  |=  (1<<TEST_BIT))
#define OFF_TEST()     (OUT_PORT_OUTPUT  &= ~(1<<TEST_BIT))
#define TEST()         (OUT_PORT_OUTPUT  & (1<<TEST_BIT))  
#define REVERSE_TEST() (TEST()?OFF_TEST():ON_TEST())


/*#define ON_TX() (OUT_PORT_OUTPUT  |=  (1<<DRIVER_BIT))
#define ON_RX() (OUT_PORT_OUTPUT  &=  ~(1<<DRIVER_BIT)) 
#define OFF_DRIVER() (OUT_PORT_OUTPUT  &= ~(1<<DRIVER_BIT))

#define BUTTON_PRESS		(!(BUTTON_PORT_PIN  & (1<<BUTTON)))
#define DRIVER_ENABLE           (!(OUT_PORT_OUTPUT  & (1<<DRIVER_BIT)))*/

void PinInit (void);
#endif

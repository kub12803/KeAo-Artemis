#ifndef _RFM98_H
#define _RFM98_H

#include <SPI.h>
#include <RH_RF95.h>
#include <RHHardwareSPI1.h>
#include <artemis_defs.h>

/* RFM98 FREQUENCY CONFIG */
#define RFM98_FREQ 434.0

/* RFM98 PIN CONFIG */
#define RFM98_CS_PIN T_CS1
#define RFM98_INT_PIN T_GPIO2
#define RFM98_RST_PIN T_GPIO3

/* SPI MISO/MOSI/SCK CONFIG */
#define RFM98_SPI_MISO SPI1_D0
#define RFM98_SPI_MOSI SPI1_D1
#define RFM98_SPI_SCK SPI1_SCLK

/* RFM98 Power Level */
#define RFM98_TX_POWER 23

namespace Artemis
{
    namespace Teensy
    {
        namespace Radio
        {
            class RFM98
            {
            private:
                RH_RF95 rfm98;

            public:
                RFM98(uint8_t slaveSelectPin = RFM98_CS_PIN, uint8_t interruptPin = RFM98_INT_PIN, RHGenericSPI &spi = hardware_spi1);
                void reset();
                bool init();
                void send(const uint8_t *input, size_t length);
                bool recv(PacketComm *packet);
            };
        }
    }
}

#endif  // _RFM98_H

#ifndef RFM69_REGISTERS_H_INCLUDED
#define RFM69_REGISTERS_H_INCLUDED

#include "device/rfm69/rfm69_table.h"
#include "device/rfm69/rfm69.h"


/** @file rfm69_registers.h @brief
    This file contains macro for radiomodule registers.
*/
 
/// @cond
#define REGFIFO             0x00
#define REGOPMODE           0x01

#define SEQUENCEROFF    0x80
#define SEQUENCERON     0x00
#define LISTENON        0x40 
#define LISTENOFF       0x00
#define LISTENABORT     5

#define RX_MODE         0x10
#define TX_MODE         0x0c
#define FS_MODE         0x08
#define STBY_MODE       0x04
#define SLEEP_MODE      0x00

#define REGDATAMODUL        0x02
        
#define CONT_MODE       0x60    // continuous mode without bit synchronizer
#define CONT_SYNCH_MODE 0x40    // continuous mode with bit synchronizer
#define PACKET_MODE     0x00    // packet mode

//#define   OOK             0x08    // OOK modulation (commented to avoid redefine)
//#define   FSK             0x00    // FSK modulation (commented to avoid redefine)

#define GAUSS_BT03      0x03    // Gaussian filter, BT = 0.3, when FSK is on
#define GAUSS_BT05      0x02    // Gaussian filter, BT = 0.3, when FSK is on
#define GAUSS_BT10      0x01    // Gaussian filter, BT = 0.3, when FSK is on
#define NO_SHAPING      0x00    // no Tx data shaping   

#define REGBITRATEMSB       0x03
#define REGBITRATELSB       0x04
#define BITRATEMSB_55555    0x02
#define BITRATELSB_55555    0x40

#define BITRATE_CALC(br_par)    FXOSC/(br_par)      // macro for calculating bitrate 

#define REGFDEVMSB          0x05
#define REGFDEVLSB          0x06
#define DEVMSB_5000    0x00
#define DEVLSB_5000    0x52

#define FDEV_CALC(fdev_par)     (fdev_par)/FSTEP    // macro for calculating deviation frequency

#define REGFRFMSB           0x07
#define REGFRFMID           0x08
#define REGFRFLSB           0x09
#define FRFMSB_915          0xE4  // Default
#define FRFMID_915          0xC0  // Default
#define FRFLSB_915          0x00  // Default

#define FRF_CALC(frf_par)       (frf_par)/FSTEP     // macro for calculating carrier frequency

#define REGOSC1             0x0a

#define RCCALSTART      7   // set this bit to start calibration process of the RC oscillator, RC calibration must be triggered in standby mode
#define RCCALDONE       6   // read 0 if RC calibration in progress, read 0 if calibration is over

#define REGAFCCTRL          0x0b

#define AFCLOWBETAON    5   // if 1 - improved AFC routine is on, if 0 - standard AFC routine is on

#define REGLISTEN1          0x0d

#define LISTENIDLE262M  0xc0
#define LISTENIDLE4M1   0x80
#define LISTENIDLE64U   0x40

#define LISTENRX262M    0x30
#define LISTENRX4M1     0x20
#define LISTENRX64U     0x10

#define LISTENCRITERIA  3

#define LISTENEND1      0x00
#define LISTENEND2      0x02
#define LISTENEND3      0x04
#define LISTENEND4      0x06

#define REGLISTEN2          0x0e
#define REGLISTEN3          0x0f    
#define REGVERSION          0x10    // version code of the chip

#define REGPALEVEL          0x11

#define PA0ON           7           // if 1 - power amplifier 0 on
#define PA1ON           6           // if 1 - power amplifier 1 on
#define PA2ON           5           // if 1 - power amplifier 2 on

#define OUT_POWER_CALC(power_par)   0x1f&(18 + (power_par)) 

#define REGPARAMP           0x12

// see rfm69_table.h to see table values of parameter

#define REGOCP              0x13
#define RF_OCP_OFF          0x0f
#define RF_OCP_ON           0x1A // default

// RegPaLevel
#define RF_PALEVEL_PA0_ON   0x80
#define RF_PALEVEL_PA0_OFF  0x00
#define RF_PALEVEL_PA1_ON   0x40
#define RF_PALEVEL_PA1_OFF  0x80
#define RF_PALEVEL_PA2_ON   0x20
#define RF_PALEVEL_PA2_OFF  0x80

#define OCPON           4   // if 1 - overload current protection is enabled, if 0 - disabled

#define OCP_CURRENT_CALC(ocp_param) 0x0f&(((ocp_param)/5) - 9)  // macro for calculating OCP trimming current in mA

#define REGLNA              0x18

#define LNAZIN          7   // if 1 - LNA input impedance is 200 Ohms, if 0 - LNA input impedance is 50 Ohms

#define LNAGAIN_AUTO    0x00    // LNA gain set by the internal AGC loop
#define LNAGAIN_0DB     0x01    // highest gain
#define LNAGAIN_6DB     0x02    // highest gain - 6dB
#define LNAGAIN_12DB    0x03    // highest gain - 12dB
#define LNAGAIN_24DB    0x04    // highest gain - 24dB
#define LNAGAIN_36DB    0x05    // highest gain - 36dB
#define LNAGAIN_48DB    0x06    // highest gain - 48dB

#define REGRXBW             0x19
#define RXBW_DCCFREQ_000                     0x00
#define RXBW_DCCFREQ_001                     0x20
#define RXBW_DCCFREQ_010                     0x40  // Default
#define RXBW_DCCFREQ_011                     0x60
#define RXBW_DCCFREQ_100                     0x80
#define RXBW_DCCFREQ_101                     0xA0
#define RXBW_DCCFREQ_110                     0xC0
#define RXBW_DCCFREQ_111                     0xE0

#define RXBW_MANT_16                           0x00
#define RXBW_MANT_20                           0x08
#define RXBW_MANT_24                           0x10  // Default

#define RXBW_EXP_0                               0x00
#define RXBW_EXP_1                           0x01
#define RXBW_EXP_2                           0x02
#define RXBW_EXP_3                               0x03
#define RXBW_EXP_4                           0x04
#define RXBW_EXP_5                           0x05  // Default
#define RXBW_EXP_6                             0x06
#define RXBW_EXP_7                             0x07

// see rfm69_table.h to see table values of parameter

#define REGAFCBW            0x1a

// see rfm69_table.h to see table values of parameter

#define REGOOKPEAK          0x1b

#define OOKTHRESFIXED   0x00    // fixed threshold in the OOK data slicer
#define OOKTHRESPEAK    0x40    // peak threshold in the OOK data slicer
#define OOKTHRESAVERAGE 0x80    // average threshold in the OOK data slicer

// see rfm69_table.h to see table values of parameter

#define REGOOKAVG           0x1c // ���� ���������
#define REGOOKFIX           0x1d

#define REGAFCFEI           0x1e

#define FEIDONE         6       // 0 - frequency error indicator is on-going, 1 - FEI is finished 
#define FEISTART        5       // write 1 to start FEI
#define AFCDONE         4       // 0 - AFC is on-going, 1 - AFC is finished
#define AFCAUTOCLEAR    3       // 0 - AFC auto clear off, 1 - auto clear on
#define AFCAUTOON       2       // 0 - AFC auto mode off, 1 - on
#define AFCCLEAR        1       // write 1 to clear AFC value
#define AFCSTART        0       // write 1 to start AFC

#define REGAFCMSB           0x1f
#define REGAFCLSB           0x20

#define AFC_VALUE(afc_par)  (afc_par)*FSTEP     // macro to calculate AFC value in Hz from register value

#define REGFEIMSB           0x21
#define REGFEILSB           0x22

#define FEI_VALUE(fei_par)  (fei_par)*FSTEP     // macro to frequency offset value in Hz from register value

#define REGRSSICONFIG       0x23

#define RSSIDONE        0x02       // 0 - RSSI is on-going, 1 - RSSI is done
#define RSSISTART       0x01     // write 1 to start RSSI measurement

#define REGRSSIVALUE        0x24

#define RSSI_VALUE(rssi_par)    (rssi_par)/2    // macro to calculate RSSI value in dBm from register value

#define REGDIOMAPPING1      0x25

#define DIO0MAP0        0x00
#define DIO0MAP1        0x40
#define DIO0MAP2        0x80
#define DIO0MAP3        0xc0

#define DIO1MAP0        0x00
#define DIO1MAP1        0x10
#define DIO1MAP2        0x20
#define DIO1MAP3        0x30

#define DIO2MAP0        0x00
#define DIO2MAP1        0x04
#define DIO2MAP2        0x08
#define DIO2MAP3        0x0c

#define DIO3MAP0        0x00
#define DIO3MAP1        0x01
#define DIO3MAP2        0x02
#define DIO3MAP3        0x03

#define REGDIOMAPPING2      0x26

#define DIO5MAP0        0x00
#define DIO5MAP1        0x10
#define DIO5MAP2        0x20
#define DIO5MAP3        0x30

#define CLKOUT32M   0x00
#define CLKOUT16M   0x01
#define CLKOUT8M    0x02
#define CLKOUT4M    0x03
#define CLKOUT2M    0x04
#define CLKOUT1M    0x05
#define CLKOUT_RC   0x06    // output frequency of the RC oscillator (automatically enabled)
#define CLKOUT_OFF  0x07    // output frequency is off

#define REGIRQFLAGS1            0x27
#define RFIRQFLAGS1_MODEREADY   0x80
#define RFIRQFLAGS1_RXREADY     0x40
#define RFIRQFLAGS1_TXREADY     0x20
#define RFIRQFLAGS1_PLLLOCK     0x10
#define RFIRQFLAGS1_RSSI        0x08
#define RFIRQFLAGS1_TIMEOUT     0x04
#define RFIRQFLAGS1_AUTOMODE    0x02
#define RFIRQFLAGS1_SYNCADDRESSMATCH    0x01

#define MODEREADY       7
#define RXREADY         6   // Set in Rx mode, after RSSI, AGC and AFC. Cleared when leaving Rx.
#define TXREADY         5   // Set in Tx mode, after PA ramp-up.
#define PLLLOCK         4   // Set (in FS, Rx or Tx) when the PLL is locked. Cleared when it is not.
#define RSSI_I          3   // Set in Rx when the RssiValue exceeds RssiThreshold. Cleared when leaving Rx.
#define TIMEOUT         2   // Set when a timeout occurs. Cleared when leaving Rx or FIFO is emptied.
#define AUTOMODE        1   // Set when entering Intermediate mode. Cleared when exiting Intermediate mode.
#define SYNCADDRMATCH   0   // Set when Sync and Address (if enabled) are detected. Cleared when leaving Rx or FIFO is emptied.

#define REGIRQFLAGS2    0x28
#define RFIRQFLAGS2_FIFOFULL             0x80
#define RFIRQFLAGS2_FIFONOTEMPTY         0x40
#define RFIRQFLAGS2_FIFOLEVEL            0x20
#define RFIRQFLAGS2_FIFOOVERRUN          0x10
#define RFIRQFLAGS2_PACKETSENT           0x08
#define RFIRQFLAGS2_PAYLOADREADY         0x04
#define RFIRQFLAGS2_CRCOK                0x02
#define RFIRQFLAGS2_LOWBAT               0x0

#define REGFIFO         0x00
#define FIFOISFULL      0x80    // Set when FIFO is full (i.e. contains 66 bytes), else cleared.
#define FIFONOTEMPTY    0x40    // Set when FIFO contains at least one byte, else cleared.
#define FIFOLEVEL       0x20    // Set when the number of bytes in the FIFO strictly exceeds FifoThreshold, else cleared.
#define FIFOOVERRUN     0x10    // Set when FIFO overrun occurs. (except in Sleep mode). Flag(s) and FIFO are cleared when this bit is set.
#define PACKETSENT      0x08    // Set in Tx when the complete packet has been sent. Cleared when exiting Tx.
#define PAYLOADREADY    0x04    // Set in Rx when the payload is ready (i.e. last byte received and CRC, if enabled and CrcAutoClearOff is cleared, is Ok). Cleared when FIFO is empty.
#define CRCOK           0x02    // Set in Rx when the CRC of the payload is Ok. Cleared when FIFO is empty.

#define REGRSSITHRESH       0x29

#define RSSI_THRESH_CALC(rssi_parr) (rssi_parr)*2   // macro to calculate trigger level of RSSI interrupt

#define REGRXTIMEOUT1       0x2a
#define REGRXTIMEOUT2       0x2b
#define REGPREAMBLEMSB      0x2c
#define REGPREAMBLELSB      0x2d

#define REGSYNCCONFIG       0x2e

#define SYNC_ON                              0x80  // Default
#define SYNC_OFF                             0x00

#define SYNC_FIFOFILL_AUTO           0x00  // Default -- when sync interrupt occurs
#define SYNC_FIFOFILL_MANUAL     0x40

#define SYNC_SIZE_1                      0x00
#define SYNC_SIZE_2                      0x08
#define SYNC_SIZE_3                      0x10
#define SYNC_SIZE_4                      0x18  // Default
#define SYNC_SIZE_5                      0x20
#define SYNC_SIZE_6                      0x28
#define SYNC_SIZE_7                      0x30
#define SYNC_SIZE_8                      0x38

#define SYNC_TOL_0                           0x00  // Default
#define SYNC_TOL_1                           0x01
#define SYNC_TOL_2                           0x02
#define SYNC_TOL_3                           0x03
#define SYNC_TOL_4                           0x04
#define SYNC_TOL_5                           0x05
#define SYNC_TOL_6                           0x06
#define SYNC_TOL_7                           0x07


#define SYNCSIZE_CALC(syncsize_par)     ( (( (syncsize_par) - 1 ) & 0x07) << 3 )

#if (SYNC_WORD_SIZE > 0)
    #define SYNC_WORD_ON    0x80
#else
    #define SYNC_WORD_ON    0x00
#endif

#define REGSYNCVALUE1       0x2f
#define REGSYNCVALUE2       0x30
#define REGSYNCVALUE3       0x31
#define REGSYNCVALUE4       0x32
#define REGSYNCVALUE5       0x33
#define REGSYNCVALUE6       0x34
#define REGSYNCVALUE7       0x35
#define REGSYNCVALUE8       0x36
#define REGPACKETCONFIG1    0x37

#define PACKETFORMAT_FIXED    0x00   //default
#define PACKETFORMAT_VARIABLE    0x80    

#define ENCODING_OFF    0x00    // off any dc free data encoding/decoding
#define MANCHESTER_ENC  0x20    // manchester encoding enabled
#define DATA_WHITENING  0x40    // data whitening enabled

#define CRCON    0x10 //default
#define CRCAUTOCLEAROFF    0x08       // When CRC check fails, if 0 - FIFO is cleared and packet is received, if 1 - FIFO is not cleared and PayloadReady interrupt issued

#define ADDRESS_OFF         0x00    // off address filtering
#define NODE_ADDRESS_ONLY   0x02    // node address is on, broadcast address is off
#define NODE_BROADCAST_ADDR 0X04    // node address and broadcast addresses are on

#define REGPAYLOADLENGTH    0x38

#define REGNODEADRS         0x39
#define REGBROADCASTADRS    0x3a
#define REGAUTOMODES        0x3b

#define REGFIFOTHRES        0x3c
// RegFifoThresh
#define FIFOTHRESH_TXSTART_FIFOTHRESH          0x00
#define FIFOTHRESH_TXSTART_FIFONOTEMPTY      0x80  // Default

#define FIFOTHRESH_VALUE                             0x0F  // Defaul

#define TXSTARTCOND     7       // if 1 - tx start when FIFO is not empty, if 0 - tx starts when number of bytes exceeds threshold 

#define REGPACKETCONFIG2    0x3d
#define PACKET2_RXRESTARTDELAY_1BIT            0x00  // Default
#define PACKET2_RXRESTARTDELAY_2BITS           0x10
#define PACKET2_RXRESTARTDELAY_4BITS         0x20
#define PACKET2_RXRESTARTDELAY_8BITS         0x30
#define PACKET2_RXRESTARTDELAY_16BITS          0x40
#define PACKET2_RXRESTARTDELAY_32BITS        0x50
#define PACKET2_RXRESTARTDELAY_64BITS        0x60
#define PACKET2_RXRESTARTDELAY_128BITS         0x70
#define PACKET2_RXRESTARTDELAY_256BITS       0x80
#define PACKET2_RXRESTARTDELAY_512BITS       0x90
#define PACKET2_RXRESTARTDELAY_1024BITS      0xA0
#define PACKET2_RXRESTARTDELAY_2048BITS      0xB0
#define PACKET2_RXRESTARTDELAY_NONE            0xC0
#define PACKET2_RXRESTART                            0x04

#define PACKET2_AUTORXRESTART_ON                 0x02  // Default
#define PACKET2_AUTORXRESTART_OFF                0x00

#define PACKET2_AES_ON                                 0x01
#define PACKET2_AES_OFF                              0x00  // Default

// see rfm69_table.h to see table of values of the parameter

#define RESTARTRX       2       // set this bit to restart the receiver in WAIT mode
#define AUTORXRESTARTON 1       // If this bit is set, receiver automstically restarted after RestartRx delay
#define AESON           0       // set this bit to enable AES encryption/decryption

#define REGAESKEY1          0x3e
#define REGAESKEY2          0x3f
#define REGAESKEY3          0x40
#define REGAESKEY4          0x41
#define REGAESKEY5          0x42
#define REGAESKEY6          0x43
#define REGAESKEY7          0x44
#define REGAESKEY8          0x45
#define REGAESKEY9          0x46
#define REGAESKEY10         0x47
#define REGAESKEY11         0x48
#define REGAESKEY12         0x49
#define REGAESKEY13         0x4a
#define REGAESKEY14         0x4b
#define REGAESKEY15         0x4c
#define REGAESKEY16         0x4d

#define REGTEMP1            0x4e

#define TEMPMEASSTART   3   // set this bit to start temperature measurement
#define TEMPMEASRUNNING 2   // 1 - if temperature measurement is on-going, 0 - if complete

#define REGTEMP2            0x4f

/// test registers
#define RETESTLNA           0x58

#define NORMAL_SENS_BOOST_MODE  0x1b
#define HIGH_SENS_BOOST_MODE    0x2d

#define REGTESTPA1          0x5a

#define PA1_NORMAL_RX_MODE      0x55
#define PA1_13DBM_RX_MODE       0x5d
#define PA1_PA0_OR_RX           0x55

#define REGTESTPA2          0x5c

#define PA2_NORMAL_RX_MODE      0x55
#define PA2_13DBM_RX_MODE       0x5d
#define PA2_PA0_OR_RX           0x55

#define REGTESTDAGC         0x6f
#define DAGC_NORMAL              0x00  // Reset value
#define DAGC_IMPROVED_LOWBETA1   0x20  //
#define DAGC_IMPROVED_LOWBETA0   0x30  // Recommended defaul

#define AFC_NORMAL_MODE         0x00
#define AFC_LOW_BETA_ON         0x20
#define AFC_LOW_BETA_OFF        0x00

#define REGTESTAFC          0x71

#define LOW_BETA_AFC_OFFSET_CALC(afcoff_par)    (afcoff_par)*448    // macro to calculate afc offset value for low modulation index systems in Hz from register value
/// @endcond

#endif // RFM69_REGISTERS_H_INCLUDED

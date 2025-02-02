#include <Arduino.h>
#include <vector>
#include <artemis_channels.h>
#include <support/configCosmos.h>
#include <USBHost_t36.h>
#include "artemisbeacons.h"

/* Helper Function Defs */
bool setup_magnetometer(void);
bool setup_imu(void);
void setup_current(void);
void setup_temperature(void);
void read_temperature(void);
void read_current(void);
void read_imu(void);

namespace
{
  PacketComm packet;

  USBHost usb;
  Adafruit_LIS3MDL magnetometer;
  Adafruit_LSM6DSOX imu;
  Adafruit_INA219 current_1(0x40); // Solar 1
  Adafruit_INA219 current_2(0x41); // Solar 2
  Adafruit_INA219 current_3(0x42); // Solar 3
  Adafruit_INA219 current_4(0x43); // Solar 4
  Adafruit_INA219 current_5(0x44); // Battery

  // Current Sensors
  // const char *current_sen_names[ARTEMIS_CURRENT_SENSOR_COUNT] = {"solar_panel_1", "solar_panel_2", "solar_panel_3", "solar_panel_4", "battery_board"};
  Adafruit_INA219 *p[ARTEMIS_CURRENT_SENSOR_COUNT] = {&current_1, &current_2, &current_3, &current_4, &current_5};

  // Temperature Sensors
  const int temps[ARTEMIS_TEMP_SENSOR_COUNT] = {A0, A1, A6, A7, A8, A9, A17};
  // const char *temp_sen_names[ARTEMIS_TEMP_SENSOR_COUNT] = {"solar_panel_1", "solar_panel_2", "solar_panel_3", "solar_panel_4", "battery_board"};

  elapsedMillis sensortimer;
  elapsedMillis uptime;

  const char* data;
}

void setup()
{
  Serial.begin(115200);
  usb.begin();
  pinMode(RPI_ENABLE, OUTPUT);
  digitalWrite(RPI_ENABLE, HIGH);
  delay(3000);

  setup_magnetometer();
  setup_imu();
  setup_current();

  threads.setSliceMillis(10);

  // Threads
  thread_list.push_back({threads.addThread(Artemis::Teensy::Channels::rfm23_channel), "rfm23 thread"});
  thread_list.push_back({threads.addThread(Artemis::Teensy::Channels::rfm98_channel), "rfm98 thread"});
  thread_list.push_back({threads.addThread(Artemis::Teensy::Channels::pdu_channel), "pdu thread"});
  thread_list.push_back({threads.addThread(Artemis::Teensy::Channels::astrodev_channel), "astrodev thread"});
  // thread_list.push_back({threads.addThread(Artemis::Teensy::Channels::rpi_channel), "rpi channel"});
}

void loop()
{
  if (PullQueue(&packet, main_queue, main_queue_mtx))
  {
    if (packet.header.dest == NODES::GROUND_NODE_ID)
    {
      switch (packet.header.radio)
      {
      case ARTEMIS_RADIOS::RFM23:
        PushQueue(&packet, rfm23_queue, rfm23_queue_mtx);
        break;
      case ARTEMIS_RADIOS::ASTRODEV:
        PushQueue(&packet, astrodev_queue, astrodev_queue_mtx);
        break;
      default:
        break;
      }
    }
    else if (packet.header.dest == NODES::RPI_NODE_ID)
    {
      PushQueue(&packet, rpi_queue, rpi_queue_mtx);
    }
    else if (packet.header.dest == NODES::PLEIADES_NODE_ID)
    {
      PushQueue(&packet, rfm98_queue, rfm98_queue_mtx);
    }
    else if (packet.header.dest == NODES::TEENSY_NODE_ID)
    {
      switch (packet.header.type)
      {
      case PacketComm::TypeId::CommandEpsCommunicate:
      case PacketComm::TypeId::CommandEpsMinimumPower:
      case PacketComm::TypeId::CommandEpsReset:
      case PacketComm::TypeId::CommandEpsSetTime:
      case PacketComm::TypeId::CommandEpsState:
      case PacketComm::TypeId::CommandEpsSwitchName:
      case PacketComm::TypeId::CommandEpsSwitchNames:
      case PacketComm::TypeId::CommandEpsSwitchNumber:
      case PacketComm::TypeId::CommandEpsSwitchStatus:
      case PacketComm::TypeId::CommandEpsWatchdog:
      {
        PushQueue(&packet, pdu_queue, pdu_queue_mtx);
        break;
      }
      case PacketComm::TypeId::CommandPing:
      {
        uint8_t temp_node = packet.header.orig;
        packet.header.orig = packet.header.dest;
        packet.header.dest = temp_node;
        packet.header.type = PacketComm::TypeId::DataPong;
        packet.data.resize(0);
        data = "Pong";
        for (size_t i = 0; i < strlen(data); i++)
        {
          packet.data.push_back(data[i]);
        }
        if (packet.header.radio == ARTEMIS_RADIOS::RFM23)
          PushQueue(&packet, rfm23_queue, rfm23_queue_mtx);
        else if (packet.header.radio == ARTEMIS_RADIOS::RFM98)
          PushQueue(&packet, rfm98_queue, rfm98_queue_mtx);
        else if (packet.header.radio == ARTEMIS_RADIOS::ASTRODEV)
          PushQueue(&packet, astrodev_queue, astrodev_queue_mtx);
        break;
      }
      default:
        break;
      }
    }
  }

  if (sensortimer > 5000)
  {
    sensortimer -= 5000;
    read_temperature();
    read_current();
    read_imu();
  }
  threads.delay(10);
}

/* Helper Functions */
bool setup_magnetometer(void)
{
  if (!magnetometer.begin_I2C())
  {
    return false;
  }

  magnetometer.setPerformanceMode(LIS3MDL_LOWPOWERMODE);
  magnetometer.setDataRate(LIS3MDL_DATARATE_0_625_HZ);
  magnetometer.setRange(LIS3MDL_RANGE_16_GAUSS);
  magnetometer.setOperationMode(LIS3MDL_CONTINUOUSMODE);

  return true;
}

bool setup_imu(void)
{
  if (!imu.begin_I2C())
  {
    return false;
  }
  imu.setAccelRange(LSM6DS_ACCEL_RANGE_16_G);
  imu.setGyroRange(LSM6DS_GYRO_RANGE_2000_DPS);
  imu.setAccelDataRate(LSM6DS_RATE_6_66K_HZ);
  imu.setGyroDataRate(LSM6DS_RATE_6_66K_HZ);

  return true;
}

void setup_current(void) // go through library and see what we need to configure and callibrate
{
  current_1.begin(&Wire2);
  current_2.begin(&Wire2);
  current_3.begin(&Wire2);
  current_4.begin(&Wire2);
  current_5.begin(&Wire2);

  return;
}

void setup_temperature(void)
{
  for (const int pin : temps)
  {
    pinMode(pin, INPUT);
  }

  return;
}

void read_temperature(void) // future make this its own library
{
  temperaturebeacon beacon;
  beacon.deci = uptime;
  for (int i = 0; i < ARTEMIS_TEMP_SENSOR_COUNT; i++)
  {
    const int reading = analogRead(temps[i]);
    float voltage = reading * AREF_VOLTAGE;
    voltage /= 1024.0;
    const float temperatureF = (voltage * 1000) - 58;
    beacon.temperatureC[i] = (temperatureF - 32) / 1.8;
  }
  packet.header.orig = NODES::TEENSY_NODE_ID;
  packet.header.dest = NODES::GROUND_NODE_ID;
  packet.header.radio = ARTEMIS_RADIOS::RFM23;
  packet.header.type = PacketComm::TypeId::DataBeacon;
  packet.data.resize(sizeof(beacon));
  memcpy(packet.data.data(), &beacon, sizeof(beacon));
  PushQueue(&packet, rfm23_queue, rfm23_queue_mtx);
}

void read_current(void)
{
  currentbeacon beacon;
  beacon.deci = uptime;
  for (int i = 0; i < ARTEMIS_CURRENT_SENSOR_COUNT; i++)
  {
    beacon.busvoltage[i] = (p[i]->getBusVoltage_V());
    beacon.current[i] = (p[i]->getCurrent_mA());
    beacon.power[i] = (p[i]->getPower_mW());
  }
  packet.header.orig = NODES::TEENSY_NODE_ID;
  packet.header.dest = NODES::GROUND_NODE_ID;
  packet.header.radio = ARTEMIS_RADIOS::RFM23;
  packet.header.type = PacketComm::TypeId::DataBeacon;
  packet.data.resize(sizeof(beacon));
  memcpy(packet.data.data(), &beacon, sizeof(beacon));
  PushQueue(&packet, rfm23_queue, rfm23_queue_mtx);
}

void read_imu(void)
{
  imubeacon beacon;
  beacon.deci = uptime;

  sensors_event_t event;
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  imu.getEvent(&accel, &gyro, &temp);
  magnetometer.getEvent(&event);
  beacon.magx = (event.magnetic.x);
  beacon.magy = (event.magnetic.y);
  beacon.magz = (event.magnetic.z);
  beacon.accelx = (accel.acceleration.x);
  beacon.accely = (accel.acceleration.y);
  beacon.accelz = (accel.acceleration.z);
  beacon.gyrox = (gyro.gyro.x);
  beacon.gyroy = (gyro.gyro.y);
  beacon.gyroz = (gyro.gyro.z);
  beacon.imutemp = (temp.temperature);

  packet.header.orig = NODES::TEENSY_NODE_ID;
  packet.header.dest = NODES::GROUND_NODE_ID;
  packet.header.radio = ARTEMIS_RADIOS::RFM23;
  packet.header.type = PacketComm::TypeId::DataBeacon;
  packet.data.resize(sizeof(beacon));
  memcpy(packet.data.data(), &beacon, sizeof(beacon));
  PushQueue(&packet, rfm23_queue, rfm23_queue_mtx);
}

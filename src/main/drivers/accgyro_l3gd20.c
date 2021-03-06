/* 
 * This file is part of RaceFlight. 
 * 
 * RaceFlight is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * 
 * RaceFlight is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with RaceFlight.  If not, see <http://www.gnu.org/licenses/>.
 * You should have received a copy of the GNU General Public License 
 * along with RaceFlight.  If not, see <http://www.gnu.org/licenses/>.
 */ 
#include <stdbool.h>
#include <stdint.h>
#include "platform.h"
#include "build_config.h"
#include "debug.h"
#include "common/maths.h"
#include "system.h"
#include "io.h"
#include "bus_spi.h"
#include "sensor.h"
#include "accgyro.h"
#include "accgyro_l3gd20.h"
static IO_t mpuSpil3gd20CsPin = IO_NONE;
#define DISABLE_MPUL3GD20 IOHi(mpuSpil3gd20CsPin)
#define ENABLE_MPUL3GD20 IOLo(mpuSpil3gd20CsPin)
#define READ_CMD ((uint8_t)0x80)
#define MULTIPLEBYTE_CMD ((uint8_t)0x40)
#define DUMMY_BYTE ((uint8_t)0x00)
#define CTRL_REG1_ADDR 0x20
#define CTRL_REG4_ADDR 0x23
#define CTRL_REG5_ADDR 0x24
#define OUT_TEMP_ADDR 0x26
#define OUT_X_L_ADDR 0x28
#define MODE_ACTIVE ((uint8_t)0x08)
#define OUTPUT_DATARATE_1 ((uint8_t)0x00)
#define OUTPUT_DATARATE_2 ((uint8_t)0x40)
#define OUTPUT_DATARATE_3 ((uint8_t)0x80)
#define OUTPUT_DATARATE_4 ((uint8_t)0xC0)
#define AXES_ENABLE ((uint8_t)0x07)
#define BANDWIDTH_1 ((uint8_t)0x00)
#define BANDWIDTH_2 ((uint8_t)0x10)
#define BANDWIDTH_3 ((uint8_t)0x20)
#define BANDWIDTH_4 ((uint8_t)0x30)
#define FULLSCALE_250 ((uint8_t)0x00)
#define FULLSCALE_500 ((uint8_t)0x10)
#define FULLSCALE_2000 ((uint8_t)0x20)
#define BLOCK_DATA_UPDATE_CONTINUOUS ((uint8_t)0x00)
#define BLE_MSB ((uint8_t)0x40)
#define BOOT ((uint8_t)0x80)
static void l3gd20SpiInit(SPI_TypeDef *SPIx)
{
    UNUSED(SPIx);
#ifdef L3GD20_CS_PIN
    mpuSpil3gd20CsPin = IOGetByTag(IO_TAG(L3GD20_CS_PIN));
#endif
    IOInit(mpuSpil3gd20CsPin, OWNER_SYSTEM, RESOURCE_SPI);
    IOConfigGPIO(mpuSpil3gd20CsPin, SPI_IO_CS_CFG);
    spiSetDivisor(L3GD20_SPI, SPI_STANDARD_CLOCK);
}
void l3gd20GyroInit(uint8_t lpf)
{
    UNUSED(lpf);
    l3gd20SpiInit(L3GD20_SPI);
    ENABLE_MPUL3GD20;
    spiTransferByte(L3GD20_SPI, CTRL_REG5_ADDR);
    spiTransferByte(L3GD20_SPI, BOOT);
    DISABLE_MPUL3GD20;
    delayMicroseconds(100);
    ENABLE_MPUL3GD20;
    spiTransferByte(L3GD20_SPI, CTRL_REG1_ADDR);
    spiTransferByte(L3GD20_SPI, MODE_ACTIVE | OUTPUT_DATARATE_3 | AXES_ENABLE | BANDWIDTH_3);
    DISABLE_MPUL3GD20;
    delayMicroseconds(1);
    ENABLE_MPUL3GD20;
    spiTransferByte(L3GD20_SPI, CTRL_REG4_ADDR);
    spiTransferByte(L3GD20_SPI, BLOCK_DATA_UPDATE_CONTINUOUS | BLE_MSB | FULLSCALE_2000);
    DISABLE_MPUL3GD20;
    delay(100);
}
static bool l3gd20GyroRead(int16_t *gyroADC)
{
    uint8_t buf[6];
    ENABLE_MPUL3GD20;
    spiTransferByte(L3GD20_SPI, OUT_X_L_ADDR | READ_CMD | MULTIPLEBYTE_CMD);
    uint8_t index;
    for (index = 0; index < sizeof(buf); index++) {
        buf[index] = spiTransferByte(L3GD20_SPI, DUMMY_BYTE);
    }
    DISABLE_MPUL3GD20;
    gyroADC[0] = (int16_t)((buf[0] << 8) | buf[1]);
    gyroADC[1] = (int16_t)((buf[2] << 8) | buf[3]);
    gyroADC[2] = (int16_t)((buf[4] << 8) | buf[5]);
    return true;
}
#define L3GD20_GYRO_SCALE_FACTOR 0.07f
bool l3gd20Detect(gyro_t *gyro)
{
    gyro->init = l3gd20GyroInit;
    gyro->read = l3gd20GyroRead;
    gyro->scale = L3GD20_GYRO_SCALE_FACTOR;
    return true;
}

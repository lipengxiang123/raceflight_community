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
 */ 
#pragma once 
       
#define TARGET_BOARD_IDENTIFIER "IFF3"
#define LED0 PB3
#define BEEPER PC15
#define LED0_GPIO GPIOB
#define LED0_PIN Pin_3
#define LED0_PERIPHERAL RCC_AHBPeriph_GPIOB
#define BEEP_GPIO GPIOC
#define BEEP_PIN Pin_15
#define BEEP_PERIPHERAL RCC_AHBPeriph_GPIOC
#define BEEPER_INVERTED 
#define USABLE_TIMER_CHANNEL_COUNT 17
#define EXTI_CALLBACK_HANDLER_COUNT 2
#define USE_MPU_DATA_READY_SIGNAL 
#define ENSURE_MPU_DATA_READY_IS_LOW 
#define USE_EXTI 
#define USE_MAG_DATA_READY_SIGNAL 
#define ENSURE_MAG_DATA_READY_IS_HIGH 
#define GYRO 
#define USE_GYRO_MPU6050 
#define GYRO_MPU6050_ALIGN CW270_DEG
#define ACC 
#define USE_ACC_MPU6050 
#define ACC_MPU6050_ALIGN CW270_DEG
#define BARO 
#define USE_BARO_MS5611 
#define USE_BARO_BMP085 
#define MAG 
#define USE_MAG_AK8975 
#define USE_MAG_HMC5883 
#define MAG_HMC5883_ALIGN CW270_DEG
#define USE_FLASHFS 
#define USE_FLASH_M25P16 
#define SONAR 
#define USE_USART1 
#define USE_USART2 
#define USE_USART3 
#define USE_SOFTSERIAL1 
#define USE_SOFTSERIAL2 
#define SERIAL_PORT_COUNT 5
#ifndef UART1_GPIO
#define UART1_TX_PIN GPIO_Pin_9
#define UART1_RX_PIN GPIO_Pin_10
#define UART1_GPIO GPIOA
#define UART1_GPIO_AF GPIO_AF_7
#define UART1_TX_PINSOURCE GPIO_PinSource9
#define UART1_RX_PINSOURCE GPIO_PinSource10
#endif
#define UART2_TX_PIN GPIO_Pin_14
#define UART2_RX_PIN GPIO_Pin_15
#define UART2_GPIO GPIOA
#define UART2_GPIO_AF GPIO_AF_7
#define UART2_TX_PINSOURCE GPIO_PinSource14
#define UART2_RX_PINSOURCE GPIO_PinSource15
#ifndef UART3_GPIO
#define UART3_TX_PIN GPIO_Pin_10
#define UART3_RX_PIN GPIO_Pin_11
#define UART3_GPIO_AF GPIO_AF_7
#define UART3_GPIO GPIOB
#define UART3_TX_PINSOURCE GPIO_PinSource10
#define UART3_RX_PINSOURCE GPIO_PinSource11
#endif
#define SOFTSERIAL_1_TIMER TIM3
#define SOFTSERIAL_1_TIMER_RX_HARDWARE 4
#define SOFTSERIAL_1_TIMER_TX_HARDWARE 5
#define SOFTSERIAL_2_TIMER TIM3
#define SOFTSERIAL_2_TIMER_RX_HARDWARE 6
#define SOFTSERIAL_2_TIMER_TX_HARDWARE 7
#define ESC_1WIRE 
#define USE_I2C 
#define I2C_DEVICE (I2CDEV_1)
#define USE_SPI 
#define USE_SPI_DEVICE_2 
#define SPI2_NSS_PIN PB12
#define SPI2_SCK_PIN PB13
#define SPI2_MISO_PIN PB14
#define SPI2_MOSI_PIN PB15
#define M25P16_CS_GPIO GPIOB
#define M25P16_CS_PIN PB12
#define M25P16_SPI_INSTANCE SPI2
#define USE_ADC 
#define BOARD_HAS_VOLTAGE_DIVIDER 
#define ADC_INSTANCE ADC2
#define ADC_DMA_CHANNEL DMA2_Channel1
#define ADC_AHB_PERIPHERAL RCC_AHBPeriph_DMA2
#define VBAT_ADC_PIN PA4
#define VBAT_ADC_CHANNEL ADC_Channel_1
#define CURRENT_METER_ADC_PIN PA5
#define CURRENT_METER_ADC_CHANNEL ADC_Channel_2
#define RSSI_ADC_PIN PB2
#define RSSI_ADC_CHANNEL ADC_Channel_12
#define LED_STRIP 
#define LED_STRIP_TIMER TIM1
#define USE_LED_STRIP_ON_DMA1_CHANNEL2 
#define WS2811_GPIO GPIOA
#define WS2811_GPIO_AHB_PERIPHERAL RCC_AHBPeriph_GPIOA
#define WS2811_GPIO_AF GPIO_AF_6
#define WS2811_PIN GPIO_Pin_8
#define WS2811_PIN_SOURCE GPIO_PinSource8
#define WS2811_TIMER TIM1
#define WS2811_TIMER_APB2_PERIPHERAL RCC_APB2Periph_TIM1
#define WS2811_DMA_CHANNEL DMA1_Channel2
#define WS2811_IRQ DMA1_Channel2_IRQn
#define BLACKBOX 
#define DISPLAY 
#define GPS 
#define GTUNE 
#define SERIAL_RX 
#define TELEMETRY 
#define USE_SERVOS 
#define USE_CLI 
#define SPEKTRUM_BIND 
#define BIND_PORT GPIOB
#define BIND_PIN Pin_11
#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTF 0xffff

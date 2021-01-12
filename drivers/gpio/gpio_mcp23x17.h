/*
 * Copyright (c) 2020 Geanix ApS
 * Copyright (c) 2020 Prevas A/S (I2C added)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Header file for the MCP23x17 driver.
 */

#ifndef ZEPHYR_DRIVERS_GPIO_GPIO_MCP23X17_H_
#define ZEPHYR_DRIVERS_GPIO_GPIO_MCP23X17_H_

#include <kernel.h>

#include <drivers/gpio.h>
#include <drivers/spi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Register definitions */
#define REG_IODIR_PORTA                 0x00
#define REG_IODIR_PORTB                 0x01
#define REG_IPOL_PORTA                  0x02
#define REG_IPOL_PORTB                  0x03
#define REG_GPINTEN_PORTA               0x04
#define REG_GPINTEN_PORTB               0x05
#define REG_DEFVAL_PORTA                0x06
#define REG_DEFVAL_PORTB                0x07
#define REG_INTCON_PORTA                0x08
#define REG_INTCON_PORTB                0x09
#define REG_GPPU_PORTA                  0x0C
#define REG_GPPU_PORTB                  0x0D
#define REG_INTF_PORTA                  0x0E
#define REG_INTF_PORTB                  0x0F
#define REG_INTCAP_PORTA                0x10
#define REG_INTCAP_PORTB                0x11
#define REG_GPIO_PORTA                  0x12
#define REG_GPIO_PORTB                  0x13
#define REG_OLAT_PORTA                  0x14
#define REG_OLAT_PORTB                  0x15

#define MCP23S17_ADDR                   0x40
#define MCP23S17_READBIT                0x01

/** Store the port 0/1 data for each register pair. */
union gpio_mcp23x17_port_data {
	uint16_t all;
	uint8_t port[2];
	uint8_t byte[2];
};


/** Configuration data */
struct mcp23x17_config {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_config common;

#if defined(CONFIG_MCP23X17_DEV_TYPE_I2C)
	/** The master I2C device's name */
	const char *const i2c_master_dev_name;
	/** The slave address of the chip */
	uint16_t i2c_slave_addr;

	uint8_t stride[2];
#elif defined(CONFIG_MCP23X17_DEV_TYPE_SPI)
	const char *const spi_dev_name;
	const uint16_t slave;
	const uint32_t freq;
	const char *const cs_dev;
	const uint32_t cs_pin;
	const uint8_t cs_flags;
#endif  /* CONFIG_MCP23X17_DEV_TYPE_ */
};

/** Runtime driver data */
struct mcp23x17_drv_data {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_config data;

#if defined(CONFIG_MCP23X17_DEV_TYPE_I2C)
	/** Master I2C device */
	const struct device *i2c_master;
#elif defined(CONFIG_MCP23X17_DEV_TYPE_SPI)
	/** Master SPI device */
	const struct device *spi;
	struct spi_config spi_cfg;
	struct spi_cs_control mcp23s17_cs_ctrl;
#endif  /* CONFIG_MCP23X17_DEV_TYPE_ */

	struct k_sem lock;

	struct {
		uint16_t iodir;
		uint16_t ipol;
		uint16_t gpinten;
		uint16_t defval;
		uint16_t intcon;
		uint16_t iocon;
		uint16_t gppu;
		uint16_t intf;
		uint16_t intcap;
		uint16_t gpio;
		uint16_t olat;
	} reg_cache;
};

#ifdef __cplusplus
}
#endif

#endif  /* ZEPHYR_DRIVERS_GPIO_GPIO_MCP23X17_H_ */

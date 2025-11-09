/*
 * Copyright (c) 2023 TOKITA Hiroshi
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* RPI 2040 has a single sensor */
static const struct device *const sensor;

static int print_die_temperature(const struct device *dev) {
  struct sensor_value val;
  int rc;

  /* fetch sensor samples */
  rc = sensor_sample_fetch(dev);
  if (rc) {
    printk("Failed to fetch sample (%d)\n", rc);
    return rc;
  }

  rc = sensor_channel_get(dev, SENSOR_CHAN_DIE_TEMP, &val);
  if (rc) {
    printk("Failed to get data (%d)\n", rc);
    return rc;
  }

  printk("CPU Die temperature[%s]: %.1f °C\n", dev->name,
         sensor_value_to_double(&val));
  return 0;
}

int main(void) {
  k_msleep(500);
  int rc;

  if (!device_is_ready(sensor)) {
    printk("sensor: device %s not ready.\n", sensor->name);
    return 0;
  }

  while (1) {
    rc = print_die_temperature(sensor);
    if (rc < 0) {
      return 0;
    }
    k_msleep(1000);
  }
  return 0;
}

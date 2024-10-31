
#ifndef _STM32_MLX90640_H_
#define _STM32_MLX90640_H_

// change the hal header to the corresponding one
#include "stm32g4xx_hal.h"
#include "headers/MLX90640_API.h"

#define MLX90640_I2CADDR_DEFAULT  0x33    // default i2c address
#define MLX90640_DEVICEID1        0x2407  // id register (2407: ID1, 2408: ID2, 2409: ID3)

#define OPENAIR_TA_SHIFT          8       // default 8 degree offset from ambient air

class MLX90640 {
public:
  MLX90640();
  int begin( I2C_HandleTypeDef *mlx_hi2c, uint8_t mlx_i2c_addr = MLX90640_I2CADDR_DEFAULT );

  uint16_t serialNumber[3];               // unique serial number read from device @(0x2407)

private:
  I2C_HandleTypeDef *hi2c;
  uint8_t addr;

  int MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data);
  int MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data);
};

#endif      // _STM32_MLX90640_H_

#include "stm32_mlx90640.hpp"

MLX90640::MLX90640();

int MLX90640::begin( I2C_HandleTypeDef *mlx_hi2c, uint8_t mlx_i2c_addr = MLX90640_I2CADDR_DEFAULT ) {
  hi2c = mlx_hi2c;
  addr = mlx_i2c_addr;

  // current expected value: 130C_056B_018A
  if (MLX90640_I2CRead(addr, MLX90640_DEVICEID1, 3, serialNumber) != HAL_OK) {
    return -1;
  }

  return 0;
}

int MLX90640::MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data) {
  if (HAL_I2C_Mem_Read( hi2c,
                        slaveAddr << 1,
                        startAddress,
                        I2C_MEMADD_SIZE_16BIT,
                        (uint8_t *) data,
                        nMemAddressRead * 2,
                        HAL_MAX_DELAY ) != HAL_OK) {
    return -1;
  }

  for (uint16_t i = 0; i < nMemAddressRead; i++) {
    data[i] = __builtin_bswap16(data[i]);
  }

  return 0;
}

int MLX90640::MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data) {
  uint8_t cmd[2];
  cmd[0] = data >> 8;       // high byte
  cmd[1] = data & 0xFF;     // low byte

  if (HAL_I2C_Mem_Write( hi2c,
                         slaveAddr << 1,
                         writeAddress,
                         I2C_MEMADD_SIZE_16BIT,
                         cmd,
                         2,
                         HAL_MAX_DELAY) != HAL_OK) {
    return -1;
  }

  uint16_t dataCheck = 0;
  if (MLX90640_I2CRead(slaveAddr, writeAddress, 1, &dataCheck) != HAL_OK) {
    return -1;
  }

  if (dataCheck != data) {
    return -2;
  }

  return 0;
}

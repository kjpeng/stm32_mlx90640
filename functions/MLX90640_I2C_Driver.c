
#include "MLX90640_I2C_Driver.h"


int MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data) {
  // HAL_StatusTypeDef HAL_I2C_Mem_Read(
  //   I2C_HandleTypeDef *hi2c,
  //   uint16_t DevAddress,
  //   uint16_t MemAddress,
  //   uint16_t MemAddSize,
  //   uint8_t * pData,
  //   uint16_t Size,
  //   uint32_t Timeout
  // )

  if (HAL_I2C_Mem_Read(&hi2c2,
                       slaveAddr << 1,
                       startAddress,
                       I2C_MEMADD_SIZE_16BIT,
                       (uint8_t *) data,
                       nMemAddressRead * 2,
                       HAL_MAX_DELAY) != HAL_OK) {
    return -1;
  }

  for (uint16_t i = 0; i < nMemAddressRead; i++) {
    data[i] = __builtin_bswap16(data[i]);
  }

  return 0;
}

int MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data) {
  uint8_t cmd[2];
  cmd[0] = data >> 8;
  cmd[1] = data & 0xFF;

  // HAL_StatusTypeDef HAL_I2C_Mem_Write(
  //   I2C_HandleTypeDef * hi2c,
  //   uint16_t DevAddress,
  //   uint16_t MemAddress,
  //   uint16_t MemAddSize,
  //   uint8_t * pData,
  //   uint16_t Size,
  //   uint32_t Timeout
  // )

  if (HAL_I2C_Mem_Write(&hi2c2,
                        slaveAddr << 1,
                        writeAddress,
                        I2C_MEMADD_SIZE_16BIT,
                        cmd,
                        2,
                        HAL_MAX_DELAY) != HAL_OK) {
    return -1;
  }

  uint16_t dataCheck = 0;
  if (MLX90640_I2CRead(slaveAddr, writeAddress, 1, &dataCheck) != HAL_OK)
    return -2;

  if (dataCheck != data)
    return -3;

  return 0;
}

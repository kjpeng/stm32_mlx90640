# STM32_MLX90640
Creates an STM32 library for use with the MLX90640 (IR thermal sensor),
based off of [Melexis mlx90640-library](https://github.com/melexis/mlx90640-library) and [Adafruit_MLX90640](https://github.com/adafruit/Adafruit_MLX90640), as well as
@imliubo's [MLX90640-With-STM32](https://github.com/imliubo/MLX90640-With-STM32/) library. Specifically, this is for use
with my [BasicBoard-STM32G473CET6 board](https://github.com/kjpeng/BasicBoard-STM32G473CET6), which uses I2C2 pins
PA8 (I2C2_SDA) and PA9 (I2C2_SCL), though that is set in the main.cpp file,
so this library can be adapted for use with other boards as well, as long as 
instances of I2C_HandleTypeDef hi2c2 is changed to reflect the correct I2C interface.

# BigRobot

Software for new BigRobot 3kg

HW PinOut

Function | Arduino Pin | Device | Arduino Pin | Device Pin | Function
--- | --- | --- | --- | --- | ---
TX | D0 |  |  |  |
RX | D1 |  |  |  |
INT0 | D2 | VNH5019 | D2 | M1INA | Motor 1 direction input A
INT1/PWM | D3 | StartStop | D0-D13 | Start | Start signal equal High
| | D4 | VNH5019 | D4 | M1INB | Motor 1 direction input B
PWM | D5 | StartStop | D0-D13 | Stop | Kill signal equal Low
PWM | D6 | VNH5019 | D6 | M1EN/DIAG | Motor 1 enable input/fault output
| | D7 | VNH5019 | D7 | M2INA | Motor 2 direction input A
| | D8 | VNH5019 | D8 | M2INB | Motor 2 direction input B
PWM | D9 | VNH5019 | D9 | M1PWM | Motor 1 speed input
SPI-SS/PWM | D10 | VNH5019 | D10 | M2PWM | Motor 2 speed input
SPI-MOSI/PWM | D11 | Button | D0-D13 | DOUT | Button press
SPI-MISO | D12 | VNH5019 | D12 | M2EN/DIAG | Motor 2 enable input/fault output
SPI-SCK | D13 | LED | D13 | DIN | Blink led
ADC0 | A0 | VNH5019 | A0 | M1CS | Motor 1 current sense output
ADC1 | A1 | VNH5019 | A1 | M2CS | Motor 2 current sense output
ADC2 | A2 | QTR-1A | A0-A5 | OUT | analog voltage output
ADC3 | A3 | QTR-1A | A0-A5 | OUT | analog voltage output
ADC4/I2C-SDA | A4 | VL53L0X | A4 | SDA | Level-shifted I²C data line: HIGH is VIN, LOW is 0 V
ADC5/I2C-SCL | A5 | VL53L0X | A5 | SCL | Level-shifted I²C clock line: HIGH is VIN, LOW is 0 V

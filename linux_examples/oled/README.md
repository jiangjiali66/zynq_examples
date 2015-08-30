# oled屏幕demo

本实验有2个模式，SPI模式、GPIO模拟模式，通过xil_oled.h里面OLED_USE_SPI的宏定义实现切换。<\br>
SPI模式屏幕连接<\br>
SCL ----- MIO12<\br>
SDA ----- MIO10<\br>
RST ----- MIO0<\br>
D/C ----- MIO9<\br>
GPIO模拟模式幕连接<\br>
SCL ----- U14<\br>
SDA ----- P14<\br>
RST ----- T15<\br>
D/C ----- T14<\br>

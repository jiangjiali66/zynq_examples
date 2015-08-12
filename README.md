# zynq_examples
实验环境：vivado2014.4
开发板系统：linaro（其他linux也可以）

1.生成bitstream
打开vivado2014.4在命令下输入以下命令
cd ./zynq_examples
source ./system_pro.tcl
等待生成完毕
2.通过sdk生成BOOT.bin
先在vivado上导出bitstream并Launch SDK
[vivado] File->Export->Export Hardware...
打钩Include bitstream
点击ok
[vivado] File->Launch SDK
使用SDK建立fsbl工程，并生成BOOT.bin
[SDK] File->New->Application Project 
输入Project name，点击下一步在Available Templates选择Zynq FSBL
等待它自动编译fsbl.elf
右键FSBL工程选择Create Zynq Boot Image
点击右下角Add按钮，添加u-boot.elf
然后点击Create Image
在工程目录下bootimage文件有BOOT.bin生成
2.linux_examples
example的目录结构为
.
├── gpio
│   ├── main.c
│   └── Makefile
├── pwm
│   ├── main.c
│   └── makefile
└── xlib
    ├── xil_gpio.c
    ├── xil_gpio.h
    ├── xil_io.c
    ├── xil_io.h
    ├── xil_pwm.c
    ├── xil_pwm.h
    └── xil_types.h
xlib为库文件源码，其他为具体应用源码

# zynq_examples
实验环境：vivado2014.4</br>
开发板系统：linaro（其他linux也可以)</br>
linaro下载地址：<code>http://pan.baidu.com/s/1dDrs4bJ</code></br>
内核下载地址：<code>https://github.com/Xilinx/linux-xlnx/tree/xilinx-v2014.4</code></br>
device tree下载地址: <code>https://github.com/Xilinx/device-tree-xlnx/tree/xilinx-v2015.1</code></br>
uboot下载地址：<code>https://github.com/Xilinx/u-boot-xlnx/tree/xilinx-v2015.1</code></br>
</br>
<h2>1.生成bitstream</h2></br>
打开vivado2014.4在命令下输入以下命令</br>
<code>cd ./zynq_examples</code></br>
<code>source ./system_pro.tcl</code></br>
等待生成完毕</br>
<h2>2.通过sdk生成BOOT.bin</h2></br>
先在vivado上导出bitstream并Launch SDK</br>
<code>[vivado] File->Export->Export Hardware...</code></br>
打钩Include bitstream</br>
点击ok</br>
<code>[vivado] File->Launch SDK</code></br>
使用SDK建立fsbl工程，并生成BOOT.bin</br>
<code>[SDK] File->New->Application Project </code></br>
输入Project name，点击下一步在Available Templates选择Zynq FSBL</br>
等待它自动编译fsbl.elf</br>
右键FSBL工程选择Create Zynq Boot Image</br>
点击右下角Add按钮，添加u-boot.elf</br>
然后点击Create Image</br>
在工程目录下bootimage文件有BOOT.bin生成</br>
<h2>3.linux_examples</h2></br>
example的目录结构为</br>
<pre>
.
├── devicetree
│   ├── devicetree.dtb
│   ├── pl.dtsi
│   ├── skeleton.dtsi
│   ├── system.dts
│   └── zynq-7000.dtsi
├── hardware_pro
│   └── workshop_v1_0
├── linux_dev
│   └── xdma
│       ├── Makefile
│       ├── xdma.c
│       └── xdma.h
├── linux_examples
│   ├── axi-dma
│   │   ├── main.c
│   │   ├── Makefile
│   │   └── drivers-session4-dma-4public.pdf
│   ├── devmem
│   │   ├── devmem.c
│   │   └── Makefile
│   ├── ds18b20
│   │   ├── ds18b20.c
│   │   ├── ds18b20.h
│   │   ├── main.c
│   │   └── Makefile
│   ├── gpio
│   │   ├── main.c
│   │   └── Makefile
│   ├── i2c
│   │   ├── eeprom.c
│   │   └── Makefile
│   ├── iio_xadc
│   │   ├── main.c
│   │   └── Makefile
│   ├── mmult
│   │   ├── main.c
│   │   ├── Makefile
│   │   ├── xil_mmult.c
│   │   └── xil_mmult.h
│   ├── oled
│   │   ├── main.c
│   │   ├── Makefile
│   │   ├── xil_oled.c
│   │   └── xil_oled.h
│   ├── pwm
│   │   ├── main.c
│   │   └── Makefile
│   ├── spi
│   │   ├── main.c
│   │   └── Makefile
│   ├── uart
│   │   ├── main.c
│   │   └── Makefile
│   └── xlib
│       ├── xil_dma.c
│       ├── xil_dma.h
│       ├── xil_gpio.c
│       ├── xil_gpio.h
│       ├── xil_i2c.c
│       ├── xil_i2c.h
│       ├── xil_io.c
│       ├── xil_io.h
│       ├── xil_oled.c
│       ├── xil_oled.h
│       ├── xil_pwm.c
│       ├── xil_pwm.h
│       ├── xil_spi.c
│       ├── xil_spi.h
│       ├── xil_types.h
│       ├── xil_uart.c
│       ├── xil_uart.h
│       ├── xil_wrapper.c
│       └── xil_wrapper.h
├── linux_img
│   ├── BOOT.bin
│   ├── devicetree.dtb
│   ├── u-boot.elf
│   └── uImage
├── makeallclean.sh
├── README.md
└── ZYBO_RM_B_V6.pdf
</pre>
<h5>
hardware_pro：硬件工程的TCL</br>
linux_dev：例程需要加载的驱动</br>
linux_img：编译好的fat分区镜像</br>
linux_examples：例程文件夹，xlib为库文件源码，其他为具体demo的源码</br>
</h5>

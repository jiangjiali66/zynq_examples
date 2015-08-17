# zynq_examples
实验环境：vivado2014.4</br>
开发板系统：linaro（其他linux也可以)</br>
内核下载地址：<code>https://github.com/Xilinx/linux-xlnx/tree/xilinx-v2014.4</br></code>
device tree下载地址: <code>https://github.com/Xilinx/device-tree-xlnx/tree/xilinx-v2015.1</br></code>
uboot下载地址：<code>https://github.com/Xilinx/u-boot-xlnx/tree/xilinx-v2015.1</br></code>
</br>
<h2>1.生成bitstream</h2></br>
打开vivado2014.4在命令下输入以下命令</br>
<code>cd ./zynq_examples</br></code>
<code>source ./system_pro.tcl</br></code>
等待生成完毕</br>
<h2>2.通过sdk生成BOOT.bin</h2></br>
先在vivado上导出bitstream并Launch SDK</br>
<code>[vivado] File->Export->Export Hardware...</br></code>
打钩Include bitstream</br>
点击ok</br>
<code>[vivado] File->Launch SDK</br></code>
使用SDK建立fsbl工程，并生成BOOT.bin</br>
<code>[SDK] File->New->Application Project </br></code>
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
├── hardware_pro
│   ├── axi_pwm_6ch_1.0
│   │   ├── bd
│   │   │   └── bd.tcl
│   │   ├── component.xml
│   │   ├── drivers
│   │   │   └── axi_pwm_6ch_v1_0
│   │   │       ├── data
│   │   │       │   ├── axi_pwm_6ch.mdd
│   │   │       │   └── axi_pwm_6ch.tcl
│   │   │       └── src
│   │   │           ├── axi_pwm_6ch.c
│   │   │           ├── axi_pwm_6ch.h
│   │   │           ├── axi_pwm_6ch_selftest.c
│   │   │           └── Makefile
│   │   ├── example_designs
│   │   │   ├── bfm_design
│   │   │   │   ├── axi_pwm_6ch_v1_0_tb.v
│   │   │   │   └── design.tcl
│   │   │   └── debug_hw_design
│   │   │       ├── axi_pwm_6ch_v1_0_hw_test.tcl
│   │   │       └── design.tcl
│   │   ├── hdl
│   │   │   ├── axi_pwm_6ch_v1_0_S00_AXI.v
│   │   │   └── axi_pwm_6ch_v1_0.v
│   │   └── xgui
│   │       └── axi_pwm_6ch_v1_0.tcl
│   ├── hw.xdc
│   ├── system_pro.tcl
│   ├── system.tcl
│   ├── system_wrapper.v
│   ├── zybo_ps7.tcl
│   └── ZYBO_zynq_def.xml
├── linux_dev
│   └── xdma
│       ├── Makefile
│       ├── xdma.c
│       └── xdma.h
├── linux_examples
│   ├── axi-dma
│   │   ├── main.c
│   │   └── Makefile
│   ├── gpio
│   │   ├── main.c
│   │   └── Makefile
│   ├── pwm
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
│       ├── xil_io.c
│       ├── xil_io.h
│       ├── xil_pwm.c
│       ├── xil_pwm.h
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
└── README.md

21 directories, 50 files
</pre>
lib为库文件源码，其他为具体应用源码</br>

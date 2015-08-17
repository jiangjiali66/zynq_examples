# zynq_examples
实验环境：vivado2014.4</br>
开发板系统：linaro（其他linux也可以)</br>
内核下载地址：https://github.com/Xilinx/linux-xlnx/tree/xilinx-v2014.4</br>
device tree下载地址: https://github.com/Xilinx/device-tree-xlnx/tree/xilinx-v2015.1</br>
uboot下载地址：https://github.com/Xilinx/u-boot-xlnx/tree/xilinx-v2015.1</br>
</br>
<h2>1.生成bitstream</h2></br>
打开vivado2014.4在命令下输入以下命令</br>
cd ./zynq_examples</br>
source ./system_pro.tcl</br>
等待生成完毕</br>
<h2>2.通过sdk生成BOOT.bin</h2></br>
先在vivado上导出bitstream并Launch SDK</br>
[vivado] File->Export->Export Hardware...</br>
打钩Include bitstream</br>
点击ok</br>
[vivado] File->Launch SDK</br>
使用SDK建立fsbl工程，并生成BOOT.bin</br>
[SDK] File->New->Application Project </br>
输入Project name，点击下一步在Available Templates选择Zynq FSBL</br>
等待它自动编译fsbl.elf</br>
右键FSBL工程选择Create Zynq Boot Image</br>
点击右下角Add按钮，添加u-boot.elf</br>
然后点击Create Image</br>
在工程目录下bootimage文件有BOOT.bin生成</br>
<h2>3.linux_examples</h2></br>
example的目录结构为</br>
.</br>
├── gpio</br>
│   ├── main.c</br>
│   └── Makefile</br>
├── pwm</br>
│   ├── main.c</br>
│   └── makefile</br>
└── xlib</br>
    ├── xil_gpio.c</br>
    ├── xil_gpio.h</br>
    ├── xil_io.c</br>
    ├── xil_io.h</br>
    ├── xil_pwm.c</br>
    ├── xil_pwm.h</br>
    └── xil_types.h</br>
xlib为库文件源码，其他为具体应用源码</br>

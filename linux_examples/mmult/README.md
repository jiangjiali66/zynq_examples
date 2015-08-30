#AXI-DMA回环demo
内核源码下载地址：<code>https://github.com/Xilinx/linux-xlnx/tree/xilinx-v2014.4</code></br>
<h2>1.xdma驱动</h2></br>
在linux_dev/xdma下编译，请修改Makefile的内核路径为你自己内核源码的路径并编译驱动，通过insmod挂载驱动。（也可以使用文件夹内已经编译好的xdma.ko）</br>
<h2>2.mmult
在linux_examples/mmult文件夹下运行make、./mmult。</br>

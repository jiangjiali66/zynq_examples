//Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2014.4 (lin64) Build 1071353 Tue Nov 18 16:47:07 MST 2014
//Date        : Sun Aug 30 10:42:30 2015
//Host        : station.xup.com running 64-bit CentOS release 6.5 (Final)
//Command     : generate_target system_wrapper.bd
//Design      : system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module system_wrapper
   (DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    M_left_phA,
    M_left_phB,
    M_right_phA,
    M_right_phB,
    UART_0_rxd,
    UART_0_txd,
    Vaux14_v_n,
    Vaux14_v_p,
    Vaux15_v_n,
    Vaux15_v_p,
    Vaux6_v_n,
    Vaux6_v_p,
    Vaux7_v_n,
    Vaux7_v_p,
    echo,
    gpio0_0_tri_io,
    gpio0_1_tri_io,
    gpio1_0_tri_io,
    gpio2_0_tri_io,
    gpio2_1_tri_io,
    iic_0_scl_io,
    iic_0_sda_io,
    iic_1_scl_io,
    iic_1_sda_io,
    pwm_out,
    trig);
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;
  input M_left_phA;
  input M_left_phB;
  input M_right_phA;
  input M_right_phB;
  input UART_0_rxd;
  output UART_0_txd;
  input Vaux14_v_n;
  input Vaux14_v_p;
  input Vaux15_v_n;
  input Vaux15_v_p;
  input Vaux6_v_n;
  input Vaux6_v_p;
  input Vaux7_v_n;
  input Vaux7_v_p;
  input [2:0]echo;
  inout [3:0]gpio0_0_tri_io;
  inout [7:0]gpio0_1_tri_io;
  inout [3:0]gpio1_0_tri_io;
  inout [3:0]gpio2_0_tri_io;
  inout [5:0]gpio2_1_tri_io;
  inout iic_0_scl_io;
  inout iic_0_sda_io;
  inout iic_1_scl_io;
  inout iic_1_sda_io;
  output [5:0]pwm_out;
  output trig;

  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire M_left_phA;
  wire M_left_phB;
  wire M_right_phA;
  wire M_right_phB;
  wire UART_0_rxd;
  wire UART_0_txd;
  wire Vaux14_v_n;
  wire Vaux14_v_p;
  wire Vaux15_v_n;
  wire Vaux15_v_p;
  wire Vaux6_v_n;
  wire Vaux6_v_p;
  wire Vaux7_v_n;
  wire Vaux7_v_p;
  wire [2:0]echo;
  wire [0:0]gpio0_0_tri_i_0;
  wire [1:1]gpio0_0_tri_i_1;
  wire [2:2]gpio0_0_tri_i_2;
  wire [3:3]gpio0_0_tri_i_3;
  wire [0:0]gpio0_0_tri_io_0;
  wire [1:1]gpio0_0_tri_io_1;
  wire [2:2]gpio0_0_tri_io_2;
  wire [3:3]gpio0_0_tri_io_3;
  wire [0:0]gpio0_0_tri_o_0;
  wire [1:1]gpio0_0_tri_o_1;
  wire [2:2]gpio0_0_tri_o_2;
  wire [3:3]gpio0_0_tri_o_3;
  wire [0:0]gpio0_0_tri_t_0;
  wire [1:1]gpio0_0_tri_t_1;
  wire [2:2]gpio0_0_tri_t_2;
  wire [3:3]gpio0_0_tri_t_3;
  wire [0:0]gpio0_1_tri_i_0;
  wire [1:1]gpio0_1_tri_i_1;
  wire [2:2]gpio0_1_tri_i_2;
  wire [3:3]gpio0_1_tri_i_3;
  wire [4:4]gpio0_1_tri_i_4;
  wire [5:5]gpio0_1_tri_i_5;
  wire [6:6]gpio0_1_tri_i_6;
  wire [7:7]gpio0_1_tri_i_7;
  wire [0:0]gpio0_1_tri_io_0;
  wire [1:1]gpio0_1_tri_io_1;
  wire [2:2]gpio0_1_tri_io_2;
  wire [3:3]gpio0_1_tri_io_3;
  wire [4:4]gpio0_1_tri_io_4;
  wire [5:5]gpio0_1_tri_io_5;
  wire [6:6]gpio0_1_tri_io_6;
  wire [7:7]gpio0_1_tri_io_7;
  wire [0:0]gpio0_1_tri_o_0;
  wire [1:1]gpio0_1_tri_o_1;
  wire [2:2]gpio0_1_tri_o_2;
  wire [3:3]gpio0_1_tri_o_3;
  wire [4:4]gpio0_1_tri_o_4;
  wire [5:5]gpio0_1_tri_o_5;
  wire [6:6]gpio0_1_tri_o_6;
  wire [7:7]gpio0_1_tri_o_7;
  wire [0:0]gpio0_1_tri_t_0;
  wire [1:1]gpio0_1_tri_t_1;
  wire [2:2]gpio0_1_tri_t_2;
  wire [3:3]gpio0_1_tri_t_3;
  wire [4:4]gpio0_1_tri_t_4;
  wire [5:5]gpio0_1_tri_t_5;
  wire [6:6]gpio0_1_tri_t_6;
  wire [7:7]gpio0_1_tri_t_7;
  wire [0:0]gpio1_0_tri_i_0;
  wire [1:1]gpio1_0_tri_i_1;
  wire [2:2]gpio1_0_tri_i_2;
  wire [3:3]gpio1_0_tri_i_3;
  wire [0:0]gpio1_0_tri_io_0;
  wire [1:1]gpio1_0_tri_io_1;
  wire [2:2]gpio1_0_tri_io_2;
  wire [3:3]gpio1_0_tri_io_3;
  wire [0:0]gpio1_0_tri_o_0;
  wire [1:1]gpio1_0_tri_o_1;
  wire [2:2]gpio1_0_tri_o_2;
  wire [3:3]gpio1_0_tri_o_3;
  wire [0:0]gpio1_0_tri_t_0;
  wire [1:1]gpio1_0_tri_t_1;
  wire [2:2]gpio1_0_tri_t_2;
  wire [3:3]gpio1_0_tri_t_3;
  wire [0:0]gpio2_0_tri_i_0;
  wire [1:1]gpio2_0_tri_i_1;
  wire [2:2]gpio2_0_tri_i_2;
  wire [3:3]gpio2_0_tri_i_3;
  wire [0:0]gpio2_0_tri_io_0;
  wire [1:1]gpio2_0_tri_io_1;
  wire [2:2]gpio2_0_tri_io_2;
  wire [3:3]gpio2_0_tri_io_3;
  wire [0:0]gpio2_0_tri_o_0;
  wire [1:1]gpio2_0_tri_o_1;
  wire [2:2]gpio2_0_tri_o_2;
  wire [3:3]gpio2_0_tri_o_3;
  wire [0:0]gpio2_0_tri_t_0;
  wire [1:1]gpio2_0_tri_t_1;
  wire [2:2]gpio2_0_tri_t_2;
  wire [3:3]gpio2_0_tri_t_3;
  wire [0:0]gpio2_1_tri_i_0;
  wire [1:1]gpio2_1_tri_i_1;
  wire [2:2]gpio2_1_tri_i_2;
  wire [3:3]gpio2_1_tri_i_3;
  wire [4:4]gpio2_1_tri_i_4;
  wire [5:5]gpio2_1_tri_i_5;
  wire [0:0]gpio2_1_tri_io_0;
  wire [1:1]gpio2_1_tri_io_1;
  wire [2:2]gpio2_1_tri_io_2;
  wire [3:3]gpio2_1_tri_io_3;
  wire [4:4]gpio2_1_tri_io_4;
  wire [5:5]gpio2_1_tri_io_5;
  wire [0:0]gpio2_1_tri_o_0;
  wire [1:1]gpio2_1_tri_o_1;
  wire [2:2]gpio2_1_tri_o_2;
  wire [3:3]gpio2_1_tri_o_3;
  wire [4:4]gpio2_1_tri_o_4;
  wire [5:5]gpio2_1_tri_o_5;
  wire [0:0]gpio2_1_tri_t_0;
  wire [1:1]gpio2_1_tri_t_1;
  wire [2:2]gpio2_1_tri_t_2;
  wire [3:3]gpio2_1_tri_t_3;
  wire [4:4]gpio2_1_tri_t_4;
  wire [5:5]gpio2_1_tri_t_5;
  wire iic_0_scl_i;
  wire iic_0_scl_io;
  wire iic_0_scl_o;
  wire iic_0_scl_t;
  wire iic_0_sda_i;
  wire iic_0_sda_io;
  wire iic_0_sda_o;
  wire iic_0_sda_t;
  wire iic_1_scl_i;
  wire iic_1_scl_io;
  wire iic_1_scl_o;
  wire iic_1_scl_t;
  wire iic_1_sda_i;
  wire iic_1_sda_io;
  wire iic_1_sda_o;
  wire iic_1_sda_t;
  wire [5:0]pwm_out;
  wire trig;

IOBUF gpio0_0_tri_iobuf_0
       (.I(gpio0_0_tri_o_0),
        .IO(gpio0_0_tri_io[0]),
        .O(gpio0_0_tri_i_0),
        .T(gpio0_0_tri_t_0));
IOBUF gpio0_0_tri_iobuf_1
       (.I(gpio0_0_tri_o_1),
        .IO(gpio0_0_tri_io[1]),
        .O(gpio0_0_tri_i_1),
        .T(gpio0_0_tri_t_1));
IOBUF gpio0_0_tri_iobuf_2
       (.I(gpio0_0_tri_o_2),
        .IO(gpio0_0_tri_io[2]),
        .O(gpio0_0_tri_i_2),
        .T(gpio0_0_tri_t_2));
IOBUF gpio0_0_tri_iobuf_3
       (.I(gpio0_0_tri_o_3),
        .IO(gpio0_0_tri_io[3]),
        .O(gpio0_0_tri_i_3),
        .T(gpio0_0_tri_t_3));
IOBUF gpio0_1_tri_iobuf_0
       (.I(gpio0_1_tri_o_0),
        .IO(gpio0_1_tri_io[0]),
        .O(gpio0_1_tri_i_0),
        .T(gpio0_1_tri_t_0));
IOBUF gpio0_1_tri_iobuf_1
       (.I(gpio0_1_tri_o_1),
        .IO(gpio0_1_tri_io[1]),
        .O(gpio0_1_tri_i_1),
        .T(gpio0_1_tri_t_1));
IOBUF gpio0_1_tri_iobuf_2
       (.I(gpio0_1_tri_o_2),
        .IO(gpio0_1_tri_io[2]),
        .O(gpio0_1_tri_i_2),
        .T(gpio0_1_tri_t_2));
IOBUF gpio0_1_tri_iobuf_3
       (.I(gpio0_1_tri_o_3),
        .IO(gpio0_1_tri_io[3]),
        .O(gpio0_1_tri_i_3),
        .T(gpio0_1_tri_t_3));
IOBUF gpio0_1_tri_iobuf_4
       (.I(gpio0_1_tri_o_4),
        .IO(gpio0_1_tri_io[4]),
        .O(gpio0_1_tri_i_4),
        .T(gpio0_1_tri_t_4));
IOBUF gpio0_1_tri_iobuf_5
       (.I(gpio0_1_tri_o_5),
        .IO(gpio0_1_tri_io[5]),
        .O(gpio0_1_tri_i_5),
        .T(gpio0_1_tri_t_5));
IOBUF gpio0_1_tri_iobuf_6
       (.I(gpio0_1_tri_o_6),
        .IO(gpio0_1_tri_io[6]),
        .O(gpio0_1_tri_i_6),
        .T(gpio0_1_tri_t_6));
IOBUF gpio0_1_tri_iobuf_7
       (.I(gpio0_1_tri_o_7),
        .IO(gpio0_1_tri_io[7]),
        .O(gpio0_1_tri_i_7),
        .T(gpio0_1_tri_t_7));
IOBUF gpio1_0_tri_iobuf_0
       (.I(gpio1_0_tri_o_0),
        .IO(gpio1_0_tri_io[0]),
        .O(gpio1_0_tri_i_0),
        .T(gpio1_0_tri_t_0));
IOBUF gpio1_0_tri_iobuf_1
       (.I(gpio1_0_tri_o_1),
        .IO(gpio1_0_tri_io[1]),
        .O(gpio1_0_tri_i_1),
        .T(gpio1_0_tri_t_1));
IOBUF gpio1_0_tri_iobuf_2
       (.I(gpio1_0_tri_o_2),
        .IO(gpio1_0_tri_io[2]),
        .O(gpio1_0_tri_i_2),
        .T(gpio1_0_tri_t_2));
IOBUF gpio1_0_tri_iobuf_3
       (.I(gpio1_0_tri_o_3),
        .IO(gpio1_0_tri_io[3]),
        .O(gpio1_0_tri_i_3),
        .T(gpio1_0_tri_t_3));
IOBUF gpio2_0_tri_iobuf_0
       (.I(gpio2_0_tri_o_0),
        .IO(gpio2_0_tri_io[0]),
        .O(gpio2_0_tri_i_0),
        .T(gpio2_0_tri_t_0));
IOBUF gpio2_0_tri_iobuf_1
       (.I(gpio2_0_tri_o_1),
        .IO(gpio2_0_tri_io[1]),
        .O(gpio2_0_tri_i_1),
        .T(gpio2_0_tri_t_1));
IOBUF gpio2_0_tri_iobuf_2
       (.I(gpio2_0_tri_o_2),
        .IO(gpio2_0_tri_io[2]),
        .O(gpio2_0_tri_i_2),
        .T(gpio2_0_tri_t_2));
IOBUF gpio2_0_tri_iobuf_3
       (.I(gpio2_0_tri_o_3),
        .IO(gpio2_0_tri_io[3]),
        .O(gpio2_0_tri_i_3),
        .T(gpio2_0_tri_t_3));
IOBUF gpio2_1_tri_iobuf_0
       (.I(gpio2_1_tri_o_0),
        .IO(gpio2_1_tri_io[0]),
        .O(gpio2_1_tri_i_0),
        .T(gpio2_1_tri_t_0));
IOBUF gpio2_1_tri_iobuf_1
       (.I(gpio2_1_tri_o_1),
        .IO(gpio2_1_tri_io[1]),
        .O(gpio2_1_tri_i_1),
        .T(gpio2_1_tri_t_1));
IOBUF gpio2_1_tri_iobuf_2
       (.I(gpio2_1_tri_o_2),
        .IO(gpio2_1_tri_io[2]),
        .O(gpio2_1_tri_i_2),
        .T(gpio2_1_tri_t_2));
IOBUF gpio2_1_tri_iobuf_3
       (.I(gpio2_1_tri_o_3),
        .IO(gpio2_1_tri_io[3]),
        .O(gpio2_1_tri_i_3),
        .T(gpio2_1_tri_t_3));
IOBUF gpio2_1_tri_iobuf_4
       (.I(gpio2_1_tri_o_4),
        .IO(gpio2_1_tri_io[4]),
        .O(gpio2_1_tri_i_4),
        .T(gpio2_1_tri_t_4));
IOBUF gpio2_1_tri_iobuf_5
       (.I(gpio2_1_tri_o_5),
        .IO(gpio2_1_tri_io[5]),
        .O(gpio2_1_tri_i_5),
        .T(gpio2_1_tri_t_5));
IOBUF iic_0_scl_iobuf
       (.I(iic_0_scl_o),
        .IO(iic_0_scl_io),
        .O(iic_0_scl_i),
        .T(iic_0_scl_t));
IOBUF iic_0_sda_iobuf
       (.I(iic_0_sda_o),
        .IO(iic_0_sda_io),
        .O(iic_0_sda_i),
        .T(iic_0_sda_t));
IOBUF iic_1_scl_iobuf
       (.I(iic_1_scl_o),
        .IO(iic_1_scl_io),
        .O(iic_1_scl_i),
        .T(iic_1_scl_t));
IOBUF iic_1_sda_iobuf
       (.I(iic_1_sda_o),
        .IO(iic_1_sda_io),
        .O(iic_1_sda_i),
        .T(iic_1_sda_t));
system system_i
       (.DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .GPIO0_0_tri_i({gpio0_0_tri_i_3,gpio0_0_tri_i_2,gpio0_0_tri_i_1,gpio0_0_tri_i_0}),
        .GPIO0_0_tri_o({gpio0_0_tri_o_3,gpio0_0_tri_o_2,gpio0_0_tri_o_1,gpio0_0_tri_o_0}),
        .GPIO0_0_tri_t({gpio0_0_tri_t_3,gpio0_0_tri_t_2,gpio0_0_tri_t_1,gpio0_0_tri_t_0}),
        .GPIO0_1_tri_i({gpio0_1_tri_i_7,gpio0_1_tri_i_6,gpio0_1_tri_i_5,gpio0_1_tri_i_4,gpio0_1_tri_i_3,gpio0_1_tri_i_2,gpio0_1_tri_i_1,gpio0_1_tri_i_0}),
        .GPIO0_1_tri_o({gpio0_1_tri_o_7,gpio0_1_tri_o_6,gpio0_1_tri_o_5,gpio0_1_tri_o_4,gpio0_1_tri_o_3,gpio0_1_tri_o_2,gpio0_1_tri_o_1,gpio0_1_tri_o_0}),
        .GPIO0_1_tri_t({gpio0_1_tri_t_7,gpio0_1_tri_t_6,gpio0_1_tri_t_5,gpio0_1_tri_t_4,gpio0_1_tri_t_3,gpio0_1_tri_t_2,gpio0_1_tri_t_1,gpio0_1_tri_t_0}),
        .GPIO1_0_tri_i({gpio1_0_tri_i_3,gpio1_0_tri_i_2,gpio1_0_tri_i_1,gpio1_0_tri_i_0}),
        .GPIO1_0_tri_o({gpio1_0_tri_o_3,gpio1_0_tri_o_2,gpio1_0_tri_o_1,gpio1_0_tri_o_0}),
        .GPIO1_0_tri_t({gpio1_0_tri_t_3,gpio1_0_tri_t_2,gpio1_0_tri_t_1,gpio1_0_tri_t_0}),
        .GPIO2_0_tri_i({gpio2_0_tri_i_3,gpio2_0_tri_i_2,gpio2_0_tri_i_1,gpio2_0_tri_i_0}),
        .GPIO2_0_tri_o({gpio2_0_tri_o_3,gpio2_0_tri_o_2,gpio2_0_tri_o_1,gpio2_0_tri_o_0}),
        .GPIO2_0_tri_t({gpio2_0_tri_t_3,gpio2_0_tri_t_2,gpio2_0_tri_t_1,gpio2_0_tri_t_0}),
        .GPIO2_1_tri_i({gpio2_1_tri_i_5,gpio2_1_tri_i_4,gpio2_1_tri_i_3,gpio2_1_tri_i_2,gpio2_1_tri_i_1,gpio2_1_tri_i_0}),
        .GPIO2_1_tri_o({gpio2_1_tri_o_5,gpio2_1_tri_o_4,gpio2_1_tri_o_3,gpio2_1_tri_o_2,gpio2_1_tri_o_1,gpio2_1_tri_o_0}),
        .GPIO2_1_tri_t({gpio2_1_tri_t_5,gpio2_1_tri_t_4,gpio2_1_tri_t_3,gpio2_1_tri_t_2,gpio2_1_tri_t_1,gpio2_1_tri_t_0}),
        .IIC_0_scl_i(iic_0_scl_i),
        .IIC_0_scl_o(iic_0_scl_o),
        .IIC_0_scl_t(iic_0_scl_t),
        .IIC_0_sda_i(iic_0_sda_i),
        .IIC_0_sda_o(iic_0_sda_o),
        .IIC_0_sda_t(iic_0_sda_t),
        .IIC_1_scl_i(iic_1_scl_i),
        .IIC_1_scl_o(iic_1_scl_o),
        .IIC_1_scl_t(iic_1_scl_t),
        .IIC_1_sda_i(iic_1_sda_i),
        .IIC_1_sda_o(iic_1_sda_o),
        .IIC_1_sda_t(iic_1_sda_t),
        .M_left_phA(M_left_phA),
        .M_left_phB(M_left_phB),
        .M_right_phA(M_right_phA),
        .M_right_phB(M_right_phB),
        .UART_0_rxd(UART_0_rxd),
        .UART_0_txd(UART_0_txd),
        .Vaux14_v_n(Vaux14_v_n),
        .Vaux14_v_p(Vaux14_v_p),
        .Vaux15_v_n(Vaux15_v_n),
        .Vaux15_v_p(Vaux15_v_p),
        .Vaux6_v_n(Vaux6_v_n),
        .Vaux6_v_p(Vaux6_v_p),
        .Vaux7_v_n(Vaux7_v_n),
        .Vaux7_v_p(Vaux7_v_p),
        .echo(echo),
        .pwm_out(pwm_out),
        .trig(trig));
endmodule

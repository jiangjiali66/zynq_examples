#led signals
#Gpio0_0 LED
set_property PACKAGE_PIN M14 [get_ports {gpio0_0_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_0_tri_io[0]}]
set_property PACKAGE_PIN M15 [get_ports {gpio0_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_0_tri_io[1]}]
set_property PACKAGE_PIN G14 [get_ports {gpio0_0_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_0_tri_io[2]}]
set_property PACKAGE_PIN D18 [get_ports {gpio0_0_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_0_tri_io[3]}]

#Gpio0_1
#SW
set_property PACKAGE_PIN G15 [get_ports {gpio0_1_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[0]}]
set_property PACKAGE_PIN P15 [get_ports {gpio0_1_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[1]}]
set_property PACKAGE_PIN W13 [get_ports {gpio0_1_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[2]}]
set_property PACKAGE_PIN T16 [get_ports {gpio0_1_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[3]}]
#BTN
set_property PACKAGE_PIN R18 [get_ports {gpio0_1_tri_io[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[4]}]
set_property PACKAGE_PIN P16 [get_ports {gpio0_1_tri_io[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[5]}]
set_property PACKAGE_PIN V16 [get_ports {gpio0_1_tri_io[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[6]}]
set_property PACKAGE_PIN Y16 [get_ports {gpio0_1_tri_io[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio0_1_tri_io[7]}]

#PWM
set_property PACKAGE_PIN V12 [get_ports {pwm_out[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pwm_out[0]}]
set_property PACKAGE_PIN W16 [get_ports {pwm_out[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pwm_out[1]}]
set_property PACKAGE_PIN J15 [get_ports {pwm_out[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pwm_out[2]}]
set_property PACKAGE_PIN H15 [get_ports {pwm_out[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pwm_out[3]}]
set_property PACKAGE_PIN T17 [get_ports {pwm_out[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pwm_out[4]}]
set_property PACKAGE_PIN Y17 [get_ports {pwm_out[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pwm_out[5]}]

#UART_0
set_property PACKAGE_PIN V18 [get_ports UART_0_txd]
set_property IOSTANDARD LVCMOS33 [get_ports UART_0_txd]
set_property PACKAGE_PIN R14 [get_ports UART_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports UART_0_rxd]

#IIC
set_property PACKAGE_PIN V13 [get_ports iic_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_0_scl_io]
set_property PACKAGE_PIN U17 [get_ports iic_0_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_0_sda_io]

#IIC EEPROM
set_property PACKAGE_PIN N18 [get_ports iic_1_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_1_scl_io]
set_property PACKAGE_PIN N17 [get_ports iic_1_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_1_sda_io]

#Gpio1_0    JB
set_property PACKAGE_PIN W20 [get_ports {gpio1_0_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio1_0_tri_io[0]}]
set_property PACKAGE_PIN Y19 [get_ports {gpio1_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio1_0_tri_io[1]}]
set_property PACKAGE_PIN W18 [get_ports {gpio1_0_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio1_0_tri_io[2]}]
set_property PACKAGE_PIN W19 [get_ports {gpio1_0_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio1_0_tri_io[3]}]

#Ultra
set_property PACKAGE_PIN U20 [get_ports trig]
set_property IOSTANDARD LVCMOS33 [get_ports trig]
set_property PACKAGE_PIN T20 [get_ports {echo[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {echo[0]}]
set_property PACKAGE_PIN Y18 [get_ports {echo[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {echo[1]}]
set_property PACKAGE_PIN V20 [get_ports {echo[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {echo[2]}]

#Gpio2_0    JC  
set_property PACKAGE_PIN V15 [get_ports {gpio2_0_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_0_tri_io[0]}]
set_property PACKAGE_PIN W15 [get_ports {gpio2_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_0_tri_io[1]}]
set_property PACKAGE_PIN W14 [get_ports {gpio2_0_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_0_tri_io[2]}]
set_property PACKAGE_PIN Y14 [get_ports {gpio2_0_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_0_tri_io[3]}]

#Gpio2_1    JD  
set_property PACKAGE_PIN T14 [get_ports {gpio2_1_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_1_tri_io[0]}]
set_property PACKAGE_PIN T15 [get_ports {gpio2_1_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_1_tri_io[1]}]
set_property PACKAGE_PIN P14 [get_ports {gpio2_1_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_1_tri_io[2]}]
set_property PACKAGE_PIN U14 [get_ports {gpio2_1_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_1_tri_io[3]}]
set_property PACKAGE_PIN U15 [get_ports {gpio2_1_tri_io[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_1_tri_io[4]}]
set_property PACKAGE_PIN V17 [get_ports {gpio2_1_tri_io[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio2_1_tri_io[5]}]

#Quadrature_Encoder JC
set_property PACKAGE_PIN T10 [get_ports M_left_phA]
set_property IOSTANDARD LVCMOS33 [get_ports M_left_phA]
set_property PACKAGE_PIN U12 [get_ports M_left_phB]
set_property IOSTANDARD LVCMOS33 [get_ports M_left_phB]
set_property PACKAGE_PIN T11 [get_ports M_right_phA]
set_property IOSTANDARD LVCMOS33 [get_ports M_right_phA]
set_property PACKAGE_PIN T12 [get_ports M_right_phB]
set_property IOSTANDARD LVCMOS33 [get_ports M_right_phB]

#ADC
set_property PACKAGE_PIN N15 [get_ports {Vaux14_v_p}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux14_v_p}]
set_property PACKAGE_PIN N16 [get_ports {Vaux14_v_n}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux14_v_n}]
set_property PACKAGE_PIN L14 [get_ports {Vaux7_v_p}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux7_v_p}]
set_property PACKAGE_PIN L15 [get_ports {Vaux7_v_n}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux7_v_n}]
set_property PACKAGE_PIN K16 [get_ports {Vaux15_v_p}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux15_v_p}]
set_property PACKAGE_PIN J16 [get_ports {Vaux15_v_n}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux15_v_n}]
set_property PACKAGE_PIN K14 [get_ports {Vaux6_v_p}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux6_v_p}]
set_property PACKAGE_PIN J14 [get_ports {Vaux6_v_n}]
set_property IOSTANDARD LVCMOS33 [get_ports {Vaux6_v_n}]



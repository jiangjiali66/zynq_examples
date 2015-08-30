# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
	set Page0 [ipgui::add_page $IPINST -name "1" -layout vertical]
	set canvas_spec [ipgui::get_canvasspec -of $IPINST]
	set_property ip_logo "misc/logo.png" $canvas_spec
	set Component_Name [ipgui::add_param $IPINST -parent $Page0 -name Component_Name]
	set tabgroup0 [ipgui::add_group $IPINST -parent $Page0 -name {S AXI CONTROL BUS (AXI4Lite Slave Interface)} -layout vertical]
	set C_S_AXI_CONTROL_BUS_ADDR_WIDTH [ipgui::add_param $IPINST -parent $tabgroup0 -name C_S_AXI_CONTROL_BUS_ADDR_WIDTH]
}

proc update_PARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH } {
	# Procedure called to update C_S_AXI_CONTROL_BUS_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH } {
	# Procedure called to validate C_S_AXI_CONTROL_BUS_ADDR_WIDTH
	return true
}


proc update_MODELPARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH { MODELPARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH PARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S_AXI_CONTROL_BUS_ADDR_WIDTH}
}


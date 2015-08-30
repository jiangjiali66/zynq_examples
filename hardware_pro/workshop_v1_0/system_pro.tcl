set version "2014.4"
set project_name "workshop"
set part "xc7z010clg400-1"

create_project $project_name . -part xc7z010clg400-1 -force
set_property ip_repo_paths  ./ip_repo [current_project]

update_ip_catalog

create_bd_design "system"
source system.tcl
source ps.tcl

generate_target {synthesis implementation} \
  [get_files  $project_name.srcs/sources_1/bd/system/system.bd]

make_wrapper -files [get_files $project_name.srcs/sources_1/bd/system/system.bd] -top
import_files -force -norecurse -fileset sources_1 ./system_wrapper.v
import_files -force -norecurse -fileset constrs_1 ./hw.xdc
set_property top system_wrapper [current_fileset]

launch_runs synth_1 -jobs 8
wait_on_run synth_1
open_run synth_1
report_timing_summary -file report_timing_summary_synth_1.log


launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1
open_run impl_1
report_timing_summary -file report_timing_summary_impl_1.log

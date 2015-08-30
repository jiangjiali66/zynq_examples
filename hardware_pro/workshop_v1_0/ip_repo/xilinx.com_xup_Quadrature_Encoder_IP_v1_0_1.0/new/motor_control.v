`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/14/2015 12:19:03 PM
// Design Name: 
// Module Name: motor_control
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module motor_control#(
		// Users to add parameters here
        parameter [7 : 0] CLK_FREQUENCY           = 8'd100,           //input clock frequency in MHz
        parameter [15 : 0] PWM_PERIOD                  = 16'd2000,     //PWM period set, in uS, maximum value is 32767
         parameter [15 : 0]		SPEED_CTRL_PERIOD = 16'd25    //speed control period,   means  the number of PWM period
         //control period is (SPEED_CTRL_PERIOD * PWM_PERIOD) uS
	)
(
input mclk,rst,
input phA,phB,
output[15:0] out_cur_speed,
output dir_o
    );
    localparam
          TIMER_1US_CONTER = CLK_FREQUENCY / 2 - 1,
          WIDTH = 8'd16,
          PWM_PERIOD_CONTER = PWM_PERIOD - 1;
          
    wire pwm_signal;
    wire dir_o;
    
    reg w_pwm_period_start;
    reg [1 : 0] reg_calc_state;
    reg reg_encoder_clr_n;

    
    wire [WIDTH - 1 : 0] w_encoder_cnter;
    
    reg reg_speed_period_end;
    reg [15 : 0] reg_speed_ctrl_period_cnter;
    reg [WIDTH - 1 : 0] out_cur_speed;
        

    reg [8 - 1 : 0]  timer_cnter;
    reg              timer_1us;
    
//20ms clk counter///////////////
reg [15:0] count;  // 0~19999
initial count = 0;

//1uS timer
always@(posedge mclk) begin
   if(rst == 1) begin
      timer_cnter <= 0;
      timer_1us <= 0;
      w_pwm_period_start <= 0;
   end
   else begin
      if(timer_cnter >= TIMER_1US_CONTER) begin
         timer_1us <= ~timer_1us;
         timer_cnter <= 0;
      end
      else begin
         timer_cnter <= timer_cnter + 1;
         if((count == 0) && (timer_cnter == 0) && (timer_1us == 1)) begin
            w_pwm_period_start <= 1;
         end
         else begin
            w_pwm_period_start <= 0;
         end
      end
   end
end

always@(posedge timer_1us) begin
	if(count >= PWM_PERIOD_CONTER) begin
		count <= 0;
   end
	else begin
		count <= count + 1;
   end
end 
            
 speed_dir_measure(
       .clk(mclk),
       .rst(rst),
       .clr(reg_encoder_clr_n),
       .phA(phA),
       .phB(phB),
       .dir(dir_o),
       .cnter(w_encoder_cnter)
       );       
            

            
  localparam
                STATE0 = 2'd0,
                STATE1 = 2'd1,
                STATE2 = 2'd2,
                STATE3 = 2'd3
                 ;
reg [1 : 0] reg_calc_state;          
always@(posedge mclk or posedge rst) begin
    if(rst == 1) begin
          reg_calc_state     <= STATE0;
          reg_encoder_clr_n  <= 0;
     end
     else begin
         case(reg_calc_state)
              STATE0: begin
                  reg_calc_state  <= STATE1;
                  reg_encoder_clr_n <= 1;
                end
                STATE1: begin
                    reg_calc_state  <= STATE2;
                    reg_encoder_clr_n <= 0;
                    out_cur_speed <= w_encoder_cnter;
                end
                STATE2: begin
                    reg_encoder_clr_n <= 1;
                    reg_calc_state  <= STATE3;
                end 
                STATE3: begin
                    if(reg_speed_period_end == 1) begin
                        reg_calc_state  <= STATE0;
                     end
                end
          endcase
     end
end
            
always@(posedge mclk or posedge rst) begin
    if(rst == 1) begin
          reg_speed_ctrl_period_cnter <= 1;
    end
     else begin
         if(w_pwm_period_start == 1) begin
              if( reg_speed_ctrl_period_cnter >= SPEED_CTRL_PERIOD) begin
                     reg_speed_ctrl_period_cnter <= 1;
                end
              else begin
                    reg_speed_ctrl_period_cnter <= reg_speed_ctrl_period_cnter + 1;
                end
          end
     end
end
            
always@(posedge mclk or posedge rst) begin
    if(rst == 1) begin
         reg_speed_period_end <= 0;
    end
     else begin
         if((w_pwm_period_start == 1)  && ( reg_speed_ctrl_period_cnter >= SPEED_CTRL_PERIOD)) begin
              reg_speed_period_end <= 1;
          end
          else begin
              reg_speed_period_end <= 0;
          end
     end
end
            
                 
endmodule


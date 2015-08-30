`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/16/2015 04:06:47 PM
// Design Name: 
// Module Name: ultrasonic
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


module ultrasonic(
input clk100,
input rstn,
input echo_0,echo_1,echo_2,
output trig,
output [31:0]ultra_value_0,ultra_value_1,ultra_value_2
);

reg [6:0]  cnt_1M;
reg clk1MHz;
always@(posedge clk100)begin
    if(cnt_1M>=49)begin
        cnt_1M<=0;
        clk1MHz<= ~clk1MHz;
    end
    else
        cnt_1M<=cnt_1M+1;
end

reg [19:0] cnt;
always@(posedge clk1MHz)begin//this 100ms period signal is used to control the time_sequence
    if(!rstn)
        cnt<=20'd0;
    else if(cnt>=20'd1000_00)
        cnt<=20'd0;
    else
        cnt<=cnt+20'd1;
end


reg trig;

always@(posedge clk1MHz)begin//generate a >10us pulse,it will be tranformed into 8 continue 40KHz ultrasonic wave by the module
    if(!rstn)
        trig<=1'b0;
    else if((cnt>=20'd20)&&(cnt<=20'd40))
        trig<=1'b1;
    else
        trig<=1'b0;
end

reg [31:0] t_0,t_1,t_2; 

always@(posedge clk1MHz)begin//get the time from the sonic wave send and the echo receive,the t will be clear when the trig pulse gen
    if(!rstn)
        t_0<=32'd0;
    else if((cnt>=20'd20)&&(cnt<=20'd40))
        t_0<=32'd0;
    else if(echo_0)
        t_0<=t_0+32'd1;
end

always@(posedge clk1MHz)begin//get the time from the sonic wave send and the echo receive,the t will be clear when the trig pulse gen
    if(!rstn)
        t_1<=32'd0;
    else if((cnt>=20'd20)&&(cnt<=20'd40))
        t_1<=32'd0;
    else if(echo_1)
        t_1<=t_1+32'd1;
end

always@(posedge clk1MHz)begin//get the time from the sonic wave send and the echo receive,the t will be clear when the trig pulse gen
    if(!rstn)
        t_2<=32'd0;
    else if((cnt>=20'd20)&&(cnt<=20'd40))
        t_2<=32'd0;
    else if(echo_2)
        t_2<=t_2+32'd1;
end

reg [31:0] s_0,s_1,s_2;

always@(posedge clk1MHz)begin
    if(!rstn)
        s_0<=32'd0;
    else if(cnt<20'd10)
        s_0<=t_0;
end

always@(posedge clk1MHz)begin
    if(!rstn)
        s_1<=32'd0;
    else if(cnt<20'd10)
        s_1<=t_1;
end

always@(posedge clk1MHz)begin
    if(!rstn)
        s_2<=32'd0;
    else if(cnt<20'd10)
        s_2<=t_2;
end

assign ultra_value_0 = s_0[31:0];
assign ultra_value_1 = s_1[31:0];
assign ultra_value_2 = s_2[31:0];     

endmodule


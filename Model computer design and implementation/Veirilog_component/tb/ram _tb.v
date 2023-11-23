`timescale 1ns/1ps
module ram_tb();
reg CE;
reg [3:0] ABUS;
wire [7:0] DBUS;
rom DUT(
.CE(CE),
.ABUS(ABUS),
.DBUS(DBUS));
initial begin
CE = 1'b0;
ABUS = 4'd0000;
end
initial begin
#20 ABUS = 4'b0000; 
#20 ABUS = 4'b0001; 
#20 ABUS = 4'b0010; 
#20 ABUS = 4'b0011; 
#20 ABUS = 4'b0100; 
#20 ABUS = 4'b0101; 
#20 ABUS = 4'b0110; 
#20 ABUS = 4'b0111; 
#20 ABUS = 4'b1000; 
#20 ABUS = 4'b1001; 
#20 ABUS = 4'b1010; 
#20 ABUS = 4'b1011; 
#20 ABUS = 4'b1100; 
#20 ABUS = 4'b1101; 
#20 ABUS = 4'b1110; 

#60 $stop;
end
endmodule
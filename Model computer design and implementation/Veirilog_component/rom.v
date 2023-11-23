`timescale 1ns / 1ps

module rom(
    input wire CE,
    input wire [3:0] ABUS,
    output reg [7:0] DBUS
    );
    
always @ (CE or ABUS) begin
    if (CE) DBUS<= 8'bzzzz_zzzz;
    else case (ABUS)
        0: DBUS <= 8'b1111_1111;//LD  FF
        1: DBUS <= 8'b0000_0101;//5
        2: DBUS <= 8'b1111_1110;//ADD FE
        3: DBUS <= 8'b0000_0100;//+4���Ϊ09
        4: DBUS <= 8'b1111_1101;//SUB FD
        5: DBUS <= 8'b0000_0011;//-3���Ϊ06
        6: DBUS <= 8'b1111_1100;//AND FC
        7: DBUS <= 8'b0000_0110;//and6���Ϊ06
	    8: DBUS <= 8'b1111_1011;//OR FB
        9: DBUS <= 8'b0000_0001;//or���Ϊ07
        10: DBUS <= 8'b1111_0010;//XOR F2
        11:DBUS <= 8'b0000_0001;// xor1���Ϊ06
        12:DBUS <= 8'b1111_1001;//SHL F9
        13:DBUS <= 8'b0000_0001;// shl1���Ϊ0c
        14:DBUS <= 8'b1111_1000;//HALT F8
        default: DBUS <= 8'bzzzz_zzzz;
    endcase
end
endmodule

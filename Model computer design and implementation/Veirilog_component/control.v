`timescale 1ns / 1ps
module control(
input wire LD,
input wire ADD,
input wire SUB,
input wire AND,
input wire OR,
input wire SHL,
input wire XOR,
input wire HALT,
input wire T0,T1,T2,T3,T4,T5,T6,T7,

output wire IPC,
output wire IMAR,//mar控制信号
output wire IDR,//dr控制信号
output wire EDR,//
output wire IA,//a控制信号
output wire EA,//
output wire ISUM,//+
output wire ISUB,//-
output wire IAND,//&
output wire IOR,//|
output wire ISHL,//<<
output wire IXOR,//^
output wire EALU,//alu控制信号
output wire IIR//ir控制信号
    );
    assign IMAR=~(T0|(T3&LD)|(T3&ADD)|(T3&SUB)|(T3&AND)|(T3&OR)|(T3&SHL)|(T3&XOR)); 
    assign IDR=T1|(T4&LD)|(T4&ADD)|(T4&SUB)|(T4&AND)|(T4&OR)|(T4&SHL)|(T4&XOR);
    assign IPC=T2|(T5&LD)|(T5&ADD)|(T5&SUB)|(T5&AND)|(T5&OR)|(T5&SHL)|(T5&XOR);
    assign IIR=~T2;
    assign ISUM=~(T5&ADD);
    assign ISUB=~(T5&SUB);
    assign IAND=~(T5&AND);
    assign IOR=~(T5&OR);
    assign ISHL=~(T5&SHL);
    assign IXOR=~(T5&XOR);
    assign IA=~((T6&LD)|(T6&ADD)|(T6&SUB)|(T6&AND)|(T6&OR)|(T6&SHL)|(T6&XOR));
    assign EALU=~((T6&ADD)|(T6&SUB)|(T6&AND)|(T6&OR)|(T6&SHL)|(T6&XOR));
    assign EA=~((T7&ADD)|(T7&SUB)|(T7&AND)|(T7&OR)|(T7&SHL)|(T7&XOR));
    assign EDR=(T6&ADD)|(T6&SUB)|(T6&AND)|(T6&OR)|(T6&SHL)|(T6&XOR)|(T7&ADD)|(T7&SUB)|(T7&AND)|(T7&OR)|(T7&SHL)|(T7&XOR);
endmodule
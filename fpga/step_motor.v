module motor(A, B,a,b,Enable,Z,clk);
input A, B, Enable,a,b;
input clk;
output wire[5:0] Z;
reg [5:0] Z_o;
assign Z = Z_o;
always@(A or B or Enable)
begin
       if(Enable == 1'b0)
              Z_o = 4'b0000;
       else
              case({A, B,a,b})
                     4'b0100: Z_o = 4'b0100;
                     4'b0010: Z_o = 4'b0010;
                     4'b1000: Z_o = 4'b1000;
                     4'b0001: Z_o = 4'b0001;
							4'b0110: Z_o = 4'b0110;
							4'b1010: Z_o = 4'b1010;
							4'b1001: Z_o = 4'b1001;
							4'b0101: Z_o = 4'b0101;
                     default: Z_o = 4'b0000;
              endcase
end
endmodule

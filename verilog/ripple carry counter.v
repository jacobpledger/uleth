module D_FF(q,d, clk, reset);
	output q;
	input d, clk, reset;
	reg q;
	always @(posedge reset or negedge clk)
	if(reset) q <= 1'b0;
	else q <= d;
endmodule

module T_FF(q, clk, reset);
	output q;
	input clk, reset;
	wire d;
	D_FF dff0(q, d, clk, reset);
	not n1 (d,q);
endmodule

module ripple_carry_counter(q, clk, reset);
	output [3:0] q;
	input clk, reset;
	T_FF tff0 (q[0], clk, reset);
	T_FF tff1(q[1], q[0], reset);
	T_FF tff2(q[2], q[1], reset);
	T_FF tff3(q[3], q[3], reset);
endmodule

module stimulus;
	reg clk;
	reg reset;
	wire[3:0] q;
	ripple_carry_counter r1(q, clk, reset);
	initial
	clk = 1'b0;
	always
		#5 clk = ~clk;
	initial
		begin
		reset = 1'b1;
		#15 reset = 1'b0;
		#180 reset = 1'b1;
		#10 reset = 1'b0;
		end
        initial 
		  $monitor($time, "output q=%d", q);
endmodule

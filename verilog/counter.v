//Jacob Pledger
//001136676
//Assignment 3

module counter(COUNT_OUT, CLOCK, DIRECTION);
    input CLOCK;
    input DIRECTION;
    output [3:0] COUNT_OUT;
	reg[3:0] count_int = 0;
		always @(posedge CLOCK)
		if(DIRECTION)
			count_int <= count_int + 1;
		else
			count_int <= count_int - 1;
		assign COUNT_OUT = count_int;
endmodule

module stimulus;
	wire [3:0] out;
	reg clk;
	reg dir = 1;
	counter mycounter(out, clk, dir);
	initial
	clk = 1'b0;
	always
		#5 clk = ~clk;
	initial
		begin
			#180 dir = 0;
		end
	initial
		$monitor($time, "---", out);
endmodule

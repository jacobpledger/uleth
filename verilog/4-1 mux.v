module mux(out, i0, i1, i2, i3, s1, s0);
	output out;
	input i0, i1, i2, i3;
	input s1, s0;
	wire s1n, s0n;
	wire c0, c1, c2, c3;
	not(s1n, s1);
	not(s0n, s0);
	and(y0, i0, s1n, s0n);
	and(y1, i1, s1n, s0);
	and(y2, i2, s1, s0n);
	and(y3, i3, s1, s0);
	or(out, y0,y1,y2,y3);
endmodule

module stimulus;
	reg IN0, IN1, IN2, IN3;
	reg S1, S0;
	wire output;
	mux mymux(output, IN0, IN1, IN2, IN3, S1, S0);
	initial
	begin
endmodule

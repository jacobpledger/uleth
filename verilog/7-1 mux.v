module mux(out, i0, i1, i2, i3, i4, i5, i6, s2, s1, s0);
	output out;
	input i0, i1, i2, i3, i4, i5, i6;
	input s2, s1, s0;
	wire s2n, s1n, s0n;
	wire c0, c1, c2, c3, c4, c5, c6;
	not(s2n, s2);
	not(s1n, s1);
	not(s0n, s0);
	and(c0, i0, s2n, s1n, s0n);
	and(c1, i1, s2n, s1n, s0);
	and(c2, i2, s2n, s1, s0n);
	and(c3, i3, s2n, s1, s0);
	and(c4, i4, s2, s1n, s0n);
	and(c5, i5, s2, s1n, s0);
	and(c6, i6, s2, s1, s0n);
	or(out, c0, c1, c2, c3, c4, c5, c6);
endmodule

module stimulus;
	reg I0, I1, I2, I3, I4, I5, I6;
	reg S2, S1, S0;
	wire OUT;
	mux mymux(OUT, I0, I1, I2, I3, I4, I5, I6, S2, S1, S0);
	initial
		begin
		$monitor($time, "I0=%b, I1=%b, I2=%b, I3=%b, I4=%b, I5=%b, I6=%b, S2=%b, S1=%b, S0=%b, -----, OUT=%b", I0, I1, I2, I3, I4, I5, I6, S2, S1, S0, OUT);
		end
		initial
			begin
				#0 I0='b1; I1='b0; I2='b0; I3='b0; I4='b0; I5='b0; I6='b0; S2='b0; S1='b0; S0='b0; //000
				#5 I0='b1; I1='b1; I2='b1; I3='b0; I4='b1; I5='b1; I6='b1; S2='b0; S1='b0; S0='b1; //001
				#5 I0='b1; I1='b0; I2='b0; I3='b0; I4='b1; I5='b0; I6='b1; S2='b0; S1='b1; S0='b0; //010
				#5 I0='b0; I1='b1; I2='b0; I3='b1; I4='b0; I5='b1; I6='b0; S2='b0; S1='b1; S0='b1; //011
				#5 I0='b0; I1='b1; I2='b0; I3='b0; I4='b1; I5='b0; I6='b0; S2='b1; S1='b0; S0='b0; //100
				#5 I0='b1; I1='b1; I2='b1; I3='b0; I4='b1; I5='b1; I6='b1; S2='b1; S1='b0; S0='b1; //101
				#5 I0='b0; I1='b0; I2='b0; I3='b0; I4='b1; I5='b1; I6='b1; S2='b1; S1='b1; S0='b0; //110
				//OUT should be 1,1,0,1,1,1,1
			end
endmodule

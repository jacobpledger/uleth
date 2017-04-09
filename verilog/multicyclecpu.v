//Jacob Pledger
//001136676
//CPU project
//32-bit Multi-cycle CPU

module pc(output [31:0] out, input [31:0] in, input PCWrite);
	reg [31:0] count;
	always @(PCWrite)
		count = in;
	assign out = count;
endmodule

module cache(output [31:0] out, input [31:0] address,data, input MemRead, MemWrite);
	reg[65535:0] cachemem;
	//always @ (MemWrite)
		//assign cachemem [address:(65535-address)] = data;
	//always @(MemRead)
		//assign out = cachemem [address:(address-31)];
endmodule

module inst_reg(output [29:0] jta, output [31:0] rs,rt,rd,imm, input [5:0] op,fn, input [31:0] in, input IRWrite);
	reg [31:0] inst_reg;
	always @(IRWrite)
		inst_reg = in;
	assign op = inst_reg[31:26];
	assign jta = inst_reg[25:0];
	assign rs = inst_reg[25:21];
	assign rt = inst_reg[20:16];
	assign rd = inst_reg[15:11];
	assign imm = inst_reg[15:0];
	assign fn = inst_reg[5:0];
endmodule

module data_reg(output [31:0] out, input [31:0] in);
	reg [31:0] data;
	always @(in)
		data = in;
	assign out = data;
endmodule

module register_file(output [31:0] rs_out,rt_out, input [31:0] rs_in,rt_in,instreg_in,datareg_in, input RegWrite);
	reg [31:0] zero; //system
	reg [31:0] at; //assembler use
	reg [31:0] v0; //procedure results
	reg [31:0] v1;
	reg [31:0] a0; //procedure arguments
	reg [31:0] a1;
	reg [31:0] a2;
	reg [31:0] a3;
	reg [31:0] t0; //temp values
	reg [31:0] t1;
	reg [31:0] t2;
	reg [31:0] t3;
	reg [31:0] t4;
	reg [31:0] t5;
	reg [31:0] t6;
	reg [31:0] t7;
	reg [31:0] s0; //operands, saved accross procedure calls
	reg [31:0] s1;
	reg [31:0] s2;
	reg [31:0] s3;
	reg [31:0] s4;
	reg [31:0] s5;
	reg [31:0] s6;
	reg [31:0] s7;
	reg [31:0] t8; //temp values
	reg [31:0] t9;
	reg [31:0] k0; //kernel
	reg [31:0] k1;
	reg [31:0] gp; //global pointer
	reg [31:0] sp; //stack pointer
	reg [31:0] fp; //frame pointer
	reg [31:0] ra; //return address
endmodule

module xreg(output [31:0] out, input [31:0] rs);
	reg [31:0] x_reg;
	always @(rs)
		x_reg = rs;
	assign out = x_reg;
endmodule

module yreg(output [31:0] out, input [31:0] rt);
	reg [31:0] y_reg;
	always @ (rt)
		y_reg = rt;
	assign out = y_reg;
endmodule

module alu(output[31:0]S,Zero,output Ovfl,input[31:0]a,b,input[1:0]ShiftFunc,LogFunc,FunctionClass,input ConstVar,AddSub);

	//shifter
	wire [4:0] const_amt = 5'd4;
	wire [4:0] amount; //shifter input mux output
	wire [31:0] shifted_b; //output from shifter

	assign amount = ConstVar?(a[4:0]):(const_amt);
	assign shifted_b = ShiftFunc[1]?(ShiftFunc[0]?(b<<<amount):(b>>>amount)):(ShiftFunc[0]?(b<<amount):(b>>amount));
	
	//adder
	wire [31:0] k; //pos/neg y
	wire [31:0] arith_result; //output from adder
	assign k = b^AddSub; //determine pos/neg
	
	wire [32:0] sum = a+b+AddSub;
	assign arith_result = sum[31:0];
	assign Ovfl = sum[32];
	
	//logic
	wire [31:0] logic_result;
	assign logic_result = LogFunc[1]?(LogFunc[0]?(~(a|b)):(a^b)):(LogFunc[0]?(a|b):(a&b));
	
	//main output
	assign S = FunctionClass[1]?(FunctionClass[1]?(logic_result):(arith_result)):(FunctionClass[1]?({32{arith_result[31]}}):(shifted_b));

	//secondary outputs for PSW
	assign Zero = ~(arith_result|1);
endmodule

module zreg(output [31:0] out, input [31:0] in);
	reg [31:0] z_reg;
	always @(in)
		z_reg = in;
	assign out = z_reg;
endmodule

module cpu(output [5:0] op,fn, output [31:0] ALUZero, output ALUOvfl, input [1:0] RegDst,ALUSrcY,PCSrc,ShiftFunc,LogFunc,FunctionClass,input PCWrite,InstData,MemRead,MemWrite,IRWrite,RegInSrc,RegWrite,ALUSrcX,JumpAddr,ConstVar,AddSub);

	//wires
	wire [31:0] pc_in;
	wire [31:0] pc_out;
	wire [31:0] address;
	wire [31:0] zreg_out;
	wire [31:0] cache_out;
	
	wire [29:0] jta;
	wire [31:0] rs;
	wire [31:0] rt;
	wire [31:0] rd;
	wire [31:0] in32 = 32'd31;
	wire [31:0] imm;
	wire [31:0] datareg_out;
	wire [31:0] regfile_uin;
	wire [31:0] regfile_lin;
	wire [31:0] rs_out;
	wire [31:0] rt_out;
	
	wire [31:0] xreg_out;
	wire [31:0] yreg_out;
	wire [31:0] xmux_out;
	wire [31:0] ymux_out;
	
	wire [31:0] alu_out;
	
	wire [29:0] syscall_addr;
	wire [29:0] jta_pcout = {jta,pc_out[31:28]};
	wire [31:0] syscall;
	
	pc cpu_pc(pc_out, pc_in,PCWrite);
	assign address = InstData?(pc_out):(zreg_out);
	cache cpu_cache(cache_out,address,yreg_out,MemRead, MemWrite);
	
	inst_reg cpu_inst_reg(jta,rs,rt,rd,imm,op,fn,cache_out,IRWrite);
	data_reg cpu_data_reg(datareg_out,cache_out);
	
	assign regfile_uin = RegDst[1]?(RegDst[0]?(in32):(in32)):(RegDst[0]?(rd):(rt));
	assign regfile_lin = RegInSrc?(zreg_out):(datareg_out);
	
	register_file cpu_regfile(rs_out, rt_out, rs,rt,regfile_uin,regfile_lin,RegWrite);
	
	xreg cpu_xreg(xreg_out,rs_out);
	yreg cpu_yreg(yreg_out,rt_out);
	
	assign xmux_out = ALUSrcX?(xreg_out):(pc_out);
	assign ymux_out = ALUSrcY[1]?(ALUSrcY[0]?(imm):(imm)):(ALUSrcY[0]?(yreg_out):(32'd4));
	
	alu cpu_alu(alu_out,ALUZero,ALUOvfl,xmux_out,ymux_out,ShiftFunc,LogFunc,FunctionClass,ConstVar,AddSub);
	zreg cpu_zreg(zreg_out,alu_out);
	
	assign syscall = JumpAddr?(jta_pcout):(syscall_addr);
	
	assign pc_in = PCSrc[1]?(PCSrc[0]?(alu_out):(zreg_out)):(PCSrc[0]?(xreg_out):(syscall));
	
endmodule

module op_decoder(output reg RtypeInst,bltz,j,jal,beq,bne,addi,slti,andi,ori,xori,lui,lw,sw, input [5:0] op);
	always @ (op)
	case(op)
		000000: RtypeInst = 1;
		000001: bltz = 1;
		000010: j = 1;
		000011: jal = 1;
		000100: beq = 1;
		//000101:
		//000110: 
		//000111:
		001000: andi = 1;
		//001001: 
		001010: slti = 1;
		//001011: 
		001100: andi = 1;
		001101: ori = 1;
		001110: xori = 1;
		001111: lui = 1;
		/*010000:
		010001:
		010010:
		010011:
		010100:
		010101:
		010110: 
		010111:
		011000:
		011001:
		011010:
		011011:
		011100:
		011101:
		011110:
		011111:
		100000:
		100001:
		100010:*/
		100011: lw = 1;
		/*100100:
		100101:
		100110: 
		100111:
		101000:
		101001:
		101010: */
		101011: sw = 1;
		/*101100:
		101101:
		101110:
		101111:
		110000:
		110001:
		110010:
		110011:
		110100:
		110101:
		110110: 
		110111:
		111000:
		111001:
		111010:
		111011:
		111100:
		111101:
		111110:
		111111:
		default: */
	endcase
endmodule

module fn_decoder(output reg jrInst,syscall,addInst,subInst,andInst,orInst,xorInst,norInst,sltInst, input RtypeInst, input [5:0] fn);
	wire [31:0] enable = fn&RtypeInst;
	always @ (enable)
	case(fn)
		/* 000000: 
		 000001:
		 000010:
		 000011:
		 000100:
		 000101:
		 000110: 
		 000111:*/
		 001000: jrInst = 1;
		/* 001001:
		 001010:
		 001011:*/
		 001100: syscall = 1;
		/* 001101:
		 001110:
		 001111:
		 010000:
		 010001:
		 010010:
		 010011:
		 010100:
		 010101:
		 010110: 
		 010111:
		 011000:
		 011001:
		 011010:
		 011011:
		 011100:
		 011101:
		 011110:
		 011111:*/
		 100000: addInst = 1;
		 //100001:
		 100010: subInst = 1;
		 //100011:
		 100100: andInst = 1;
		 100101: orInst = 1;
		 100110: xorInst = 1;
		 100111: norInst = 1;
		 //101000:
		 //101001:
		 101010: sltInst = 1;
		/* 101011:
		 101100:
		 101101:
		 101110:
		 101111:
		 110000:
		 110001:
		 110010:
		 110011:
		 110100:
		 110101:
		 110110: 
		 110111:
		 111000:
		 111001:
		 111010:
		 111011:
		 111100:
		 111101:
		 111110:
		 111111:
		default:*/
	endcase
endmodule

module control_signal_generator(output reg[3:0] st_out, output reg [1:0] RegDst, LogicFn, FnClass, PCSrc, FunctionClass,LogFunc, output reg PCWrite, InstData, MemRead, MemWrite, IRWrite,RegInSrc,RegWrite, ALUSrcX, ALUSrcY, JumpAddr, AddSub, input [5:0] op, fn, input [3:0] st_in);
	
	//Instruction Signals
	wire RtypeInst,bltzInst,jInst,jalInst,beqInst,bneInst,addiInst,sltiInst,andiInst,oriInst,xoriInst,luiInst,lwInst,swInst,jrInst,syscall,addInst,subInst,andInst,orInst,xorInst,norInst,sltInst;
		
	//help signals
	wire arithInst,logicInst,immInst,aluInst,brjInst,rdInst;
	
	//generate control signals
	op_decoder myopdecoder(RtypeInst,bltzInst,jInst,jalInst,beqInst,bneInst,addiInst,sltiInst,andiInst,oriInst,xoriInst,luiInst,lwInst,swInst,op);
	fn_decoder myfndecoder(jrInst,syscall,addInst,subInst,andInst,orInst,xorInst,norInst,sltInst,RtypeInst,fn);
	
	//instantiate help signals
	or(arithInst,addInst,subInst,sltInst,addiInst,sltiInst); //arithmetic instructions
	or(logicInst,andInst,orInst,xorInst,norInst,andiInst,oriInst,xoriInst); //logic instructions
	or(immInst,luiInst,addiInst,sltiInst,andiInst,oriInst,xoriInst); //immediate instructions
	or(aluInst,arithInst,logicInst,immInst); //alu instructions
	or(brjInst,bltzInst,jInst,jalInst,beqInst,bneInst); //branch/jump instructions
	or(rdInst,addInst,subInst,sltInst,sltiInst,andInst,orInst,xorInst);
	
	always @(st_in)
	case(st_in)
		0000: 
			begin 
			st_out = 4'd1;
			assign InstData = 0;
			MemRead = 1;
			IRWrite = 1;
			ALUSrcX = 0;
			ALUSrcY = 0;
			FunctionClass = 2'd2;
			AddSub = 0;
			PCSrc = 4'd3;
			PCWrite = 1;
			end
		0001: 
			begin
			st_out = brjInst?(4'd5):(lwInst|swInst)?(4'd2):(aluInst?(4'd7):(4'd1));
			ALUSrcX = 0;
			ALUSrcY = 4'd3;
			FunctionClass = 2'd2;
			AddSub = 0;
			end
		0010:
			begin
			st_out = swInst?(4'd6):(lwInst?(4'd3):(4'd2));
			ALUSrcX = 1;
			ALUSrcY = 4'd2;
			FunctionClass = 2'd2;
			AddSub = 0;
			end
		0011:
			begin
			st_out = 4'd4;
			InstData = 1;
			MemRead = 1;
			end
		0100:
		begin
			st_out = 4'd0;
			RegDst = 0;
			RegInSrc = 0;
			RegWrite = 1;
		end
		0101:
			begin
			st_out = 4'd0;
			ALUSrcX = 1;
			ALUSrcY = 4'd1;
			FunctionClass = 2'd2;
			AddSub = 1;
			JumpAddr = 0;
			PCSrc = 0;
			PCWrite = 1;
			end
		0110:
			begin
			st_out = 4'd0;
			InstData = 1;
			MemWrite = 1;
			end
		0111:
			begin
			st_out = 4'd8;
			ALUSrcX = 1;
			ALUSrcY = immInst?(2'd2):(2'd1);
			//ShiftFunc;
			//ConstVar;
			assign LogFunc = andInst?(2'b0):(orInst?(2'd1):(xorInst?(2'd2):(norInst?(2'd3):(2'd0))));
			FunctionClass = 2'd2;
			AddSub = 0;
			end
		1000:
			begin
			st_out = 4'd0;
			assign RegDst = rdInst?(2'd1):(2'd0);
			RegInSrc = 1;
			RegWrite = 1;
			end
		/*1001:
		1010:
		1011:
		1100:
		1101:
		1110:
		1111:*/
	endcase
endmodule

module stimulus;

wire [5:0] op,fn;
wire [31:0] ALUZero;
wire ALUOvfl;
wire [1:0] RegDst,ALUSrcY,PCSrc,ShiftFunc,LogFunc,FunctionClass;
wire PCWrite,InstData,MemRead,MemWrite,IRWrite,RegInSrc,RegWrite,ALUSrcX,JumpAddr,ConstVar,AddSub;
wire[3:0] st;

control_signal_generator mycontsiggen(st,RegDst,LogFunc,FnClass,PCSrc,FunctionClass,LogFunc,PCWrite,InstData,MemRead,MemWrite,IRWrite,RegInSrc,RegWrite,ALUSrcX,ALUSrcY,JumpAddr,AddSub,op,fn,st);
cpu mycpu(op,fn,ALUZero,ALUOvfl,RegDst,ALUSrcY,PCSrc,ShiftFunc,LogFunc,FunctionClass,PCWrite,InstData,MemRead,MemWrite,IRWrite,RegInSrc,RegWrite,ALUSrcX,JumpAddr,ConstVar,AddSub);
	
endmodule

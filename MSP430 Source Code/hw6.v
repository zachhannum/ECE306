module hw6 (
	input clk, rst_n,
	input serial,
	output detect
);

	reg cstate[2:0];
	reg nstate[2:0];

	always @ (posedge clk) begin
	if(!rst_n)
		cstate <= 0;
	else
		cstate <= nstate;
	end
	
	always@ * begin
	
	case 
	
	0: begin
		if(serial)
			nstate <= 1;
		else
			nstate <= 0;
		detect <= 0;
	end
	
	1: begin
		if(serial)
			nstate <= 1;
		else
			nstate <= 2;
		detect <= 0;
	end
	
	2: begin
		if(serial)
			nstate <= 3;
		else
			nstate <= 0;
		detect <= 0;
	end
	
	3: begin
		if(serial)
			nstate <= 4;
		else
			nstate <= 2;
		detect <= 0;
	end
	
	4: begin
		if(serial)
			nstate <= 1;
		else
			nstate <= 0;
		detect <= 1;
	end
	endcase
	end
endmodule


module hw6_tb;

	reg rst_n, clk;
	reg serial;
	wire detect;
	
	hw6 u1(clk, rst_n, serial, detect);
	
	always
		#5 clk <= ~clk
		
	initial begin
	rst_n <= 0;
	serial <= 0;
	#10 rst_n <= 1;
	#10 serial <= 1;
	#10 serial <= 0;
	#10 serial <= 1;
	#10 serial <= 1;
	#10 serial <= 0;
	#10 serial <= 1;
	#10 serial <= 1;
	#10 serial <= 1;
	#10 serial <= 0;
	#10 serial <= 1;
	#10 serial <= 1;
	#10 serial <= 0;
	#10 serial <= 0;
	#10 serial <= 1;
	#10 serial <= 0;
	#10 serial <= 1;
	#10 serial <= 1;
	#10 serial <= 1;
	#10
	
	end
	
endmodule
	
	
	
	
	
	
	
	
	end
	
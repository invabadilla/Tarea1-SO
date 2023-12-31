// platform_CPU_0.v

// This file was auto-generated from altera_nios2_hw.tcl.  If you edit it your changes
// will probably be lost.
// 
// Generated using ACDS version 20.1 711

`timescale 1 ps / 1 ps
module platform_CPU_0 (
		input  wire        clk,           //                       clk.clk
		input  wire        reset_n,       //                     reset.reset_n
		output wire [14:0] d_address,     //               data_master.address
		output wire [3:0]  d_byteenable,  //                          .byteenable
		output wire        d_read,        //                          .read
		input  wire [31:0] d_readdata,    //                          .readdata
		input  wire        d_waitrequest, //                          .waitrequest
		output wire        d_write,       //                          .write
		output wire [31:0] d_writedata,   //                          .writedata
		output wire [14:0] i_address,     //        instruction_master.address
		output wire        i_read,        //                          .read
		input  wire [31:0] i_readdata,    //                          .readdata
		input  wire        i_waitrequest, //                          .waitrequest
		input  wire [31:0] irq,           //                       irq.irq
		output wire        dummy_ci_port  // custom_instruction_master.readra
	);

	platform_CPU_0_cpu cpu (
		.clk           (clk),           //                       clk.clk
		.reset_n       (reset_n),       //                     reset.reset_n
		.d_address     (d_address),     //               data_master.address
		.d_byteenable  (d_byteenable),  //                          .byteenable
		.d_read        (d_read),        //                          .read
		.d_readdata    (d_readdata),    //                          .readdata
		.d_waitrequest (d_waitrequest), //                          .waitrequest
		.d_write       (d_write),       //                          .write
		.d_writedata   (d_writedata),   //                          .writedata
		.i_address     (i_address),     //        instruction_master.address
		.i_read        (i_read),        //                          .read
		.i_readdata    (i_readdata),    //                          .readdata
		.i_waitrequest (i_waitrequest), //                          .waitrequest
		.irq           (irq),           //                       irq.irq
		.dummy_ci_port (dummy_ci_port)  // custom_instruction_master.readra
	);

endmodule

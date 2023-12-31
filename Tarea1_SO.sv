module Tarea1_SO (
		input  logic        clk,
		input  logic 		  button_0,
		input  logic 		  button_1,		
		input  logic        rst_n,                            
		input  logic [1:0]  switches,		
		output logic [13:0] segm_min, 
		output logic [13:0] segm_ms,  
		output logic [13:0] segm_s   
);

	platform plat (
		.button_0_external_connection_export(button_0),
		.button_1_external_connection_export(button_1)	,	
		.clk_clk(clk),                               
		.reset_reset_n(rst_n),                        
		.segm_min_0_external_connection_export(segm_min), 
		.segm_ms_0_external_connection_export(segm_ms),  
		.segm_s_0_external_connection_export(segm_s),   
		.switches_0_external_connection_export(switches)
	);

	
endmodule 
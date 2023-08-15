
module platform (
	clk_clk,
	reset_reset_n,
	switches_0_external_connection_export,
	segm_ms_0_external_connection_export,
	segm_s_0_external_connection_export,
	segm_min_0_external_connection_export,
	button_0_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[1:0]	switches_0_external_connection_export;
	output	[13:0]	segm_ms_0_external_connection_export;
	output	[13:0]	segm_s_0_external_connection_export;
	output	[13:0]	segm_min_0_external_connection_export;
	input		button_0_external_connection_export;
endmodule

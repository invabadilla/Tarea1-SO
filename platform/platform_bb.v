
module platform (
	clk_clk,
	reset_reset_n,
	switches_0_external_connection_export,
	pio_0_external_connection_export,
	id7segm_ms_0_external_connection_export,
	id7segm_s_0_external_connection_export,
	id7segm_min_0_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[2:0]	switches_0_external_connection_export;
	input	[1:0]	pio_0_external_connection_export;
	output	[13:0]	id7segm_ms_0_external_connection_export;
	output	[13:0]	id7segm_s_0_external_connection_export;
	output	[13:0]	id7segm_min_0_external_connection_export;
endmodule

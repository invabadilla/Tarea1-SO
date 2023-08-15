	component platform is
		port (
			clk_clk                               : in  std_logic                     := 'X';             -- clk
			reset_reset_n                         : in  std_logic                     := 'X';             -- reset_n
			switches_0_external_connection_export : in  std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			segm_ms_0_external_connection_export  : out std_logic_vector(13 downto 0);                    -- export
			segm_s_0_external_connection_export   : out std_logic_vector(13 downto 0);                    -- export
			segm_min_0_external_connection_export : out std_logic_vector(13 downto 0);                    -- export
			button_0_external_connection_export   : in  std_logic                     := 'X'              -- export
		);
	end component platform;

	u0 : component platform
		port map (
			clk_clk                               => CONNECTED_TO_clk_clk,                               --                            clk.clk
			reset_reset_n                         => CONNECTED_TO_reset_reset_n,                         --                          reset.reset_n
			switches_0_external_connection_export => CONNECTED_TO_switches_0_external_connection_export, -- switches_0_external_connection.export
			segm_ms_0_external_connection_export  => CONNECTED_TO_segm_ms_0_external_connection_export,  --  segm_ms_0_external_connection.export
			segm_s_0_external_connection_export   => CONNECTED_TO_segm_s_0_external_connection_export,   --   segm_s_0_external_connection.export
			segm_min_0_external_connection_export => CONNECTED_TO_segm_min_0_external_connection_export, -- segm_min_0_external_connection.export
			button_0_external_connection_export   => CONNECTED_TO_button_0_external_connection_export    --   button_0_external_connection.export
		);


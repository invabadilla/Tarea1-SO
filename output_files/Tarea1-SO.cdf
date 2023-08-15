/* Quartus Prime Version 20.1.0 Build 711 06/05/2020 SJ Lite Edition */
JedecChain;
	FileRevision(JESD32A);
	DefaultMfr(6E);

	P ActionCode(Ign)
		Device PartName(5CSEMA5F31) MfrSpec(OpMask(0) FullPath("D:/Proyectos/Quartus/Tarea1-SO/output_files/Tarea1-SO.sof"));
	P ActionCode(Cfg)
		Device PartName(5CSEMA5F31) Path("D:/Proyectos/Quartus/Tarea1-SO/output_files/") File("Tarea1-SO.sof") MfrSpec(OpMask(1));

ChainEnd;

AlteraBegin;
	ChainType(JTAG);
AlteraEnd;

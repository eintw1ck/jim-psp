PspPacker Readme
----------------

PSPPacker currently only works with PRXes

How to use:
	generate payload.S with bin2s:
		bin2s your_prog.prx payload.S payload
		
	edit payload.s and add the following:
		.globl size_payload_uncomp
		size_payload_uncomp: .word <size of payload before compression (in bytes)>
	compile
	run :)
	
See main.c for todo

  - John_K
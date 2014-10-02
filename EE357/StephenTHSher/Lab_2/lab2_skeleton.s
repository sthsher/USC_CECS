// Lab #2 Up/Down Counter
// Place static data declarations/directives here
  		.data
INITIAL:	.dc.w 3
STEP:		.dc.w 1
SPEEDS:		.dc.w 4
MINSPEED:	.dc.w 3
MAXSPEED: 	.ds.l 1 
			.text
			.global _main
			.global main
			.global mydat
			.include "../Project_Headers/ee357_asm_lib_hdr.s"

_main:
main:	
//------- Template: Add Code Here ----- //












//======= Let the following few lines always end your main routing ===//		
//------- No OS to return to so loop ---- //
//------- infinitely...Never hits rts --- //		
inflp:	bra.s	inflp
		rts
		

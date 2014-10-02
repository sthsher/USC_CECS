// Lab #2 Up/Down Counter
// Place static data declarations/directives here
  		.data
INITIAL:	.dc.w 3
STEP:		.dc.w 1
SPEEDS:		.dc.w 4
MINSPEED:	.dc.w 3
MAXSPEED:	.dc.w 1
			.text
			.global _main
			.global main
			.global mydat
			.include "../Project_Headers/ee357_asm_lib_hdr.s"

_main:
main:	
//------- Template: Add Code Here ----- //

	//variables
	//d5 holds interval amount
	//d4 holds number for one second
	//d3 holds the inital number to use
	//d2 holds the time delay
	//d1 holds the counter amount

	//Initialize LED's
	move.l 		#0x0,			d0
	move.b 		d0,				0x4010006F		//set pins to be used GPIO
	move.l		#0xFFFFFFFF,	d0
	move.b		d0,				0x40100027		//Set LED's as output
	
	//Initialize value INITIAL for the LED's
	move.w		INITIAL,		d1
	move.b		d1,				0x4010000F

	move.l		#45000000,		d4				//d4 holds clock speed
	clr.l 		d3
	move.l 		d4,				d3				//d3 will hold interval

	//Calcualate interval amounts
	move.w		MINSPEED,		d5				//d5 holds minspeed
	move.w		MAXSPEED,		d6				//d6 holds maxspeed
	sub.l		d6,				d5				//d5 now holds the difference
	move.w		SPEEDS,			d6				//d6 now holds the number of speeds
	subq.l		#0x1,			d6				//d6 now holds denonminator

	divs.w		d6,				d3				//divide by denonminator
	muls.w 		d5,				d3
	

	//This will calculate the speed desired
	//right now it's set to 2
	muls.w 		#2,				d3				//d3 will hold 
	add.l 		d3,				d4		



//The inifinite loop
LOOP1:
	//Inner loop delay: this sets the time
	//move.l		#0xffffff,		d2
	
	move.l 		d4,				d2

	LOOP2:
		subq.l	#0x1, 			d2
		bne.s	LOOP2

	addq.l		#0x1,			d1
	move.b		d1,				0x4010000F		//Light up LED's
	
	bra.s LOOP1



//======= Let the following few lines always end your main routing ===//		
//------- No OS to return to so loop ---- //
//------- infinitely...Never hits rts --- //		
inflp:	bra.s	inflp
		rts
		

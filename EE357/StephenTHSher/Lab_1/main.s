// Place static data declarations/directives here
        .data
welcomeMessage:  	.asciz "This is EE357 Lab 1! \nCatching the Bus \n"  // Remember to put and get
finalMessage:		.asciz "The final number of people on the bus is: "
INITIAL:	.dc.w 5
STOPS:		.dc.w 7
LEAVING:	.dc.w 0,3,22,100,17,19
ARRIVING:	.dc.w 10,80,45,15,166,64
bus:		.ds.l 1
		.text
		.global _main
		.global main
		.global mydat
		.include "../Project_Headers/ee357_asm_lib_hdr.s"

_main:
main:	
//------- Template Test: Replace Me ----- //

welc: 	movea.l #welcomeMessage, a1
		jsr ee357_put_str				//jump to put string subroutine	
		
		//d1 holds results
		//d2 holds temp values to operate with
		//d3 holds loop counter
		
		//a1 is ARRIVING
		//a2 is LEAVING

init:	movea.l 	#ARRIVING, 	a1		//put LEAVING vector into a2
		movea.l 	#LEAVING, 	a2		//put ARRIVING vector into a1
		move.w 		STOPS,		d4		//put number of stops into d1
		sub.l		#1,			d4		//last stop is not a part of arrive/leaving process, thus loop one less time than STOPS
		move.w 		INITIAL, 	d1		//put initial number of people in d0
		clr.w		d2
		
		//Calculate LEAVING / ARRIVING
loop:	move.w		(a1)+,		d2		//move arriving to d2
		add.l		d2,			d1		//add arriving to d1

		move.w		(a2)+,		d2		//move leaving to d2
		sub.l		d2,			d1		//sub leaving to d1
		
		sub.l 		#1,			d4		//decrement STOPS (for loop)
		bgt loop						//loop if counter is greater than 0
		
		//Calculate 3/4ths of the number of people left (1/4 leaves)
		clr.l 		d2
		add.l 		d1,			d2
		lsr.l 		#2, 		d2
		sub.l 		d2,			d1

		
final:	movea.l	#finalMessage,	a1		//print final message
		jsr ee357_put_str
		jsr ee357_put_int
	  
	  
//======= Let the following few lines always end your main routing ===//		
//------- No OS to return to so loop ---- //
//------- infinitely...Never hits rts --- //		
inflp:	bra.s	inflp
		rts
		


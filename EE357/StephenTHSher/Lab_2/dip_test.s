
	//Dip Switches
	//Setup addresses
	move.l 		#0x00000000,	d0
	move.b 		d0,				0x4010002C


	move.b 		0x40100044,		d4				
	lsr.l 		#4,				d4
	move.b 		d4, 			d3
	lsr.l 		#3,				d3				//d3 will hold direction, 0 for down, 1 for up

	if (d3 == 0){
		//down count
		//d4 is holding the speed option
		//Rest of loop
	}
	else{
		//up count
		sub.l 	#8,				d4
		//Get rid of the 4th bit
		//rest of loop
	}

For speeds:
There will be a register that holds the interval values (let's say d5)

To update the speed, multiply d5 by d4 (as shown above).

Then move d5 into d2, which will be the loop counter


move.l		#45000000,		d4

//Get parameters
move.w		MINSPEED,		d5
move.w		MAXSPEED,		d6
muls.l		d4,				d5
muls.l		d4,				d6		//d5 and d6 now holds amount of clocks for MIN and MAX
move.w		d6,				d4		//d4 now also holds MAX speed
sub.l		d6,				d5		//d5 holds difference

move.w		SPEEDS,			d6		//d5 holds SPEEDS
subq.l		#0x1,			d6		//Subtract 1 for intervals

divs.l		d6,				d5		//d5 now holds intervals in seconds

//now final steps
clr.l		d6
move.w		TEMP,			d6		//d6 holds desired speed option, multiply it by interval
muls.l		d5,				d6		//d6 now holds value to add onto MAX
add.l		d6,				d4		//ADDED!
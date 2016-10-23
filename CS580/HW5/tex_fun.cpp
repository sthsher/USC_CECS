/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"
#include	"math.h"

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

#include <fstream>

#define	ARRAY(x,y,xres)	(x+(y*xres))	

void pC(GzColor c)
{
	std::ofstream console("console.txt", std::ios::app);
	console << "[";
	for (int i = 0; i < 3; ++i)
	{
		console << c[i] << " ";
	}
	console << "]";
	console << std::endl;
}

void equateColor(GzColor& lhs, const GzCoord rhs)
{
	lhs[RED] = rhs[RED];
	lhs[GREEN] = rhs[GREEN];
	lhs[BLUE] = rhs[BLUE];
}

/* Image texture function */
int tex_fun(float u, float v, GzColor color)
{

	std::ofstream console("console.txt", std::ios::app);
	unsigned char		pixel[3];
	unsigned char     dummy;
	char  		foo[8];
	int   		i, j;
	FILE			*fd;

	if (reset) {          /* open and load texture file */
		fd = fopen ("texture", "rb");
		if (fd == NULL) {
		console << "EXIT\n";

			exit(-1);
		}
		fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
		image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
		if (image == NULL) {
			fprintf (stderr, "malloc for texture image failed\n");
			exit(-1);
		}

		for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
			fread(pixel, sizeof(pixel), 1, fd);
			image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
			image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
			image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
			}

		reset = 0;          /* init is done */
	fclose(fd);


	}

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */

	//scale uv values
	u *= (xs - 1);
	v *= (ys - 1);

	GzColor tl, tr, bl, br;

	equateColor(tl, image[ARRAY(static_cast<int>(std::floor(u)), static_cast<int>(std::floor(v)), xs)]);
	equateColor(tr, image[ARRAY(static_cast<int>(std::ceil(u)), static_cast<int>(std::floor(v)), xs)]);
	equateColor(bl, image[ARRAY(static_cast<int>(std::floor(u)), static_cast<int>(std::ceil(v)), xs)]);
	equateColor(br, image[ARRAY(static_cast<int>(std::ceil(u)), static_cast<int>(std::ceil(v)), xs)]);

	double t = v - std::floor(v);
	double s = u - std::floor(u);


	color[RED] = (s * t * br[RED]) + ((1 - s) * t * bl[RED]) + (s * (1 - t) * tr[RED]) + ((1 - s) * (1 - t) * tl[RED]);
	color[GREEN] = (s * t * br[GREEN]) + ((1 - s) * t * bl[GREEN]) + (s * (1 - t) * tr[GREEN]) + ((1 - s) * (1 - t) * tl[GREEN]);
	color[BLUE] = (s * t * br[BLUE]) + ((1 - s) * t * bl[BLUE]) + (s * (1 - t) * tr[BLUE]) + ((1 - s) * (1 - t) * tl[BLUE]);
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
	int tweak = 64;
	int offset = .5;

	//colors are between 0 and 1, scale to 0 and 255
	u *= tweak;
	v *= tweak;

	//center is 128 128

	//calculate distance to center

	float distance = std::sqrt(std::pow(u - (tweak/2), 2) + std::pow(v - (tweak/2), 2));

	color[RED] = (std::sin(distance)) + offset;
	color[GREEN] = (std::asin(distance)) + (2*offset);
	color[BLUE] = (std::sin(distance)) + (4*offset);

	return 0;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}


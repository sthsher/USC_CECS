/*   CS580 HW1 display functions to be completed   */

#include   "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"

#include <string>

int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- pass back pointer 
 */
	//check proper resolution
	if (width < 1 || height < 1)
	{
		return GZ_FAILURE;
	}

	//allocate memory, will be in form of
	//[b1,g1,r1,b2,g2,r2] etc..

	int mem = 3 * width * height;
	(*framebuffer) = new char[mem];

	return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay	**display, int xRes, int yRes)
{
/* HW1.2 create a display:
  -- allocate memory for indicated resolution
  -- pass back pointer to GzDisplay object in display
*/
	if (xRes < 1 || xRes > MAXXRES)
	{
		return GZ_FAILURE;
	}
	if (yRes < 1 || yRes > MAXYRES)
	{
		return GZ_FAILURE;
	}

	int resolution = xRes * yRes;

	//initialize members
	(*display) = new GzDisplay;
	(*display)->xres = xRes;
	(*display)->yres = yRes;
	(*display)->fbuf = new GzPixel[resolution];

	return GZ_SUCCESS;
}


int GzFreeDisplay(GzDisplay	*display)
{
/* HW1.3 clean up, free memory */

	delete display;

	return GZ_SUCCESS;
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes)
{
/* HW1.4 pass back values for a display */

	//pass by pointers, so just dereference the pointers
	(*xRes) = display->xres;
	(*yRes) = display->yres;

	return GZ_SUCCESS;
}

#include <string>

int GzInitDisplay(GzDisplay	*display)
{
/* HW1.5 set everything to some default values - start a new frame */

	//set background color
	int resolution = display->xres * display->yres;

	for (int i = 0; i < resolution; ++i)
	{
		(display->fbuf)[i].red = 3000;
		(display->fbuf)[i].green = 3000;
		(display->fbuf)[i].blue = 3000;
		(display->fbuf)[i].alpha = 1;
		(display->fbuf)[i].z = 0;
	}

	return GZ_SUCCESS;
}

int ClampGzIntensity(GzIntensity x)
{
	if (x < 0) return 0;
	else if (x > 4095) return 4095;
	else return x;
}

int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.6 write pixel values into the display */

	//check i and j values
	if (i > -1 && i < display->xres &&
		j > -1 && j < display->yres)
	{
		int index = (j*(display->xres)) + i;

		//clamp the rgb values
		r = ClampGzIntensity(r);
		g = ClampGzIntensity(g);
		b = ClampGzIntensity(b);
		a = ClampGzIntensity(a);
		z = ClampGzIntensity(z);

		(display->fbuf)[index].red = r;
		(display->fbuf)[index].green = g;
		(display->fbuf)[index].blue = b;
		(display->fbuf)[index].alpha = a;
		(display->fbuf)[index].z = z;
	}
	return GZ_SUCCESS;
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.7 pass back a pixel value to the display */

	//once again check for valid values
	if (i > -1 && i < display->xres &&
		j > -1 && j < display->yres)
	{
		int index = (j * (display->xres)) + i;
		*r = (display->fbuf)[index].red;
		*g = (display->fbuf)[index].green;
		*b = (display->fbuf)[index].blue;
		*a = (display->fbuf)[index].alpha;
		*z = (display->fbuf)[index].z;
	}

	return GZ_SUCCESS;
}


int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{
/* HW1.8 write pixels to ppm file -- "P6 %d %d 255\r" */

	//write P6 xres yres 255\r
	
	//header
	fputs("P6 ", outfile);
	fputs(std::to_string(display->xres).c_str(), outfile);
	fputs(" ", outfile);
	fputs(std::to_string(display->yres).c_str(), outfile);
	fputs(" 255\r", outfile);

	int resolution = display->xres * display->yres;

	//every pixel
	for (int i = 0; i < resolution; ++i)
	{
		GzIntensity blue = display->fbuf[i].blue;
		GzIntensity green = display->fbuf[i].green;
		GzIntensity red = display->fbuf[i].red;

		unsigned char b = static_cast<unsigned char>(blue >> 4);
		unsigned char g = static_cast<unsigned char>(green >> 4);
		unsigned char r = static_cast<unsigned char>(red >> 4);

		fwrite(&r, sizeof(unsigned char), sizeof(unsigned char), outfile);
		fwrite(&g, sizeof(unsigned char), sizeof(unsigned char), outfile);
		fwrite(&b, sizeof(unsigned char), sizeof(unsigned char), outfile);
	}

	return GZ_SUCCESS;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{

/* HW1.9 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/

	int resolution = display->xres * display->yres;

	for (int i = 0; i < resolution; ++i)
	{
		//wrote blue green red
		GzIntensity blue = display->fbuf[i].blue;
		GzIntensity green = display->fbuf[i].green;
		GzIntensity red = display->fbuf[i].red;

		unsigned char b = static_cast<unsigned char>(blue >> 4);
		unsigned char g = static_cast<unsigned char>(green >> 4);
		unsigned char r = static_cast<unsigned char>(red >> 4);

		framebuffer[(i * 3) + 0] = b;
		framebuffer[(i * 3) + 1] = g;
		framebuffer[(i * 3) + 2] = r;
	}
	

	return GZ_SUCCESS;
}
#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

short ctoi(float color);

int GzNewRender(GzRender **render, GzDisplay *display)
{
/* 
- malloc a renderer struct
- span interpolator needs pointer to display for pixel writes
*/
	*render = new GzRender;
	(*render)->display = display;

	return GZ_SUCCESS;
}


int GzFreeRender(GzRender *render)
{
/* 
-free all renderer resources
*/
	if (render != NULL)
	{
		delete render;
	}

	return GZ_SUCCESS;
}


int GzBeginRender(GzRender	*render)
{
/* 
- set up for start of each frame - init frame buffer
*/

	if (GzInitDisplay(render->display) == GZ_SUCCESS) 
	{
		return GZ_SUCCESS;
	}
	else
	{
		return GZ_FAILURE;
	}
}


int GzPutAttribute(GzRender	*render, int numAttributes,
	GzToken	*nameList, GzPointer *valueList) /* void** valuelist */
{
/*
- set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
- later set shaders, interpolaters, texture maps, and lights
*/
	//iterate through the attributes and look at the identifier in nameList
	//
	for (int i = 0; i < numAttributes; ++i)
	{
		if (*nameList == GZ_RGB_COLOR)
		{
			render->flatcolor[RED] = *((static_cast<GzColor*>(*valueList))[RED]);
			render->flatcolor[GREEN] = *((static_cast<GzColor*>(*valueList))[GREEN]);
			render->flatcolor[BLUE] = *((static_cast<GzColor*>(*valueList))[BLUE]);
		}

		//iterate GzToken
		nameList += 1;
		//iterate GzPointer
		valueList += sizeof(GzToken);
	}

	return GZ_SUCCESS;
}

#include <fstream>

#define TOP 0
#define LEFT 1
#define RIGHT 2

void equateGzCoord(GzCoord& left, const GzCoord right)
{
	left[X] = right[X];
	left[Y] = right[Y];
	left[Z] = right[Z];
}

bool equalityGzCoord(const GzCoord a, const GzCoord b)
{
	return ((a[X] == b[X]) && (a[Y] == b[Y]) && (a[Z] == b[Z]));
}

float calculateSlope(const GzCoord point1, const GzCoord point2)
{
	float x1 = point1[X];
	float x2 = point2[X];
	float y1 = point1[Y];
	float y2 = point2[Y];

	float xDelta = x2 - x1;
	float yDelta = y2 - y1;
	return xDelta / yDelta;
}

int interpolateZ(const GzCoord* vertices, const int x, const int y)
{
	//Plane : Ax + By + Cz + D = 0
	//D = -Ax - By - Cz = (-1) * (Ax + By + Cz)

	//cross product two vertices to get normal
	//A x B = (a2b3 - a3b2, a3b1 - a1b3, a1b2 - a2b1)
	GzCoord vecA;
	vecA[X] = vertices[TOP][X] - vertices[LEFT][X];
	vecA[Y] = vertices[TOP][Y] - vertices[LEFT][Y];
	vecA[Z] = vertices[TOP][Z] - vertices[LEFT][Z];

	GzCoord vecB;
	vecB[X] = vertices[LEFT][X] - vertices[RIGHT][X];
	vecB[Y] = vertices[LEFT][Y] - vertices[RIGHT][Y];
	vecB[Z] = vertices[LEFT][Z] - vertices[RIGHT][Z];

	float A, B, C;
	A = (vecA[Y] * vecB[Z]) - (vecA[Z] * vecB[Y]);
	B = (vecA[Z] * vecB[X]) - (vecA[X] * vecB[Z]);
	C = (vecA[X] * vecB[Y]) - (vecA[Y] * vecB[X]);

	//Calcualte D
	float D = (-1) * ((A * vertices[TOP][X]) + (B * vertices[TOP][Y]) + (C * vertices[TOP][Z]));

	//Interpolate
	//z = (-1) * (D + Ax + By)  /  C
	return static_cast<int>((((-1) * (D + (A*x) + (B*y))) / C));
}

int GzPutTriangle(GzRender *render, int	numParts,
	GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
/* 
- pass in a triangle description with tokens and values corresponding to
      GZ_NULL_TOKEN:		do nothing - no values
      GZ_POSITION:		3 vert positions 
- Invoke the scan converter and return an error code
*/

	for (int p = 0; p < numParts; ++p)
	{
		if (*nameList == GZ_NULL_TOKEN)
		{
			//do nothing
		}
		else if (*nameList == GZ_POSITION)
		{
			//get the 3 vertices
			GzCoord vertexA;
			GzCoord vertexB;
			GzCoord vertexC;

			equateGzCoord(vertexA, (static_cast<GzCoord*>(*valueList))[0]);
			equateGzCoord(vertexB, (static_cast<GzCoord*>(*valueList))[1]);
			equateGzCoord(vertexC, (static_cast<GzCoord*>(*valueList))[2]);


			//find the points of interest, in form of [topmost, left, right]
			GzCoord vertices[3];

			//Case A
			if (vertexA[Y] <= vertexB[Y] && vertexA[Y] <= vertexC[Y])
			{
				equateGzCoord(vertices[TOP], vertexA);
			}
			//Case B
			else if (vertexB[Y] <= vertexA[Y] && vertexB[Y] <= vertexC[Y])
			{
				equateGzCoord(vertices[TOP], vertexB);
			}

			//Case C
			else
			{
				equateGzCoord(vertices[TOP], vertexC);
			}

			//Now identify leftmost & rightmost
			if (equalityGzCoord(vertices[TOP], vertexA))
			{
				//B & C
				vertexB[X] <= vertexC[X] ? equateGzCoord(vertices[LEFT], vertexB) : equateGzCoord(vertices[LEFT], vertexC);
				vertexB[X] <= vertexC[X] ? equateGzCoord(vertices[RIGHT], vertexC) : equateGzCoord(vertices[RIGHT], vertexB);
			}
			else if (equalityGzCoord(vertices[TOP], vertexB))
			{
				//A & C
				vertexA[X] <= vertexC[X] ? equateGzCoord(vertices[LEFT], vertexA) : equateGzCoord(vertices[LEFT], vertexC);
				vertexA[X] <= vertexC[X] ? equateGzCoord(vertices[RIGHT], vertexC) : equateGzCoord(vertices[RIGHT], vertexA);
			}
			else
			{
				//A & B
				vertexA[X] <= vertexB[X] ? equateGzCoord(vertices[LEFT], vertexA) : equateGzCoord(vertices[LEFT], vertexB);
				vertexA[X] <= vertexB[X] ? equateGzCoord(vertices[RIGHT], vertexB) : equateGzCoord(vertices[RIGHT], vertexA);
			}

			//std::ofstream console("console.txt", std::ios::app);
			//console << "Triangle:" << std::endl;
			//console << "VertexA: " << vertexA[X] << " " << vertexA[Y] << " " << vertexA[Z] << std::endl;
			//console << "VertexB: " << vertexB[X] << " " << vertexB[Y] << " " << vertexB[Z] << std::endl;
			//console << "VertexC: " << vertexC[X] << " " << vertexC[Y] << " " << vertexC[Z] << std::endl;
			//console << "Top    : " << vertices[TOP][X] << " " << vertices[TOP][Y] << " " << vertices[TOP][Z] << std::endl;
			//console << "LEFT   : " << vertices[LEFT][X] << " " << vertices[LEFT][Y] << " " << vertices[LEFT][Z] << std::endl;
			//console << "RIGHT  : " << vertices[RIGHT][X] << " " << vertices[RIGHT][Y] << " " << vertices[RIGHT][Z] << std::endl;
			//console << std::endl;


			//Doesn't seem to happen
			//if (vertices[TOP][Y] == vertices[LEFT][Y] || vertices[TOP][Y] == vertices[RIGHT][Y])
			//{
			//	std::ofstream console("console.txt", std::ios::app);
			//	console << "Special case\n";
			//}

			//see if TOP is a pixel
			if (ceil(vertices[TOP][X] == vertices[TOP][X] && ceil(vertices[TOP][Y] == vertices[TOP][Y])))
			{
				int i = static_cast<int>(vertices[TOP][X]);
				int j = static_cast<int>(vertices[TOP][Y]);
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//put onto display
				GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
			}

			//Case 1:
			//Left is lower than right
			/*
						TOP

									RIGHT


					LEFT
			*/
			if (vertices[LEFT][Y] > vertices[RIGHT][Y])
			{
				//calculate slopes
				float mainSlope = calculateSlope(vertices[TOP], vertices[LEFT]);
				float slopeA = calculateSlope(vertices[TOP], vertices[RIGHT]);
				float slopeB = calculateSlope(vertices[RIGHT], vertices[LEFT]);

				float xLeft = vertices[TOP][X];
				float xRight = vertices[TOP][X];

				//TODO: see if the starting vertex is a pixel

				//loop throught main loop
				for (float j = ceil(vertices[TOP][Y]); j < vertices[LEFT][Y]; j = j + 1)
				{
					//increment xLeft and xRight
					xLeft += mainSlope;
					j < vertices[RIGHT][Y] ? xRight += slopeA : xRight += slopeB;

					//check bounds, clamp if necessary
					if (xLeft < 0 || xLeft > render->display->xres) xLeft = vertices[LEFT][X];
					if (xRight < 0 || xRight > render->display->xres) xRight = vertices[RIGHT][X];

					//iterate pixels from xLeft to xRight
					for (float i = floor(xLeft); i < xRight; i = i + 1)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, static_cast<int>(i), static_cast<int>(j));

						//put onto display
						GzPutDisplay(render->display, static_cast<int>(i), static_cast<int>(j), ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}
			}

			//Case 2:
			//Left is higher than right
			/*
						TOP


				LEFT

								RIGHT
			*/
			else if (vertices[LEFT][Y] < vertices[RIGHT][Y])
			{
				float mainSlope = calculateSlope(vertices[TOP], vertices[RIGHT]);
				float slopeA = calculateSlope(vertices[TOP], vertices[LEFT]);
				float slopeB = calculateSlope(vertices[LEFT], vertices[RIGHT]);

				float xLeft = vertices[TOP][X];
				float xRight = vertices[TOP][X];

				//TODO: see if the starting vertex is a pixel

				//loop throught main loop
				for (int j = ceil(vertices[TOP][Y]); j < vertices[RIGHT][Y]; ++j)
				{
					//increment xLeft and xRight
					xRight += mainSlope;
					j < vertices[LEFT][Y] ? xLeft += slopeA : xLeft += slopeB;

					//check bounds
					if (xLeft < 0 || xLeft > render->display->xres) xLeft = vertices[LEFT][X];
					if (xRight < 0 || xRight > render->display->xres) xRight = vertices[RIGHT][X];

					//iterate pixels from xLeft to xRight
					for (int i = floor(xLeft); i < xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//put onto display
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}
			}

			//Case 2:
			//Left and right are equal
			/*
							TOP


					LEFT			RIGHT
			*/
			else if (vertices[LEFT][Y] == vertices[RIGHT][Y])
			{
				std::ofstream console("console.txt", std::ios::app);
				console << "MARKER\n";

				float leftSlope = calculateSlope(vertices[TOP], vertices[LEFT]);
				float rightSlope = calculateSlope(vertices[TOP], vertices[RIGHT]);

				float xLeft = vertices[TOP][X];
				float xRight = vertices[TOP][X];

				//loop through main loop
				for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[RIGHT][Y]; ++j)
				{
					//increment xleft and xRight
					xLeft += leftSlope;
					xRight += rightSlope;
					
					//iterate pixels from xLeft to xRight
					for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
					{						
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);
						
						//put onto display
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}
			}
		}

	}

	return GZ_SUCCESS;
}

/* NOT part of API - just for general assistance */

short	ctoi(float color)		/* convert float color to GzIntensity short */
{
  return(short)((int)(color * ((1 << 12) - 1)));
}


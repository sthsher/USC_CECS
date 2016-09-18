/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"


#define TOP 0
#define LEFT 1
#define RIGHT 2

#define TOP2 1
#define SIDE 1
#define BOT 2

/* NOT part of API - just for general assistance */

short	ctoi(float color)		/* convert float color to GzIntensity short */
{
	return(short)((int)(color * ((1 << 12) - 1)));
}

int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value

	return GZ_SUCCESS;
}


int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value

	return GZ_SUCCESS;
}


int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value

	return GZ_SUCCESS;
}


int GzTrxMat(GzCoord translate, GzMatrix mat)
{
// Create translation matrix
// Pass back the matrix using mat value

	return GZ_SUCCESS;
}


int GzScaleMat(GzCoord scale, GzMatrix mat)
{
// Create scaling matrix
// Pass back the matrix using mat value

	return GZ_SUCCESS;
}


//----------------------------------------------------------
// Begin main functions

int GzNewRender(GzRender **render, GzDisplay	*display)
{
/*  
- malloc a renderer struct 
- setup Xsp and anything only done once 
- save the pointer to display 
- init default camera 
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


int GzBeginRender(GzRender *render)
{
/*  
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 
	return GZ_SUCCESS;
}

int GzPutCamera(GzRender *render, GzCamera *camera)
{
/*
- overwrite renderer camera structure with new camera definition
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

int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	return GZ_SUCCESS;
}

int GzPopMatrix(GzRender *render)
{
/*
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	return GZ_SUCCESS;
}


int GzPutAttribute(GzRender	*render, int numAttributes, GzToken	*nameList, 
	GzPointer	*valueList) /* void** valuelist */
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
			render->flatcolor[RED] = (*static_cast<GzColor*>(*valueList))[RED];
			render->flatcolor[GREEN] = (*static_cast<GzColor*>(*valueList))[GREEN];
			render->flatcolor[BLUE] = (*static_cast<GzColor*>(*valueList))[BLUE];
		}

		//iterate GzToken
		nameList += 1;
		//iterate GzPointer
		valueList += sizeof(GzToken);
	}

	return GZ_SUCCESS;
}

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

float interpolateX(const float slope, const float intercept, const int y)
{
	//x = my + b
	return ((slope * y) + intercept);
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

int GzPutTriangle(GzRender	*render, int numParts, GzToken *nameList, GzPointer	*valueList)
/* numParts : how many names and values */
{
/*  
- pass in a triangle description with tokens and values corresponding to 
      GZ_POSITION:3 vert positions in model space 
- Xform positions of verts using matrix on top of stack 
- Clip - just discard any triangle with any vert(s) behind view plane 
       - optional: test for triangles with all three verts off-screen (trivial frustum cull)
- invoke triangle rasterizer  
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
			if (vertexA[Y] < vertexB[Y] && vertexA[Y] < vertexC[Y])
			{
				equateGzCoord(vertices[TOP], vertexA);
			}
			//Case B
			else if (vertexB[Y] < vertexA[Y] && vertexB[Y] < vertexC[Y])
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

			//Doesn't seem to happen
			if (vertices[TOP][Y] == vertices[LEFT][Y] || vertices[TOP][Y] == vertices[RIGHT][Y] || vertices[LEFT][Y] == vertices[RIGHT][Y])
			{
				//console << "Special case\n";
			}

			//Special Cases:
			//top two vertices are same height
			//		TOP1			TOP2
			//
			//
			//
			//				BOT
			if (vertices[TOP][Y] == vertices[LEFT][Y] || vertices[TOP][Y] == vertices[RIGHT][Y])
			{
				vertices[TOP][Y] == vertices[LEFT][Y] ? equateGzCoord(vertices[TOP2], vertices[LEFT]) : equateGzCoord(vertices[TOP2], vertices[RIGHT]);
				vertices[TOP][Y] == vertices[LEFT][Y] ? equateGzCoord(vertices[BOT], vertices[RIGHT]) : equateGzCoord(vertices[BOT], vertices[LEFT]);

				//calculate slopes
				float mainSlope = calculateSlope(vertices[TOP], vertices[BOT]);
				float slopeA = calculateSlope(vertices[TOP2], vertices[BOT]);

				//intercepts
				float interceptM = vertices[BOT][X] - (mainSlope * vertices[BOT][Y]);
				float interceptA = vertices[BOT][X] - (slopeA * vertices[BOT][Y]);

				float xLeft = 0;
				float xRight = 0;

				//scan
				for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[BOT][Y]; ++j)
				{
					//calculate x interpolations
					xLeft = interpolateX(mainSlope, interceptM, j);
					xRight = interpolateX(slopeA, interceptA, j);

					//scan
					for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}

					//scan
					for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}
			}

			//vertical lines
			//		TOP											TOP
			//			
			//					SIDE				SIDE
			//
			//		BOT											BOT

			else if (vertices[TOP][X] == vertices[LEFT][X] || vertices[TOP][X] == vertices[RIGHT][X])
			{
				//Add as needed
			}

			//Case 1:
			//Left is lower than right
			/*
			TOP

			RIGHT


			LEFT
			*/
			else if (vertices[LEFT][Y] > vertices[RIGHT][Y])
			{
				//calculate slopes
				float mainSlope = calculateSlope(vertices[TOP], vertices[LEFT]);
				float slopeA = calculateSlope(vertices[TOP], vertices[RIGHT]);
				float slopeB = calculateSlope(vertices[RIGHT], vertices[LEFT]);

				//intercept = x - slope(y)
				float interceptM = vertices[TOP][X] - (mainSlope * vertices[TOP][Y]);
				float interceptA = vertices[TOP][X] - (slopeA * vertices[TOP][Y]);
				float interceptB = vertices[RIGHT][X] - (slopeB * vertices[RIGHT][Y]);

				float xLeft = 0;
				float xRight = 0;

				//scan set 1
				for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[RIGHT][Y]; ++j)
				{
					//for every j increment, calculate the x interpolations
					xLeft = interpolateX(mainSlope, interceptM, j);
					xRight = interpolateX(slopeA, interceptA, j);

					//iterate through scan line
					for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}

					for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}

				//scan set 2
				for (int j = static_cast<int>(ceil(vertices[RIGHT][Y])); j < vertices[LEFT][Y]; ++j)
				{
					//for every j increment, calculate the x interpolations
					xLeft = interpolateX(mainSlope, interceptM, j);
					xRight = interpolateX(slopeB, interceptB, j);

					//iterate through scan line
					for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}

					//Scan left
					for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
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
				//calculate slopes
				float mainSlope = calculateSlope(vertices[TOP], vertices[RIGHT]);
				float slopeA = calculateSlope(vertices[TOP], vertices[LEFT]);
				float slopeB = calculateSlope(vertices[LEFT], vertices[RIGHT]);

				//intercept = x - slope(y)
				float interceptM = vertices[TOP][X] - (mainSlope * vertices[TOP][Y]);
				float interceptA = vertices[TOP][X] - (slopeA * vertices[TOP][Y]);
				float interceptB = vertices[LEFT][X] - (slopeB * vertices[LEFT][Y]);

				float xLeft = 0;
				float xRight = 0;

				//scan set 1
				for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[LEFT][Y]; ++j)
				{
					//for every j increment, calculate the x interpolations
					xLeft = interpolateX(slopeA, interceptA, j);
					xRight = interpolateX(mainSlope, interceptM, j);

					//iterate through scan line
					for (int i = static_cast<int>(ceil(xLeft)); i <= xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}

					//Scan left
					for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}

				//scan set 2
				for (int j = static_cast<int>(ceil(vertices[LEFT][Y])); j < vertices[RIGHT][Y]; ++j)
				{
					//for every j increment, calculate the x interpolations
					xLeft = interpolateX(slopeB, interceptB, j);
					xRight = interpolateX(mainSlope, interceptM, j);

					//iterate through scan line
					for (int i = static_cast<int>(ceil(xLeft)); i <= xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
					//Scan left
					for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}
			}

			//Case 3:
			//Left is same height as right
			/*
			TOP


			LEFT			RIGHT
			*/
			else
			{
				//calculate slopes
				float mainSlope = calculateSlope(vertices[TOP], vertices[LEFT]);
				float slopeA = calculateSlope(vertices[TOP], vertices[RIGHT]);

				//intercept = x - slope(y)
				float interceptM = vertices[TOP][X] - (mainSlope * vertices[TOP][Y]);
				float interceptA = vertices[TOP][X] - (slopeA * vertices[TOP][Y]);

				float xLeft = 0;
				float xRight = 0;

				//scan set 1
				for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[LEFT][Y]; ++j)
				{
					//for every j increment, calculate the x interpolations
					xLeft = interpolateX(mainSlope, interceptM, j);
					xRight = interpolateX(slopeA, interceptA, j);

					//iterate through scan line
					for (int i = static_cast<int>(ceil(xLeft)); i <= xRight; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}

					//Scan left
					for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
					{
						//interpolate Z
						int Z_ = interpolateZ(vertices, i, j);

						//draw
						GzPutDisplay(render->display, i, j, ctoi(render->flatcolor[RED]), ctoi(render->flatcolor[GREEN]), ctoi(render->flatcolor[BLUE]), 1, Z_);
					}
				}
			}
		}
	}

	return GZ_SUCCESS;
}



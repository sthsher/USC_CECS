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

#define PI 3.14159265358979

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


void initializeXsp(GzMatrix* Xsp, const unsigned short xs, const unsigned short ys)
{
	(*Xsp)[0][0] = static_cast<float>(xs / 2);
	(*Xsp)[1][1] = static_cast<float>(-1 * (ys / 2));
	(*Xsp)[3][0] = static_cast<float>(xs / 2);
	(*Xsp)[3][1] = static_cast<float>(ys / 2);
	(*Xsp)[2][2] = static_cast<float>(MAXINT);
	(*Xsp)[3][3] = 1;

	return;
}

//----------------------------------------------------------
// Begin main functions

int GzNewRender(GzRender **render, GzDisplay *display)
{
/*  
- malloc a renderer struct 
- setup Xsp and anything only done once 
- save the pointer to display 
- init default camera 
*/ 

	*render = new GzRender;
	(*render)->display = display;

	//setup render->Xsp
	unsigned short xs = display->xres;
	unsigned short ys = display->yres;
	initializeXsp(&((*render)->Xsp), display->xres, display->yres);

	//push this matrix onto the stack
	GzPushMatrix(*render, (*render)->Xsp);

	//initialize default camera
	(*render)->camera.FOV = DEFAULT_FOV;
	(*render)->camera.lookat[X] = 0;
	(*render)->camera.lookat[Y] = 0;
	(*render)->camera.lookat[Z] = 0;
	(*render)->camera.position[X] = DEFAULT_IM_X;
	(*render)->camera.position[Y] = DEFAULT_IM_Y;
	(*render)->camera.position[Z] = DEFAULT_IM_Z;
	(*render)->camera.worldup[X] = 0;
	(*render)->camera.worldup[Y] = 1;
	(*render)->camera.worldup[Z] = 0;

	//initialize stack counter
	(*render)->matlevel = 0;

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
	if (GzInitDisplay(render->display) == GZ_SUCCESS)
	{
		return GZ_SUCCESS;
	}
	else
	{
		return GZ_FAILURE;
	}
}

float calculateDistance(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2)
{
	double pow1 = pow(x2 - x1, 2);
	double pow2 = pow(y2 - y1, 2);
	double pow3 = pow(z2 - z1, 2);
	return static_cast<float>(sqrt(pow1 + pow2 + pow3));
}

float calculateDotProduct(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2)
{
	return (x1 * x2) + (y1 * y2) + (z1 * z2);
}

int GzPutCamera(GzRender *render, GzCamera *camera)
{
	/*
	- overwrite renderer camera structure with new camera definition
	*/

	//Has position, lookat, worldup, and FOV
	//calculate Xiw and Xip
	(camera->Xpi)[0][0] = 1;
	(camera->Xpi)[1][1] = 1;
	(camera->Xpi)[3][3] = 1;

	//calculate 1/d = tan(FOV/2)
	float dInverse = static_cast<float>(tan(camera->FOV * PI / (180 * 2)));
	(camera->Xpi)[2][2] = dInverse;
	(camera->Xpi)[2][3] = dInverse;


	float z_axis[3], y_axis[3], x_axis[3];

	//Zaxis = lookat point - origin / length
	float cI_length = calculateDistance(camera->lookat[X], camera->lookat[Y], camera->lookat[Z], DEFAULT_IM_X, DEFAULT_IM_Y, DEFAULT_IM_Z);
	z_axis[X] = static_cast<float>((camera->lookat[X] - DEFAULT_IM_X) / cI_length);
	z_axis[Y] = static_cast<float>((camera->lookat[Y] - DEFAULT_IM_Y) / cI_length);
	z_axis[Z] = static_cast<float>((camera->lookat[Z] - DEFAULT_IM_Z) / cI_length);

	//Yaxis
	float up_[3];
	float dot_product = calculateDotProduct(camera->worldup[X], camera->worldup[Y], camera->worldup[Z], z_axis[X], z_axis[Y], z_axis[Z]);
	/*
								[ up.x ] -		[ Z.x ]
		up_ = up - (up.Z)Z =	[ up.y ] - up.Z [ Z.y ]
								[ up.z ] -		[ Z.z ]
	*/

	up_[X] = camera->worldup[X] - (dot_product * z_axis[X]);
	up_[Y] = camera->worldup[Y] - (dot_product * z_axis[Y]);
	up_[Z] = camera->worldup[Z] - (dot_product * z_axis[Z]);
	float up_length = calculateDistance(up_[X], up_[Y], up_[Z], DEFAULT_IM_X, DEFAULT_IM_Y, DEFAULT_IM_Z);

	y_axis[X] = up_[X] / up_length;
	y_axis[Y] = up_[Y] / up_length;
	y_axis[Z] = up_[Z] / up_length;

	//Xaxis = Y x Z
	x_axis[X] = (y_axis[Y] * z_axis[Z]) - (y_axis[Z] * z_axis[Y]);
	x_axis[Y] = (y_axis[Z] * z_axis[X]) - (y_axis[X] * z_axis[Z]);
	x_axis[Z] = (y_axis[X] * z_axis[Y]) - (y_axis[Y] * z_axis[X]);

	//build Xwi
	float XC = calculateDotProduct(x_axis[X], x_axis[Y], x_axis[Z], DEFAULT_IM_X, DEFAULT_IM_Y, DEFAULT_IM_Z);
	float YC = calculateDotProduct(y_axis[X], y_axis[Y], y_axis[Z], DEFAULT_IM_X, DEFAULT_IM_Y, DEFAULT_IM_Z);
	float ZC = calculateDotProduct(z_axis[X], z_axis[Y], z_axis[Z], DEFAULT_IM_X, DEFAULT_IM_Y, DEFAULT_IM_Z);

	camera->Xiw[0][0] = x_axis[X];
	camera->Xiw[0][1] = x_axis[Y];
	camera->Xiw[0][2] = x_axis[Z];
	camera->Xiw[0][3] = (-1) * XC;
	camera->Xiw[1][0] = y_axis[X];
	camera->Xiw[1][1] = y_axis[Y];
	camera->Xiw[1][2] = y_axis[Z];
	camera->Xiw[1][3] = (-1) * YC;
	camera->Xiw[2][0] = z_axis[X];
	camera->Xiw[2][1] = z_axis[Y];
	camera->Xiw[2][2] = z_axis[Z];
	camera->Xiw[2][3] = (-1) * ZC;
	camera->Xiw[3][0] = 0;
	camera->Xiw[3][1] = 0;
	camera->Xiw[3][2] = 0;
	camera->Xiw[3][3] = 1;

	render->camera = *camera;

	//push onto stack
	GzPushMatrix(render, camera->Xpi);
	GzPushMatrix(render, camera->Xiw);

	return GZ_SUCCESS;

}

int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	if (render->matlevel == MATLEVELS - 1)
	{
		return GZ_FAILURE;
	}

	//for (int i = 0; i < 4; ++i)
	//{
	//	for (int j = 0; j < 4; ++j)
	//	{
	//		(render->Ximage[render->matlevel])[i][j] = matrix[i][j];
	//	}
	//}

	if (render->matlevel == 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				(render->Ximage[render->matlevel])[i][j] = matrix[i][j];
			}
		}	
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				float value = 0;
				for (int x = 0; x < 4; ++x)
				{
					value += (render->Ximage[render->matlevel][x][j] * matrix[i][x]);
				}
				render->Ximage[render->matlevel + 1][i][j] = value;
			}
		}
		++render->matlevel;
	}

	return GZ_SUCCESS;
}

int GzPopMatrix(GzRender *render)
{
/*
- pop a matrix off the Ximage stack
- check for stack underflow
*/

	if (render->matlevel == 0)
	{
		return GZ_FAILURE;
	}

	--render->matlevel;

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

void transformGzCoord(GzCoord& vertex, const GzRender* render)
{
	float X_, Y_, Z_, W_;
	X_ = vertex[0];
	Y_ = vertex[1];
	Z_ = vertex[2];
	W_ = 1;

	float xform[4];
	float x1 = render->Ximage[render->matlevel][0][0];
	float x2 = render->Ximage[render->matlevel][1][0];
	float x3 = render->Ximage[render->matlevel][2][0];
	float x4 = render->Ximage[render->matlevel][3][0];
	float y1 = render->Ximage[render->matlevel][0][1];
	float y2 = render->Ximage[render->matlevel][1][1];
	float y3 = render->Ximage[render->matlevel][2][1];
	float y4 = render->Ximage[render->matlevel][3][1];
	float z1 = render->Ximage[render->matlevel][0][2];
	float z2 = render->Ximage[render->matlevel][1][2];
	float z3 = render->Ximage[render->matlevel][2][2];
	float z4 = render->Ximage[render->matlevel][3][2];
	float w1 = render->Ximage[render->matlevel][0][3];
	float w2 = render->Ximage[render->matlevel][1][3];
	float w3 = render->Ximage[render->matlevel][2][3];
	float w4 = render->Ximage[render->matlevel][3][3];

	xform[0] = (x1 * X_) + (x2 * Y_) + (x3 * Z_) + (x4 * W_);
	xform[1] = (y1 * X_) + (y2 * Y_) + (y3 * Z_) + (y4 * W_);
	xform[2] = (z1 * X_) + (z2 * Y_) + (z3 * Z_) + (z4 * W_);
	xform[3] = (w1 * X_) + (w2 * Y_) + (w3 * Z_) + (w4 * W_);

	vertex[0] = xform[0];
	vertex[1] = xform[1];
	vertex[2] = xform[2];
	vertex[3] = xform[3];
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

			transformGzCoord(vertexA, render);
			transformGzCoord(vertexB, render);
			transformGzCoord(vertexC, render);

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



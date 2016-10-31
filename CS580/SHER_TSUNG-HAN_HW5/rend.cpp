/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"
#include <string>

#define TOP 0
#define LEFT 1
#define RIGHT 2

#define TOP2 1
#define SIDE 1
#define BOT 2

#define DEBUG false

static const GzMatrix IDENTITY =
{
	1.0,	0.0,	0.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0,
	0.0,	0.0,	0.0,	1.0
};

short normlevel;

#define PI 3.14159265358979
#define	RADIANS(d)	((d * PI)/180)	

/* NOT part of API - just for general assistance */

void CalculateCamera(GzRender* render);

#include <fstream>

void printString(std::string string)
{
	std::ofstream console("console.txt", std::ios::app);

	console << string << std::endl;
}

void printUV(const GzTextureIndex ti)
{
	std::ofstream console("console.txt", std::ios::app);

	console << "UV: [" << ti[U] << "," << ti[V] << "]" << std::endl;
}

void printCoord(GzCoord c)
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

void printColor(GzColor c)
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

void printMatrix(const GzMatrix matrix)
{
	std::ofstream console("console.txt", std::ios::app);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			console << matrix[j][i] << " ";
		}
		console << std::endl;
	}
	console << std::endl;

	console.close();
}

void transposeMatrix(const GzMatrix matrix, GzMatrix& transposed)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transposed[i][j] = matrix[j][i];
		}
	}
}

void equateMatrix(GzMatrix LHS, const GzMatrix RHS)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			LHS[i][j] = RHS[i][j];
		}
	}
}

short	ctoi(float color)		/* convert float color to GzIntensity short */
{
	return(short)((int)(color * ((1 << 12) - 1)));
}

int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value

	float sin = static_cast<float>(std::sin(RADIANS(degree)));
	float cos = static_cast<float>(std::cos(RADIANS(degree)));

	mat[1][1] = cos;
	mat[2][1] = (-1) * sin;
	mat[1][2] = sin;
	mat[2][2] = cos;

	GzMatrix transposed;
	transposeMatrix(mat, transposed);
	equateMatrix(mat, transposed);

	return GZ_SUCCESS;
}


int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value

	float sin = static_cast<float>(std::sin(RADIANS(degree)));
	float cos = static_cast<float>(std::cos(RADIANS(degree)));

	mat[0][0] = cos;
	mat[2][0] = sin;
	mat[0][2] = (-1) * sin;
	mat[2][2] = cos;

	GzMatrix transposed;
	transposeMatrix(mat, transposed);
	equateMatrix(mat, transposed);

	return GZ_SUCCESS;
}

int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value

	float sin = static_cast<float>(std::sin(RADIANS(degree)));
	float cos = static_cast<float>(std::cos(RADIANS(degree)));

	mat[0][0] = cos;
	mat[0][1] = sin;
	mat[1][0] = (-1) * sin;
	mat[1][1] = cos;

	GzMatrix transposed;
	transposeMatrix(mat, transposed);
	equateMatrix(mat, transposed);

	return GZ_SUCCESS;
}


int GzTrxMat(GzCoord translate, GzMatrix mat)
{
// Create translation matrix
// Pass back the matrix using mat value

	mat[3][0] = translate[X];
	mat[3][1] = translate[Y];
	mat[3][2] = translate[Z];

	GzMatrix transposed;
	transposeMatrix(mat, transposed);
	equateMatrix(mat, transposed);

	return GZ_SUCCESS;
}


int GzScaleMat(GzCoord scale, GzMatrix mat)
{
// Create scaling matrix
// Pass back the matrix using mat value

	mat[0][0] = scale[X];
	mat[1][1] = scale[Y];
	mat[2][2] = scale[Z];

	GzMatrix transposed;
	transposeMatrix(mat, transposed);
	equateMatrix(mat, transposed);

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


void clearMatrix(GzMatrix& matrix)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matrix[i][j] = 0;
		}
	}
}

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

	//initialize stack counter
	(*render)->matlevel = 0;
	normlevel = 0;

	//push this matrix onto the stack
	GzMatrix transpose;
	transposeMatrix((*render)->Xsp, transpose);
	GzPushMatrix(*render, transpose);

	//push Norm
	//GzPushMatrixXnorm(*render, IDENTITY_T);

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

	clearMatrix((*render)->camera.Xpi);
	clearMatrix((*render)->camera.Xiw);

	//lights
	(*render)->numlights = 0;

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
		CalculateCamera(render);
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
//
//float calculateDotProduct(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2)
//{
//	return (x1 * x2) + (y1 * y2) + (z1 * z2);
//}

float calculateDotProduct(const GzCoord a, const GzCoord b)
{
	return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

void calculateCross(const float* m1, const float *m2, float* result)
{
	result[X] = (m1[Y] * m2[Z]) - (m1[Z] * m2[Y]);
	result[Y] = (m1[Z] * m2[X]) - (m1[X] * m2[Z]);
	result[Z] = (m1[X] * m2[Y]) - (m1[Y] * m2[X]);
}

void CalculateCamera(GzRender* render)
{
	GzCamera* camera = &(render->camera);

	//Has position, lookat, worldup, and FOV
	//calculate Xiw and Xip

	clearMatrix(camera->Xpi);
	clearMatrix(camera->Xiw);

	//initialize with 0's
	(camera->Xpi)[0][0] = 1;
	(camera->Xpi)[1][1] = 1;
	(camera->Xpi)[3][3] = 1;

	//calculate 1/d = tan(FOV/2)
	float dInverse = static_cast<float>(tan(camera->FOV * PI / (180 * 2)));
	(camera->Xpi)[2][2] = dInverse;
	(camera->Xpi)[2][3] = dInverse;


	float z_axis[3], y_axis[3], x_axis[3];

	//Zaxis = lookat point - origin / length
	float cI_length = calculateDistance(camera->lookat[X], camera->lookat[Y], camera->lookat[Z], camera->position[X], camera->position[Y], camera->position[Z]);
	z_axis[X] = static_cast<float>((camera->lookat[X] - camera->position[X]) / cI_length);
	z_axis[Y] = static_cast<float>((camera->lookat[Y] - camera->position[Y]) / cI_length);
	z_axis[Z] = static_cast<float>((camera->lookat[Z] - camera->position[Z]) / cI_length);

	float z_length = calculateDistance(z_axis[X], z_axis[Y], z_axis[Z], 0, 0, 0);

	//Yaxis
	float up_[3];
	//float dot_product = calculateDotProduct(camera->worldup[X], camera->worldup[Y], camera->worldup[Z], z_axis[X], z_axis[Y], z_axis[Z]);
	float dot_product = calculateDotProduct(camera->worldup, z_axis);

	//							[ up.x ] -		[ Z.x ]
	//	up_ = up - (up.Z)Z =	[ up.y ] - up.Z [ Z.y ]
	//							[ up.z ] -		[ Z.z ]
	

	up_[X] = camera->worldup[X] - (dot_product * z_axis[X]);
	up_[Y] = camera->worldup[Y] - (dot_product * z_axis[Y]);
	up_[Z] = camera->worldup[Z] - (dot_product * z_axis[Z]);

	float up_length = calculateDistance(up_[X], up_[Y], up_[Z], 0,0,0);

	y_axis[X] = up_[X] / up_length;
	y_axis[Y] = up_[Y] / up_length;
	y_axis[Z] = up_[Z] / up_length;

	float y_length = calculateDistance(y_axis[X], y_axis[Y], y_axis[Z], 0, 0, 0);


	//Xaxis = Y x Z
	calculateCross(y_axis, z_axis, x_axis);
	float x_length = calculateDistance(x_axis[X], x_axis[Y], x_axis[Z], 0,0,0);

	x_axis[X] = x_axis[X] / x_length;
	x_axis[Y] = x_axis[Y] / x_length;
	x_axis[Z] = x_axis[Z] / x_length;

	x_length = calculateDistance(x_axis[X], x_axis[Y], x_axis[Z], 0, 0, 0);

	//build Xwi
	float XC = calculateDotProduct(x_axis, camera->position);
	float YC = calculateDotProduct(y_axis, camera->position);
	float ZC = calculateDotProduct(z_axis, camera->position);

	camera->Xiw[0][0] = x_axis[X];
	camera->Xiw[1][0] = x_axis[Y];
	camera->Xiw[2][0] = x_axis[Z];
	camera->Xiw[3][0] = (-1) * XC;
	camera->Xiw[0][1] = y_axis[X];
	camera->Xiw[1][1] = y_axis[Y];
	camera->Xiw[2][1] = y_axis[Z];
	camera->Xiw[3][1] = (-1) * YC;
	camera->Xiw[0][2] = z_axis[X];
	camera->Xiw[1][2] = z_axis[Y];
	camera->Xiw[2][2] = z_axis[Z];
	camera->Xiw[3][2] = (-1) * ZC;
	camera->Xiw[0][3] = 0;
	camera->Xiw[1][3] = 0;
	camera->Xiw[2][3] = 0;
	camera->Xiw[3][3] = 1;

	//push onto stack
	GzMatrix XpiTranspose, XiwTranspose;
	transposeMatrix(render->camera.Xpi, XpiTranspose);
	transposeMatrix(render->camera.Xiw, XiwTranspose);

	GzPushMatrix(render, XpiTranspose);
	GzPushMatrix(render, XiwTranspose);
}

int GzPutCamera(GzRender *render, GzCamera *camera)
{
	/*
	- overwrite renderer camera structure with new camera definition
	*/

	render->camera.FOV = camera->FOV;
	render->camera.lookat[X] = camera->lookat[X];
	render->camera.lookat[Y] = camera->lookat[Y];
	render->camera.lookat[Z] = camera->lookat[Z];
	render->camera.position[X] = camera->position[X];
	render->camera.position[Y] = camera->position[Y];
	render->camera.position[Z] = camera->position[Z];
	render->camera.worldup[X] = camera->worldup[X];
	render->camera.worldup[Y] = camera->worldup[Y];
	render->camera.worldup[Z] = camera->worldup[Z];

	return GZ_SUCCESS;

}

//matrix has to be transposed
int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	//transpose the matrix first
	GzMatrix transposed;
	transposeMatrix(matrix, transposed);
	
	GzMatrix normMat;
	equateMatrix(normMat, transposed);

	if (normMat[2][2] == MAXINT || normMat[2][3] != 0)
	{
		equateMatrix(normMat, IDENTITY);
	}
	else
	{
		//rid transpose and turn unitary
		//clear transpose
		normMat[3][0] = 0;
		normMat[3][1] = 0;
		normMat[3][2] = 0;

		//unitary
		float K = sqrt(pow(normMat[0][0], 2) + pow(normMat[1][0], 2) + pow(normMat[2][0], 2));
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				normMat[i][j] = normMat[i][j] / K;
			}
		}
	}

	if (render->matlevel == MATLEVELS - 1)
	{
		return GZ_FAILURE;
	}

	if (render->matlevel == 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				(render->Ximage[render->matlevel])[i][j] = transposed[i][j];
				(render->Xnorm[render->matlevel])[i][j] = normMat[i][j];
			}
		}
		++render->matlevel;
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				float valueImage = 0;
				float valueNormal = 0;
				for (int x = 0; x < 4; ++x)
				{
					valueImage += (render->Ximage[render->matlevel - 1][x][j] * transposed[i][x]);
					valueNormal += (render->Xnorm[render->matlevel - 1][x][j] * normMat[i][x]);
				}
				render->Ximage[render->matlevel][i][j] = valueImage;
				render->Xnorm[render->matlevel][i][j] = valueNormal;
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
		switch (nameList[i])
		{
			case GZ_RGB_COLOR:
			{
				render->flatcolor[RED] = (*static_cast<GzColor*>(valueList[i]))[RED];
				render->flatcolor[GREEN] = (*static_cast<GzColor*>(valueList[i]))[GREEN];
				render->flatcolor[BLUE] = (*static_cast<GzColor*>(valueList[i]))[BLUE];
				break;
			}
			case GZ_DIRECTIONAL_LIGHT:
			{
				GzLight newLight = *(static_cast<GzLight*>(valueList[i]));

				//add to renderer
				render->lights[render->numlights++] = newLight;
				break;
			}
			case GZ_AMBIENT_LIGHT:
			{
				render->ambientlight = *(static_cast<GzLight*>(valueList[i]));				
				break;
			}
			case GZ_DIFFUSE_COEFFICIENT:
			{
				render->Kd[RED] = (*static_cast<GzColor*>(valueList[i]))[RED];
				render->Kd[GREEN] = (*static_cast<GzColor*>(valueList[i]))[GREEN];
				render->Kd[BLUE] = (*static_cast<GzColor*>(valueList[i]))[BLUE];
				break;
			}
			case GZ_AMBIENT_COEFFICIENT:
			{
				render->Ka[RED] = (*static_cast<GzColor*>(valueList[i]))[RED];
				render->Ka[GREEN] = (*static_cast<GzColor*>(valueList[i]))[GREEN];
				render->Ka[BLUE] = (*static_cast<GzColor*>(valueList[i]))[BLUE];
				break;
			}
			case GZ_SPECULAR_COEFFICIENT:
			{
				render->Ks[RED] = (*static_cast<GzColor*>(valueList[i]))[RED];
				render->Ks[GREEN] = (*static_cast<GzColor*>(valueList[i]))[GREEN];
				render->Ks[BLUE] = (*static_cast<GzColor*>(valueList[i]))[BLUE];
				break;
			}
			case GZ_DISTRIBUTION_COEFFICIENT:
			{
				render->spec = (*static_cast<float*>(valueList[i]));
				break;
			}

			case GZ_INTERPOLATE:
			{
				render->interp_mode = (*static_cast<int*>(valueList[i]));
				break;
			}
			case GZ_TEXTURE_MAP:
			{
				render->tex_fun = static_cast<GzTexture>(valueList[i]);
			}
		}
	}

	return GZ_SUCCESS;
}

void equateGzTextureIndex(GzTextureIndex& lhs, const GzTextureIndex rhs)
{
	lhs[U] = rhs[U];
	lhs[V] = rhs[V];
}

void equateGzCoord(GzCoord& lhs, const GzCoord rhs)
{
	lhs[X] = rhs[X];
	lhs[Y] = rhs[Y];
	lhs[Z] = rhs[Z];
}

void equateGzColor(GzColor& lhs, const GzCoord rhs)
{
	lhs[RED] = rhs[RED];
	lhs[GREEN] = rhs[GREEN];
	lhs[BLUE] = rhs[BLUE];
}

void unitizeGzCoord(GzCoord& c)
{
	float K = std::sqrt(std::pow(c[0], 2) + std::pow(c[1], 2) + std::pow(c[2], 2));
	for (int i = 0; i < 3; ++i)
	{
		c[i] = c[i] / K;
	}

}

bool equalityGzCoord(const GzCoord a, const GzCoord b)
{
	return ((a[X] == b[X]) && (a[Y] == b[Y]) && (a[Z] == b[Z]));
}

//SLOPES
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

void calculateTextureSlope(const GzCoord point1, const GzCoord point2, const GzTextureIndex texture1, const GzTextureIndex texture2, float* slopes)
{
	float U1 = texture1[U];
	float U2 = texture2[U];
	float V1 = texture1[V];
	float V2 = texture2[V];

	float yDelta = point2[Y] - point1[Y];
	float uDelta = U2 - U1;
	float vDelta = V2 - V1;

	slopes[U] = uDelta / yDelta;
	slopes[V] = vDelta / yDelta;
}

void calculateRGBSlope(const GzCoord point1, const GzCoord point2, const GzColor color1, const GzColor color2, float* slopes)
{
	float r1 = color1[RED];
	float r2 = color2[RED];
	float g1 = color1[GREEN];
	float g2 = color2[GREEN];
	float b1 = color1[BLUE];
	float b2 = color2[BLUE];

	float yDelta = point2[Y] - point1[Y];
	float rDelta = r2 - r1;
	float gDelta = g2 - g1;
	float bDelta = b2 - b1;

	slopes[RED] = rDelta / yDelta;
	slopes[GREEN] = gDelta / yDelta;
	slopes[BLUE] = bDelta / yDelta;
}

void calculateNormalSlope(const GzCoord point1, const GzCoord point2, const GzCoord normal1, const GzCoord normal2, float* slopes)
{
	float x1 = normal1[X];
	float x2 = normal2[X];
	float y1 = normal1[Y];
	float y2 = normal2[Y];
	float z1 = normal1[Z];
	float z2 = normal2[Z];

	float DELTA = point2[Y] - point1[Y];
	float xDelta = x2 - x1;
	float yDelta = y2 - y1;
	float zDelta = z2 - z1;

	slopes[X] = xDelta / DELTA;
	slopes[Y] = yDelta / DELTA;
	slopes[Z] = zDelta / DELTA;
}

//SLOPES
void calculateRGBSlopePoint(const float* RGBxLeft, const float* RGBxRight, const float deltaX, float* slopes)
{
	slopes[RED] = (RGBxRight[RED] - RGBxLeft[RED]) / deltaX;
	slopes[GREEN] = (RGBxRight[GREEN] - RGBxLeft[GREEN]) / deltaX;
	slopes[BLUE] = (RGBxRight[BLUE] - RGBxLeft[BLUE]) / deltaX;
}

void calculateNormalSlopePoint(const float* normalxLeft, const float* normalxRight, const float deltaX, float* slopes)
{
	slopes[X] = (normalxRight[X] - normalxLeft[X]) / deltaX;
	slopes[Y] = (normalxRight[Y] - normalxLeft[Y]) / deltaX;
	slopes[Z] = (normalxRight[Z] - normalxLeft[Z]) / deltaX;
}

void calculateTextureSlopePoint(const float* texturexLeft, const float* texturexRight, const float deltaX, float* slopes)
{
	slopes[U] = (texturexRight[U] - texturexLeft[U]) / deltaX;
	slopes[V] = (texturexRight[V] - texturexLeft[V]) / deltaX;
}

//INTERCEPTS
void calculateTextureIntercepts(const float* slopes, const GzTextureIndex t, const float y, float* intercepts)
{
	//intercept = c - slope * y
	intercepts[U] = t[U] - (slopes[U] * y);
	intercepts[V] = t[V] - (slopes[V] * y);
}

void calculateRGBIntercepts(const float* slopes, const GzColor c, const float y, float* intercepts)
{
	//intercept = c - slope * y
	intercepts[RED] = c[RED] - (slopes[RED] * y);
	intercepts[GREEN] = c[GREEN] - (slopes[GREEN] * y);
	intercepts[BLUE] = c[BLUE] - (slopes[BLUE] * y);
}

void calculateNormalIntercepts(const float* slopes, const GzCoord n, const float y, float* intercepts)
{
	//intercept = c - slope * y
	intercepts[X] = n[X] - (slopes[X] * y);
	intercepts[Y] = n[Y] - (slopes[Y] * y);
	intercepts[Z] = n[Z] - (slopes[Z] * y);
}


//INTERPOLATE POINTS
float interpolateX(const float slope, const float intercept, const int y)
{
	//x = my + b
	return ((slope * y) + intercept);
}

void interpolateTexture(const float* slopes, const float* intercepts, const int y, GzTextureIndex& t)
{
	t[U] = ((slopes[U] * y) + intercepts[U]);
	t[V] = ((slopes[V] * y) + intercepts[V]);
}

void interpolateRGB(const float* slopes, const float* intercepts, const int y, GzColor& c)
{
	c[RED] = ((slopes[RED] * y) + intercepts[RED]);
	c[GREEN] = ((slopes[GREEN] * y) + intercepts[GREEN]);
	c[BLUE] = ((slopes[BLUE] * y) + intercepts[BLUE]);
}

void interpolateNormals(const float* slopes, const float* intercepts, const int y, GzCoord& normals)
{
	normals[X] = ((slopes[X] * y) + intercepts[X]);
	normals[Y] = ((slopes[Y] * y) + intercepts[Y]);
	normals[Z] = ((slopes[Z] * y) + intercepts[Z]);
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

bool transformGzCoord(GzCoord& vertex, const GzRender* render)
{
	float X_, Y_, Z_, W_;
	X_ = vertex[0];
	Y_ = vertex[1];
	Z_ = vertex[2];
	W_ = 1;

	float xform[4];
	float x1 = render->Ximage[render->matlevel - 1][0][0];
	float x2 = render->Ximage[render->matlevel - 1][1][0];
	float x3 = render->Ximage[render->matlevel - 1][2][0];
	float x4 = render->Ximage[render->matlevel - 1][3][0];
	float y1 = render->Ximage[render->matlevel - 1][0][1];
	float y2 = render->Ximage[render->matlevel - 1][1][1];
	float y3 = render->Ximage[render->matlevel - 1][2][1];
	float y4 = render->Ximage[render->matlevel - 1][3][1];
	float z1 = render->Ximage[render->matlevel - 1][0][2];
	float z2 = render->Ximage[render->matlevel - 1][1][2];
	float z3 = render->Ximage[render->matlevel - 1][2][2];
	float z4 = render->Ximage[render->matlevel - 1][3][2];
	float w1 = render->Ximage[render->matlevel - 1][0][3];
	float w2 = render->Ximage[render->matlevel - 1][1][3];
	float w3 = render->Ximage[render->matlevel - 1][2][3];
	float w4 = render->Ximage[render->matlevel - 1][3][3];

	if (xform[2] < 0) return false;

	xform[0] = (x1 * X_) + (x2 * Y_) + (x3 * Z_) + (x4 * W_);
	xform[1] = (y1 * X_) + (y2 * Y_) + (y3 * Z_) + (y4 * W_);
	xform[2] = (z1 * X_) + (z2 * Y_) + (z3 * Z_) + (z4 * W_);
	xform[3] = (w1 * X_) + (w2 * Y_) + (w3 * Z_) + (w4 * W_);

	vertex[0] = xform[0] / xform[3];
	vertex[1] = xform[1] / xform[3];
	vertex[2] = xform[2] / xform[3];

	return true;
}

bool transformGzNormal(GzCoord& vertex, const GzRender* render)
{
	float X_, Y_, Z_, W_;
	X_ = vertex[0];
	Y_ = vertex[1];
	Z_ = vertex[2];
	W_ = 1;

	float xform[4];
	float x1 = render->Xnorm[render->matlevel - 1][0][0];
	float x2 = render->Xnorm[render->matlevel - 1][1][0];
	float x3 = render->Xnorm[render->matlevel - 1][2][0];
	float x4 = render->Xnorm[render->matlevel - 1][3][0];
	float y1 = render->Xnorm[render->matlevel - 1][0][1];
	float y2 = render->Xnorm[render->matlevel - 1][1][1];
	float y3 = render->Xnorm[render->matlevel - 1][2][1];
	float y4 = render->Xnorm[render->matlevel - 1][3][1];
	float z1 = render->Xnorm[render->matlevel - 1][0][2];
	float z2 = render->Xnorm[render->matlevel - 1][1][2];
	float z3 = render->Xnorm[render->matlevel - 1][2][2];
	float z4 = render->Xnorm[render->matlevel - 1][3][2];
	float w1 = render->Xnorm[render->matlevel - 1][0][3];
	float w2 = render->Xnorm[render->matlevel - 1][1][3];
	float w3 = render->Xnorm[render->matlevel - 1][2][3];
	float w4 = render->Xnorm[render->matlevel - 1][3][3];

	if (xform[2] < 0) return false;

	xform[0] = (x1 * X_) + (x2 * Y_) + (x3 * Z_) + (x4 * W_);
	xform[1] = (y1 * X_) + (y2 * Y_) + (y3 * Z_) + (y4 * W_);
	xform[2] = (z1 * X_) + (z2 * Y_) + (z3 * Z_) + (z4 * W_);
	xform[3] = (w1 * X_) + (w2 * Y_) + (w3 * Z_) + (w4 * W_);

	vertex[0] = xform[0] / xform[3];
	vertex[1] = xform[1] / xform[3];
	vertex[2] = xform[2] / xform[3];

	return true;
}

float clampToZero(const float num)
{
	if (num < 0)
	{
		return 0;
	}
	else
	{
		return num;
	}
}

void perspectiveSpace(float* parameter, const float z, const int n)
{
	float zPrime = z / (MAXINT - z);
	for (int i = 0; i < n; ++i)
	{
		parameter[i] = (parameter[i] / (zPrime + 1));
	}
}

void affineSpace(float* pPrime, const float z, const int n)
{
	float zPrime = z / (MAXINT - z);
	for (int i = 0; i < n; ++i)
	{
		pPrime[i] = pPrime[i] * (zPrime + 1);
	}
}

bool lightIntensityInterpolation(GzColor &returnColor, GzRender *render, GzCoord normal)
{
	//clear returncolor
	returnColor[RED] = 0;
	returnColor[GREEN] = 0;
	returnColor[BLUE] = 0;

	GzColor specularColor;
	GzColor diffuseColor;
	GzColor ambientColor;

	GzColor specSum = { 0,0,0 };
	GzColor diffSum = { 0,0,0 };

	for (int i = 0; i < render->numlights; ++i)
	{
		bool skip = false;
		//precompute N dot L and N dot E
		GzCoord N, L, E;
		equateGzCoord(N, normal);
		equateGzCoord(L, render->lights[i].direction);

		E[X] = 0;
		E[Y] = 0;
		E[Z] = -1;

		unitizeGzCoord(N);
		unitizeGzCoord(L);
		unitizeGzCoord(E);

		float NdotL = calculateDotProduct(N, L);
		float NdotE = calculateDotProduct(N, E);

		if (NdotL > 0 && NdotE > 0)
		{
			//both positive
			//do nothing
		}
		else if (NdotL < 0 && NdotE < 0)
		{
			//both negative
			//flip normal and compute
			N[X] *= -1;
			N[Y] *= -1;
			N[Z] *= -1;

			//Recompute dot products
			NdotL = calculateDotProduct(N, L);
			NdotE = calculateDotProduct(N, E);
		}
		else
		{
			//different sign, skip this
			skip = true;
		}

		if (!skip)
		{
			//Specular
			//Ks * SUM (le * (R DOT E)^ S)
			//R = 2(N DOT L)N - L
			float dot = NdotL;
			dot *= 2;
			N[0] *= dot;
			N[1] *= dot;
			N[2] *= dot;

			GzCoord R;
			R[0] = N[0] - L[0];
			R[1] = N[1] - L[1];
			R[2] = N[2] - L[2];

			unitizeGzCoord(R);

			float RdotE = calculateDotProduct(R, E);
			if (RdotE < 0) RdotE = 0;

			float pow = std::pow(RdotE, render->spec);

			specSum[RED] += render->lights[i].color[RED] * pow;
			specSum[GREEN] += render->lights[i].color[GREEN] * pow;
			specSum[BLUE] += render->lights[i].color[BLUE] * pow;

			//Diffuse
			//Kd * SUM (le (N DOT L)

			diffSum[RED] += render->lights[i].color[RED] * NdotL;
			diffSum[GREEN] += render->lights[i].color[GREEN] * NdotL;
			diffSum[BLUE] += render->lights[i].color[BLUE] * NdotL;
		}
	}

	specularColor[RED] = specSum[RED];
	specularColor[GREEN] =specSum[GREEN];
	specularColor[BLUE] = specSum[BLUE];

	diffuseColor[RED] = diffSum[RED];
	diffuseColor[GREEN] = diffSum[GREEN];
	diffuseColor[BLUE] = diffSum[BLUE];


	//Ambient
	// Ka * la
	ambientColor[RED] = render->ambientlight.color[RED];
	ambientColor[GREEN] = render->ambientlight.color[GREEN];
	ambientColor[BLUE] = render->ambientlight.color[BLUE];

	//calculate color
	returnColor[RED] += clampToZero(diffuseColor[RED]);
	returnColor[GREEN] += clampToZero(diffuseColor[GREEN]);
	returnColor[BLUE] += clampToZero(diffuseColor[BLUE]);

	returnColor[RED] += ambientColor[RED];
	returnColor[GREEN] += ambientColor[GREEN];
	returnColor[BLUE] += ambientColor[BLUE];

	returnColor[RED] += clampToZero(specularColor[RED]);
	returnColor[GREEN] += clampToZero(specularColor[GREEN]);
	returnColor[BLUE] += clampToZero(specularColor[BLUE]);

	if (returnColor[RED] > 1) returnColor[RED] = 1;
	if (returnColor[GREEN] > 1) returnColor[GREEN] = 1;
	if (returnColor[BLUE] > 1) returnColor[BLUE] = 1;

	return true;
}


bool shadingEquation(GzColor &returnColor, GzRender *render, GzCoord normal)
{
	//clear returncolor
	returnColor[RED] = 0;
	returnColor[GREEN] = 0;
	returnColor[BLUE] = 0;

	GzColor specularColor;
	GzColor diffuseColor;
	GzColor ambientColor;

	GzColor specSum = { 0,0,0 };
	GzColor diffSum = { 0,0,0 };

	for (int i = 0; i < render->numlights; ++i)
	{
		bool skip = false;
		//precompute N dot L and N dot E
		GzCoord N, L, E;
		equateGzCoord(N, normal);
		equateGzCoord(L, render->lights[i].direction);

		E[X] = 0;
		E[Y] = 0;
		E[Z] = -1;

		unitizeGzCoord(N);
		unitizeGzCoord(L);
		unitizeGzCoord(E);

		float NdotL = calculateDotProduct(N, L);
		float NdotE = calculateDotProduct(N, E);

		if (NdotL > 0 && NdotE > 0)
		{
			//both positive
			//do nothing
		}
		else if (NdotL < 0 && NdotE < 0)
		{
			//both negative
			//flip normal and compute
			N[X] *= -1;
			N[Y] *= -1;
			N[Z] *= -1;

			//Recompute dot products
			NdotL = calculateDotProduct(N, L);
			NdotE = calculateDotProduct(N, E);
		}
		else
		{
			//different sign, skip this
			skip = true;
		}

		if (!skip)
		{
			//Specular
			//Ks * SUM (le * (R DOT E)^ S)
			//R = 2(N DOT L)N - L
			float dot = NdotL;
			dot *= 2;
			N[0] *= dot;
			N[1] *= dot;
			N[2] *= dot;

			GzCoord R;
			R[0] = N[0] - L[0];
			R[1] = N[1] - L[1];
			R[2] = N[2] - L[2];

			unitizeGzCoord(R);

			float RdotE = calculateDotProduct(R, E);
			if (RdotE < 0) RdotE = 0;

			float pow = std::pow(RdotE, render->spec);

			specSum[RED] += render->lights[i].color[RED] * pow;
			specSum[GREEN] += render->lights[i].color[GREEN] * pow;
			specSum[BLUE] += render->lights[i].color[BLUE] * pow;

			//Diffuse
			//Kd * SUM (le (N DOT L)

			diffSum[RED] += render->lights[i].color[RED] * NdotL;
			diffSum[GREEN] += render->lights[i].color[GREEN] * NdotL;
			diffSum[BLUE] += render->lights[i].color[BLUE] * NdotL;
		}
	}

	specularColor[RED] = render->Ks[RED] * specSum[RED];
	specularColor[GREEN] = render->Ks[GREEN] * specSum[GREEN];
	specularColor[BLUE] = render->Ks[BLUE] * specSum[BLUE];

	diffuseColor[RED] = render->Kd[RED] * diffSum[RED];
	diffuseColor[GREEN] = render->Kd[GREEN] * diffSum[GREEN];
	diffuseColor[BLUE] = render->Kd[BLUE] * diffSum[BLUE];


	//Ambient
	// Ka * la
	ambientColor[RED] = render->Ka[RED] * render->ambientlight.color[RED];
	ambientColor[GREEN] = render->Ka[GREEN] * render->ambientlight.color[GREEN];
	ambientColor[BLUE] = render->Ka[BLUE] * render->ambientlight.color[BLUE];

	//calculate color
	returnColor[RED] += clampToZero(diffuseColor[RED]);
	returnColor[GREEN] += clampToZero(diffuseColor[GREEN]);
	returnColor[BLUE] += clampToZero(diffuseColor[BLUE]);

	returnColor[RED] += ambientColor[RED];
	returnColor[GREEN] += ambientColor[GREEN];
	returnColor[BLUE] += ambientColor[BLUE];

	returnColor[RED] += clampToZero(specularColor[RED]);
	returnColor[GREEN] += clampToZero(specularColor[GREEN]);
	returnColor[BLUE] += clampToZero(specularColor[BLUE]);

	if (returnColor[RED] > 1) returnColor[RED] = 1;
	if (returnColor[GREEN] > 1) returnColor[GREEN] = 1;
	if (returnColor[BLUE] > 1) returnColor[BLUE] = 1;

	return true;
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

	//three vertices
	GzCoord vertexA, vertexB, vertexC;
	GzCoord normalA, normalB, normalC;
	GzColor colorA, colorB, colorC;
	GzTextureIndex textureA, textureB, textureC;

	for (int p = 0; p < numParts; ++p)
	{

		switch (nameList[p])
		{
			case GZ_NULL_TOKEN:
			{
				//do nothing
				break;
			}
			case GZ_NORMAL:
			{
				//get the 3 normals
				equateGzCoord(normalA, (static_cast<GzCoord*>(valueList[p]))[0]);
				equateGzCoord(normalB, (static_cast<GzCoord*>(valueList[p]))[1]);
				equateGzCoord(normalC, (static_cast<GzCoord*>(valueList[p]))[2]);

				//transform and clip
				if (!transformGzNormal(normalA, render)) return GZ_FAILURE;
				if (!transformGzNormal(normalB, render)) return GZ_FAILURE;
				if (!transformGzNormal(normalC, render)) return GZ_FAILURE;

				break;
			}
			case GZ_POSITION:
			{
				//get the 3 vertices
				equateGzCoord(vertexA, (static_cast<GzCoord*>(valueList[p]))[0]);
				equateGzCoord(vertexB, (static_cast<GzCoord*>(valueList[p]))[1]);
				equateGzCoord(vertexC, (static_cast<GzCoord*>(valueList[p]))[2]);

				//transform and clip
				if (!transformGzCoord(vertexA, render)) return GZ_FAILURE;
				if (!transformGzCoord(vertexB, render)) return GZ_FAILURE;
				if (!transformGzCoord(vertexC, render)) return GZ_FAILURE;

				break;
			}
			case GZ_TEXTURE_INDEX:
			{
				//Get the UV coordinates
				equateGzTextureIndex(textureA, (static_cast<GzTextureIndex*>(valueList[p]))[0]);
				equateGzTextureIndex(textureB, (static_cast<GzTextureIndex*>(valueList[p]))[1]);
				equateGzTextureIndex(textureC, (static_cast<GzTextureIndex*>(valueList[p]))[2]);
			}
		}
	}

	//Perspective Correction

	if (render->tex_fun != NULL)
	{
		perspectiveSpace(textureA, vertexA[Z], 2);
		perspectiveSpace(textureB, vertexB[Z], 2);
		perspectiveSpace(textureC, vertexC[Z], 2);
	}

	//calculate color
	if (render->interp_mode == GZ_COLOR)
	{
		if (render->tex_fun == NULL)
		{
			if (!shadingEquation(colorA, render, normalA)) return GZ_FAILURE;
			if (!shadingEquation(colorB, render, normalB)) return GZ_FAILURE;
			if (!shadingEquation(colorC, render, normalC)) return GZ_FAILURE;
		}
		else
		{
			//Texture turned on
			//Gouraud Shading, calculate color at each vertex
			if (!lightIntensityInterpolation(colorA, render, normalA)) return GZ_FAILURE;
			if (!lightIntensityInterpolation(colorB, render, normalB)) return GZ_FAILURE;
			if (!lightIntensityInterpolation(colorC, render, normalC)) return GZ_FAILURE;
		}
	}

	//render
	//find the points of interest, in form of [topmost, left, right]
	GzCoord vertices[3];
	GzCoord normals[3];
	GzColor colors[3];
	GzTextureIndex textures[3];

	//Case A
	if (vertexA[Y] < vertexB[Y] && vertexA[Y] < vertexC[Y])
	{
		equateGzCoord(vertices[TOP], vertexA);
		equateGzCoord(normals[TOP], normalA);
		equateGzColor(colors[TOP], colorA);
		equateGzTextureIndex(textures[TOP], textureA);
	}
	//Case B
	else if (vertexB[Y] < vertexA[Y] && vertexB[Y] < vertexC[Y])
	{
		equateGzCoord(vertices[TOP], vertexB);
		equateGzCoord(normals[TOP], normalB);
		equateGzColor(colors[TOP], colorB);
		equateGzTextureIndex(textures[TOP], textureB);
	}

	//Case C
	else
	{
		equateGzCoord(vertices[TOP], vertexC);
		equateGzCoord(normals[TOP], normalC);
		equateGzColor(colors[TOP], colorC);
		equateGzTextureIndex(textures[TOP], textureC);
	}

	//Now identify leftmost & rightmost
	if (equalityGzCoord(vertices[TOP], vertexA))
	{
		//B & C
		if (vertexB[X] <= vertexC[X])
		{
			equateGzCoord(vertices[LEFT], vertexB);
			equateGzCoord(normals[LEFT], normalB);
			equateGzColor(colors[LEFT], colorB);
			equateGzTextureIndex(textures[LEFT], textureB);

			equateGzCoord(vertices[RIGHT], vertexC);
			equateGzCoord(normals[RIGHT], normalC);
			equateGzColor(colors[RIGHT], colorC);
			equateGzTextureIndex(textures[RIGHT], textureC);
		}
		else
		{
			equateGzCoord(vertices[LEFT], vertexC);
			equateGzCoord(normals[LEFT], normalC);
			equateGzColor(colors[LEFT], colorC);
			equateGzTextureIndex(textures[LEFT], textureC);

			equateGzCoord(vertices[RIGHT], vertexB);
			equateGzCoord(normals[RIGHT], normalB);
			equateGzColor(colors[RIGHT], colorB);
			equateGzTextureIndex(textures[RIGHT], textureB);
		}
	}
	else if (equalityGzCoord(vertices[TOP], vertexB))
	{
		//A & C
		if (vertexA[X] <= vertexC[X])
		{
			equateGzCoord(vertices[LEFT], vertexA);
			equateGzCoord(normals[LEFT], normalA);
			equateGzColor(colors[LEFT], colorA);
			equateGzTextureIndex(textures[LEFT], textureA);

			equateGzCoord(vertices[RIGHT], vertexC);
			equateGzCoord(normals[RIGHT], normalC);
			equateGzColor(colors[RIGHT], colorC);
			equateGzTextureIndex(textures[RIGHT], textureC);
		}
		else
		{
			equateGzCoord(vertices[LEFT], vertexC);
			equateGzCoord(normals[LEFT], normalC);
			equateGzColor(colors[LEFT], colorC);
			equateGzTextureIndex(textures[LEFT], textureC);

			equateGzCoord(vertices[RIGHT], vertexA);
			equateGzCoord(normals[RIGHT], normalA);
			equateGzColor(colors[RIGHT], colorA);
			equateGzTextureIndex(textures[RIGHT], textureA);
		}
	}
	else
	{
		//A & B
		if (vertexA[X] <= vertexB[X])
		{
			equateGzCoord(vertices[LEFT], vertexA);
			equateGzCoord(normals[LEFT], normalA);
			equateGzColor(colors[LEFT], colorA);
			equateGzTextureIndex(textures[LEFT], textureA);

			equateGzCoord(vertices[RIGHT], vertexB);
			equateGzCoord(normals[RIGHT], normalB);
			equateGzColor(colors[RIGHT], colorB);
			equateGzTextureIndex(textures[RIGHT], textureB);
		}
		else
		{
			equateGzCoord(vertices[LEFT], vertexB);
			equateGzCoord(normals[LEFT], normalB);
			equateGzColor(colors[LEFT], colorB);
			equateGzTextureIndex(textures[LEFT], textureB);

			equateGzCoord(vertices[RIGHT], vertexA);
			equateGzCoord(normals[RIGHT], normalA);
			equateGzColor(colors[RIGHT], colorA);
			equateGzTextureIndex(textures[RIGHT], textureA);
		}
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

		//intercept = x - slope * y
		float interceptM = vertices[TOP][X] - (mainSlope * vertices[TOP][Y]);
		float interceptA = vertices[TOP][X] - (slopeA * vertices[TOP][Y]);
		float interceptB = vertices[RIGHT][X] - (slopeB * vertices[RIGHT][Y]);

		float xLeft = 0;
		float xRight = 0;

		//For Flat
		GzCoord triNormal;

		//For Gouraud
		float mainRGBSlopes[3];
		float RGBSlopesA[3];
		float RGBSlopesB[3];

		float RGBinterceptsM[3];
		float RGBinterceptsA[3];
		float RGBinterceptsB[3];

		GzColor RGBxLeft;
		GzColor RGBxRight;

		//For Phong
		float mainNormalSlopes[3];
		float normalSlopesA[3];
		float normalSlopesB[3];

		float normalInterceptsM[3];
		float normalInterceptsA[3];
		float normalInterceptsB[3];

		GzCoord normalxLeft;
		GzCoord normalxRight;

		//For Textures
		float mainTextureSlopes[2];
		float textureSlopesA[2];
		float textureSlopesB[2];

		float textureInterceptsM[2];
		float textureInterceptsA[2];
		float textureInterceptsB[2];

		GzTextureIndex texturexLeft;
		GzTextureIndex texturexRight;

		if (render->interp_mode == GZ_COLOR)
		{
			calculateRGBSlope(vertices[TOP], vertices[LEFT], colors[TOP], colors[LEFT], mainRGBSlopes);
			calculateRGBSlope(vertices[TOP], vertices[RIGHT], colors[TOP], colors[RIGHT], RGBSlopesA);
			calculateRGBSlope(vertices[RIGHT], vertices[LEFT], colors[RIGHT], colors[LEFT], RGBSlopesB);

			calculateRGBIntercepts(mainRGBSlopes, colors[TOP], vertices[TOP][Y], RGBinterceptsM);
			calculateRGBIntercepts(RGBSlopesA, colors[TOP], vertices[TOP][Y], RGBinterceptsA);
			calculateRGBIntercepts(RGBSlopesB, colors[RIGHT], vertices[RIGHT][Y], RGBinterceptsB);
		}
		else if (render->interp_mode == GZ_NORMALS)
		{
			calculateNormalSlope(vertices[TOP], vertices[LEFT], normals[TOP], normals[LEFT], mainNormalSlopes);
			calculateNormalSlope(vertices[TOP], vertices[RIGHT], normals[TOP], normals[RIGHT], normalSlopesA);
			calculateNormalSlope(vertices[RIGHT], vertices[LEFT], normals[RIGHT], normals[LEFT], normalSlopesB);

			calculateNormalIntercepts(mainNormalSlopes, normals[TOP], vertices[TOP][Y], normalInterceptsM);
			calculateNormalIntercepts(normalSlopesA, normals[TOP], vertices[TOP][Y], normalInterceptsA);
			calculateNormalIntercepts(normalSlopesB, normals[RIGHT], vertices[RIGHT][Y], normalInterceptsB);
		}
		else if (render->interp_mode == GZ_FLAT)
		{
			//calculate the normal
			GzCoord vecA;
			vecA[X] = vertices[TOP][X] - vertices[LEFT][X];
			vecA[Y] = vertices[TOP][Y] - vertices[LEFT][Y];
			vecA[Z] = vertices[TOP][Z] - vertices[LEFT][Z];

			GzCoord vecB;
			vecB[X] = vertices[LEFT][X] - vertices[RIGHT][X];
			vecB[Y] = vertices[LEFT][Y] - vertices[RIGHT][Y];
			vecB[Z] = vertices[LEFT][Z] - vertices[RIGHT][Z];

			triNormal[X] = (vecA[Y] * vecB[Z]) - (vecA[Z] * vecB[Y]);
			triNormal[Y] = (vecA[Z] * vecB[X]) - (vecA[X] * vecB[Z]);
			triNormal[Z] = (vecA[X] * vecB[Y]) - (vecA[Y] * vecB[X]);

			shadingEquation(render->flatcolor, render, triNormal);
		}

		if (render->tex_fun != NULL)
		{
			calculateTextureSlope(vertices[TOP], vertices[LEFT], textures[TOP], textures[LEFT], mainTextureSlopes);
			calculateTextureSlope(vertices[TOP], vertices[RIGHT], textures[TOP], textures[RIGHT], textureSlopesA);
			calculateTextureSlope(vertices[RIGHT], vertices[LEFT], textures[RIGHT], textures[LEFT], textureSlopesB);

			calculateTextureIntercepts(mainTextureSlopes, textures[TOP], vertices[TOP][Y], textureInterceptsM);
			calculateTextureIntercepts(textureSlopesA, textures[TOP], vertices[TOP][Y], textureInterceptsA);
			calculateTextureIntercepts(textureSlopesB, textures[RIGHT], vertices[RIGHT][Y], textureInterceptsB);
		}

		//scan set 1
		for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[RIGHT][Y]; ++j)
		{
			//for every j increment, calculate the x interpolations
			xLeft = interpolateX(mainSlope, interceptM, j);
			xRight = interpolateX(slopeA, interceptA, j);

			float mRGB[3];
			float bRGB[3];
			float mNormal[3];
			float bNormal[3];
			float deltaX = xRight - xLeft;

			float mTexture[2];
			float bTexture[2];

			if (render->interp_mode == GZ_COLOR)
			{
				//interpolate RGB
				interpolateRGB(mainRGBSlopes, RGBinterceptsM, j, RGBxLeft);
				interpolateRGB(RGBSlopesA, RGBinterceptsA, j, RGBxRight);

				calculateRGBSlopePoint(RGBxLeft, RGBxRight, deltaX, mRGB);
				calculateRGBIntercepts(mRGB, RGBxLeft, xLeft, bRGB);
			}
			else if (render->interp_mode == GZ_NORMALS)
			{
				//interpolate Normals
				interpolateNormals(mainNormalSlopes, normalInterceptsM, j, normalxLeft);
				interpolateNormals(normalSlopesA, normalInterceptsA, j, normalxRight);

				calculateNormalSlopePoint(normalxLeft, normalxRight, deltaX, mNormal);
				calculateNormalIntercepts(mNormal, normalxLeft, xLeft, bNormal);
			}

			if (render->tex_fun != NULL)
			{
				//interpolate texture UV
				interpolateTexture(mainTextureSlopes, textureInterceptsM, j, texturexLeft);
				interpolateTexture(textureSlopesA, textureInterceptsA, j, texturexRight);

				calculateTextureSlopePoint(texturexLeft, texturexRight, deltaX, mTexture);
				calculateTextureIntercepts(mTexture, texturexLeft, xLeft, bTexture);
			}

			//iterate through scan line
			for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//perspective correction Vz'
				float zPrime = Z_ / (MAXINT - Z_);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);
						
						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//Texture: for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}

				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
			}

			for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}
				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
			}
		}

		//scan set 2
		for (int j = static_cast<int>(ceil(vertices[RIGHT][Y])); j < vertices[LEFT][Y]; ++j)
		{
			//for every j increment, calculate the x interpolations
			xLeft = interpolateX(mainSlope, interceptM, j);
			xRight = interpolateX(slopeB, interceptB, j);

			float mRGB[3];
			float bRGB[3];
			float mNormal[3];
			float bNormal[3];
			float deltaX = xRight - xLeft;

			float mTexture[2];
			float bTexture[2];

			if (render->interp_mode == GZ_COLOR)
			{
				//interpolate RGB
				interpolateRGB(mainRGBSlopes, RGBinterceptsM, j, RGBxLeft);
				interpolateRGB(RGBSlopesB, RGBinterceptsB, j, RGBxRight);

				calculateRGBSlopePoint(RGBxLeft, RGBxRight, deltaX, mRGB);
				calculateRGBIntercepts(mRGB, RGBxLeft, xLeft, bRGB);
			}
			else if (render->interp_mode == GZ_NORMALS)
			{
				//interpolate Normals
				interpolateNormals(mainNormalSlopes, normalInterceptsM, j, normalxLeft);
				interpolateNormals(normalSlopesB, normalInterceptsB, j, normalxRight);

				calculateNormalSlopePoint(normalxLeft, normalxRight, deltaX, mNormal);
				calculateNormalIntercepts(mNormal, normalxLeft, xLeft, bNormal);
			}


			if (render->tex_fun != NULL)
			{
				//interpolate texture UV
				interpolateTexture(mainTextureSlopes, textureInterceptsM, j, texturexLeft);
				interpolateTexture(textureSlopesB, textureInterceptsB, j, texturexRight);

				calculateTextureSlopePoint(texturexLeft, texturexRight, deltaX, mTexture);
				calculateTextureIntercepts(mTexture, texturexLeft, xLeft, bTexture);
			}

			//iterate through scan line
			for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}
				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
			}

			for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}
				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
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

		//For Flat
		GzCoord triNormal;

		//For Gouraud
		float RGBinterceptsM[3];
		float RGBinterceptsA[3];
		float RGBinterceptsB[3];

		GzColor RGBxLeft;
		GzColor RGBxRight;

		float mainRGBSlopes[3];
		float RGBSlopesA[3];
		float RGBSlopesB[3];

		//For Phong
		float mainNormalSlopes[3];
		float normalSlopesA[3];
		float normalSlopesB[3];

		float normalInterceptsM[3];
		float normalInterceptsA[3];
		float normalInterceptsB[3];

		GzCoord normalxLeft;
		GzCoord normalxRight;

		//For Textures
		float mainTextureSlopes[2];
		float textureSlopesA[2];
		float textureSlopesB[2];

		float textureInterceptsM[2];
		float textureInterceptsA[2];
		float textureInterceptsB[2];

		GzTextureIndex texturexLeft;
		GzTextureIndex texturexRight;

		if (render->interp_mode == GZ_COLOR)
		{
			calculateRGBSlope(vertices[TOP], vertices[RIGHT], colors[TOP], colors[RIGHT], mainRGBSlopes);
			calculateRGBSlope(vertices[TOP], vertices[LEFT], colors[TOP], colors[LEFT], RGBSlopesA);
			calculateRGBSlope(vertices[LEFT], vertices[RIGHT], colors[LEFT], colors[RIGHT], RGBSlopesB);

			calculateRGBIntercepts(mainRGBSlopes, colors[TOP], vertices[TOP][Y], RGBinterceptsM);
			calculateRGBIntercepts(RGBSlopesA, colors[TOP], vertices[TOP][Y], RGBinterceptsA);
			calculateRGBIntercepts(RGBSlopesB, colors[LEFT], vertices[LEFT][Y], RGBinterceptsB);
		}
		else if (render->interp_mode == GZ_NORMALS)
		{
			calculateNormalSlope(vertices[TOP], vertices[RIGHT], normals[TOP], normals[RIGHT], mainNormalSlopes);
			calculateNormalSlope(vertices[TOP], vertices[LEFT], normals[TOP], normals[LEFT], normalSlopesA);
			calculateNormalSlope(vertices[LEFT], vertices[RIGHT], normals[LEFT], normals[RIGHT], normalSlopesB);

			calculateNormalIntercepts(mainNormalSlopes, normals[TOP], vertices[TOP][Y], normalInterceptsM);
			calculateNormalIntercepts(normalSlopesA, normals[TOP], vertices[TOP][Y], normalInterceptsA);
			calculateNormalIntercepts(normalSlopesB, normals[LEFT], vertices[LEFT][Y], normalInterceptsB);
		}
		else if (render->interp_mode == GZ_FLAT)
		{
			//calculate the normal
			GzCoord vecA;
			vecA[X] = vertices[TOP][X] - vertices[LEFT][X];
			vecA[Y] = vertices[TOP][Y] - vertices[LEFT][Y];
			vecA[Z] = vertices[TOP][Z] - vertices[LEFT][Z];

			GzCoord vecB;
			vecB[X] = vertices[LEFT][X] - vertices[RIGHT][X];
			vecB[Y] = vertices[LEFT][Y] - vertices[RIGHT][Y];
			vecB[Z] = vertices[LEFT][Z] - vertices[RIGHT][Z];

			triNormal[X] = (vecA[Y] * vecB[Z]) - (vecA[Z] * vecB[Y]);
			triNormal[Y] = (vecA[Z] * vecB[X]) - (vecA[X] * vecB[Z]);
			triNormal[Z] = (vecA[X] * vecB[Y]) - (vecA[Y] * vecB[X]);

			shadingEquation(render->flatcolor, render, triNormal);
		}


		if (render->tex_fun != NULL)
		{
			calculateTextureSlope(vertices[TOP], vertices[RIGHT], textures[TOP], textures[RIGHT], mainTextureSlopes);
			calculateTextureSlope(vertices[TOP], vertices[LEFT], textures[TOP], textures[LEFT], textureSlopesA);
			calculateTextureSlope(vertices[LEFT], vertices[RIGHT], textures[LEFT], textures[RIGHT], textureSlopesB);

			calculateTextureIntercepts(mainTextureSlopes, textures[TOP], vertices[TOP][Y], textureInterceptsM);
			calculateTextureIntercepts(textureSlopesA, textures[TOP], vertices[TOP][Y], textureInterceptsA);
			calculateTextureIntercepts(textureSlopesB, textures[LEFT], vertices[LEFT][Y], textureInterceptsB);
		}

		//scan set 1
		for (int j = static_cast<int>(ceil(vertices[TOP][Y])); j < vertices[LEFT][Y]; ++j)
		{
			//for every j increment, calculate the x interpolations
			xLeft = interpolateX(slopeA, interceptA, j);
			xRight = interpolateX(mainSlope, interceptM, j);

			float mRGB[3];
			float bRGB[3];
			float mNormal[3];
			float bNormal[3];
			float deltaX = xRight - xLeft;

			float mTexture[2];
			float bTexture[2];

			if (render->interp_mode == GZ_COLOR)
			{
				//interpolate RGB
				interpolateRGB(RGBSlopesA, RGBinterceptsA, j, RGBxLeft);
				interpolateRGB(mainRGBSlopes, RGBinterceptsM, j, RGBxRight);

				calculateRGBSlopePoint(RGBxLeft, RGBxRight, deltaX, mRGB);
				calculateRGBIntercepts(mRGB, RGBxLeft, xLeft, bRGB);
			}
			else if (render->interp_mode == GZ_NORMALS)
			{
				//interpolate Normals
				interpolateNormals(normalSlopesA, normalInterceptsA, j, normalxLeft);
				interpolateNormals(mainNormalSlopes, normalInterceptsM, j, normalxRight);

				calculateNormalSlopePoint(normalxLeft, normalxRight, deltaX, mNormal);
				calculateNormalIntercepts(mNormal, normalxLeft, xLeft, bNormal);
			}

			if (render->tex_fun != NULL)
			{
				//interpolate texture UV
				interpolateTexture(textureSlopesA, textureInterceptsA, j, texturexLeft);
				interpolateTexture(mainTextureSlopes, textureInterceptsM, j, texturexRight);

				calculateTextureSlopePoint(texturexLeft, texturexRight, deltaX, mTexture);
				calculateTextureIntercepts(mTexture, texturexLeft, xLeft, bTexture);
			}

			//iterate through scan line
			for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}
				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
			}

			for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}
				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
			}
		}

		//scan set 2
		for (int j = static_cast<int>(ceil(vertices[LEFT][Y])); j < vertices[RIGHT][Y]; ++j)
		{
			//for every j increment, calculate the x interpolations
			xLeft = interpolateX(slopeB, interceptB, j);
			xRight = interpolateX(mainSlope, interceptM, j);

			float mRGB[3];
			float bRGB[3];
			float mNormal[3];
			float bNormal[3];
			float deltaX = xRight - xLeft;
			
			float mTexture[2];
			float bTexture[2];

			if (render->interp_mode == GZ_COLOR)
			{
				//interpolate RGB
				interpolateRGB(RGBSlopesB, RGBinterceptsB, j, RGBxLeft);
				interpolateRGB(mainRGBSlopes, RGBinterceptsM, j, RGBxRight);

				calculateRGBSlopePoint(RGBxLeft, RGBxRight, deltaX, mRGB);
				calculateRGBIntercepts(mRGB, RGBxLeft, xLeft, bRGB);
			}
			else if (render->interp_mode == GZ_NORMALS)
			{
				//interpolate Normals
				interpolateNormals(normalSlopesB, normalInterceptsB, j, normalxLeft);
				interpolateNormals(mainNormalSlopes, normalInterceptsM, j, normalxRight);

				calculateNormalSlopePoint(normalxLeft, normalxRight, deltaX, mNormal);
				calculateNormalIntercepts(mNormal, normalxLeft, xLeft, bNormal);
			}

			if (render->tex_fun != NULL)
			{
				//interpolate texture UV
				interpolateTexture(textureSlopesB, textureInterceptsB, j, texturexLeft);
				interpolateTexture(mainTextureSlopes, textureInterceptsM, j, texturexRight);

				calculateTextureSlopePoint(texturexLeft, texturexRight, deltaX, mTexture);
				calculateTextureIntercepts(mTexture, texturexLeft, xLeft, bTexture);
			}

			//iterate through scan line
			for (int i = static_cast<int>(ceil(xLeft)); i < xRight; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;
				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}

				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);
			}

			for (int i = static_cast<int>(ceil(xRight)); i < xLeft; ++i)
			{
				//interpolate Z
				int Z_ = interpolateZ(vertices, i, j);

				//interpolate RGB
				GzColor color;

				//interpolate UV
				GzTextureIndex texture;

				if (render->tex_fun != NULL)
				{
					interpolateTexture(mTexture, bTexture, i, texture);

					//persepctive correction
					affineSpace(texture, Z_, 2);

					render->tex_fun(texture[U], texture[V], color);
				}

				switch (render->interp_mode)
				{
					case GZ_FLAT:
					{
						color[RED] = render->flatcolor[RED];
						color[GREEN] = render->flatcolor[GREEN];
						color[BLUE] = render->flatcolor[BLUE];
						break;
					}
					case GZ_COLOR:
					{
						//for Gourand shading, set kd, ka, and ks all to the texture color
						GzColor interpolatedColor;
						interpolateRGB(mRGB, bRGB, i, interpolatedColor);

						if (render->tex_fun != NULL)
						{
							color[RED] *= interpolatedColor[RED];
							color[GREEN] *= interpolatedColor[GREEN];
							color[BLUE] *= interpolatedColor[BLUE];
						}
						else
						{
							equateGzColor(color, interpolatedColor);
						}
						break;
					}
					case GZ_NORMALS:
					{
						if (render->tex_fun != NULL)
						{
							//for Phong shading, set kd and ka
							equateGzColor(render->Ka, color);
							equateGzColor(render->Kd, color);
						}

						GzCoord normal;
						interpolateNormals(mNormal, bNormal, i, normal);
						shadingEquation(color, render, normal);
						break;
					}
				}

				GzPutDisplay(render->display, i, j, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, Z_);

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

	return GZ_SUCCESS;
}



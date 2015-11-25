#pragma once
/**
**	classe que fornecera os principais calculos matematicos
**	necessarios, tais como calculo de angulos e operacao com vetores
**/

#include <stdlib.h>

using namespace std;

class MathSupport
{
public:
	//MathSupport(void);
	//~MathSupport(void);

	static void normalize(float vector[3]);
	static void sum(float vector1[3], float vector2[3], float resultVector[3]);
	static void sub(float vector1[3], float vector2[3], float resultVector[3]);
	static int angleInDegrees(float vector1[3], float vector2[3]);
	static float dotProduct(float vector1[3], float vector2[3]);
	static int dotProduct(int vector1[2], int vector2[2]);
	static void crossProduct(float vector1[3], float vector2[3], float resultVector[3]);
	static float distanceBetween(float vector1[3], float vector2[3]);
	static float norm(float vector[3]);
	static void basisChange(float vector[3], float basisX[3], float basisY[3], float basisZ[3], float resultVector[3]);
	static float angleInDegreesFloat(float vector1[3], float vector2[3]);
	static float angle2distance(float angle);									// retorna a distancia entre vetores unitarios dado o angulo entre eles
	static void orthogonalProjection(float v[3], float s[3], float result[3]);
	static float determinant3x3(float matrix[3][3]);
	static float determinant2x2(float matrix[2][2]);
	static void coFactor(float matrix[3][3], float ret[3][3]);
	static void transpose(float matrix[3][3]);
};


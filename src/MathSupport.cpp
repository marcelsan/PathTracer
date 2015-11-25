#include "MathSupport.h"

#include <cmath>

#define PI (3.141592653589793)

void MathSupport::normalize(float vector[3])
{
	float normVector = norm(vector);
	if(normVector != 0){
		vector[0] = vector[0] / normVector;
		vector[1] = vector[1] / normVector;
		vector[2] = vector[2] / normVector;
	}
}
void MathSupport::sum(float vector1[3], float vector2[3], float resultVector[3])
{
	resultVector[0] = vector1[0] + vector2[0];
	resultVector[1] = vector1[1] + vector2[1];
	resultVector[2] = vector1[2] + vector2[2];
}

void MathSupport::sub(float vector1[3], float vector2[3], float resultVector[3])
{
	resultVector[0] = vector1[0] - vector2[0];
	resultVector[1] = vector1[1] - vector2[1];
	resultVector[2] = vector1[2] - vector2[2];
}

int MathSupport::angleInDegrees(float vector1[3], float vector2[3])
{
	float normVetor1 = norm(vector1);
	float normVetor2 = norm(vector2);

	float dotProductV1V2 = dotProduct(vector1, vector2);
	int anguloTemp = -1; // -1 indicara erro!
	if(normVetor1 != 0 && normVetor2 != 0){
		float temp = dotProductV1V2/(normVetor1*normVetor2);
		//if(temp > 1) temp = 1;		// evitando que erros que se propaguem nas casa decimais causem erro (por ex dar um numero maior que 1)
		//if(temp < -1) temp = -1;
		
		anguloTemp = (int)(acos(temp)*(180/PI));
	}

	return anguloTemp;
}

float MathSupport::angleInDegreesFloat(float vector1[3], float vector2[3])
{
	float normVetor1 = norm(vector1);
	float normVetor2 = norm(vector2);

	float dotProductV1V2 = dotProduct(vector1, vector2);
	float anguloTemp = 0;
	if(normVetor1 != 0 && normVetor2 != 0){
		anguloTemp = (float)(acos(dotProductV1V2/(normVetor1*normVetor2))*(180/PI));
	}

	return anguloTemp;
}

float MathSupport::dotProduct(float vector1[3], float vector2[3])
{
	return ( (vector1[0] * vector2[0]) + (vector1[1] * vector2[1]) + (vector1[2] * vector2[2]) );
}

int MathSupport::dotProduct(int vector1[2], int vector2[2])
{
	return ( (vector1[0] * vector2[0]) + (vector1[1] * vector2[1]) );
}

void MathSupport::crossProduct(float vector1[3], float vector2[3], float resultVector[3])
{
	resultVector[0] = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
	resultVector[1] = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
	resultVector[2] = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
}

float MathSupport::distanceBetween(float vector1[3], float vector2[3])
{
	float distanceVector[3];
	distanceVector[0] = vector2[0] - vector1[0];
	distanceVector[1] = vector2[1] - vector1[1];
	distanceVector[2] = vector2[2] - vector1[2];
	//float norm = sqrt(pow(distanceVector[0], 2) + pow(distanceVector[1],2) + pow(distanceVector[2],2));
	
	return norm(distanceVector);
}

float MathSupport::norm(float vector[3])
{
	return sqrt(pow(vector[0], 2) + pow(vector[1],2) + pow(vector[2],2));
}

void MathSupport::basisChange(float vector[3], float basisX[3], float basisY[3], float basisZ[3], float resultVector[3])
{
	// normalizando os vetores (para serem ortonormais -assumindo que ja sao ortogonais)
	normalize(basisX);
	normalize(basisY);
	normalize(basisZ);

	//resultVector[0] = basisX[0]*vector[0] + basisY[0]*vector[1] + basisZ[0]*vector[2];
	//resultVector[1] = basisX[1]*vector[0] + basisY[1]*vector[1] + basisZ[1]*vector[2];
	//resultVector[2] = basisX[2]*vector[0] + basisY[2]*vector[1] + basisZ[2]*vector[2];
	float T[3][3];
	T[0][0] = basisX[0];
	T[1][0] = basisX[1];
	T[2][0] = basisX[2];
	T[0][1] = basisY[0];
	T[1][1] = basisY[1];
	T[2][1] = basisY[2];
	T[0][2] = basisZ[0];
	T[1][2] = basisZ[1];
	T[2][2] = basisZ[2];
	float det = determinant3x3(T);
	if(det != 0){
		float cofactorMatrix[3][3];
		coFactor(T,cofactorMatrix);
		transpose(cofactorMatrix);
		det = 1/det;
		float invT[3][3];
		invT[0][0] = det*cofactorMatrix[0][0];
		invT[0][1] = det*cofactorMatrix[0][1];
		invT[0][2] = det*cofactorMatrix[0][2]; 
		invT[1][0] = det*cofactorMatrix[1][0];
		invT[1][1] = det*cofactorMatrix[1][1];
		invT[1][2] = det*cofactorMatrix[1][2];
		invT[2][0] = det*cofactorMatrix[2][0];
		invT[2][1] = det*cofactorMatrix[2][1];
		invT[2][2] = det*cofactorMatrix[2][2];
		resultVector[0] = invT[0][0]*vector[0] + invT[0][1]*vector[1] + invT[0][2]*vector[2];
		resultVector[1] = invT[1][0]*vector[0] + invT[1][1]*vector[1] + invT[1][2]*vector[2];
		resultVector[2] = invT[2][0]*vector[0] + invT[2][1]*vector[1] + invT[2][2]*vector[2];
	}
}

float MathSupport::angle2distance(float angle)
{
	float ret = 0;
	if(angle > 0){
		angle = angle*(float)PI/(float)180.0;		// convertendo de graus para radianos
		ret = sqrt(2-2*cos(angle));			// lei dos cossenos (considerando dois vetores unitarios separados por uma angulacao 'angle')
	}
	return ret;
}

void MathSupport::orthogonalProjection(float v[3], float s[3], float result[3])
{
	result[0] = 0; result[1] = 0; result[2] = 0;

	if(s[0] != 0 && s[1] != 0 && s[2] != 0){	//o vetor s tem que ser nao nulo
		float temp = (dotProduct(v,s) / dotProduct(s,s));
		result[0] = temp * s[0];
		result[1] = temp * s[1];
		result[2] = temp * s[2];
	}
}


float MathSupport::determinant3x3(float matrix[3][3])
{
	return (matrix[0][0]*matrix[1][1]*matrix[2][2] + matrix[0][1]*matrix[1][2]*matrix[2][0] + matrix[0][2]*matrix[1][0]*matrix[2][1]
			-matrix[2][0]*matrix[1][1]*matrix[0][2] - matrix[2][1]*matrix[1][2]*matrix[0][0] - matrix[2][2]*matrix[1][0]*matrix[0][1]);
}

float MathSupport::determinant2x2(float matrix[2][2])
{
	return (matrix[0][0]*matrix[1][1]-matrix[1][0]*matrix[0][1]);
}

void MathSupport::coFactor(float matrix[3][3], float ret[3][3])
{
	int i1, j1;
	float det;
	float temp[2][2];

	for(int i=0; i < 3; i++) {
		for(int j=0; j < 3; j++) {

         // formando a submatriz 2x2 (excluindo a linha e coluna do elemento [i][j])
         i1 = 0;
         for(int ii=0; ii < 3; ii++) {
            if (ii != i){
				j1 = 0;
				for(int jj=0; jj < 3; jj++) {
				   if (jj != j){
					   temp[i1][j1] = matrix[ii][jj];
					   j1++;
				   }
				}
				i1++;
			}
         }

         /* Calculate the determinate */
         det = determinant2x2(temp);

         /* Fill in the elements of the cofactor */
         ret[i][j] = (float)(pow(-1.0,i+j+2.0) * det);		//o pow eh pra determinar o sinal
      }
   }
}

void MathSupport::transpose(float matrix[3][3])
{
	float temp1;
	temp1 = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = temp1;
	temp1 = matrix[0][2];
	matrix[0][2] = matrix[2][0];
	matrix[2][0] = temp1;
	temp1 = matrix[1][2];
	matrix[1][2] = matrix[2][1];
	matrix[2][1] = temp1;
}
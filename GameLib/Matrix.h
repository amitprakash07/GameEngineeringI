#ifndef __MATRIX_4x4_H
#define __MATRIX_4x4_H

#include <assert.h>
#include <math.h>
#include "Vector3D.h"
#include "additionaltypes.h"


namespace myEngine
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(myEngine::typedefs::MatrixMajor);
		Matrix4x4(const float, const float, const float, const float,
			const float, const float, const float, const float,
			const float, const float, const float, const float,
			const float, const float, const float, const float);
		Matrix4x4(const float[16]);
		Matrix4x4(const Matrix4x4 &);
		Matrix4x4(const Vector3D);
		void																	transpose();  //use to change transpose itself
		Matrix4x4																getTransposeMatrix4x4(); //use to get transpose matrix; doesn't change the matrix itself
		bool																	isRowMajor();
		bool																	isColumnMajor();
		void																	changeMatrixMajor(myEngine::typedefs::MatrixMajor);
		//void*																	operator new(size_t);
		Matrix4x4																operator +(const Matrix4x4);
		void																	operator +=(const Matrix4x4);
		Matrix4x4																operator -(const Matrix4x4);
		void																	operator -=(const Matrix4x4);
		void																	operator =(const Matrix4x4);
		bool																	operator ==(const Matrix4x4);
		Matrix4x4																operator *(const float);
		Matrix4x4																operator *(Matrix4x4);
		Vector3D																operator *(const Vector3D);
		float & 																operator()(const unsigned __int8, const unsigned __int8);
		bool																	isSymmetric();
		void																	invert();
		Matrix4x4																getInvertMatrix4x4();
		Vector3D																getAsVector3D();
		float																	getCoFactor(const unsigned __int8, const unsigned __int8);
		float																	getDeterminant();
		Matrix4x4																getCoFactorMatrix();
		Vector3D																getPositionFromMatrix4x4(); //Use this on your own - only meant if you created the matrix using Position of any object in the virtual world

		//Matrix4x4 Utilities
		static Matrix4x4														getIdentityMatrix();
		static Matrix4x4														getZeroMatrix();
		static Matrix4x4														getRotationMatrixAlongX(const float, myEngine::typedefs::MatrixMajor);	//argument is angle in radians
		static Matrix4x4														getRotationMatrixAlongY(const float, myEngine::typedefs::MatrixMajor);	//argument is angle in radians
		static Matrix4x4														getRotationMatrixAlongZ(const float, myEngine::typedefs::MatrixMajor);	//argument is angle in radians
		static Matrix4x4														getTranslationMatrix(const float, const float, const float, myEngine::typedefs::MatrixMajor); //argument are translation in x,y,z respectively
		static Matrix4x4														getTranslationMatrix(const Vector3D &, myEngine::typedefs::MatrixMajor); //argument are translation in x,y,z respectively
		static void																UnitTest();

	private:
		float																	mValues[16];
		myEngine::typedefs::MatrixMajor											mMatrixMajor;
		
	};
} //namespace myEngine

#endif

#include "Matrix.h"
#include "Determinant.h"



namespace myEngine
{
	
	Matrix4x4::Matrix4x4() :
		mMatrixMajor(myEngine::typedefs::COLUMN_MAJOR)
	{
		for (unsigned __int8 i = 0; i < 16; i++)
			mValues[i] = 0.0f;
	}


	Matrix4x4::Matrix4x4(myEngine::typedefs::MatrixMajor i_MatrixMajor):
		mMatrixMajor(i_MatrixMajor)
	{
		for (unsigned __int8 i = 0; i < 16; i++)
			mValues[i] = 0.0f;
	}

	Matrix4x4::Matrix4x4(const Vector3D i_vector)
	{
		mMatrixMajor = myEngine::typedefs::COLUMN_MAJOR;
		mValues[0] = 1;		mValues[4] = 0;		mValues[8] = 0;		mValues[12] = i_vector.getX();
		mValues[1] = 0;		mValues[5] = 1;		mValues[9] = 0;		mValues[13] = i_vector.getY();
		mValues[2] = 0;		mValues[6] = 0;		mValues[10] = 1;		mValues[14] = i_vector.getZ();
		mValues[3] = 0;		mValues[7] = 0;		mValues[11] = 0;		mValues[15] = 1;
	}

	//Pass Row Wise
	Matrix4x4::Matrix4x4(const float i_a, const float i_b, const float i_c, const float i_d,
		const float i_e, const float i_f, const float i_g, const float i_h,
		const float i_i, const float i_j, const float i_k, const float i_l,
		const float i_m, const float i_n, const float i_o, const float i_p):
		mMatrixMajor(myEngine::typedefs::COLUMN_MAJOR)
	{
		mValues[0] = i_a;		mValues[4] = i_b;		mValues[8] = i_c;		mValues[12] = i_d;
		mValues[1] = i_e;		mValues[5] = i_f;		mValues[9] = i_g;		mValues[13] = i_h;
		mValues[2] = i_i;		mValues[6] = i_j;		mValues[10] = i_k;		mValues[14] = i_l;
		mValues[3] = i_m;		mValues[7] = i_n;		mValues[11] = i_o;		mValues[15] = i_p;
	}


	//Pass row wise
	Matrix4x4::Matrix4x4(const float i_values[16]) 
	{
		mValues[0] = i_values[0];		mValues[4] = i_values[1];		mValues[8] = i_values[2];		mValues[12] = i_values[3];
		mValues[1] = i_values[4];		mValues[5] = i_values[5];		mValues[9] = i_values[6];		mValues[13] = i_values[7];
		mValues[2] = i_values[8];		mValues[6] = i_values[9];		mValues[10] = i_values[10];		mValues[14] = i_values[11];
		mValues[3] = i_values[12];		mValues[7] = i_values[13];		mValues[11] = i_values[14];		mValues[15] = i_values[15];
		mMatrixMajor = myEngine::typedefs::COLUMN_MAJOR;
	}

	
	
	Matrix4x4::Matrix4x4(const Matrix4x4 &i_other)
	{
		for (unsigned __int8 i = 0; i < 16; i++)
			mValues[i] = i_other.mValues[i];
		mMatrixMajor = i_other.mMatrixMajor;
	}

	
	//Returns position in Vector3d - use if you created the Matrix using Vector3D
	Vector3D Matrix4x4::getPositionFromMatrix4x4()
	{
		if (mMatrixMajor == myEngine::typedefs::COLUMN_MAJOR)
		return (Vector3D(
			mValues[12],
			mValues[13],
			mValues[14]));
		return (Vector3D(
			mValues[3],
			mValues[7],
			mValues[11]));
	}

	//Transpose itself
	void Matrix4x4::transpose()
	{
		Matrix4x4 transposed = Matrix4x4::getZeroMatrix();
		transposed.changeMatrixMajor(this->mMatrixMajor);

		for (unsigned __int8 i = 0; i < 4; i++)
		{
			for (unsigned __int8 j = 0; j < 4; j++)
			{
				transposed(i, j) = (*this)(j, i);
			}
		}
		*this = transposed;
	}
	
	
	//Doesn't change value of itself
	Matrix4x4 Matrix4x4::getTransposeMatrix4x4()
	{
		Matrix4x4 transposed = Matrix4x4::getZeroMatrix();
		transposed.changeMatrixMajor(this->mMatrixMajor);

		for (unsigned __int8 i = 0; i < 4; i++)
		{
			for (unsigned __int8 j = 0; j < 4; j++)
			{
				transposed(i, j) = (*this)(j, i);
			}
		}
		return transposed;
	}
	
	
	
	bool Matrix4x4::isRowMajor()
	{
		return (mMatrixMajor == myEngine::typedefs::ROW_MAJOR ? true : false);
	}


	
	bool Matrix4x4::isColumnMajor()
	{
		return (mMatrixMajor == myEngine::typedefs::COLUMN_MAJOR ? true : false);
	}

	
	
	void Matrix4x4::changeMatrixMajor(myEngine::typedefs::MatrixMajor i_other)
	{
		if (mMatrixMajor != i_other)
			mMatrixMajor = i_other;
	}


	/*void* Matrix4x4::operator new(size_t s) //To-Do ask
	{
		return(EngineController::GameEngine::isEngineInitialized() ?
		EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(Matrix4x4)) : new Matrix4x4());		
	}*/
	
		
	Matrix4x4 Matrix4x4::operator +(const Matrix4x4 i_other)
	{
		Matrix4x4 temp;
		for (unsigned __int8 i = 0; i < 16; i++)
			temp.mValues[i] = mValues[i] + i_other.mValues[i];
		return temp;
	}

	
	
	void Matrix4x4::operator +=(const Matrix4x4 i_other)
	{
		for (unsigned __int8 i = 0; i < 16; i++)
			mValues[i] += i_other.mValues[i];
	}

	
	
	Matrix4x4 Matrix4x4::operator -(const Matrix4x4 i_other)
	{
		Matrix4x4 temp;
		for (unsigned __int8 i = 0; i < 16; i++)
			temp.mValues[i] = mValues[i] - i_other.mValues[i];
		return temp;
	}

	
	
	void Matrix4x4::operator -=(const Matrix4x4 i_other)
	{
		for (unsigned __int8 i = 0; i < 16; i++)
			mValues[i] -= i_other.mValues[i];
	}

	
	
	void Matrix4x4::operator =(const Matrix4x4 i_other)
	{
		for (unsigned __int8 i = 0; i < 16; i++)
			mValues[i] = i_other.mValues[i];
		mMatrixMajor = i_other.mMatrixMajor;
	}

	
	bool Matrix4x4::operator ==(const Matrix4x4 i_other)
	{
		if (mMatrixMajor == i_other.mMatrixMajor)
		{
			for (unsigned __int8 i = 0; i < 16; i++)
			{
				if (mValues[i] != i_other.mValues[i])
				{
					return false;
				}
				
			}
			return true;
		}
		return false;
	}



	Matrix4x4 Matrix4x4::operator *(const float i_scalar)
	{
		Matrix4x4 temp;
		for (unsigned __int8 i = 0; i < 16; i++)
			temp.mValues[i] = mValues[i] * i_scalar;
		return temp;
	}


	
	Matrix4x4 Matrix4x4::operator *(Matrix4x4 i_other) //ask - giving error if passing as const  -  because i_other(int, int) is not defined as const function
	{
		Matrix4x4 temp = Matrix4x4::getZeroMatrix();
		
		if (temp.mMatrixMajor != i_other.mMatrixMajor)
			temp.changeMatrixMajor(i_other.mMatrixMajor);

		for (unsigned __int8 i = 0; i < 4; i++)
		{
			for (unsigned __int8 j = 0; j < 4; j++)
			{
				for (unsigned __int8 k = 0; k < 4; k++)
				{
					temp(i, j) += (*this)(i, k) * (i_other(k, j));
				}				
			}
		}
		return temp;
	}

	
	
	Vector3D Matrix4x4::operator *(Vector3D i_vector)
	{
		if (this->isColumnMajor())
		{
			return(
				Vector3D(	
				(	((*this)(0, 0)*i_vector.getX()) + ((*this)(0, 1)*i_vector.getY()) + ((*this)(0, 2)*i_vector.getZ())	 + ((*this)(0, 3)) 	),
					(((*this)(1, 0)*i_vector.getX()) + ((*this)(1, 1)*i_vector.getY()) + ((*this)(1, 2)*i_vector.getZ()) + ((*this)(1, 3))	),
					(((*this)(2, 0)*i_vector.getX()) + ((*this)(2, 1)*i_vector.getY()) + ((*this)(2, 2)*i_vector.getZ()) + ((*this)(2, 3))	)
						)
				  );
		}
		else
		{
			return(
				Vector3D(
				(i_vector.getX()*((*this)(0, 0))) + (i_vector.getY()*((*this)(1, 0))) + (i_vector.getZ()*((*this)(2, 0))) + ((*this)(3, 0)),
				(i_vector.getX()*((*this)(0, 1))) + (i_vector.getY()*((*this)(1, 1))) + (i_vector.getZ()*((*this)(2, 1))) + ((*this)(3, 1)),
				(i_vector.getX()*((*this)(0, 2))) + (i_vector.getY()*((*this)(1, 2))) + (i_vector.getZ()*((*this)(2, 2))) + ((*this)(3, 2))
				)
			);
		}		
	}


	
	float& Matrix4x4::operator()(const unsigned __int8 i_row, const unsigned __int8 i_col)
	{
		assert(i_row < 4 && i_col < 4);
		if (mMatrixMajor == myEngine::typedefs::COLUMN_MAJOR)
		{
#ifdef _ENGINE_DEBUG
			//std::cout << mValues[i_row + (4 * i_col)];
#endif
			return( mValues[i_row + (4 * i_col)]);
		}
		else
		{
			return( mValues[(i_row * 4) + i_col]);
		}
	}


	bool Matrix4x4::isSymmetric()
	{
		return ((*this).getTransposeMatrix4x4() == (*this) ? true:false);
	}


	

	Matrix4x4 Matrix4x4::getInvertMatrix4x4()
	{
		Matrix4x4 invertMatrix;
		for (unsigned __int8 i = 0; i < 4;i++)
		{
			for (unsigned __int8 j = 0; j < 4; j++)
			{
				invertMatrix(i, j) = getCoFactor(i, j);
			}
		}
		invertMatrix.transpose();
		invertMatrix = invertMatrix * (1 / myEngine::Maths::getDerteminant4x4(
			invertMatrix.mValues[0], invertMatrix.mValues[1], invertMatrix.mValues[2], invertMatrix.mValues[3],
			invertMatrix.mValues[4], invertMatrix.mValues[5], invertMatrix.mValues[6], invertMatrix.mValues[7],
			invertMatrix.mValues[8], invertMatrix.mValues[9], invertMatrix.mValues[10], invertMatrix.mValues[11],
			invertMatrix.mValues[12], invertMatrix.mValues[13], invertMatrix.mValues[14], invertMatrix.mValues[15]
			));
		return invertMatrix;
	}


	void Matrix4x4::invert()
	{
		(*this) = getInvertMatrix4x4();
	}



	float Matrix4x4::getCoFactor(const unsigned __int8 i_row, const unsigned __int8 i_col)
	{
		float f[9];
		__int8 counter= 0;
		assert(i_row < 4 && i_col < 4);
		
		for (unsigned __int8 i = 0; i < 4; i++)
		{
			for (unsigned __int8 j = 0; j < 4; j++)
			{
				if ((i != i_row) && (j != i_col))
				{
					f[counter] = (*this)(i , j);

#ifdef _ENGINE_DEBUG
					//std::cout << f[counter];
#endif

					++counter;
				}
			}
		}

		return(
			pow(-1.0f, (i_row + i_col + 2)) * myEngine::Maths::getDeterminant3x3(
			f[0], f[1], f[2],
			f[3], f[4], f[5],
			f[6], f[7], f[8]));
	}

	Matrix4x4 Matrix4x4::getCoFactorMatrix()
	{
		Matrix4x4 coFactorMatrix;
		for (unsigned __int8 i = 0; i < 4; i++)
		{
			for (unsigned __int8 j = 0; j < 4; j++)
			{
				coFactorMatrix(i, j) = getCoFactor(i, j);
			}
		}
		return coFactorMatrix;
	}



	float Matrix4x4::getDeterminant()
	{
		return(
			myEngine::Maths::getDerteminant4x4(
			mValues[0], mValues[4], mValues[8],  mValues[12],
			mValues[1], mValues[5], mValues[9],  mValues[13],
			mValues[2], mValues[6], mValues[10], mValues[14],
			mValues[3], mValues[7], mValues[11], mValues[15]
			)
			);
	}
	
	
	Matrix4x4 Matrix4x4::getIdentityMatrix()
	{
		Matrix4x4 temp;
		temp.mValues[0] = 1.0f;
		temp.mValues[5] = 1.0f;
		temp.mValues[10] = 1.0f;
		temp.mValues[15] = 1.0f;
		return temp;
	}


	Matrix4x4 Matrix4x4::getZeroMatrix()
	{
		return (Matrix4x4(myEngine::typedefs::COLUMN_MAJOR));
	}




	Matrix4x4 Matrix4x4::getRotationMatrixAlongX(const float i_angle, myEngine::typedefs::MatrixMajor i_matrixMajor)
	{
		Matrix4x4 xRotate = Matrix4x4::getIdentityMatrix();
		xRotate.mValues[5] = cos(i_angle);
		xRotate.mValues[6] = sin(i_angle);
		xRotate.mValues[9] = -sin(i_angle);
		xRotate.mValues[10] = cos(i_angle);
		if (i_matrixMajor == myEngine::typedefs::ROW_MAJOR)
		{
			xRotate.changeMatrixMajor(i_matrixMajor);
			xRotate.transpose();
		}
		return xRotate;
	}
	
	


	Matrix4x4 Matrix4x4::getRotationMatrixAlongY(const float i_angle, myEngine::typedefs::MatrixMajor i_matrixMajor)
	{
		Matrix4x4 yRotate = Matrix4x4::getIdentityMatrix();
		yRotate.mValues[0] = cos(i_angle);
		yRotate.mValues[2] = -sin(i_angle);
		yRotate.mValues[8] = sin(i_angle);
		yRotate.mValues[10] = cos(i_angle);
		if (i_matrixMajor == myEngine::typedefs::ROW_MAJOR)
		{
			yRotate.changeMatrixMajor(i_matrixMajor);
			yRotate.transpose();
		}
		return yRotate;
	}


	
	Matrix4x4 Matrix4x4::getRotationMatrixAlongZ(const float i_angle, myEngine::typedefs::MatrixMajor i_matrixMajor)
	{
		Matrix4x4 zRotate = Matrix4x4::getIdentityMatrix();
		zRotate.mValues[0] = cos(i_angle);
		zRotate.mValues[1] = sin(i_angle);
		zRotate.mValues[4] = -(sin(i_angle));
		zRotate.mValues[5] = cos(i_angle);
		if (i_matrixMajor == myEngine::typedefs::ROW_MAJOR)
		{
			zRotate.changeMatrixMajor(i_matrixMajor);
			zRotate.transpose();
		}
		return zRotate;
	}
	

	
	Matrix4x4 Matrix4x4::getTranslationMatrix(const float i_x, const float i_y, const float i_z, myEngine::typedefs::MatrixMajor i_matrixMajor)
	{
		Matrix4x4 translation = Matrix4x4::getIdentityMatrix();
		translation.mValues[12] = i_x;
		translation.mValues[13] = i_y;
		translation.mValues[14] = i_z;
		if (i_matrixMajor == myEngine::typedefs::ROW_MAJOR)
		{
			translation.changeMatrixMajor(i_matrixMajor);
			translation.transpose();
		}
		return translation;
	}

	Matrix4x4 Matrix4x4::getTranslationMatrix(const Vector3D & i_newPosition, myEngine::typedefs::MatrixMajor i_matrixMajor) //ask - why it's giving error when passing Vector as const
	{
		Matrix4x4 translation = Matrix4x4::getIdentityMatrix();
		translation.mValues[12] = i_newPosition.getX();
		translation.mValues[13] = i_newPosition.getY();
		translation.mValues[14] = i_newPosition.getZ();
		if (i_matrixMajor == myEngine::typedefs::ROW_MAJOR)
		{
			translation.changeMatrixMajor(i_matrixMajor);
			translation.transpose();
		}
		return translation;
	}


	void Matrix4x4::UnitTest()
	{
		Matrix4x4 A, B, C;
		Matrix4x4 D(
			10, 20, 30, 40,
			11, 21, 31, 41,
			12, 22, 32, 42,
			13, 23, 33, 43	);
		A = D;
		B = A + D;
		C = A * B;
		A.transpose();
		Matrix4x4 temp = A.getTransposeMatrix4x4();
		Matrix4x4 trans;
		Matrix4x4 rotate;
		Vector3D position(5, 10, 23);
		if (temp == A)
			trans = Matrix4x4::getTranslationMatrix(Vector3D(5, 5, 5), myEngine::typedefs::COLUMN_MAJOR);
		else
			rotate = Matrix4x4::getRotationMatrixAlongX(20, myEngine::typedefs::COLUMN_MAJOR);
		Matrix4x4 finalTransformation = trans * rotate;
		Vector3D finalPosition = finalTransformation * position;
		finalTransformation.invert();
	}


}//namespace myEngine
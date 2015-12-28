#ifndef MMATH_H
#define MMATH_H

#include "Matrix.h"
///  A class devoted to graphics related Math - OpenGL style

namespace  MATH {

	class MMath {
	public:
		static Matrix4 rotate(float degrees, float x, float y, float z);
		static Matrix4 translate(float x, float y, float z);
		static Matrix4 scale(float x, float y, float z);
		static Matrix4 perspective(float fovy, float aspect, float zNear, float zFar);


		/// It was just derived a different way, test it if you wish
		///static Matrix perspectiveOld(float fFov, float fAspect, float zMin, float zMax);


		static Matrix4 orthographic(float xMin, float xMax,
			float yMin, float yMax,
			float zMin, float zMax);
		static Matrix4 lookAt(float eyeX, float eyeY, float eyeZ,
			float atX, float atY, float atZ,
			float upX, float upY, float upZ);
		static Matrix4 lookAt(const Vec3& eye, const Vec3& at, const Vec3& up);

		static Matrix4 transpose(const Matrix4 m);
		static Matrix4 inverse(const Matrix4 m);
		static Matrix4 viewportNDC(int width, int height);
	};

}

#endif
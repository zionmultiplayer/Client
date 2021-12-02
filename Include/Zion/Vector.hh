#pragma once
#include "Game/CVector.h"
#include "Game/CMatrix.h"

namespace Zion
{
    class Vector2F
    {
        public:
            float x;
            float y;

    };

    class Vector3F
    {
        public:
            void operator =(CVector cvector);
            operator CVector();

            float x;
            float y;
            float z;
    };

    class Vector4F
    {
        public:
            void operator =(CMatrix cmatrix);
            operator CMatrix();
            void Normalize();
            void Slerp(Vector4F b, float t);

            float w;
            float x;
            float y;
            float z;
    };
}
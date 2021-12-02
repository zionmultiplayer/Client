#include "Zion/Vector.hh"
#include <math.h>

template<typename T>
static inline T Max(T a, T b)
{
    return (a > b ? a : b);
}

void Zion::Vector3F::operator =(CVector cvector)
{
    this->x = cvector.x;
    this->y = cvector.y;
    this->z = cvector.z;
}

Zion::Vector3F::operator CVector()
{
    CVector cvector;
    cvector.x = this->x;
    cvector.y = this->y;
    cvector.z = this->z;
    return cvector;
}

void Zion::Vector4F::operator =(CMatrix cmatrix)
{
    this->w = sqrt(Max(0.0F, 1.0F + cmatrix.right.x + cmatrix.up.y + cmatrix.at.z)) * 0.5F;
    this->x = sqrt(Max(0.0F, 1.0F + cmatrix.right.x - cmatrix.up.y - cmatrix.at.z)) * 0.5F;
    this->y = sqrt(Max(0.0F, 1.0F - cmatrix.right.x + cmatrix.up.y - cmatrix.at.z)) * 0.5F;
    this->z = sqrt(Max(0.0F, 1.0F - cmatrix.right.x - cmatrix.up.y + cmatrix.at.z)) * 0.5F;

    this->x = copysign(this->x, cmatrix.at.y - cmatrix.up.z );
    this->y = copysign(this->y, cmatrix.right.z - cmatrix.at.x);
    this->z = copysign(this->z, cmatrix.up.x - cmatrix.right.y);
}

Zion::Vector4F::operator CMatrix()
{
    CMatrix matrix;

    float sqw = this->w * this->w;
    float sqx = this->x * this->x;
    float sqy = this->y * this->y;
    float sqz = this->z * this->z;

    matrix.right.x = (sqx - sqy - sqz + sqw);
    matrix.up.y = (-sqx + sqy - sqz + sqw);
    matrix.at.z = (-sqx - sqy + sqz + sqw);

    float tmp1 = this->x * this->y;
    float tmp2 = this->z * this->w;
    matrix.up.x = 2.0F * (tmp1 + tmp2);
    matrix.right.y = 2.0F * (tmp1 - tmp2);

    tmp1 = this->x * this->z;
    tmp2 = this->y * this->w;
    matrix.at.x = 2.0F * (tmp1 - tmp2);
    matrix.right.z = 2.0F * (tmp1 + tmp2);
    tmp1 = this->y * this->z;
    tmp2 = this->x * this->w;
    matrix.at.y = 2.0F * (tmp1 + tmp2);
    matrix.up.z = 2.0F * (tmp1 - tmp2);

    return matrix;
}

void Zion::Vector4F::Normalize()
{
    float n = sqrtf(
        this->w * this->w +
        this->x * this->x +
        this->y * this->y +
        this->z * this->z);

    this->w /= n;
    this->x /= n;
    this->y /= n;
    this->z /= n;
}

void Zion::Vector4F::Slerp(Vector4F b, float t)
{
    float p1[4];
    double scale0;
    double scale1;
    double omega;
    double sinom;
    double cosom = this->x * b.x + this->y * b.y + this->z * b.z + this->w * b.w;

    if(cosom < 0.0)
    {
        cosom = -cosom;
        p1[0] = - b.x;
        p1[1] = - b.y;
        p1[2] = - b.z;
        p1[3] = - b.w;
    }
    else
    {
        p1[0] = b.x;
        p1[1] = b.y;
        p1[2] = b.z;
        p1[3] = b.w;
    }

    if(1.0F - cosom > 0.1F)
    {
        omega = acos(cosom);
        sinom = sin(omega);
        scale0 = sin((1.0F - t) * omega) / sinom;
        scale1 = sin(t * omega) / sinom;
    }
    else
    {
        scale0 = 1.0F - t;
        scale1 = t;
    }

    this->w = scale0 * this->w + scale1 * p1[3];
    this->x = scale0 * this->x + scale1 * p1[0];
    this->y = scale0 * this->y + scale1 * p1[1];
    this->z = scale0 * this->z + scale1 * p1[2];
}
/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

//----------------Affine_transformation_E2d_Begin----------------
class Affine_transformation_E2d
{
    double m00, m01;
    double m10, m11;

    Vector_E2d translation;
public:
    Affine_transformation_E2d(
        const double& _m00 = 1.0,
        const double& _m01 = 0.0,
        const double& _m10 = 0.0,
        const double& _m11 = 1.0,
        const Vector_E2d& _translation = Vector_E2d(0.0,0.0))
    {
        m00 = _m00; m01 = _m01;
        m10 = _m10; m11 = _m11;
        translation = _translation;
    }

    Point_E2d transform(const Point_E2d& P)
    {
        double x, y;
        x = m00 * P.x() + m01 * P.y() + translation.x();
        y = m10 * P.x() + m11 * P.y() + translation.y();
        return Point_E2d(x,y);
    }

    Vector_E2d transform(const Vector_E2d& V)
    {
        double x, y;
        x = m00 * V.x() + m01 * V.y();
        y = m10 * V.x() + m11 * V.y();
        return Vector_E2d(x,y);
    }
};
//----------------Affine_transformation_E2d_End----------------


//----------------Affine_transformation_E2d_types_Begin----------------
enum Affine_transformation_E2d_types {
    IDENTITY, SCALE, TRANSLATION, ROTATION
};

Affine_transformation_E2d::Affine_transformation_E2d(
        Affine_transformation_E2d_types type,
        const T& x, const T& y)
{
    if(type == TRANSLATION) {
        m00 = 1.0; m01 = 0.0;
        m10 = 0.0; m11 = 1.0;
        translation = Vector_E2d(x,y);
    }
    else if(type == SCALE) {
        m00 = x;   m01 = 0.0;
        m10 = 0.0; m11 = y;
        translation = Vector_E2d(0.0,0.0);
    }
}
//----------------Affine_transformation_E2d_types_End----------------

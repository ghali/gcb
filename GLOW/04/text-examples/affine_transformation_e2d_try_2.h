/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

//----------------Affine_transformation_E2d_1_Begin----------------
class Identity    {};
class Scale       {};
class Rotation    {};
class Translation {};

Identity    IDENTITY;
Scale       SCALE;
Rotation    ROTATION;
Translation TRANSLATION;

class Affine_transformation_E2d
{
    double m00, m01;
    double m10, m11;

    Vector_E2d translation;
public:
    void set_to_identity()
    {
        m00 = 1.0; m01 = 0.0;
        m10 = 0.0; m11 = 1.0;
    }
    Affine_transformation_E2d(
        const Identity& t)
    {
        set_to_identity();
    }
//----------------Affine_transformation_E2d_1_End----------------

//----------------Affine_transformation_E2d_2_Begin----------------
    Affine_transformation_E2d(
        const Scale& s,
        const double& xscale,
        const double& yscale)
    {
        m00 = xscale; m01 = 0.0;
        m10 = 0.0; m11 = yscale;
        translation = Vector_E2d(0,0);
    }
    Affine_transformation_E2d(
        const Translation& t,
        const Vector_E2d& _translation)
    {
        set_to_identity();
        translation = _translation;
    }
    Affine_transformation_E2d(
        const Rotation& r,
        double angle)
    {
        double c = cos(angle);
        double s = sin(angle);
        m00 = c; m01 = -s;
        m10 = s; m11 =  c;
        translation = Vector_E2d(0,0);
    }

    ...
};
//----------------Affine_transformation_E2d_2_End----------------

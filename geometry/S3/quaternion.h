/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

template<typename NT>
class Quaternion
{
    NT _r, _vi, _vj, _vk;
public:
    Quaternion(const NT& r=0, const NT& vi=0, const NT& vj=0, const NT& vk=0)
        : _r(r), _vi(vi), _vj(vj), _vk(vk) {}

    NT norm() const { return _r*_r + _vi*_vi + _vj*_vj + _vk*_vk; }

    NT magnitude() const { return std::sqrt(norm()); }

    NT r()  const { return _r; }
    NT vi() const { return _vi; }
    NT vj() const { return _vj; }
    NT vk() const { return _vk; }

    Quaternion<NT>
    conjugate() const {
        return Quaternion<NT>(_r, -_vi, -_vj, -_vk);
    }

    Quaternion<NT>
    operator+(const Quaternion<NT>& q2) const
    {
        return Quaternion(_r+q2._r, _vi+q2._vi, _vj+q2._vj, _vk+q2._vk);
    }
    Quaternion<NT>
    operator*(const NT& k) const
    {
        return Quaternion(k*_r, k*_vi, k*_vj, k*_vk);
    }

    Quaternion<NT>
    operator*(const Quaternion<NT>& q2) const
    {
        // ii = jj = kk = -1
        NT newr  = _r * q2._r  - _vi * q2._vi - _vj * q2._vj - _vk * q2._vk;
        // jk = -kj = i;  ki = -ik = j;  ij = -ji = k
        NT newvi = _r * q2._vi + _vi * q2._r  + _vj * q2._vk - _vk * q2._vj;
        NT newvj = _r * q2._vj + _vj * q2._r  + _vk * q2._vi - _vi * q2._vk;
        NT newvk = _r * q2._vk + _vk * q2._r  + _vi * q2._vj - _vj * q2._vi;
        return Quaternion(newr, newvi, newvj, newvk);
    }
};

template<class S>
S
dot_product(const Quaternion<S>& q1, const Quaternion<S>& q2)
{
    return q1.r() * q2.r() + q1.vi() * q2.vi() + q1.vj() * q2.vj() + q1.vk() * q2.vk();
}

#endif // QUATERNION_H

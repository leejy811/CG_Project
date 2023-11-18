#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <stdio.h>

class Vec3
{
public:
	double _value[3];
public:
	Vec3(void)
	{
		_value[0] = 0.0;
		_value[1] = 0.0;
		_value[2] = 0.0;
	}
	Vec3(double v)
	{
		_value[0] = v;
		_value[1] = v;
		_value[2] = v;

	}
	Vec3(Vec3 const& v)
	{
		_value[0] = v._value[0];
		_value[1] = v._value[1];
		_value[2] = v._value[2];
	}
	Vec3(double const& x, double const& y, double const& z)
	{
		_value[0] = x;
		_value[1] = y;
		_value[2] = z;
	}
	~Vec3() {}
	void						x(double d) { _value[0] = d; }
	void						y(double d) { _value[1] = d; }
	void						z(double d) { _value[2] = d; }
	void						set(double v)
	{
		_value[0] = v;
		_value[1] = v;
		_value[2] = v;

	}
	void						set(double& v)
	{
		_value[0] = v;
		_value[1] = v;
		_value[2] = v;

	}
	void						set(Vec3 v)
	{
		_value[0] = v._value[0];
		_value[1] = v._value[1];
		_value[2] = v._value[2];
	}
	void						set(double x, double y, double z)
	{
		_value[0] = x;
		_value[1] = y;
		_value[2] = z;
	}
	void						set(double* p)
	{
		_value[0] = p[0];
		_value[1] = p[1];
		_value[2] = p[2];
	}
	void						set(float* p)
	{
		_value[0] = p[0];
		_value[1] = p[1];
		_value[2] = p[2];
	}
	void						clear(void)
	{
		_value[0] = 0.0;
		_value[1] = 0.0;
		_value[2] = 0.0;
	}
	void						print(void)
	{
		printf("%f, %f, %f\n", _value[0], _value[1], _value[2]);
	}
	void						normalize(void)
	{
		double norm = getNorm();
		if (norm != 0) {
			_value[0] = _value[0] / norm;
			_value[1] = _value[1] / norm;
			_value[2] = _value[2] / norm;
		}
	}
	void						inverse(void)
	{
		_value[0] *= -1.0;
		_value[1] *= -1.0;
		_value[2] *= -1.0;
	}

	Vec3	abs()
	{
		Vec3 vector;
		vector.x(fabs(x()));
		vector.y(fabs(y()));
		vector.z(fabs(z()));
		return vector;
	}

	double						getNorm(void)
	{
		return sqrt(_value[0] * _value[0] + _value[1] * _value[1] + _value[2] * _value[2]);
	}
	double						length(void)
	{
		return(sqrt(lengthSquared()));
	}
	double						lengthSquared(void)
	{
		return (_value[0] * _value[0] + _value[1] * _value[1] + _value[2] * _value[2]);
	}
	double						dot(Vec3& v)
	{
		return (_value[0] * v.x() + _value[1] * v.y() + _value[2] * v.z());
	}
	double						x(void) { return _value[0]; }
	double						y(void) { return _value[1]; }
	double						z(void) { return _value[2]; }
	double& get(int n)
	{
		return  *((&_value[0]) + n);
	}
	Vec3	cross(Vec3& v)
	{
		Vec3 vector;
		vector.x((_value[1] * v.z()) - (_value[2] * v.y()));
		vector.y((_value[2] * v.x()) - (_value[0] * v.z()));
		vector.z((_value[0] * v.y()) - (_value[1] * v.x()));
		return vector;
	}
public:
	bool						operator==(Vec3 const& v) const
	{
		return _value[0] == v._value[0] && _value[1] == v._value[1] && _value[2] == v._value[2];
	}
	bool						operator!=(Vec3 const& v) const
	{
		return _value[0] != v._value[0] && _value[1] != v._value[1] && _value[2] != v._value[2];
	}
	double& operator()(int index)
	{
		return  *((&_value[0]) + index);
	}
	double& operator[](int index)
	{
		return  *((&_value[0]) + index);
	}
	double const& operator()(int index) const
	{
		return  *((&_value[0]) + index);
	}

	Vec3 operator*(Vec3 v)
	{
		return Vec3(this->x() * v.x(), this->y() * v.y(), this->z() * v.z());
	}

	double const& operator[](int index) const
	{
		return  *((&_value[0]) + index);
	}
	Vec3& operator=(Vec3 const& v)
	{
		_value[0] = v._value[0];
		_value[1] = v._value[1];
		_value[2] = v._value[2];
		return *this;
	}
	Vec3& operator+=(Vec3 const& v)
	{
		_value[0] += v._value[0];
		_value[1] += v._value[1];
		_value[2] += v._value[2];
		return *this;
	}
	Vec3& operator+=(double v)
	{
		_value[0] += v;
		_value[1] += v;
		_value[2] += v;
		return *this;
	}
	Vec3& operator-=(double v)
	{
		_value[0] -= v;
		_value[1] -= v;
		_value[2] -= v;
		return *this;
	}
	Vec3& operator-=(Vec3 const& v)
	{
		_value[0] -= v._value[0];
		_value[1] -= v._value[1];
		_value[2] -= v._value[2];
		return *this;
	}
	Vec3& operator*=(double const& d)
	{
		_value[0] *= d;
		_value[1] *= d;
		_value[2] *= d;
		return *this;
	}
	Vec3& operator*=(Vec3& v)
	{
		_value[0] *= v.x();
		_value[1] *= v.y();
		_value[2] *= v.z();
		return *this;
	}
	Vec3& operator/=(double const& d)
	{
		_value[0] /= d;
		_value[1] /= d;
		_value[2] /= d;
		return *this;
	}
	Vec3	operator/(const double& d)
	{
		return Vec3(_value[0] / d, _value[1] / d, _value[2] / d);
	}
	Vec3	operator*(const double& d)
	{
		return Vec3(_value[0] * d, _value[1] * d, _value[2] * d);
	}
	Vec3	operator-(const double& d)
	{
		return Vec3(_value[0] - d, _value[1] - d, _value[2] - d);
	}
	Vec3	operator+(const double& d)
	{
		return Vec3(_value[0] + d, _value[1] + d, _value[2] + d);
	}
	Vec3	operator-() const
	{
		return Vec3(-_value[0], -_value[1], -_value[2]);
	}
	Vec3	operator+(Vec3 const& v) const
	{
		return Vec3(_value[0] + v._value[0], _value[1] + v._value[1], _value[2] + v._value[2]);
	}
	Vec3	operator-(Vec3 const& v) const
	{
		return Vec3(_value[0] - v._value[0], _value[1] - v._value[1], _value[2] - v._value[2]);
	}
	Vec3	operator/(Vec3& v)
	{
		return Vec3(_value[0] / v._value[0], _value[1] / v._value[1], _value[2] / v._value[2]);
	}
	//Vec3	operator*(Vec3	v)
	//{
	//	return Vec3(_value[0] * v._value[0], _value[1] * v._value[1], _value[2] * v._value[2]);
	//}
	double						angleBetweenVectors(Vec3& v)
	{
		Vec3 tmp;
		tmp.set(cross(v));
		return atan2(tmp.length(), dot(v));
	}
	Vec3	getOrtho(void)
	{
		if (_value[0] != 0) {
			return Vec3(-_value[1], _value[0], 0);
		}
		else {
			return Vec3(1, 0, 0);
		}
	}
	void						processInner(Vec3* u, Vec3* v)
	{
		_value[0] = u->y() * v->z() - u->z() * v->y();
		_value[1] = u->z() * v->x() - u->x() * v->z();
		_value[2] = u->x() * v->y() - u->y() * v->x();
	}
};

#endif
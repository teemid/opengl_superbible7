#ifndef SB_VMATH_H
#define SB_VMATH_H

#include <cmath>


struct Vector2f
{
    union
    {
        float data[2];
        struct { float x, y; };
        struct { float u, v; };
    };

    inline Vector2f (void) : x(0), y(0) { }
    inline Vector2f (float x, float y) : x(x), y(y) { };

    inline Vector2f & operator +=(const Vector2f & rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    inline Vector2f & operator -=(const Vector2f & rhs)
    {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    inline Vector2f & operator +=(const float s)
    {
        x += s;
        y += s;

        return *this;
    }

    inline Vector2f & operator -=(const float s)
    {
        x -= s;
        y -= s;

        return *this;
    }

    inline Vector2f & operator *=(const float s)
    {
        x *= s;
        y *= s;

        return *this;
    }

    inline Vector2f & operator /=(const float s)
    {
        x /= s;
        y /= s;

        return *this;
    }

    inline Vector2f operator +(const Vector2f & rhs)
    {
        Vector2f v = { x + rhs.x, y + rhs.y };

        return v;
    }

    inline Vector2f operator -(const Vector2f & rhs)
    {
        Vector2f v = { x - rhs.x, y - rhs.y };

        return v;
    }

    inline Vector2f operator +(const float s)
    {
        Vector2f v = { x + s, y + s };

        return v;
    }

    inline Vector2f operator -(const float s)
    {
        Vector2f v = { x - s, y - s };

        return v;
    }

    inline Vector2f operator *(const float s)
    {
        Vector2f v = { x * s, y * s };

        return v;
    }

    inline Vector2f operator /(const float s)
    {
        Vector2f v = { x / s, y / s };

        return v;
    }

    inline Vector2f operator -(void)
    {
        Vector2f v = { -x, -y };

        return v;
    }

    inline bool operator ==(const Vector2f & rhs)
    {
        return (x == rhs.x) && (y == rhs.y);
    }

    inline bool operator !=(const Vector2f & rhs)
    {
        return !(*this == rhs);
    }

    inline bool operator < (const Vector2f & rhs)
    {
        return (x < rhs.x) && (y < rhs.y);
    }

    inline bool operator > (const Vector2f & rhs)
    {
        return (x > rhs.x) && (y > rhs.y);
    }

    inline bool operator <=(const Vector2f & rhs)
    {
        return (*this < rhs) || (*this == rhs);
    }

    inline bool operator >=(const Vector2f & rhs)
    {
        return (*this < rhs) || (*this == rhs);
    }
};


struct Vector3f
{
    union
    {
        float data[3];
        struct { float x, y, z; };
        struct { float r, g, b; };
    };

    inline Vector3f (void) : x(0), y(0), z(0) { };
    inline Vector3f (float i) : x(i), y(i), z(i) { };
    inline Vector3f (float x, float y, float z) : x(x), y(y), z(z) { };

    inline Vector3f & operator +=(const Vector3f & rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    inline Vector3f & operator -=(const Vector2f & rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    inline Vector3f & operator +=(const float s)
    {
        x += s;
        y += s;
        z += s;

        return *this;
    }

    inline Vector3f & operator -=(const float s)
    {
        x -= s;
        y -= s;
        z -= s;

        return *this;
    }

    inline Vector3f & operator *=(const float s)
    {
        x *= s;
        y *= s;
        z *= s;

        return *this;
    }

    inline Vector3f & operator /=(const float s)
    {
        x /= s;
        y /= s;
        z /= s;

        return *this;
    }

    inline Vector3f operator +(Vector3f lhs, Vector3f rhs)
    {
        lhs += rhs;

        return lhs;
    }

    inline Vector3f operator -(Vector3f lhs, Vector3f rhs)
    {
        lhs -= rhs;

        return lhs;
    }

    inline Vector3f operator +(Vector3f lhs, float s)
    {
        lhs += s;

        return r;
    }

    inline Vector3f operator -(Vector3f lhs, float s)
    {
        lhs -= s;

        return lhs;
    }

    inline Vector3f operator *(Vector3f lhs, float s)
    {
        lhs *= s;

        return lhs;
    }

    inline Vector3f operator /(Vector3f lhs, float s)
    {
        lhs /= s;

        return lhs;
    }

    inline Vector3f operator -(void)
    {
        Vector3f v = { -x, -y };

        return v;
    }

    inline bool operator ==(const Vector3f & lhs, const Vector3f & rhs)
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }

    inline bool operator !=(const Vector3f & lhs, const Vector3f & rhs)
    {
        return !(lhs == rhs);
    }

    inline bool operator < (const Vector3f & lhs, const Vector3f & rhs)
    {
        return (lhs.x < rhs.x) && (lhs.y < rhs.y);
    }

    inline bool operator > (const Vector3f & lhs, const Vector3f & rhs)
    {
        return (lhs.x > rhs.x) && (lhs.y > rhs.y);
    }

    inline bool operator <=(const Vector3f & lhs, const Vector3f & rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }

    inline bool operator >=(const Vector3f & lhs, const Vector3f & rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }
}


struct Vector4f
{
    union
    {
        float data[4];
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
    }

    inline Vector4f (void) : x(0), y(0), z(0), w(0) { };
    inline Vector4f (float i) : x(i), y(i), z(i), w(0) { };
    inline Vector4f (float x, float y, float z) : x(x), y(y), z(z), w(0) { };

    inline Vector4f & operator +=(const Vector4f & rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    inline Vector4f & operator -=(const Vector4f & rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    inline Vector4f & operator +=(const float s)
    {
        x += s;
        y += s;
        z += s;

        return *this;
    }

    inline Vector4f & operator -=(const float s)
    {
        x -= s;
        y -= s;
        z -= s;

        return *this;
    }

    inline Vector4f & operator *=(const float s)
    {
        x *= s;
        y *= s;
        z *= s;

        return *this;
    }

    inline Vector4f & operator /=(const float s)
    {
        x /= s;
        y /= s;
        z /= s;

        return *this;
    }

    inline Vector4f operator +(Vector4f lhs, Vector3f rhs)
    {
        lhs += rhs;

        return lhs;
    }

    inline Vector4f operator -(Vector4f lhs, Vector3f rhs)
    {
        lhs -= rhs;

        return lhs;
    }

    inline Vector4f operator +(Vector4f lhs, float s)
    {
        lhs += s;

        return r;
    }

    inline Vector4f operator -(Vector4f lhs, float s)
    {
        lhs -= s;

        return lhs;
    }

    inline Vector4f operator *(Vector4f lhs, float s)
    {
        lhs *= s;

        return lhs;
    }

    inline Vector4f operator /(Vector4f lhs, float s)
    {
        lhs /= s;

        return lhs;
    }

    inline Vector4f operator -(void)
    {
        Vector4f v = { -x, -y };

        return v;
    }

    inline bool operator ==(const Vector4f & lhs, const Vector4f & rhs)
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }

    inline bool operator !=(const Vector4f & lhs, const Vector4f & rhs)
    {
        return !(lhs == rhs);
    }

    inline bool operator < (const Vector4f & lhs, const Vector4f & rhs)
    {
        return (lhs.x < rhs.x) && (lhs.y < rhs.y);
    }

    inline bool operator > (const Vector4f & lhs, const Vector4f & rhs)
    {
        return (lhs.x > rhs.x) && (lhs.y > rhs.y);
    }

    inline bool operator <=(const Vector4f & lhs, const Vector4f & rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }

    inline bool operator >=(const Vector4f & lhs, const Vector4f & rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }
}



struct Matrix4f
{
    union
    {
        float data[16];
        Vector4f row[4];
    }
}


inline float LengthSquared (Vector2f & v)
{
    return v.x * v.x + v.y + v.y;
}

inline float LengthSquared (Vector3f & v)
{
    return v.x * v.x + v.y + v.y + v.z * v.z;
}

inline float LengthSquared (Vector4f & v)
{
    return v.x * v.x + v.y + v.y + v.z * v.z;
}

inline float Length (Vector2f & v)
{
    return sqrt(LengthSquared(v));
}

inline float Length (Vector3f & v)
{
    return sqrt(LengthSquared(v));
}

inline float Length (Vector4f & v)
{
    return sqrt(LengthSquared(v));
}

inline Vector2f Normalize (Vector2f & v)
{
    Vector2f r;

    auto length = Length(v);

    r.x = v.x / length;
    r.y = v.y / length;

    return r;
}

inline Vector3f Normalize (Vector3f & v)
{
    Vector3f r;

    auto length = Length(v);

    r.x = v.x / length;
    r.y = v.y / length;
    r.z = v.z / length;

    return r;
}

inline Vector4f Normalize (Vector4f & v)
{
    Vector4f r;

    auto length = Length(v);

    r.x = v.x / length;
    r.y = v.y / length;
    r.z = v.z / length;

    return r;
}

inline float Dot (Vector2f & v1, Vector2f & v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

inline float Dot (Vector3f & v1, Vector3f & v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float Dot (Vector4f & v1, Vector4f & v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


inline float Angle (Vector2f & v1, Vector2f & v2)
{
    auto product = Dot(v1, v2);

    auto l = Length(v1) * Length(v2);

    return acos(product / l);
}

inline float Angle (Vector3f & v1, Vector3f & v2)
{
    auto product = Dot(v1, v2);

    auto l = Length(v1) * Length(v2);

    return acos(product / l);
}

inline float Angle (Vector4f & v1, Vector4f & v2)
{
    auto product = Dot(v1, v2);

    auto l = Length(v1) * Length(v2);

    return acos(product / l);
}

inline Vector3f Cross(Vector3f & v1, Vector3f & v2)
{
    Vector3f r;

    r.x = v1.y * v2.z - v1.z * v2.y;
    r.y = v1.z * v2.x - v1.x * v2.z;
    r.z = v1.x * v2.y - v1.y * v2.x;

    return r;
}


#endif

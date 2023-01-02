#include <cmath>

struct vec2 {
    float x, y;
    vec2() {
        this->x = 0;
        this->y = 0;
    }
    vec2(float a, float b) {
        this->x = a;
        this->y = b;
    }
};

struct vec3 {
    float x, y, z;
    float r, g, b;
    vec3() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    vec3(float a, float b, float c) {
        this->x = a;
        this->y = b;
        this->z = c;
    }
    vec3(float a, float b, float c, float d, float e, float f) {
        this->x = a;
        this->y = b;
        this->z = c;
        this->r = d;
        this->g = e;
        this->b = f;
    }
    vec3 operator/(float a) {
        return vec3(this->x / a, this->y / a, this->z / a, this->r, this->g, this->b);
    }
    vec3 operator*(float a) {
        return vec3(this->x * a, this->y * a, this->z * a, this->r, this->g, this->b);
    }
    vec3 operator+(float a) {
        return vec3(this->x + a, this->y + a, this->z + a, this->r, this->g, this->b);
    }
    vec3 operator+(vec3 a) {
        return vec3(this->x + a.x, this->y + a.y, this->z + a.z, this->r, this->g, this->b);
    }
    vec3 operator-(vec3 a) {
        return vec3(this->x - a.x, this->y - a.y, this->z - a.z, this->r, this->g, this->b);
    }
};

float length(vec3 a, vec3 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + 
                (a.y - b.y) * (a.y - b.y) + 
                (a.z - b.z) * (a.z - b.z));
}

struct sphere {
    vec3 c;
    float r;
    vec3 color;
    sphere() {
        this->c = vec3();
        this->r = 1.f;
        this->color = vec3();
    }
    sphere(vec3 a, float b) {
        this->c = a;
        this->r = b;
        this->color = vec3();
    }
    sphere(vec3 a, float b, vec3 c) {
        this->c = a;
        this->r = b;
        this->color = c;
    }
    float dist(vec3 p) {
        return length(this->c, p) - this->r;
    }
};

struct plane {
    float y;
    vec3 color;
    plane() {
        this->y = 0;
        this->color = vec3();
    }
    plane(float a) {
        this->y = a;
        this->color = vec3();
    }
    plane(float a, vec3 b) {
        this->y = a;
        this->color = b;
    }
    float dist(vec3 p) {
        return p.y - y;
    }
};

float clamp(float a, float b, float c) {
    return fmin(fmax(a, b), c);
}

vec3 RotateY(vec3 c, float angle, vec3 p) {
    float sn = sin(angle);
    float cs = cos(angle);

    p.x -= c.x;
    p.z -= c.z;

    float xnew = p.x * cs - p.z * sn;
    float znew = p.x * sn + p.z * cs;

    p.x = xnew + c.x;
    p.z = znew + c.z;
    return p;
}

vec3 norm(vec3 vec) {
    return vec / length(vec3(), vec);
}

vec3 dir(vec3 a, vec3 b) {
    return norm(vec3(b.x - a.x, b.y - a.y, b.z - a.z));
}

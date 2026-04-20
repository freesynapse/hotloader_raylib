#ifndef __RAYLIB_UTILS_H
#define __RAYLIB_UTILS_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#include <raylib.h>

#define _min(a, b) ((a) < (b) ? (a) : (b))
#define _max(a, b) ((a) > (b) ? (a) : (b))
#define _clamp(a, lo, hi) _max((lo), _min((a), (hi)))

//
class vec2
{
public:
    //
    float x, y;
    
    //
    vec2() {}
    vec2(float x, float y) : x(x), y(y) {}
    vec2(const Vector2 v) : x(v.x), y(v.y) {}
    
    //
    vec2 operator+(const vec2 &v)  { return vec2(x+v.x, y+v.y);  }
    vec2 operator+(float f)        { return vec2(x+f, y+f);      }
    void operator+=(const vec2 &v) { this->x+=v.x; this->y+=v.y; }
    void operator+=(float f)       { this->x+=f; this->y+=f;     }
    
    vec2 operator-(const vec2 &v)  { return vec2(x-v.x, y-v.y);  }
    vec2 operator-(float f)        { return vec2(x-f, y-f);      }
    void operator-=(const vec2 &v) { this->x-=v.x; this->y-=v.y; }
    void operator-=(float f)       { this->x-=f; this->y-=f;     }

    //component-wise multiplication and division
    vec2 operator*(const vec2 &v)  { return vec2(x*v.x, y*v.y);  }
    vec2 operator*(float f)        { return vec2(x*f, y*f);      }
    void operator*=(const vec2 &v) { this->x*=v.x; this->y*=v.y; }
    void operator*=(float f)       { this->x*=f; this->y*=f;     }

    vec2 operator/(const vec2 &v)  { return vec2(x/v.x, y/v.y);  }
    vec2 operator/(float f)        { return vec2(x/f, y/f);      }
    void operator/=(const vec2 &v) { this->x/=v.x; this->y/=v.y; }
    void operator/=(float f)       { this->x/=f; this->y/=f;     }

    // calculates distance between this and another vector
    float dist(const vec2 &v) const { float dx = v.x-this->x; float dy = v.y-this->y; return sqrtf(dx*dx + dy*dy); }
    // calculates length of vector
    float len() const { return sqrtf(x*x + y*y); }
    // calculates squared length of vector
    float len2() const { return x*x + y*y; }
    // normalizes the vector
    void norm() { float l = this->len(); x /= l; y /= l; }
    // sets the length to l
    void setlen(float l) { this->norm(); x *= l; y *= l; }

    // calculate the dot product between vectors (commutative)
    float dot(const vec2 &v) const { return x*v.x + y*v.y; }
    // calculate cos(theta)
    float theta(const vec2 &v) const { return this->dot(v) / (this->len() * v.len()); }
    // computes the angle (in radians) from theta
    float angle(const vec2 &v) const { return acosf(this->theta(v)); }
    // Calculates the cross porduct (or vector product), corresponding to the area of the 
    // parallellogram defined by the vectors. A negative cross product indicates clockwise
    // rotation. (non-commutative)
    float cross(const vec2 &v) { return x*v.y - y*v.x; }

    // adjusts components to lower limit
    void setmin(float lim) { x = _max(x, lim);  y = _max(y, lim);  }
    // adjusts components to lower limit (element-wise)
    void setmin(float xlim, float ylim) { x = _max(x, xlim); y = _max(y, ylim); }
    // limits length of vector to at least the lim value
    void setminlen(float lim)
    {
        float l = this->len();
        if (l < lim)
            this->setlen(lim);
    }
    // adjusts components to upper limit
    void setmax(float lim) { x = _min(x, lim);  y = _min(y, lim);  }
    // adjusts components to upper limit (element-wise)
    void setmax(float xlim, float ylim) { x = _min(x, xlim); y = _min(y, ylim); }
    // limits length of vector to at most the lim value
    void setmaxlen(float lim)
    {
        float l = this->len();
        if (l > lim)
            this->setlen(lim);
    }
    // clamps components between values
    void clamp(float lo, float hi) { x = _clamp(x, lo, hi);   y = _clamp(y, lo, hi);   }
    // clamps components between values (element-wise)
    void clamp(float xlo, float xhi, float ylo, float yhi) { x = _clamp(x, xlo, xhi); y = _clamp(y, ylo, yhi); }
    // clamps len between values
    void clamplen(float lo, float hi)
    {
        float l = this->len();
        if (l < lo)
            this->setlen(lo);
        else if (l > hi)
            this->setlen(hi);
    }
    // convert vector to raylib-style vector
    Vector2 to_rlvec2() { return (Vector2){ .x=x, .y=y }; }
    // print to stdout (debug)
    void print(const char *pfx="") { printf("vec2(%s) = [ %.2f  %.2f ]\n", strcmp(pfx, "") == 0 ? "" : pfx, x, y); }

};

// element-wise addition
vec2 vec2add(const vec2 &a, const vec2 &b) { return { a.x+b.x, a.y+b.y}; }
// element-wise addition (in-place) of vector a
void vec2add(vec2 *a, const vec2 &b) { *a+=b; }
// scalar addition
vec2 vec2add(const vec2 &v, float f) { return { v.x+f, v.y+f}; }
// scalar addition (in-place)
void vec2add(vec2 *v, float f) { *v+=f; }

// element-wise subtraction
vec2 vec2sub(const vec2 &a, const vec2 &b) { return { a.x-b.x, a.y-b.y}; }
// element-wise subtraction (in-place) of vector a
void vec2sub(vec2 *a, const vec2 &b) { *a-=b; }
// scalar subtraction
vec2 vec2sub(const vec2 &v, float f) { return { v.x-f, v.y-f}; }
// scalar subtraction (in-place)
void vec2sub(vec2 *v, float f) { *v-=f; }

// element-wise multiplication
vec2 vec2mult(const vec2 &a, const vec2 &b) { return { a.x*b.x, a.y*b.y}; }
// element-wise multiplication (in-place) of vector a
void vec2mult(vec2 *a, const vec2 &b) { *a*=b; }
// scalar multiplication
vec2 vec2mult(const vec2 &v, float f) { return { v.x*f, v.y*f}; }
// scalar multiplication (in-place)
void vec2mult(vec2 *v, float f) { *v*=f; }

// element-wise division
vec2 vec2div(const vec2 &a, const vec2 &b) { return { a.x/b.x, a.y/b.y}; }
// element-wise division (in-place) of vector a
void vec2div(vec2 *a, const vec2 &b) { *a/=b; }
// scalar division
vec2 vec2div(const vec2 &v, float f) { return { v.x/f, v.y/f}; }
// scalar division (in-place)
void vec2div(vec2 *v, float f) { *v/=f; }

// calculates distance between two vectors
float vec2dist(const vec2 &a, const vec2 &b) { float dx=a.x-b.x; float dy=a.y-b.y; return sqrtf(dx*dx+dy*dy); }
// calculate length
float vec2len(const vec2 &v) { return sqrtf(v.x*v.x+v.y*v.y); }
// calculates the squared length
float vec2len2(const vec2 &v) { return v.x*v.x+v.y*v.y; }
// normalizes the vector (in-place)
void vec2norm(vec2 *v) { float l=vec2len(*v); *v/=l; }
// returns a new, normalized vector
vec2 vec2norm(const vec2 &v) { return vec2div(v, vec2len(v)); }
// sets the length to l (in-place)
void vec2setlen(vec2 *v, float l) { v->norm(); *v*=l; }
// returns a new vector with length of l
vec2 vec2setlen(const vec2 &v, float l) { return vec2mult(vec2norm(v), l); }

// calculate the dot product between vectors (commutative)
float vec2dot(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }
// calculate cos(theta)
float vec2theta(const vec2 &a, const vec2 &b) { return  vec2dot(a, b) / (vec2len(a) * vec2len(b)); }
// computes the angle (in radians) from theta
float vec2angle(const vec2 &a, const vec2 &b) { return acosf(vec2theta(a, b)); }
// Calculates the cross porduct (or vector product), corresponding to the area of the 
// parallellogram defined by the vectors. A negative cross product indicates clockwise
// rotation. (non-commutative)
float vec2cross(const vec2 &a, const vec2 &b) { return a.x*b.y-a.y*b.x; }

// creates a random unit vector
vec2 vec2randunit()
{
    vec2 v((((float)rand()) / (float)RAND_MAX) * 2.0f - 1.0f,
           (((float)rand()) / (float)RAND_MAX) * 2.0f - 1.0f);
    v.norm();
    return v;
}
// creates a random vector defined by limits (component-wise)
vec2 vec2rand(float xlo, float xhi, float ylo, float yhi)
{
    return { (((float)rand()) / (float)RAND_MAX) * (xhi - xlo) + xlo,
             (((float)rand()) / (float)RAND_MAX) * (yhi - ylo) + ylo };
}
// creates a random vector defined by common limits
vec2 vec2rand(float lo, float hi)
{
    return { (((float)rand()) / (float)RAND_MAX) * (hi - lo) + lo,
             (((float)rand()) / (float)RAND_MAX) * (hi - lo) + lo };
}

// convert to raylib-style vector
Vector2 vec2torlvec2(const vec2 &v) { return (Vector2){ .x=v.x, .y=v.y }; }
// convert from raylib-style vector
vec2 rlvec2tovec2(const Vector2 &v) { return vec2(v.x, v.y); }
// print to stdout (debug)
void vec2print(const vec2 &v, const char *pfx="") { printf("vec2(%s) = [ %.2f  %.2f ]\n", strcmp(pfx, "") == 0 ? "" : pfx, v.x, v.y); }

// MISCELLANEOUS //////////////////////////////////////////////////////////////////////////////////
//

// Returns a random float in [lo..hi] (inclusive)
float randf_range(float lo, float hi)
{
    float f = ((float)rand()) / (float)RAND_MAX;
    return f * (hi - lo) + lo;
}
// Returns a random float in [0..1] (inclusive)
float randf() { return ((float)rand()) / (float)RAND_MAX; }

// TIMERS /////////////////////////////////////////////////////////////////////////////////////////
//
timespec _timer_start;
void timer_start() { clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &_timer_start); }
float timer_elapsed()
{
    timespec t;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    // convert to ms
    float start_ms, stop_ms;
    start_ms = _timer_start.tv_sec * 1000.0f + _timer_start.tv_nsec * 1e-6;
    stop_ms = t.tv_sec * 1000.0f + t.tv_nsec * 1e-6;
    
    // restart timer, permitting subsequent calls to timer_elapsed to show dt between calls
    timer_start();

    return stop_ms - start_ms;

}

// PIXEL ACCESS ///////////////////////////////////////////////////////////////////////////////////
//
/* struct px_t 
 *
 * The format is designed to be compatible with PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 from raylib.
 * Used primarily for direct pixel acces through the use of a 2D texture loaded from an image. For
 * example:
 *
 *      // initialization
 * 
 *      px_t *pixels = (px_t *)malloc(win_dim.x * win_dim.y * sizeof(px_t));
 *      Image img = {
 *           .data = (void *)pixels,
 *           .width = win_dim.x,
 *           .height = win_dim.y,
 *           .mipmaps = 1,
 *           .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
 *      };
 *      
 *      Texture2D tex = LoadTextureFromImage(img);
 * 
 * 
 *      // updating and rendering
 * 
 *      [... pixel manipulations...]
 *      
 *      UpdateTexture(tex, (void *)pixels);
 *      DrawTexture(tex, 0, 0, WHITE);
 * 
 */ 
struct px_t {
    union {
        uint8_t rgba[4];
        uint32_t c;
    };
    px_t(char r, char g, char b, char a)
    {
        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
    }
    px_t(char r, char g, char b)
    {
        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = 255;
    }
    px_t(int c) : c(c) {}
};
#define PX_BLACK    px_t(0x000000FF)
#define PX_WHITE    px_t(0xFFFFFFFF)


/* CreatePixelBuffer
 * CreatePixelTexture
 * UpdatePixelTexture
 * DrawPixelTexture
 * ReleasePixelTexture
 *  
 * Utility globals and functions for setting up a pixel array for the window (1:1 resolution).
 */
px_t *_pixels_ptr = NULL;
Image *_img_ptr = NULL;
Texture2D *_tex_ptr = NULL;
int _win_width = 0;
int _win_height = 0;
#define PIXELS _pixels_ptr  // accessor; PIXELS[idx] = ...
#define PIXELS_SIZE (sizeof(px_t) * _win_width * _win_height)
//
void CreatePixelBuffer(int width, int height)
{ 
    _win_width  = width;
    _win_height = height;
    _pixels_ptr = (px_t *)malloc(width * height * sizeof(px_t));
}

//
void CreatePixelTexture(int width, int height)
{
    _img_ptr = (Image *)malloc(sizeof(Image));
    *_img_ptr = (Image){
        .data = (void *)_pixels_ptr,
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,        
    };

    _tex_ptr = (Texture2D *)malloc(sizeof(Texture2D));
    *_tex_ptr = LoadTextureFromImage(*_img_ptr);
}

//
void UpdatePixelTexture(px_t *__pixels_ptr=PIXELS) { UpdateTexture(*_tex_ptr, (void *)__pixels_ptr); }
// void UpdatePixelTexture() { UpdateTexture(*_tex_ptr, (void *)_pixels_ptr); }
    
//
void DrawPixelTexture() { DrawTexture(*_tex_ptr, 0, 0, WHITE); }

//
void ReleasePixelTexture()
{
    if (_pixels_ptr != NULL) free(_pixels_ptr);
    if (_img_ptr != NULL)    free(_img_ptr);
    if (_tex_ptr != NULL)    free(_tex_ptr);
}


// PHYSICS ////////////////////////////////////////////////////////////////////////////////////////
//
bool check_collisions_circles(const vec2 v0, float r0, const vec2 &v1, float r1)
{
    float dx = v1.x - v0.x;     // X distance between centers
    float dy = v1.y - v0.y;     // Y distance between centers

    float dst2 = dx*dx+dy*dy;   // Distance between centers squared
    float rr = r0+r1;

    return (dst2 <= (rr*rr));
}

// renders a vector v as a line from the origin o
void render_vector(vec2 v, vec2 o={0, 0}, float scale=1.0f, Color color=WHITE)
{
    vec2 v_ = v;
    if (scale != 1.0f)  v_ *= scale;
    DrawLineEx(vec2torlvec2(o), vec2torlvec2(o + v_), 1.0f, color);
}

// DEBUGGING FUNCTIONS ////////////////////////////////////////////////////////////////////////////
//






#endif


// PERFORMED TESTS //
/*    
    printf("\n\ntest _min: _min(%.1f, %.1f) = %.1f\n", a, b, _min(a, b));
    printf("test _max: _max(%.1f, %.1f) = %.1f\n", a, b, _max(a, b));
    printf("test _clamp(%.1f, %.1f, %.1f) = %.1f\n", a, lo, hi, _clamp(a, lo, hi));
    printf("test _clamp(%.1f, %.1f, %.1f) = %.1f\n", b, lo, hi, _clamp(b, lo, hi));
    //
    vec2 v(2.0f, 4.0f);
    vec2 o(2.0f, 4.0f);
    printf("----- vec2 ADDITION -----\n");
    v.print("v");
    printf("\n");
    v = v + o;
    v.print("v=v+[2,4]");
    v = vec2(2.0f, 4.0f);
    v += o;
    v.print("v+=[2,4]");
    v = vec2(2.0f, 4.0f);
    v = v + 2.0f;
    v.print("v=v+2.0");
    v = vec2(2.0f, 4.0f);
    v += 2.0f;
    v.print("v+=2.0");
    v = vec2(2.0f, 4.0f);
    printf("\n----- vec2 SUBTRACTION -----\n");
    v.print("v");
    printf("\n");
    v = v - o;
    v.print("v=v-[2,4]");
    v = vec2(2.0f, 4.0f);
    v -= o;
    v.print("v-=[2,4]");
    v = vec2(2.0f, 4.0f);
    v = v - 2.0f;
    v.print("v=v-2.0");
    v = vec2(2.0f, 4.0f);
    v -= 2.0f;
    v.print("v-=2.0");
    v = vec2(2.0f, 4.0f);
    printf("\n----- vec2 MULTIPLICATION -----\n");
    v.print("v");
    printf("\n");
    v = v * o;
    v.print("v=v*[2,4]");
    v = vec2(2.0f, 4.0f);
    v *= o;
    v.print("v*=[2,4]");
    v = vec2(2.0f, 4.0f);
    v = v * 2.0f;
    v.print("v=v*2.0");
    v = vec2(2.0f, 4.0f);
    v *= 2.0f;
    v.print("v*=2.0");
    v = vec2(2.0f, 4.0f);
    printf("\n----- vec2 DIVISION -----\n");
    v.print("v");
    printf("\n");
    v = v / o;
    v.print("v=v/[2,4]");
    v = vec2(2.0f, 4.0f);
    v /= o;
    v.print("v/=[2,4]");
    v = vec2(2.0f, 4.0f);
    v = v / 2.0f;
    v.print("v=v/2.0");
    v = vec2(2.0f, 4.0f);
    v /= 2.0f;
    v.print("v/=2.0");
    v = vec2(2.0f, 4.0f);
    printf("----- vec2 LEN AND DIST TESTS -----\n");
    vec2 v(3.0f, 4.0f);
    v.print();
    printf("v.len() = %.1f\n", v.len());
    printf("v.len2()= %.1f\n", v.len2());
    v.norm();
    v.print("v.norm()");
    printf("v.len() after .norm() = %.1f\n", v.len());
    v.setlen(5.0f);
    v.print("setlen(5.0)");
    vec2 a(3,1), b(6,5);
    printf("[3,1].dist[6,5] = %.1f\n", a.dist(b));
    assert(a.dist(b) == b.dist(a));
    printf("\n----- vec2 MIN/MAX TESTS -----\n");
    v = vec2(1.0f, 12.0f);
    v.print("v");
    v.setmin(3.0f);
    v.print("setmin(3.0)");
    v = vec2(1.0f, 12.0f);
    v.setmin(3.0f, 15.0f);
    v.print("setmin(3.0, 15.0)");
    v = vec2(1.0f, 12.0f);
    v.setminlen(20.0f);
    v.print("setminlen(20.0)");
    printf("v.len() = %.1f\n", v.len());
    v = vec2(1.0f, 12.0f);
    v.setmax(3.0f);
    v.print("setmax(3.0)");
    v = vec2(1.0f, 12.0f);
    v.setmax(0.0f, 7.0f);
    v.print("setmax(0.0, 7.0)");
    v = vec2(1.0f, 12.0f);
    v.setmaxlen(4.0f);
    v.print("setmaxlen(4.0)");
    printf("v.len() = %.1f\n", v.len());
    printf("\n----- vec2 CLAMP TESTS -----\n");
    v = vec2(3.0f, 10.0f);
    v.print();
    v.clamp(4.0f, 7.0f);
    v.print("clamp(4,7)");
    v = vec2(3.0f, 10.0f);
    v.clamp(4, 5, -10, -5);
    v.print("clamp(4,5,-10,-5)");
    v = vec2(3.0f, 10.0f);
    v.clamplen(7.0f, 9.0f);
    v.print("clamplen(7,9)");
    printf("v.len() = %.1f\n", v.len());
    printf("----- vec2 RAYLIB CONVERSION -----\n");
    vec2 v(3, 4);
    Vector2 vrl= v.to_rlvec2();
    printf("vrl = [ %.1f  %.1f ]\n", vrl.x, vrl.y);
    printf("----- vec2 VECTOR PRODUCTS AND ANGLES -----\n");
    vec2 a(2, 1), b(-3, 2);
    a.print("a");
    b.print("b");
    printf("a.cross(b) = %.1f (7.0?)\n", a.cross(b));
    printf("a.dot(b) = %.1f (-4.0?)\n", a.dot(b));
    printf("a.theta(b) = %.4f (-0.4961)\n", a.theta(b));
    printf("a.angle(b) = %.2f (2.09)\n", a.angle(b));



*/
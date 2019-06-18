/*
 * Copyright 2018 (c), Bruce Davidson.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */
#ifndef _GLM_H_
#define _GLM_H_
/**
 * Vector/Matrix types for use with Vala
 */
#include "cglm/cglm.h"

/*
** Vec2 - x, y
*/
typedef struct Vec2 Vec2;
struct Vec2
{
    union {
        vec2 data;      /* the opaque typedef from cglm */
        struct {
            float x;    /* x coordinate */
            float y;    /* y coordinate */
        };
        struct {
            float X;    /* x coordinate */
            float Y;    /* y coordinate */
        };
    };
    int ref_count;      /* vala compact class reference counter */
};

typedef struct Vec3 Vec3;
struct Vec3
{
    union {
        vec3 data;
        struct {
            float x;
            float y;
            float z;
        };
        struct {
            float X;
            float Y;
            float Z;
        };
    };
    int ref_count;
};


typedef struct Vec4 Vec4;
struct Vec4
{
    union {
        vec4 data;
        struct {
            float w;
            float x;
            float y;
            float z;
        };
        struct {
            float W;
            float X;
            float Y;
            float Z;
        };
    };
    int ref_count;
};

typedef struct Quat Quat;
struct Quat 
{
    union {
        vec4 data;
        struct {
            float w;
            float x;
            float y;
            float z;
        };
        struct {
            float W;
            float X;
            float Y;
            float Z;
        };
    };
    int ref_count;
};

typedef struct Mat3 Mat3;
struct Mat3 
{
    union {
        mat3 data;    
        struct {
            float M11;
            float M12;
            float M13;
            float M21;
            float M22;
            float M23;
            float M31;
            float M32;
            float M33;
        };
    };
    int ref_count;
};

typedef struct Mat4 Mat4;
struct Mat4
{
    union {
        mat4 data;    
        struct {
            float M11;
            float M12;
            float M13;
            float M14;   
            float M21;
            float M22;
            float M23;
            float M24;   
            float M31;
            float M32;
            float M33;
            float M34;   
            float M41;
            float M42;
            float M43;
            float M44;   
        };
    };
    int ref_count;
};



/**
 * Api extension
 */
Vec2* glm_vec2_new(float x, float y);
Vec2* glm_vec2_ref(Vec2* this);
void  glm_vec2_unref(Vec2* this);
int   glm_vec2_hash(Vec2* this);
bool  glm_vec2_equals(Vec2* this, Vec2* other);
void  glm_vec2_sub(Vec2* this, Vec2* other, Vec2* dest);
void  glm_vec2_scale(Vec2* this, float scale, Vec2* dest);
float glm_vec2_len(Vec2* this);
float glm_vec2_len2(Vec2* this);
void  glm_vec2_normalize(Vec2* this);


Vec3* glm_vec3_new(float x, float y, float z);
Vec3* glm_vec3_ref(Vec3* this);
void  glm_vec3_unref(Vec3* this);
int   glm_vec3_hash(Vec3* this);
bool  glm_vec3_equals(Vec3* this, Vec3* other);

Vec4* glm_vec4_new(float w, float x, float y, float z);
Vec4* glm_vec4_ref(Vec4* this);
void  glm_vec4_unref(Vec4* this);

Quat* glm_quat_new();
Quat* glm_quat_ref(Quat* this);
void  glm_quat_unref(Quat* this);

Mat3* glm_mat3_new(float value);
Mat3* glm_mat3_ref(Mat3* this);
void  glm_mat3_unref(Mat3* this);

Mat4* glm_mat4_new(float value);
Mat4* glm_mat4_ref(Mat4* this);
void  glm_mat4_unref(Mat4* this);

#endif // _GLM_H_

/*
 * Copyright (c) 2018 Bruce Davidspn <darkoverlordofdata@gmail.com>

The MIT License (MIT)


Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
[Version (since = "0.4.9")] // cglm v0.4.9
[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "glm.h")]
namespace Glm
{
	/**
	 * bindings for cglm
	 * 
	 * 
	 */
	public const int CGLM_VERSION_MAJOR;
	public const int CGLM_VERSION_MINOR;
	public const int CGLM_VERSION_PATCH;


	/**
	 * Vec2
	 */
	[Compact, CCode (ref_function = "glm_vec2_ref", unref_function = "glm_vec2_unref")]
	public class Vec2 
	{ 
		public float X; // same as data[0]
		public float Y; // same as data[1]
		public float data[2];

		[CCode (cname = "glm_vec2_new")]
		public Vec2(float x = 0f, float y = 0f);
		[CCode (cname = "glm_vec2_print")]
		public void Print(GLib.FileStream ostream = GLib.stdout);
		[CCode (cname = "glm_vec2_hash")]
		public int GetHashCode();
		[CCode (cname = "glm_vec2_equals")]
		public bool Equals(Vec2 other);
		[CCode (cname = "glm_vec2_len2")]
		public float LengthSquared();
		[CCode (cname = "glm_vec2_len")]
		public float Length();

		public Vec2 Sub(Vec2 other)
		{
			glm_vec2_sub(this, other, this);
			return this;
		}

		public Vec2 Mul(Vec2 other)
		{
			glm_vec2_mul(this, other, this);
			return this;
		}

		public Vec2 Multiply(float f)
		{
			glm_vec2_scale(this, f, this);
			return this;
		}

		public Vec2 Normalize()
		{
			glm_vec2_normalize(this);
			return this;
		}

		public string to_string()
		{
			return @"{X:$X, Y:$Y}";
		}

	}
	
	/**
	 * Vec3
	 */
	[Compact, CCode (ref_function = "glm_vec3_ref", unref_function = "glm_vec3_unref")]
	public class Vec3 
	{ 
		public float X; // same as data[0]
		public float Y; // same as data[1]
		public float Z; // same as data[2]
		public float data[3];

		[CCode (cname = "glm_vec3_new")]
		public Vec3(float x = 0f, float y = 0f, float z = 0f);

		public Vec3.FromVec4(Vec4 value)
		{
			glm_vec3(value, this);
		}
		[CCode (cname = "glm_vec3_print")]
		public void Print(GLib.FileStream ostream = GLib.stdout);
		[CCode (cname = "glm_vec3_hash")]
		public int GetHashCode();
		[CCode (cname = "glm_vec3_equals")]
		public bool Equals(Vec3 other);

		public string to_string()
		{
			return @"{X:$X, Y:$Y, Z:$Z}";
		}

	}

	/**
	 * Vec4
	 */
	[Compact, CCode (ref_function = "glm_vec4_ref", unref_function = "glm_vec4_unref")]
	public class Vec4 
	{ 
		public float W; // same as data[0]
		public float X; // same as data[1]
		public float Y; // same as data[2]
		public float Z; // same as data[3]
		public float data[4];

		[CCode (cname = "glm_vec4_new")]
		public Vec4(float w = 0f, float x = 0f, float y = 0f, float z = 0f);

		public Vec4.FromVec3(Vec3 value, float last)
		{
			glm_vec4(value, last, this);
		}
		[CCode (cname = "glm_vec4_print")]
		public void Print(GLib.FileStream ostream = GLib.stdout);
	}

	/**
	 * Quat
	 */
	[Compact, CCode (ref_function = "glm_quat_ref", unref_function = "glm_quat_unref")]
	public class Quat 
	{ 
		public float W; // same as data[0]
		public float X; // same as data[1]
		public float Y; // same as data[2]
		public float Z; // same as data[3]
		public float data[4];

		[CCode (cname = "glm_quat_new")]
		public Quat();
		[CCode (cname = "glm_quat_print")]
		public void Print(GLib.FileStream ostream = GLib.stdout);
	}

	/**
	 * Mat3
	 */
	[Compact, CCode (ref_function = "glm_mat3_ref", unref_function = "glm_mat3_unref")]
	public class Mat3 
	{ 
		public float M11;
		public float M12;
		public float M13;
		public float M21;
		public float M22;
		public float M23;
		public float M31;
		public float M32;
		public float M33;
		public float[] data[3];

		[CCode (cname = "glm_mat3_new")]
		public Mat3(float value = 1f);
		[CCode (cname = "glm_mat3_print")]
		public void Print(GLib.FileStream ostream = GLib.stdout);

	}

	/**
	 * Mat4
	 */
	[Compact, CCode (ref_function = "glm_mat4_ref", unref_function = "glm_mat4_unref")]
	public class Mat4 
	{ 
		public float M11;
		public float M12;
		public float M13;
		public float M14;
		public float M21;
		public float M22;
		public float M23;
		public float M24;
		public float M31;
		public float M32;
		public float M33;
		public float M34;
		public float M41;
		public float M42;
		public float M43;
		public float M44;

		public float[] data[4];

		[CCode (cname = "glm_mat4_new")]
		public Mat4(float value = 1f);
		[CCode (cname = "glm_mat4_print")]
		public void Print(GLib.FileStream ostream = GLib.stdout);

		public Mat4 Multiply(Mat4 other)
		{
			glm_mat4_mul(this, other, this);
			return this;
		}
		public Mat4 Invert()
		{
			glm_mat4_inv(this, this);
			return this;
		}
	}

	public void  glm_cross(Vec3 a, Vec3 b, Vec3 d);
	public float glm_dot(Vec3 a, Vec3 b);
	public void  glm_normalize(Vec3 v);
	public void  glm_normalize_to(Vec3 v, Vec3 dest);
	public int 	 glm_sign(int val);
	public float glm_signf(float val);
	public float glm_rad(float deg);
	public float glm_deg(float rad);
	public void  glm_make_rad(float* deg);
	public void  glm_make_deg(float* rad);
	public float glm_pow2(float X);
	public float glm_min(float a, float b);
	public float glm_max(float a, float b);
	public float glm_clamp(float val, float minVal, float maxVal);
	public float glm_clamp_to(float val);
	public float glm_lerp(float from, float to, float t);
	public bool  glm_eq(float a, float b);
	public float glm_percent(float from, float to, float current);
	public float glm_percentc(float from, float to, float current);
	public float glm_quatv(Quat q, float angle, Vec3 axis);
	public float glm_unprojecti(Vec3 pos, Mat4 invMat, Vec4 vp, Vec3 dest);
	public float glm_unproject(Vec3 pos, Mat4 m, Vec4 vp, Vec3 dest);
	public float glm_project(Vec3 pos, Mat4 m, Vec4 vp, Vec3 dest);
	public void  glm_translate(Mat4 m, Vec3 v);
	public void  glm_translate_to(Mat4 m, Vec3 v, Mat4 dest);
	public void  glm_translate_x(Mat4 m, float x);
	public void  glm_translate_y(Mat4 m, float y);
	public void  glm_translate_z(Mat4 m, float z);
	public void  glm_translate_make(Mat4 m, Vec3 v);
	public void  glm_scale_to(Mat4 m, Vec3 v, Mat4 dest);
	public void  glm_scale_make(Mat4 m, Vec3 v);
	public void  glm_scale(Mat4 m, Vec3 v);
	public void  glm_scale_uni(Mat4 m, float s);
	public void  glm_rotate_x(Mat4 m, float angle, Mat4 dest);
	public void  glm_rotate_y(Mat4 m, float angle, Mat4 dest);
	public void  glm_rotate_z(Mat4 m, float angle, Mat4 dest);
	public void  glm_rotate_make(Mat4 m, float angle, Vec3 axis);
	public void  glm_rotate(Mat4 m, float angle, Vec3 axis);
	public void  glm_rotate_at(Mat4 m, Vec3 pivot, float angle, Vec3 axis);
	public void  glm_rotate_atm(Mat4 m, Vec3 pivot, float angle, Vec3 axis);
	public void  glm_decompose_scalev(float* m, float* s);
	public bool  glm_uniscaled(Mat4 m, Vec3 s);
	public void  glm_decompose_rs(Mat4 m, Mat4 r, Vec3 s);	
	public void  glm_decompose(Mat4 m, Mat4 t, Mat4 r, Vec3 s);
	public void  glm_perspective(float fovy, float aspect, float nearVal, float farVal, Mat4 dest);
	public void  glm_lookat(Vec3 eye, Vec3 center, Vec3 up, Mat4 dest);

	public void  glm_mat3_print(Mat3 matrix, GLib.FileStream ostream);
	public void  glm_mat3_identity(Mat3 mat);
	public void  glm_mat3_mul(Mat3 m1, Mat3 m2, Mat3 dest);
	public void  glm_mat3_transpose_to(Mat3 m, Mat3 dest);
	public void  glm_mat3_transpose(Mat3 m);
	public void  glm_mat3_mulv(Mat3 m, Vec3 v, Vec3 dest);
	public void  glm_mat3_quat(Mat3 m, Quat dest);
	public void  glm_mat3_scale(Mat3 m, float s);
	public float glm_mat3_det(Mat3 m);
	public void  glm_mat3_inv(Mat3 mat, Mat3 dest);
	public void  glm_mat3_swap_col(Mat3 mat, int col1, int col2);
	public void  glm_mat3_swap_row(Mat3 mat, int row1, int row2);

	public void  glm_mat4_print(Mat4 matrix, GLib.FileStream ostream);
	public void  glm_mat4_identity(Mat4 mat);
	public void  glm_mat4_pick3(Mat4 mat, Mat3 dest);
	public void  glm_mat4_pick3t(Mat4 mat, Mat3 dest);
	public void  glm_mat4_ins3(Mat3 mat, Mat4 dest);
	public void  glm_mat4_mul(Mat4 m1, Mat4 m2, Mat4 dest);
	public void  glm_mat4_mulN(Mat4 matrices, uint len, Mat4 dest);
	public void  glm_mat4_mulv(Mat4 m, Vec4 v, Vec4 dest);
	public void  glm_mat4_quat(Mat4 m, Quat dest);
	public void  glm_mat4_mulv3(Mat4 m, Vec3 v, float last, Vec3 dest);
	public void  glm_mat4_transpose_to(Mat4 m, Mat4 dest);
	public void  glm_mat4_transpose(Mat4 m);
	public void  glm_mat4_scale_p(Mat4 m, float s);
	public void  glm_mat4_scale(Mat4 m, float s);
	public float glm_mat4_det(Mat4 m);
	public void  glm_mat4_inv(Mat4 mat, Mat4 dest);
	public void  glm_mat4_inv_fast(Mat4 mat, Mat4 dest);
	public void  glm_mat4_swap_col(Mat4 mat, int col1, int col2);
	public void  glm_mat4_swap_row(Mat4 mat, int row1, int row2);


	public void  glm_quat(Quat q, float angle, float x, float y, float z);
	public void  glm_versor_print(Quat versor, GLib.FileStream ostream);
	public void  glm_quat_identity(Quat q);
	public void  glm_quat_identity_array(Quat q, size_t count);
	public void  glm_quat_init(Quat q, float x, float y, float z, float w);
	public float glm_quat_norm(Quat q);
	public void  glm_quat_normalize_to(Quat q, Quat dest);
	public void  glm_quat_normalize(Quat q);
	public float glm_quat_dot(Quat p, Quat q);
	public void  glm_quat_conjugate(Quat q, Quat dest);
	public void  glm_quat_inv(Quat q, Quat dest);
	public void  glm_quat_add(Quat p, Quat q, Quat dest);
	public void  glm_quat_sub(Quat p, Quat q, Quat dest);
	public float glm_quat_real(Quat q);
	public void  glm_quat_imag(Quat q, Vec3 dest);
	public void  glm_quat_imagn(Quat q, Vec3 dest);
	public float glm_quat_imagnlen(Quat q);
	public float glm_quat_angle(Quat q);
	public void  glm_quat_axis(Quat q, Quat dest);
	public void  glm_quat_mul(Quat p, Quat q, Quat dest);
	public void  glm_quat_mat4(Quat q, Mat4 dest);
	public void  glm_quat_mat4t(Quat q, Mat4 dest);
	public void  glm_quat_mat3(Quat q, Mat3 dest);
	public void  glm_quat_mat3t(Quat q, Mat3 dest);
	public void  glm_quat_lerp(Quat from, Quat to, float t, Quat dest);
	public void  glm_quat_slerp(Quat from, Quat to, float t, Quat dest);
	public void  glm_quat_look(Quat eye, Quat ori, Quat dest);
	public void  glm_quat_for(Quat dir, Quat fwd, Quat up, Quat dest);
	public void  glm_quat_forp(Quat from, Quat to, Quat fwd, Quat up, Quat dest);
	public void  glm_quat_rotatev(Quat q, Quat v, Quat dest);
	public void  glm_quat_rotate(Mat4 m, Quat q, Mat4 dest);
	public void  glm_quat_rotate_at(Mat4 m, Quat q, Vec3 pivot);
	public void  glm_quat_rotate_atm(Mat4 m, Quat q, Vec3 pivot);

	public void  glm_vec2_sub(Vec2 a, Vec2 b, Vec2 dest);
	public void  glm_vec2_scale(Vec2 a, float f, Vec2 dest);
	public float glm_vec2_len(Vec2 a);
	public float glm_vec2_len2(Vec2 a);
	public void  glm_vec2_normalize(Vec2 a);
	public void  glm_vec2_mul(Vec2 a, Vec2 b, Vec2 dest);

	public void  glm_vec3(Vec4 v4, Vec3 dest);
	public void  glm_vec3_print(Vec3 vec, GLib.FileStream ostream);
	public void  glm_vec_copy(Vec3 src, Vec3 dest);
	public void  glm_vec_zero(Vec3 v);
	public void  glm_vec_one(Vec3 v);
	public float glm_vec_dot(Vec3 a, Vec3 b);
	public void  glm_vec_cross(Vec3 a, Vec3 b, Vec3 d);
	public float glm_vec_norm2(Vec3 v);
	public float glm_vec_norm(Vec3 v);
	public void  glm_vec_add(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_adds(Vec3 v, float s, Vec3 dest);
	public void  glm_vec_sub(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_subs(Vec3 v, float s, Vec3 dest);
	public void  glm_vec_mul(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_scale(Vec3 v, float s, Vec3 dest);
	public void  glm_vec_scale_as(Vec3 v, float s, Vec3 dest);
	public void  glm_vec_div(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_divs(Vec3 v, float s, Vec3 dest);
	public void  glm_vec_addadd(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_subadd(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_muladd(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_muladds(Vec3 a, float s, Vec3 dest);
	public void  glm_vec_flipsign(Vec3 v);
	public void  glm_vec_flipsign_to(Vec3 v, Vec3 dest);
	public void  glm_vec_inv(Vec3 v);
	public void  glm_vec_normalize(Vec3 v);
	public void  glm_vec_normalize_to(Vec3 v, Vec3 dest);
	public float glm_vec_angle(Vec3 v1, Vec3 v2);
	public void  glm_vec_rotate(Vec3 v, float angle, Vec3 axis);
	public void  glm_vec_rotate_m4(Mat4 m, float v, Vec3 dest);
	public void  glm_vec_rotate_m3(Mat3 m, float v, Vec3 dest);
	public void  glm_vec_proj(Vec3 a, Vec3 b, Vec3 dest);
	public void  glm_vec_center(Vec3 v1, Vec3 v2, Vec3 dest);
	public float glm_vec_distance2(Vec3 v1, Vec3 v2);
	public float glm_vec_distance(Vec3 v1, Vec3 v2);
	public void  glm_vec_maxv(Vec3 v1, Vec3 v2, Vec3 dest);
	public void  glm_vec_minv(Vec3 v1, Vec3 v2, Vec3 dest);
	public void  glm_vec_ortho(Vec3 v, Vec3 dest);
	public void  glm_vec_clamp(Vec3 v, float minVal, float maxVal);
	public void  glm_vec_mulv(Vec3 a, Vec3 b, Vec3 d);
	public void  glm_vec_broadcast(float val, Vec3 d);
	public bool  glm_vec_eq(Vec3 v, float val);
	public bool  glm_vec_eq_eps(Vec3 v, float val);
	public bool  glm_vec_eq_all(Vec3 v);
	public bool  glm_vec_eqv(Vec3 v1, Vec3 v2);
	public bool  glm_vec_eqv_eps(Vec3 v1, Vec3 v2);
	public float glm_vec_max(Vec3 v);
	public float glm_vec_min(Vec3 v);
	public bool  glm_vec_isnan(Vec3 v);
	public bool  glm_vec_isinf(Vec3 v);
	public bool  glm_vec_isvalid(Vec3 v);
	public void  glm_vec_sign(Vec3 v, Vec3 dest);
	public void  glm_vec_sqrt(Vec3 v, Vec3 dest);

	public void  glm_vec4(Vec3 v3, float last, Vec4 dest);
	public void  glm_vec4_print(Vec4 vec, GLib.FileStream ostream);
	public void  glm_vec4_copy3(Vec4 a, Vec3 dest);
	public void  glm_vec4_ucopy(Vec4 a, Vec4 dest);
	public void  glm_vec4_zero(Vec4 v);
	public void  glm_vec4_one(Vec4 v);
	public float glm_vec4_dot(Vec4 a, Vec4 b);
	public float glm_vec4_norm2(Vec4 v);
	public void  glm_vec4_norm(Vec4 v);
	public void  glm_vec4_add(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_adds(Vec4 v, float s, Vec4 dest);
	public void  glm_vec4_sub(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_subs(Vec4 v, float s, Vec4 dest);
	public void  glm_vec4_mul(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_scale(Vec4 v, float s, Vec4 dest);
	public void  glm_vec4_scale_as(Vec4 v, float s, Vec4 dest);
	public void  glm_vec4_div(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_divs(Vec4 v, float s, Vec4 dest);
	public void  glm_vec4_addadd(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_subadd(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_muladd(Vec4 a, Vec4 b, Vec4 dest);
	public void  glm_vec4_muladds(Vec4 v, float s, Vec4 dest);
	public void  glm_vec4_flipsign(Vec4 v);
	public void  glm_vec4_flipsign_to(Vec4 v, Vec4 dest);
	public void  glm_vec4_inv(Vec4 v);
	public void  glm_vec4_inv_to(Vec4 v, Vec4 dest);
	public void  glm_vec4_normalize_to(Vec4 vec, Vec4 dest);
	public void  glm_vec4_normalize(Vec4 v);
	public float glm_vec4_distance(Vec4 v1, Vec4 v2);
	public void  glm_vec4_maxv(Vec4 v1, Vec4 v2, Vec4 dest);
	public void  glm_vec4_minv(Vec4 v1, Vec4 v2, Vec4 dest);
	public void  glm_vec4_clamp(Vec4 v, float minVal, float maxVal);
	public void  glm_vec4_lerp(Vec4 from, Vec4 to, float t, Vec4 dest);
	public void  glm_vec4_broadcast(float val, Vec4 d);
	public bool  glm_vec4_eq(Vec4 v, float val);
	public bool  glm_vec4_eq_eps(Vec4 v, float val);
	public bool  glm_vec4_eq_all(Vec4 v);
	public bool  glm_vec4_eqv(Vec4 v1, Vec4 v2);
	public bool  glm_vec4_eqv_eps(Vec4 v1, Vec4 v2);
	public float glm_vec4_max(Vec4 v);
	public float glm_vec4_min(Vec4 v);
	public bool  glm_vec4_isnan(Vec4 v);
	public bool  glm_vec4_isinf(Vec4 v);
	public bool  glm_vec4_isvalid(Vec4 v);
	public void  glm_vec4_sign(Vec4 v, Vec4 dest);
	public void  glm_vec4_sqrt(Vec4 v, Vec4 dest);

	//------------------------------------------------------------------
	[CCode (cname = "glm_translate")]
	public void  glm_translatef(Mat4 m, 
		[CCode (array_length = false)]float[] v);

	[CCode (cname = "glm_rotate")]
	public void  glm_rotatef(Mat4 m, float angle, 
		[CCode (array_length = false)]float[] axis);


	[CCode (cname = "glm_vec_copy")]
	public void  glm_vec_copyf(float* src, Vec3 dest);

	
}
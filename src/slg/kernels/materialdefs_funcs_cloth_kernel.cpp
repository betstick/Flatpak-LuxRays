#include <string>
namespace slg { namespace ocl {
std::string KernelSource_materialdefs_funcs_cloth = 
"#line 2 \"materialdefs_funcs_cloth.cl\"\n"
"\n"
"/***************************************************************************\n"
" * Copyright 1998-2017 by authors (see AUTHORS.txt)                        *\n"
" *                                                                         *\n"
" *   This file is part of LuxRender.                                       *\n"
" *                                                                         *\n"
" * Licensed under the Apache License, Version 2.0 (the \"License\");         *\n"
" * you may not use this file except in compliance with the License.        *\n"
" * You may obtain a copy of the License at                                 *\n"
" *                                                                         *\n"
" *     http://www.apache.org/licenses/LICENSE-2.0                          *\n"
" *                                                                         *\n"
" * Unless required by applicable law or agreed to in writing, software     *\n"
" * distributed under the License is distributed on an \"AS IS\" BASIS,       *\n"
" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*\n"
" * See the License for the specific language governing permissions and     *\n"
" * limitations under the License.                                          *\n"
" ***************************************************************************/\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// Cloth material\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined (PARAM_ENABLE_MAT_CLOTH)\n"
"\n"
"BSDFEvent ClothMaterial_GetEventTypes() {\n"
"	return GLOSSY | REFLECT;\n"
"}\n"
"\n"
"__constant WeaveConfig ClothWeaves[] = {\n"
"    // DenimWeave\n"
"    {\n"
"        3, 6,\n"
"        0.01f, 4.0f,\n"
"        0.0f, 0.5f,\n"
"        5.0f, 1.0f, 3.0f,\n"
"        0.0f, 0.0f, 0.0f, 0.0f,\n"
"        0.0f\n"
"    },\n"
"    // SilkShantungWeave\n"
"    {\n"
"        6, 8,\n"
"        0.02f, 1.5f,\n"
"        0.5f, 0.5f, \n"
"        8.0f, 16.0f, 0.0f,\n"
"        20.0f, 20.0f, 10.0f, 10.0f,\n"
"        500.0f\n"
"    },\n"
"    // SilkCharmeuseWeave\n"
"    {\n"
"        5, 10,\n"
"        0.02f, 7.3f,\n"
"        0.5f, 0.5f, \n"
"        9.0f, 1.0f, 3.0f,\n"
"        0.0f, 0.0f, 0.0f, 0.0f,\n"
"        0.0f\n"
"    },\n"
"    // CottonTwillWeave\n"
"    {\n"
"        4, 8,\n"
"        0.01f, 4.0f,\n"
"        0.0f, 0.5f, \n"
"        6.0f, 2.0f, 4.0f,\n"
"        0.0f, 0.0f, 0.0f, 0.0f,\n"
"        0.0f\n"
"    },\n"
"    // WoolGarbardineWeave\n"
"    {\n"
"        6, 9,\n"
"        0.01f, 4.0f,\n"
"        0.0f, 0.5f, \n"
"        12.0f, 6.0f, 0.0f,\n"
"        0.0f, 0.0f, 0.0f, 0.0f,\n"
"        0.0f\n"
"    },\n"
"    // PolyesterWeave\n"
"    {\n"
"        2, 2,\n"
"        0.015f, 4.0f,\n"
"        0.5f, 0.5f,\n"
"        1.0f, 1.0f, 0.0f, \n"
"        8.0f, 8.0f, 6.0f, 6.0f,\n"
"        50.0f\n"
"    }\n"
"};\n"
"\n"
"__constant Yarn ClothYarns[][14] = {\n"
"    // DenimYarn[8]\n"
"    {\n"
"        {-30, 12, 0, 1, 5, 0.1667f, 0.75f, WARP},\n"
"        {-30, 12, 0, 1, 5, 0.1667f, -0.25f, WARP},\n"
"        {-30, 12, 0, 1, 5, 0.5f, 1.0833f, WARP},\n"
"        {-30, 12, 0, 1, 5, 0.5f, 0.0833f, WARP},\n"
"        {-30, 12, 0, 1, 5, 0.8333f, 0.4167f, WARP},\n"
"        {-30, 38, 0, 1, 1, 0.1667f, 0.25f, WEFT},\n"
"        {-30, 38, 0, 1, 1, 0.5f, 0.5833f, WEFT},\n"
"        {-30, 38, 0, 1, 1, 0.8333f, 0.9167f, WEFT}\n"
"    },\n"
"    // SilkShantungYarn[5]\n"
"    {\n"
"        {0, 50, -0.5, 2, 4,  0.3333f, 0.25f, WARP},\n"
"        {0, 50, -0.5, 2, 4,  0.8333f, 0.75f, WARP},\n"
"        {0, 23, -0.3, 4, 4,  0.3333f, 0.75f, WEFT},\n"
"        {0, 23, -0.3, 4, 4, -0.1667f, 0.25f, WEFT},\n"
"        {0, 23, -0.3, 4, 4,  0.8333f, 0.25f, WEFT}\n"
"    },\n"
"    // SilkCharmeuseYarn[14]\n"
"    {\n"
"        {0, 40, 2, 1, 9, 0.1, 0.45, WARP},\n"
"        {0, 40, 2, 1, 9, 0.3, 1.05, WARP},\n"
"        {0, 40, 2, 1, 9, 0.3, 0.05, WARP},\n"
"        {0, 40, 2, 1, 9, 0.5, 0.65, WARP},\n"
"        {0, 40, 2, 1, 9, 0.5, -0.35, WARP},\n"
"        {0, 40, 2, 1, 9, 0.7, 1.25, WARP},\n"
"        {0, 40, 2, 1, 9, 0.7, 0.25, WARP},\n"
"        {0, 40, 2, 1, 9, 0.9, 0.85, WARP},\n"
"        {0, 40, 2, 1, 9, 0.9, -0.15, WARP},\n"
"        {0, 60, 0, 1, 1, 0.1, 0.95, WEFT},\n"
"        {0, 60, 0, 1, 1, 0.3, 0.55, WEFT},\n"
"        {0, 60, 0, 1, 1, 0.5, 0.15, WEFT},\n"
"        {0, 60, 0, 1, 1, 0.7, 0.75, WEFT},\n"
"        {0, 60, 0, 1, 1, 0.9, 0.35, WEFT}\n"
"    },\n"
"    // CottonTwillYarn[10]\n"
"    {\n"
"        {-30, 24, 0, 1, 6, 0.125,  0.375, WARP},\n"
"        {-30, 24, 0, 1, 6, 0.375,  1.125, WARP},\n"
"        {-30, 24, 0, 1, 6, 0.375,  0.125, WARP},\n"
"        {-30, 24, 0, 1, 6, 0.625,  0.875, WARP},\n"
"        {-30, 24, 0, 1, 6, 0.625, -0.125, WARP},\n"
"        {-30, 24, 0, 1, 6, 0.875,  0.625, WARP},\n"
"        {-30, 36, 0, 2, 1, 0.125,  0.875, WEFT},\n"
"        {-30, 36, 0, 2, 1, 0.375,  0.625, WEFT},\n"
"        {-30, 36, 0, 2, 1, 0.625,  0.375, WEFT},\n"
"        {-30, 36, 0, 2, 1, 0.875,  0.125, WEFT}\n"
"    },\n"
"    // WoolGarbardineYarn[7]\n"
"    {\n"
"        {30, 30, 0, 2, 6, 0.167, 0.667, WARP},\n"
"        {30, 30, 0, 2, 6, 0.500, 1.000, WARP},\n"
"        {30, 30, 0, 2, 6, 0.500, 0.000, WARP},\n"
"        {30, 30, 0, 2, 6, 0.833, 0.333, WARP},\n"
"        {30, 30, 0, 3, 2, 0.167, 0.167, WEFT},\n"
"        {30, 30, 0, 3, 2, 0.500, 0.500, WEFT},\n"
"        {30, 30, 0, 3, 2, 0.833, 0.833, WEFT}\n"
"    },\n"
"    // PolyesterYarn[4]\n"
"    {\n"
"        {0, 22, -0.7, 1, 1, 0.25, 0.25, WARP},\n"
"        {0, 22, -0.7, 1, 1, 0.75, 0.75, WARP},\n"
"        {0, 16, -0.7, 1, 1, 0.25, 0.75, WEFT},\n"
"        {0, 16, -0.7, 1, 1, 0.75, 0.25, WEFT}\n"
"    }\n"
"};\n"
"\n"
"__constant int ClothPatterns[][6 * 9] = {\n"
"    // DenimPattern[3 * 6]\n"
"    {\n"
"        1, 3, 8,  1, 3, 5,  1, 7, 5,  1, 4, 5,  6, 4, 5,  2, 4, 5\n"
"    },\n"
"    // SilkShantungPattern[6 * 8]\n"
"    {\n"
"        3, 3, 3, 3, 2, 2,  3, 3, 3, 3, 2, 2,  3, 3, 3, 3, 2, 2,  3, 3, 3, 3, 2, 2,\n"
"        4, 1, 1, 5, 5, 5,  4, 1, 1, 5, 5, 5,  4, 1, 1, 5, 5, 5,  4, 1, 1, 5, 5, 5\n"
"    },\n"
"    // SilkCharmeusePattern[5 * 10]\n"
"    {\n"
"        10, 2, 4, 6, 8,   1, 2, 4, 6,  8,  1, 2, 4, 13, 8,  1, 2,  4, 7, 8,  1, 11, 4, 7, 8,\n"
"        1, 3, 4, 7, 8,   1, 3, 4, 7, 14,  1, 3, 4,  7, 9,  1, 3, 12, 7, 9,  1,  3, 5, 7, 9\n"
"    },\n"
"    // CottonTwillPattern[4 * 8]\n"
"    {\n"
"        7, 2, 4, 6,  7, 2, 4, 6,  1, 8, 4,  6,  1, 8, 4,  6,\n"
"        1, 3, 9, 6,  1, 3, 9, 6,  1, 3, 5, 10,  1, 3, 5, 10\n"
"    },\n"
"    // WoolGarbardinePattern[6 * 9]\n"
"    {\n"
"        1, 1, 2, 2, 7, 7,  1, 1, 2, 2, 7, 7,  1, 1, 2, 2, 7, 7,\n"
"        1, 1, 6, 6, 4, 4,  1, 1, 6, 6, 4, 4,  1, 1, 6, 6, 4, 4,\n"
"        5, 5, 3, 3, 4, 4,  5, 5, 3, 3, 4, 4,  5, 5, 3, 3, 4, 4\n"
"    },\n"
"    // PolyesterPattern[2 * 2]\n"
"    {\n"
"        3, 2, 1, 4\n"
"    }\n"
"};\n"
"\n"
"ulong sampleTEA(uint v0, uint v1, uint rounds) {\n"
"	uint sum = 0;\n"
"\n"
"	for (uint i = 0; i < rounds; ++i) {\n"
"		sum += 0x9e3779b9;\n"
"		v0 += ((v1 << 4) + 0xA341316C) ^ (v1 + sum) ^ ((v1 >> 5) + 0xC8013EA4);\n"
"		v1 += ((v0 << 4) + 0xAD90777D) ^ (v0 + sum) ^ ((v0 >> 5) + 0x7E95761E);\n"
"	}\n"
"\n"
"	return ((ulong) v1 << 32) + v0;\n"
"}\n"
"\n"
"float sampleTEAfloat(uint v0, uint v1, uint rounds) {\n"
"	/* Trick from MTGP: generate an uniformly distributed\n"
"	   single precision number in [1,2) and subtract 1. */\n"
"	union {\n"
"		uint u;\n"
"		float f;\n"
"	} x;\n"
"	x.u = ((sampleTEA(v0, v1, rounds) & 0xFFFFFFFF) >> 9) | 0x3f800000UL;\n"
"	return x.f - 1.0f;\n"
"}\n"
"\n"
"// von Mises Distribution\n"
"float vonMises(float cos_x, float b) {\n"
"	// assumes a = 0, b > 0 is a concentration parameter.\n"
"\n"
"	const float factor = exp(b * cos_x) * (.5f * M_1_PI_F);\n"
"	const float absB = fabs(b);\n"
"	if (absB <= 3.75f) {\n"
"		const float t0 = absB / 3.75f;\n"
"		const float t = t0 * t0;\n"
"		return factor / (1.0f + t * (3.5156229f + t * (3.0899424f +\n"
"			t * (1.2067492f + t * (0.2659732f + t * (0.0360768f +\n"
"			t * 0.0045813f))))));\n"
"	} else {\n"
"		const float t = 3.75f / absB;\n"
"		return factor * sqrt(absB) / (exp(absB) * (0.39894228f +\n"
"			t * (0.01328592f + t * (0.00225319f +\n"
"			t * (-0.00157565f + t * (0.00916281f +\n"
"			t * (-0.02057706f + t * (0.02635537f +\n"
"			t * (-0.01647633f + t * 0.00392377f)))))))));\n"
"	}\n"
"}\n"
"\n"
"// Attenuation term\n"
"float seeliger(float cos_th1, float cos_th2, float sg_a, float sg_s) {\n"
"	const float al = sg_s / (sg_a + sg_s); // albedo\n"
"	const float c1 = fmax(0.f, cos_th1);\n"
"	const float c2 = fmax(0.f, cos_th2);\n"
"	if (c1 == 0.0f || c2 == 0.0f)\n"
"		return 0.0f;\n"
"	return al * (.5f * M_1_PI_F) * .5f * c1 * c2 / (c1 + c2);\n"
"}\n"
"\n"
"void GetYarnUV(__constant WeaveConfig *Weave, __constant Yarn *yarn,\n"
"        const float Repeat_U, const float Repeat_V,\n"
"        const float3 center, const float3 xy, float2 *uv, float *umaxMod) {\n"
"	*umaxMod = Radians(yarn->umax);\n"
"	if (Weave->period > 0.f) {\n"
"		/* Number of TEA iterations (the more, the better the\n"
"		   quality of the pseudorandom floats) */\n"
"		const int teaIterations = 8;\n"
"\n"
"		// Correlated (Perlin) noise.\n"
"		// generate 1 seed per yarn segment\n"
"		const float random1 = Noise((center.x *\n"
"			(Weave->tileHeight * Repeat_V +\n"
"			sampleTEAfloat(center.x, 2.f * center.y,\n"
"			teaIterations)) + center.y) / Weave->period, 0.0, 0.0);\n"
"		const float random2 = Noise((center.y *\n"
"			(Weave->tileWidth * Repeat_U +\n"
"			sampleTEAfloat(center.x, 2.f * center.y + 1.f,\n"
"			teaIterations)) + center.x) / Weave->period, 0.0, 0.0);\n"
"		\n"
"		if (yarn->yarn_type == WARP)\n"
"	  		*umaxMod += random1 * Radians(Weave->dWarpUmaxOverDWarp) +\n"
"				random2 * Radians(Weave->dWarpUmaxOverDWeft);\n"
"		else\n"
"			*umaxMod += random1 * Radians(Weave->dWeftUmaxOverDWarp) +\n"
"				random2 * Radians(Weave->dWeftUmaxOverDWeft);\n"
"	}\n"
"	\n"
"\n"
"	// Compute u and v.\n"
"	// See Chapter 6.\n"
"	// Rotate pi/2 radians around z axis\n"
"	if (yarn->yarn_type == WARP) {\n"
"		(*uv).s0 = xy.y * 2.f * *umaxMod / yarn->length;\n"
"		(*uv).s1 = xy.x * M_PI_F / yarn->width;\n"
"	} else {\n"
"		(*uv).s0 = xy.x * 2.f * *umaxMod / yarn->length;\n"
"		(*uv).s1 = -xy.y * M_PI_F / yarn->width;\n"
"	}\n"
"}\n"
"\n"
"__constant Yarn *GetYarn(const ClothPreset Preset, __constant WeaveConfig *Weave,\n"
"        const float Repeat_U, const float Repeat_V,\n"
"        const float u_i, const float v_i,\n"
"        float2 *uv, float *umax, float *scale) {\n"
"	const float u = u_i * Repeat_U;\n"
"	const int bu = Floor2Int(u);\n"
"	const float ou = u - bu;\n"
"	const float v = v_i * Repeat_V;\n"
"	const int bv = Floor2Int(v);\n"
"	const float ov = v - bv;\n"
"	const uint lx = min(Weave->tileWidth - 1, Floor2UInt(ou * Weave->tileWidth));\n"
"	const uint ly = Weave->tileHeight - 1 -\n"
"		min(Weave->tileHeight - 1, Floor2UInt(ov * Weave->tileHeight));\n"
"\n"
"	const int yarnID = ClothPatterns[Preset][lx + Weave->tileWidth * ly] - 1;\n"
"	__constant Yarn *yarn = &ClothYarns[Preset][yarnID];\n"
"\n"
"	const float3 center = (float3)((bu + yarn->centerU) * Weave->tileWidth,\n"
"		(bv + yarn->centerV) * Weave->tileHeight, 0.f);\n"
"	const float3 xy = (float3)((ou - yarn->centerU) * Weave->tileWidth,\n"
"		(ov - yarn->centerV) * Weave->tileHeight, 0.f);\n"
"\n"
"	GetYarnUV(Weave, yarn, Repeat_U, Repeat_V, center, xy, uv, umax);\n"
"\n"
"	/* Number of TEA iterations (the more, the better the\n"
"	   quality of the pseudorandom floats) */\n"
"	const int teaIterations = 8;\n"
"\n"
"	// Compute random variation and scale specular component.\n"
"	if (Weave->fineness > 0.0f) {\n"
"		// Initialize random number generator based on texture location.\n"
"		// Generate fineness^2 seeds per 1 unit of texture.\n"
"		const uint index1 = (uint) ((center.x + xy.x) * Weave->fineness);\n"
"		const uint index2 = (uint) ((center.y + xy.y) * Weave->fineness);\n"
"\n"
"		const float xi = sampleTEAfloat(index1, index2, teaIterations);\n"
"		\n"
"		*scale *= fmin(-log(xi), 10.0f);\n"
"	}\n"
"\n"
"	return yarn;\n"
"}\n"
"\n"
"float RadiusOfCurvature(__constant Yarn *yarn, float u, float umaxMod) {\n"
"	// rhat determines whether the spine is a segment\n"
"	// of an ellipse, a parabole, or a hyperbola.\n"
"	// See Section 5.3.\n"
"	const float rhat = 1.0f + yarn->kappa * (1.0f + 1.0f / tan(umaxMod));\n"
"	const float a = 0.5f * yarn->width;\n"
"	\n"
"	if (rhat == 1.0f) { // circle; see Subsection 5.3.1.\n"
"		return 0.5f * yarn->length / sin(umaxMod) - a;\n"
"	} else if (rhat > 0.0f) { // ellipsis\n"
"		const float tmax = atan(rhat * tan(umaxMod));\n"
"		const float bhat = (0.5f * yarn->length - a * sin(umaxMod)) / sin(tmax);\n"
"		const float ahat = bhat / rhat;\n"
"		const float t = atan(rhat * tan(u));\n"
"		return pow(bhat * bhat * cos(t) * cos(t) +\n"
"			ahat * ahat * sin(t) * sin(t), 1.5f) / (ahat * bhat);\n"
"	} else if (rhat < 0.0f) { // hyperbola; see Subsection 5.3.3.\n"
"		const float tmax = -atanh(rhat * tan(umaxMod));\n"
"		const float bhat = (0.5f * yarn->length - a * sin(umaxMod)) / sinh(tmax);\n"
"		const float ahat = bhat / rhat;\n"
"		const float t = -atanh(rhat * tan(u));\n"
"		return -pow(bhat * bhat * cosh(t) * cosh(t) +\n"
"			ahat * ahat * sinh(t) * sinh(t), 1.5f) / (ahat * bhat);\n"
"	} else { // rhat == 0  // parabola; see Subsection 5.3.2.\n"
"		const float tmax = tan(umaxMod);\n"
"		const float ahat = (0.5f * yarn->length - a * sin(umaxMod)) / (2.f * tmax);\n"
"		const float t = tan(u);\n"
"		return 2.f * ahat * pow(1.f + t * t, 1.5f);\n"
"	}\n"
"}\n"
"\n"
"float EvalFilamentIntegrand(__constant WeaveConfig *Weave, __constant Yarn *yarn, const float3 om_i,\n"
"        const float3 om_r, float u, float v, float umaxMod) {\n"
"	// 0 <= ss < 1.0\n"
"	if (Weave->ss < 0.0f || Weave->ss >= 1.0f)\n"
"		return 0.0f;\n"
"\n"
"	// w * sin(umax) < l\n"
"	if (yarn->width * sin(umaxMod) >= yarn->length)\n"
"		return 0.0f;\n"
"\n"
"	// -1 < kappa < inf\n"
"	if (yarn->kappa < -1.0f)\n"
"		return 0.0f;\n"
"\n"
"	// h is the half vector\n"
"	const float3 h = normalize(om_r + om_i);\n"
"\n"
"	// u_of_v is location of specular reflection.\n"
"	const float u_of_v = atan2(h.y, h.z);\n"
"\n"
"	// Check if u_of_v within the range of valid u values\n"
"	if (fabs(u_of_v) >= umaxMod)\n"
"		return 0.f;\n"
"\n"
"	// Highlight has constant width delta_u\n"
"	const float delta_u = umaxMod * Weave->hWidth;\n"
"\n"
"	// Check if |u(v) - u| < delta_u.\n"
"	if (fabs(u_of_v - u) >= delta_u)\n"
"		return 0.f;\n"
"\n"
"	\n"
"	// n is normal to the yarn surface\n"
"	// t is tangent of the fibers.\n"
"	const float3 n = normalize((float3)(sin(v), sin(u_of_v) * cos(v),\n"
"		cos(u_of_v) * cos(v)));\n"
"	const float3 t = normalize((float3)(0.0f, cos(u_of_v), -sin(u_of_v)));\n"
"\n"
"	// R is radius of curvature.\n"
"	const float R = RadiusOfCurvature(yarn, fmin(fabs(u_of_v),\n"
"		(1.f - Weave->ss) * umaxMod), (1.f - Weave->ss) * umaxMod);\n"
"\n"
"	// G is geometry factor.\n"
"	const float a = 0.5f * yarn->width;\n"
"	const float3 om_i_plus_om_r = om_i + om_r;\n"
"    const float3 t_cross_h = cross(t, h);\n"
"	const float Gu = a * (R + a * cos(v)) /\n"
"		(length(om_i_plus_om_r) * fabs(t_cross_h.x));\n"
"\n"
"\n"
"	// fc is phase function\n"
"	const float fc = Weave->alpha + vonMises(-dot(om_i, om_r), Weave->beta);\n"
"\n"
"	// attenuation function without smoothing.\n"
"	float As = seeliger(dot(n, om_i), dot(n, om_r), 0, 1);\n"
"	// As is attenuation function with smoothing.\n"
"	if (Weave->ss > 0.0f)\n"
"		As *= SmoothStep(0.f, 1.f, (umaxMod - fabs(u_of_v)) /\n"
"			(Weave->ss * umaxMod));\n"
"\n"
"	// fs is scattering function.\n"
"	const float fs = Gu * fc * As;\n"
"\n"
"	// Domain transform.\n"
"	return fs * M_PI_F / Weave->hWidth;\n"
"}\n"
"\n"
"float EvalStapleIntegrand(__constant WeaveConfig *Weave, __constant Yarn *yarn,\n"
"        const float3 om_i, const float3 om_r, float u, float v, float umaxMod) {\n"
"	// w * sin(umax) < l\n"
"	if (yarn->width * sin(umaxMod) >= yarn->length)\n"
"		return 0.0f;\n"
"\n"
"	// -1 < kappa < inf\n"
"	if (yarn->kappa < -1.0f)\n"
"		return 0.0f;\n"
"\n"
"	// h is the half vector\n"
"	const float3 h = normalize(om_i + om_r);\n"
"\n"
"	// v_of_u is location of specular reflection.\n"
"	const float D = (h.y * cos(u) - h.z * sin(u)) /\n"
"		(sqrt(h.x * h.x + pow(h.y * sin(u) + h.z * cos(u),\n"
"		2.0f)) * tan(Radians(yarn->psi)));\n"
"	if (!(fabs(D) < 1.f))\n"
"		return 0.f;\n"
"	const float v_of_u = atan2(-h.y * sin(u) - h.z * cos(u), h.x) +\n"
"		acos(D);\n"
"\n"
"	// Highlight has constant width delta_x on screen.\n"
"	const float delta_v = .5f * M_PI_F * Weave->hWidth;\n"
"\n"
"	// Check if |x(v(u)) - x(v)| < delta_x/2.\n"
"	if (fabs(v_of_u - v) >= delta_v)\n"
"		return 0.f;\n"
"\n"
"	// n is normal to the yarn surface.\n"
"	const float3 n = normalize((float3)(sin(v_of_u), sin(u) * cos(v_of_u),\n"
"		cos(u) * cos(v_of_u)));\n"
"\n"
"	// R is radius of curvature.\n"
"	const float R = RadiusOfCurvature(yarn, fabs(u), umaxMod);\n"
"\n"
"	// G is geometry factor.\n"
"	const float a = 0.5f * yarn->width;\n"
"	const float3 om_i_plus_om_r = om_i + om_r;\n"
"	const float Gv = a * (R + a * cos(v_of_u)) /\n"
"		(length(om_i_plus_om_r) * dot(n, h) * fabs(sin(Radians(yarn->psi))));\n"
"\n"
"	// fc is phase function.\n"
"	const float fc = Weave->alpha + vonMises(-dot(om_i, om_r), Weave->beta);\n"
"\n"
"	// A is attenuation function without smoothing.\n"
"	const float A = seeliger(dot(n, om_i), dot(n, om_r), 0, 1);\n"
"\n"
"	// fs is scattering function.\n"
"	const float fs = Gv * fc * A;\n"
"	\n"
"	// Domain transform.\n"
"	return fs * 2.0f * umaxMod / Weave->hWidth;\n"
"}\n"
"\n"
"float EvalIntegrand(__constant WeaveConfig *Weave, __constant Yarn *yarn,\n"
"        const float2 uv, float umaxMod, float3 *om_i, float3 *om_r) {\n"
"	if (yarn->yarn_type == WARP) {\n"
"		if (yarn->psi != 0.0f)\n"
"			return EvalStapleIntegrand(Weave, yarn, *om_i, *om_r, uv.s0, uv.s1,\n"
"				umaxMod) * (Weave->warpArea + Weave->weftArea) /\n"
"				Weave->warpArea;\n"
"		else\n"
"			return EvalFilamentIntegrand(Weave, yarn, *om_i, *om_r, uv.s0, uv.s1,\n"
"				umaxMod) * (Weave->warpArea + Weave->weftArea) /\n"
"				Weave->warpArea;\n"
"	} else {\n"
"		// Rotate pi/2 radians around z axis\n"
"        //swap((*om_i).x, (*om_i).y);\n"
"        float tmp = (*om_i).x;\n"
"        (*om_i).x = (*om_i).y;\n"
"        (*om_i).y = tmp;\n"
"		(*om_i).x = -(*om_i).x;\n"
"\n"
"		//swap((*om_r).x, (*om_r).y);\n"
"        tmp = (*om_r).x;\n"
"        (*om_r).x = (*om_r).y;\n"
"        (*om_r).y = tmp;\n"
"		(*om_r).x = -(*om_r).x;\n"
"\n"
"		if (yarn->psi != 0.0f)\n"
"			return EvalStapleIntegrand(Weave, yarn, *om_i, *om_r, uv.s0, uv.s1,\n"
"				umaxMod) * (Weave->warpArea + Weave->weftArea) /\n"
"				Weave->weftArea;\n"
"		else\n"
"			return EvalFilamentIntegrand(Weave, yarn, *om_i, *om_r, uv.s0, uv.s1,\n"
"				umaxMod) * (Weave->warpArea + Weave->weftArea) /\n"
"				Weave->weftArea;\n"
"	}\n"
"}\n"
"\n"
"float EvalSpecular(__constant WeaveConfig *Weave, __constant Yarn *yarn, const float2 uv,\n"
"        float umax, const float3 wo, const float3 wi) {\n"
"	// Get incident and exitant directions.\n"
"	float3 om_i = wi;\n"
"	if (om_i.z < 0.f)\n"
"		om_i = -om_i;\n"
"	float3 om_r = wo;\n"
"	if (om_r.z < 0.f)\n"
"		om_r = -om_r;\n"
"\n"
"	// Compute specular contribution.\n"
"	return EvalIntegrand(Weave, yarn, uv, umax, &om_i, &om_r);\n"
"}\n"
"\n"
"float3 ClothMaterial_Evaluate(\n"
"		__global HitPoint *hitPoint, const float3 localLightDir, const float3 localEyeDir,\n"
"		BSDFEvent *event, float *directPdfW,\n"
"		const ClothPreset Preset, const float Repeat_U, const float Repeat_V,\n"
"		const float s, const float3 Warp_Ks, const float3 Weft_Ks,\n"
"		const float3 Warp_Kd, const float3 Weft_Kd) {\n"
"    *directPdfW = fabs(localLightDir.z * M_1_PI_F);\n"
"    \n"
"    *event = GLOSSY | REFLECT;\n"
"\n"
"    __constant WeaveConfig *Weave = &ClothWeaves[Preset];\n"
"\n"
"	float2 uv;\n"
"	float umax, scale = s;\n"
"	__constant Yarn *yarn = GetYarn(Preset, Weave, Repeat_U, Repeat_V,\n"
"            hitPoint->uv.u, hitPoint->uv.v, &uv, &umax, &scale);\n"
"    \n"
"    scale = scale * EvalSpecular(Weave, yarn, uv, umax, localLightDir, localEyeDir);\n"
"	\n"
"	const float3 ks = (yarn->yarn_type == WARP) ? Warp_Ks : Weft_Ks;\n"
"	const float3 kd = (yarn->yarn_type == WARP) ? Warp_Kd : Weft_Kd;\n"
"\n"
"    const float3 ksVal = Spectrum_Clamp(ks);\n"
"    const float3 kdVal = Spectrum_Clamp(kd);\n"
"\n"
"	return (kdVal + ksVal * scale) * M_1_PI_F * fabs(localLightDir.z);\n"
"}\n"
"\n"
"float3 ClothMaterial_Sample(\n"
"		__global HitPoint *hitPoint, const float3 localFixedDir, float3 *localSampledDir,\n"
"		const float u0, const float u1,\n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"		const float passThroughEvent,\n"
"#endif\n"
"		float *pdfW, float *absCosSampledDir, BSDFEvent *event,\n"
"		const BSDFEvent requestedEvent,\n"
"		const ClothPreset Preset, const float Repeat_U, const float Repeat_V,\n"
"		const float s, const float3 Warp_Ks, const float3 Weft_Ks,\n"
"		const float3 Warp_Kd, const float3 Weft_Kd) {\n"
"	if (!(requestedEvent & (GLOSSY | REFLECT)) ||\n"
"			(fabs(localFixedDir.z) < DEFAULT_COS_EPSILON_STATIC))\n"
"		return BLACK;\n"
"\n"
"	*localSampledDir = (signbit(localFixedDir.z) ? -1.f : 1.f) * CosineSampleHemisphereWithPdf(u0, u1, pdfW);\n"
"\n"
"	*absCosSampledDir = fabs((*localSampledDir).z);\n"
"	if (*absCosSampledDir < DEFAULT_COS_EPSILON_STATIC)\n"
"		return BLACK;\n"
"\n"
"	*event = GLOSSY | REFLECT;\n"
"\n"
"    __constant WeaveConfig *Weave = &ClothWeaves[Preset];\n"
"\n"
"	float2 uv;\n"
"	float umax, scale = s;\n"
"	__constant Yarn *yarn = GetYarn(Preset, Weave, Repeat_U, Repeat_V,\n"
"            hitPoint->uv.u, hitPoint->uv.v, &uv, &umax, &scale);\n"
"\n"
"//	if (!hitPoint.fromLight)\n"
"	    scale = scale * EvalSpecular(Weave, yarn, uv, umax, localFixedDir, *localSampledDir);\n"
"//	else\n"
"//	    scale = scale * EvalSpecular(Weave, yarn, uv, umax, *localSampledDir, localFixedDir);\n"
"\n"
"    const float3 ks = (yarn->yarn_type == WARP) ? Warp_Ks : Weft_Ks;\n"
"	const float3 kd = (yarn->yarn_type == WARP) ? Warp_Kd : Weft_Kd;\n"
"\n"
"    const float3 ksVal = Spectrum_Clamp(ks);\n"
"    const float3 kdVal = Spectrum_Clamp(kd);\n"
"\n"
"	return kdVal + ksVal * scale;\n"
"}\n"
"\n"
"#endif\n"
; } }

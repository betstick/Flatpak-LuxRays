#include <string>
namespace luxrays { namespace ocl {
std::string KernelSource_vector_funcs = 
"#line 2 \"vector_funcs.cl\"\n"
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
"float SphericalTheta(const float3 v) {\n"
"	return acos(clamp(v.z, -1.f, 1.f));\n"
"}\n"
"\n"
"float SphericalPhi(const float3 v) {\n"
"	const float p = atan2(v.y, v.x);\n"
"	return (p < 0.f) ? p + 2.f * M_PI_F : p;\n"
"}\n"
"\n"
"void CoordinateSystem(const float3 v1, float3 *v2, float3 *v3) {\n"
"	if (fabs(v1.x) > fabs(v1.y)) {\n"
"		float invLen = 1.f / sqrt(v1.x * v1.x + v1.z * v1.z);\n"
"		(*v2).x = -v1.z * invLen;\n"
"		(*v2).y = 0.f;\n"
"		(*v2).z = v1.x * invLen;\n"
"	} else {\n"
"		float invLen = 1.f / sqrt(v1.y * v1.y + v1.z * v1.z);\n"
"		(*v2).x = 0.f;\n"
"		(*v2).y = v1.z * invLen;\n"
"		(*v2).z = -v1.y * invLen;\n"
"	}\n"
"\n"
"	*v3 = cross(v1, *v2);\n"
"}\n"
; } }

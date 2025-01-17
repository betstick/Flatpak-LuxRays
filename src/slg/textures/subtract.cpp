/***************************************************************************
 * Copyright 1998-2017 by authors (see AUTHORS.txt)                        *
 *                                                                         *
 *   This file is part of LuxRender.                                       *
 *                                                                         *
 * Licensed under the Apache License, Version 2.0 (the "License");         *
 * you may not use this file except in compliance with the License.        *
 * You may obtain a copy of the License at                                 *
 *                                                                         *
 *     http://www.apache.org/licenses/LICENSE-2.0                          *
 *                                                                         *
 * Unless required by applicable law or agreed to in writing, software     *
 * distributed under the License is distributed on an "AS IS" BASIS,       *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
 * See the License for the specific language governing permissions and     *
 * limitations under the License.                                          *
 ***************************************************************************/

#include "slg/textures/subtract.h"

using namespace std;
using namespace luxrays;
using namespace slg;

//------------------------------------------------------------------------------
// Subtract texture
//------------------------------------------------------------------------------

float SubtractTexture::GetFloatValue(const HitPoint &hitPoint) const {
	return tex1->GetFloatValue(hitPoint) - tex2->GetFloatValue(hitPoint);
}

Spectrum SubtractTexture::GetSpectrumValue(const HitPoint &hitPoint) const {
	return tex1->GetSpectrumValue(hitPoint) - tex2->GetSpectrumValue(hitPoint);
}

Normal SubtractTexture::Bump(const HitPoint &hitPoint, const float sampleDistance) const {
	const Normal tex1ShadeN = tex1->Bump(hitPoint, sampleDistance);
	const Normal tex2ShadeN = tex2->Bump(hitPoint, sampleDistance);

	// Same of Normalize(hitPoint.shadeN + (tex1ShadeN - hitPoint.shadeN) - (tex2ShadeN - hitPoint.shadeN))
	return Normalize(tex1ShadeN - tex2ShadeN + hitPoint.shadeN);
}

Properties SubtractTexture::ToProperties(const ImageMapCache &imgMapCache) const {
	Properties props;
	
	const string name = GetName();
	props.Set(Property("scene.textures." + name + ".type")("subtract"));
	props.Set(Property("scene.textures." + name + ".texture1")(tex1->GetName()));
	props.Set(Property("scene.textures." + name + ".texture2")(tex2->GetName()));
	
	return props;
}

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

#ifndef _SLG_RENDERCONFIG_H
#define	_SLG_RENDERCONFIG_H

#include <boost/thread/mutex.hpp>

#include "luxrays/core/randomgen.h"
#include "luxrays/utils/properties.h"
#include "slg/slg.h"
#include "slg/samplers/sampler.h"
#include "slg/scene/scene.h"

namespace slg {

class RenderConfig {
public:
	RenderConfig(const luxrays::Properties &props, Scene *scene = NULL);
	~RenderConfig();

	const luxrays::Property GetProperty(const std::string &name) const;

	void Parse(const luxrays::Properties &props);
	void UpdateFilmProperties(const luxrays::Properties &props);
	void Delete(const std::string &prefix);

	bool GetFilmSize(u_int *filmFullWidth, u_int *filmFullHeight,
		u_int *filmSubRegion) const;

	Filter *AllocPixelFilter() const;
	Film *AllocFilm() const;

	SamplerSharedData *AllocSamplerSharedData(luxrays::RandomGenerator *rndGen, Film *film) const;
	Sampler *AllocSampler(luxrays::RandomGenerator *rndGen, Film *film,
		const FilmSampleSplatter *flmSplatter,
		SamplerSharedData *sharedData) const;

	RenderEngine *AllocRenderEngine(Film *film, boost::mutex *filmMutex) const;

	const luxrays::Properties &ToProperties() const;

	static luxrays::Properties ToProperties(const luxrays::Properties &cfg);
	static const luxrays::Properties &GetDefaultProperties();

	luxrays::Properties cfg;
	Scene *scene;

private:
	static void InitDefaultProperties();

	mutable luxrays::Properties propsCache;

	bool allocatedScene, enableParsePrint;
};

}

#endif	/* _SLG_RENDERCONFIG_H */

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

#ifndef _SLG_TILEPATHCPU_H
#define	_SLG_TILEPATHCPU_H

#include "slg/slg.h"
#include "slg/engines/cpurenderengine.h"
#include "slg/engines/pathtracer.h"
#include "slg/samplers/sampler.h"
#include "slg/film/film.h"
#include "slg/film/filters/filter.h"
#include "slg/bsdf/bsdf.h"
#include "slg/utils/pathdepthinfo.h"

namespace slg {

//------------------------------------------------------------------------------
// Tile path tracing CPU render engine
//------------------------------------------------------------------------------

class TilePathCPURenderEngine;

class TilePathCPURenderThread : public CPUTileRenderThread {
public:
	TilePathCPURenderThread(TilePathCPURenderEngine *engine, const u_int index,
			luxrays::IntersectionDevice *device);

	friend class TilePathCPURenderEngine;

private:
	virtual boost::thread *AllocRenderThread() { return new boost::thread(&TilePathCPURenderThread::RenderFunc, this); }

	void RenderFunc();

	void SampleGrid(luxrays::RandomGenerator *rndGen, const u_int size,
		const u_int ix, const u_int iy, float *u0, float *u1) const;
};

class TilePathCPURenderEngine : public CPUTileRenderEngine {
public:
	TilePathCPURenderEngine(const RenderConfig *cfg, Film *flm, boost::mutex *flmMutex);
	~TilePathCPURenderEngine();

	virtual RenderEngineType GetType() const { return GetObjectType(); }
	virtual std::string GetTag() const { return GetObjectTag(); }

	virtual RenderState *GetRenderState();

	//--------------------------------------------------------------------------
	// Static methods used by RenderEngineRegistry
	//--------------------------------------------------------------------------

	static RenderEngineType GetObjectType() { return TILEPATHCPU; }
	static std::string GetObjectTag() { return "TILEPATHCPU"; }
	static luxrays::Properties ToProperties(const luxrays::Properties &cfg);
	static RenderEngine *FromProperties(const RenderConfig *rcfg, Film *flm, boost::mutex *flmMutex);

	friend class TilePathCPURenderThread;

protected:
	static const luxrays::Properties &GetDefaultProps();

	virtual void InitFilm();
	virtual void StartLockLess();

	// Samples settings
	u_int aaSamples;

	PathTracer pathTracer;

private:
	virtual CPURenderThread *NewRenderThread(const u_int index,
			luxrays::IntersectionDevice *device) {
		return new TilePathCPURenderThread(this, index, device);
	}
};

}

#endif	/* _SLG_TILEPATHCPU_H */

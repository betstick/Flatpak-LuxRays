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

#ifndef _SLG_RTPATHCPU_H
#define	_SLG_RTPATHCPU_H

#include <boost/thread/barrier.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>    

#include "slg/engines/pathcpu/pathcpu.h"

namespace slg {

//------------------------------------------------------------------------------
// Real-Time path tracing CPU render engine
//------------------------------------------------------------------------------

class RTPathCPURenderEngine;

class RTPathCPURenderThread : public PathCPURenderThread {
public:
	RTPathCPURenderThread(RTPathCPURenderEngine *engine, const u_int index,
			luxrays::IntersectionDevice *device);
	~RTPathCPURenderThread();

	friend class RTPathCPURenderEngine;

protected:
	void RTRenderFunc();
	virtual boost::thread *AllocRenderThread() { return new boost::thread(&RTPathCPURenderThread::RTRenderFunc, this); }

	virtual void StartRenderThread();
};

class RTPathCPUSampler;

class RTPathCPURenderEngine : public PathCPURenderEngine {
public:
	RTPathCPURenderEngine(const RenderConfig *cfg, Film *flm, boost::mutex *flmMutex);
	~RTPathCPURenderEngine();

	virtual RenderEngineType GetType() const { return GetObjectType(); }
	virtual std::string GetTag() const { return GetObjectTag(); }

	void WaitNewFrame();
	virtual void Pause();
	virtual void Resume();

	//--------------------------------------------------------------------------
	// Static methods used by RenderEngineRegistry
	//--------------------------------------------------------------------------

	static RenderEngineType GetObjectType() { return RTPATHCPU; }
	static std::string GetObjectTag() { return "RTPATHCPU"; }
	static luxrays::Properties ToProperties(const luxrays::Properties &cfg);
	static RenderEngine *FromProperties(const RenderConfig *rcfg, Film *flm, boost::mutex *flmMutex);

	friend class PathCPURenderEngine;
	friend class RTPathCPURenderThread;
	friend class RTPathCPUSampler;

protected:
	static const luxrays::Properties &GetDefaultProps();

	CPURenderThread *NewRenderThread(const u_int index,
			luxrays::IntersectionDevice *device) {
		return new RTPathCPURenderThread(this, index, device);
	}

	virtual void StartLockLess();
	virtual void StopLockLess();

	virtual void BeginSceneEditLockLess();
	virtual void EndSceneEditLockLess(const EditActionList &editActions);

	virtual void BeginFilmEdit();
	virtual void EndFilmEdit(Film *flm);

	virtual void UpdateFilmLockLess();

	void PauseThreads();
	void ResumeThreads();

	u_int zoomFactor;
	float zoomWeight;

	boost::mutex firstFrameMutex;
    boost::condition_variable firstFrameCondition;
	u_int firstFrameThreadDoneCount;
	bool firstFrameDone;

	boost::barrier *threadsSyncBarrier;
	bool threadsPauseMode;
};

}

#endif	/* _SLG_RTPATHCPU_H */

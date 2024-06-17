// FPS={FPS},
// Prd={Prediction}ms,
// Tear={Tears},
// Early={Early},
// Stale={Stale},
// VSnc={Swap Interval},
// Lat={Extra Latency Mode},
// Fov={Foveation Level},
// CPU{Measured CPU Core}/GPU={CPU Level}/{GPU Level},
// {CPU Frequency}/{GPU Frequency}MHz,
// OC={Online Core Mask},
// TA={TimeWarp Thread Affinity}/{Main Thread Affinity}/{Render Thread Affinity},
// SP={Timewarp Scheduling Priority}/{Main Thread Scheduling Priority}/{Render Thread Scheduling Priority},
// Mem={Memory Frequency}MHz,
// Free={Available Memory}MB,
// PSM={Power Save Mode},
// PLS={Power Level},
// Temp={Battery Temperature}C/{Sensor Temperature}C,
// TW={TimeWarp GPU Time}ms,
// App={App GPU Time}ms,
// GD={Guardian GPU Time}ms,
// CPU&GPU={CPU & GPU Time}ms,
// LCnt={Layer Count},
// GPU%={GPU Utilization},
// CPU%={Average CPU Utilization}(W{Worst Core CPU Utilization})

// 06-14 22:00:33.011  2072 10406 I VrApi   : 
// FPS=23/90,
// Prd=0ms,
// Tear=0,
// Early=0,
// Stale=1,
// Stale2/5/10/max=0/0/0/0,
// VSnc=1,
// Lat=-1,
// Fov=0,
// CPU4/GPU=2/4,
// 2419/305MHz,
// OC=FF,
// TA=0/70/0,
// SP=N/F/N,
// Mem=2092MHz,
// Free=2901MB,
// PLS=0,
// Temp=29.2C/0.0C,
// TW=2.62ms,
// App=8.13ms,
// GD=0.00ms,
// CPU&GPU=0.00ms,
// LCnt=1(DR0,LM0),
// GPU%=0.33,
// CPU%=0.98(W1.00),
// DSF=1.00,
// CFL=-1000.00/-1000.00,
// ICFLp95=19.00,
// LD=0,
// SF=0.00,
// LP=0,
// DVFS=0

#pragma once

#include <vector>

class LogParser
{
public:
	void ParseLatest();
};
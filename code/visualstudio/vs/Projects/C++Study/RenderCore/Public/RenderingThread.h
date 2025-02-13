// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	RenderingThread.h: Rendering thread definitions.
=============================================================================*/

#pragma once

#include "RenderCore.h"
//#include "CoreMinimal.h"
#include "Public/CoreGlobals.h"
//#include "Stats/Stats.h"
#include "Async/TaskGraphInterfaces.h"
#include "Public/Templates/Atomic.h"

//#define RENDERCORE_API __declspec(dllexport)

class FRHICommandListImmediate;

////////////////////////////////////
// Render thread API
////////////////////////////////////
extern int nTest;
/**
 * Whether the renderer is currently running in a separate thread.
 * If this is false, then all rendering commands will be executed immediately instead of being enqueued in the rendering command buffer.
 */
extern RENDERCORE_API bool GIsThreadedRendering;

/**
 * Whether the rendering thread should be created or not.
 * Currently set by command line parameter and by the ToggleRenderingThread console command.
 */
extern RENDERCORE_API bool GUseThreadedRendering;

extern RENDERCORE_API void SetRHIThreadEnabled(bool bEnableDedicatedThread, bool bEnableRHIOnTaskThreads);

#if (UE_BUILD_SHIPPING || UE_BUILD_TEST)
	static FORCEINLINE void CheckNotBlockedOnRenderThread() {}
#else // #if (UE_BUILD_SHIPPING || UE_BUILD_TEST)
	/** Whether the main thread is currently blocked on the rendering thread, e.g. a call to FlushRenderingCommands. */
	//extern RENDERCORE_API TAtomic<bool> GMainThreadBlockedOnRenderThread;

	/** Asserts if called from the main thread when the main thread is blocked on the rendering thread. */
	//static FORCEINLINE void CheckNotBlockedOnRenderThread() { ensure(!GMainThreadBlockedOnRenderThread.Load(EMemoryOrder::Relaxed) || !IsInGameThread()); }
#endif // #if (UE_BUILD_SHIPPING || UE_BUILD_TEST)


/** Starts the rendering thread. */
extern RENDERCORE_API void StartRenderingThread();

/** Stops the rendering thread. */
extern RENDERCORE_API void StopRenderingThread();

/**
 * Checks if the rendering thread is healthy and running.
 * If it has crashed, UE_LOG is called with the exception information.
 */
extern RENDERCORE_API void CheckRenderingThreadHealth();

/** Checks if the rendering thread is healthy and running, without crashing */
extern RENDERCORE_API bool IsRenderingThreadHealthy();

/**
 * Advances stats for the rendering thread. Called from the game thread.
 */
extern RENDERCORE_API void AdvanceRenderingThreadStatsGT( bool bDiscardCallstack, int64 StatsFrame, int32 MasterDisableChangeTagStartFrame );

/**
 * Adds a task that must be completed either before the next scene draw or a flush rendering commands
 * This can be called from any thread though it probably doesn't make sense to call it from the render thread.
 * @param TaskToAdd, task to add as a pending render thread task
 */
extern RENDERCORE_API void AddFrameRenderPrerequisite(const FGraphEventRef& TaskToAdd);

/**
 * Gather the frame render prerequisites and make sure all render commands are at least queued
 */
extern RENDERCORE_API void AdvanceFrameRenderPrerequisite();

/**
 * Waits for the rendering thread to finish executing all pending rendering commands.  Should only be used from the game thread.
 */
extern RENDERCORE_API void FlushRenderingCommands(bool bFlushDeferredDeletes = false);

extern RENDERCORE_API void FlushPendingDeleteRHIResources_GameThread();
extern RENDERCORE_API void FlushPendingDeleteRHIResources_RenderThread();

extern RENDERCORE_API void TickRenderingTickables();

extern RENDERCORE_API void StartRenderCommandFenceBundler();
extern RENDERCORE_API void StopRenderCommandFenceBundler();

////////////////////////////////////
// Render thread suspension
////////////////////////////////////

/**
 * Encapsulates stopping and starting the renderthread so that other threads can manipulate graphics resources.
 */
class RENDERCORE_API FSuspendRenderingThread
{
public:
	/**
	 *	Constructor that flushes and suspends the renderthread
	 *	@param bRecreateThread	- Whether the rendering thread should be completely destroyed and recreated, or just suspended.
	 */
	FSuspendRenderingThread( bool bRecreateThread );

	/** Destructor that starts the renderthread again */
	~FSuspendRenderingThread();

private:
	/** Whether we should use a rendering thread or not */
	bool bUseRenderingThread;

	/** Whether the rendering thread was currently running or not */
	bool bWasRenderingThreadRunning;

	/** Whether the rendering thread should be completely destroyed and recreated, or just suspended */
	bool bRecreateThread;
};

/** Helper macro for safely flushing and suspending the rendering thread while manipulating graphics resources */
#define SCOPED_SUSPEND_RENDERING_THREAD(bRecreateThread)	FSuspendRenderingThread SuspendRenderingThread(bRecreateThread)

////////////////////////////////////
// Render commands
////////////////////////////////////

/** The parent class of commands stored in the rendering command queue. */
class RENDERCORE_API FRenderCommand
{
public:
	// All render commands run on the render thread
	static ENamedThreads::Type GetDesiredThread()
	{
		//check(!GIsThreadedRendering || ENamedThreads::GetRenderThread() != ENamedThreads::GameThread);
		return ENamedThreads::GetRenderThread();
	}

	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		// Don't support tasks having dependencies on us, reduces task graph overhead tracking and dealing with subsequents
		return ESubsequentsMode::FireAndForget;
	}
};

//
// Macros for using render commands.
//
// ideally this would be inline, however that changes the module dependency situation
extern RENDERCORE_API class FRHICommandListImmediate& GetImmediateCommandList_ForRenderCommand();


//DECLARE_STATS_GROUP(TEXT("Render Thread Commands"), STATGROUP_RenderThreadCommands, STATCAT_Advanced);

// Log render commands on server for debugging
#if 0 // UE_SERVER && UE_BUILD_DEBUG
	#define LogRenderCommand(TypeName)				UE_LOG(LogRHI, Warning, TEXT("Render command '%s' is being executed on a dedicated server."), TEXT(#TypeName))
#else
	#define LogRenderCommand(TypeName)
#endif 

// conditions when rendering commands are executed in the thread
#if UE_SERVER
	#define	ShouldExecuteOnRenderThread()			false
#else
	#define	ShouldExecuteOnRenderThread()			(LIKELY(GIsThreadedRendering || !IsInGameThread()))
#endif // UE_SERVER

//FRHICommandListImmediate& RHICmdList = GetImmediateCommandList_ForRenderCommand(); \
//Code; \
#define TASK_FUNCTION(Code) \
		void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) \
		{ \
		} 

#define TASKNAME_FUNCTION(TypeName) \
		FORCEINLINE TStatId GetStatId() const \
		{ \
			RETURN_QUICK_DECLARE_CYCLE_STAT(TypeName, STATGROUP_RenderThreadCommands); \
		}

template<typename TSTR, typename LAMBDA>
class TEnqueueUniqueRenderCommandType : public FRenderCommand
{
public:
	TEnqueueUniqueRenderCommandType(LAMBDA&& InLambda) : Lambda(Forward<LAMBDA>(InLambda)) {}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
#if CPUPROFILERTRACE_ENABLED
		static uint16 __CpuProfilerEventSpecId;
		if (__CpuProfilerEventSpecId == 0)
		{
			__CpuProfilerEventSpecId = FCpuProfilerTrace::OutputEventType(TSTR::TStr(), CpuProfilerGroup_Default);
		}
		FCpuProfilerTrace::FEventScope __CpuProfilerEventScope(__CpuProfilerEventSpecId);
#endif
		//FRHICommandListImmediate& RHICmdList = GetImmediateCommandList_ForRenderCommand();
		Lambda(/*RHICmdList*/);
	}

//	FORCEINLINE_DEBUGGABLE TStatId GetStatId() const
//	{
//#if STATS
//		static struct FThreadSafeStaticStat<FStat_EnqueueUniqueRenderCommandType> StatPtr_EnqueueUniqueRenderCommandType;
//		return StatPtr_EnqueueUniqueRenderCommandType.GetStatId();
//#else
//		return TStatId();
//#endif
//	}

private:
#if STATS
	struct FStat_EnqueueUniqueRenderCommandType
	{
		typedef FStatGroup_STATGROUP_RenderThreadCommands TGroup;
		static FORCEINLINE const char* GetStatName()
		{
			return TSTR::CStr();
		}
		static FORCEINLINE const TCHAR* GetDescription()
		{
			return TSTR::TStr();
		}
		static FORCEINLINE EStatDataType::Type GetStatType()
		{
			return EStatDataType::ST_int64;
		}
		static FORCEINLINE bool IsClearEveryFrame()
		{
			return true;
		}
		static FORCEINLINE bool IsCycleStat()
		{
			return true;
		}
		static FORCEINLINE FPlatformMemory::EMemoryCounterRegion GetMemoryRegion()
		{
			return FPlatformMemory::MCR_Invalid;
		}
	};
#endif

private:
	LAMBDA Lambda;
};

#define FORCEINLINE_DEBUGGABLE __forceinline									/* Force code to be inline */

template<typename TSTR, typename LAMBDA>
FORCEINLINE_DEBUGGABLE void EnqueueUniqueRenderCommand(LAMBDA&& Lambda)
{
	typedef TEnqueueUniqueRenderCommandType<TSTR, LAMBDA> EURCType;

#if 0 // UE_SERVER && UE_BUILD_DEBUG
	UE_LOG(LogRHI, Warning, TEXT("Render command '%s' is being executed on a dedicated server."), TSTR::TStr())
#endif
	if (IsInRenderingThread())
	{
		//FRHICommandListImmediate& RHICmdList = GetImmediateCommandList_ForRenderCommand();
		//Lambda(RHICmdList);
	}
	else
	{
		if (ShouldExecuteOnRenderThread())
		{
			//CheckNotBlockedOnRenderThread();
			TGraphTask<EURCType>::CreateTask().ConstructAndDispatchWhenReady(Forward<LAMBDA>(Lambda));
		}
		else
		{
			EURCType TempCommand(Forward<LAMBDA>(Lambda));
			//FScopeCycleCounter EURCMacro_Scope(TempCommand.GetStatId());
			TempCommand.DoTask(ENamedThreads::GameThread, FGraphEventRef());
		}
	}
}

#define ENQUEUE_RENDER_COMMAND(Type) \
	struct Type##Name \
	{  \
		static const char* CStr() { return #Type; } \
		static const TCHAR* TStr() { return TEXT(#Type); } \
	}; \
	EnqueueUniqueRenderCommand<Type##Name>

template<typename LAMBDA>
FORCEINLINE_DEBUGGABLE void EnqueueUniqueRenderCommand(LAMBDA& Lambda)
{
	static_assert(sizeof(LAMBDA) == 0, "EnqueueUniqueRenderCommand enforces use of rvalue and therefore move to avoid an extra copy of the Lambda");
}


////////////////////////////////////
// Deferred cleanup
////////////////////////////////////

/**
 * The base class of objects that need to defer deletion until the render command queue has been flushed.
 */
class RENDERCORE_API FDeferredCleanupInterface
{
public:
	virtual ~FDeferredCleanupInterface() {}

	/*UE_DEPRECATED(4.20, "FinishCleanup is deprecated. Use RAII in the destructor instead.")
	virtual void FinishCleanup() final {}*/
};

/**
 * A set of cleanup objects which are pending deletion.
 */
class FPendingCleanupObjects
{
	TArray<FDeferredCleanupInterface*> CleanupArray;
public:
	FPendingCleanupObjects();
	RENDERCORE_API ~FPendingCleanupObjects();
};

/**
 * Adds the specified deferred cleanup object to the current set of pending cleanup objects.
 */
extern RENDERCORE_API void BeginCleanup(FDeferredCleanupInterface* CleanupObject);

/**
 * Transfers ownership of the current set of pending cleanup objects to the caller.  A new set is created for subsequent BeginCleanup calls.
 * @return A pointer to the set of pending cleanup objects.  The called is responsible for deletion.
 */
extern RENDERCORE_API FPendingCleanupObjects* GetPendingCleanupObjects();

////////////////////////////////////
// RenderThread scoped work
////////////////////////////////////

class RENDERCORE_API FRenderThreadScope
{
	typedef /*TFunction*/std::function<void(FRHICommandListImmediate&)> RenderCommandFunction;
	typedef TArray<RenderCommandFunction> RenderCommandFunctionArray;
public:
	FRenderThreadScope()
	{
		RenderCommands = new RenderCommandFunctionArray;
	}

	~FRenderThreadScope()
	{
		RenderCommandFunctionArray* RenderCommandArray = RenderCommands;

		ENQUEUE_RENDER_COMMAND(DispatchScopeCommands)(
			[RenderCommandArray](FRHICommandListImmediate& RHICmdList)
		{
			for(int32 Index = 0; Index < RenderCommandArray->Num(); Index++)
			{
				(*RenderCommandArray)[Index](RHICmdList);
			}

			delete RenderCommandArray;
		});
	}

	void EnqueueRenderCommand(RenderCommandFunction&& Lambda)
	{
		RenderCommands->Add(MoveTemp(Lambda));
	}

private:
	RenderCommandFunctionArray* RenderCommands;
};

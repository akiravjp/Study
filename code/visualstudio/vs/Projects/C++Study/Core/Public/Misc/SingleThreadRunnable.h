// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Public/CoreTypes.h"

/** 
 * Interface for ticking runnables when there's only one thread available and 
 * multithreading is disabled.
 */
class CORE_API FSingleThreadRunnable
{
public:

	virtual ~FSingleThreadRunnable() { }

	/* Tick function. */
	virtual void Tick() = 0;
};

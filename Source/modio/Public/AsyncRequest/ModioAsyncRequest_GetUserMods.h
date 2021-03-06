// Copyright 2020 modio. All Rights Reserved.
// Released under MIT.

#pragma once
#include "AsyncRequest/ModioAsyncRequest.h"
#include "Schemas/ModioResponse.h"
#include "Schemas/ModioMod.h"

/**
* Callback returning all the mods the authenticated user owns
* @param ModioResponse - Response from Modio backend
* @param Mods - Mods information retreived from mod.io
*/

class FModioAsyncRequest_GetUserMods : public FModioAsyncRequest
{
public:
  static void Response(void *Object, ModioResponse ModioResponse, ModioMod *ModioMods, u32 ModioModsSize);

protected:
  FModioAsyncRequest_GetUserMods( FModioSubsystem* Modio, FModioModArrayDelegate Delegate );

  /** This should be the only way to create and queue async requests */
  template<typename RequestType, typename CallbackType, typename... Params>
  friend RequestType* CreateAsyncRequest( FModioSubsystem* Subsystem, CallbackType CallbackDelegate, Params... Parameters );
private:
  FModioModArrayDelegate ResponseDelegate;
};
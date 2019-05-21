// Copyright 2019 modio. All Rights Reserved.
// Released under MIT.

#include "CallbackProxy_GetAllMods.h"
#include "ModioSubsystem.h"

UCallbackProxy_GetAllMods::UCallbackProxy_GetAllMods(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UCallbackProxy_GetAllMods *UCallbackProxy_GetAllMods::GetAllMods(UObject *WorldContext, TEnumAsByte<EModioFilterType> FilterType, int32 Limit, int32 Offset)
{
  UCallbackProxy_GetAllMods *Proxy = NewObject<UCallbackProxy_GetAllMods>();
  Proxy->SetFlags(RF_StrongRefOnFrame);
  Proxy->FilterType = FilterType;
  Proxy->Limit = Limit;
  Proxy->Offset = Offset;
  Proxy->WorldContextObject = WorldContext;
  return Proxy;
}

void UCallbackProxy_GetAllMods::Activate()
{
  UWorld* World = GEngine->GetWorldFromContextObject( WorldContextObject, EGetWorldErrorMode::LogAndReturnNull );
  FModioSubsystemPtr Modio = FModioSubsystem::Get( World );
  if( Modio.IsValid() )
  {
    Modio->GetAllMods( this->FilterType, this->Limit, this->Offset, FModioModArrayDelegate::CreateUObject( this, &UCallbackProxy_GetAllMods::OnGetAllModsDelegate ) );
  }
  else
  {
    // @todonow: Make something more pretty than this
    FModioResponse Response;
    TArray<FModioMod> Mods;
    OnFailure.Broadcast( Response, Mods );
  }
}

void UCallbackProxy_GetAllMods::OnGetAllModsDelegate(FModioResponse Response, const TArray<FModioMod> &Mods)
{
  if (Response.Code >= 200 && Response.Code < 300)
  {
    OnSuccess.Broadcast(Response, Mods);
  }
  else
  {
    OnFailure.Broadcast(Response, Mods);
  }
}
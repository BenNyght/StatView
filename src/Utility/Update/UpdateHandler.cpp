
#include "UpdateHandler.h"

#include "Implementations/IDraw.h"
#include "Implementations/IEarlyUpdate.h"
#include "Implementations/ILateUpdate.h"
#include "Implementations/IUpdate.h"

void UpdateHandler::Update()
{
    for (auto& updateObject : IEarlyUpdate::GetMapOfObjects()) 
    {
        updateObject.second->EarlyUpdate();
    }

    for (auto& updateObject : IUpdate::GetMapOfObjects()) 
    {
        updateObject.second->Update();
    }

    for (auto& updateObject : ILateUpdate::GetMapOfObjects()) 
    {
        updateObject.second->LateUpdate();
    }

    for (auto& updateObject : IDraw::GetMapOfObjects()) 
    {
        updateObject.second->Draw();
    }
}

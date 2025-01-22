-- Manges registering player avatar in system component

local PlayerAvatarRegistrar = 
{
    Properties =
    {
        -- Property definitions
    }
}

function PlayerAvatarRegistrar:OnActivate()
    -- Activation Code
    keywRequestBus.Broadcast.RegisterPlayerAvatar(self.entityId)
    Debug.Log("Registering player avatar id: "..tostring(self.entityId))
end

function PlayerAvatarRegistrar:OnDeactivate()
    -- Deactivation Code
end

return PlayerAvatarRegistrar
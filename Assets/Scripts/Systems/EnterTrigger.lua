local BuildingEnterTrigger = {
	Properties ={
		Roof= {default = EntityId()}
	}
}

function BuildingEnterTrigger:OnActivate()
	self.RigidBodyHandler = RigidBodyNotificationBus.Connect(self, self)
end


function BuildingEnterTrigger:OnPhysicsEnabled(entityId)
	Debug.Log("Physics enabled")
	BuildingEnterTrigger:TriggerEnter(self, entityId)
end

function BuildingEnterTrigger:TriggerEnter(sourceID, otherId)
	Debug.Log("Enter detected")
end

function BuildingEnterTrigger:OnDeactivate()
	self.RigidBodyHandler = RigidBodyNotificationBus:Disconnect()
end


return BuildingEnterTrigger
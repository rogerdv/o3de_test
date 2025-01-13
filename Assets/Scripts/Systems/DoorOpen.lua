local OpenDoor = {
	Properties = {
		--ScriptEventAsset = {default = ScriptEventsAssetRef()},
		Pivot= {default = EntityId()},
		Collider= {default = EntityId()}
	}
}

Open=false

function OpenDoor:OnActivate()
	--self.RigidBodyHandler = RigidBodyNotificationBus.Connect(self, self.Properties.Pivot)
	self.controller = DoorInteractEvent.Connect(self, self.entityId)
end


--function OpenDoor:OnPhysicsEnabled(entityId)
	--OpenDoor:TriggerEnter(self, entityId)
--end

function OpenDoor:DoorInteraction()	
	--TransformBus.Event.RotateAroundLocalZ(self.Properties.Pivot, 90)
	--[[Rot=TransformBus.Event.GetLocalRotation(self.Properties.Pivot)
	if Rot.z==0 then 
		TransformBus.Event.RotateAroundLocalZ(self.Properties.Pivot, 90)
	else 
		TransformBus.Event.RotateAroundLocalZ(self.Properties.Pivot, -90)
	end
	TransformBus.Event.SetLocalRotation(self.Properties.Pivot, Rot)]]
	
	
	if self.Open==false then
		TransformBus.Event.RotateAroundLocalZ(self.Properties.Pivot, 90)				
		TransformBus.Event.RotateAroundLocalZ(self.EntityId, 90)		
		self.Open=true
	else
		self.Open=false
		TransformBus.Event.RotateAroundLocalZ(self.Properties.Pivot, -90)
		TransformBus.Event.RotateAroundLocalZ(self.EntityId, -90)		
	end --if open
end

return OpenDoor
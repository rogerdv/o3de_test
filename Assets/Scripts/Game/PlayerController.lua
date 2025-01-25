-- DEals with moving the character 
local PlayerController = {
	Properties = {
		ScEventRef = {default=ScriptEventsAssetRef()},
		
		
	}
	
}

local path 
local PathIndex
local moving = false

function PlayerController:OnActivate()
	self.TickBusHandler = TickBus.Connect(self)		
	self.controller = GameEntityController.Connect(self, self.entityId)
	--self.inventory = InventoryNotificationsBus.Connect(self)
	self.ItemManage = ItemNotificationsBus.Connect(self, self.entityId)
	
end

function PlayerController:OnTick(dt, time)
	if self.moving then		
		pos = TransformBus.Event.GetWorldTranslation(self.entityId)
		distance = pos.GetDistance(pos, self.path[self.PathIndex])
		--Debug.Log("Distance t next ")
		--Debug.Log(tostring(distance))
		if pos.GetDistance(pos, self.path[self.PathIndex])<0.5 then			
			self.PathIndex=self.PathIndex+1
			if self.PathIndex>self.path:Size() then
				--reached last point in path
				AnimGraphComponentRequestBus.Event.SetParameterFloat(self.entityId,"Speed", 0.0)
				self.moving=false	--stop movement
				-- Go to idle animation				
				--Debug.Log("Stop")
				return
			end
			--Debug.Log("Moving to next point: ")
			--Debug.Log(tostring(self.PathIndex))
		end
		-- We are still far from destination point		
		local RotQuat = TransformBus.Event.GetWorldRotationQuaternion(self.entityId)
		local EulerAngle = RotQuat.GetEulerDegrees(RotQuat)
		local LookRotQuat= Transform.CreateLookAt(pos, self.path[self.PathIndex],2):GetRotation()	
		local LookEulerAngle = LookRotQuat.GetEulerDegrees(LookRotQuat)
		EulerAngle.z=LookEulerAngle.z
		RotQuat.SetFromEulerDegrees(RotQuat, EulerAngle)
		
		TransformBus.Event.SetWorldRotationQuaternion(self.entityId,RotQuat)
		--MoveOffset = pos:Lerp(self.path[self.PathIndex], dt)
		--MoveOffset =self.path[self.PathIndex]-pos
		velocity=self.path[self.PathIndex]-pos
		velocity=velocity.GetNormalized(velocity)*200*dt
		velocity.z=-9	--add gravity
		CharacterControllerRequestBus.Event.AddVelocity(self.entityId, velocity)
		--TransformBus.Event.SetWorldTranslation(self.entityId, MoveOffset)	
	end --moving
end --tick

function PlayerController:OnDeactivate()
	self.TickBusHandler:Disconnect()
end

function PlayerController:MoveTo(pos)
	local myPos = TransformBus.Event.GetWorldTranslation(self.entityId)
	self.path = DetourNavigationRequestBus.Event.FindPathBetweenPositions(self.entityId, myPos, pos)	
	--
	if self.path:Size() >0 then		
		--Debug.Log("Path size is ")
		--Debug.Log(tostring(self.path:Size()))		
		self.moving=true
		self.PathIndex=1
		AnimGraphComponentRequestBus.Event.SetParameterFloat(self.entityId,"Speed", 1.0)
	else
		Debug.Log("There is no path")
	end		
end

function PlayerController:SetNavmesh(NavmeshEntity)
	DetourNavigationRequestBus.Event.SetNavigationMeshEntity(self.entityId, NavmeshEntity)
end

function PlayerController:OnItemEquipped(ItemId)
	Debug.Log("Script received item equipped event for "..ItemId.." and my Id is "..tostring(self.entityId))
	local me = CharacterComponentBus.Event.GetName(self.entityId)
	--Debug.Log("And my name is "..me)
	item = keywRequestBus.Broadcast.GetItem(ItemId)
	self.EventScript = require("assets.scripts.equiptest")
			
	
end

return PlayerController
local GameEntity = {
	Properties = {		
		Name="",				
		attribs = {10,10,10,10,10}
		
	}
}


local dead=false
local HitPoints 
local EnergyPoints
local target= EntityId()

function GameEntity:OnActivate() 
	self.TickBusHandler = TickBus.Connect(self)	
	self.controller = GameEntityEvents.Connect(self, self.entityId)
	self.HitPoints={}
	self.EnergyPoints={}
	self:RecalculateStats()
	CharacterInventoryBus.Event.ReceiveItem(self.entityId,"aa")
	local w = CharacterInventoryBus.Event.TotalWeight(self.entityId)
	Debug.Log("Total weight"..tostring(w))
end

function GameEntity:RecalculateStats()
	
	self.HitPoints["max"]=self.Properties.attribs[4]*10
	self.HitPoints["current"]=self.HitPoints["max"]
	
end

function GameEntity:OnTick(dt, time)
	if self.dead then
		return
	end	
	if self.HitPoints["current"]<=0 and not self.dead then
		self.dead=true
		return
	end
	--Calculate regeneration and such
end --tick

function GameEntity:GetAttribute(attr, base)
	return self.Properties.attribs[attr]
end

function GameEntity:SetAttribute(attr, value)
	self.Properties.attribs[attr]=value
end

function GameEntity:GetName()	
	--Debug.Log(self.Properties.Name)
	return self.Properties.Name
end

function GameEntity:GetCurrentHP()
	return self.HitPoints["current"]
end

function GameEntity:GetMaxHP()
	return self.HitPoints["max"]
end

function SetTarget(id)
	target = id
end

return GameEntity
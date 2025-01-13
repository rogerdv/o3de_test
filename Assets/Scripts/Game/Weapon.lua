local Weapon = {
	Properties ={
		Slot ={default=EntityId()},
		ScriptEventAsset = {default = ScriptEventsAssetRef()}
	}
}


function Weapon:OnActivate()
	self.controller = WeaponControl.Connect(self, self.entityId)
end

function Weapon:Equip(SlotId) 
	Debug.Log("Equip weapon")
	TransformBus.Event.SetParent(self.entityId, SlotId)
	TransformBus.Event.SetLocalTranslation(self.entityId, Vector3(0,0,0))
	--AttachmentComponentRequestBus.Event.Attach()
end

return Weapon
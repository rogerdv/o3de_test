local IngameUI ={
	Properties =  {
	ScriptEventAsset = {default = ScriptEventsAssetRef()}
	}

} 

function IngameUI:OnActivate()
	self.TickBusHandler = TickBus.Connect(self)		
	self.controller = IngameUIEvent.Connect(self, self.entityId)
	
end


function IngameUI:SetTargetInfo(TargetName, HPPercent)
	canvas = UiCanvasRefBus.Event.GetCanvas(self.entityId)
	NameTextEntity = UiCanvasBus.Event.FindElementByName(canvas, "TargetName")
	UiTextBus.Event.SetText(NameTextEntity,TargetName)
	--HpText = UiCanvasBus.Event.FindElementByName(canvas, "HP")
	HPImage = UiCanvasBus.Event.FindElementByName(canvas, "HpBar")
	UiImageBus.Event.SetFillAmount(HPImage, HPPercent)
	--UiTextBus.Event.SetText(HpText,HPPercent)
	
end

function IngameUI:OnTick(dt, time)
	--do nothing, for now
end 

function IngameUI:OnClickQuickSlot(slot)

end

return IngameUI
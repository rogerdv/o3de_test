-- NewComponent.lua

local MainMenu = 
{
    Properties =
    {
        -- Property definitions
        LevelPrefab = {default = SpawnableScriptAssetRef()},
        SpawnTicket = {default = EntitySpawnTicket()}
    }
}



function MainMenu:OnActivate()
    -- Activation Code
    self.canvas = UiCanvasRefBus.Event.GetCanvas(self.entityId)
	StartButton = UiCanvasBus.Event.FindElementByName(self.canvas, "BtStart")
    self.buttonHandler = UiButtonNotificationBus.Connect(self, StartButton)
end

function MainMenu:OnDeactivate()
    -- Deactivation Code
    self.buttonHandler:Disconnect()
end

function MainMenu:OnButtonClick()
    --UiCanvasManagerBus.Broadcast.LoadCanvas(self.Properties.canvasName)
    Debug.Log("Button was pressed")
    self.SpawnMediator = SpawnableScriptMediator()
	self.Properties.SpawnTicket = self.SpawnMediator:CreateSpawnTicket(self.Properties.LevelPrefab)
	--self.SpawnTicket = self.SpawnMediator:CreateSpawnTicket(self.Properties.SpawnTicket)
	self.SpawnableListener = SpawnableScriptNotificationsBus.Connect(self, self.Properties.SpawnTicket:GetId())
	self.SpawnMediator:SpawnAndParent(self.Properties.SpawnTicket, self.entityId)	
	UiCanvasAssetRefBus.Event.UnloadCanvas(self.entityId)
end

return MainMenu
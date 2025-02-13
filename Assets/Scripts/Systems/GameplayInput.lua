local GameplayInput = {
	Properties = {
		camera = {default = EntityId()},
		pivot = {default = EntityId(), description="Camera pivot"},		
		Navmesh = {default = EntityId()},
		Start = {default = EntityId(), description="Player starting point"},	
		UI = {default = EntityId()},		
		slot = {default = EntityId()},
		weapon = {default = EntityId()},
		wpref = {default=SpawnableScriptAssetRef(), description="Prefab reference"}
	}
}

local player
local PlayerStart

function GameplayInput:OnActivate()
	--val = keywRequestBus.Broadcast.GetValue()
	
	--Debug.Log("Value from sys component "..tostring(val))
	keywRequestBus.Broadcast.InitItemDb()
	--self.NavHandler = Navmesh.
	self.keywNot = keywNotificationBus.Connect(self)
	
	self.OnRClick = {}
	self.OnLClick = {}
	--Debug.Log("Gameplay activation")
	
	self.PlayerStart = TransformBus.Event.GetWorldTranslation(self.Properties.Start)
	--TransformBus.Event.SetWorldTranslation(self.Properties.player, PlayerStart)
	--GameEntityController.Event.SetNavmesh(self.player, self.Properties.Navmesh)
	
		
	self.OnRClick.OnPressed = function(_, value)	
		CharacterInventoryBus.Event.EquipByIndex(self.player, "Sword", self.player)					
		--TargetEvent.Event.TargetCall(self.Properties.target, 125)
		--local asset =ItemWeapon()
		--asset = keywRequestBus.Broadcast.GetItem("Sword")
		--Debug.Log("Item dmg "..tostring(asset.Dmg[1]))
		--asset:Equip()	
		
		--WeaponControl.Event.Equip(self.Properties.weapon, self.Properties.slot)
		--self.SpawnMediator = SpawnableScriptMediator()
		--self.SpawnTicket = self.SpawnMediator:CreateSpawnTicket(self.Properties.wpref)
		--self.SpawnTicket = self.SpawnMediator:CreateSpawnTicket(self.Properties.wpref)
		--self.SpawnableListener = SpawnableScriptNotificationsBus.Connect(self, self.SpawnTicket:GetId())
		--self.SpawnMediator:SpawnAndParent(self.SpawnTicket, self.Properties.slot)		
		
	end
	
	self.OnLClick.OnPressed = function(_, value)		
		
		local cursorPos = UiCursorBus.Broadcast.GetUiCursorPosition()
		local startPos = CameraRequestBus.Event.ScreenToWorld(self.Properties.camera, cursorPos, 0)
		--CameraRequestBus.Broadcast.ScreenToWorld(cursorPos, 0)
		local endPos = CameraRequestBus.Event.ScreenToWorld(self.Properties.camera, cursorPos, 1) 
		--CameraRequestBus.Broadcast.ScreenToWorld(cursorPos, 1)
		 -- ray/plane intersection
        local direction = (endPos - startPos):GetNormalized()
        physicsSystem = GetPhysicsSystem()
		sceneHandle = physicsSystem:GetSceneHandle(DefaultPhysicsSceneName)
		scene = physicsSystem:GetScene(sceneHandle)
		request = RayCastRequest()
		request.Start = startPos
		request.Direction = direction
		request.Distance = 100.0
		request.ReportMultipleHits = true
		hits = scene:QueryScene(request)		
		numHits = hits.HitArray:Size()		
		if numHits>0 then	
			for i = numHits, 1, -1 do					
				p=hits.HitArray[i]
				--EName=ComponentApplicationBus.Broadcast.GetEntityName(p.EntityId)
				--Debug.Log("entityHit: "..EName);
			
				if(TagComponentRequestBus.Event.HasTag(p.EntityId, Crc32("Interact")) == true) then			
					--Debug.Log("Clicked interactable")
					DoorInteractEvent.Event.DoorInteraction(p.EntityId)
					break
				elseif (TagComponentRequestBus.Event.HasTag(p.EntityId, Crc32("NPC")) == true) then
					target=CharacterComponentBus.Event.GetName(p.EntityId)					
					Hp=CharacterComponentBus.Event.GetCurrentHP(p.EntityId)
					HpMax=CharacterComponentBus.Event.GetMaxHP(p.EntityId)					
					IngameUIEvent.Event.SetTargetInfo(self.Properties.UI, target, Hp/HpMax*100)
					break
				else
					GameEntityController.Event.MoveTo(self.player, p.Position)					
				end --if Tag
			end--for
		end --if numhits			
        
	end

	self.RClickInputHandler = InputEventNotificationBus.Connect(self.OnRClick, InputEventNotificationId("RClick"))
	self.LClickInputHandler = InputEventNotificationBus.Connect(self.OnLClick, InputEventNotificationId("LClick"))
end

function GameplayInput:OnPlayerRegister()	
	self.player = keywRequestBus.Broadcast.GetPlayerAvatar()
	Debug.Log("Player entity Id is "..tostring(self.player))
	--Place camera and player in start point
	TransformBus.Event.SetWorldTranslation(self.player, self.PlayerStart)	
	TransformBus.Event.SetWorldTranslation(self.Properties.pivot, self.PlayerStart)
	CharacterInventoryBus.Event.ReceiveItem(self.player,"Sword")
	CharacterInventoryBus.Event.ReceiveItem(self.player,"Item 1")
	local w=0
	
	w=CharacterInventoryBus.Event.TotalWeight(self.player)
		
	Debug.Log("Player has "..tostring(w).." in the inventory") 
	
	
end

return GameplayInput
-- Handles the sections of game characters 

local CharacterModelManager ={
	Properties ={
		Head = {default =  EntityId(), description="Character Head Entity"},
		HeadMesh = {default="",description="Head model" }
	}
}

function OnActivate()
	
end

return CharacterModelManager
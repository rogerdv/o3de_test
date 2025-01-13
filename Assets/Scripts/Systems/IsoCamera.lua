local IsoCamera = {
	Properties = {
	}
}

delta=0.0

function IsoCamera:OnActivate()
     self.RotInputs = {}
     self.VScrollInputs = {}
     self.HScrollInputs = {}
     self.ZoomInputs = {}
    self.TickBusHandler = TickBus.Connect(self)

    self.RotInputs.OnHeld = function(_, value)
    	--Debug.Log("Rot Value ")
     	--Debug.Log(tostring(value))
        TransformBus.Event.RotateAroundLocalZ(self.entityId, value*self.delta)
    end
    
    self.VScrollInputs.OnHeld = function(_, value)
      --pos = TransformBus.Event.GetLocalX(self.entityId)
      --Debug.Log("VScroll Value ")
      --Debug.Log(tostring(value))
      rotation = TransformBus.Event.GetWorldRotationQuaternion(self.entityId)
      pos =Vector3(0,15,0)*value*self.delta
      MoveVec = rotation*pos
      
      TransformBus.Event.MoveEntity(self.entityId, MoveVec)
    end
    
    self.HScrollInputs.OnHeld = function(_, value)
      --pos = TransformBus.Event.GetLocalX(self.entityId)
      --Debug.Log("HScroll Value ")
      --Debug.Log(tostring(value))
      rotation = TransformBus.Event.GetWorldRotationQuaternion(self.entityId)
      pos =Vector3(15,0,0)*value*self.delta
      MoveVec = rotation*pos      
      
      TransformBus.Event.MoveEntity(self.entityId, MoveVec)
    end
    
    -- Mouse wheel zoom 
    self.ZoomInputs.OnHeld = function(_, value)
    	
     	local x = TransformBus.Event.GetChildren(self.entityId)
     	size = CameraRequestBus.Broadcast.GetFovDegrees()
     	local zv = value*self.delta*-0.1
     	--Debug.Log("Value ")
     	--Debug.Log(tostring(value))
     	if value>0 then
			if size>10 then
     			size = size+zv
     			end
     	else
     		if size<20 then
     			size = size+zv
     			end
		 
	    end --if value
	    CameraRequestBus.Broadcast.SetFovDegrees(size)	

		x = nil
    end

    self.RotInputHandler = InputEventNotificationBus.Connect(self.RotInputs, InputEventNotificationId("CamRotate"))
    self.VScrollInputHandler = InputEventNotificationBus.Connect(self.VScrollInputs, InputEventNotificationId("CamVScroll"))
    self.HScrollInputHandler = InputEventNotificationBus.Connect(self.HScrollInputs, InputEventNotificationId("CamHScroll"))
    self.ZoomInputHandler = InputEventNotificationBus.Connect(self.ZoomInputs, InputEventNotificationId("CamZoom"))
end

function IsoCamera:OnTick(dt, time)
	self.delta=dt
end


function IsoCamera:OnDeactivate()
     self.RotInputHandler:Disconnect()
     self.VScrollInputHandler:Disconnect()
     self.HScrollInputHandler:Disconnect()
     self.ZoomInputHandler:Disconnect()
end

return IsoCamera
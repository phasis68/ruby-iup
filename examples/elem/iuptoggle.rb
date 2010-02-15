require 'rubygems'
require 'iup'

img_1 = [
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
]

img_2 = [
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,2,2,2,2,2,2,1,1,1,1,1,1,
  1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
]



toggle1cb = lambda do |ih,v|
  if(v == 1)
  	Iup.Message("Toggle 1","pressed") 
  else 
  	Iup.Message("Toggle 1","released") 
  end

  Iup::DEFAULT
end

  img1 = Iup.Image(16,16, img_1)
  img2 = Iup.Image(16,16, img_2)
  img1["1"] = "255 255 255" 
  img1["2"] = "0 192 0" 
  img2["1"] = "255 255 255" 
  img2["2"] = "0 192 0" 

  toggle1 = Iup.Toggle("toggle with image")
  toggle2 = Iup.Toggle("deactivated toggle with image")
  toggle3 = Iup.Toggle("regular toggle")
  toggle4 = Iup.Toggle("toggle with blue foreground color")
  toggle5 = Iup.Toggle("toggle with red background color")
  toggle6 = Iup.Toggle("toggle with black background color and green foreground color")
  toggle7 = Iup.Toggle("deactivated toggle")
  toggle8 = Iup.Toggle("toggle with Courier 14 Bold font")
  toggle9 = Iup.Toggle("toggle with size EIGHTxEIGHT")
	
  toggle1.action = toggle1cb
  
  toggle1.image = img1                  # Toggle 1 uses image                 
  toggle2.image = img2                  # Toggle 2 uses image                 
  toggle2.active = "NO"                 # Toggle 2 inactive                   
  toggle4.fgcolor = "0 0 255"           # Toggle 4 has blue foreground color  
  toggle5.bgcolor = "255 0 0"           # Toggle 5 has red background color   
  toggle6.fgcolor = "0 255 0"           # Toggle 6 has green foreground color 
  toggle6.bgcolor = "0 0 0"             # Toggle 6 has black background color 
  toggle7.active =  "NO"                # Toggle 7 inactive                   
  toggle8.font =    "COURIER_BOLD_14"   # Toggle 8 has Courier 14 Bold font   
  toggle9.size =    "EIGHTHxEIGHTH"     # Toggle 9 has size EIGHTxEIGHT       

  # Creating box that contains the toggles 
  caixa = 
    Iup.Vbox([
      toggle1, 
      toggle2, 
      toggle3, 
      toggle4, 
      toggle5, 
      toggle6, 
      toggle7, 
      toggle8, 
      toggle9])

  toggles = Iup.Radio( caixa ) # Grouping toggles 
  toggles.expand = "YES"

  # Dialog 
  dlg = Iup.Dialog(toggles)
  dlg.tile = "IupToggle" 
  dlg.attr = "MARGIN=5x5, GAP=5, RESIZE=NO" 

  # Associates a menu to the dialog 
  dlg.ShowXY(Iup::CENTER, Iup::CENTER) 
  Iup.MainLoop()
  dlg.Destroy()
  img1.Destroy
  img2.Destroy

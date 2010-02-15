require 'rubygems'
require 'iup'


  fill = Iup.Fill() 

  text = Iup.Text()

  text.attr = "EXPAND = YES, VALUE = \"Enter your text here\""
  
  # Creates a label 
  lbl = Iup.Label("This element is a label") 

  # Creatas a button 
  btn = Iup.Button("This button does nothing") 

	
  # Creates zbox with four elements 
  zbox = Iup.Zbox([fill, text, lbl, btn]) 

  # Creates handles for manipulating the zbox VALUE 
  zbox.fill = fill
  zbox.text = text
  zbox.lbl = lbl
  zbox.btn = btn

list_cb = lambda do |h,t, o, selected|
  if(selected == 1)
    zbox.value = zbox[t]
  end
  Iup::DEFAULT 
end

  # Sets zbox alignment 
  zbox.alignment = "ACENTER" 

  # Creates frame 
  frm = Iup.Frame(
    Iup.Hbox([
      Iup.Fill(),
      list = Iup.List(),
      Iup.Fill()])
  )

  # Creates dialog 
  dlg = Iup.Dialog(
    Iup.Vbox([
      frm,
      zbox])
  ) 

  list.attr = "1 = fill, 2 = text, 3 = lbl, 4 = btn"
  frm.title = "Select an element" 
  dlg.attr = "SIZE = QUARTER, TITLE = \"Iup.Zbox Example\"" 
  list.action = list_cb 

  dlg.ShowXY(Iup::CENTER, Iup::CENTER ) 
  Iup.MainLoop() 
  dlg.Destroy()
  

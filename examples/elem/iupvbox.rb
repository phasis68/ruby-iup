require 'rubygems'
require 'iup'

  # Creates frame 1 
  frm_1 = Iup.Frame(
    Iup.Hbox([
      Iup.Fill(),
      vbox_1 = Iup.Vbox([
        btn_11=Iup.Button("1"),
        btn_12=Iup.Button("2"),
        btn_13=Iup.Button("3")]),
      Iup.Fill()])
  ) 

  # Sets title of frame 1 
  frm_1.title = "ALIGNMENT = ALEFT, GAP = 10" 

  # Sets attributes of buttons inside frame 1 
  btn_11.size = "20x30" 
  btn_12.size = "30x30" 
  btn_13.size = "40x30" 

  # Sets attributes of vbox 1 
  vbox_1.attr = "ALIGNMENT = ALEFT, GAP = 10" 

  # Creates frame 2 
  frm_2 = Iup.Frame(
    Iup.Hbox([
      Iup.Fill(),
      vbox_2 = Iup.Vbox([
        btn_21 = Iup.Button("1"),
        btn_22 = Iup.Button("2"),
        btn_23 = Iup.Button("3")]),
      Iup.Fill()])
  )

  # Sets title of frame 1 
  frm_2.title = "ALIGNMENT = ACENTER, MARGIN = 15" 

  # Sets attributes of buttons inside frame 2 
  btn_21.size = "20x30" 
  btn_22.size = "30x30" 
  btn_23.size = "40x30" 

  # Sets attributes of vbox 2 
  vbox_2.attr = "ALIGNMENT = ACENTER, MARGIN = 15" 

  # Creates frame 3 
  frm_3 = Iup.Frame(
    Iup.Hbox([
      Iup.Fill(),
      vbox_3 = Iup.Vbox([
        btn_31=Iup.Button("1"),
        btn_32=Iup.Button("2"),
        btn_33=Iup.Button("3")]),
      Iup.Fill()])
  ) 

  # Sets title of frame 3 
  frm_3.title = "ALIGNMENT = ARIGHT, SIZE = 20"

  # Sets attributes of buttons inside frame 3 
  btn_31.size = "20x30" 
  btn_32.size = "30x30" 
  btn_33.size = "40x30" 

  # Sets attributes of vbox 3 
  vbox_3.attr = "ALIGNMENT = ARIGHT, SIZE = 20"

  # Creates dialog with three frames inside a vbo_ 
  dlg = Iup.Dialog(
    Iup.Vbox([
      frm_1,
      frm_2,
      frm_3])
  ) 

  # Sets title and size of the dialog 
  dlg.attr = "TITLE = \"Iup.Vbox Example\", SIZE = QUARTER"

  # Shows dialog in the center of the screen 
  dlg.ShowXY(Iup::CENTER, Iup::CENTER) 

  # Initializes IUP main loop 
  Iup.MainLoop() 

  dlg.Destroy()

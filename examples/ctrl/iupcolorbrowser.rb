require 'rubygems'
require 'iup'


  text_red = Iup.Text()
  text_green = Iup.Text()
  text_blue = Iup.Text()

  clrbrwsr_drag_cb = lambda do |h,r,g,b|
	text_red.value = r
	text_green.value = g
	text_blue.value = b
	Iup.LoopStep
	
	Iup::DEFAULT
  end
  
  clrbrwsr = Iup.ColorBrowser()
  clrbrwsr.drag_cb = clrbrwsr_drag_cb
  clrbrwsr.change_cb = clrbrwsr_drag_cb
  
  # Creates a vbox */
  vbox = Iup.Vbox([
           Iup.Fill(),
           text_red,
           Iup.Fill(),
           text_green,
           Iup.Fill(),
           text_blue,
           Iup.Fill()
           ])

  # Creates an hbox */
  hbox_final = Iup.Hbox([clrbrwsr, Iup.Fill(), vbox])

  # Creates a dialog */
  dlg = Iup.Dialog(hbox_final,:title=>"IupColorBrowser") 

  # Shows dialog in the center of the screen */
  dlg.ShowXY(Iup::CENTER, Iup::CENTER)

  # Initializes IUP main loop */
  Iup.MainLoop

  dlg.Destroy()

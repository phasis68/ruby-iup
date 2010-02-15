require 'rubygems'
require 'iup'

  # Creates frame with left aligned button */
  frame_left = Iup.Frame(
    Iup.Hbox([
      Iup.Button("Ok"),
      Iup.Fill()
     ]
    )
  ) 

  # Sets frame's title */
  frame_left.title = "Left aligned"  

  # Creates frame with centered button */
  frame_center = Iup.Frame(
    Iup.Hbox([
      Iup.Fill(),
      Iup.Button("Ok"),
      Iup.Fill()])
  ) 

  # Sets frame's title */
  frame_center.title = "Centered"  

  # Creates frame with right aligned button */
  frame_right = Iup.Frame(
    Iup.Hbox([
      Iup.Fill(),
      Iup.Button( "Ok", "" )])
  ) 

  # Sets frame's title */
  frame_right.title = "Right aligned"  

  # Creates dialog with these three frames */
  dialog = Iup.Dialog(
    Iup.Vbox([
      frame_left,
      frame_center,
      frame_right])
  ) 

  # Sets dialog's size and title */
  dialog.attr = "SIZE=120, TITLE=IupFill" 

  dialog.Show   # Shows dialog in the center of the screen */
  Iup.MainLoop       # Initializes IUP main loop */
  dialog.Destroy


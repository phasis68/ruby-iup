require 'rubygems'
require 'iup'

  # Creates frame with a label */
  frame = Iup.Frame(
            Iup.Hbox([
              Iup.Fill(),
              Iup.Label("IupFrame Attributes:\nFGCOLOR = \"255 0 0\"\nSIZE = \"EIGHTHxEIGHTH\"\nTITLE = \"This is the frame\"\nMARGIN = \"10x10\""),
              Iup.Fill()]
            )
          ) 

  # Sets frame's attributes */
  frame.attr = "FGCOLOR=\"255 0 0\", SIZE=EIGHTHxEIGHTH, TITLE=\"This is the frame\", MARGIN=10x10"

  # Creates dialog with these three frames */
  dialog = Iup.Dialog(frame)
   
  # Sets dialog's title */
  dialog.title = "IupFrame" 

  dialog.Show   # Shows dialog in the center of the screen */
  Iup.MainLoop       # Initializes IUP main loop */
  dialog.Destroy


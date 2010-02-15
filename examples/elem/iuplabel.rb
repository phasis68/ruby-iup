require 'rubygems'
require "iup"

# Global variables */
pixmap_star = [
  1,1,1,1,1,1,2,1,1,1,1,1,1,
  1,1,1,1,1,1,2,1,1,1,1,1,1,
  1,1,1,1,1,2,2,2,1,1,1,1,1,
  1,1,1,1,1,2,2,2,1,1,1,1,1,
  1,1,2,2,2,2,2,2,2,2,2,1,1,
  2,2,2,2,2,2,2,2,2,2,2,2,2,
  1,1,1,2,2,2,2,2,2,2,1,1,1,
  1,1,1,1,2,2,2,2,2,1,1,1,1,
  1,1,1,1,2,2,2,2,2,1,1,1,1,
  1,1,1,2,2,1,1,2,2,2,1,1,1,
  1,1,2,2,1,1,1,1,1,2,2,1,1,
  1,2,2,1,1,1,1,1,1,1,2,2,1,
  2,2,1,1,1,1,1,1,1,1,1,2,2
]
  # Creates the star image */
  img_star = Iup.Image( 13, 13, pixmap_star ) 

  # Sets star image colors */
  img_star["1"] = "0 0 0" 
  img_star["2"] = "0 198 0" 

  # Creates a label */
  lbl = Iup.Label( "This label has the following attributes set:\nBGCOLOR = 255 255 0\nFGCOLOR = 0 0 255\nFONT = COURIER_NORMAL_14\nSIZE = HALFxQUARTER\nTITLE = All text contained here\nALIGNMENT = ACENTER\n" )
  
  # Sets all the attributes of label lbl, except for IMAGE */
  lbl.attr = "BGCOLOR = \"255 255 0\", FGCOLOR = \"0 0 255\", FONT = COURIER_NORMAL_14, SIZE = HALFxQUARTER, ALIGNMENT = ACENTER"

  # Creates a label to explain that the label on the right has an image */
  lbl_explain = Iup.Label( "The label on the right has the image of a star" ) 

  # Creates a label whose title is not important, cause it will have an image */
  lbl_star = Iup.Label( "Does not matter" ) 

  # Associates image "img_star" with label lbl_star */
  lbl_star.image = img_star
  
  # Creates dialog with the label */
  dlg = Iup.Dialog(Iup.Vbox([ lbl, Iup.Hbox([ lbl_explain, lbl_star])])) 

  # Sets title of the dialog */
  dlg.title = "IupLabel Example"  

  # Shows dialog in the center of the screen */
  dlg.ShowXY(Iup::CENTER, Iup::CENTER ) 

  # Initializes IUP main loop */
  Iup.MainLoop( ) 

  dlg.Destroy()
  img_star.Destroy()



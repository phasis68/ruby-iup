require 'rubygems'
require 'iup'

  # Creates frame with three top aligned buttons */
  fr1 = Iup.Frame(
    h1=Iup.Hbox([
      Iup.Fill(),
      b11=Iup.Button("1"),
      b12=Iup.Button("2"),
      b13=Iup.Button("3"),
      Iup.Fill()]
    )
  )
  fr1.title = "ALIGNMENT=ATOP, GAP=10, SIZE=200"
  b11.size = "30x30"
  b12.size = "30x40"
  b13.size = "30x50"
  h1.attr = "ALIGNMENT=ATOP, GAP=10, SIZE=200"  # Sets hbox's alignment, gap and size */

  # Creates frame with three buttons */
  fr2 = Iup.Frame(
    h2=Iup.Hbox([
      Iup.Fill(),
      b21=Iup.Button("1"),
      b22=Iup.Button("2"),
      b23=Iup.Button("3"),
      Iup.Fill()]
    )
  )
  fr2.title = "ALIGNMENT=ACENTER, GAP=20"
  b21.size = "30x30"
  b22.size = "30x40"
  b23.size = "30x50"
  h2.attr = "ALIGNMENT=ACENTER, GAP=20"  # Sets hbox's alignment and gap */

  # Creates frame with three bottom aligned buttons */
  fr3 = Iup.Frame(
    h3=Iup.Hbox([
      Iup.Fill(),
      b31=Iup.Button("1"),
      b32=Iup.Button("2"),
      b33=Iup.Button("3"),
      Iup.Fill()]
    )
  )
  fr3.title = "ALIGNMENT = ABOTTOM, SIZE = 150"
  b31.size = "30x30"
  b32.size = "30x40"
  b33.size = "30x50"
  h3.attr = "ALIGNMENT = ABOTTOM, SIZE = 150"  # Sets hbox's alignment and size */

  # Creates dialog with the three frames */
  dialog = Iup.Dialog(
    Iup.Vbox([
      fr1,
      fr2,
      fr3]
    )
  )

  dialog.title = "IupHbox"  # Sets dialog's title */

  dialog.ShowXY(Iup::CENTER, Iup::CENTER )  # Shows dialog in the center of the screen */

  dialog.Show   # Shows dialog in the center of the screen */
  Iup.MainLoop       # Initializes IUP main loop */
  dialog.Destroy


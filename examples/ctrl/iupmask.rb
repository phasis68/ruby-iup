require 'rubygems'
require 'iup'

  text = Iup.Text()
  text.mask = "/d*"
  text.size = "100x"
  text.expand = "HORIZONTAL"

  dg = Iup.Dialog(text,:title=> "IupMask")

  dg.Show()
  Iup.MainLoop()
  dg.Destroy()

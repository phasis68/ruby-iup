require 'rubygems'
require 'iup'

  vbox1 = Iup.Vbox([Iup.Label("Inside Tab A"), Iup.Button("Button A")],:tabtitle=>"Tab A")
  vbox2 = Iup.Vbox([Iup.Label("Inside Tab B"), Iup.Button("Button B")],:tabtitle=>"Tab B")

  tabs1 = Iup.Tabs([vbox1, vbox2])

  vbox1 = Iup.Vbox([Iup.Label("Inside Tab C"), Iup.Button("Button C")],:tabtitle=>"Tab C")
  vbox2 = Iup.Vbox([Iup.Label("Inside Tab D"), Iup.Button("Button D")],:tabtitle=>"Tab D")

  tabs2 = Iup.Tabs([vbox1, vbox2],:tabtype=>"LEFT")

  box = Iup.Hbox([tabs1, tabs2],:margin=>"10x10",:gap=>10)

  dlg = Iup.Dialog(box,:title=>"IupTabs",:size=>"200x80")

  dlg.ShowXY(Iup::CENTER, Iup::CENTER)

  Iup.MainLoop()
  dlg.Destroy()


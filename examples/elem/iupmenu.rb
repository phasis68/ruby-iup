require 'rubygems'
require 'iup'

exit_cb = lambda do |ih|
  Iup::CLOSE
end

  item_open = Iup.Item("&Open")

  item_save = Iup.Item("&Save")

  item_undo = Iup.Item("&Undo")
  item_undo.active = "NO"

  item_exit = Iup.Item("E&xit")
  item_exit.action = exit_cb

  file_menu = Iup.Menu([item_open, 
                      item_save, 
                      Iup.Separator(),
                      item_undo,
                      item_exit])

  sub1_menu = Iup.Submenu("&File", file_menu)

  menu = Iup.Menu([sub1_menu])
  dg = Iup.Dialog(Iup.Canvas(""))
  dg.menu = menu

  dg.Show()
  Iup.MainLoop()
  dg.Destroy()

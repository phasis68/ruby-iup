require 'rubygems'
require "iup"

item_save_cb = lambda do |ih,*c|
  Iup.Message("Test","Saved!")
  Iup::DEFAULT
end

item_autosave_cb = lambda do |ih,*c|
  item_autosave = Iup.GetHandle("item_autosave")
  if (item_autosave.value=="ON")  
    Iup.Message("Auto Save","OFF")
    item_autosave.value = "OFF"
  else
    Iup.Message("Auto Save","ON")
    item_autosave.value = "ON"
  end
  
  Iup::DEFAULT
end

item_exit_cb = lambda do |ih,*c|
  return Iup::CLOSE
end

  text = Iup.Text(:value=>"This is an empty text")

  item_save = Iup.Item("Save\tCtrl+S")  # this is NOT related with the Ctrl+S key callback, it will just align the text at right */
  item_autosave = Iup.Item("&Auto Save")
  item_exit = Iup.Item("Exit")

  item_exit.key = "K_x"   # this is NOT related with the Ctrl+X key callback, it will just underline the letter */

  item_exit.action = item_exit_cb
  item_autosave.action = item_autosave_cb

  item_autosave.value = "ON"
  Iup.SetHandle("item_autosave", item_autosave) # giving a name to a iup handle */

  menu_file = Iup.Menu([item_save, item_autosave, item_exit])
  
  submenu_file = Iup.Submenu("File", menu_file)
  
  menu = Iup.Menu([submenu_file])
  
  Iup.SetHandle("menu", menu)
                                
  dlg = Iup.Dialog(Iup.Vbox([text, Iup.Button("Test")]))

  dlg.margin =  "10x10"
  dlg.gap = 10
  dlg.title = "IupItem"
  dlg.menu = "menu"
  dlg.K_cX = item_exit_cb   # this will also affect the Iup.Text if at focus, since it is used for clipboard cut */
  dlg.K_cA = item_autosave_cb  # this will also affect the Iup.Text if at focus, since it is used for select all */
  dlg.K_cS = item_save_cb

  dlg.ShowXY(Iup::CENTER, Iup::CENTER)
  Iup.MainLoop()
  dlg.Destroy()

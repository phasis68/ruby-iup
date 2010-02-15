require 'rubygems'
require 'iup'


quit_cb = lambda do |ih|
  Iup::CLOSE
end

  # Creating the button */ 
  quit_bt = Iup.Button("Quit", quit_cb)

  # the container with a label and the button */
  vbox = Iup.Vbox([
           Iup.Label(:title=>"Very Long Text Label",:attr=>"EXPAND=YES, ALIGNMENT=ACENTER"), 
           quit_bt 
           ],:alignment=>"ACENTER",:margin=>"10x10",:gap=>5)


  # Creating the dialog */ 
  dialog = Iup.Dialog(vbox,:title=>"Dialog Title")
  dialog.SetAttributeHandle("DEFAULTESC", quit_bt)

  dialog.Show()
  Iup.MainLoop()
  dialog.Destroy()

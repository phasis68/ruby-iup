require 'rubygems'
require 'iup'

def show_message()
  Iup.Message("Warning", "This item performs no operation\nIt is here only to compose") 
end

item_new_cb = lambda do |ih|
  show_message()   
  Iup::DEFAULT 
end

item_open_cb = lambda do |ih|
  show_message()  
  Iup::DEFAULT 
end

item_close_cb = lambda do |ih|
  show_message()   
  Iup::DEFAULT 
end
 
item_pagesetup_cb = lambda do |ih|
  show_message()   
  Iup::DEFAULT 
end

item_print_cb = lambda do |ih|
  show_message()   
  Iup::DEFAULT 
end

item_exit_cb = lambda do |ih|
  Iup::CLOSE 
end

  # Creates a text */
  text = Iup.Text() 
  
  # Sets value of the text and turns on expand */ 
  text.attr = "VALUE = \"This text is here only to compose\", EXPAND = YES" 
 
  # Creates six items */
  item_new = Iup.Item("New")
  item_open = Iup.Item("Open")
  item_close = Iup.Item("Close")
  item_pagesetup = Iup.Item("Page Setup")
  item_print = Iup.Item("Page Setup")
  item_exit = Iup.Item("Exit")

  # Registers callbacks */
  item_new.action = item_new_cb 
  item_open.action = item_open_cb 
  item_close.action = item_close_cb 
  item_pagesetup.action = item_pagesetup_cb 
  item_print.action = item_print_cb 
  item_exit.action = item_exit_cb 

  # Creates file menu */
  menu_file = Iup.Menu([item_new, item_open, item_close, Iup.Separator(), item_pagesetup, item_print, Iup.Separator(), item_exit]) 

  # Creates file submenu */
  submenu_file = Iup.Submenu("File", menu_file) 
  
  # Creates main menu with file menu */
  menu = Iup.Menu([submenu_file]) 
 
  # Creates dialog with a text */
  dlg = Iup.Dialog(text,:menu=>menu) 

  # Sets title and size of the dialog and associates a menu to it */
  dlg.attr = "TITLE=\"Iup.Separator Example\", SIZE = QUARTERxEIGHTH" 

  # Shows dialog in the center of the screen */
  dlg.ShowXY(Iup::CENTER, Iup::CENTER) 

  # Initializes IUP main loop */
  Iup.MainLoop() 

  dlg.Destroy()


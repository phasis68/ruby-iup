require 'rubygems'
require 'iup'

item_help_cb = lambda do |ih|
  Iup.Message("Warning", "Only Help and Exit items performs an operation") 
  
  Iup::DEFAULT 
end


item_exit_cb = lambda do |ih|
  Iup::CLOSE 
end

  # Creates a multiline */
  text = Iup.Text() 
  
  # Sets value of the text and turns on expand */ 
  text.attr = "VALUE = \"This text is here only to compose\", EXPAND = YES" 
     
  # Creates items of menu file */
  item_new = Iup.Item("New") 
  item_open = Iup.Item("Open") 
  item_close = Iup.Item("Close") 
  item_exit = Iup.Item("Exit", "item_exit_act") 

  # Creates items of menu edit */
  item_copy = Iup.Item("Copy") 
  item_paste = Iup.Item("Paste") 

  # Creates items for menu triangle */
  item_scalenus = Iup.Item("Scalenus") 
  item_isoceles = Iup.Item("Isoceles") 
  item_equilateral = Iup.Item("Equilateral") 

  # Create menu triangle */
  menu_triangle = Iup.Menu([item_equilateral, item_isoceles, item_scalenus]) 

  # Creates submenu triangle */
  submenu_triangle = Iup.Submenu("Triangle", menu_triangle) 

  # Creates items for menu create */
  item_line = Iup.Item("Line") 
  item_circle = Iup.Item("Circle") 

  # Creates menu create */
  menu_create = Iup.Menu([item_line, item_circle, submenu_triangle]) 

  # Creates submenu create */
  submenu_create = Iup.Submenu("Create", menu_create) 

  # Creates items of menu help */
  item_help = Iup.Item("Help", "item_help_act") 
  
  # Creates three menus */
  menu_file = Iup.Menu([item_new, item_open, item_close, Iup.Separator(), item_exit]) 
  menu_edit = Iup.Menu([item_copy, item_paste, Iup.Separator(), submenu_create])
  menu_help = Iup.Menu([item_help])

  # Creates three submenus */
  submenu_file = Iup.Submenu("File", menu_file) 
  submenu_edit = Iup.Submenu("Edit", menu_edit) 
  submenu_help = Iup.Submenu("Help", menu_help) 
  
  # Creates main menu with file menu */
  menu = Iup.Menu([submenu_file, submenu_edit, submenu_help]) 

  # Registers callbacks */
  item_help.action = item_help_cb 
  item_exit.action = item_exit_cb 
                                 
  # Creates dialog with a text */
  dlg = Iup.Dialog(text,:menu=>menu) 

  # Sets title and size of the dialog and associates a menu to it */
  dlg.attr = "TITLE=\"Iup.Submenu Example\", SIZE = QUARTERxEIGHTH" 

  # Shows dialog in the center of the screen */
  dlg.ShowXY(Iup::CENTER, Iup::CENTER) 

  # Initializes IUP main loop */
  Iup.MainLoop() 

  dlg.Destroy()


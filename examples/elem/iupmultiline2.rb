require 'rubygems'

require 'iup'



  # Creates a multiline, a text and a list*/ 
  mltline = Iup.MultiLine()   
  text = Iup.Text() 
  list = Iup.List() 

  # Turns on multiline expand ans text horizontal expand */
  mltline.expand = "YES" 
  text.expand = "HORIZONTAL" 

  # Sets list items and dropdown */
  list.attr = "1 = SET, 2 = GET, DROPDOWN = YES"


	set_attribute = lambda do |attribute|
	  mltline[attribute] = text.value
	
	  string_message = "Attribute #{attribute} set with value #{text.value}"
	  Iup.Message("Set attribute", string_message) 
	  Iup::DEFAULT 
	end
	
	get_attribute = lambda do |attribute|
	  text.value = mltline[attribute]
	
	  string_message = "Attribute #{attribute} get with value #{text.value}"
	  Iup.Message("Get attribute", string_message) 
	  Iup::DEFAULT 
	end

	btn_append_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::APPEND)  
	  else 
	  	get_attribute.call(Iup::APPEND) 
	  end
	
	  Iup::DEFAULT 
	end
	
	btn_insert_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::INSERT)  
	  else 
	  	get_attribute.call(Iup::INSERT) 
	  end
	  
	  Iup::DEFAULT 
	end
	
	btn_border_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::BORDER)  
	  else 
	  	get_attribute.call(Iup::BORDER) 
	  end
	  Iup::DEFAULT 
	end
	
	btn_caret_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::CARET)  
	  else 
	  	get_attribute.call(Iup::CARET) 
	  end
	  Iup::DEFAULT 
	end
	
	btn_readonly_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::READONLY)  
	  else 
	  	get_attribute.call(Iup::READONLY) 
	  end
	  Iup::DEFAULT 
	end
	
	btn_selection_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::SELECTION)  
	  else 
	  	get_attribute.call(Iup::SELECTION) 
	  end  
	  Iup::DEFAULT 
	end
	
	btn_selectedtext_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::SELECTEDTEXT)  
	  else 
	  	get_attribute.call(Iup::SELECTEDTEXT) 
	  end
	  Iup::DEFAULT 
	end
	
	btn_nc_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::NC)  
	  else 
	  	get_attribute.call(Iup::NC) 
	  end
	  Iup::DEFAULT 
	end
	
	btn_value_cb = lambda do |ih|
	  if(list.value == '1') 
	  	set_attribute.call(Iup::VALUE)  
	  else 
	  	get_attribute.call(Iup::VALUE) 
	  end  
	  Iup::DEFAULT 
	end

  # Creates buttons */
  btn_append = Iup.Button("Append") 
  btn_insert = Iup.Button("Insert") 
  btn_border = Iup.Button("Border") 
  btn_caret = Iup.Button("Caret") 
  btn_readonly = Iup.Button("Read only") 
  btn_selection = Iup.Button("Selection") 
  btn_selectedtext = Iup.Button("Selected Text") 
  btn_nc = Iup.Button("Number of characters") 
  btn_value = Iup.Button("Value") 

  # Registers callbacks */
  btn_append.action = btn_append_cb 
  btn_insert.action = btn_insert_cb 
  btn_border.action = btn_border_cb 
  btn_caret.action = btn_caret_cb 
  btn_readonly.action = btn_readonly_cb 
  btn_selection.action = btn_selection_cb 
  btn_selectedtext.action = btn_selectedtext_cb 
  btn_nc.action = btn_nc_cb 
  btn_value.action = btn_value_cb 

  # Creates dialog */
  dlg = Iup.Dialog(Iup.Vbox([mltline, 
                   Iup.Hbox([text, list]),
                   Iup.Hbox([btn_append, btn_insert, btn_border, btn_caret, btn_readonly, btn_selection]),
                   Iup.Hbox([btn_selectedtext, btn_nc, btn_value])])) 

  # Sets title and size of the dialog */
  dlg.attr = "TITLE=\"Iup.MultiLine Example\", SIZE=HALFxQUARTER"

  # Shows dialog in the center of the screen */
  dlg.ShowXY(Iup::CENTER, Iup::CENTER) 

  # Initializes IUP main loop */
  Iup.MainLoop() 

  dlg.Destroy()

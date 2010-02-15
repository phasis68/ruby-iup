require 'rubygems'
require 'iup'

  password = ""

  pwd = Iup.Text(:readonly=>"YES",:size=>"200x")

	k_any = lambda do |ih, c|
	  case c
	    when
	     Iup::K_CR,
	     Iup::K_SP,
	     Iup::K_ESC,
	     Iup::K_INS,
	     Iup::K_DEL,
	     Iup::K_TAB,
	     Iup::K_HOME,
	     Iup::K_UP,
	     Iup::K_PGUP,
	     Iup::K_LEFT,
	     Iup::K_MIDDLE,
	     Iup::K_RIGHT,
	     Iup::K_END,
	     Iup::K_DOWN,
	     Iup::K_PGDN
	      return Iup::IGNORE
	    else
	      return Iup::DEFAULT
	  end
	end
	
	action = lambda do |ih, c, after|
	  size = password.size
	  case c  
	    when Iup::K_BS
	      if (size==0)
	        return Iup::IGNORE
	      end
	      password.chop!
	      pwd.value = password
	      return Iup::DEFAULT
	    else
	      if (k_any.call(ih, c) == Iup::IGNORE)
	        return Iup::IGNORE
	      end
	      password += c.chr
	  end
	  pwd.value = password
	  Iup::K_asterisk
	end
	

  text = Iup.Text(:size=>"200x",:action=>action,:k_any=>k_any)

  dlg = Iup.Dialog(Iup.Vbox([text, pwd]),:title=>"IupText")

  dlg.ShowXY(Iup::CENTER, Iup::CENTER)

  Iup.MainLoop()
  dlg.Destroy()


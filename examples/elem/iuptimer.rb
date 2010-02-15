require 'rubygems'
require 'iup'


  text = Iup.Label("Timer example")

  # Creating main dialog */
  dialog = Iup.Dialog(Iup.Vbox([text]),:title=>"timer example",:size=>"200x200")
  dialog.ShowXY(Iup::CENTER, Iup::CENTER)

  timer1 = Iup.Timer()
  timer2 = Iup.Timer()

	timer_cb = lambda do |n|
	  if(n == timer1)
	    puts("timer 1 called")
	  end
	  if(n == timer2)
	    puts("timer 2 called")
	    return Iup::CLOSE  
	  end
	
	  Iup::DEFAULT
	end

  timer1.time = 100
  timer1.run = "YES"
  timer1.action_cb = timer_cb
        
  timer2.time = 400
  timer2.run = "YES"
  timer2.action_cb = timer_cb

  Iup.MainLoop()
  timer1.Destroy()
  timer2.Destroy()

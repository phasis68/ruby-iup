require 'rubygems'

require 'iup'

calc = {}


  text = Iup.Text(:size=>"100x20")

	calc_end = lambda do
	  Iup.SetIdle(nil)
	  Iup::DEFAULT
	end
	
	idle_function = lambda do 
	  # Iup::TITLE value for IUP */
	  sleep 0.01
	  calc[:passo]+= 1 # next iteration step */
	  calc[:fatorial] *= calc[:passo] # executes one computation step */
	
	  # feedback to the user on the current step and the last computed value */
	  str = "%d -> %10.4g" % [calc[:passo],calc[:fatorial]]
	  text.value = str
	
	  if(calc[:passo] == 100) # computation ends when step = 100 */
	    calc_end.call
	  end
	  Iup::DEFAULT
	end

	calc_begin = lambda do |ih|
	  calc[:passo] = 0
	  calc[:fatorial] = 1.0
	  Iup.SetIdle(idle_function)
	  text.value = "Computing..."
	  Iup::DEFAULT
	end

  bt = Iup.Button(:title=>"Calcular",:action=>calc_begin)

  dg = Iup.Dialog(Iup.Vbox([text, bt]))
  
  dg.ShowXY(Iup::CENTER, Iup::CENTER)

  Iup.MainLoop()
  dg.Destroy()



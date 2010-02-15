require 'rubygems'
require 'iup'

  lbl_h = Iup.Label(:title=>"0",:alignment=>"ACENTER",:size=>"30x")
  lbl_v = Iup.Label(:title=>"0",:alignment=>"ACENTER",:size=>"30x")
  lbl_c = Iup.Label(:title=>"0",:alignment=>"ACENTER",:size=>"30x")
  
  
  dial_v = Iup.Dial(:type=>"VERTICAL",:unit=>"DEGREES",:size=>"100x100")
  dial_h = Iup.Dial(:type=>"HORIZONTAL",:density=>0.1)
  dial_c = Iup.Dial(:type=>"CIRCULAR")
  
  dlg = Iup.Dialog(
  	Iup.Hbox([
  		Iup.Fill(),
  		Iup.Vbox([
			Iup.Frame(
				Iup.Vbox([
					Iup.Hbox([
						Iup.Fill(),
						dial_v,
						Iup.Fill()
					]),
					Iup.Hbox([
						Iup.Fill(),
						lbl_v,
						Iup.Fill()
					])
				])
			),
			Iup.Fill(),
			Iup.Frame(
				Iup.Vbox([
					Iup.Hbox([
						Iup.Fill(),
						dial_h,
						Iup.Fill()
					]),
					Iup.Hbox([
						Iup.Fill(),
						lbl_h,
						Iup.Fill()
					])
				])
			),
			Iup.Fill(),
			Iup.Frame(
				Iup.Vbox([
					Iup.Hbox([
						Iup.Fill(),
						dial_c,
						Iup.Fill()
					]),
					Iup.Hbox([
						Iup.Fill(),
						lbl_c,
						Iup.Fill()
					])
				])
			),
			Iup.Fill()
		]),
		Iup.Fill()
  	])
  )
  dlg.title = "IupDial"
  
printdial = lambda do |c,a,color|
  case c['type']
  when 'VERTICAL'
    label = lbl_v
  when 'HORIZONTAL'
    label = lbl_h
  when 'CIRCULAR'
    label = lbl_c
  end

  if label
    label.title = "%.3g" % a
    label.bgcolor = color
  end
end
  
mousemove = lambda do |c,a|
  printdial.call(c, a, "0 255 0")
  Iup::DEFAULT
end

button_press = lambda do |c,a|
  printdial.call(c, a, "255 0 0")
  Iup::DEFAULT
end 

button_release = lambda do |c,a|
  printdial.call(c, a,nil)
  Iup::DEFAULT
end 
  
  dial_v.button_press_cb = button_press
  dial_c.button_press_cb = button_press
  dial_h.button_press_cb = button_press

  dial_v.button_release_cb = button_release
  dial_c.button_release_cb = button_release
  dial_h.button_release_cb = button_release

  dial_v.mousemove_cb = mousemove
  dial_c.mousemove_cb = mousemove
  dial_h.mousemove_cb = mousemove

  # Shows dialog in the center of the screen */
  dlg.ShowXY(Iup::CENTER, Iup::CENTER)

  # Initializes IUP main loop */
  Iup.MainLoop

  dlg.Destroy

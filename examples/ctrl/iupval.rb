require 'rubygems'
require 'iup'

  val_v = Iup.Val("VERTICAL")
  val_h = Iup.Val("HORIZONTAL")
  lbl_v = Iup.Label(:title=>"VALUE=",:size=>"50x")
  lbl_h = Iup.Label(:title=>"VALUE=",:size=>"50x")
  val_v.showticks = 5

  dlg_val = Iup.Dialog(
    Iup.Hbox([
        Iup.Hbox([val_v,lbl_v],:alignment=>"ACENTER"),
        Iup.Vbox([val_h,lbl_h],:alignment=>"ACENTER")])
  )

mousemove = lambda do |c,a|
  buffer =  "VALUE=%.2g" % a

  case(c.type)  
    when 'VERTICAL'
      lbl_v.title = buffer
    when 'HORIZONTAL'
      lbl_h.title = buffer
  end

  Iup::DEFAULT
end

button_press = lambda do |c,a|
  case(c.type)  
    when 'VERTICAL'
      lbl_v.fgcolor = "255 0 0"
    when 'HORIZONTAL'
      lbl_h.fgcolor = "255 0 0"
  end

  mousemove.call(c, a)

  Iup::DEFAULT
end

button_release = lambda do |c,a|
  type = c.type
  
  case(type = c.type)  
    when 'VERTICAL'
      lbl_v.fgcolor = "0 0 0"
    when 'HORIZONTAL'
      lbl_h.fgcolor = "0 0 0"
  end

  mousemove.call(c, a)

  Iup::DEFAULT
end


  val_v.button_press_cb = button_press
  val_v.button_release_cb = button_release
  val_v.mousemove_cb = mousemove 
       
  val_h.button_press_cb =  button_press
  val_h.button_release_cb =  button_release
  val_h.mousemove_cb = mousemove 

  dlg_val.title = "IupVal"
  dlg_val.margin = "10x10"
  dlg_val.ShowXY(Iup::CENTER,Iup::CENTER)

  Iup.MainLoop
  dlg_val.Destroy

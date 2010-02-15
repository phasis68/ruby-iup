# IupCanvas Redraw example

require 'rubygems'
require 'iup'

need_redraw = 0
redraw_count = 0
cdcanvas = nil


  gauge = Iup.ProgressBar()
  cv    = Iup.Canvas()
  bt    = Iup.Button("Start/Stop")
  bt.size = "50x50"
  gauge.size = "200x15"
  cv.size = "200x200"
  dlg   = Iup.Dialog(Iup.Vbox([cv, Iup.Hbox([gauge, bt])]),:title=>"Redraw test")

toggle_redraw = lambda do |ih|
  cdcanvas.CanvasActivate() if cdcanvas
  need_redraw = 1 - need_redraw
  Iup::DEFAULT
end

redraw = lambda do
  if(need_redraw == 1)
      cdcanvas.CanvasBox(0, 300, 0, redraw_count/100)
      gauge.value = redraw_count/30000.0
      redraw_count += 1
      if(redraw_count==30000)
        cdcanvas.CanvasClear()
        redraw_count = 0
        need_redraw = 0
      end
  end      
  Iup::DEFAULT
end


  Iup.SetIdle(redraw)

  dlg.Map()
  
  cdcanvas = Cd.CreateCanvas(Cd.CD_IUP, cv) 
  cdcanvas.CanvasForeground(Cd::BLUE)
  cdcanvas.CanvasClear()
    
  bt.action = toggle_redraw

  dlg.ShowXY(Iup::CENTER, Iup::CENTER)
  Iup.MainLoop()
  dlg.Destroy()

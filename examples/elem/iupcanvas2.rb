# Advanced IupCanvas example
# Description : This example shows how several canvas callbacks are used and how the scrollbar works.
#      Remark : IUP must be linked to the CD library                      

require 'rubygems'
require 'iup'


  image = []
  for x in 0...640
    image[x] = []
    for y in 0...400
      image[x][y]=0
    end
  end

  label = Iup.Label("IupCanvas")

  iupcanvas = Iup.Canvas()
  iupcanvas.attr = "CURSOR=CROSS, RASTERSIZE=320x200, EXPAND=NO, SCROLLBAR=YES, DX=0.5, DY=0.5"

repaint_cb = lambda do |ih,x,y|
  sx = ih.posx.to_f
  sy = -ih.posy.to_f

  cdcanvas = Cd.ActiveCanvas()
  return Iup::DEFAULT if cdcanvas == nil

  cdcanvas.CanvasClear()

  for x in 0...320
    for y in 0...200
      cdcanvas.CanvasMark(x,y) if(image[(320.0*sx).to_i+x][(200.0*sy).to_i+y]!=0)
    end
  end
  Iup::DEFAULT
end

button_cb = lambda do |ih, botao, estado, x, y,status|
  sx = ih.posx.to_f
  sy = -ih.posy.to_f

  cdcanvas = Cd.ActiveCanvas()
  y = cdcanvas.CanvasUpdateYAxis(y)
  if(botao == Iup::BUTTON1 && estado!=0)
    cdcanvas.CanvasMark(x,y)
    image[(320.0*sx).to_i+x][(200.0*sy).to_i+y] = 1
  end

  Iup::DEFAULT
end

motion_cb = lambda do |ih,  x,  y,status|
  sx = ih.posx.to_f

  sy = -ih.posy.to_f

  buffer = "(#{(320.0*sx).to_i+x}, #{(200.0*sy).to_i+y})"

  label.title = buffer

  Iup::DEFAULT
end

scroll_cb = lambda do |ih,op,posx,posy|
  repaint_cb.call(ih,0.0,0.0)

  Iup::DEFAULT
end

enter_cb = lambda do |ih|
  Cd.Background(Cd::WHITE)
  repaint_cb.call(ih,0.0,0.0)

  Iup::DEFAULT
end

leave_cb = lambda do |ih|
  Cd.Background(Cd::GRAY)
  repaint_cb.call(ih,0.0,0.0)
  label = Iup.GetHandle("label")
  label.title = "IupCanvas"

  Iup::DEFAULT
end

  iupcanvas.action = repaint_cb
  iupcanvas.button_cb = button_cb
  iupcanvas.scroll_cb = scroll_cb
  iupcanvas.motion_cb = motion_cb
  iupcanvas.enterwindow_cb = enter_cb
  iupcanvas.leavewindow_cb = leave_cb

  dlg = Iup.Dialog(Iup.Vbox([iupcanvas,Iup.Hbox([Iup.Fill(), label, Iup.Fill()])]))
  dlg.attr = "TITLE=IupCanvas, RESIZE=NO, MAXBOX=NO"

  dlg.ShowXY(Iup::CENTER,Iup::CENTER)

  cdcanvas = Cd.CreateCanvas(Cd.CD_IUP, iupcanvas)
  if(cdcanvas==nil)
    Iup.Message("IupCanvas","Error creating canvas")
    dlg.Destroy
    exit
  end

  if(cdcanvas.Activate() == Cd::ERROR)
    Iup.Message("IupCanvas","Error creating canvas")
    dlg.Destroy
    exit
  end

  cdcanvas.CanvasClear
  Iup.MainLoop
  dlg.Destroy

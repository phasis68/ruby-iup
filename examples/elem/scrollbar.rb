require 'rubygems'
require 'iup'


cdcanvas = nil

action = lambda do |ih,  posx,  posy|

  iposx = posx.to_i
  iposy = posy.to_i
  # invert scroll reference (YMAX - DY - POSY) 
  iposy = 399 - ih.dy.to_i - iposy
  
  cdcanvas.CanvasClear()
  
  cdcanvas.CanvasForeground(Cd::RED)
  cdcanvas.CanvasLine(0-iposx, 0-iposy, 599-iposx, 399-iposy)
  cdcanvas.CanvasLine(0-iposx, 399-iposy, 599-iposx, 0-iposy)

  Iup::DEFAULT
end

scroll_cb = lambda do |ih,  op,  posx,  posy|
  action.call(ih, posx, posy)
  Iup::DEFAULT
end

resize_cb = lambda do |ih,  w,  h|
  return Iup::DEFAULT if cdcanvas==nil
  # update CD canvas size 
  cdcanvas.CanvasActivate()
 
  # update page size, it is always the client size of the canvas 
  ih.dx = w
  ih.dy = h
  
  # refresh scroolbar in IUP 2.x 
  ih.posx = ih.posx
  ih.posy = ih.posy
  return Iup::DEFAULT
end

  canvas = Iup.Canvas()
  canvas.rastersize = "300x200" # initial size 
  canvas.scrollbar = "YES"
  canvas.xmax = 599
  canvas.ymax = 399

  canvas.scroll_cb =  scroll_cb
  canvas.resize_cb =  resize_cb
  canvas.action =  action
                   
  dialog = Iup.Dialog(canvas)
  dialog.title = "Scrollbar Test"

  dialog.Map()
  cdcanvas = Cd.CreateCanvas(Cd.CD_IUP, canvas)
  canvas.rastersize = nil  # release the minimum limitation 
  
  dialog.ShowXY(Iup::CENTER,Iup::CENTER)

  Iup.MainLoop()

  cdcanvas.KillCanvas()
  dialog.Destroy()


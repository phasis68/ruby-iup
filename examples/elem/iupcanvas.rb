# IupCanvas example
# Description : Creates a IUP canvas and uses CD to draw on it
#      Remark : IUP must be linked to the CD library           
           
require 'rubygems'
require 'iup'


cdcanvas = nil

repaint_cb = lambda do |ih,x,y|
  cdcanvas.CanvasActivate()
  cdcanvas.CanvasBackground(Cd::BLACK)
  cdcanvas.CanvasClear()
  cdcanvas.CanvasForeground(Cd::BLUE)
  cdcanvas.CanvasBox(0, 100, 0, 100)
  Iup::DEFAULT
end

  cnvs = Iup.Canvas(:action=>repaint_cb,:size=>"300x100")  
  dlg = Iup.Dialog(Iup.Frame(cnvs),:title=>"IupCanvas + Canvas Draw" )
  dlg.Map
  
  cdcanvas = Cd.CreateCanvas( Cd.CD_IUP, cnvs )
  
  dlg.ShowXY(Iup::CENTER, Iup::CENTER )
    
  Iup.MainLoop()
  dlg.Destroy()

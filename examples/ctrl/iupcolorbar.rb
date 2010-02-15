require 'rubygems'
require 'iup'


cdcanvas = nil

  repaint_cb = lambda do |h,posx,posy|
	return Iup::DEFAULT if cdcanvas==nil
	
	cdcanvas.CanvasActivate()
	cdcanvas.CanvasClear()
	
	cdcanvas.CanvasBegin(Cd::FILL)
	cdcanvas.CanvasVertex(50,50)
	cdcanvas.CanvasVertex(150,50)
	cdcanvas.CanvasVertex(100,150)
	cdcanvas.CanvasEnd()
	
	Iup::DEFAULT
  end


  cb = Iup.Colorbar() 
  cb.rastersize = "70x"
  cb.expand = "VERTICAL"
  cb.num_parts = 2
  cb.show_secondary = "YES"
  cb.preview_size = 60  
  cb.squared = "NO"
  
  cnvs = Iup.Canvas() 
  cnvs.action = repaint_cb
  
  # Sets size, mininum and maximum values, position and size of the thumb   
  # of the horizontal scrollbar of the canvas                               
  cnvs.rastersize = "200x300"

  cb.select_cb = lambda do |h,cell,type|
	ri,gi,bi = h["CELL#{cell}"].scan(/\d+/)
	cd_color = Cd.EncodeColor(ri.to_i,gi.to_i,bi.to_i)
	
	cdcanvas.CanvasActivate()
	if (type==Iup::PRIMARY)
		cdcanvas.CanvasSetForeground(cd_color)
	else
		cdcanvas.CanvasSetBackground(cd_color)
	end
	repaint_cb.call(nil,0,0)
	
	Iup::DEFAULT 
  end

  cb.cell_cb = lambda do |h,cell|
	ri,gi,bi = h["CELL#{cell}"].scan(/\d+/)
	res = Iup.GetColor(Iup::MOUSEPOS, Iup::MOUSEPOS)
	if res
		r,g,b = res
		str = "#{r} #{g} #{b}"
		cdcanvas.CanvasActivate()
		cdcanvas.CanvasSetForeground(Cd.EncodeColor(r,g,b))
		repaint_cb.call(nil,0,0)
		return str
	end
	nil 
  end
  
  cb.switch_cb = lambda do |h,primcell,seccell|
	cdcanvas.CanvasActivate()
	fgcolor = cdcanvas.CanvasForeground(Cd::QUERY)
	cdcanvas.CanvasSetForeground(Cd.CanvasBackground(Cd::QUERY))
	cdcanvas.CanvasSetBackground(fgcolor)
	repaint_cb.call(nil,0,0)
  end


  # Creates a dialog with a vbox containing the canvas and the colorbar. 
  dlg = Iup.Dialog(Iup.Hbox([cnvs,cb]))
  
  # Sets the dialog's title, so that it is mapped properly 
  dlg.title = "IupColorbar"
  
  # Maps the dialog. This must be done before the creation of the CD canvas 
  dlg.Map

  # Creates a CD canvas of type CD_IUP  
  cdcanvas = Cd.CreateCanvas(Cd.CD_IUP, cnvs)

  # Shows dialog on the center of the screen 
  dlg.Show

  # Initializes IUP main loop 
  Iup.MainLoop

  dlg.Destroy


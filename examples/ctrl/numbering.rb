require 'rubygems'
require 'iup'


def create() 
	nlines_cb = lambda {|h| 20 }
	ncols_cb = lambda {|h| 50 }
	height_cb = lambda {|h,i| 30 }
	width_cb = lambda {|h,j| 70 } 
	mouseclick_cb = lambda do |h,b,m,i,j,x,y,r| 
	  Iup.Message("Hi!","CLICK: #{b}: (#{i}, #{j})")
	  Iup::DEFAULT
	end
	
	draw_cb = lambda do |h,i,j,xmin,xmax,ymin,ymax,cnv|
	  xm = (xmax + xmin) / 2
	  ym = (ymax + ymin) / 2
	
	  cnv.CanvasSetForeground(Cd.EncodeColor((i*20),(j*100),(i+100)))
	  cnv.CanvasBox(xmin, xmax, ymin, ymax)
	  cnv.CanvasTextAlignment(Cd::CENTER)
	  cnv.CanvasSetForeground(Cd::BLACK)
	  cnv.CanvasText(xm, ym, "(#{i}, #{j})")
	
	  Iup::DEFAULT
	end
	
	cells = Iup.Cells() 
	cells.mouseclick_cb = mouseclick_cb
	cells.draw_cb = draw_cb
	cells.width_cb = width_cb
	cells.height_cb = height_cb
	cells.nlines_cb = nlines_cb
	cells.boxed = "NO"
	cells
end

  cells = create()
  dlg = Iup.Dialog(cells) 

  dlg.rastersize = "500x500"
  dlg.title = "IupCells"
  
  dlg.ShowXY(Iup::CENTER,Iup::CENTER) 
  Iup.MainLoop 
  dlg.Destroy

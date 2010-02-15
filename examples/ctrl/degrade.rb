require 'rubygems'
require 'iup'


def create() 
  cells = Iup.Cells() 
  cells.mouseclick_cb = lambda {|h,b,m,i,j,x,y,r|
  	puts("CLICK: #{b}: (#{i}, #{j})")
  	Iup::DEFAULT
  }

  cells.draw_cb = lambda {|h,i,j,xmin,xmax,ymin,ymax,cnv|
	  xm = (xmax + xmin) / 2
	  ym = (ymax + ymin) / 2
	  buffer = 0.chr * 64
	
	  return Iup::DEFAULT if (i == 1 && j == 2)
	  return Iup::DEFAULT if (i == 2 && j == 1)
	  return Iup::DEFAULT if (i == 2 && j == 2)
	  return Iup::DEFAULT if (i == 5 && j == 6)
	  return Iup::DEFAULT if (i == 6 && j == 5)
	  return Iup::DEFAULT if (i == 6 && j == 6)
	
	  if (i == 1 && j == 1) 
	  	cnv.CanvasSetForeground(Cd::WHITE)
	  else 
	    	cnv.CanvasSetForeground(Cd.EncodeColor(
	    		(i*20),(j*100),(i+100)))
	  end
	  cnv.CanvasBox(xmin, xmax, ymin, ymax)
	  cnv.CanvasTextAlignment(Cd::CENTER)
	  cnv.CanvasSetForeground(Cd::BLACK)
	  buffer = "(#{i}, #{j})"
	  cnv.CanvasText( xm, ym, buffer)
	
	  Iup::DEFAULT
  }
  
  cells.width_cb = lambda {|h,j| (50+j*1.5).to_i }
  cells.height_cb = lambda {|h,i| (30+i*1.5).to_i }
  cells.nlines_cb = lambda {|h| 7 }
  cells.ncols_cb = lambda {|h| 7 }
  cells.hspan_cb = lambda {|h,i,j| 
	  return 2 if (i == 1 && j == 1) 
	  return 2 if (i == 5 && j == 5) 
	  1
  }
  cells.vspan_cb = lambda {|h,i,j| 
	  return 2 if (i == 1 && j == 1)   
	  return 2 if (i == 5 && j == 5) 
	  1
  }  
  cells.scrolling_cb = lambda {|h,i,j| 
	  puts("SCROLL: (#{i}, #{j})");
	  Iup::DEFAULT
  }
  cells.boxed = 'NO'
  cells.rastersize = "395x255"

  return cells
end

  cells = create()
  box = Iup.Vbox([cells])
  box.margin = "10x10"

  dlg = Iup.Dialog(box) 
  dlg.title = "IupCells"
  dlg.rastersize = "350x250"
  dlg.ShowXY(Iup::CENTER,Iup::CENTER) 
  Iup.MainLoop 
  dlg.Destroy





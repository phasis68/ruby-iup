require 'rubygems'
require 'iup'


def create()
   cells = Iup.Cells()
   
   cells.draw_cb = lambda {|h,i,j,xmin,xmax,ymin,ymax,cnv|
	  if (((i%2)!=0 && (j%2)!=0) || (((i+1)%2)!=0 && ((j+1)%2)!=0)) 
		cnv.CanvasSetForeground(Cd::WHITE)
	  else 
		cnv.CanvasSetForeground(Cd::BLACK)
	  end
	  cnv.CanvasBox(xmin, xmax, ymin, ymax)

	  Iup::DEFAULT
   }
   cells.width_cb = lambda {|h,j| 50 }
   cells.height_cb = lambda {|h,i| 50 }
   cells.nlines_cb = lambda {|h| 8 }
   cells.ncols_cb = lambda {|h| 8 }

   return cells
end


   cells = create()
   dlg = Iup.Dialog(cells,:rastersize=>"440x480",:title=>"IupCells")

   dlg.ShowXY(Iup::CENTER,Iup::CENTER)
   Iup.MainLoop 
   dlg.Destroy


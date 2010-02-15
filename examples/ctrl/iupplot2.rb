require 'rubygems'
require 'iup'

MAXPLOT = 6  # room for examples

class IupPlotTest
	
	def InitPlots()

		delete_cb = lambda do |ih, index, sample_index, x, y|
		  puts("DELETE_CB(#{index}, #{sample_index}, #{x}, #{y})")
		  Iup::DEFAULT
		end
		
		select_cb = lambda do |ih, index, sample_index, x, y, select|
		  puts("SELECT_CB(#{index}, #{sample_index}, #{x}, #{y}, #{select})")
		  Iup::DEFAULT
		end
		
		edit_cb = lambda do |ih, index, sample_index, x, y,new_x,new_y|
		  puts("EDIT_CB(#{index}, #{sample_index}, #{x}, #{y}, #{new_x}, #{new_y})")
		  Iup::DEFAULT
		end
		
		postdraw_cb = lambda do |ih,cnv|
		  ix,iy = ih.PPlotTransform(0.003, 0.02)
		  cnv.CanvasFont(nil, Cd::BOLD, 10)
		  cnv.CanvasTextAlignment(Cd::SOUTH)
		  cnv.CanvasText(ix, iy, "My Inline Legend")
		  puts("POSTDRAW_CB()")
		  Iup::DEFAULT
		end
		
		predraw_cb = lambda do |ih, cnv|
		  puts("PREDRAW_CB()")
		  Iup::DEFAULT
		end
	
	  # PLOT 0 - MakeExamplePlot1
	  @plot[0].title = "AutoScale"
	  @plot[0].margintop = 40
	  @plot[0].marginleft = 40
	  @plot[0].marginbottom = 50
	  @plot[0].titlefontsize = 16
	  @plot[0].axs_xlabel = "gnu (Foo)"
	  @plot[0].axs_ylabel = "Space (m^3)"
	  @plot[0].axs_yfontsize = 7
	  @plot[0].axs_ytickfontsize = 7
	  @plot[0].legendshow = "YES"
	  @plot[0].axs_xfontsize = 10
	  @plot[0].axs_yfontsize = 10
	  @plot[0].axs_xlabelcentered = "NO"
	  @plot[0].axs_ylabelcentered = "NO"
	  
	#  @plot[0].use_imagergb = "YES"
	#  @plot[0].use_gdi = "YES"
	
	  theFac = 1.0/(100*100*100)
	  @plot[0].PPlotBegin(0)
	  for theI in -100..100
	    x = theI+50.0
	    y = theFac*theI*theI*theI
	    @plot[0].PPlotAdd(x, y)
	  end
	  @plot[0].PPlotEnd()
	  @plot[0].ds_linewidth = 3
	  @plot[0].ds_legend = "Line"
	
	  theFac = 2.0/100
	  @plot[0].PPlotBegin(0)
	  for theI in -100..100
	    x = 1.0*theI
	    y = -theFac*theI
	    @plot[0].PPlotAdd(x, y)
	  end
	  @plot[0].PPlotEnd()
	  @plot[0].ds_legend = "Curve 1"
	
	  @plot[0].PPlotBegin(0)
	  for theI in -100..100
	    x = 0.01*theI*theI-30
	    y = 0.01*theI;
	    @plot[0].PPlotAdd(x, y)
	  end
	  @plot[0].PPlotEnd()
	  @plot[0].ds_legend = "Curve 2"
	
	  # PLOT 1 - MakeExamplePlot2
	  @plot[1].title = "No Autoscale+No CrossOrigin"
	  @plot[1].titlefontsize = 16
	  @plot[1].margintop = 40
	  @plot[1].marginleft = 55
	  @plot[1].marginbottom = 50
	  @plot[1].bgcolor = "0 192 192"
	  @plot[1].axs_xlabel = "Tg (X)"
	  @plot[1].axs_ylabel = "Tg (Y)"
	  @plot[1].axs_xautomin = "NO"
	  @plot[1].axs_xautomax = "NO"
	  @plot[1].axs_yautomin = "NO"
	  @plot[1].axs_yautomax = "NO"
	  @plot[1].axs_xmin = 10
	  @plot[1].axs_xmax = 60
	  @plot[1].axs_ymin = -0.5
	  @plot[1].axs_ymax = 0.5
	  @plot[1].axs_xcrossorigin = "NO"
	  @plot[1].axs_ycrossorigin = "NO"
	  @plot[1].axs_xfontstyle = "BOLD"
	  @plot[1].axs_yfontstyle = "BOLD"
	  @plot[1].axs_xreverse = "YES"
	  @plot[1].gridcolor = "128 255 128"
	  @plot[1].gridlinestyle = "DOTTED"
	  @plot[1].grid = "YES"
	  @plot[1].legendshow = "YES"
	
	  theFac = 1.0/(100*100*100)
	  @plot[1].PPlotBegin(0)
	  for theI in 0..100
	    x = 1.0*(theI)
	    y = theFac*theI*theI*theI;
	    @plot[1].PPlotAdd(x, y)
	  end
	  @plot[1].PPlotEnd()
	
	  theFac = 2.0/100
	  @plot[1].PPlotBegin(0)
	  for theI in 0..100
	    x = 1.0*(theI)
	    y = -theFac*theI
	    @plot[1].PPlotAdd(x, y)
	  end
	  @plot[1].PPlotEnd()
	
	  # PLOT 2 - MakeExamplePlot4
	  @plot[2].title = "Log Scale"
	  @plot[2].titlefontsize = 16
	  @plot[2].margintop = 40
	  @plot[2].marginleft = 70
	  @plot[2].marginbottom = 50
	  @plot[2].grid = "YES"
	  @plot[2].axs_xscale = "LOG10"
	  @plot[2].axs_yscale = "LOG2"
	  @plot[2].axs_xlabel = "Tg (X)"
	  @plot[2].axs_ylabel = "Tg (Y)"
	  @plot[2].axs_xfontstyle = "BOLD"
	  @plot[2].axs_yfontstyle = "BOLD"
	
	  theFac = 100.0/(100*100*100)
	  @plot[2].PPlotBegin(0)
	  for theI in 0..100
	    x = (0.0001+theI*0.001)
	    y = (0.01+theFac*theI*theI*theI)
	    @plot[2].PPlotAdd(x, y)
	  end
	  @plot[2].PPlotEnd()
	  @plot[2].ds_color = "100 100 200"
	
	  #PLOT 3 - MakeExamplePlot5
	  @plot[3].title = "Bar Mode"
	  @plot[3].titlefontsize = 16
	  @plot[3].margintop = 40
	  @plot[3].marginleft = 30
	  @plot[3].marginbottom = 30
	  kLables = ["jan","feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"]
	  kData = [1,2,3,4,5,6,7,8,9,0,1,2]
	
	  @plot[3].PPlotBegin(1)
	  for theI in 0...12
	    @plot[3].PPlotAddStr(kLables[theI], kData[theI])
	  end
	  @plot[3].PPlotEnd()
	  @plot[3].ds_color = "100 100 200"
	  @plot[3].ds_mode = "BAR"
	
	  #PLOT 4 - MakeExamplePlot6
	  @plot[4].title = "Marks Mode"
	  @plot[4].titlefontsize = 16
	  @plot[4].margintop = 40
	  @plot[4].marginleft = 45
	  @plot[4].marginbottom = 40
	  @plot[4].axs_xautomin = "NO"
	  @plot[4].axs_xautomax = "NO"
	  @plot[4].axs_yautomin = "NO"
	  @plot[4].axs_yautomax = "NO"
	  @plot[4].axs_xmin = 0
	  @plot[4].axs_xmax = 0.011
	  @plot[4].axs_ymin = 0
	  @plot[4].axs_ymax = 0.22
	  @plot[4].axs_xcrossorigin = "NO"
	  @plot[4].axs_ycrossorigin = "NO"
	  @plot[4].axs_xtickformat = "%1.3f"
	  @plot[4].legendshow = "YES"
	  @plot[4].legendpos = "BOTTOMRIGHT"
	
	  theFac = 100.0/(100*100*100)
	  @plot[4].PPlotBegin(0)
	  for theI in 0..10
	    x = (0.0001+theI*0.001)
	    y = (0.01+theFac*theI*theI)
	    @plot[4].PPlotAdd(x, y)
	  end
	  @plot[4].PPlotEnd()
	  @plot[4].ds_mode = "MARKLINE"
	  @plot[4].ds_showvalues = "YES"
	
	  @plot[4].PPlotBegin(0)
	  for theI in 0..10
	    x = (0.0001+theI*0.001)
	    y = (0.2-theFac*theI*theI)
	    @plot[4].PPlotAdd(x, y)
	  end
	  @plot[4].PPlotEnd()
	  @plot[4].ds_mode = "MARK"
	  @plot[4].ds_markstyle = "HOLLOW_CIRCLE"
	  
	  #PLOT 5 - MakeExamplePlot8
	  @plot[5].title = "Data Selection and Editing"
	  @plot[5].titlefontsize = 16
	  @plot[5].margintop = 40
	
	  theFac = 100.0/(100*100*100)
	  @plot[5].PPlotBegin(0)
	  for theI in -10..10
	    x = (0.001*theI)
	    y = (0.01+theFac*theI*theI*theI)
	    @plot[5].PPlotAdd(x, y)
	  end
	  @plot[5].PPlotEnd()
	  @plot[5].ds_color = "100 100 200"
	  @plot[5].ds_edit = "YES"
	  @plot[5].delete_cb = delete_cb
	  @plot[5].select_cb = select_cb
	  @plot[5].postdraw_cb = postdraw_cb
	  @plot[5].predraw_cb = predraw_cb
	  @plot[5].edit_cb = edit_cb
	end

	def tabs_get_index()
	  @tabs.valuepos.to_i
	end

	def initialize
		# Some processing required by current tab change: the controls at left
		# will be updated according to current @plot props
		tabs_tabchange_cb = lambda do |ih, new_tab, old_tab|
		  ii=0

		  ss = new_tab.tabtitle
		  ss = ss[5..-1] # Skip "Plot "
		  ii = ss.to_i
		
		  # autoscaling
		  # X axis
		  if (@plot[ii].axs_xautomin=="YES" && @plot[ii].axs_xautomax=="YES") 
		    @tgg2.value = "ON"
		    @dial2.active = "NO"
		  else 
		    @tgg2.value = "OFF"
		    @dial2.active = "YES"
		  end
		  # Y axis
		  if (@plot[ii].axs_yautomin=="YES" && @plot[ii].axs_yautomax=="YES") 
		    @tgg1.value = "ON"
		    @dial1.active = "NO"
		  else 
		    @tgg1.value = "OFF"
		    @dial1.active = "YES"
		  end
		
		  # grid
		  if (@plot[ii].grid=="YES")
		    @tgg3.value = "ON"
		    @tgg4.value = "ON"
		  else
		    # X axis
		    if (@plot[ii].grid == 'VERTICAL')
		    	@tgg3.value = "ON"
		    else
		    	@tgg3.value = "OFF"
		    end
		    # Y axis
		    if (@plot[ii].grid == 'HORIZONTAL')
		    	@tgg4.value = "ON"
		    else
		    	@tgg4.value = "OFF"
		    end
		  end
		
		  # legend
		  if (@plot[ii].legendshow == "YES")
		    	@tgg5.value = "ON"
		  else
		    	@tgg5.value = "OFF"
		  end
		  
		  Iup::DEFAULT
		end
		
		
		# show/hide V grid
		tgg3_cb = lambda do |ih,v|
		  ii = tabs_get_index()
		  
		  if (v!=0)
		    if (@tgg4.value == "ON")
		      @plot[ii].grid = "YES"
		    else
		      @plot[ii].grid = "VERTICAL"
		    end
		  else
		    if (@tgg4.value == "OFF")
		      @plot[ii].grid = "NO"
		    else
		      @plot[ii].grid = "HORIZONTAL"
		    end
		  end
		  @plot[ii].redraw = nil
		
		  Iup::DEFAULT
		end
		
		
		# show/hide H grid
		tgg4_cb = lambda do |ih, v|
		  ii = tabs_get_index()
		  
		  if (v!=0)
		    if (@tgg3.value == "ON")
		      @plot[ii].grid = "YES"
		    else
		      @plot[ii].grid = "HORIZONTAL"
		    end
		  else
		    if (@tgg3.value == "OFF")
		      @plot[ii].grid = "NO"
		    else
		      @plot[ii].grid = "VERTICAL"
		    end
		  end
		  @plot[ii].redraw = nil
		
		  Iup::DEFAULT
		end
		
		
		# show/hide legend
		tgg5_cb = lambda do |ih, v|
		  ii = tabs_get_index()
		
		  if (v!=0)
		    @plot[ii].legendshow = "YES"
		  else
		    @plot[ii].legendshow = "NO"
		  end    
		  @plot[ii].redraw = nil
		
		  Iup::DEFAULT
		end
		
		
		# autoscale Y
		tgg1_cb = lambda do |ih, v|
		  ii = tabs_get_index()
		
		  if (v!=0)   
		    @dial1.active = "NO"
		    @plot[ii].axs_yautomin = "YES"
		    @plot[ii].axs_yautomax = "YES"
		  else 
		    @dial1.active = "YES"
		    @plot[ii].axs_yautomin = "NO"
		    @plot[ii].axs_yautomax = "NO"
		  end
		  @plot[ii].redraw = nil       
		
		  Iup::DEFAULT
		end
		
		
		# autoscale X
		tgg2_cb = lambda do |ih, v|
		  ii = tabs_get_index()
		
		  if (v!=0) 
		    @dial2.active = "NO"
		    @plot[ii].axs_xautomin = "YES"
		    @plot[ii].axs_xautomax = "YES"
		  else 
		    @dial2.active = "YES"
		    @plot[ii].axs_xautomin = "NO"
		    @plot[ii].axs_xautomax = "NO"
		  end
		  @plot[ii].redraw = nil     
		
		  Iup::DEFAULT
		end
		
		
		# Y zoom
		dial1_btndown_cb = lambda do |ih, angle|
		  ii = tabs_get_index()
		
		  @plot[ii].old_ymin = @plot[ii].axs_ymin
		  @plot[ii].old_ymax = @plot[ii].axs_ymax
		
		  Iup::DEFAULT
		end
		
		dial1_btnup_cb = lambda do |ih, angle|
		  ii = tabs_get_index()
		
		  x1 = @plot[ii].old_ymin.to_f
		  x2 = @plot[ii].old_ymax.to_f
		
		  ss = @plot[ii].axs_ymode
		  if ( ss && ss[3,1]=='2' ) 
		    # LOG2:  one circle will zoom 2 times
		    xm = 4.0 * fabs(angle) / 3.141592
		    if (angle>0.0) 
		      x2 /= xm
		      x1 *= xm 
		    else 
		      x2 *= xm 
		      x1 /= xm 
		    end
		  end
		  if ( ss && ss[3,1]=='1' ) 
		    # LOG10:  one circle will zoom 10 times
		    xm = 10.0 * fabs(angle) / 3.141592
		    if (angle>0.0) 
		      x2 /= xm
		      x1 *= xm 
		    else 
		      x2 *= xm
		      x1 /= xm
		    end
		  else 
		    # LIN: one circle will zoom 2 times
		    xm = (x1 + x2) / 2.0
		    x1 = xm - (xm - x1)*(1.0-angle*1.0/3.141592)
		    x2 = xm + (x2 - xm)*(1.0-angle*1.0/3.141592)
		  end
		
		  if (x1<x2)
		    @plot[ii].axs_ymin = x1
		    @plot[ii].axs_ymax = x2
		  end
		  @plot[ii].redraw = nil 
		
		  return Iup::DEFAULT
		end
		
		
		# X zoom
		dial2_btndown_cb = lambda do |ih, angle|
		  ii = tabs_get_index()
		
		  @plot[ii].old_xmin = @plot[ii].axs_xmin
		  @plot[ii].old_xmax = @plot[ii].axs_xmax
		     
		  Iup::DEFAULT
		end
		
		dial2_btnup_cb = lambda do |ih, angle|
		  ii = tabs_get_index()
		
		  x1 = @plot[ii].old_xmin.to_f
		  x2 = @plot[ii].old_xmax.to_f
		
		  xm = (x1 + x2) / 2.0
		
		  x1 = xm - (xm - x1)*(1.0-angle*1.0/3.141592) # one circle will zoom 2 times
		  x2 = xm + (x2 - xm)*(1.0-angle*1.0/3.141592)
		
		  @plot[ii].axs_xmin = x1
		  @plot[ii].axs_xmax = x2
		
		  @plot[ii].redraw = nil   
		
		  Iup::DEFAULT
		end
		
		bt1_cb = lambda do |ih|
		p "bt1_cb"
		  ii = tabs_get_index()
		#  cnv = Cd.CreateCanvas(Cd.ContextPDF(), "pplot.pdf -o")
		#  Iup.PPlotPaintTo(@plot[ii], cnv)
		#  Cd.KillCanvas(cnv)
		  Iup::DEFAULT
		end
		
		
		@plot = Array.new(MAXPLOT)
		# create plots
		for ii in 0...MAXPLOT
		    @plot[ii] = Iup.PPlot()
		end
		
		# left panel: @plot control
		# Y zooming
		@dial1 = Iup.Dial("VERTICAL")
		lbl1 = Iup.Label("+")
		lbl2 = Iup.Label("-")
		boxinfo = Iup.Vbox([lbl1, Iup.Fill(),lbl2])
		boxdial1 = Iup.Hbox([boxinfo, @dial1])
		
		boxdial1.align = "ACENTER"
		boxinfo.align = "ACENTER"
		boxinfo.size = "20x52"
		boxinfo.gap = 2
		boxinfo.margin = 4
		boxinfo.expand = "YES"
		lbl1.expand = "NO"
		lbl2.expand = "NO"
		
		@dial1.active = "NO"
		@dial1.size = "20x52"
		@dial1.button_press_cb = dial1_btndown_cb
		@dial1.mousemove_cb = dial1_btnup_cb
		@dial1.button_release_cb = dial1_btnup_cb
		
		@tgg1 = Iup.Toggle("Y Autoscale")
		@tgg1.action = tgg1_cb
		@tgg1.value = "ON"
		
		f1 = Iup.Frame( Iup.Vbox([boxdial1, @tgg1]),:title=> "Y Zoom" )

		# X zooming
		@dial2 = Iup.Dial("HORIZONTAL")
		lbl1 = Iup.Label("-")
		lbl2 = Iup.Label("+")
		boxinfo = Iup.Hbox([lbl1, Iup.Fill(), lbl2])
		boxdial2 = Iup.Vbox([@dial2, boxinfo])
		
		boxdial2.align = "ACENTER"
		boxinfo.align = "ACENTER"
		boxinfo.size = "64x16"
		boxinfo.gap = 2
		boxinfo.margin = 4
		boxinfo.expand = "HORIZONTAL"
		
		lbl1.expand = "NO"
		lbl2.expand = "NO"
		
		@dial2.active = "NO"
		@dial2.size = "64x16"
		@dial2.button_press_cb = dial2_btndown_cb
		@dial2.mousemove_cb = dial2_btnup_cb
		@dial2.button_release_cb = dial2_btnup_cb
		
		@tgg2 = Iup.Toggle("X Autoscale")      
		@tgg2.action = tgg2_cb
		@tgg2.value = "ON"
		
		f2 = Iup.Frame( Iup.Vbox([boxdial2, @tgg2]),:title=> "X Zoom")
		
		lbl1 = Iup.Label(:title=>"",:separator=>"HORIZONTAL")
		
		@tgg3 = Iup.Toggle("Vertical Grid")
		@tgg3.action = tgg3_cb
		
		@tgg4 = Iup.Toggle("Hirozontal Grid")
		@tgg4.action = tgg4_cb
		
		lbl2 = Iup.Label(:title=>"",:separator=>"HORIZONTAL")
		
		@tgg5 = Iup.Toggle("Legend", nil)
		@tgg5.action = tgg5_cb
		
		lbl3 = Iup.Label(:title=>"",:separator=>"HORIZONTAL")
		
		bt1 = Iup.Button("Export PDF")
		bt1.action = bt1_cb
		
		vboxl = Iup.Vbox([f1, f2, lbl1, @tgg3, @tgg4, lbl2, @tgg5, lbl3, bt1],:gap=>4,:expand=>"NO")
		
		vboxr = Array.new(MAXPLOT)   # tabs containing the plots
		# right panel: tabs with plots
		for ii in 0...MAXPLOT
		vboxr[ii] = Iup.Vbox([@plot[ii]]) # each @plot a tab
		vboxr[ii].tabtitle = "Plot #{ii}"
		end
		
		@tabs = Iup.Tabs(vboxr) # create tabs
		@tabs.tabchange_cb = tabs_tabchange_cb
		
		# dialog
		hbox = Iup.Hbox([vboxl, @tabs],:margin =>"4x4",:gap=>10)
		
		dlg = Iup.Dialog(hbox,:size=>"600x240",:title=>"IupPPlot Example")
		
		InitPlots() # It must be able to be done independent of dialog Mapping
		
		#tabs_tabchange_cb.call(@tabs, vboxr[0], 0)
		
		dlg.ShowXY(Iup::CENTER, Iup::CENTER)
		Iup.MainLoop
		dlg.Destroy
	end		
end
	
plot = IupPlotTest.new

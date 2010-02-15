require 'rubygems'
require 'iup'

class MdiTest

	def createImages()
		img_bits1 = [
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,0,2,0,2,0,2,2,0,2,2,2,0,0,0,2,2,2,0,0,2,0,2,2,0,0,0,2,2,2,
		2,2,2,0,2,0,0,2,0,0,2,0,2,0,2,2,2,0,2,0,2,2,0,0,2,0,2,2,2,0,2,2,
		2,2,2,0,2,0,2,2,0,2,2,0,2,2,2,2,2,0,2,0,2,2,2,0,2,0,2,2,2,0,2,2,
		2,2,2,0,2,0,2,2,0,2,2,0,2,2,0,0,0,0,2,0,2,2,2,0,2,0,0,0,0,0,2,2,
		2,2,2,0,2,0,2,2,0,2,2,0,2,0,2,2,2,0,2,0,2,2,2,0,2,0,2,2,2,2,2,2,
		2,2,2,0,2,0,2,2,0,2,2,0,2,0,2,2,2,0,2,0,2,2,0,0,2,0,2,2,2,0,2,2,
		2,2,2,0,2,0,2,2,0,2,2,0,2,2,0,0,0,0,2,2,0,0,2,0,2,2,0,0,0,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		]
		
		img_bits2 = [
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,0,3,0,3,0,3,3,0,3,3,3,1,1,0,3,3,3,0,0,3,0,3,3,0,0,0,3,3,3,
		3,3,3,0,3,0,0,3,0,0,3,0,3,0,1,1,3,0,3,0,3,3,0,0,3,0,3,3,3,0,3,3,
		3,3,3,0,3,0,3,3,0,3,3,0,3,3,1,1,3,0,3,0,3,3,3,0,3,0,3,3,3,0,3,3,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		3,3,3,0,3,0,3,3,0,3,3,0,3,0,1,1,3,0,3,0,3,3,0,0,3,0,3,3,3,0,3,3,
		3,3,3,0,3,0,3,3,0,3,3,0,3,3,1,1,0,0,3,3,0,0,3,0,3,3,0,0,0,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,0,3,3,3,0,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		2,2,2,2,2,2,2,3,3,3,3,3,3,3,1,1,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,3,3,3,3,3,3,3,3,1,1,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
		]
	
		@img1 = Iup.Image(32,32, img_bits1)
		@img1["0"] = "0 0 0" 
		@img1["1"] = "BGCOLOR"
		@img1["2"] = "255 0 0"
		
		@img2 = Iup.Image(32,32, img_bits2)
		@img2["0"] = "0 0 0" 
		@img2["1"] = "0 255 0"
		@img2["2"] = "BGCOLOR"
		@img2["3"] = "255 0 0"
	end
	
	def set_callbacks(ctrl)  
	
		action = lambda do |ih|
		  printf("%2d-action(%s#%s) Value=%s\n", @line, ih.GetClassName(), ih.cindex, ih.value) 
		  @line+=1
		  Iup::DEFAULT
		end
	
		getfocus_cb = lambda do |ih|
		  printf("%2d-getfocus(%s#%s)\n", @line, ih.GetClassName(), ih.cindex)
		  @line += 1
		  Iup::DEFAULT
		end
		
		killfocus_cb = lambda do |ih|
		  printf("%2d-killfocus(%s#%s)\n", @line, ih.GetClassName(), ih.cindex)
		  @line+=1
		  Iup::DEFAULT
		end
	
	  ctrl.getfocus_cb = getfocus_cb
	  ctrl.killfocus_cb = killfocus_cb
	#  ctrl.action = action
	  
	  child = Iup.GetNextChild(ctrl, nil)
	  while (child)   
	    set_callbacks(child)  
	    child = Iup.GetNextChild(ctrl, child)
	  end
	end
	
	def createDialog()
	
	  _frm_1 = Iup.Frame(
	    Iup.Vbox([
	      Iup.Button(:title=>"Button Text",:attr=>"CINDEX=1"),
	      Iup.Button(:attr=> "CINDEX=2, BGCOLOR=\"255 128 0\", RASTERSIZE=30x30"),
	      Iup.Button(:image=>@img1,:attr=> "CINDEX=3"),
	      Iup.Button(:image=>@img1,:attr=> "CINDEX=4, FLAT=YES"),
	      Iup.Button(:image=>@img1,:impress=>@img2,:attr=> "CINDEX=5")
	      ]),:title=>"IupButton")
	
	  _frm_2 = Iup.Frame(
	    Iup.Vbox([
	      Iup.Label(:title=>"Label Text\nLine 2\nLine 3",:attr=> "CINDEX=1"),
	      Iup.Label(:title=>"",:attr => "SEPARATOR=HORIZONTAL,CINDEX=2"),
	      Iup.Label(:title=>"",:image=>@img1,:attr => "CINDEX=3")
	      ]),:title=>"IupLabel")
	
	  _frm_3 = Iup.Frame(
	    Iup.Vbox([
	      Iup.Toggle(:title=>"Toggle Text",:attr=>"VALUE=ON,CINDEX=1"),
	      Iup.Toggle(:title=>"3State Text",:attr=>"VALUE=NOTDEF,CINDEX=2,3STATE=YES"),
	      Iup.Toggle(:title=>"",:image=>@img1,:impress=>@img2,:attr=> "CINDEX=3"),
	      Iup.Frame(Iup.Radio(Iup.Vbox([
	        Iup.Toggle(:title=>"Toggle Text",:cindex=>4),
	        Iup.Toggle(:title=>"Toggle Text",:cindex=>5)
	        ])), :title=>"IupRadio")
	      ]),:title=>"IupToggle")
	
	  _text_1 = Iup.Text( )
	  _text_1.value = "IupText Text"
	# _text_1.size = "80x"
	  _text_1.cindex = 1
	
	  _ml_1 = Iup.MultiLine( )
	  _ml_1.value = "IupMultiline Text\nSecond line\nThird line"
	#  _ml_1.size = "50x30"
	#  _ml_1.expand = "YES"
	#  _ml_1.size = "80x60"
	  _ml_1.cindex = 1
	
	  _frm_4 = Iup.Frame(Iup.Vbox([
	    _text_1,
	    _ml_1,
	    ]),:title=>"IupText/IupMultiline")
	
	  _list_1 = Iup.List()
	  _list_1.expand = "YES"
	# _list_1.size =  "50x40"
	  _list_1.value = 1
	  _list_1.multiple = "YES"  
	  _list_1["1"] = "Item 1 Text"
	  _list_1["2"] = "Item 2 Text"
	  _list_1["3"] = "Item 3 Text Big Item"
	  _list_1["4"] = "Item 4 Text"
	  _list_1["5"] = "Item 5 Text"
	  _list_1["6"] = "Item 6 Text"
	  _list_1.cindex = 1        
	
	  _list_2 = Iup.List( )
	  _list_2.dropdown="YES"
	  _list_2.expand="YES"
	  _list_2.visible_items= 3
	# _list_2.size= "50x"
	  _list_2.value=2
	  _list_2["1"]="Item 1 Text"
	  _list_2["2"]="Item 2 Text Big Item"
	  _list_2["3"]="Item 3 Text"
	  _list_2["4"]="Item 4 Text"
	  _list_2["5"]="Item 5 Text"
	  _list_2["6"]="Item 6 Text"
	  _list_2.cindex=2
	
	  _list_3 = Iup.List( )
	  _list_3.editbox="YES"
	  _list_3.xpand="YES"
	# _list_3.size="50x40"
	  _list_3.value="Test Value"
	  _list_3["1"]="Item 1 Text"
	  _list_3["2"]="Item 2 Text Big Item"
	  _list_3["3"]="Item 3 Text"
	  _list_3["4"]="Item 4 Text"
	  _list_3["5"]="Item 5 Text"
	  _list_3["6"]="Item 6 Text"
	  _list_3.cindex = 3
	
	  _list_4 = Iup.List( )
	  _list_4.editbox = "YES"
	  _list_4.dropdown="YES"
	  _list_4.expand="YES"
	  _list_4.visible_items = 3
	# _list_4.size = "50x10"
	  _list_4.value = "Test Value"
	  _list_4["1"] = "Item 1 Text"
	  _list_4["2"] = "Item 2 Text Big Item"
	  _list_4["3"] = "Item 3 Text"
	  _list_4["4"] = "Item 4 Text"
	  _list_4["5"] = "Item 5 Text"
	  _list_4["6"] = "Item 6 Text"
	  _list_4.cindex="4"
	
	  _frm_5 =  Iup.Frame(Iup.Vbox([
	      _list_1,
	      _list_2,
	      _list_3,
	      _list_4
	      ]))
	  _frm_5.title = "IupList"
	
	  _hbox_1 = Iup.Hbox([
	    _frm_1,
	    _frm_2,
	    _frm_3,
	    _frm_4,
	    _frm_5
	    ])
	
	  _cnv_1 = Iup.Canvas( "do_nothing")
	  _cnv_1.bgcolor = "128 255 0"
	
	  _vbox_1 = Iup.Vbox([
	#    Iup.Tabs(_hbox_1, NULL),
	    _hbox_1,
	    _cnv_1
	    ])
	  _vbox_1.margin = "5x5"
	  _vbox_1.alignment = "ARIGHT"
	  _vbox_1.gap = "5"            
	
	  set_callbacks(_vbox_1)  
	
	  dlg = Iup.Dialog(_vbox_1)
	  dlg.title = "MDI Child"
	#  dlg.shrink = "YES"
	#  dlg.size = "500x200"
	
	#  dlg.bgcolor = "255 0 255"
	#  dlg.font","Times New Roman:ITALIC:10"
	#  dlg.font = "TIMES_BOLD_14"
	#  _vbox_1.active = "NO"
	
	  #dlg.composited = "YES"
	  #dlg.layered = "YES"
	  #dlg.layeralpha = 192
	
	#  dlg.Map()
	#  dlg.size = nil
	
	  return dlg
	end
	
	
	def createMenu()
	
		mdi_tilehoriz = lambda do |ih|
		  Iup.GetDialog(ih).mdiarrange = "TILEHORIZONTAL"
		  Iup::DEFAULT
		end
		
		mdi_tilevert = lambda do |ih|
		  Iup.GetDialog(ih).mdiarrange= "TILEVERTICAL"
		  Iup::DEFAULT
		end
		
		mdi_cascade = lambda do |ih|
		  Iup.GetDialog(ih).mdiarrange= "CASCADE"
		  Iup::DEFAULT
		end
		
		mdi_icon = lambda do |ih|
		  Iup.GetDialog(ih).mdiarrange = "ICON"
		  Iup::DEFAULT
		end
		
		mdi_next = lambda do |ih|
		  Iup.GetDialog(ih).mdiactivate = "NEXT"
		  Iup::DEFAULT
		end
		
		mdi_previous = lambda do |ih|
		  Iup.GetDialog(ih).mdiactivate = "PREVIOUS"
		  return Iup::DEFAULT
		end
		
		mdi_closeall = lambda do |ih|
		  Iup.GetDialog(ih).mdicloseall = nil
		  Iup::DEFAULT
		end
		
		mdi_activate = lambda do |ih|
		  printf("%2d-mdi_activate(%s)\n", @line, Iup.GetName(ih))
		  @line+=1
		  Iup::DEFAULT
		end
		
		mdi_new = lambda do |ih|	
		  dlg = createDialog()
		  dlg.mdichild = "YES"
		  dlg.parentdialog = "mdiFrame"
		  dlg.mdiclient = @mdiClient
		  #dlg.mdiactivate_cb = mdi_activate
		  #dlg.placement =  "MAXIMIZED"	
		  dlg.Show()
	
		  Iup::DEFAULT
		end
	
	  mnu = Iup.Menu([
	  	Iup.Submenu("MDI",Iup.Menu([
	      		Iup.Item("New",mdi_new)])),
	      winmenu = Iup.Submenu("Window", 
	        Iup.Menu([
		      Iup.Item("Tile Horizontal", mdi_tilehoriz), 
		      Iup.Item("Tile Vertical", mdi_tilevert), 
		      Iup.Item("Cascade", mdi_cascade), 
		      Iup.Item("Icon Arrange", mdi_icon), 
		      Iup.Item("Close All", mdi_closeall), 
		      Iup.Separator(),
		      Iup.Item("Next", mdi_next), 
		      Iup.Item("Previous", mdi_previous) 
	      ]))
	    ])
	  @mdiMenu = winmenu
	  @mnu = mnu
	end
	
	def createFrame()
	  cnv = Iup.Canvas( "do_nothing")
	  cnv.mdiclient = "YES"
	  cnv.mdimenu = @mdiMenu
	  @mdiClient = cnv
	
	  dlg = Iup.Dialog(cnv)
	  dlg.title = "MDI Frame"
	  dlg.mdiframe = "YES"
	  dlg.rastersize = "800x600"
	  Iup.SetHandle("mdiFrame",dlg)
	  
	  dlg
	end

	def initialize	
	  @line = 0
	  createImages()
	  createMenu()
	  dlg = createFrame() 
	# dlg.placement = "MAXIMIZED"
	  dlg.menu = @mnu
	  dlg.ShowXY(Iup::CENTER,Iup::CENTER)
	  Iup.MainLoop()
	  @img1.Destroy
	  @img2.Destroy
	  dlg.Destroy
	end
	
end

test = MdiTest.new

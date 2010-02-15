require 'rubygems'
require 'iup'


class IupTreeTest
	# Initializes IupTree and registers callbacks */

	
	def init_tree()	
	

		# Callback called when a leaf is added by the menu. */
		addleaf = lambda do |h|
		  id = @tree.value
		  @tree["addleaf#{id}"] = ""
		  @tree.redraw = "YES"
		  Iup::DEFAULT
		end
		
		# Callback called when a branch is added by the menu. */
		addbranch = lambda do |h|
		  id = @tree.value
		  @tree["addbranch#{id}"] = ""
		  @tree.redraw = "YES"
		  Iup::DEFAULT
		end
		
		selectnode = lambda do |h|
		  @tree.value = h.title
	          @tree.redraw = "YES"  
		  return Iup::DEFAULT
		end
		
		# Callback called when a node is removed by the menu. */
		removenode = lambda do |h|
		  @tree.delnode	= "MARKED"
	          @tree.redraw = "YES"  
		  Iup::DEFAULT
		end
		
		# from the menu */
		renamenode = lambda do |h|
		  Iup::DEFAULT
		end
		
		text_cb = lambda do |ih,c,after|
		  if (c == Iup::K_ESC)
		    return Iup::CLOSE
		  end
		
		  if (c == Iup::K_CR)  
		    @tree.name = after
		    @tree.redraw = "YES"  
		    return Iup::CLOSE
		  end
		  Iup::DEFAULT
		end
				
		executeleaf_cb = lambda do |ih,id|
		  puts "executeleaf_cb (#{id})"
		  Iup::DEFAULT
		end
		
		renamenode_cb = lambda do |ih,id,name|
		  puts "renamenode_cb (#{id}=#{name})"
		  Iup::DEFAULT
		end
		
		rename_cb = lambda do |ih,id,name|
		  puts "rename_cb (#{id}=#{name})"
		  if (name == "fool")
		    return Iup::IGNORE
		  end
		  Iup::DEFAULT
		end
		
		branchopen_cb = lambda do |ih,id|
		  puts "branchopen_cb (#{id})"
		  Iup::DEFAULT
		end
		
		branchclose_cb = lambda do |ih,id|
		  puts "branchclose_cb (#{id})"
		  Iup::DEFAULT
		end
		
		dragdrop_cb = lambda do |ih, drag_id, drop_id, isshift, iscontrol|
		  puts "dragdrop_cb (#{drag_id})->(#{drop_id})"
		  Iup::DEFAULT
		end
		
		# Callback called when a key is hit */
		k_any_cb = lambda do |ih,c|
		  if (c == Iup::K_DEL)   
		    @tree.delnode = "MARKED"
	            @tree.redraw = "YES"  
		  end
		
		  Iup::DEFAULT
		end
		
		
		# Callback called when the right mouse button is pressed */
		rightclick_cb = lambda do |h,id|

		  popup_menu = Iup.Menu([
		    Iup.Item("Add Leaf",addleaf),
		    Iup.Item("Add Branch",addbranch),
		    Iup.Item("Rename Node",renamenode),
		    Iup.Item("Remove Node",removenode),
		    Iup.Submenu("Selection", Iup.Menu([
		      Iup.Item("ROOT", selectnode),
		      Iup.Item("LAST", selectnode),
		      Iup.Item("PGUP", selectnode),
		      Iup.Item("PGDN", selectnode),
		      Iup.Item("NEXT", selectnode),
		      Iup.Item("PREVIOUS", selectnode),
		      Iup.Separator(),
		      Iup.Item("INVERT", selectnode),
		      Iup.Item("BLOCK", selectnode),
		      Iup.Item("CLEARALL", selectnode),
		      Iup.Item("MARKALL", selectnode),
		      Iup.Item("INVERTALL", selectnode)
		      ]))
		    ])
		    
		  h.value = id.to_s
		  popup_menu.Popup(Iup::MOUSEPOS,Iup::MOUSEPOS)
		
		  popup_menu.Destroy()
		
		  Iup::DEFAULT
		end
	
	  @tree = Iup.Tree() 
	  @tree.executeleaf_cb = executeleaf_cb
	  @tree.renamenode_cb = renamenode_cb
	  @tree.rename_cb = rename_cb
	  @tree.branchclose_cb = branchclose_cb
	  @tree.branchopen_cb = branchopen_cb
	  @tree.dragdrop_cb = dragdrop_cb
	  @tree.rightclick_cb = rightclick_cb
	  @tree.k_any = k_any_cb	
	end
	
	# Initializes the dialog */
	def init_dlg()	
	  box = Iup.Vbox([Iup.Hbox([@tree, Iup.Button("teste", "xx") ])])
	  @dlg = Iup.Dialog(box,:title=>"IupTree",:size=>"QUARTERxTHIRD") 
	  box.margin = "20x20"
	  @dlg.bgcolor = "192 192 192"
	end
	
	# Initializes the Iup.Tree's attributes */
	def init_tree_atributes()
	  @tree.font = "COURIER_NORMAL_10"
	  @tree.name = "Figures"
	  @tree.addbranch = "3D"
	  @tree.addbranch = "2D"
	  @tree.addleaf = "test"
	  @tree.addbranch1 = "parallelogram"
	  @tree.addleaf2 = "diamond"
	  @tree.addleaf2 = "square"
	  @tree.addbranch1 = "triangle"
	  @tree.addleaf2 = "scalenus"
	  @tree.addleaf2 = "isoceles"
	  @tree.addleaf2 = "equilateral"
	  @tree.value = 6
	  @tree.ctrl = "YES"
	  @tree.shift = "YES"
	  @tree.addexpanded = "NO"
	  @tree.showdragdrop = "YES"
	  @tree.showrename = "YES"
		
	  @tree.redraw = "YES"
	end

	def initialize
	  init_tree()                          # Initializes Iup.Tree */
	  init_dlg()                           # Initializes the dialog */
	  @dlg.ShowXY(Iup::CENTER,Iup::CENTER) # Displays the dialog */
	  init_tree_atributes()                # Initializes attributes, can be done here or anywhere */
	
	  Iup.MainLoop()                         # Main loop */
	  @dlg.Destroy()
	end
end

test = IupTreeTest.new


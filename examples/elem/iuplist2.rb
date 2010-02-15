require 'rubygems'

require 'iup'

list_cb = lambda do |ih, t, i, v|
  lbl = ih._label
  lbl.title = t
  Iup::DEFAULT
end

edit_cb = lambda do |ih, c, after|
  lbl = ih._label
  if(Iup.isxkey(c) && c != Iup::K_DEL) 
  	return Iup::DEFAULT
  end
  lbl.title = after
  Iup::DEFAULT
end

btclose_cb = lambda do |ih|
  return Iup::CLOSE
end

bt_cb = lambda do |ih|
  list = ih._list
  Iup.Message("List", "Value=#{list.value}")
  Iup::DEFAULT
end

getfocus_cb = lambda do |ih|
  bt = ih._button
  bt.bgcolor = "255 0 128"
  Iup::DEFAULT
end

killfocus_cb = lambda do |ih|
  bt = ih._button
  bt.bgcolor = nil
  Iup::DEFAULT
end

  bt1 = Iup.Button("Drop+Edit")
  bt1.action = bt_cb
  bt2 = Iup.Button("Drop")
  bt2.action = bt_cb
  bt3 = Iup.Button("List+Edit")
  bt3.action = bt_cb 
  bt4 = Iup.Button("List")
  bt4.action = bt_cb
  
  list1 = Iup.List()
  list1.action = list_cb
  list2 = Iup.List()
  list2.action = list_cb
  list3 = Iup.List()
  list3.action = list_cb
  list4 = Iup.List()
  list4.action = list_cb
  
  list1.attr = "1=\"US$ 1000\", 2=\"US$ 2000\", 3=\"US$ 30000000\", 4=\"US$ 4000\", 5=\"US$ 5000\", 6=\"US$ 6000\", 7=\"US$ 7000\","+
       		"EXPAND=HORIZONTAL, EDITBOX=YES, DROPDOWN=YES, VISIBLE_ITEMS=5"
  list2.attr = "1=\"R$ 1000\", 2=\"R$ 2000\", 3=\"R$ 3000\", 4=\"R$ 4000\", 5=\"R$ 5000\", 6=\"R$ 6000\", 7=\"R$ 7000\","+
       		"EXPAND=HORIZONTAL, DROPDOWN=YES, VISIBLE_ITEMS=5"
  list3.attr = "1=\"Char A\", 2=\"Char B\", 3=\"Char CCCCC\", 4=\"Char D\", 5=\"Char F\", 6=\"Char G\", 7=\"Char H\","+
       		"EXPAND=YES, EDITBOX=YES"
  list4.attr = "1=\"Number 1\", 2=\"Number 2\", 3=\"Number 3\", 4=\"Number 4\", 5=\"Number 5\", 6=\"Number 6\", 7=\"Number 7\","+
                "EXPAND=YES"

  bt1._list = list1
  bt2._list = list2
  bt3._list = list3
  bt4._list = list4

  list1._button = bt1
  list2._button = bt2
  list3._button = bt3
  list4._button = bt4

  bt1.bgcolor = "192 192 192"
  bt2.bgcolor = "192 192 192"
  bt3.bgcolor = "192 192 192"
  bt4.bgcolor = "192 192 192"

  list1.getfocus_cb = getfocus_cb
  list1.killfocus_cb = killfocus_cb
  list2.getfocus_cb = getfocus_cb
  list2.killfocus_cb = killfocus_cb
  list3.getfocus_cb = getfocus_cb
  list3.killfocus_cb = killfocus_cb
  list4.getfocus_cb = getfocus_cb
  list4.killfocus_cb = killfocus_cb

  list1.list_edit_cb = edit_cb
  list3.list_edit_cb = edit_cb

# list3.readonly = "YES"

  box1 = Iup.Vbox([list1, bt1])
  box2 = Iup.Vbox([list2, bt2])
  box3 = Iup.Vbox([list3, bt3])
  box4 = Iup.Vbox([list4, bt4])

  lbl = Iup.Label("")
  lbl.expand = "HORIZONTAL"

  btok = Iup.Button(:title=>"OK",:action=>btclose_cb)
  
  btcancel = Iup.Button(:title=>"Cancel",:action=>btclose_cb)

  btok._list1 = list1
  btok._list2 = list2
  btok._list3 = list3
  btok._list4 = list4
           
  dlg = Iup.Dialog(Iup.Vbox([Iup.Hbox([box1, box2, box3, box4]), lbl, btok, btcancel]),:attr=>"MARGIN=10x10, GAP=10")
  dlg.title = "IupList Example"
  dlg._label = lbl
  dlg.defaultenter = btok
  dlg.defaultesc = btcancel

  dlg.ShowXY(Iup::CENTER, Iup::CENTER)

  Iup.MainLoop()
  dlg.Destroy()


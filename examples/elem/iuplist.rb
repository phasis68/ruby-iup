require 'rubygems'
require "iup"

list_multiple_cb = lambda do |hi,t,i,v|
  message =  "Item #{i} - #{t} - #{v == 0 ? 'deselected' : 'selected'}" 
  Iup.Message("Competed in", message)

  Iup::DEFAULT
end

  list = Iup.List("list_act")
  list.attr = "1=Gold, 2=Silver, 3=Bronze, 4=None,"+
                          "VALUE=4, SIZE=EIGHTHxEIGHTH"

  frm_medal = Iup.Frame(list)
  frm_medal.title = "Best medal"
  
  list_multiple = Iup.List()
  
  list_multiple.attr = "1=\"100m dash\", 2=\"Long jump\", 3=\"Javelin throw\", 4=\"110m hurdlers\", 5=\"Hammer throw\",6=\"High jump\","+
                                   "MULTIPLE=YES, VALUE=\"+--+--\", SIZE=EIGHTHxEIGHTH"

  list_multiple.action = list_multiple_cb
  
  frm_sport = Iup.Frame(list_multiple)  
  frm_sport.title = "Competed in"

  list_dropdown = Iup.List()
  list_dropdown.attr = "1=\"Less than US$ 1000\", 2=\"US$ 2000\", 3=\"US$ 5000\", 4=\"US$ 10000\", 5=\"US$ 20000\", 6=\"US$ 50000\", 7=\"More than US$ 100000\","+
                                   "DROPDOWN=YES, VISIBLE_ITEMS=5"
  
  frm_prize = Iup.Frame(list_dropdown)
  frm_prize.title = "Prizes won"

  dlg = Iup.Dialog(Iup.Hbox([frm_medal, frm_sport, frm_prize]))
  dlg.title = "IupList Example"
  dlg.ShowXY(Iup::CENTER, Iup::CENTER)

  Iup.MainLoop()
  dlg.Destroy()
  

require 'rubygems'
require 'iup'


def create_mat()

  mat = Iup.Matrix(nil) 
 
  mat.numcol_visible = 2
  mat.numlin_visible = 3
  mat.resizematrix = "YES"
  
  mat.numlin = 3
  mat.numcol = 2

  mat["0:0"] = "Inflation"
  mat["1:0"] = "Medicine "
  mat["2:0"] = "Food" 
  mat["3:0"] = "Energy" 
  mat["0:1"] = "January  2000" 
  mat["0:2"] = "February 2000" 
  mat["1:1"] = 5.6
  mat["2:1"] = 2.2
  mat["3:1"] = 7.2
  mat["1:2"] = 4.5
  mat["2:2"] = 8.1
  mat["3:2"] = 3.4
  mat.widthdef = 34

  mat
end



  dlg = Iup.Dialog(create_mat)
  dlg.ShowXY(Iup::CENTER,Iup::CENTER)
  Iup.MainLoop
  dlg.Destroy


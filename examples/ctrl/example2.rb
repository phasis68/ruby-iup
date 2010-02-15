require 'rubygems'
require 'iup'

def createtree()
  tree = Iup.Tree(:size=>'80x80',:expand=>'YES',:font=>'COURIER_NORMAL_10',:name=>'Figures')
  tree.addbranch='3D'
  tree.addbranch='2D'
  tree.addleaf1='trapeze'
  tree.addbranch1='parallelogram'
  tree.addleaf2='diamond'
  tree.addleaf2='square'
  tree.addbranch4='triangle'
  tree.addleaf5='scalenus'
  tree.addleaf5='isoceles'
  tree.addleaf5='equilateral'
  tree.value='6'
  tree.addexpanded='NO'
  return tree
end


  tree = createtree()
  sbox = Iup.Sbox(:elem=>tree,:direction=>'EAST')

  cv = Iup.Canvas(:expand=>'YES')
  
  ml = Iup.MultiLine(:expand=>'YES')
  sbox2 = Iup.Sbox(:elem=>ml,:direction=>'WEST')

  vbox = Iup.Hbox([sbox, cv, sbox2])

  lb = Iup.Label(:title=>"This is a label",:expand=>'NO')
  sbox3 = Iup.Sbox(:elem=>lb,:direction=>'NORTH')
  dg = Iup.Dialog(Iup.Vbox([vbox, sbox3]))

  dg.Show    
  Iup.MainLoop
  dg.Destroy


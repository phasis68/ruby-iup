require 'rubygems'
require 'iup'

  r,g,b=Iup.GetColor(100,100)
  if r
    puts "RGB = %.2X%.2X%.2X" % [r,g,b]
  end
  
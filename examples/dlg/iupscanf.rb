require 'rubygems'
require 'iup'

text = "This is a vector of characters"
real = 0.0012
integer = 12
fmt = "Data entering example\n" +
   "text = %300.40%s\n" +
   "real = %20.10%g\n" +
   "integer = %20.10%d\n"
text,real,integer = Iup.Scanf(fmt,text,real,integer)
if text.nil? then
	Iup.Message("IupScanf","Operation canceled")
else
	string = "Text: #{text}\nReal: #{real}\nInteger: #{integer}\n"
	Iup.Message("IupScanf",string)
end

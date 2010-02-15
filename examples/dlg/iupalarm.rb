#  Shows a dialog similar to the one shown when you exit a program without saving.

require 'rubygems'
require 'iup'

case(Iup.Alarm("IupAlarm Example","File not saved! Save it now?", "Yes", "No", "Cancel"))
	when 1
		Iup.Message("Save file", "File saved sucessfully - leaving program")
	when 2
		Iup.Message("Save file", "File not saved - leaving program anyway")
	when 3
		Iup.Message("Save file", "Operation canceled")
end




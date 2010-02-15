require 'rubygems'
require 'iup'

marks = [0,0,0,0,1,1,0,0]
options = ["Blue","Red","Green"  ,"Yellow","Black","White","Gray","Brown"]
size = options.size

marks,error = Iup.ListDialog(2,"Color Selection",size,options,0,16,5,marks)

if(error == -1)
	Iup.Message("IupListDialog","Operation canceled");
else
	selection = ""

	marks.each_index {|i|
		selection += options[i]+"\n" if(marks[i]==1)
	}
	
	if(selection!="")
		Iup.Message("Options selected",selection)	  
	else
		Iup.Message("IupListDialog","No option selected")
	end
end



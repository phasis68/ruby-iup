require 'rubygems'
require 'iup'

file = "./*.txt"
file,err = Iup.GetFile(file)
case(err)
	when 1
		Iup.Message("New file",file)
	when 0 
      		Iup.Message("File already exists",file)
	when -1  
      		Iup.Message("IupFileDlg","Operation canceled")
    	when -2  
      		Iup.Message("IupFileDlg","Allocation error")
	when -3  
      		Iup.Message("IupFileDlg","Invalid parameter")
end
	


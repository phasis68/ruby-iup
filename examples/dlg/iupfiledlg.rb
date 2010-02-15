require 'rubygems'
require 'iup'


filedlg = Iup.FileDlg(:dialogtype=>"SAVE",:title=>"File Save",:filter=>"*.jpg",:filterinfo=>"JPEG Files") 

filedlg.Popup(Iup::CENTER, Iup::CENTER)

case(filedlg.status)
	when '1'
		Iup.Message("New file",filedlg.value)
	when '0'
		Iup.Message("File already exists",filedlg.value)
	when '-1'
		Iup.Message("IupFileDlg","Operation Canceled")
end

filedlg.Destroy()


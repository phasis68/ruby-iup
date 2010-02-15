require 'rubygems'

require 'iup'

mlaction = lambda do |ih,c,after|
  if(c==Iup::K_DEL)
    return Iup::IGNORE
  else
    return Iup::DEFAULT
  end
end

  ml = Iup.MultiLine(:action=>mlaction)
  ml.expand = "YES"
  ml.value = "I ignore the DEL key!"
  ml.border = "YES"

  dlg = Iup.Dialog(ml)
  dlg.title = "IupMultiline"
  dlg.size = "QUARTERxQUARTER"

  dlg.Show()
  Iup.MainLoop()
  dlg.Destroy()

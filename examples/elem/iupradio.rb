require 'rubygems'

require 'iup'

  male	= Iup.Toggle("Male")
  female = Iup.Toggle("Female")

  exclusive = Iup.Radio(
    Iup.Vbox([
      male,
      female])
  )
  exclusive.value = female
  exclusive.tip = "Two state button - Exclusive - RADIO"

  frame = Iup.Frame(
    exclusive
  )
  frame.title = "Gender"

  dialog = Iup.Dialog(
    Iup.Hbox([
      Iup.Fill(),
      frame,
      Iup.Fill()])
  )

  dialog.attr = "SIZE=140, TITLE=IupRadio, RESIZE=NO, MINBOX=NO, MAXBOX=NO"

  dialog.Show()
  Iup.MainLoop()
  dialog.Destroy()

require 'rubygems'
require 'iup'

	acao_numero = lambda do |ih, c, new_value|
	  valid_character = "0123456789.+-Ee"
	  
	  if(c == Iup::K_CR)  # replaces TAB for ENTER */
	    return Iup::K_TAB
	  elsif(c<256 && valid_character[c.chr])  # c is a valid character */
	    return Iup::DEFAULT
	  elsif(c<20 || c>=256)  # c is a control character(TAB, BACKSPACE, ...) */
	    return Iup::DEFAULT
	  end
	  return Iup::IGNORE
	end

  campo = Iup.Text("acao_numero")                           # creates TEXT field */
  campo.action = acao_numero 				    # registers callback */
  campo.value = 1.0                                         # defines initial value */

  mensagem = Iup.Label("Entre a Number: ") # creates message */
  prompt = Iup.Hbox([mensagem, campo])  # creates prompt */

  dlg = Iup.Dialog(prompt)
  dlg.Show()                   # displays and creates dialog */
  Iup.MainLoop()               # interacts with user */

  puts("Integer Number: %d" % campo.GetInt("VALUE"))   # prints the integer number entered by the user */
  puts("Real Number: %g" % campo.GetFloat("VALUE"))    # prints the real number entered by the user */
  puts("Text: %s" % campo.value)  		       # prints the text entered by the user */

  dlg.Destroy()

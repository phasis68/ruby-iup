#
#                             IupButton example                             
#   Description : Creates four buttons. The first uses images, the second   
#                 turns the first on and off, the third exits the           
#                 application and the last does nothing                     
#

require 'rubygems'
require 'iup'

#* Defines released button's image 

pixmap_release = [
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,4,4,3,3,3,3,2,2,
       1,1,3,3,3,3,3,4,4,4,4,3,3,3,2,2,
       1,1,3,3,3,3,3,4,4,4,4,3,3,3,2,2,
       1,1,3,3,3,3,3,3,4,4,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
       2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
]

#* Defines pressed button's image 
pixmap_press = [
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,4,4,3,3,3,3,3,2,2,
       1,1,3,3,3,3,4,4,4,4,3,3,3,3,2,2,
       1,1,3,3,3,3,4,4,4,4,3,3,3,3,2,2,
       1,1,3,3,3,3,3,4,4,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
       2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
]

#* Defines inactive button's image 
pixmap_inactive = [
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,4,4,3,3,3,3,2,2,
       1,1,3,3,3,3,3,4,4,4,4,3,3,3,2,2,
       1,1,3,3,3,3,3,4,4,4,4,3,3,3,2,2,
       1,1,3,3,3,3,3,3,4,4,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,1,3,3,3,3,3,3,3,3,3,3,3,3,2,2,
       1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
       2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
]

  # Creates a text 
  text = Iup.Text(:readonly=>"YES")

  # Defines released button's image size 
  img_release = Iup.Image(16, 16, pixmap_release)

  # Defines released button's image colors 
  img_release["1"] = "215 215 215"
  img_release["2"] = "40 40 40"
  img_release["3"] = "30 50 210"
  img_release["4"] = "240 0 0"

  # Defines pressed button's image size 
  img_press = Iup.Image( 16, 16, pixmap_press )

  # Defines pressed button's image colors 
  img_press["1"] = "40 40 40"
  img_press["2"] = "215 215 215"
  img_press["3"] = "0 20 180"
  img_press["4"] = "210 0 0"

  # Defines inactive button's image size 
  img_inactive = Iup.Image( 16, 16, pixmap_inactive )

  # Defines inactive button's image colors 
  img_inactive["1"] = "215 215 215"
  img_inactive["2"] = "40 40 40"
  img_inactive["3"] = "100 100 100"
  img_inactive["4"] = "200 200 200"

  # Creates a button 
  btn_image = Iup.Button(:title=>"Button with image",:image=>img_release,:impress=>img_press,:iminactive=>img_inactive)

  # Creates a button 
  btn_big = Iup.Button(:title=>"Big useless button",:size=>"EIGHTHxEIGHTH")

  # Creates a button entitled Exit associated with action exit_act 
  btn_exit = Iup.Button("Exit")

  # Creates a button entitled on/off associated with action onoff_act 
  btn_on_off = Iup.Button("on/off")

  # Creates dialog with the four buttons and the text
  dlg = Iup.Dialog(
          Iup.Vbox([
            Iup.Hbox([
              btn_image,
              btn_on_off,
              btn_exit]),
            text,
            btn_big]),
        :expand=>"YES",:title=>"IupButton",:resize=>"NO",
        :menubox=>"NO",:maxbox=>"NO",:minbox=>"NO")


	btn_on_off_cb = lambda do |ih|
	  # If the button with with image is active...
	  if(btn_image.active=="YES")
	    # Deactivates the button with image 
	    btn_image.active = "NO"
	  # else it is inactive 
	  else
	    # Activates the button with image 
	    btn_image.active = "YES"
	  end

	  # Executed function sucessfully 
	  Iup::DEFAULT
	end

	btn_image_button_cb = lambda do |ih,b,e,x,y,status|
	  # If the left button changed its state... 
	  if b == Iup::BUTTON1 
	    # If the button was pressed... 
	    if e == 1
	      # Sets text's value 
	      text.value = "Red button pressed"
	    # else the button was released 
	    else
	      # Sets text's value 
	      text.value = "Red button released"
	    end
	  end

	  # Executed function sucessfully 
	  Iup::DEFAULT
	end

	btn_exit_cb = lambda do |ih|
	  # Exits the program 
	  Iup::CLOSE
	end


  # Registers callbacks 
  btn_exit.action = btn_exit_cb
  btn_on_off.action = btn_on_off_cb
  btn_image.button_cb = btn_image_button_cb

  # Shows dialog on the center of the screen 
  dlg.ShowXY(Iup::CENTER, Iup::CENTER )

  # Initializes IUP main loop 
  Iup.MainLoop()

  dlg.Destroy()

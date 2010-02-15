require 'rubygems'
require 'iup'

def param_action(dialog,param_index,user_data)
  case(param_index)
  when -1
      puts("OK")
  when -2
      puts("Map")
  when -3
      puts("Cancel")
  else
      param_str =  "PARAM#{param_index}"
      param = dialog.GetNode(param_str)
      puts "#{param_str} = #{param.value}"
  end
  return 1
end

  pboolean = 1
  pinteger = 3456
  preal = 3.543
  pinteger2 = 192
  preal2 = 0.5
  pangle = 90.0
  pstring = "string text"
  plist = 2
  pstring2 = "second text\nsecond line"
  file_name = "test.jpg"


pboolean, pinteger, preal, pinteger2, preal2, pangle, pstring, plist, file_name, pstring2 =
  Iup.GetParam("Title", 'param_action', 0,
                   "Boolean: %b[No,Yes]\n"+
                   "Integer: %i\n"+
                   "Real 1: %r\n"+
                   "Sep1 %t\n"+
                   "Integer: %i[0,255]\n"+
                   "Real 2: %r[-1.5,1.5]\n"+
                   "Sep2 %t\n"+
                   "Angle: %a[0,360]\n"+
                   "String: %s\n"+
                   "List: %l|item1|item2|item3|\n" +
                   "File: %f[OPEN|*.bmp;*.jpg|CURRENT|NO|NO]\n"+
                   "Sep3 %t\n"+
                   "Multiline: %m\n",
                   pboolean, pinteger, preal, pinteger2, preal2, pangle, pstring, plist, file_name, pstring2)
  
  Iup.Messagef("IupGetParam",
              "Boolean Value: %d\n"+
              "Integer: %d\n"+
              "Real 1: %g\n"+
              "Integer: %d\n"+
              "Real 2: %g\n"+
              "Angle: %g\n"+
              "String: %s\n"+
              "List Index: %d\n"+ 
              "FileName: %s\n"+
              "Multiline: %s",
              pboolean, pinteger, preal, pinteger2, preal2, pangle, pstring, plist, file_name, pstring2);

  

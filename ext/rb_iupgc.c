#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupGetColor(VALUE self,VALUE v_x,VALUE v_y)
{
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int v;
	VALUE v_r;
	v = IupGetColor(x,y,&r,&g,&b);
	if(v==0) return Qnil;
	v_r = rb_ary_new3(3,INT2FIX(r),INT2FIX(g),INT2FIX(b));
	return v_r;
}

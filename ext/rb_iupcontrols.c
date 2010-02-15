#include <ruby.h>
#include "iup.h"
#include "rb_iup.h"

VALUE rb_IupControlsOpen(VALUE self)
{
	int v;
	v = IupControlsOpen();
	return INT2FIX((int)v);
}

VALUE rb_IupControlsClose(VALUE self)
{
	IupControlsClose();
	return Qnil;
}

VALUE rb_IupImageLibOpen(VALUE self)
{
	IupImageLibOpen();
	return Qnil;
}


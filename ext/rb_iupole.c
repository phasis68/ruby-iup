#include <ruby.h>
#include "iup.h"
#include "rb_iup.h"

VALUE rb_IupOleControl(VALUE self,VALUE v_ProgID)
{
	const char *ProgID = RSTRING_PTR(v_ProgID);
	Ihandle* v;
	v = IupOleControl(ProgID);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupOleControlOpen(VALUE self)
{
	IupOleControlOpen();
	return Qnil;
}
/*
VALUE rb_IupOleControl_getclass(VALUE self)
{
	IupOleControl_getclass();
	return Qnil;
}
*/

#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupTree(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupTree;
	Ihandle* v;
	IupControlsOpen();
	v = IupTree();
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupTree,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupTreeSetUserId(VALUE node,VALUE v_id,VALUE v_userid)
{
	int id = NUM2INT(v_id);
	void *userid = (void*)NUM2ULONG(v_userid);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupTreeSetUserId((Ihandle*)NUM2ULONG(v_ih),id,userid);
	return INT2FIX((int)v);
}

VALUE rb_IupTreeGetUserId(VALUE node,VALUE v_id)
{
	int id = NUM2INT(v_id);
	void* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupTreeGetUserId((Ihandle*)NUM2ULONG(v_ih),id);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupTreeGetId(VALUE node,VALUE v_userid)
{
	int v;
	void *userid = (void*)NUM2ULONG(v_userid);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupTreeGetId((Ihandle*)NUM2ULONG(v_ih),userid);
	return INT2FIX((int)v);
}

VALUE rb_IupTreeSetAttribute(VALUE node,VALUE v_a,VALUE v_id,VALUE v_v)
{
	const char* a = RSTRING_PTR(v_a);
	int id = NUM2INT(v_id);
	char* v = RSTRING_PTR(v_v);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupTreeSetAttribute((Ihandle*)NUM2ULONG(v_ih),a,id,v);
	return Qnil;
}

VALUE rb_IupTreeStoreAttribute(VALUE node,VALUE v_a,VALUE v_id,VALUE v_v)
{
	const char* a = RSTRING_PTR(v_a);
	int id = NUM2INT(v_id);
	char* v = RSTRING_PTR(v_v);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupTreeStoreAttribute((Ihandle*)NUM2ULONG(v_ih),a,id,v);
	return Qnil;
}

VALUE rb_IupTreeGetAttribute(VALUE node,VALUE v_a,VALUE v_id)
{
	const char* a = RSTRING_PTR(v_a);
	int id = NUM2INT(v_id);
	char* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupTreeGetAttribute((Ihandle*)NUM2ULONG(v_ih),a,id);
	return  rb_str_new2(v);
}

VALUE rb_IupTreeGetInt(VALUE node,VALUE v_a,VALUE v_id)
{
	const char* a = RSTRING_PTR(v_a);
	int id = NUM2INT(v_id);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupTreeGetInt((Ihandle*)NUM2ULONG(v_ih),a,id);
	return INT2FIX((int)v);
}

VALUE rb_IupTreeGetFloat(VALUE node,VALUE v_a,VALUE v_id)
{
	const char* a = RSTRING_PTR(v_a);
	int id = NUM2INT(v_id);
	float v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupTreeGetFloat((Ihandle*)NUM2ULONG(v_ih),a,id);
	return INT2FIX((int)v);
}


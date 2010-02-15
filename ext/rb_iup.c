#include <ruby.h>
#include "rb_iup.h"

extern VALUE rb_eIupError;
static char IdleAction[100];
static VALUE IdleProc = Qnil;

VALUE rb_mIup;
VALUE rb_mCd;
VALUE rb_eIupError;
VALUE rb_cIupImage;
VALUE rb_cIupButton;
VALUE rb_cIupCanvas;
VALUE rb_cIupDialog;
VALUE rb_cIupFill;
VALUE rb_cIupFrame;
VALUE rb_cIupHbox;
VALUE rb_cIupItem;
VALUE rb_cIupSeparator;
VALUE rb_cIupSubmenu;
VALUE rb_cIupLabel;
VALUE rb_cIupList;
VALUE rb_cIupMenu;
VALUE rb_cIupRadio;
VALUE rb_cIupText;
VALUE rb_cIupToggle;
VALUE rb_cIupToggle;
VALUE rb_cIupVbox;
VALUE rb_cIupZbox;
VALUE rb_cIupMultiLine;
VALUE rb_cIupUser;
VALUE rb_cIupControl;
VALUE rb_cIupTimer;
VALUE rb_cIupProgressBar;
VALUE rb_cIupFileDlg;
VALUE rb_cIupTree;
VALUE rb_cIupNode;
VALUE rb_cIupTabs;
VALUE rb_cIupGLCanvas;
VALUE rb_cIupSpin;
VALUE rb_cIupSpinbox;
VALUE rb_cIupSbox;
VALUE rb_cIupCbox;
VALUE rb_cIupMatrix;
VALUE rb_cIupGauge;
VALUE rb_cIupDial;
VALUE rb_cIupColorbar;
VALUE rb_cIupColorBrowser;
VALUE rb_cIupCells;
VALUE rb_cIupPPlot;
VALUE rb_cIupVal;
VALUE rb_cCdCanvas;

extern VALUE rb_IupSetCallback(VALUE node,VALUE v_name,VALUE v_func);

void exit_handler(void)
{
	IupControlsClose();
	IupClose();	
}

char* rb_str_upper(char* s) 
{
       char* temp=s;
       if(isupper(*temp)) return s;
       for(;*temp;temp++)
               *temp=toupper(*temp);
       return s;
}

VALUE rb_method_missing(int argc,VALUE *argv, VALUE self)
{
	static char mname[100];
	static char pname[100];
	int n;
	char *value = NULL;
	ID id = rb_to_id(argv[0]);
	VALUE v_ih = rb_iv_get(self,"@ihandle");
	strcpy(mname,rb_id2name(id));
	rb_str_upper(mname); 
	if(!*mname) {
        	rb_raise(rb_eRuntimeError, "fail: unknown method or property");
    	} 	
		n = strlen(mname);
    	if(mname[n-1] == '=') 
    		mname[n-1] = 0;
    	if(argc==2) {
		if(TYPE(argv[1])==T_OBJECT) {
			VALUE v_ih_named = rb_iv_get(argv[1],"@ihandle");
			IupSetAttributeHandle((Ihandle*)NUM2ULONG(v_ih),mname,(Ihandle*)NUM2ULONG(v_ih_named));
		}
		else if(TYPE(argv[1])==T_DATA) {
			rb_IupSetCallback(self,rb_str_new2(mname),rb_str_new2("Proc"));
			sprintf(pname,"RB_PROC_%s",mname);		
			IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),pname,(char*)argv[1]);
		} else {			
			if(strcmp(mname,"ATTR")==0) {			
				VALUE v_arr;
				int j;
				v_arr = rb_funcall(argv[1],rb_intern("split"),1,rb_reg_new("[,=]",4,0));	
				for(j=0;j<RARRAY_LEN(v_arr);j+=2) {
					rb_funcall(RARRAY_PTR(v_arr)[j],rb_intern("strip!"),0,0);
					rb_funcall(RARRAY_PTR(v_arr)[j+1],rb_intern("strip!"),0,0);
					strcpy(mname,RSTRING_PTR(RARRAY_PTR(v_arr)[j]));
					rb_str_upper(mname);
					value = RSTRING_PTR(RARRAY_PTR(v_arr)[j+1]);
					if(value[0]=='"') {
					  value[strlen(value)-1]=0;
					  strcpy(pname,&value[1]);
					  value = pname;
					}
					IupStoreAttribute((Ihandle*)NUM2ULONG(v_ih),mname,value);
				}				
			}
			else {
				if(argv[1]!=Qnil && TYPE(argv[1])!=T_STRING) {
				VALUE v_value = rb_funcall(argv[1],rb_intern("to_s"),0);
				value = RSTRING_PTR(v_value);
				} else if(argv[1]!=Qnil)	    			
	        			value = RSTRING_PTR(argv[1]);
	        		IupStoreAttribute((Ihandle*)NUM2ULONG(v_ih),mname,value);
	        	}
        	}
        	return Qnil;
    	}
    	else {       
    		Ihandle *ih = IupGetAttributeHandle((Ihandle*)NUM2ULONG(v_ih),mname);   
    		if(ih) {
			return (VALUE)IupGetAttribute(ih,"RB_CLASS");    			
    		}
    		else {	   
	        	value = IupGetAttribute((Ihandle*)NUM2ULONG(v_ih),mname);
	        	if(value==NULL) return Qnil;
	        	return rb_str_new2(value);
        	}
    	} 
}

void rb_set_attribute(Ihandle *v,VALUE arg) 
{
	static char key[100];
	static char pkey[100];
	static char value[1024];
	int i;
	VALUE v_value;
	VALUE klass;
	VALUE v_keys = rb_funcall(arg,rb_intern("keys"),0);
	for(i=0;i<RARRAY_LEN(v_keys);i++) {
		if(TYPE(RARRAY_PTR(v_keys)[i])==T_SYMBOL) {
			strcpy(key,rb_id2name(SYM2ID(RARRAY_PTR(v_keys)[i])));
			rb_str_upper(key);
		} else if(TYPE(RARRAY_PTR(v_keys)[i])==T_STRING) {
			strcpy(key,RSTRING_PTR(RARRAY_PTR(v_keys)[i]));
			rb_str_upper(key);
		}
		v_value = rb_hash_aref(arg,RARRAY_PTR(v_keys)[i]);
		if(TYPE(v_value)==T_OBJECT) {
			VALUE v_ih_named = rb_iv_get(v_value,"@ihandle");
			IupSetAttributeHandle(v,key,(Ihandle*)NUM2ULONG(v_ih_named));
		}
		else if(TYPE(v_value)==T_DATA) {
			klass = (VALUE)IupGetAttribute(v,"RB_CLASS");
			if(klass) {
				IupSetAttribute(v,key,(char*)v_value);
				rb_IupSetCallback(klass,rb_str_new2(key),rb_str_new2("Proc"));
			}
		} else {
			if(TYPE(v_value)!=T_STRING)
				v_value = rb_funcall(v_value,rb_intern("to_s"),0);
			strcpy(value,RSTRING_PTR(v_value));
			if(strcmp(key,"ATTR")==0) {			
				VALUE v_arr;
				int j;
				v_arr = rb_funcall(v_value,rb_intern("split"),1,rb_reg_new("[,=\\s]+",7,0));	
				for(j=0;j<RARRAY_LEN(v_arr);j+=2) {
					rb_funcall(RARRAY_PTR(v_arr)[j],rb_intern("strip!"),0,0);
					rb_funcall(RARRAY_PTR(v_arr)[j+1],rb_intern("strip!"),0,0);
					strcpy(key,RSTRING_PTR(RARRAY_PTR(v_arr)[j]));
					rb_str_upper(key);
					strcpy(value,RSTRING_PTR(RARRAY_PTR(v_arr)[j+1]));
					if(value[0]=='"') {
					  value[strlen(value)-1]=0;
					  strcpy(pkey,&value[1]);
					  strcpy(value,pkey);
					}
					IupStoreAttribute(v,key,value);
				}				
			}
			else
				IupStoreAttribute(v,key,value);
		}
	}
}

VALUE rb_isxkey(VALUE self,VALUE s)
{
	return isxkey(NUM2INT(s))?Qtrue:Qfalse;
}

VALUE rb_isshift(VALUE self,VALUE s)
{
	return isshift(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_iscontrol(VALUE self,VALUE s)
{
	return iscontrol(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isbutton1(VALUE self,VALUE s)
{
	return isbutton1(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isbutton2(VALUE self,VALUE s)
{
	return isbutton2(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isbutton3(VALUE self,VALUE s)
{
	return isbutton3(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isdouble(VALUE self,VALUE s)
{
	return isdouble(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isalt(VALUE self,VALUE s)
{
	return isalt(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_issys(VALUE self,VALUE s)
{
	return issys(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isbutton4(VALUE self,VALUE s)
{
	return isbutton4(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_isbutton5(VALUE self,VALUE s)
{
	return isbutton5(RSTRING_PTR(s))?Qtrue:Qfalse;
}

VALUE rb_IupFileDlg(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	v = IupFileDlg();
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupFileDlg,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupGetFile(VALUE self,VALUE v_arq)
{
	char *arq = RSTRING_PTR(v_arq);
	char filename[256];
	int v;
	VALUE v_r;
	strcpy(filename,arq);
	v = IupGetFile(filename);
	v_r = rb_ary_new3(2,rb_str_new2(filename),INT2NUM(v));
	return v_r;
}

VALUE rb_IupNode_initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE v_ih,v_action;
	rb_scan_args(argc,argv,"11",&v_ih,&v_action);
	IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),"RB_CLASS",(char*)self);
	rb_iv_set(self,"@ihandle",v_ih);
	if(TYPE(v_action)==T_DATA) {	
		IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),"RB_PROC_ACTION",(char*)v_action);
		rb_IupSetCallback(self,rb_str_new2("ACTION"),rb_str_new2("Proc"));
	}
	return self;
}

VALUE rb_IupMessage(VALUE self,VALUE v_title,VALUE v_msg)
{
	const char *title = RSTRING_PTR(v_title);
	const char *msg = RSTRING_PTR(v_msg);
	IupMessage(title,msg);
	return Qnil;
}

VALUE rb_IupMessagef(int argc,VALUE *argv,VALUE self)
{
	VALUE v;
	const char *title = RSTRING_PTR(argv[0]);
	const char *msg = RSTRING_PTR(argv[1]);
	if(argc==2) {
		IupMessage(title,msg);
		return Qnil;
	}
	v = rb_f_sprintf(argc-1,argv+1);
	msg = RSTRING_PTR(v);
	IupMessage(title,msg);
	return Qnil;
}

VALUE rb_IupAlarm(VALUE self,VALUE v_title,VALUE v_msg,VALUE v_b1,VALUE v_b2,VALUE v_b3)
{
	const char *title = RSTRING_PTR(v_title);
	const char *msg = RSTRING_PTR(v_msg);
	const char *b1 = RSTRING_PTR(v_b1);
	const char *b2 = RSTRING_PTR(v_b2);
	const char *b3 = RSTRING_PTR(v_b3);
	int v;
	v = IupAlarm(title,msg,b1,b2,b3);
	return INT2NUM(v);
}

VALUE rb_IupScanf(int argc,VALUE *argv,VALUE self)
{
	VALUE v_format = argv[0];
	char args[5][256];
	const char *format = RSTRING_PTR(v_format);
	int v;
	int i;
	int t_n;
	float t_f;
	char *t_s;
	VALUE v_r = Qnil;
	for(i=1;i<argc && i<=5;i++) {
		switch(TYPE(argv[i])) {
			case T_FIXNUM:
				t_n = NUM2INT(argv[i]);
				memcpy(args[i-1],&t_n,sizeof(t_n));
				break;
			case T_STRING:
				t_s = RSTRING_PTR(argv[i]);
				memcpy(args[i-1],t_s,RSTRING_LEN(argv[i])+1);
				break;
			case T_FLOAT:
				t_f = RFLOAT_VALUE(argv[i]);
				memcpy(args[i-1],&t_f,sizeof(t_f));
				break;
			default:
				rb_raise(rb_eIupError,"Invalid Type");
		}
	}
	switch(argc) {
		case 2:
			v = IupScanf(format,args[0]);
			break;
		case 3:
			v = IupScanf(format,args[0],args[1]);
			break;
		case 4:
			v = IupScanf(format,args[0],args[1],args[2]);
			break;
		case 5:
			v = IupScanf(format,args[0],args[1],args[2],args[3]);
			break;
		case 6:
			v = IupScanf(format,args[0],args[1],args[2],args[3],args[4]);
			break;
		default:
			rb_raise(rb_eIupError,"Too many arguments");
	}
	v_r = rb_ary_new();
	for(i=1;i<argc && i<=v;i++) {
		switch(TYPE(argv[i])) {
			case T_FIXNUM:
			case T_BIGNUM:
				memcpy(&t_n,args[i-1],sizeof(t_n));
				rb_ary_push(v_r,INT2NUM(t_n));
				break;
			case T_STRING:
				rb_ary_push(v_r,rb_str_new2(args[i-1]));
				break;
			case T_FLOAT:
				memcpy(&t_f,args[i-1],sizeof(t_f));
				sprintf(args[i-1],"%g",t_f);
				rb_ary_push(v_r,rb_float_new(atof(args[i-1])));
				break;
			default:
				rb_raise(rb_eIupError,"Invalid Type");
		}
	}
	return v_r;
}

VALUE  rb_IupListDialog (VALUE self,VALUE v_type, VALUE v_title, VALUE v_size, VALUE v_lst,
                    VALUE v_op, VALUE v_col, VALUE v_line, VALUE v_marks)
{
	int type = NUM2INT(v_type);
	const char* title = RSTRING_PTR(v_title);
	int size = NUM2INT(v_size);
	char *lst[256];
	int op = NUM2INT(v_op);
	int col = NUM2INT(v_col);
	int line = NUM2INT(v_line);
	int marks[256];
	int v;
	int i;
	VALUE v_r;
	for(i=0;i<size;i++) {
		lst[i] = RSTRING_PTR(RARRAY_PTR(v_lst)[i]);
		marks[i] = NUM2INT(RARRAY_PTR(v_marks)[i]);
	}
	v = IupListDialog(type,title,size,(const char**)lst,op,col,line,marks);
	v_marks = rb_ary_new();
	if(type==2) {
		for(i=0;i<size;i++) {
			rb_ary_push(v_marks,INT2FIX(marks[i]));
		}
	} else {
		for(i=0;i<size;i++) {
			if(v==i)
				rb_ary_push(v_marks,INT2FIX(1));
			else
				rb_ary_push(v_marks,INT2FIX(0));
		}
	}
	v_r = rb_ary_new3(2,v_marks,INT2FIX(v));
	return v_r;
}

VALUE rb_IupGetText(VALUE self,VALUE v_title,VALUE v_text)
{
	const char* title = RSTRING_PTR(v_title);
	char* text = RSTRING_PTR(v_text);
	int v;
	v = IupGetText(title,text);
	return INT2NUM(v);
}

VALUE rb_IupOpen(VALUE self)
{
	int argc = 1;
	char *name = "iupruby";
	char **argv = &name;
	int v;
	v = IupOpen(&argc,&argv);

	if(v==IUP_ERROR)
		 rb_raise(rb_eIupError, "Error Opening IUP.");
	IupControlsOpen();
	return INT2NUM(v);
}

VALUE rb_IupClose(VALUE self)
{
	IupClose();
	return Qnil;
}

int def_idle(void) {
	rb_funcall(Qnil,rb_intern("sleep"),1,INT2NUM(0));
	return IupLoopStep(); 
}

VALUE rb_IupMainLoop(VALUE self)
{
	int v;
	if(IupGetFunction("IDLE_ACTION")==NULL) {
		IupSetFunction("IDLE_ACTION",def_idle);
	}
	v = IupMainLoop();
	return INT2NUM(v);
}

VALUE rb_IupLoopStep(VALUE self)
{
	int v;
	v = IupLoopStep();
	return INT2NUM(v);
}

VALUE rb_IupFlush(VALUE self)
{
	IupFlush();
	return Qnil;
}

VALUE rb_IupExitLoop(VALUE self)
{
	IupExitLoop();
	return Qnil;
}

VALUE rb_IupUpdate(VALUE self,VALUE node)
{
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupUpdate((Ihandle*)NUM2ULONG(v_ih));
	return Qnil;
}

VALUE rb_IupRefresh(VALUE self,VALUE node)
{
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupRefresh((Ihandle*)NUM2ULONG(v_ih));
	return Qnil;
}

VALUE rb_IupMapFont(VALUE self,VALUE v_iupfont)
{
	const char *iupfont = RSTRING_PTR(v_iupfont);
	char* v;
	v = IupMapFont(iupfont);
	return  rb_str_new2(v);
}

VALUE rb_IupUnMapFont(VALUE self,VALUE v_driverfont)
{
	const char *driverfont = RSTRING_PTR(v_driverfont);
	char* v;
	v = IupUnMapFont(driverfont);
	return  rb_str_new2(v);
}

VALUE rb_IupHelp(VALUE self,VALUE v_url)
{
	const char* url = RSTRING_PTR(v_url);
	int v;
	v = IupHelp(url);
	return INT2NUM(v);
}

VALUE rb_IupVersion(VALUE self)
{
	char* v;
	v = IupVersion();
	return  rb_str_new2(v);
}

VALUE rb_IupVersionDate(VALUE self)
{
	char* v;
	v = IupVersionDate();
	return  rb_str_new2(v);
}

VALUE rb_IupVersionNumber(VALUE self)
{
	int v;
	v = IupVersionNumber();
	return INT2NUM(v);
}

VALUE rb_IupSetLanguage(VALUE self,VALUE v_lng)
{
	const char *lng = RSTRING_PTR(v_lng);
	IupSetLanguage(lng);
	return Qnil;
}

VALUE rb_IupGetLanguage(VALUE self)
{
	char* v;
	v = IupGetLanguage();
	return  rb_str_new2(v);
}

VALUE rb_IupDestroy(VALUE node)
{
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupDestroy((Ihandle*)NUM2ULONG(v_ih));
	return Qnil;
}

VALUE rb_IupDetach(VALUE self,VALUE vchild)
{
	VALUE v_child = rb_iv_get(vchild,"@ihandle");
	IupDetach((Ihandle*)NUM2ULONG(v_child));
	return Qnil;
}

VALUE rb_IupAppend(VALUE self,VALUE node,VALUE vchild)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	VALUE v_child = rb_iv_get(vchild,"@ihandle");
	v = IupAppend((Ihandle*)NUM2ULONG(v_ih),(Ihandle*)NUM2ULONG(v_child));
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetNextChild(VALUE self,VALUE node,VALUE vchild)
{
	Ihandle* child = NULL;
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	VALUE v_child = rb_iv_get(vchild,"@ihandle");
	if(v_child!=Qnil) child = (Ihandle*)NUM2ULONG(v_child);
	v = IupGetNextChild((Ihandle*)NUM2ULONG(v_ih),child);
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetBrother(VALUE self,VALUE node)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetBrother((Ihandle*)NUM2ULONG(v_ih));
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetParent(VALUE self,VALUE node)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetParent((Ihandle*)NUM2ULONG(v_ih));
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetDialog(VALUE self,VALUE node)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetDialog((Ihandle*)NUM2ULONG(v_ih));
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupPopup(VALUE node,VALUE v_x,VALUE v_y)
{
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupPopup((Ihandle*)NUM2ULONG(v_ih),x,y);
	return INT2NUM(v);
}

VALUE rb_IupShow(VALUE node)
{
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupShow((Ihandle*)NUM2ULONG(v_ih));
	return INT2NUM(v);
}

VALUE rb_IupShowXY(VALUE node,VALUE v_x,VALUE v_y)
{
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupShowXY((Ihandle*)NUM2ULONG(v_ih),x,y);
	return INT2NUM(v);
}

VALUE rb_IupHide(VALUE node)
{
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupHide((Ihandle*)NUM2ULONG(v_ih));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupMap(VALUE node)
{
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupMap((Ihandle*)NUM2ULONG(v_ih));
	return INT2NUM(v);
}

VALUE rb_IupSetAttribute(VALUE node,VALUE v_name,VALUE v_value)
{
	static char name[100];
	static char pname[100];
	const char* value = NULL;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	strcpy(name,RSTRING_PTR(v_name));
	rb_str_upper(name);
	if(v_value!=Qnil) {
		if(TYPE(v_value)==T_OBJECT) {
			VALUE v_ih_named = rb_iv_get(v_value,"@ihandle");
			IupSetAttributeHandle((Ihandle*)NUM2ULONG(v_ih),name,(Ihandle*)NUM2ULONG(v_ih_named));
		}
		else if(TYPE(v_value)==T_DATA) {
			rb_IupSetCallback(node,rb_str_new2(name),rb_str_new2("Proc"));
			sprintf(pname,"RB_PROC_%s",name);
			IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),pname,(char*)v_value);
			return Qnil;
		} else {
			if(TYPE(v_value)!=T_STRING)
				v_value = rb_funcall(v_value,rb_intern("to_s"),0);
			value = RSTRING_PTR(v_value);
		}
	}
	IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),name,value);
	return Qnil;
}

VALUE rb_IupSetAttributePtr(VALUE node,VALUE v_name,VALUE v_value)
{
        extern VALUE rb_IupSetCallback(VALUE node,VALUE v_name,VALUE v_func);
	char name[100];
	const char* value = NULL;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	strcpy(name,RSTRING_PTR(v_name));
	rb_str_upper(name);
	if(v_value!=Qnil) {
		if(TYPE(v_value)==T_DATA) {
			IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),name,(char*)v_value);
			rb_IupSetCallback(node,rb_str_new2(name),rb_str_new2("Proc"));
			return Qnil;
		} else {
			if(TYPE(v_value)==T_FIXNUM)
				value = (char*)NUM2ULONG(v_value);
		}
	}
	IupSetAttribute((Ihandle*)NUM2ULONG(v_ih),name,value);
	return Qnil;
}

VALUE rb_IupStoreAttribute(VALUE node,VALUE v_name,VALUE v_value)
{
	const char* name = RSTRING_PTR(v_name);
	const char* value = NULL;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	if(v_value!=Qnil)
		value = RSTRING_PTR(v_value);
	IupStoreAttribute((Ihandle*)NUM2ULONG(v_ih),name,value);
	return Qnil;
}

VALUE rb_IupSetAttributes(VALUE node,VALUE v_str)
{
	const char *str = RSTRING_PTR(v_str);
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupSetAttributes((Ihandle*)NUM2ULONG(v_ih),str);
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetAttribute(VALUE node,VALUE v_name)
{
	char name[100];
	char* v;
	Ihandle *ih;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	strcpy(name,RSTRING_PTR(v_name));
	rb_str_upper(name);
	ih = IupGetAttributeHandle((Ihandle*)NUM2ULONG(v_ih),name);   
	if(ih) {
		return (VALUE)IupGetAttribute(ih,"RB_CLASS");    			
	}
	v = IupGetAttribute((Ihandle*)NUM2ULONG(v_ih),name);
	if(v==NULL)
		return Qnil;
	else
		return rb_str_new2(v);
}

VALUE rb_IupGetAttributePtr(VALUE node,VALUE v_name)
{
	char name[100];
	char* v;
	VALUE klass;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	strcpy(name,RSTRING_PTR(v_name));
	rb_str_upper(name);
	v = IupGetAttribute((Ihandle*)NUM2ULONG(v_ih),name);	
	klass = rb_funcall(rb_cIupNode,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	if(v==NULL)
		return Qnil;
	else
		return klass;
}

VALUE rb_IupGetAttributes(VALUE node)
{
	char* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetAttributes((Ihandle*)NUM2ULONG(v_ih));
	return  rb_str_new2(v);
}

VALUE rb_IupGetInt(VALUE node,VALUE v_name)
{
	const char* name = RSTRING_PTR(v_name);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetInt((Ihandle*)NUM2ULONG(v_ih),name);
	return INT2NUM(v);
}

VALUE rb_IupGetFloat(VALUE node,VALUE v_name)
{
	const char* name = RSTRING_PTR(v_name);
	float v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetFloat((Ihandle*)NUM2ULONG(v_ih),name);
	return rb_float_new(v);
}

VALUE rb_IupSetGlobal(VALUE self,VALUE v_name,VALUE v_value)
{
	const char* name = RSTRING_PTR(v_name);
	const char* value = RSTRING_PTR(v_value);
	IupSetGlobal(name,value);
	return Qnil;
}

VALUE rb_IupStoreGlobal(VALUE self,VALUE v_name,VALUE v_value)
{
	const char* name = RSTRING_PTR(v_name);
	const char* value = RSTRING_PTR(v_value);
	IupStoreGlobal(name,value);
	return Qnil;
}

VALUE rb_IupGetGlobal(VALUE self,VALUE v_name)
{
	const char* name = RSTRING_PTR(v_name);
	char* v;
	v = IupGetGlobal(name);
	return  rb_str_new2(v);
}

VALUE rb_IupSetFocus(VALUE self,VALUE node)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupSetFocus((Ihandle*)NUM2ULONG(v_ih));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupGetFocus(VALUE self)
{
	Ihandle* v;
	v = IupGetFocus();
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupPreviousField(VALUE self,VALUE node)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupPreviousField((Ihandle*)NUM2ULONG(v_ih));
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupNextField(VALUE self,VALUE node)
{
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupNextField((Ihandle*)NUM2ULONG(v_ih));
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

static int _canvas_action(Ihandle* ih, float posx, float posy)
{
	char* func = (char*)IupGetAttribute(ih,"RB_ACTION");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_ACTION");
			v = rb_funcall(proc,rb_intern("call"),3,node,rb_float_new(posx),rb_float_new(posy));
		} else {
			v = rb_funcall(Qnil,rb_intern(func),3,node,rb_float_new(posx),rb_float_new(posy));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _toggle_action(Ihandle* ih, int state)
{
	char* func = (char*)IupGetAttribute(ih,"RB_ACTION");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_ACTION");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(state));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(state));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _button_action(Ihandle* ih)
{
	char* func = (char*)IupGetAttribute(ih,"RB_ACTION");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_ACTION");
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _list_action(Ihandle* ih, char *text, int pos, int state)
{
	char* func = (char*)IupGetAttribute(ih,"RB_ACTION");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_ACTION");
			v = rb_funcall(proc,rb_intern("call"),4,node,rb_str_new2(text),INT2FIX(pos),INT2FIX(state));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),4,node,rb_str_new2(text),INT2FIX(pos),INT2FIX(state));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _idle_cb()
{
	VALUE v;
	if(IdleProc!=Qnil) {
		v = rb_funcall(IdleProc,rb_intern("call"),0);
		return NUM2INT(v);
	}
	else if(*IdleAction) {
		v = rb_funcall(rb_cObject,rb_intern(IdleAction),0);
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _postdraw_cb(Ihandle* ih,void *cnv)
{
	char* func = (char*)IupGetAttribute(ih,"RB_POSTDRAW_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_POSTDRAW_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _predraw_cb(Ihandle* ih,void *cnv)
{
	char* func = (char*)IupGetAttribute(ih,"RB_PREDRAW_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_PREDRAW_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _change_cb(Ihandle* ih, unsigned char r, unsigned char g, unsigned char b)
{
	char* func = (char*)IupGetAttribute(ih,"RB_CHANGE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_CHANGE_CB");
			v = rb_funcall(proc,rb_intern("call"),4,node,INT2FIX(r),INT2FIX(g),INT2FIX(b));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),4,node,INT2FIX(r),INT2FIX(g),INT2FIX(b));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _drag_cb(Ihandle* ih, unsigned char r, unsigned char g, unsigned char b)
{
	char* func = (char*)IupGetAttribute(ih,"RB_DRAG_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_DRAG_CB");
			v = rb_funcall(proc,rb_intern("call"),4,node,INT2FIX(r),INT2FIX(g),INT2FIX(b));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),4,node,INT2FIX(r),INT2FIX(g),INT2FIX(b));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _tabchange_cb(Ihandle* ih, Ihandle* newtab, Ihandle* oldtab)
{
	char* func = (char*)IupGetAttribute(ih,"RB_TABCHANGE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		VALUE node_old = (VALUE)IupGetAttribute(oldtab,"RB_CLASS");
		VALUE node_new = (VALUE)IupGetAttribute(newtab,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_TABCHANGE_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,node_new,node_old);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,node_new,node_old);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _button_press_cb(Ihandle* ih, double angle)
{
	char* func = (char*)IupGetAttribute(ih,"RB_BUTTON_PRESS_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_BUTTON_PRESS_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,rb_float_new(angle));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,rb_float_new(angle));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _button_release_cb(Ihandle* ih, double angle)
{
	char* func = (char*)IupGetAttribute(ih,"RB_BUTTON_RELEASE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_BUTTON_RELEASE_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,rb_float_new(angle));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,rb_float_new(angle));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _mousemove_cb(Ihandle* ih, double angle)
{
	char* func = (char*)IupGetAttribute(ih,"RB_MOUSEMOVE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_MOUSEMOVE_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,rb_float_new(angle));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,rb_float_new(angle));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _draw_cb(Ihandle* ih, void* cnv)
{
	char* func = (char*)IupGetAttribute(ih,"RB_DRAW_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_DRAW_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,
				rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,
				rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static char* _cell_cb(Ihandle* ih, int cell)
{
	char* func = (char*)IupGetAttribute(ih,"RB_CELL_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_CELL_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(cell));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(cell));
		}
		if(v==Qnil)
			return NULL;
		else
			return RSTRING_PTR(v);
	}
	return NULL;
}

static int _extended_cb(Ihandle* ih, int cell)
{
	char* func = (char*)IupGetAttribute(ih,"RB_EXTENDED_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_EXTENDED_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(cell));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(cell));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _colorbar_select_cb(Ihandle* ih, int cell,int type)
{
	char* func = (char*)IupGetAttribute(ih,"RB_SELECT_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_SELECT_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(cell),INT2FIX(type));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(cell),INT2FIX(type));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _switch_cb(Ihandle* ih, int prim_cell,int sec_cell)
{
	char* func = (char*)IupGetAttribute(ih,"RB_SWITCH_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_SWITCH_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(prim_cell),INT2FIX(sec_cell));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(prim_cell),INT2FIX(sec_cell));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _height_cb(Ihandle* ih, int line)
{
	char* func = (char*)IupGetAttribute(ih,"RB_HEIGHT_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_HEIGHT_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(line));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(line));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _width_cb(Ihandle* ih, int column)
{
	char* func = (char*)IupGetAttribute(ih,"RB_WIDTH_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_WIDTH_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(column));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(column));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _hspan_cb(Ihandle* ih, int line, int column)
{
	char* func = (char*)IupGetAttribute(ih,"RB_HSPAN_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_HSPAN_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(line),INT2FIX(column));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(line),INT2FIX(column));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _scrolling_cb(Ihandle* ih, int line, int column)
{
	char* func = (char*)IupGetAttribute(ih,"RB_SCROLLING_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_SCROLLING_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(line),INT2FIX(column));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(line),INT2FIX(column));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _vspan_cb(Ihandle* ih, int line, int column)
{
	char* func = (char*)IupGetAttribute(ih,"RB_VSPAN_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_VSPAN_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(line),INT2FIX(column));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(line),INT2FIX(column));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _ncols_cb(Ihandle* ih)
{
	char* func = (char*)IupGetAttribute(ih,"RB_NCOLS_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_NCOLS_CB");
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _nlines_cb(Ihandle* ih)
{
	char* func = (char*)IupGetAttribute(ih,"RB_NLINES_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_NLINES_CB");
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _mouseclick_cb(Ihandle* ih,int button, int pressed, int line, int column, int x, int y, char* status)
{
	char* func = (char*)IupGetAttribute(ih,"RB_MOUSECLICK_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_MOUSECLICK_CB");
			v = rb_funcall(proc,rb_intern("call"),8,node,INT2FIX(button),INT2FIX(pressed),
			INT2FIX(line),INT2FIX(column),INT2FIX(x),INT2FIX(y),rb_str_new2(status));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),8,node,INT2FIX(button),INT2FIX(pressed),
			INT2FIX(line),INT2FIX(column),INT2FIX(x),INT2FIX(y),rb_str_new2(status));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _mousemotion_cb(Ihandle* ih,int line, int column, int x, int y, char* r)
{
	char* func = (char*)IupGetAttribute(ih,"RB_MOUSEMOTION_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_MOUSEMOTION_CB");
			v = rb_funcall(proc,rb_intern("call"),8,node,
			INT2FIX(line),INT2FIX(column),INT2FIX(x),INT2FIX(y),rb_str_new2(r));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),8,node,
			INT2FIX(line),INT2FIX(column),INT2FIX(x),INT2FIX(y),rb_str_new2(r));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _motion_cb(Ihandle* ih,int x, int y, char* status)
{
	char* func = (char*)IupGetAttribute(ih,"RB_MOTION_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_MOTION_CB");
			v = rb_funcall(proc,rb_intern("call"),4,node,
			INT2FIX(x),INT2FIX(y),rb_str_new2(status));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),4,node,
			INT2FIX(x),INT2FIX(y),rb_str_new2(status));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _cell_draw_cb(Ihandle* ih,int line, int column, int xmin, int xmax, int ymin, int ymax)
{
	char* func = (char*)IupGetAttribute(ih,"RB_DRAW_CB");
	VALUE v;
	void *cnv = (void*)cdActiveCanvas();
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_DRAW_CB");
			v = rb_funcall(proc,rb_intern("call"),8,node,
			INT2FIX(line),INT2FIX(column),INT2FIX(xmin),INT2FIX(xmax),INT2FIX(ymin),INT2FIX(ymax),
			rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),8,node,
			INT2FIX(line),INT2FIX(column),INT2FIX(xmin),INT2FIX(xmax),INT2FIX(ymin),INT2FIX(ymax),rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)cnv)));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _delete_cb(Ihandle* ih, int index, int sample_index, float x, float y)
{
	char* func = (char*)IupGetAttribute(ih,"RB_DELETE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_DELETE_CB");
			v = rb_funcall(proc,rb_intern("call"),5,node,INT2FIX(index),
			INT2FIX(sample_index),rb_float_new(x),rb_float_new(y));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),5,node,INT2FIX(index),
			INT2FIX(sample_index),rb_float_new(x),rb_float_new(y));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _select_cb(Ihandle* ih, int index, int sample_index, float x, float y, int select)
{
	char* func = (char*)IupGetAttribute(ih,"RB_SELECT_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_SELECT_CB");
			v = rb_funcall(proc,rb_intern("call"),6,node,INT2FIX(index),
			INT2FIX(sample_index),rb_float_new(x),rb_float_new(y),INT2FIX(select));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),6,node,INT2FIX(index),
			INT2FIX(sample_index),rb_float_new(x),rb_float_new(y),INT2FIX(select));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _edit_cb(Ihandle* ih, int index, int sample_index, float x, float y, float* new_x, float* new_y)
{
	char* func = (char*)IupGetAttribute(ih,"RB_EDIT_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_EDIT_CB");
			v = rb_funcall(proc,rb_intern("call"),7,node,INT2FIX(index),
			INT2FIX(sample_index),rb_float_new(x),rb_float_new(y),rb_float_new(*new_x),rb_float_new(*new_y));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),7,node,INT2FIX(index),
			INT2FIX(sample_index),rb_float_new(x),rb_float_new(y),rb_float_new(*new_x),rb_float_new(*new_y));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _list_edit_cb(Ihandle *ih, int c, char *new_value)
{
	char* func = (char*)IupGetAttribute(ih,"RB_EDIT_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_EDIT_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(c),rb_str_new2(new_value)); 
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(c),rb_str_new2(new_value)); 
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _text_action(Ihandle *ih, int c, char *new_value)
{
	char* func = (char*)IupGetAttribute(ih,"RB_ACTION");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_ACTION");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(c),rb_str_new2(new_value));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(c),rb_str_new2(new_value));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _button_cb(Ihandle* ih, int button, int pressed, int x, int y, char* status)
{
	char* func = (char*)IupGetAttribute(ih,"RB_BUTTON_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_BUTTON_CB");
			v = rb_funcall(proc,rb_intern("call"),6,node,INT2FIX(button),INT2FIX(pressed),
			INT2FIX(x),INT2FIX(y),rb_str_new2(status));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),6,node,INT2FIX(button),INT2FIX(pressed),
			INT2FIX(x),INT2FIX(y),rb_str_new2(status));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _executeleaf_cb(Ihandle* ih, int id)
{
	char* func = (char*)IupGetAttribute(ih,"RB_EXECUTELEAF_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_EXECUTELEAF_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(id));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(id));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _branchopen_cb(Ihandle* ih, int id)
{
	char* func = (char*)IupGetAttribute(ih,"RB_BRANCHOPEN_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_BRANCHOPEN_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(id));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(id));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _branchclose_cb(Ihandle* ih, int id)
{
	char* func = (char*)IupGetAttribute(ih,"RB_BRANCHCLOSE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_BRANCHCLOSE_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(id));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(id));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _rightclick_cb(Ihandle* ih, int id)
{
	char* func = (char*)IupGetAttribute(ih,"RB_RIGHTCLICK_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_RIGHTCLICK_CB");
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(id));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(id));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _k_any_cb(Ihandle* ih, int c)
{
	extern char *iupKeyCodeToName(int c);
	char* func = NULL;
	VALUE v;
	static char key[100];
	static char pkey[100];
	sprintf(key,"RB_%s",(char*)iupKeyCodeToName(c));
	func = (char*)IupGetAttribute(ih,key);
	if(func==NULL) {
		func = (char*)IupGetAttribute(ih,"RB_K_ANY");
		strcpy(key,"RB_K_ANY");
	}
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc;
			sprintf(pkey,"RB_PROC_%s",&key[3]);
			proc = (VALUE)IupGetAttribute(ih,pkey);
			v = rb_funcall(proc,rb_intern("call"),2,node,INT2FIX(c));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),2,node,INT2FIX(c));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _renamenode_cb(Ihandle* ih, int id, char *name)
{
	char* func = (char*)IupGetAttribute(ih,"RB_RENAMENODE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_RENAMENODE_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(id),rb_str_new2(name));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(id),rb_str_new2(name));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _rename_cb(Ihandle* ih, int id, char *name)
{
	char* func = (char*)IupGetAttribute(ih,"RB_RENAME_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_RENAME_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(id),rb_str_new2(name));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(id),rb_str_new2(name));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _dragdrop_cb(Ihandle *ih, int drag_id, int drop_id, int isshift, int iscontrol)
{
	char* func = (char*)IupGetAttribute(ih,"RB_DRAGDROP_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_DRAGDROP_CB");
			v = rb_funcall(proc,rb_intern("call"),5,node,
			INT2FIX(drag_id),INT2FIX(drop_id),INT2FIX(isshift),INT2FIX(iscontrol));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),5,node,
			INT2FIX(drag_id),INT2FIX(drop_id),INT2FIX(isshift),INT2FIX(iscontrol));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _action_cb(Ihandle* ih)
{
	char *key = "RB_PROC_ACTION";
	char* func = (char*)IupGetAttribute(ih,"RB_ACTION");
	VALUE v;
	if(func==NULL) {
		func = (char*)IupGetAttribute(ih,"RB_ACTION_CB");
		key = "RB_PROC_ACTION_CB";
	}
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,key);
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _mdiactivate_cb(Ihandle* ih)
{
	char* func = (char*)IupGetAttribute(ih,"RB_MDIACTIVATE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_MDIACTIVATE_CB");
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _getfocus_cb(Ihandle* ih)
{
	char* func = (char*)IupGetAttribute(ih,"RB_GETFOCUS_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_GETFOCUS_CB");
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _killfocus_cb(Ihandle* ih)
{
	char* func = (char*)IupGetAttribute(ih,"RB_KILLFOCUS_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_KILLFOCUS_CB");
			v = rb_funcall(proc,rb_intern("call"),1,node);
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),1,node);
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _trayclick_cb(Ihandle* ih, int b, int press, int dclick)
{
	char* func = (char*)IupGetAttribute(ih,"RB_TRAYCLICK_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_TRAYCLICK_CB");
			v = rb_funcall(proc,rb_intern("call"),4,node,INT2FIX(b),rb_float_new(press),rb_float_new(dclick));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),4,node,INT2FIX(b),rb_float_new(press),rb_float_new(dclick));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _scroll_cb(Ihandle* ih, int op, float posx, float posy)
{
	char* func = (char*)IupGetAttribute(ih,"RB_SCROLL_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_SCROLL_CB");
			v = rb_funcall(proc,rb_intern("call"),4,node,INT2FIX(op),rb_float_new(posx),rb_float_new(posy));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),4,node,INT2FIX(op),rb_float_new(posx),rb_float_new(posy));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

static int _resize_cb(Ihandle* ih, int width, int height)
{
	char* func = (char*)IupGetAttribute(ih,"RB_RESIZE_CB");
	VALUE v;
	if(func) {
		VALUE node = (VALUE)IupGetAttribute(ih,"RB_CLASS");
		if(strcmp(func,"Proc")==0) {
			VALUE proc = (VALUE)IupGetAttribute(ih,"RB_PROC_RESIZE_CB");
			v = rb_funcall(proc,rb_intern("call"),3,node,INT2FIX(width),INT2FIX(height));
		} else {
			v = rb_funcall(rb_cObject,rb_intern(func),3,node,INT2FIX(width),INT2FIX(height));
		}
		return NUM2INT(v);
	}
	return IUP_DEFAULT;
}

VALUE rb_IupGetCallback(VALUE node,VALUE v_name)
{
	const char *name = RSTRING_PTR(v_name);
	Icallback v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetCallback((Ihandle*)NUM2ULONG(v_ih),name);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupSetCallback(VALUE node,VALUE v_name,VALUE v_func)
{
	const char *name = RSTRING_PTR(v_name);
	const char *func = NULL;
	char cb_name[100] = "RB_";
	VALUE klass = Qnil;
	Icallback v = (Icallback)NULL;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	if(v_func!=Qnil) func = RSTRING_PTR(v_func);
	strcat(cb_name,name);
	IupStoreAttribute((Ihandle*)NUM2ULONG(v_ih),cb_name,func);
	klass = rb_funcall(node,rb_intern("class"),0,0);
	if(strcmp(name,"DRAW_CB")==0)
		if(klass==rb_cIupCells)
			v = (Icallback)_cell_draw_cb;
		else
			v = (Icallback)_draw_cb;
	else if(strcmp(name,"HEIGHT_CB")==0)
		v = (Icallback)_height_cb;
	else if(strcmp(name,"HSPAN_CB")==0)
		v = (Icallback)_hspan_cb;
	else if(strcmp(name,"MOUSECLICK_CB")==0)
		v = (Icallback)_mouseclick_cb;
	else if(strcmp(name,"MOUSEMOTION_CB")==0)
		v = (Icallback)_mousemotion_cb;
	else if(strcmp(name,"MOTION_CB")==0)
		v = (Icallback)_motion_cb;
	else if(strcmp(name,"NCOLS_CB")==0)
		v = (Icallback)_ncols_cb;
	else if(strcmp(name,"NLINES_CB")==0)
		v = (Icallback)_nlines_cb;
	else if(strcmp(name,"SCROLLING_CB")==0)
		v = (Icallback)_scrolling_cb;
	else if(strcmp(name,"VSPAN_CB")==0)
		v = (Icallback)_vspan_cb;
	else if(strcmp(name,"WIDTH_CB")==0)
		v = (Icallback)_width_cb;
	else if(strcmp(name,"DELETE_CB")==0)
		v = (Icallback)_delete_cb;
	else if(strcmp(name,"SELECT_CB")==0) {
		if(klass==rb_cIupColorbar) 
			v = (Icallback)_colorbar_select_cb;
		else
			v = (Icallback)_select_cb;
	}
	else if(strcmp(name,"EDIT_CB")==0) {
		if(klass==rb_cIupList) 
			v = (Icallback)_list_edit_cb;
		else
			v = (Icallback)_edit_cb;
	}
	else if(strcmp(name,"BUTTON_CB")==0)
		v = (Icallback)_button_cb;
	else if(strcmp(name,"BUTTON_PRESS_CB")==0)
		v = (Icallback)_button_press_cb;
	else if(strcmp(name,"BUTTON_RELEASE_CB")==0)
		v = (Icallback)_button_release_cb;
	else if(strcmp(name,"MOUSEMOVE_CB")==0)
		v = (Icallback)_mousemove_cb;
	else if(strcmp(name,"SCROLL_CB")==0) 
		v = (Icallback)_scroll_cb;
	else if(strcmp(name,"RESIZE_CB")==0)
		v = (Icallback)_resize_cb;
	else if(strcmp(name,"ACTION")==0) {
		if(rb_class_inherited_p(klass,rb_cIupCanvas)==Qtrue) 
			v = (Icallback)_canvas_action;
		else if(klass==rb_cIupToggle) 
			v = (Icallback)_toggle_action;
		else if(klass==rb_cIupButton) 
			v = (Icallback)_button_action;
		else if(klass==rb_cIupText||klass==rb_cIupMultiLine) 
			v = (Icallback)_text_action;
		else if(klass==rb_cIupList) 
			v = (Icallback)_list_action;
		else 
			v = (Icallback)_action_cb;
	}
	else if(strcmp(name,"ACTION_CB")==0)
		v = (Icallback)_action_cb;
	else if(strcmp(name,"MDIACTIVATE_CB")==0)
		v = (Icallback)_mdiactivate_cb;
	else if(strcmp(name,"GETFOCUS_CB")==0)
		v = (Icallback)_getfocus_cb;
	else if(strcmp(name,"KILLFOCUS_CB")==0)
		v = (Icallback)_killfocus_cb;
	else if(strcmp(name,"TRAYCLICK_CB")==0)
		v = (Icallback)_trayclick_cb;
	else if(strcmp(name,"DRAG_CB")==0)
		v = (Icallback)_drag_cb;
	else if(strcmp(name,"CHANGE_CB")==0)
		v = (Icallback)_change_cb;
	else if(strcmp(name,"TABCHANGE_CB")==0)
		v = (Icallback)_tabchange_cb;
	else if(strcmp(name,"POSTDRAW_CB")==0)
		v = (Icallback)_postdraw_cb;
	else if(strcmp(name,"PREDRAW_CB")==0)
		v = (Icallback)_predraw_cb;
	else if(strcmp(name,"CELL_CB")==0)
		v = (Icallback)_cell_cb;
	else if(strcmp(name,"EXTENDED_CB")==0)
		v = (Icallback)_extended_cb;
	else if(strcmp(name,"SWITCH_CB")==0)
		v = (Icallback)_switch_cb;
	else if(strcmp(name,"EXECUTELEAF_CB")==0)
		v = (Icallback)_executeleaf_cb;
	else if(strcmp(name,"RENAMENODE_CB")==0)
		v = (Icallback)_renamenode_cb;
	else if(strcmp(name,"RENAME_CB")==0)
		v = (Icallback)_rename_cb;
	else if(strcmp(name,"BRANCHCLOSE_CB")==0)
		v = (Icallback)_branchclose_cb;
	else if(strcmp(name,"BRANCHOPEN_CB")==0)
		v = (Icallback)_branchopen_cb;
	else if(strcmp(name,"DRAGDROP_CB")==0)
		v = (Icallback)_dragdrop_cb;
	else if(strcmp(name,"RIGHTCLICK_CB")==0)
		v = (Icallback)_rightclick_cb;
	else if(strcmp(name,"K_ANY")==0)
		v = (Icallback)_k_any_cb;
	else if(strncmp(name,"K_",2)==0)
		v = (Icallback)_k_any_cb;
	v = IupSetCallback((Ihandle*)NUM2ULONG(v_ih),name,v);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupGetIdle(VALUE self)
{
	Icallback v;
	v = IupGetFunction("IDLE_ACTION");
	if(v)
		return ULONG2NUM((unsigned long)v);
	return Qnil;
}

VALUE rb_IupGetFunction(VALUE self,VALUE v_name)
{
	const char *name = RSTRING_PTR(v_name);
	Icallback v;
	v = IupGetFunction(name);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupSetIdle(VALUE self,VALUE v_func)
{
	Icallback func = NULL;
	Icallback v;
	if(v_func==Qnil) {
		*IdleAction=0;
		IdleProc = Qnil;
	}
	else if(TYPE(v_func)==T_DATA) {
		IdleProc = v_func;
		func = (Icallback)_idle_cb;
	}
	else if(TYPE(v_func)==T_STRING) {
		strcpy(IdleAction,RSTRING_PTR(v_func));
		func = (Icallback)_idle_cb;
	}
	v = IupSetFunction("IDLE_ACTION",func);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupSetFunction(VALUE self,VALUE v_name,VALUE v_func)
{
	const char *name = RSTRING_PTR(v_name);
	Icallback func = NULL;
	Icallback v;
	if(strcmp(name,"IDLE_ACTION")==0) {
		if(v_func==Qnil) {
			*IdleAction=0;
			IdleProc = Qnil;
		}
		else if(TYPE(v_func)==T_DATA) {
			IdleProc = v_func;
			func = (Icallback)_idle_cb;
		}
		else if(TYPE(v_func)==T_STRING) {
			strcpy(IdleAction,RSTRING_PTR(v_func));
			func = (Icallback)_idle_cb;
		}
	} else {
		func = (Icallback)_action_cb;
	}
	v = IupSetFunction(name,func);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_IupGetActionName(VALUE self)
{
	const char* v;
	v = IupGetActionName();
	return  rb_str_new2(v);
}

VALUE rb_IupGetHandle(VALUE self,VALUE v_name)
{
	const char *name = RSTRING_PTR(v_name);
	Ihandle* v;
	v = IupGetHandle(name);
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupSetHandle(VALUE self,VALUE v_name,VALUE node)
{
	const char *name = RSTRING_PTR(v_name);
	Ihandle* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupSetHandle(name,(Ihandle*)NUM2ULONG(v_ih));
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetAllNames(VALUE self,VALUE v_n)
{
	int n = NUM2INT(v_n);
	int i;
	VALUE v_r;
	int v;
	char **names = xmalloc(n*(sizeof(char*)));
	v_r = rb_ary_new();
	v = IupGetAllNames(names,n);
	for(i=0;i<n && i<v;i++)
	  rb_ary_push(v_r,rb_str_new2(names[i]));
	free(names);
	return v_r;
}

VALUE rb_IupGetAllDialogs(VALUE self,VALUE v_n)
{
	int n = NUM2INT(v_n);
	int i;
	VALUE v_r;
	int v;
	char **names = xmalloc(n*(sizeof(char*)));
	v_r = rb_ary_new();
	v = IupGetAllDialogs(names,n);
	for(i=0;i<n && i<v;i++)
	  rb_ary_push(v_r,rb_str_new2(names[i]));
	free(names);
	return v_r;
}

VALUE rb_IupGetName(VALUE self,VALUE node)
{
	char* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetName((Ihandle*)NUM2ULONG(v_ih));
	return  rb_str_new2(v);
}

VALUE rb_IupSetAttributeHandle(VALUE node,VALUE v_name,VALUE v_node_named)
{
	const char* name = RSTRING_PTR(v_name);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	VALUE v_ih_named = rb_iv_get(v_node_named,"@ihandle");
	IupSetAttributeHandle((Ihandle*)NUM2ULONG(v_ih),name,(Ihandle*)NUM2ULONG(v_ih_named));
	return Qnil;
}

VALUE rb_IupGetAttributeHandle(VALUE node,VALUE v_name)
{
	const char* name = RSTRING_PTR(v_name);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	Ihandle* v;
	v = IupGetAttributeHandle((Ihandle*)NUM2ULONG(v_ih),name);
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupGetClassName(VALUE node)
{
	char* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGetClassName((Ihandle*)NUM2ULONG(v_ih));
	return  rb_str_new2(v);
}
/*
VALUE rb_IupCreate(VALUE self,VALUE v_name)
{
	const char *name = RSTRING_PTR(v_name);
	Ihandle* v;
	v = IupCreate(name);
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}

VALUE rb_IupCreatev(int argc,VALUE *argv,VALUE self)
{
	const char *name = RSTRING_PTR(argv[0]);
	Ihandle* v;
	int i;
	void **params = (void**)xmalloc(sizeof(void*)*(argc));
	for(i=0;i<argc-1;i++)
		params[i] = (void*)NUM2INT(argv[i+1]);
	params[i] = NULL;
	v = IupCreatev(name,params);
	free(params);
	if(v==NULL) return Qnil;
	return (VALUE)IupGetAttribute(v,"RB_CLASS");
}
*/
VALUE rb_IupFill(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	v = IupFill();
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupFill,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupRadio(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	VALUE child_node,v_hash;
	VALUE v_child;
	rb_scan_args(argc,argv,"11",&child_node,&v_hash);
	v_child = rb_iv_get(child_node,"@ihandle");
	v = IupRadio((Ihandle*)NUM2ULONG(v_child));
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupRadio,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupVboxv(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	int i;
	Ihandle *children[100];
	VALUE node;
	VALUE v_children,v_hash;
	rb_scan_args(argc,argv,"11",&v_children,&v_hash);
	for(i=0;i<RARRAY_LEN(v_children);i++) {
		node = RARRAY_PTR(v_children)[i];
		children[i] = (Ihandle*)NUM2ULONG(rb_iv_get(node,"@ihandle"));
	}
	children[i] = NULL;

	v = IupVboxv(children);
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupVbox,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupZboxv(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	int i;
	Ihandle *children[100];
	VALUE node;
	VALUE v_children,v_hash;
	rb_scan_args(argc,argv,"11",&v_children,&v_hash);
	for(i=0;i<RARRAY_LEN(v_children);i++) {
		node = RARRAY_PTR(v_children)[i];
		children[i] = (Ihandle*)NUM2ULONG(rb_iv_get(node,"@ihandle"));
	}
	children[i] = NULL;
	v = IupZboxv(children);
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupZbox,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupHboxv(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	int i;
	Ihandle *children[100];
	VALUE node;
	VALUE v_children,v_hash;
	rb_scan_args(argc,argv,"11",&v_children,&v_hash);
	for(i=0;i<RARRAY_LEN(v_children);i++) {
		node = RARRAY_PTR(v_children)[i];
		children[i] = (Ihandle*)NUM2ULONG(rb_iv_get(node,"@ihandle"));
	}
	children[i] = NULL;
	v = IupHboxv(children);
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupHbox,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupFrame(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	VALUE child_node,v_hash,v_child;
	rb_scan_args(argc,argv,"11",&child_node,&v_hash);
	v_child = rb_iv_get(child_node,"@ihandle");
	v = IupFrame((Ihandle*)NUM2ULONG(v_child));
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupFrame,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupImage(int argc,VALUE *argv,VALUE self)
{
	int width;
	int height;
	int i;
	Ihandle* v;
	VALUE v_width;
	VALUE v_height;
	VALUE v_pixmap;
	unsigned char *pixmap = NULL;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_width = rb_hash_delete(argv[0],ID2SYM(rb_intern("width")));
		v_height = rb_hash_delete(argv[0],ID2SYM(rb_intern("height")));
		v_pixmap = rb_hash_delete(argv[0],ID2SYM(rb_intern("pixmap")));
	} else {
		rb_scan_args(argc,argv,"30",&v_width,&v_height,&v_pixmap);
	}
	if(v_width==Qnil||v_height==Qnil||v_pixmap==Qnil) {
		rb_raise(rb_eIupError,"Invalid Argument");
	}
	width = NUM2INT(v_width);
	height = NUM2INT(v_height);
	pixmap = xmalloc(RARRAY_LEN(v_pixmap));
	for(i=0;i<RARRAY_LEN(v_pixmap);i++)
	  pixmap[i] = NUM2INT(RARRAY_PTR(v_pixmap)[i]);
	v = IupImage(width,height,pixmap);
	free(pixmap);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupImage,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupButton(int argc,VALUE *argv,VALUE self)
{
	const char* title = NULL;
	const char* action = NULL;
	Ihandle* v;
	VALUE v_title,v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_title = rb_hash_delete(argv[0],ID2SYM(rb_intern("title")));
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"11",&v_title,&v_action);
	}
	if(v_title!=Qnil)
		title = RSTRING_PTR(v_title);
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupButton(title,action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupButton,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupCanvas(int argc,VALUE *argv,VALUE self)
{
	const char* action = NULL;
	Ihandle* v;
	VALUE v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"01",&v_action);
	}
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupCanvas(action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupCanvas,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupDialog(int argc,VALUE *argv,VALUE self)
{
	Ihandle* v;
	VALUE child_node,v_hash;
	VALUE v_child;
	rb_scan_args(argc,argv,"11",&child_node,&v_hash);	
	v_child = rb_iv_get(child_node,"@ihandle");
	v = IupDialog((Ihandle*)NUM2ULONG(v_child));
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupDialog,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupUser(VALUE self)
{
	Ihandle* v;
	v = IupUser();
	if(v)
		return rb_funcall(rb_cIupUser,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupItem(int argc,VALUE *argv,VALUE self)
{
	const char* title = NULL;
	const char* action = NULL;
	Ihandle* v;
	VALUE v_title,v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_title = rb_hash_delete(argv[0],ID2SYM(rb_intern("title")));
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"11",&v_title,&v_action);
	}
	if(v_title!=Qnil)
		title = RSTRING_PTR(v_title);
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupItem(title,action);
	if(action)
		IupStoreAttribute(v,"RB_ACTION",action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupItem,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupSubmenu(int argc,VALUE *argv,VALUE self)
{
	const char* title = NULL; 
	Ihandle* v;
	VALUE v_title,child_node;
	VALUE v_child;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_title = rb_hash_delete(argv[0],ID2SYM(rb_intern("title")));
		child_node = rb_hash_delete(argv[0],ID2SYM(rb_intern("menu")));
	} else {
		rb_scan_args(argc,argv,"20",&v_title,&child_node);
	}
	if(v_title!=Qnil)
		title = RSTRING_PTR(v_title);
	v_child = rb_iv_get(child_node,"@ihandle");
	v = IupSubmenu(title,(Ihandle*)NUM2ULONG(v_child));
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupSubmenu,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupSeparator(VALUE self)
{
	Ihandle* v;
	v = IupSeparator();
	if(v)
		return rb_funcall(rb_cIupSeparator,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupLabel(int argc,VALUE *argv,VALUE self)
{
	const char* title = NULL;
	Ihandle* v;
	VALUE v_title;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_title = rb_hash_delete(argv[0],ID2SYM(rb_intern("title")));
	} else {
		rb_scan_args(argc,argv,"10",&v_title);
	}
	title = RSTRING_PTR(v_title);
	v = IupLabel(title);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupLabel,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupList(int argc,VALUE *argv,VALUE self)
{
	const char* action = NULL;
	Ihandle* v;
	VALUE v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"01",&v_action);
	}
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupList(action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupList,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupMenuv(VALUE self,VALUE v_children)
{
	Ihandle* v;
	int i;
	Ihandle *children[100];
	VALUE node;
	for(i=0;i<RARRAY_LEN(v_children);i++) {
		node = RARRAY_PTR(v_children)[i];
		children[i] = (Ihandle*)NUM2ULONG(rb_iv_get(node,"@ihandle"));
	}
	children[i] = NULL;
	v = IupMenuv(children);
	if(v)
		return rb_funcall(rb_cIupMenu,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupText(int argc,VALUE *argv,VALUE self)
{
	const char* action = NULL;
	Ihandle* v;
	VALUE v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"01",&v_action);
	}
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupText(action);
	if(action)
		IupStoreAttribute(v,"RB_ACTION",action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupText,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupMultiLine(int argc,VALUE *argv,VALUE self)
{
	const char* action = NULL;
	Ihandle* v;
	VALUE v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"01",&v_action);
	}
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupMultiLine(action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupMultiLine,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupToggle(int argc,VALUE *argv,VALUE self)
{
	const char* title = NULL;
	const char* action = NULL;
	Ihandle* v;
	VALUE v_title,v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_title = rb_hash_delete(argv[0],ID2SYM(rb_intern("title")));
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"02",&v_title,&v_action);
	}
	if(v_title!=Qnil)
		title = RSTRING_PTR(v_title);
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	v = IupToggle(title,action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupToggle,rb_intern("new"),2,ULONG2NUM((unsigned long)v),v_action);
	return Qnil;
}

VALUE rb_IupTimer(VALUE self)
{
	Ihandle* v;
	v = IupTimer();
	if(v)
		return rb_funcall(rb_cIupTimer,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupProgressBar(VALUE self)
{
	Ihandle* v;
	v = IupProgressBar();
	if(v)
		return rb_funcall(rb_cIupProgressBar,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupCboxv(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupCbox;
	Ihandle* v;
	int i;
	Ihandle *params[100];
	VALUE v_params,v_hash;
	VALUE node;
	rb_scan_args(argc,argv,"11",&v_params,&v_hash);
	for(i=0;i<RARRAY_LEN(v_params);i++) {
		node = RARRAY_PTR(v_params)[i];
		params[i] = (Ihandle*)NUM2ULONG(rb_iv_get(node,"@ihandle"));
	}
	params[i] = NULL;
	v = IupCboxv(params);
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupCbox,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

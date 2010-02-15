#include <ruby.h>
#include <ctype.h>
#include "iup.h"
#include "iupcontrols.h"
#include "cd.h"
#include "cdiup.h"
#include "cdpdf.h"
#include "iup_pplot.h"
#include "iupcb.h"
#include "iupcells.h"
#include "iupcolorbar.h"
#include "iupcontrols.h"
#include "iupgl.h"
#include "iupim.h"
#include "iupole.h"

// Ruby 1.9.x
#ifndef RSTRING_PTR
#define RSTRING_PTR(s) (RSTRING(s)->ptr)
#endif
#ifndef RSTRING_LEN
#define RSTRING_LEN(s) (RSTRING(s)->len)
#endif
#ifndef RARRAY_PTR
#define RARRAY_PTR(a) (RARRAY(a)->ptr)
#endif
#ifndef RARRAY_LEN
#define RARRAY_LEN(a) (RARRAY(a)->len)
#endif 
#ifndef RFLOAT_VALUE
#define RFLOAT_VALUE(v) (RFLOAT(v)->value) 
#endif

#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif 

VALUE rb_IupVal(int argc,VALUE *argv,VALUE self);

VALUE rb_IupTree(int argc,VALUE *argv,VALUE self);
VALUE rb_IupTreeGetAttribute(VALUE node,VALUE v_a,VALUE v_id);
VALUE rb_IupTreeGetFloat(VALUE node,VALUE v_a,VALUE v_id);
VALUE rb_IupTreeGetId(VALUE node,VALUE v_userid);
VALUE rb_IupTreeGetInt(VALUE node,VALUE v_a,VALUE v_id);
VALUE rb_IupTreeGetUserId(VALUE node,VALUE v_id);
VALUE rb_IupTreeSetAttribute(VALUE node,VALUE v_a,VALUE v_id,VALUE v_v);
VALUE rb_IupTreeSetUserId(VALUE node,VALUE v_id,VALUE v_userid);
VALUE rb_IupTreeStoreAttribute(VALUE node,VALUE v_a,VALUE v_id,VALUE v_v);

VALUE rb_IupTabsv(int argc,VALUE *argv,VALUE self);

VALUE rb_IupSpin(VALUE self);
VALUE rb_IupSpinbox(int argc,VALUE *argv,VALUE self);

VALUE rb_IupSbox(int argc,VALUE *argv,VALUE self);

VALUE rb_IupOleControl(VALUE self,VALUE v_ProgID);
//VALUE rb_IupOleControl_getclass(VALUE self);
VALUE rb_IupOleControlOpen(VALUE self);

VALUE rb_IupMatGetAttribute(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c);
VALUE rb_IupMatGetFloat(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c);
VALUE rb_IupMatGetInt(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c);
VALUE rb_IupMatrix(int argc,VALUE *argv,VALUE self);
VALUE rb_IupMatSetAttribute(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c,VALUE v_v);
VALUE rb_IupMatStoreAttribute(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c,VALUE v_v);

VALUE rb_IupLoadImage(VALUE self,VALUE v_file_name);
VALUE rb_IupSaveImage(VALUE self,VALUE node,VALUE v_file_name,VALUE v_format);

VALUE rb_IupGLCanvas(int argc,VALUE *argv,VALUE self);
VALUE rb_IupGLCanvasOpen(VALUE self);
VALUE rb_IupGLIsCurrent(VALUE self,VALUE node);
VALUE rb_IupGLMakeCurrent(VALUE self,VALUE node);
VALUE rb_IupGLPalette(VALUE self,VALUE node,VALUE v_index,VALUE v_r,VALUE v_g,VALUE v_b);
VALUE rb_IupGLSwapBuffers(VALUE self,VALUE node);

VALUE rb_IupGetParam(int argc,VALUE *argv,VALUE self);

VALUE rb_IupGetColor(VALUE self,VALUE v_x,VALUE v_y);

VALUE rb_IupDial(int argc,VALUE *argv,VALUE self);

VALUE rb_IupGauge(int argc,VALUE *argv,VALUE self);

VALUE rb_IupControlsClose(VALUE self);
VALUE rb_IupControlsOpen(VALUE self);
VALUE rb_IupImageLibOpen(VALUE self);

VALUE rb_IupColorbar(VALUE self);

VALUE rb_IupCells(int argc,VALUE *argv, VALUE self);

VALUE rb_IupColorBrowser(VALUE self);

VALUE rb_IupPPlot(VALUE self);
VALUE rb_IupPPlotAdd(VALUE node,VALUE v_x,VALUE v_y);
VALUE rb_IupPPlotAddStr(VALUE node,VALUE v_x,VALUE v_y);
VALUE rb_IupPPlotBegin(VALUE node,VALUE v_strXdata);
VALUE rb_IupPPlotEnd(VALUE node);
VALUE rb_IupPPlotInsert(VALUE node,VALUE v_index,VALUE v_sample_index,VALUE v_x,VALUE v_y);
VALUE rb_IupPPlotInsertStr(VALUE node,VALUE v_index,VALUE v_sample_index,VALUE v_x,VALUE v_y);
VALUE rb_IupPPlotOpen(VALUE self);
VALUE rb_IupPPlotPaintTo(VALUE node,VALUE v_cnv);
VALUE rb_IupPPlotTransform(VALUE node,VALUE v_x,VALUE v_y);

VALUE rb_cCdCanvas_initialize(VALUE self,VALUE v_canvas);
VALUE rb_cdActivate(VALUE self);
VALUE rb_cdActiveCanvas(VALUE self);
VALUE rb_cdAlpha(VALUE self,VALUE v_color);
VALUE rb_cdBitmapGetData(VALUE self,VALUE v_bitmap,VALUE v_dataptr);
VALUE rb_cdBitmapRGB2Map(VALUE self,VALUE v_bitmap_rgb,VALUE v_bitmap_map);
VALUE rb_cdBitmapSetRect(VALUE self,VALUE v_bitmap,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdBlue(VALUE self,VALUE v_color);
VALUE rb_cdCanvasActivate(VALUE self);
VALUE rb_cdCanvasArc(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2);
VALUE rb_cdCanvasBackground(VALUE self,VALUE v_color);
VALUE rb_cdCanvasBackOpacity(VALUE self,VALUE v_opacity);
VALUE rb_cdCanvasBegin(VALUE self,VALUE v_mode);
VALUE rb_cdCanvasBox(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasChord(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2);
VALUE rb_cdCanvasClear(VALUE self);
VALUE rb_cdCanvasClip(VALUE self,VALUE v_mode);
VALUE rb_cdCanvasClipArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasCreateImage(VALUE self,VALUE v_w,VALUE v_h);
VALUE rb_cdCanvasDeactivate(VALUE self);
VALUE rb_cdCanvasEnd(VALUE self);
VALUE rb_cdCanvasFillMode(VALUE self,VALUE v_mode);
VALUE rb_cdCanvasFlush(VALUE self);
VALUE rb_cdCanvasFont(VALUE self,VALUE v_type_face,VALUE v_style,VALUE v_size);
VALUE rb_cdCanvasForeground(VALUE self,VALUE v_color);
VALUE rb_cdCanvasGetAttribute(VALUE self,VALUE v_name);
VALUE rb_cdCanvasGetBitmap(VALUE self,VALUE v_bitmap,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasGetClipArea(VALUE self);
VALUE rb_cdCanvasGetColorPlanes(VALUE self);
VALUE rb_cdCanvasGetContext(VALUE self);
VALUE rb_cdCanvasGetFont(VALUE self);
VALUE rb_cdCanvasGetFontDim(VALUE self);
VALUE rb_cdCanvasGetImage(VALUE self,VALUE v_image,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasGetImageRGB(VALUE self,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h);
VALUE rb_cdCanvasGetOrigin(VALUE self);
VALUE rb_cdCanvasGetPattern(VALUE self);
VALUE rb_cdCanvasGetRegionBox(VALUE self);
VALUE rb_cdCanvasGetSize(VALUE self,VALUE v_width,VALUE v_height,VALUE v_width_mm,VALUE v_height_mm);
VALUE rb_cdCanvasGetStipple(VALUE self);
VALUE rb_cdCanvasGetTextBounds(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s);
VALUE rb_cdCanvasGetTextBox(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s);
VALUE rb_cdCanvasGetTextSize(VALUE self,VALUE v_s);
VALUE rb_cdCanvasGetTransform(VALUE self);
VALUE rb_cdCanvasGetVectorTextBounds(VALUE self,VALUE v_s,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasGetVectorTextSize(VALUE self,VALUE v_s);
VALUE rb_cdCanvasHatch(VALUE self,VALUE v_style);
VALUE rb_cdCanvasInteriorStyle(VALUE self,VALUE v_style);
VALUE rb_cdCanvasInvertYAxis(VALUE self,VALUE v_y);
VALUE rb_cdCanvasIsPointInRegion(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasLine(VALUE self,VALUE v_x1,VALUE v_y1,VALUE v_x2,VALUE v_y2);
VALUE rb_cdCanvasLineCap(VALUE self,VALUE v_cap);
VALUE rb_cdCanvasLineJoin(VALUE self,VALUE v_join);
VALUE rb_cdCanvasLineStyle(VALUE self,VALUE v_style);
VALUE rb_cdCanvasLineStyleDashes(VALUE self,VALUE v_dashes);
VALUE rb_cdCanvasLineWidth(VALUE self,VALUE v_width);
VALUE rb_cdCanvasMark(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasMarkSize(VALUE self,VALUE v_size);
VALUE rb_cdCanvasMarkType(VALUE self,VALUE v_type);
VALUE rb_cdCanvasMM2Pixel(VALUE self,VALUE v_mm_dx,VALUE v_mm_dy);
VALUE rb_cdCanvasMultiLineVectorText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s);
VALUE rb_cdCanvasNativeFont(VALUE self,VALUE v_font);
VALUE rb_cdCanvasOffsetRegion(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasOrigin(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasPalette(VALUE self,VALUE v_palette,VALUE v_mode);
VALUE rb_cdCanvasPattern(VALUE self,VALUE v_w,VALUE v_h,VALUE v_pattern);
VALUE rb_cdCanvasPixel(VALUE self,VALUE v_x,VALUE v_y,VALUE v_color);
VALUE rb_cdCanvasPixel2MM(VALUE self,VALUE v_dx,VALUE v_dy);
VALUE rb_cdCanvasPlay(VALUE self,VALUE v_context,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax,VALUE v_data);
VALUE rb_cdCanvasPutBitmap(VALUE self,VALUE v_bitmap,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h);
VALUE rb_cdCanvasPutImageRect(VALUE self,VALUE v_image,VALUE v_x,VALUE v_y,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasPutImageRectMap(VALUE self,VALUE v_iw,VALUE v_ih,VALUE v_index,VALUE v_colors,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasPutImageRectRGB(VALUE self,VALUE v_iw,VALUE v_ih,VALUE v_r,VALUE v_g,VALUE v_b,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasPutImageRectRGBA(VALUE self,VALUE v_iw,VALUE v_ih,VALUE v_r,VALUE v_g,VALUE v_b,VALUE v_a,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasRect(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdCanvasRegionCombineMode(VALUE self,VALUE v_mode);
VALUE rb_cdCanvasRestoreState(VALUE self,VALUE v_state);
VALUE rb_cdCanvasSaveState(VALUE self);
VALUE rb_cdCanvasScrollArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax,VALUE v_dx,VALUE v_dy);
VALUE rb_cdCanvasSector(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2);
VALUE rb_cdCanvasSetAttribute(VALUE self,VALUE v_name,VALUE v_data);
VALUE rb_cdCanvasSetBackground(VALUE self,VALUE v_color);
VALUE rb_cdCanvasSetForeground(VALUE self,VALUE v_color);
VALUE rb_cdCanvasSimulate(VALUE self,VALUE v_mode);
VALUE rb_cdCanvasStipple(VALUE self,VALUE v_w,VALUE v_h,VALUE v_stipple);
VALUE rb_cdCanvasText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s);
VALUE rb_cdCanvasTextAlignment(VALUE self,VALUE v_alignment);
VALUE rb_cdCanvasTextOrientation(VALUE self,VALUE v_angle);
VALUE rb_cdCanvasTransform(VALUE self,VALUE v_matrix);
VALUE rb_cdCanvasTransformMultiply(VALUE self,VALUE v_matrix);
VALUE rb_cdCanvasTransformPoint(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasTransformRotate(VALUE self,VALUE v_angle);
VALUE rb_cdCanvasTransformScale(VALUE self,VALUE v_sx,VALUE v_sy);
VALUE rb_cdCanvasTransformTranslate(VALUE self,VALUE v_dx,VALUE v_dy);
VALUE rb_cdCanvasUpdateYAxis(VALUE self,VALUE v_y);
VALUE rb_cdCanvasVectorCharSize(VALUE self,VALUE v_size);
VALUE rb_cdCanvasVectorFont(VALUE self,VALUE v_filename);
VALUE rb_cdCanvasVectorText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s);
VALUE rb_cdCanvasVectorTextDirection(VALUE self,VALUE v_x1,VALUE v_y1,VALUE v_x2,VALUE v_y2);
VALUE rb_cdCanvasVectorTextSize(VALUE self,VALUE v_size_x,VALUE v_size_y,VALUE v_s);
VALUE rb_cdCanvasVectorTextTransform(VALUE self,VALUE v_matrix);
VALUE rb_cdCanvasVertex(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdCanvasWriteMode(VALUE self,VALUE v_mode);
VALUE rb_cdContextCaps(VALUE self,VALUE v_context);
VALUE rb_cdContextIup();
VALUE rb_cdContextPDF();
VALUE rb_cdContextRegisterCallback(VALUE self,VALUE v_context,VALUE v_cb,VALUE v_func);
VALUE rb_cdCreateBitmap(VALUE self,VALUE v_w,VALUE v_h,VALUE v_type);
VALUE rb_cdCreateCanvas(VALUE self,VALUE v_context,VALUE v_data);
VALUE rb_cdDecodeAlpha(VALUE self,VALUE v_color);
VALUE rb_cdDecodeColor(VALUE self,VALUE v_color);
VALUE rb_cdEncodeAlpha(VALUE self,VALUE v_color,VALUE v_alpha);
VALUE rb_cdEncodeColor(VALUE self,VALUE v_red,VALUE v_green,VALUE v_blue);
VALUE rb_cdfCanvasArc(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2);
VALUE rb_cdfCanvasBox(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdfCanvasChord(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2);
VALUE rb_cdfCanvasClipArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdfCanvasGetClipArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdfCanvasGetOrigin(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdfCanvasInvertYAxis(VALUE self,VALUE v_y);
VALUE rb_cdfCanvasLine(VALUE self,VALUE v_x1,VALUE v_y1,VALUE v_x2,VALUE v_y2);
VALUE rb_cdfCanvasMM2Pixel(VALUE self,VALUE v_mm_dx,VALUE v_mm_dy,VALUE v_dx,VALUE v_dy);
VALUE rb_cdfCanvasOrigin(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdfCanvasPixel2MM(VALUE self,VALUE v_dx,VALUE v_dy);
VALUE rb_cdfCanvasRect(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax);
VALUE rb_cdfCanvasSector(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2);
VALUE rb_cdfCanvasText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s);
VALUE rb_cdfCanvasTransformPoint(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdfCanvasUpdateYAxis(VALUE self,VALUE v_y);
VALUE rb_cdfCanvasVertex(VALUE self,VALUE v_x,VALUE v_y);
VALUE rb_cdGreen(VALUE self,VALUE v_color);
VALUE rb_cdInitBitmap(int argc,VALUE *argv,VALUE self);
VALUE rb_cdKillBitmap(VALUE self,VALUE v_bitmap);
VALUE rb_cdKillCanvas(VALUE self);
VALUE rb_cdKillImage(VALUE self,VALUE v_image);
VALUE rb_cdRed(VALUE self,VALUE v_color);
VALUE rb_cdReleaseState(VALUE self,VALUE v_state);
VALUE rb_cdReserved(VALUE self,VALUE v_color);
VALUE rb_cdRGB2Map(VALUE self,VALUE v_width,VALUE v_height,VALUE v_red,VALUE v_green,VALUE v_blue,VALUE v_index,VALUE v_pal_size,VALUE v_color);
VALUE rb_cdUseContextPlus(VALUE self,VALUE v_use);
VALUE rb_cdVersion(VALUE self);
VALUE rb_cdVersionDate(VALUE self);

VALUE rb_IupListDialog (VALUE self,VALUE v_type, VALUE v_title, VALUE v_size, VALUE v_lst,VALUE v_op, VALUE v_col, VALUE v_line, VALUE v_marks);
VALUE rb_isalt(VALUE self,VALUE s);
VALUE rb_isbutton1(VALUE self,VALUE s);
VALUE rb_isbutton2(VALUE self,VALUE s);
VALUE rb_isbutton3(VALUE self,VALUE s);
VALUE rb_isbutton4(VALUE self,VALUE s);
VALUE rb_isbutton5(VALUE self,VALUE s);
VALUE rb_iscontrol(VALUE self,VALUE s);
VALUE rb_isdouble(VALUE self,VALUE s);
VALUE rb_isshift(VALUE self,VALUE s);
VALUE rb_issys(VALUE self,VALUE s);
VALUE rb_isxkey(VALUE self,VALUE s);
VALUE rb_IupAlarm(VALUE self,VALUE v_title,VALUE v_msg,VALUE v_b1,VALUE v_b2,VALUE v_b3);
VALUE rb_IupAppend(VALUE self,VALUE node,VALUE vchild);
VALUE rb_IupButton(int argc,VALUE *argv,VALUE self);
VALUE rb_IupCanvas(int argc,VALUE *argv,VALUE self);
VALUE rb_IupCboxv(int argc,VALUE *argv,VALUE self);
VALUE rb_IupClose(VALUE self);
VALUE rb_IupCreate(VALUE self,VALUE v_name);
VALUE rb_IupCreatev(int argc,VALUE *argv,VALUE self);
VALUE rb_IupDestroy(VALUE node);
VALUE rb_IupDetach(VALUE self,VALUE vchild);
VALUE rb_IupDialog(int argc,VALUE *argv,VALUE self);
VALUE rb_IupExitLoop(VALUE self);
VALUE rb_IupFileDlg(int argc,VALUE *argv,VALUE self);
VALUE rb_IupFill(int argc,VALUE *argv,VALUE self);
VALUE rb_IupFlush(VALUE self);
VALUE rb_IupFrame(int argc,VALUE *argv,VALUE self);
VALUE rb_IupGetActionName(VALUE self);
VALUE rb_IupGetAllDialogs(VALUE self,VALUE v_n);
VALUE rb_IupGetAllNames(VALUE self,VALUE v_n);
VALUE rb_IupGetAttribute(VALUE node,VALUE v_name);
VALUE rb_IupGetAttributeHandle(VALUE node,VALUE v_name);
VALUE rb_IupGetAttributePtr(VALUE node,VALUE v_name);
VALUE rb_IupGetAttributes(VALUE node);
VALUE rb_IupGetBrother(VALUE self,VALUE node);
VALUE rb_IupGetCallback(VALUE node,VALUE v_name);
VALUE rb_IupGetClassName(VALUE node);
VALUE rb_IupGetDialog(VALUE self,VALUE node);
VALUE rb_IupGetFile(VALUE self,VALUE v_arq);
VALUE rb_IupGetFloat(VALUE node,VALUE v_name);
VALUE rb_IupGetFocus(VALUE self);
VALUE rb_IupGetFunction(VALUE self,VALUE v_name);
VALUE rb_IupGetGlobal(VALUE self,VALUE v_name);
VALUE rb_IupGetHandle(VALUE self,VALUE v_name);
VALUE rb_IupGetIdle(VALUE self);
VALUE rb_IupGetInt(VALUE node,VALUE v_name);
VALUE rb_IupGetLanguage(VALUE self);
VALUE rb_IupGetName(VALUE self,VALUE node);
VALUE rb_IupGetNextChild(VALUE self,VALUE node,VALUE vchild);
VALUE rb_IupGetParent(VALUE self,VALUE node);
VALUE rb_IupGetText(VALUE self,VALUE v_title,VALUE v_text);
VALUE rb_IupHboxv(int argc,VALUE *argv,VALUE self);
VALUE rb_IupHelp(VALUE self,VALUE v_url);
VALUE rb_IupHide(VALUE node);
VALUE rb_IupImage(int argc,VALUE *argv,VALUE self);
VALUE rb_IupItem(int argc,VALUE *argv,VALUE self);
VALUE rb_IupLabel(int argc,VALUE *argv,VALUE self);
VALUE rb_IupList(int argc,VALUE *argv,VALUE self);
VALUE rb_IupLoopStep(VALUE self);
VALUE rb_IupMainLoop(VALUE self);
VALUE rb_IupMap(VALUE node);
VALUE rb_IupMapFont(VALUE self,VALUE v_iupfont);
VALUE rb_IupMenuv(VALUE self,VALUE v_children);
VALUE rb_IupMessage(VALUE self,VALUE v_title,VALUE v_msg);
VALUE rb_IupMessagef(int argc,VALUE *argv,VALUE self);
VALUE rb_IupMultiLine(int argc,VALUE *argv,VALUE self);
VALUE rb_IupNextField(VALUE self,VALUE node);
VALUE rb_IupNode_initialize(int argc,VALUE *argv,VALUE self);
VALUE rb_IupOpen(VALUE self);
VALUE rb_IupPopup(VALUE node,VALUE v_x,VALUE v_y);
VALUE rb_IupPreviousField(VALUE self,VALUE node);
VALUE rb_IupProgressBar(VALUE self);
VALUE rb_IupRadio(int argc,VALUE *argv,VALUE self);
VALUE rb_IupRefresh(VALUE self,VALUE node);
VALUE rb_IupScanf(int argc,VALUE *argv,VALUE self);
VALUE rb_IupSeparator(VALUE self);
VALUE rb_IupSetAttribute(VALUE node,VALUE v_name,VALUE v_value);
VALUE rb_IupSetAttributeHandle(VALUE node,VALUE v_name,VALUE v_node_named);
VALUE rb_IupSetAttributePtr(VALUE node,VALUE v_name,VALUE v_value);
VALUE rb_IupSetAttributes(VALUE node,VALUE v_str);
VALUE rb_IupSetCallback(VALUE node,VALUE v_name,VALUE v_func);
VALUE rb_IupSetFocus(VALUE self,VALUE node);
VALUE rb_IupSetFunction(VALUE self,VALUE v_name,VALUE v_func);
VALUE rb_IupSetGlobal(VALUE self,VALUE v_name,VALUE v_value);
VALUE rb_IupSetHandle(VALUE self,VALUE v_name,VALUE node);
VALUE rb_IupSetIdle(VALUE self,VALUE v_func);
VALUE rb_IupSetLanguage(VALUE self,VALUE v_lng);
VALUE rb_IupShow(VALUE node);
VALUE rb_IupShowXY(VALUE node,VALUE v_x,VALUE v_y);
VALUE rb_IupStoreAttribute(VALUE node,VALUE v_name,VALUE v_value);
VALUE rb_IupStoreGlobal(VALUE self,VALUE v_name,VALUE v_value);
VALUE rb_IupSubmenu(int argc,VALUE *argv,VALUE self);
VALUE rb_IupText(int argc,VALUE *argv,VALUE self);
VALUE rb_IupTimer(VALUE self);
VALUE rb_IupToggle(int argc,VALUE *argv,VALUE self);
VALUE rb_IupUnMapFont(VALUE self,VALUE v_driverfont);
VALUE rb_IupUpdate(VALUE self,VALUE node);
VALUE rb_IupUser(VALUE self);
VALUE rb_IupVboxv(int argc,VALUE *argv,VALUE self);
VALUE rb_IupVersion(VALUE self);
VALUE rb_IupVersionDate(VALUE self);
VALUE rb_IupVersionNumber(VALUE self);
VALUE rb_IupZboxv(int argc,VALUE *argv,VALUE self);
VALUE rb_method_missing(int argc,VALUE *argv, VALUE self);
void exit_handler(void);
char* rb_str_upper(char* s);
void rb_set_attribute(Ihandle *v,VALUE arg);

extern VALUE rb_mIup;
extern VALUE rb_mCd;
extern VALUE rb_eIupError;
extern VALUE rb_cIupImage;
extern VALUE rb_cIupButton;
extern VALUE rb_cIupCanvas;
extern VALUE rb_cIupDialog;
extern VALUE rb_cIupFill;
extern VALUE rb_cIupFrame;
extern VALUE rb_cIupHbox;
extern VALUE rb_cIupItem;
extern VALUE rb_cIupSeparator;
extern VALUE rb_cIupSubmenu;
extern VALUE rb_cIupLabel;
extern VALUE rb_cIupList;
extern VALUE rb_cIupMenu;
extern VALUE rb_cIupRadio;
extern VALUE rb_cIupText;
extern VALUE rb_cIupToggle;
extern VALUE rb_cIupToggle;
extern VALUE rb_cIupVbox;
extern VALUE rb_cIupZbox;
extern VALUE rb_cIupMultiLine;
extern VALUE rb_cIupUser;
extern VALUE rb_cIupControl;
extern VALUE rb_cIupTimer;
extern VALUE rb_cIupProgressBar;
extern VALUE rb_cIupFileDlg;
extern VALUE rb_cIupTree;
extern VALUE rb_cIupNode;
extern VALUE rb_cIupTabs;
extern VALUE rb_cIupGLCanvas;
extern VALUE rb_cIupSpin;
extern VALUE rb_cIupSpinbox;
extern VALUE rb_cIupSbox;
extern VALUE rb_cIupCbox;
extern VALUE rb_cIupMatrix;
extern VALUE rb_cIupGauge;
extern VALUE rb_cIupDial;
extern VALUE rb_cIupColorbar;
extern VALUE rb_cIupColorBrowser;
extern VALUE rb_cIupCells;
extern VALUE rb_cIupPPlot;
extern VALUE rb_cIupVal;
extern VALUE rb_cCdCanvas;

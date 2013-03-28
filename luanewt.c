#include <stdlib.h>

#include "luanewt.h"

/** private helper functions **/

/* check and return pointer */ 
void *luaL_checkpointer(lua_State* L, int i) {
	luaL_checktype(L, i, LUA_TLIGHTUSERDATA);
	return lua_touserdata(L, i);
}

/* check and return component object parameter */ 
component luaL_checkcomponent(lua_State* L, int i) {
	luaL_checkudata(L, i, TYPE_COMPONENT);
   	return lua_toncom(L, i);
}

/* push a component object on the stack */
void lua_pushcomponent(lua_State *L, newtComponent com, int type) {
	if (com) {
		component p = lua_newncom(L);
		luaL_getmetatable(L, TYPE_COMPONENT);
		lua_setmetatable(L, -2);
		p->p = com;
		p->t = type;
	} else {
		lua_pushnil(L);
	}
}

/** module registration **/

/* base functions */
static const luaL_Reg R_newt_functions[] = {
	
	{"Init", L_Init},
	{"Cls", L_Cls},
	{"Compare", L_Compare},
	{"WaitForKey", L_WaitForKey},
	{"ClearKeyBuffer", L_ClearKeyBuffer},
	{"DrawRootText", L_DrawRootText},
	{"OpenWindow", L_OpenWindow},
	{"CenteredWindow", L_CenteredWindow},
	{"PopWindow", L_PopWindow},
	{"PushHelpLine", L_PushHelpLine},
	{"PopHelpLine", L_PopHelpLine},
	{"Refresh", L_Refresh},
	{"Finished", L_Finished},
	{"WinMessage", L_WinMessage},
	{"Suspend", L_Suspend},
	{"Resume", L_Resume},
	{"SetSuspendCallback", L_SetSuspendCallback},
	{"Bell", L_Bell},
	{"GetScreenSize", L_GetScreenSize},
	{"ReflowText", L_ReflowText},
	
	{"Button", L_Button},
	{"CompactButton", L_CompactButton},
	{"Checkbox", L_Checkbox}, 
	{"Entry", L_Entry},
	{"Form", L_Form},
	{"Label", L_Label}, 
	{"Textbox", L_Textbox}, 
	{"TextboxReflowed", L_TextboxReflowed}, 
	{"Listbox", L_Listbox},
	{"Radiobutton", L_Radiobutton},
	{"Scale", L_Scale},
	{"VerticalScrollbar", L_VerticalScrollbar},

	{NULL, NULL}
};

/* Newt.Component methods */
static const luaL_Reg R_comp_methods[] = {

	{"AddComponents", L_AddComponents},
	{"Clear", L_Clear},
	{"Destroy", L_Destroy},
	{"GetValue", L_GetValue},
	{"Run", L_Run},
	{"Set", L_Set},
	{"SetText", L_SetText},
	{"TakesFocus", L_TakesFocus},
	
	{NULL, NULL}
};

/* open the library - used by require() */
LUALIB_API int luaopen_newt(lua_State *L) {
	
	/* register the base functions and module tags */
	luaL_register(L, "newt", R_newt_functions);
	
	lua_pushliteral(L, MYVERSION);
	lua_setfield(L, -2, "version");			/** version */

	lua_pushinteger(L, NEWT_FLAG_RETURNEXIT);
	lua_setfield(L, -2, "FLAG_RETURNEXIT");
	lua_pushinteger(L, NEWT_FLAG_HIDDEN);
	lua_setfield(L, -2, "FLAG_HIDDEN");
	lua_pushinteger(L, NEWT_FLAG_SCROLL);
	lua_setfield(L, -2, "FLAG_SCROLL");
	lua_pushinteger(L, NEWT_FLAG_DISABLED);
	lua_setfield(L, -2, "FLAG_DISABLED");
	lua_pushinteger(L, NEWT_FLAG_BORDER);
	lua_setfield(L, -2, "FLAG_BORDER");
	lua_pushinteger(L, NEWT_FLAG_WRAP);
	lua_setfield(L, -2, "FLAG_WRAP");
	lua_pushinteger(L, NEWT_FLAG_NOF12);
	lua_setfield(L, -2, "FLAG_NOF12");
	lua_pushinteger(L, NEWT_FLAG_MULTIPLE);
	lua_setfield(L, -2, "FLAG_MULTIPLE");
	lua_pushinteger(L, NEWT_FLAG_SELECTED);
	lua_setfield(L, -2, "FLAG_SELECTED");
	lua_pushinteger(L, NEWT_FLAG_CHECKBOX);
	lua_setfield(L, -2, "FLAG_CHECKBOX");
	lua_pushinteger(L, NEWT_FLAG_PASSWORD);
	lua_setfield(L, -2, "FLAG_PASSWORD");
	lua_pushinteger(L, NEWT_FLAG_SHOWCURSOR);
	lua_setfield(L, -2, "FLAG_SHOWCURSOR");

	lua_pushinteger(L, NEWT_CHECKBOXTREE_UNSELECTABLE);
	lua_setfield(L, -2, "FLAG_CHECKBOXTREE_UNSELECTABLE");
	lua_pushinteger(L, NEWT_CHECKBOXTREE_HIDE_BOX);
	lua_setfield(L, -2, "FLAG_CHECKBOXTREE_HIDE_BOX");
	
	lua_pushinteger(L, NEWT_EXIT_HOTKEY);
	lua_setfield(L, -2, "EXIT_HOTKEY");
	lua_pushinteger(L, NEWT_EXIT_COMPONENT);
	lua_setfield(L, -2, "EXIT_COMPONENT");
	lua_pushinteger(L, NEWT_EXIT_FDREADY);
	lua_setfield(L, -2, "EXIT_FDREADY");
	lua_pushinteger(L, NEWT_EXIT_TIMER);
	lua_setfield(L, -2, "EXIT_TIMER");
	
	luaL_newmetatable(L, TYPE_COMPONENT); 
	lua_pushvalue(L, -1); 
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, R_comp_methods); 
	lua_pop(L, 1);
	
	/* return the library handle */
	return 1;
}


/** root functions **/

/* bool Init() */
LUALIB_API int L_Init(lua_State *L) {
	int result;
	result = newtInit();
	lua_pushboolean(L, result);
	return 1;
}

/* Cls() */
LUALIB_API int L_Cls(lua_State *L) {
	newtCls();
	return 0;
}

/* Compare(component, component) */
LUALIB_API int L_Compare(lua_State *L) {
	component c1;
	component c2;
	bool result;
	result = false;
	c1 = luaL_checkcomponent(L, 1);
	c2 = luaL_checkcomponent(L, 2);
	if (c1->p == c2->p) result = true;
	lua_pushboolean(L, result);
	return 1;
}

/* WaitForKey() */
LUALIB_API int L_WaitForKey(lua_State *L) {
	newtWaitForKey();
	return 0;
}

/* ClearKeyBuffer() */
LUALIB_API int L_ClearKeyBuffer(lua_State *L) {
	newtClearKeyBuffer();
	return 0;
}

/* DrawRootText(left, top, text) */
LUALIB_API int L_DrawRootText(lua_State *L) {
	int left; int top;
	const char *text;
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);
	newtDrawRootText(left, top, text);
	return 0;
}

/* newtOpenWindow(left, top, width, height, [title]) */
LUALIB_API int L_OpenWindow(lua_State *L) {
	int result;
	int left; int top;
	int width; int height;
	const char *title;
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	width = luaL_checkinteger(L, 3);
	height = luaL_checkinteger(L, 4);
	if ((lua_gettop(L) < 5) || (lua_isnil(L, 5) == 1)) {
		title = NULL;
	} else {
		title = luaL_checkstring(L, 5);
	}
	result = newtOpenWindow(left, top, width, height, title);
	return 0;
}

/* bool newtCenteredWindow(width, height, [title]) */
LUALIB_API int L_CenteredWindow(lua_State *L) {
	int result;
	int width; int height;
	const char *title;
	width = luaL_checkinteger(L, 1);
	height = luaL_checkinteger(L, 2);

	if ((lua_gettop(L) < 3) || (lua_isnil(L, 3) == 1)) title = NULL;
	else title = luaL_checkstring(L, 3);

	result = newtCenteredWindow(width, height, title);
	return 0;
}

/* PopWindow() */
LUALIB_API int L_PopWindow(lua_State *L) {
	newtPopWindow();
	return 0;
}

/* PushHelpLine([text]) */
LUALIB_API int L_PushHelpLine(lua_State *L) {
	const char *text;

	if ((lua_gettop(L) < 1) || (lua_isnil(L, 1) == 1)) text = NULL;
	else text = luaL_checkstring(L, 1);

	newtPushHelpLine(text);	
	return 0;
}

/* PopHelpLine() */
LUALIB_API int L_PopHelpLine(lua_State *L) {
	newtPopHelpLine();
	return 0;
}

/* Refresh() */
LUALIB_API int L_Refresh(lua_State *L) {
	newtRefresh();
	return 0;
}

/* bool Finished() */
LUALIB_API int L_Finished(lua_State *L) {
	int result;
	result = newtFinished();
	lua_pushboolean(L, result);
	return 1;
}

LUALIB_API int L_WinMessage(lua_State *L) {
	return 0;
}

/* Suspend() */
LUALIB_API int L_Suspend(lua_State *L) {
	newtSuspend();
	return 0;
}

/* Resume */
LUALIB_API int L_Resume(lua_State *L) {
	newtResume();
	return 0;
}

LUALIB_API int L_SetSuspendCallback(lua_State *L) {
	return 0;
}

/* Bell() */
LUALIB_API int L_Bell(lua_State *L) {
	newtBell();
	return 0;
}

/* number, number GetScreenSize() */
LUALIB_API int L_GetScreenSize(lua_State *L) {
	int cols; int rows;
	newtGetScreenSize(&cols, &rows);
	lua_pushinteger(L, cols);
	lua_pushinteger(L, rows);
	return 2;
}

LUALIB_API int L_ReflowText(lua_State *L) {
	return 0;
}

/* widget functions */

/* com = Button(left, top, text) */
LUALIB_API int L_Button(lua_State *L) {
	newtComponent result;
	int left; int top; 
	const char *text;
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);
	result = newtButton(left, top, text);
	lua_pushcomponent(L, result, TYPE_BUTTON);
	return 1;
}

/* com = CompactButton(left, top, text) */
LUALIB_API int L_CompactButton(lua_State *L) {
	newtComponent result;
	int left; int top; 
	const char *text;
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);
	result = newtCompactButton(left, top, text);
	lua_pushcomponent(L, result, TYPE_BUTTON);
	return 1;
}

LUALIB_API int L_Checkbox(lua_State *L) {
	return 0;
}

/* com = Entry(left, top, value, width, [flags])*/
LUALIB_API int L_Entry(lua_State *L) {
	int left; int top;
	const char *value;
	int width; int flags;
	newtComponent result;
	
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	
	if (lua_isnil(L, 3) == 1) value = NULL;
	else value = luaL_checkstring(L, 3);
	
	width = luaL_checkinteger(L, 4);
	
	if (lua_gettop(L) < 5 || lua_isnil(L, 5) == 1) flags = 0;
	else flags = luaL_checkinteger(L, 5);
	
	result = newtEntry(left, top, value, width, NULL, flags);
	lua_pushcomponent(L, result, TYPE_ENTRY);
	return 1;
}

/* com = Form([vertBar], [help], [flags]) */
LUALIB_API int L_Form(lua_State *L) {
	newtComponent vertBar;
	const char *help;
	int flags;
	newtComponent result;
	
	if (lua_gettop(L) < 1 || lua_isnil(L, 1) == 1) vertBar = NULL;
	else vertBar = luaL_checkcomponent(L, 1)->p;

	if (lua_gettop(L) < 2 || lua_isnil(L, 2) == 1) help = NULL;
	else help = luaL_checkstring(L, 2);

	if (lua_gettop(L) < 3 || lua_isnil(L, 3) == 1) flags = 0;		
	else flags = luaL_checkinteger(L, 3);
	
	result = newtForm(vertBar, (void *)help, flags);
	lua_pushcomponent(L, result, TYPE_FORM);
	return 1;
}

/* com = Label(left, top, text) */
LUALIB_API int L_Label(lua_State *L) {
	int left; int top;
	const char *text;
	newtComponent result;

	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);
	
	result = newtLabel(left, top, text);
	lua_pushcomponent(L, result, TYPE_LABEL);
	return 1;
}

LUALIB_API int L_Textbox(lua_State *L) {
	return 0;
}

LUALIB_API int L_TextboxReflowed(lua_State *L) {
	return 0;
}

LUALIB_API int L_Listbox(lua_State *L) {
	return 0;
}

LUALIB_API int L_Radiobutton(lua_State *L) {
	return 0;
}

LUALIB_API int L_Scale(lua_State *L) {
	return 0;
}

LUALIB_API int L_VerticalScrollbar(lua_State *L) {
	return 0;
}


/** Newt.Component object **/

LUALIB_API int L_AddCallback(lua_State *L) {
	return 0;
}

/* AddComponents(com, ...) */
LUALIB_API int L_AddComponents(lua_State *L) {
	int i;
	component form;
	component com;
	form = luaL_checkcomponent(L, 1);
	com = luaL_checkcomponent(L, 2);
	if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
	newtFormAddComponent(form->p, com->p);
	for (i = 3; i <= lua_gettop(L); i++) {
		com = luaL_checkcomponent(L, i);
		newtFormAddComponent(form->p, com->p);
	}
	return 0;
}

LUALIB_API int L_AddHotKey(lua_State *L) {
	return 0;
}

LUALIB_API int L_AppendEntry(lua_State *L) {
	return 0;
}

/* listbox:Clear() */
LUALIB_API int L_Clear(lua_State *L) {
	component com;
	com = luaL_checkcomponent(L, 1);
	if (com->t == TYPE_LISTBOX) return luaL_error(L, "Invalid Method");
	newtListboxClear(com->p);
	return 0;
}

/* com:TakesFocus(bool) */
LUALIB_API int L_TakesFocus(lua_State *L) {
	component com;
	int val;
	com = luaL_checkcomponent(L, 1);
	
	if (lua_gettop(L) < 2) val = true;
	else val = lua_toboolean(L, 2);
	
	newtComponentTakesFocus(com->p, val);
	return 0;
}

/* entry:Set(value, [cursoratend]) */
LUALIB_API int L_Set(lua_State *L) {
	component com;
	const char *svalue;
	bool cursoratend;
	
	com = luaL_checkcomponent(L, 1);
	switch (com->t) {
		case TYPE_ENTRY:
			svalue = luaL_checkstring(L, 2);
			if (lua_gettop(L) < 3) cursoratend = false;
			else cursoratend = lua_toboolean(L, 3);
			newtEntrySet(com->p, svalue, cursoratend);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	return 0;	
}

/* value = entry:GetValue() */
LUALIB_API int L_GetValue(lua_State *L) {
	component com;

	com = luaL_checkcomponent(L, 1);
	switch (com->t) {
		case TYPE_ENTRY:
			lua_pushstring(L, newtEntryGetValue(com->p));
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	return 1;
}

LUALIB_API int L_SetValue(lua_State *L) {
	return 0;
}

LUALIB_API int L_GetCurrent(lua_State *L) {
	return 0;
}

/* reason, value = form:Run() */
LUALIB_API int L_Run(lua_State *L) {
	component form; 
	struct newtExitStruct result;
	form = luaL_checkcomponent(L, 1);
	if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
	newtFormRun(form->p, &result);
	lua_pushinteger(L, (int)result.reason);
	if (result.reason == NEWT_EXIT_COMPONENT) {
		lua_pushcomponent(L, result.u.co, TYPE_UNKNOWN);
	} else {
		lua_pushinteger(L, result.u.key);
	}
	return 2;
}

LUALIB_API int L_SetBackground(lua_State *L) {
	return 0;
}

LUALIB_API int L_SetHeight(lua_State *L) {
	return 0;
}

LUALIB_API int L_SetTimer(lua_State *L) {
	return 0;
}

LUALIB_API int L_Destroy(lua_State *L) {
	component form;
	form = luaL_checkcomponent(L, 1);
	if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method"); 
	newtFormDestroy(form->p);
	return 0;
}

/* label:SetText(text) */
LUALIB_API int L_SetText(lua_State *L) {
	component com;
	const char *text;
	com = luaL_checkcomponent(L, 1);
	text = luaL_checkstring(L, 2);
	switch (com->t) {
		case TYPE_LABEL:
			newtLabelSetText(com->p, text);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	return 0;
}

/* newt.Textbox object */
LUALIB_API int L_TextboxSetText(lua_State *L) {
	return 0;
}

LUALIB_API int L_TextboxGetNumLines(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxDeleteEntry(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxInsertEntry(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxSetEntry(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxSetWidth(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxSetCurrent(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxSetCurrentByKey(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxGetCurrent(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxGetSelection(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxClearSelection(lua_State *L) {
	return 0;
}

LUALIB_API int L_ListboxSelectItem(lua_State *L) {
	return 0;
}

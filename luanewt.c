#include <stdlib.h>

#include "luanewt.h"

/** private helper functions **/

/* Lua 5.2.0 compatibility */
#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501

static void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
	luaL_checkstack(L, nup, "too many upvalues");
	for (; l->name != NULL; l++) {  /* fill the table with given functions */
		int i;
		for (i = 0; i < nup; i++)  /* copy upvalues to the top */
			lua_pushvalue(L, -nup);
		lua_pushstring(L, l->name);
		lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
		lua_settable(L, -(nup + 3));
	}
	lua_pop(L, nup);  /* remove upvalues */
}

LUALIB_API void *luaL_testudata (lua_State *L, int ud, const char *tname) {
	void *p = lua_touserdata(L, ud);
	if (p != NULL) {  /* value is a userdata? */
		if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
			luaL_getmetatable(L, tname);  /* get correct metatable */
			if (!lua_rawequal(L, -1, -2))  /* not the same? */
			p = NULL;  /* value is a userdata with wrong metatable */
			lua_pop(L, 2);  /* remove both metatables */
			return p;
		}
	}
	return NULL;  /* value is not a userdata with a metatable */
}

#endif

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

/* register component tag */
void lua_regtag(lua_State *L, newtComponent com, const char *tag) {
	char id[20];
	sprintf(id, "newt.%p", (void *)(com));
	lua_pushstring(L, id);
	if (tag != NULL) lua_pushstring(L, tag);
	else lua_pushnil(L);
	lua_settable(L, LUA_REGISTRYINDEX);
}

/* push component tag onto Lua stack */
void lua_pushtag(lua_State *L, newtComponent com) {
	char id[20];
	sprintf(id, "newt.%p", (void *)(com));
	lua_pushstring(L, id);
	lua_gettable(L, LUA_REGISTRYINDEX);
}


/** module registration **/

/* base functions */
static const luaL_Reg R_newt_functions[] = {
	
	{"Init", L_Init},
	{"Cls", L_Cls},
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
	{"CursorOff", L_CursorOff},
	{"CursorOn", L_CursorOn},
	{"Delay", L_Delay},
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
	{"AddHotKey", L_AddHotKey},
	{"AppendEntry", L_AppendEntry},
	{"Clear", L_Clear},
	{"Destroy", L_Destroy},
	{"Draw", L_Draw},
	{"GetCurrent", L_GetCurrent},
	{"GetValue", L_GetValue},
	{"ID", L_ID},
	{"Run", L_Run},
	{"Set", L_Set},
	{"SetText", L_SetText},
	{"SetTimer", L_SetTimer},
	{"SetType", L_SetType},
	{"TakesFocus", L_TakesFocus},
	{"Text", L_Text},
	
	{NULL, NULL}
};

/* open the library - used by require() */
LUALIB_API int luaopen_newt(lua_State *L) {
	
	/* register the base functions and module flags */
	/*luaL_register(L, "newt", R_newt_functions);*/
	luaL_newlib(L, "newt", R_newt_functions);
	
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


	lua_pushinteger(L, NEWT_KEY_ESCAPE);
	lua_setfield(L, -2, "KEY_ESCAPE");
	lua_pushinteger(L, NEWT_KEY_RETURN);
	lua_setfield(L, -2, "KEY_RETURN");
	lua_pushinteger(L, NEWT_KEY_PGDN);
	lua_setfield(L, -2, "KEY_PGDN");
	lua_pushinteger(L, NEWT_KEY_PGUP);
	lua_setfield(L, -2, "KEY_PGUP");

	lua_pushinteger(L, NEWT_KEY_F1);
	lua_setfield(L, -2, "KEY_F1");
	lua_pushinteger(L, NEWT_KEY_F2);
	lua_setfield(L, -2, "KEY_F2");
	lua_pushinteger(L, NEWT_KEY_F3);
	lua_setfield(L, -2, "KEY_F3");
	lua_pushinteger(L, NEWT_KEY_F4);
	lua_setfield(L, -2, "KEY_F4");
	lua_pushinteger(L, NEWT_KEY_F5);
	lua_setfield(L, -2, "KEY_F5");
	lua_pushinteger(L, NEWT_KEY_F6);
	lua_setfield(L, -2, "KEY_F6");
	lua_pushinteger(L, NEWT_KEY_F7);
	lua_setfield(L, -2, "KEY_F7");
	lua_pushinteger(L, NEWT_KEY_F8);
	lua_setfield(L, -2, "KEY_F8");
	lua_pushinteger(L, NEWT_KEY_F9);
	lua_setfield(L, -2, "KEY_F9");
	lua_pushinteger(L, NEWT_KEY_F10);
	lua_setfield(L, -2, "KEY_F10");
	lua_pushinteger(L, NEWT_KEY_F11);
	lua_setfield(L, -2, "KEY_F11");
	lua_pushinteger(L, NEWT_KEY_F12);
	lua_setfield(L, -2, "KEY_F12");
	
	lua_pushinteger(L, TYPE_FORM);
	lua_setfield(L, -2, "TYPE_FORM");
	lua_pushinteger(L, TYPE_UNKNOWN);
	lua_setfield(L, -2, "TYPE_UNKNOWN");
	lua_pushinteger(L, TYPE_LABEL);
	lua_setfield(L, -2, "TYPE_LABEL");
	lua_pushinteger(L, TYPE_ENTRY);
	lua_setfield(L, -2, "TYPE_ENTRY");
	lua_pushinteger(L, TYPE_BUTTON);
	lua_setfield(L, -2, "TYPE_BUTTON");
	lua_pushinteger(L, TYPE_CHECKBOX);
	lua_setfield(L, -2, "TYPE_CHECKBOX");
	lua_pushinteger(L, TYPE_RADIOBUTTON);
	lua_setfield(L, -2, "TYPE_RADIOBUTTON");
	lua_pushinteger(L, TYPE_LISTBOX);
	lua_setfield(L, -2, "TYPE_LISTBOX");
	lua_pushinteger(L, TYPE_SCALE);
	lua_setfield(L, -2, "TYPE_SCALE");

	/* Newt.Component type & methods */
	luaL_newmetatable(L, TYPE_COMPONENT); 
	lua_pushvalue(L, -1); 
	lua_setfield(L, -2, "__index");
	/*luaL_register(L, NULL, R_comp_methods);*/
	luaL_setfuncs(L, R_comp_methods, 0);
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
	lua_pushboolean(L, result);
	return 1;
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
	lua_pushboolean(L, result);
	return 1;
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

/* CursorOff() */
LUALIB_API int L_CursorOff(lua_State *L) {
	newtCursorOff();
	return 0;
}

/* CursorOn() */
LUALIB_API int L_CursorOn(lua_State *L) {
	newtCursorOn();
	return 0;
}

/* Delay() */
LUALIB_API int L_Delay(lua_State *L) {
	int msec;
	msec = luaL_checkinteger(L, 1);
	newtDelay(msec * 1000);
	return 0;
}

/* cols, rows = GetScreenSize() */
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
	lua_regtag(L, result, text);
	lua_pushcomponent(L, result, TYPE_BUTTON);
	return 1;
}

/* com = CompactButton(left, top, text) */
LUALIB_API int L_CompactButton(lua_State *L) {
	int left; int top; 
	const char *text;
	newtComponent result;

	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);

	result = newtCompactButton(left, top, text);
	lua_regtag(L, result, text);
	lua_pushcomponent(L, result, TYPE_BUTTON);
	return 1;
}

/* com = Checkbox(left, top, text, [checked]) */
LUALIB_API int L_Checkbox(lua_State *L) {
	int left; int top;
	const char *text;
	bool checked;
	newtComponent result;
	
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);
	if (lua_gettop(L) < 4 || lua_isnil(L, 4) == 1) checked = false;
	else checked = lua_toboolean(L, 4);
	
	if (checked == false) result = newtCheckbox(left, top, text, ' ', " *", NULL);
	else result = newtCheckbox(left, top, text, '*', " *", NULL);
	lua_regtag(L, result, text);
	lua_pushcomponent(L, result, TYPE_CHECKBOX);
	return 1;
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

/* textbox = Textbox(left, top, width, height, [flags]) */
LUALIB_API int L_Textbox(lua_State *L) {
	int left; int top;
	int width; int height;
	int flags;
	newtComponent result;
	
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	width = luaL_checkinteger(L, 3);
	height = luaL_checkinteger(L, 4);
	if (lua_gettop(L) < 5 || lua_isnil(L, 5) == 1) flags = 0;		
	else flags = luaL_checkinteger(L, 5);
	
	result = newtTextbox(left, top, width, height, flags);
	lua_pushcomponent(L, result, TYPE_TEXTBOX);
	return 1;
}

LUALIB_API int L_TextboxReflowed(lua_State *L) {
	return 0;
}

/* list = Listbox(left, top, height, flags) */
LUALIB_API int L_Listbox(lua_State *L) {
	int left; int top;
	int height; int flags;
	newtComponent result;
	
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	height = luaL_checkinteger(L, 3);
	if (lua_gettop(L) < 4 || lua_isnil(L, 4) == 1) flags = 0;		
	else flags = luaL_checkinteger(L, 4);
	
	result = newtListbox(left, top, height, flags);
	lua_pushcomponent(L, result, TYPE_LISTBOX);
	return 1;
}

/* com = Radiobutton(left, top, text, [selected], [prev]) */
LUALIB_API int L_Radiobutton(lua_State *L) {
	int left; int top;
	const char *text;
	bool selected;
	component com;
	newtComponent prev;
	newtComponent result;
	
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	text = luaL_checkstring(L, 3);
	if (lua_gettop(L) < 4 || lua_isnil(L, 4) == 1) selected = false;
	else selected = lua_toboolean(L, 4);
	if (lua_gettop(L) < 5 || lua_isnil(L, 5) == 1) prev = NULL;
	else {
		com = luaL_checkcomponent(L, 5);
		if (com->t != TYPE_RADIOBUTTON) return luaL_error(L, "Previous component must be a Radiobutton");
		prev = com->p;
	}
	
	result = newtRadiobutton(left, top, text, selected, prev);
	lua_regtag(L, result, text);
	lua_pushcomponent(L, result, TYPE_RADIOBUTTON);
	return 1;	
}

/* com = Scale(left, top, width, max) */
LUALIB_API int L_Scale(lua_State *L) {
	int left; int top; 
	int width; lua_Integer max;
	newtComponent result;
	
	left = luaL_checkinteger(L, 1);
	top = luaL_checkinteger(L, 2);
	width = luaL_checkinteger(L, 3);
	max = luaL_checkinteger(L, 4);
	
	result = newtScale(left, top, width, max);
	lua_pushcomponent(L, result, TYPE_SCALE);
	return 1;
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
	int argi; int argc;
	component form;
	component com;
	form = luaL_checkcomponent(L, 1);
	if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
	argc = lua_gettop(L);
	argi = 2;
	while ((argc > 1) && (argi <= argc)) {
		if ((lua_type(L, argi) == LUA_TUSERDATA) && (luaL_testudata(L, argi, TYPE_COMPONENT) != NULL)) {
			com = lua_toncom(L, argi);
			newtFormAddComponent(form->p, com->p);
		} else if (lua_type(L, argi) == LUA_TTABLE) {
			/* iterate through the array */
			lua_pushnil(L);  /* first key */
			while (lua_next(L, argi) != 0) {
				if ((lua_type(L, -1) == LUA_TUSERDATA) && (luaL_testudata(L, -1, TYPE_COMPONENT) != NULL)) {
					com = lua_toncom(L, -1);
					newtFormAddComponent(form->p, com->p);
				}
				/* removes 'value'; keeps 'key' for next iteration */
				lua_pop(L, 1);
			}
		}
		argi++;
	}
	return 0;
}

/* form:AddHotKey(key) */
/* form:AddHotKey({key, ...}) */
LUALIB_API int L_AddHotKey(lua_State *L) {
	component com;
	int key;
	
	com = luaL_checkcomponent(L, 1);
	if (com->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
	if (lua_type(L, 2) == LUA_TTABLE) {
		/* iterate through the array */
		lua_pushnil(L);  /* first key */
		while (lua_next(L, 2) != 0) {
			key = luaL_checkinteger(L, -1);
			newtFormAddHotKey(com->p, key);
			/* removes 'value'; keeps 'key' for next iteration */
			lua_pop(L, 1);
		}
	} else {
		key = luaL_checkinteger(L, 2);
		newtFormAddHotKey(com->p, key);
	}
	
	return 0;
}

/* listbox:AppendEntry(text, [index]) */
/* listbox:AppendEntry({text, text}, [startindex]) */
LUALIB_API int L_AppendEntry(lua_State *L) {
	component com;
	const char *text;
	size_t key;
	
	com = luaL_checkcomponent(L, 1);
	if (com->t != TYPE_LISTBOX) return luaL_error(L, "Invalid Method");
	if (lua_gettop(L) < 3 || lua_isnil(L, 3) == 1) 
		/* hack for newtListItemCount */
		key = ((struct listbox *)com->p->data)->numItems + 1;
	else key = luaL_checkinteger(L, 3);

	if (lua_type(L, 2) == LUA_TTABLE) {
		/* iterate through the array */
		lua_pushnil(L);  /* first key */
		while (lua_next(L, 2) != 0) {
			text = luaL_checkstring(L, -1);
			newtListboxAppendEntry(com->p, text, (const void *)key);
			/* removes 'value'; keeps 'key' for next iteration */
			lua_pop(L, 1);
			key++;
		}
	} else {
		text = luaL_checkstring(L, 2);
		newtListboxAppendEntry(com->p, text, (const void *)key);
	}

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

LUALIB_API int L_ClearSelection(lua_State *L) {
	return 0;
}

LUALIB_API int L_DeleteEntry(lua_State *L) {
	return 0;
}

LUALIB_API int L_Destroy(lua_State *L) {
	component form;
	form = luaL_checkcomponent(L, 1);
	if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method"); 
	newtFormDestroy(form->p);
	return 0;
}

/* form:Draw() */
LUALIB_API int L_Draw(lua_State *L) {
	component form;
	form = luaL_checkcomponent(L, 1);
	if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method"); 
	newtDrawForm(form->p);
	return 0;
}

/* com = radiobutton:GetCurrent() */
LUALIB_API int L_GetCurrent(lua_State *L) {
	component com;
	size_t iresult;
	newtComponent cresult;
	
	com = luaL_checkcomponent(L, 1);
	switch (com->t) {
		case TYPE_RADIOBUTTON:
			cresult = newtRadioGetCurrent(com->p);
			lua_pushcomponent(L, cresult, TYPE_RADIOBUTTON);
			break;
		case TYPE_LISTBOX:
			iresult = (size_t)newtListboxGetCurrent(com->p);
			lua_pushinteger(L, iresult);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	
	return 1;
}

LUALIB_API int L_GetSelection(lua_State *L) {
	return 0;
}

LUALIB_API int L_GetNumLines(lua_State *L) {
	return 0;
}

/* value = entry:GetValue() */
/* value = checkbox:GetValue() */
LUALIB_API int L_GetValue(lua_State *L) {
	component com;
	char c;
	
	com = luaL_checkcomponent(L, 1);
	switch (com->t) {
		case TYPE_ENTRY:
			lua_pushstring(L, newtEntryGetValue(com->p));
			break;
		case TYPE_CHECKBOX:
			c = newtCheckboxGetValue(com->p);
			if (c == ' ') lua_pushboolean(L, false);
			else lua_pushboolean(L, true);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	return 1;
}

LUALIB_API int L_InsertEntry(lua_State *L) {
	return 0;
}

/* hex = com:ID() */
LUALIB_API int L_ID(lua_State *L) {
	component com;
	char result[20];
	
	com = luaL_checkcomponent(L, 1);
	sprintf(result, "%p", (void *)(com->p));

	lua_pushstring(L, result);
	return 1;
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

LUALIB_API int L_SelectItem(lua_State *L) {
	return 0;
}

/* entry:Set(value, [cursoratend]) */
/* scale:Set(value) */
LUALIB_API int L_Set(lua_State *L) {
	component com;
	const char *svalue;
	bool cursoratend;
	lua_Integer ivalue;
	
	com = luaL_checkcomponent(L, 1);
	switch (com->t) {
		case TYPE_ENTRY:
			svalue = luaL_checkstring(L, 2);
			if (lua_gettop(L) < 3) cursoratend = false;
			else cursoratend = lua_toboolean(L, 3);
			newtEntrySet(com->p, svalue, cursoratend);
			break;
		case TYPE_SCALE:
			ivalue = luaL_checkinteger(L, 2);
			newtScaleSet(com->p, ivalue);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	return 0;	
}

/* com = com:SetType(type) */
LUALIB_API int L_SetType(lua_State *L) {
	component com;
	int type;
	
	com = luaL_checkcomponent(L, 1);
	type = luaL_checkinteger(L, 2);
	
	lua_pushcomponent(L, com->p, type);
	return 1;
}

LUALIB_API int L_SetValue(lua_State *L) {
	return 0;
}

LUALIB_API int L_SetBackground(lua_State *L) {
	return 0;
}

LUALIB_API int L_SetHeight(lua_State *L) {
	return 0;
}

/* form:SetTimer(millisecs) */
LUALIB_API int L_SetTimer(lua_State *L) {
	component com;
	int period;
	
	com = luaL_checkcomponent(L, 1);
	period = luaL_checkinteger(L, 2);
	
	switch (com->t) {
		case TYPE_FORM:
			newtFormSetTimer(com->p, period);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
	
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
		case TYPE_TEXTBOX:
			newtTextboxSetText(com->p, text);
			break;
		default:
			return luaL_error(L, "Invalid Method");
	}
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

/* tag = com:Text() */
LUALIB_API int L_Text(lua_State *L) {
	component com;
	com = luaL_checkcomponent(L, 1);
	
	lua_pushtag(L, com->p);
	return 1;
}




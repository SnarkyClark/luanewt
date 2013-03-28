#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <lua.h>
#include <lauxlib.h>
#include <newt.h>

#define MYNAME "NEWT"
#define MYVERSION MYNAME " binding for " LUA_VERSION " 2013.03.20"

#define TYPE_COMPONENT "Newt.Component"

#define TYPE_UNKNOWN 0
#define TYPE_ENTRY 1
#define TYPE_BUTTON 2
#define TYPE_FORM 3
#define TYPE_LABEL 4
#define TYPE_LISTBOX 5

#define lua_newncom(L) ((component)(lua_newuserdata(L, sizeof(struct com_t))))
#define lua_toncom(L, i) ((component)(lua_touserdata(L, i)))

#define bool int
#define false 0
#define true 1

/** wrapper structs **/

struct com_t {
	newtComponent p;
	int t;
};

typedef struct com_t * component;

/** module registration **/

/* open the library - used by require() */
LUALIB_API int luaopen_newt(lua_State *L);

/** exported functions **/

/* root functions */
LUALIB_API int L_Init(lua_State *L);
LUALIB_API int L_Cls(lua_State *L);
LUALIB_API int L_Compare(lua_State *L);
LUALIB_API int L_WaitForKey(lua_State *L);
LUALIB_API int L_ClearKeyBuffer(lua_State *L);
LUALIB_API int L_DrawRootText(lua_State *L);
LUALIB_API int L_OpenWindow(lua_State *L);
LUALIB_API int L_CenteredWindow(lua_State *L);
LUALIB_API int L_PopWindow(lua_State *L);
LUALIB_API int L_PushHelpLine(lua_State *L);
LUALIB_API int L_PopHelpLine(lua_State *L);
LUALIB_API int L_Refresh(lua_State *L);
LUALIB_API int L_Finished(lua_State *L);
LUALIB_API int L_WinMessage(lua_State *L);
LUALIB_API int L_Suspend(lua_State *L);
LUALIB_API int L_Resume(lua_State *L);
LUALIB_API int L_SetSuspendCallback(lua_State *L);
LUALIB_API int L_Bell(lua_State *L);
LUALIB_API int L_GetScreenSize(lua_State *L);
LUALIB_API int L_ReflowText(lua_State *L);

/* widgets */
LUALIB_API int L_Button(lua_State *L);
LUALIB_API int L_CompactButton(lua_State *L);
LUALIB_API int L_Checkbox(lua_State *L);
LUALIB_API int L_Entry(lua_State *L);
LUALIB_API int L_Form(lua_State *L);
LUALIB_API int L_Label(lua_State *L);
LUALIB_API int L_Textbox(lua_State *L);
LUALIB_API int L_TextboxReflowed(lua_State *L);
LUALIB_API int L_Listbox(lua_State *L);
LUALIB_API int L_Radiobutton(lua_State *L);
LUALIB_API int L_Scale(lua_State *L);
LUALIB_API int L_VerticalScrollbar(lua_State *L);

/* Newt.Component Object */
LUALIB_API int L_AddCallback(lua_State *L);
LUALIB_API int L_AddComponents(lua_State *L);
LUALIB_API int L_AddHotKey(lua_State *L);
LUALIB_API int L_AppendEntry(lua_State *L);
LUALIB_API int L_Clear(lua_State *L);
LUALIB_API int L_ClearSelection(lua_State *L);
LUALIB_API int L_DeleteEntry(lua_State *L);
LUALIB_API int L_Destroy(lua_State *L);
LUALIB_API int L_GetCurrent(lua_State *L);
LUALIB_API int L_GetSelection(lua_State *L);
LUALIB_API int L_GetNumLines(lua_State *L);
LUALIB_API int L_GetValue(lua_State *L);
LUALIB_API int L_InsertEntry(lua_State *L);
LUALIB_API int L_Run(lua_State *L);
LUALIB_API int L_SelectItem(lua_State *L);
LUALIB_API int L_Set(lua_State *L);
LUALIB_API int L_SetBackground(lua_State *L);
LUALIB_API int L_SetCurrent(lua_State *L);
LUALIB_API int L_SetCurrentByKey(lua_State *L);
LUALIB_API int L_SetEntry(lua_State *L);
LUALIB_API int L_SetHeight(lua_State *L);
LUALIB_API int L_SetText(lua_State *L);
LUALIB_API int L_SetTimer(lua_State *L);
LUALIB_API int L_SetValue(lua_State *L);
LUALIB_API int L_SetWidth(lua_State *L);
LUALIB_API int L_TakesFocus(lua_State *L);

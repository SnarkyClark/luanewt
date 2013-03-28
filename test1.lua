package.cpath = package.cpath .. ";./Debug/?.so"
require('newt')

newt.Init()
newt.Cls()

local msg = "Hello World!"
local cols, rows = newt.GetScreenSize()
newt.DrawRootText((cols - #msg) / 2, rows / 2, msg)

newt.PushHelpLine(nil)
newt.Refresh()
newt.WaitForKey()

newt.PushHelpLine("Testing 1,2,3...")
newt.Refresh()
newt.WaitForKey()

newt.PopHelpLine()
newt.CenteredWindow(20, 4, "Window 1")
newt.WaitForKey()

newt.PopWindow()
newt.OpenWindow(5, 5, 20, 4, "Window 2")
newt.Refresh()
newt.WaitForKey()

newt.Finished()
package.cpath = package.cpath .. ";./Debug/?.so"
local n = require('newt')

n.Init()
n.Cls()

local msg = "Newt Test 2"
local cols, rows = n.GetScreenSize()
n.DrawRootText((cols - #msg) / 2, rows / 2, msg)

n.PushHelpLine(nil)

n.OpenWindow(10, 5, 40, 6, "Button Sample")

b1 = n.Button(10, 1, "Ok")
b2 = n.Button(22, 1, "Cancel")

form = n.Form(nil, nil, 0)

form:AddComponents(b1, b2)
r, v = form:Run()
form:Destroy()

n.Finished()

if r == n.EXIT_COMPONENT then
	if n.Compare(v, b1) then
		print("Ok!")
	elseif n.Compare(v, b2) then
		print("Cancel!")
	else
		print("????")
	end
else 
	print(r, v)
end
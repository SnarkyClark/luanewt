package.cpath = package.cpath .. ";./Debug/?.so"
local n = require('newt')

n.Init()
n.Cls()

local msg = "Newt Test 2"
local cols, rows = n.GetScreenSize()
n.DrawRootText((cols - #msg) / 2, rows / 2, msg)

n.PushHelpLine(nil)

n.OpenWindow((cols - 40) / 2, (rows - 20) / 2, 40, 20, "Test Form")

form = n.Form(nil, nil, 0)

label = n.Label(1, 1, "Test Label")
entry = n.Entry(12, 1, "Test", 20)
button = {
	ok = n.Button(10, 3, "Ok"),
	cancel = n.Button(22, 3, "Cancel")
}

form:AddComponents(label, entry, button.ok, button.cancel)
entry:Set("Updated Test", true)

r, v = form:Run()
value = entry:GetValue()
form:Destroy()

n.Finished()

if r == n.EXIT_COMPONENT then
	if v:ID() == button.ok:ID() then
		print(v:ID(), "Ok!", value)
	elseif v:ID() == button.cancel:ID() then
		print(v:ID(), "Cancel!")
	else
		print(v:ID(), "????")
	end
else 
	print(r, v)
end
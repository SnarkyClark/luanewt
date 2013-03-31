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
radio = {}
radio.red = n.Radiobutton(1, 2, "Red", false)
radio.green = n.Radiobutton(1, 3, "Green", true, radio.red)
radio.blue = n.Radiobutton(1, 4, "Blue", false, radio.green)

button = {
	ok = n.Button(10, 5, "Ok"),
	cancel = n.Button(22, 5, "Cancel")
}

form:AddComponents(label, entry, radio.red, radio.green, radio.blue, button.ok, button.cancel)
entry:Set("Updated Test", true)

r, v = form:Run()
value = {
	entry = entry:GetValue(),
	radio = radio.red:GetCurrent():Tag()
}

form:Destroy()

n.Finished()

if r == n.EXIT_COMPONENT then
	if v:Tag() == 'Ok' then
		print("Entry: " .. value.entry)
		print("Radio: " .. value.radio)
	elseif v:Tag() == 'Cancel' then
		print("Canceled!")
	else
		print(v:ID(), "????")
	end
else 
	print(r, v)
end
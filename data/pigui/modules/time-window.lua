-- Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = require 'Engine'
local Game = require 'Game'
local utils = require 'utils'
local Event = require 'Event'

local Lang = require 'Lang'
local lc = Lang.GetResource("core");
local lui = Lang.GetResource("ui-core");

local ui = require 'pigui'

local player = nil
local pionillium = ui.fonts.pionillium
local colors = ui.theme.colors
local icons = ui.theme.icons
-- names of the keys in lang/core/
local months = {"MONTH_JAN", "MONTH_FEB", "MONTH_MAR", "MONTH_APR", "MONTH_MAY", "MONTH_JUN", "MONTH_JUL", "MONTH_AUG", "MONTH_SEP", "MONTH_OCT", "MONTH_NOV", "MONTH_DEC"}

local button_size = Vector2(32,32) * (ui.screenHeight / 1200)
local frame_padding = 3
local bg_color = colors.buttonBlue
local fg_color = colors.white


local function displayTimeWindow()
	player = Game.player

	-- HACK: Don't display the time window if we're in a bespoke view
	if Game.CurrentView() == nil then return end

	local year, month_num, day, hour, minute, second = Game.GetDateTime()
	local month = lc[months[month_num]]
	local date = string.format("%04i %s %i - %02i:%02i:%02i", year, month, day, hour, minute, second)
	local current = Game.GetTimeAcceleration()
	local requested = Game.GetRequestedTimeAcceleration()

	local function accelButton(name, key)
		local color = bg_color
		if requested == name and current ~= name then
			color = colors.white
		end
		local time = name
		-- translate only paused, the rest can stay
		if time == "paused" then
			time = lc.PAUSED
		end
		local tooltip = string.interp(lui.HUD_REQUEST_TIME_ACCEL, { time = time })
		if ui.coloredSelectedIconButton(icons['time_accel_' .. name], button_size, current == name, frame_padding, color, fg_color, tooltip .. "##time_accel_"..name)
		or (ui.shiftHeld() and ui.isKeyReleased(key)) then
			Game.SetTimeAcceleration(name, ui.ctrlHeld() or ui.isMouseDown(1))
		end
		ui.sameLine()
	end

	ui.withFont(pionillium.large.name, pionillium.large.size, function()
		local text_size = ui.calcTextSize(date)
		local window_size = Vector2(math.max(text_size.x, (button_size.x + frame_padding * 2 + 7) * 6) + 15, text_size.y + button_size.y + frame_padding * 2 + 20)
		ui.timeWindowSize = window_size
		ui.setNextWindowSize(window_size, "Always")
		ui.setNextWindowPos(Vector2(0, ui.screenHeight - window_size.y), "Always")
		ui.window("Time", {"NoTitleBar", "NoResize", "NoSavedSettings", "NoFocusOnAppearing", "NoBringToFrontOnFocus"}, function()
			ui.text(date)
			accelButton("paused", ui.keys.escape)
			accelButton("1x", ui.keys.f1)
			accelButton("10x", ui.keys.f2)
			accelButton("100x", ui.keys.f3)
			accelButton("1000x", ui.keys.f4)
			accelButton("10000x", ui.keys.f5)
		end)
	end)
end

ui.registerModule("game", displayTimeWindow)

return {}

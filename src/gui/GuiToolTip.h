// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUITOOLTIP_H
#define _GUITOOLTIP_H

#include "GuiWidget.h"
#include <string>

namespace Gui {
	class ToolTip : public Widget {
	public:
		ToolTip(Widget *owner, const char *text);
		ToolTip(Widget *owner, std::string &text);
		virtual void Draw();
		virtual ~ToolTip();
		virtual void GetSizeRequested(float size[2]);
		void SetText(const char *text);
		void SetText(std::string &text);

	private:
		void CalcSize();
		Widget *m_owner;
		std::string m_text;
		std::unique_ptr<TextLayout> m_layout;
		Uint32 m_createdTime;
		Graphics::Drawables::Lines m_outlines;
		std::unique_ptr<Graphics::Drawables::Rect> m_background;
	};
} // namespace Gui

#endif /* _GUITOOLTIP_H */

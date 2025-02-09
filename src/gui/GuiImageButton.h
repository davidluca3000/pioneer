// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUIIMAGEBUTTON_H
#define _GUIIMAGEBUTTON_H

#include "GuiButton.h"
#include "GuiWidget.h"
#include "gui/GuiImage.h"

#include <string>

namespace Gui {
	class ImageButton : public Button {
	public:
		ImageButton(const char *img_normal);
		ImageButton(const char *img_normal, const char *img_pressed);
		virtual void Draw();
		virtual ~ImageButton();
		virtual void GetSizeRequested(float size[2]);
		void SetRenderDimensions(const float wide, const float high);

	private:
		void LoadImages(const char *img_normal, const char *img_pressed);
		Image *m_imgNormal;
		Image *m_imgPressed;
	};
} // namespace Gui

#endif /* _GUIIMAGEBUTTON_H */

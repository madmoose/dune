/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef DUNE_GRAPHICS_H
#define DUNE_GRAPHICS_H

#include "common/endian.h"

namespace Common {
	class ReadStream;
}

namespace Dune {

class DuneEngine;

class Graphics {
	DuneEngine *_engine;

	byte *_framebuffer;

	int  _global_y_offset;

	bool _pal1_slot_active[256];

	byte _pal1[256][3] = { { 0 } };
	byte _pal2[256][3] = {
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x2A }, { 0x00, 0x2A, 0x00 }, { 0x00, 0x2A, 0x2A },
		{ 0x2A, 0x00, 0x00 }, { 0x3F, 0x34, 0x14 }, { 0x2A, 0x15, 0x00 }, { 0x2A, 0x2A, 0x2A },
		{ 0x15, 0x15, 0x15 }, { 0x15, 0x15, 0x3F }, { 0x15, 0x3F, 0x15 }, { 0x15, 0x3F, 0x3F },
		{ 0x3F, 0x15, 0x15 }, { 0x3F, 0x15, 0x3F }, { 0x3F, 0x3F, 0x15 }, { 0x3F, 0x3F, 0x3F },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x3E, 0x39, 0x1B }, { 0x3F, 0x3F, 0x26 }, { 0x3F, 0x3D, 0x15 }, { 0x3F, 0x36, 0x1B },
		{ 0x3F, 0x2D, 0x00 }, { 0x36, 0x24, 0x0A }, { 0x36, 0x18, 0x0A }, { 0x2D, 0x10, 0x00 },
		{ 0x24, 0x12, 0x00 }, { 0x1B, 0x12, 0x0F }, { 0x1B, 0x0E, 0x08 }, { 0x12, 0x00, 0x0F },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x30, 0x3F, 0x34 }, { 0x28, 0x36, 0x2E }, { 0x21, 0x2D, 0x28 }, { 0x1A, 0x24, 0x21 },
		{ 0x13, 0x1B, 0x1A }, { 0x0D, 0x13, 0x13 }, { 0x08, 0x04, 0x08 }, { 0x10, 0x04, 0x18 },
		{ 0x08, 0x00, 0x10 }, { 0x04, 0x00, 0x0C }, { 0x0A, 0x00, 0x02 }, { 0x14, 0x1C, 0x1A },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x14, 0x18, 0x1C }, { 0x01, 0x01, 0x02 },
		{ 0x04, 0x04, 0x05 }, { 0x07, 0x06, 0x09 }, { 0x09, 0x09, 0x0C }, { 0x0C, 0x0B, 0x0F },
		{ 0x0F, 0x0E, 0x12 }, { 0x11, 0x11, 0x16 }, { 0x14, 0x13, 0x19 }, { 0x17, 0x16, 0x1C },
		{ 0x1E, 0x1A, 0x21 }, { 0x27, 0x1D, 0x27 }, { 0x2D, 0x20, 0x29 }, { 0x33, 0x23, 0x28 },
		{ 0x39, 0x28, 0x26 }, { 0x3F, 0x33, 0x29 }, { 0x3F, 0x3F, 0x29 }, { 0x00, 0x00, 0x3F },
		{ 0x02, 0x00, 0x3B }, { 0x05, 0x00, 0x37 }, { 0x08, 0x00, 0x34 }, { 0x0A, 0x00, 0x30 },
		{ 0x0C, 0x00, 0x2C }, { 0x0E, 0x00, 0x29 }, { 0x0E, 0x00, 0x25 }, { 0x0F, 0x00, 0x21 },
		{ 0x0F, 0x00, 0x1E }, { 0x0F, 0x00, 0x1A }, { 0x0E, 0x00, 0x16 }, { 0x0D, 0x00, 0x13 },
		{ 0x0B, 0x00, 0x0F }, { 0x09, 0x00, 0x0B }, { 0x07, 0x00, 0x08 }, { 0x3B, 0x30, 0x28 },
		{ 0x3B, 0x31, 0x28 }, { 0x3B, 0x31, 0x29 }, { 0x3C, 0x32, 0x2A }, { 0x3C, 0x33, 0x2B },
		{ 0x3C, 0x33, 0x2C }, { 0x3C, 0x34, 0x2C }, { 0x3D, 0x34, 0x2E }, { 0x3D, 0x35, 0x2E },
		{ 0x3D, 0x36, 0x2F }, { 0x08, 0x10, 0x0A }, { 0x3F, 0x3F, 0x3F }, { 0x2E, 0x3D, 0x32 },
		{ 0x22, 0x30, 0x28 }, { 0x1F, 0x2A, 0x26 }, { 0x26, 0x34, 0x2C }, { 0x08, 0x0A, 0x10 },
		{ 0x0B, 0x0B, 0x10 }, { 0x0C, 0x0B, 0x10 }, { 0x0D, 0x0B, 0x10 }, { 0x0F, 0x0B, 0x10 },
		{ 0x10, 0x0B, 0x10 }, { 0x10, 0x0B, 0x0F }, { 0x10, 0x0B, 0x0D }, { 0x10, 0x0B, 0x0C },
		{ 0x10, 0x0B, 0x0B }, { 0x32, 0x32, 0x32 }, { 0x2F, 0x2A, 0x37 }, { 0x1E, 0x16, 0x3E },
		{ 0x1C, 0x0B, 0x3F }, { 0x0F, 0x10, 0x0B }, { 0x3D, 0x34, 0x2E }, { 0x0C, 0x10, 0x0B },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x3F, 0x3F, 0x3F }
	};
	byte _pal3[16][3] = {
		{ 0x12, 0x12, 0x12 }, { 0x15, 0x15, 0x15 }, { 0x18, 0x18, 0x18 }, { 0x1B, 0x1B, 0x1B },
		{ 0x1E, 0x1E, 0x1E }, { 0x21, 0x21, 0x21 }, { 0x24, 0x24, 0x24 }, { 0x27, 0x27, 0x27 },
		{ 0x2A, 0x2A, 0x2A }, { 0x2D, 0x2D, 0x2D }, { 0x30, 0x30, 0x30 }, { 0x33, 0x33, 0x33 },
		{ 0x36, 0x36, 0x36 }, { 0x39, 0x39, 0x39 }, { 0x3C, 0x3C, 0x3C }, { 0x3F, 0x3F, 0x3F },
	};

public:
	Graphics(DuneEngine *_engine);

	/* 00 */ void setMode();
	/* 01 */ void getInfo(byte **screen, int *size);

	void  setFrameBuffer(byte *framebuffer) {
		_framebuffer = framebuffer;
	}
	void  drawCursor(int x, int y, const byte *cursorData);
	void  setGlobalYOffset(int y_offset);
	byte *getPixelPtr(int x, int y);

	void draw_4bpp    (bool flip_x, bool flip_y, Common::ReadStream *r, int x_offset, int y_offset, int w, int h, byte mode);
	void draw_4bpp_rle(bool flip_x, bool flip_y, Common::ReadStream *r, int x_offset, int y_offset, int w, int h, byte mode);
	void draw_8bpp    (bool flip_x, bool flip_y, Common::ReadStream *r, int x_offset, int y_offset, int w, int h, byte mode);
	void draw_8bpp_rle(bool flip_x, bool flip_y, Common::ReadStream *r, int x_offset, int y_offset, int w, int h, byte mode);

	void blitGraphics(Common::ReadStream *r, int x_offset, int y_offset, int w, int h, byte flags, byte mode);
	void blitGraphics(byte *buf, int buf_len, int x_offset, int y_offset, int w, int h, byte flags, byte mode);
	void copyScaled(byte *src, uint16 src_pitch, int x_offset, int y_offset, int dst_w, int dst_h, byte flags, byte pal_offset, uint16 src_delta_fp);

	void drawNoise(uint16 x, uint16 y, uint16 count, uint16 start_value, uint16 increment, uint16 xor_state, uint16 xor_increment);
};

} // End of namespace Dune

#endif

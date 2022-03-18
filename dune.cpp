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

#include "dune/dune.h"

#include "dune/hsq.h"
#include "dune/intro.h"
#include "dune/room.h"
#include "dune/resources.h"
#include "dune/sprite_sheet.h"
#include "dune/statics.h"
#include "dune/video.h"

#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/debug.h"
#include "common/file.h"
#include "common/fs.h"
#include "common/scummsys.h"
#include "engines/util.h"
#include "graphics/palette.h"
#include "gui/EventRecorder.h"

namespace Dune {

DuneEngine::DuneEngine(OSystem *syst, const ADGameDescription *gameDesc)
	: Engine(syst),
	  _graphics(this)
{
	_timerTicks = 0;
	_video = new HnmPlayer(this);
	_rnd = new Common::RandomSource("dune_randomseed");

	_currentBankId   = 0xffff;
	_currentBankData = nullptr;
}

DuneEngine::~DuneEngine() {
	delete _rnd;
}

Common::Error DuneEngine::run() {
	debug("run");
	_graphics.getInfo(&_screen, &_screenBufferSize);
	_graphics.setMode();

	if (!_archive.openArchive("DUNE.DAT")) {
		debug("Failed to open DUNE.DAT");
	}

	_framebuffer1 = new byte[320*200]{};
	_framebuffer2 = new byte[320*200]{};

	_graphics.setFrameBuffer(_framebuffer1);

	Common::Event event;
	Common::EventManager *eventMan = _system->getEventManager();

	openSpriteSheet("POR.HSQ");

	Room room(this, _archive.openMember("PALACE.SAL"));
	room.draw(_framebuffer1, 0);

	if (true) {
		struct ui_element_t {
			int16_t  x;
			int16_t  y;
			int16_t  unk2;
			int16_t  unk3;
			int16_t  unk4;
			uint16_t id;
			uint16_t unk6;
		};

		ui_element_t ui_elements[22] = {
			{  22, 161,  68, 196,    0,  0xffff, 0xb8c6 },
			{   0, 152,   0, 152,    0,       0, 0x0f66 },
			{ 228, 152, 300, 198,    0,       3, 0x0f66 },
			{  24, 155,  69, 176, 0x80,  0xffff, 0xaed6 },
			{  92, 152, 229, 159,    0,      14, 0x0f66 },
			{   2, 154,   2, 154,    0,      12, 0x0f66 },
			{ 317, 154, 317, 154,    0,      12, 0x0f66 },
			{  92, 159, 228, 167, 0x80,      27, 0xd443 },
			{  92, 167, 228, 175, 0x80,      27, 0xd43e },
			{  92, 175, 228, 183, 0x80,      27, 0xd439 },
			{  92, 183, 228, 191, 0x80,      27, 0xd434 },
			{  92, 191, 228, 199, 0x80,      27, 0xd42f },
			{ 255, 162, 295, 192,    0,  0xffff, 0x0f66 },
			{ 269, 162, 279, 172,    0,  0xffff, 0x0f66 },
			{ 284, 172, 294, 182,    0,  0xffff, 0x0f66 },
			{ 269, 181, 279, 191,    0,  0xffff, 0x0f66 },
			{ 255, 172, 265, 182,    0,  0xffff, 0x0f66 },
			{   0,   0,   0,   0,    0,  0xffff, 0x0f66 },
			{   0,   0,   0,   0,    0,  0xffff, 0x0f66 },
			{   0,   0,   0,   0,    0,  0xffff, 0x945b },
			{   0,   0, 320, 152,    0,  0xffff, 0x941d },
			{  35, 182,  56, 196, 0x80,      64, 0x9215 }
		};

		openSpriteSheet("ICONES.HSQ");
		for (int i = 0; i != 22; ++i) {
			if (ui_elements[i].id != 0xffff) {
				drawSprite(
					ui_elements[i].id,
					ui_elements[i].x,
					ui_elements[i].y,
					0x00);
			}
		}
	}

	_system->copyRectToScreen(_framebuffer1, 320, 0, 0, 320, 200);
	_system->updateScreen();

	while (!shouldQuit()) {
		while (eventMan->pollEvent(event)) {
		}
		_system->delayMillis(10);
	}

	return Common::kNoError;
}

void DuneEngine::runIntro() {
	Intro intro(this);
	intro.run();
};

bool DuneEngine::isCD() {
	return _gameDescription->flags & ADGF_CD;
}

void DuneEngine::loadBank(uint16 index) {
	if (index == _currentBankId) {
		return;
	}
}

void DuneEngine::applyPaletteBlock(Common::ReadStream *reader) {
	uint8 buf[3 * 256];
	PaletteManager *paletteManager = _system->getPaletteManager();

	for (;;) {
		uint16 h = reader->readUint16LE();
		if (h == 0x100) {
			// Skip 3 bytes
			reader->readByte();
			reader->readByte();
			reader->readByte();
			continue;
		}
		if (h == 0xffff) {
			break;
		}
		int count = (h >> 8);
		int index = h & 0xff;

		if (count == 0) {
			count = 256;
		}

		reader->read(buf, 3 * count);

		// Convert R6G6B6 to R8G8B8
		for (int i = 0; i != 3 * count; ++i) {
			buf[i] = (buf[i] * 255 + 31) / 63;
		}

		paletteManager->setPalette(buf, index, count);
	}
}

void DuneEngine::dumpResource(const char *filename) {
	Resource r = _archive.openMember(filename);
	if (!r) {
		return;
	}

	Common::DumpFile f;

	Common::String fn = filename;
	fn.replace(6, 3, "BIN");
	f.open(fn);

	int size = r->size();
	byte *buf = new byte[size];
	r->read(buf, size);

	f.write(buf, size);
	r->seek(0);
	delete[] buf;
}

void DuneEngine::loadVideo(uint16 videoId) {
	const char *filename = getResourceFilenameByIndex(videoId + INDEX_FIRST_HNM);
	debug("openMember(\"%s\")\n", filename);
	Resource r = _archive.openMember(filename);
	if (!r) {
		return;
	}
	_video->setReader(r);
}

void DuneEngine::playVideo(uint16 videoId) {
	const char *filename = getResourceFilenameByIndex(videoId + INDEX_FIRST_HNM);
	debug("openMember(\"%s\")\n", filename);
	Resource r = _archive.openMember(filename);
	if (!r) {
		return;
	}
	_video->setReader(r);

	if (videoId == HNM_IRULAN) {
		_video->setSubtitles(Subs::irulan, _archive.openMember("IRUL1.HSQ"));
	}

	_video->setInterlace(videoId >= HNM_IRULAN);
	_video->start();

	Common::Event event;
	Common::EventManager *eventMan = _system->getEventManager();

	float nextFrameTime = _system->getMillis() + (1000.0/12.0);
	while (!_video->done() && !shouldQuit()) {
		_video->decodeAVFrame();

		_system->copyRectToScreen(_video->_frameBuffer, 320, 0, 0, 320, 200);
		_system->updateScreen();

		while (eventMan->pollEvent(event)) {
		}

		float now = _system->getMillis();
		if (now < nextFrameTime) {
			_system->delayMillis((int)floor(nextFrameTime - now));
		}
		nextFrameTime += (1000.0/12.0);
	}

}

void DuneEngine::dumpSAL(const char *filename) {
	Resource r = _archive.openMember(filename);

	Common::Array<uint32_t> roomOffsets;

	uint16_t offset_0 = r->readUint16LE();
	roomOffsets.push_back(offset_0);

	for (int i = 1; i != offset_0 / 2; ++i) {
		uint16_t offset = r->readUint16LE();
		roomOffsets.push_back(offset);
	}

	for (int i = 0; i != roomOffsets.size(); ++i) {
		debug("%04x", roomOffsets[i]);
	}
}

static void readFrameHeader(Common::ReadStream *r, int *w, int *h, byte *flags, byte *mode) {
	byte b[4];
	r->read(b, 4);

	*w     = ((0x1 & b[1]) << 8) | b[0];
	*flags = b[1] & 0xfe;
	*h     = b[2];
	*mode  = b[3];
}

void DuneEngine::openSpriteSheet(const char *filename) {
	Resource r = _archive.openMember(filename);

	debug("Opening sprite sheet %s", filename);
	currentSpriteSheet = new SpriteSheet(this, r);
}

void DuneEngine::drawSprite(int index, int dst_x, int dst_y, byte draw_flags) {
	assert(currentSpriteSheet);

	currentSpriteSheet->draw(index, dst_x, dst_y, draw_flags);
}

} // End of namespace Dune

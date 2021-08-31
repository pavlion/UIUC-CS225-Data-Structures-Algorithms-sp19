/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>

using namespace cs225;

struct stickerSet
{
	Image sticker;
	unsigned x;
	unsigned y;
	bool valid;
};

class StickerSheet
{
	public:
	StickerSheet (const Image &picture, unsigned max);
	~StickerSheet ();
	StickerSheet (const StickerSheet &other);
	const StickerSheet & 	operator= (const StickerSheet &other);
	void 	changeMaxStickers (unsigned max);
	int 	addSticker (Image &sticker, unsigned x, unsigned y);
	bool 	translate (unsigned index, unsigned x, unsigned y);
	void 	removeSticker (unsigned index);
	Image * 	getSticker (unsigned index);
	Image 	render () const;

	private:
	Image picture_;
	stickerSet *stickers_;
	unsigned sticker_ct;
	unsigned max_;
	void _copy(const StickerSheet &other);
	void _destroy();
};
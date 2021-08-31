#include "StickerSheet.h"
#include <iostream>
#include <algorithm>

using namespace cs225;
using std::cout;
using std::endl;

StickerSheet::StickerSheet (const Image &picture, unsigned max){
    picture_ = picture;
    stickers_ = new stickerSet[max];
    sticker_ct = 0;
    max_ = max;

    for (unsigned i = 0; i < max_; ++i)
    {
        stickers_[i].valid = false;
    }
}

StickerSheet::~StickerSheet (){
    _destroy();
}

StickerSheet::StickerSheet (const StickerSheet &other){
    _copy(other);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    if(this!=&other){
        _destroy();
        _copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max){
        stickerSet* newSticker = new stickerSet[max];
    if(max > max_){
        for (unsigned i = 0; i < max_; ++i)
        {
            newSticker[i].sticker = stickers_[i].sticker;
            newSticker[i].x = stickers_[i].x;
            newSticker[i].y = stickers_[i].y;
            newSticker[i].valid = stickers_[i].valid;
        }
        for (unsigned i = max_; i < max; ++i)
        {
            newSticker[i].x = 0;
            newSticker[i].y = 0;
            newSticker[i].valid = false;
        }
        sticker_ct = max_;
    }
    else{ //max <= max_
        for (unsigned i = 0; i < max; ++i)
        {
            newSticker[i].sticker = stickers_[i].sticker;
            newSticker[i].x = stickers_[i].x;
            newSticker[i].y = stickers_[i].y;
            newSticker[i].valid = stickers_[i].valid;
        }
        sticker_ct = max;
    }
	max_ = max;
	_destroy();
	stickers_ = newSticker;
}

int  StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
	if(sticker_ct != max_){
        stickers_[sticker_ct].sticker = sticker;//sticker_ct represents the sticker_ct+1 th sticker.
        stickers_[sticker_ct].x = x;
        stickers_[sticker_ct].y = y;
        stickers_[sticker_ct].valid = true;
        sticker_ct += 1;
        return sticker_ct;
    }
    else
        return -1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
	if(index<sticker_ct && stickers_[index].valid == true){
        stickers_[index].x = x;
        stickers_[index].y = y;
        return true;
    }
    else 
        return false;
}
void StickerSheet::removeSticker (unsigned index){
    if(index < sticker_ct && stickers_[index].valid == true)
        stickers_[index].valid = false;
    //sticker_ct -= 1;
}

Image * StickerSheet::getSticker (unsigned index){
	if(index > sticker_ct || stickers_[index].valid == false ){
		return NULL;
    }        
    else 
        return &stickers_[index].sticker;
}
Image StickerSheet::render () const{
    int xMax = picture_.width(), yMax = picture_.height();
    for (unsigned i = 0; i < sticker_ct;++i){
        if(stickers_[i].valid == true){    
            int x = stickers_[i].x + stickers_[i].sticker.width();
            int y = stickers_[i].y + stickers_[i].sticker.height();
            xMax = std::max(x, xMax);
            yMax = std::max(y, yMax);
        }
    }
    Image output;
    output.resize(xMax, yMax);

    for (unsigned i = 0; i < picture_.width();  ++i){
    for (unsigned j = 0; j < picture_.height(); ++j)
    {
        output.getPixel(i,j) = picture_.getPixel(i,j);
    }
    }

    for (unsigned i = 0; i < sticker_ct; ++i){
        if(stickers_[i].valid == true){ 
            stickerSet &s = stickers_[i];
            for (unsigned j = s.x; j < s.x+s.sticker.width() ; ++j){
            for (unsigned k = s.y; k < s.y+s.sticker.height() ; ++k)
            {
                HSLAPixel & pixel = s.sticker.getPixel(j-s.x, k-s.y);
                if(pixel.a!=0){
                    HSLAPixel & newPixel = output.getPixel(j, k);
                    newPixel = pixel;
                }
            }
            }
        }
    } 
    return output;
}

void StickerSheet::_copy(const StickerSheet &other){
    if(this != &other){
        cout<<"other.sticker_ct"<<other.sticker_ct<<endl;
        cout<<"other.max_"<<other.max_<<endl;
        picture_ = other.picture_;
        stickerSet* newSti = new stickerSet[other.max_];
        for (unsigned i = 0; i < other.sticker_ct; ++i)
        {cout<<i<<"REACHED LINE"<<__LINE__<<endl;
            newSti[i].sticker = other.stickers_[i].sticker;
            newSti[i].x = other.stickers_[i].x;
            newSti[i].y = other.stickers_[i].y;
            newSti[i].valid = other.stickers_[i].valid;
        }

        for (unsigned i = other.sticker_ct; i < other.max_; ++i)
        {cout<<i<<"REACHED LINE"<<__LINE__<<endl;
            newSti[i].x = 0;
            newSti[i].y = 0;
            newSti[i].valid = false;
        }
        sticker_ct = other.sticker_ct;
        max_ = other.max_;
        stickers_ = newSti;
    }
}

void StickerSheet::_destroy(){
    if(stickers_!=NULL){
        delete[] stickers_;
        stickers_ = NULL;
    }
}

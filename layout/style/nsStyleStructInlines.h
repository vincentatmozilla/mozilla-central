/* vim: set shiftwidth=2 tabstop=8 autoindent cindent expandtab: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Inline methods that belong in nsStyleStruct.h, except that they
 * require more headers.
 */

#ifndef nsStyleStructInlines_h_
#define nsStyleStructInlines_h_

#include "nsIFrame.h"
#include "nsStyleStruct.h"
#include "imgIRequest.h"
#include "imgIContainer.h"
#include "nsIContent.h"

inline void
nsStyleBorder::SetBorderImage(imgRequestProxy* aImage)
{
  mBorderImageSource = aImage;
  mSubImages.Clear();
}

inline imgRequestProxy*
nsStyleBorder::GetBorderImage() const
{
  NS_ABORT_IF_FALSE(!mBorderImageSource || mImageTracked,
                    "Should be tracking any images we're going to use!");
  return mBorderImageSource;
}

inline bool nsStyleBorder::IsBorderImageLoaded() const
{
  uint32_t status;
  return mBorderImageSource &&
         NS_SUCCEEDED(mBorderImageSource->GetImageStatus(&status)) &&
         (status & imgIRequest::STATUS_LOAD_COMPLETE) &&
         !(status & imgIRequest::STATUS_ERROR);
}

inline void
nsStyleBorder::SetSubImage(uint8_t aIndex, imgIContainer* aSubImage) const
{
  const_cast<nsStyleBorder*>(this)->mSubImages.ReplaceObjectAt(aSubImage, aIndex);
}

inline imgIContainer*
nsStyleBorder::GetSubImage(uint8_t aIndex) const
{
  imgIContainer* subImage = nullptr;
  if (aIndex < mSubImages.Count())
    subImage = mSubImages[aIndex];
  return subImage;
}

bool
nsStyleText::HasTextShadow(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleText() == this, "unexpected aContextFrame");
  return mTextShadow && !aContextFrame->IsSVGText();
}

nsCSSShadowArray*
nsStyleText::GetTextShadow(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleText() == this, "unexpected aContextFrame");
  if (aContextFrame->IsSVGText()) {
    return nullptr;
  }
  return mTextShadow;
}

bool
nsStyleText::WhiteSpaceCanWrap(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleText() == this, "unexpected aContextFrame");
  return WhiteSpaceCanWrapStyle() && !aContextFrame->IsSVGText();
}

bool
nsStyleText::WordCanWrap(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleText() == this, "unexpected aContextFrame");
  return WordCanWrapStyle() && !aContextFrame->IsSVGText();
}

bool
nsStyleDisplay::IsBlockInside(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  if (aContextFrame->IsSVGText()) {
    return aContextFrame->GetType() == nsGkAtoms::blockFrame;
  }
  return IsBlockInsideStyle();
}

bool
nsStyleDisplay::IsBlockOutside(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  if (aContextFrame->IsSVGText()) {
    return aContextFrame->GetType() == nsGkAtoms::blockFrame;
  }
  return IsBlockOutsideStyle();
}

bool
nsStyleDisplay::IsInlineOutside(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  if (aContextFrame->IsSVGText()) {
    return aContextFrame->GetType() != nsGkAtoms::blockFrame;
  }
  return IsInlineOutsideStyle();
}

bool
nsStyleDisplay::IsOriginalDisplayInlineOutside(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  if (aContextFrame->IsSVGText()) {
    return aContextFrame->GetType() != nsGkAtoms::blockFrame;
  }
  return IsOriginalDisplayInlineOutsideStyle();
}

uint8_t
nsStyleDisplay::GetDisplay(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  if (aContextFrame->IsSVGText() &&
      mDisplay != NS_STYLE_DISPLAY_NONE) {
    return aContextFrame->GetType() == nsGkAtoms::blockFrame ?
             NS_STYLE_DISPLAY_BLOCK :
             NS_STYLE_DISPLAY_INLINE;
  }
  return mDisplay;
}

bool
nsStyleDisplay::IsFloating(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  return IsFloatingStyle() && !aContextFrame->IsSVGText();
}

bool
nsStyleDisplay::HasTransform(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  return HasTransformStyle() && aContextFrame->IsFrameOfType(nsIFrame::eSupportsCSSTransforms);
}

bool
nsStyleDisplay::IsPositioned(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this,
               "unexpected aContextFrame");
  return (IsAbsolutelyPositionedStyle() ||
          IsRelativelyPositionedStyle() ||
          HasTransform(aContextFrame)) &&
         !aContextFrame->IsSVGText();
}

bool
nsStyleDisplay::IsRelativelyPositioned(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  return IsRelativelyPositionedStyle() && !aContextFrame->IsSVGText();
}

bool
nsStyleDisplay::IsAbsolutelyPositioned(const nsIFrame* aContextFrame) const
{
  NS_ASSERTION(aContextFrame->StyleDisplay() == this, "unexpected aContextFrame");
  return IsAbsolutelyPositionedStyle() && !aContextFrame->IsSVGText();
}

uint8_t
nsStyleVisibility::GetEffectivePointerEvents(nsIFrame* aFrame) const
{
  if (aFrame->GetContent() && !aFrame->GetContent()->GetParent()) {
    // The root element has a cluster of frames associated with it
    // (root scroll frame, canvas frame, the actual primary frame). Make
    // those take their pointer-events value from the root element's primary
    // frame.
    nsIFrame* f = aFrame->GetContent()->GetPrimaryFrame();
    if (f) {
      return f->StyleVisibility()->mPointerEvents;
    }
  }
  return mPointerEvents;
}

#endif /* !defined(nsStyleStructInlines_h_) */

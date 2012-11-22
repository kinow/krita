/*
 * Copyright (c) 2006 Cyrille Berger  <cberger@cberger.net>
 * Copyright (c) 2011 Silvio Heinrich <plassy@web.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KOOPTIMIZEDCOMPOSITEOPOVER32_H_
#define KOOPTIMIZEDCOMPOSITEOPOVER32_H_

#include "KoCompositeOpFunctions.h"
#include "KoCompositeOpBase.h"

#include "KoStreamedMath.h"


template<typename channels_type, typename pixel_type, bool alphaLocked, bool allChannelsFlag>
struct OverCompositor32 {
    // \see docs in AlphaDarkenCompositor32

#ifdef HAVE_VC

    template<bool haveMask, bool src_aligned>
    static ALWAYS_INLINE void compositeVector(const quint8 *src, quint8 *dst, const quint8 *mask, float opacity, float flow)
    {
        Q_UNUSED(flow);

        Vc::float_v src_alpha;
        Vc::float_v dst_alpha;

        src_alpha = KoStreamedMath::fetch_alpha_32<src_aligned>(src);

        bool haveOpacity = opacity != 1.0;
        Vc::float_v opacity_norm_vec(opacity);

        Vc::float_v uint8Max((float)255.0);
        Vc::float_v uint8MaxRec1((float)1.0 / 255.0);
        Vc::float_v zeroValue(Vc::Zero);
        Vc::float_v oneValue(Vc::One);

        src_alpha *= opacity_norm_vec;

        if (haveMask) {
            Vc::float_v mask_vec = KoStreamedMath::fetch_mask_8(mask);
            src_alpha *= mask_vec * uint8MaxRec1;
        }

        // The source cannot change the colors in the destination,
        // since its fully transparent
        if ((src_alpha == zeroValue).isFull()) {
            return;
        }

        dst_alpha = KoStreamedMath::fetch_alpha_32<true>(dst);

        Vc::float_v src_c1;
        Vc::float_v src_c2;
        Vc::float_v src_c3;

        Vc::float_v dst_c1;
        Vc::float_v dst_c2;
        Vc::float_v dst_c3;


        KoStreamedMath::fetch_colors_32<src_aligned>(src, src_c1, src_c2, src_c3);
        Vc::float_v src_blend;
        Vc::float_v new_alpha;

        if ((dst_alpha == uint8Max).isFull()) {
            new_alpha = dst_alpha;
            src_blend = src_alpha * uint8MaxRec1;
        } else if ((dst_alpha == zeroValue).isFull()) {
            new_alpha = src_alpha;
            src_blend = oneValue;
        } else {
            /**
             * The value of new_alpha can have *some* zero values,
             * which will result in NaN values while division. But
             * when converted to integers these NaN values will
             * be converted to zeroes, which is exactly what we need
             */
            new_alpha = dst_alpha + (uint8Max - dst_alpha) * src_alpha * uint8MaxRec1;
            src_blend = src_alpha / new_alpha;
        }

        if (!(src_blend == oneValue).isFull()) {
            KoStreamedMath::fetch_colors_32<true>(dst, dst_c1, dst_c2, dst_c3);

            dst_c1 = src_blend * (src_c1 - dst_c1) + dst_c1;
            dst_c2 = src_blend * (src_c2 - dst_c2) + dst_c2;
            dst_c3 = src_blend * (src_c3 - dst_c3) + dst_c3;

        } else {
            if (!haveMask && !haveOpacity) {
                memcpy(dst, src, 4 * Vc::float_v::Size);
                return;
            } else {
                // opacity has changed the alpha of the source,
                // so we can't just memcpy the bytes
                dst_c1 = src_c1;
                dst_c2 = src_c2;
                dst_c3 = src_c3;
            }
        }

        KoStreamedMath::write_channels_32(dst, new_alpha, dst_c1, dst_c2, dst_c3);
    }

#endif /* HAVE_VC */

    template <bool haveMask>
    static ALWAYS_INLINE void compositeOnePixelFloat(const channels_type *src, channels_type *dst, const quint8 *mask, float opacity, float flow, const QBitArray &channelFlags)
    {
        using namespace Arithmetic;
        const qint32 alpha_pos = 3;

        const float uint8Rec1 = 1.0 / 255.0;
        const float uint8Max = 255.0;

        float srcAlpha = src[alpha_pos];
        srcAlpha *= opacity;

        if (haveMask) {
            srcAlpha *= float(*mask) * uint8Rec1;
        }

        if (srcAlpha != 0.0) {

            float dstAlpha = dst[alpha_pos];
            float srcBlendNorm;

            if (dstAlpha == uint8Max) {
                srcBlendNorm = srcAlpha * uint8Rec1;
            } else {
                dstAlpha += (uint8Max - dstAlpha) * srcAlpha * uint8Rec1;

                if (dstAlpha != 0.0) {
                    srcBlendNorm = srcAlpha / dstAlpha;
                } else {
                    srcBlendNorm = 0.0;
                }
            }

            if(allChannelsFlag) {
                if (srcBlendNorm == 1.0) {
                    const pixel_type *s = reinterpret_cast<const pixel_type*>(src);
                    pixel_type *d = reinterpret_cast<pixel_type*>(dst);
                    *d = *s;
                } else if (srcBlendNorm != 0.0){
                    dst[0] = KoStreamedMath::lerp_mixed_u8_float(dst[0], src[0], srcBlendNorm);
                    dst[1] = KoStreamedMath::lerp_mixed_u8_float(dst[1], src[1], srcBlendNorm);
                    dst[2] = KoStreamedMath::lerp_mixed_u8_float(dst[2], src[2], srcBlendNorm);
                }
            } else {
                if (srcBlendNorm == 1.0) {
                    if(channelFlags.at(0)) dst[0] = src[0];
                    if(channelFlags.at(1)) dst[1] = src[1];
                    if(channelFlags.at(2)) dst[2] = src[2];
                } else if (srcBlendNorm != 0.0) {
                    if(channelFlags.at(0)) dst[0] = KoStreamedMath::lerp_mixed_u8_float(dst[0], src[0], srcBlendNorm);
                    if(channelFlags.at(1)) dst[1] = KoStreamedMath::lerp_mixed_u8_float(dst[1], src[1], srcBlendNorm);
                    if(channelFlags.at(2)) dst[2] = KoStreamedMath::lerp_mixed_u8_float(dst[2], src[2], srcBlendNorm);
                }
            }

            if (!alphaLocked) {
                dst[alpha_pos] = quint8(dstAlpha);
            }
        }

    }

    template <bool haveMask>
    static ALWAYS_INLINE void compositeOnePixel(const channels_type *src, channels_type *dst, const quint8 *mask, channels_type opacity, channels_type flow, const QBitArray &channelFlags)
    {
        using namespace Arithmetic;
        const qint32 alpha_pos = 3;

        channels_type srcAlpha = src[alpha_pos];

        if (haveMask) {
            srcAlpha = mul(scale<channels_type>(*mask), srcAlpha, opacity);
        } else if (opacity != unitValue<channels_type>()) {
            srcAlpha = mul(srcAlpha, opacity);
        }

        if (srcAlpha != zeroValue<channels_type>()) {

            channels_type dstAlpha = dst[alpha_pos];
            channels_type srcBlend;

            if (dstAlpha == unitValue<channels_type>()) {
                srcBlend = srcAlpha;
            } else {
                dstAlpha += mul(channels_type(unitValue<channels_type>() - dstAlpha), srcAlpha);

                if (dstAlpha != zeroValue<channels_type>()) {
                    srcBlend = div<channels_type>(srcAlpha, dstAlpha);
                } else {
                    srcBlend = zeroValue<channels_type>();
                }
            }

            if(allChannelsFlag) {
                if (srcBlend == unitValue<channels_type>()) {
                    const pixel_type *s = reinterpret_cast<const pixel_type*>(src);
                    pixel_type *d = reinterpret_cast<pixel_type*>(dst);
                    *d = *s;
                } else if (srcBlend != zeroValue<channels_type>()) {
                    dst[0] = lerp(dst[0], src[0], srcBlend);
                    dst[1] = lerp(dst[1], src[1], srcBlend);
                    dst[2] = lerp(dst[2], src[2], srcBlend);

                }
            } else {
                if (srcBlend == unitValue<channels_type>()) {
                    if(channelFlags.at(0)) dst[0] = src[0];
                    if(channelFlags.at(1)) dst[1] = src[1];
                    if(channelFlags.at(2)) dst[2] = src[2];
                } else if (srcBlend != zeroValue<channels_type>()) {
                    if(channelFlags.at(0)) dst[0] = lerp(dst[0], src[0], srcBlend);
                    if(channelFlags.at(1)) dst[1] = lerp(dst[1], src[1], srcBlend);
                    if(channelFlags.at(2)) dst[2] = lerp(dst[2], src[2], srcBlend);
                }
            }

            if (!alphaLocked) {
                dst[alpha_pos] = dstAlpha;
            }
        }

    }
};

/**
 * An optimized version of a composite op for the use in 4 byte
 * colorspaces with alpha channel placed at the last byte of
 * the pixel: C1_C2_C3_A.
 */
class KoOptimizedCompositeOpOver32 : public KoCompositeOp
{
public:
    KoOptimizedCompositeOpOver32(const KoColorSpace* cs)
        : KoCompositeOp(cs, COMPOSITE_OVER, i18n("Normal"), KoCompositeOp::categoryMix()) {}

    using KoCompositeOp::composite;

    virtual void composite(const KoCompositeOp::ParameterInfo& params) const
    {
        if(params.maskRowStart) {
            composite<true>(params);
        } else {
            composite<false>(params);
        }
    }

    template <bool haveMask>
    inline void composite(const KoCompositeOp::ParameterInfo& params) const {
        if (params.channelFlags.isEmpty() ||
            params.channelFlags == QBitArray(4, true)) {

            KoStreamedMath::genericComposite32<haveMask, false, OverCompositor32<quint8, quint32, false, true> >(params);
        } else {
            const bool allChannelsFlag =
                params.channelFlags.at(0) &&
                params.channelFlags.at(1) &&
                params.channelFlags.at(2);

            const bool alphaLocked =
                !params.channelFlags.at(3);

            if (allChannelsFlag && alphaLocked) {
                KoStreamedMath::genericComposite32_novector<haveMask, false, OverCompositor32<quint8, quint32, true, true> >(params);
            } else if (!allChannelsFlag && !alphaLocked) {
                KoStreamedMath::genericComposite32_novector<haveMask, false, OverCompositor32<quint8, quint32, false, true> >(params);
            } else /*if (!allChannelsFlag && alphaLocked) */{
                KoStreamedMath::genericComposite32_novector<haveMask, false, OverCompositor32<quint8, quint32, true, false> >(params);
            }
        }
    }
};

#endif // KOOPTIMIZEDCOMPOSITEOPOVER32_H_
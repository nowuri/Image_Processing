#include "pch.h"
#include "CDib.h"
#include "DibEnhancement.h"
#include "RGBBYTE.h"

void DibHistogram(CDib& dib, float histo[3][256])
{
	register int i, j;
	int w = dib.GetWidth();
	int h = dib.GetHeight();
	// 히스토그램 계산
	int temp[3][256];

	memset(temp, 0, sizeof(int) * 256*3);

	if (dib.GetBitCount() == 8) {
		BYTE** ptr = dib.GetPtr();
		for (j = 0; j < h; j++)
			for (i = 0; i < w; i++)
			{
				temp[0][ptr[j][i]]++;
			}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptrrgb = dib.GetRGBPtr();

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				temp[0][ptrrgb[j][i].r]++;
				temp[1][ptrrgb[j][i].g]++;
				temp[2][ptrrgb[j][i].b]++;
			}
		}
	}
	// 히스토그램 정규화(histogram normalization)
	float area = (float)w * h;
	for (i = 0; i < 256; i++) {
		histo[0][i] = temp[0][i] / area;
		histo[1][i] = temp[1][i] / area;
		histo[2][i] = temp[2][i] / area;
	}
}

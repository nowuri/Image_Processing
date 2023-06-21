#include "pch.h"
#include "CDib.h"
#include "DibEnhancement.h"

void DibHistogram(CDib& dib, float histo[256])
{
	register int i, j;
	int w = dib.GetWidth();
	int h = dib.GetHeight();
	// 히스토그램 계산
	int temp[256];
	memset(temp, 0, sizeof(int) * 256);
	if (dib.GetBitCount() == 8) {
		BYTE** ptr = dib.GetPtr();
		for (j = 0; j < h; j++)
			for (i = 0; i < w; i++)
			{
				temp[ptr[j][i]]++;
			}
	}
	else if (dib.GetBitCount() == 8) {
	}
	// 히스토그램 정규화(histogram normalization)
	float area = (float)w * h;
	for (i = 0; i < 256; i++)
		histo[i] = temp[i] / area;
}

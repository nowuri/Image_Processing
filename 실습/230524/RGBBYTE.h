#pragma once
#include <wtypes.h>
class RGBBYTE
{
	//-----------------------------------------------------------------------------
	// ��� ���� ����
	//-----------------------------------------------------------------------------
public:
	BYTE b;
	BYTE g;
	BYTE r;

	//-----------------------------------------------------------------------------
	// ��� �Լ� ����
	//-----------------------------------------------------------------------------

public:
	RGBBYTE(const BYTE& pixel = 0);     // �⺻ ������
	RGBBYTE(const BYTE& _r, const BYTE& _g, const BYTE& _b);
	RGBBYTE(const RGBBYTE& pixel);      // ���� ������
	~RGBBYTE();							// �Ҹ���

public:
	// ġȯ ������ �����ε�
	RGBBYTE& operator=(const RGBBYTE& pixel);
	RGBBYTE& operator=(const COLORREF& pixel);
	RGBBYTE& operator=(const BYTE& pixel);

	// ���� ������ �����ε�
	int         operator==(const RGBBYTE& pixel);
	int         operator!=(const RGBBYTE& pixel);
};


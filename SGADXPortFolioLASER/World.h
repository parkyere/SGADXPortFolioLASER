#pragma once

struct World
{
	D3DXVECTOR2 translation;
	D3DXVECTOR2 size;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	D3DXVECTOR2 center;

	D3DXVECTOR2 minBox;
	D3DXVECTOR2 maxBox;

	D3DXMATRIX matWorld;

	World()
	{
		translation = center = minBox = maxBox = { 0.0f, 0.0f };
		scale = size = { 1.0f, 1.0f };
		rotation = { 0.0f, 0.0f, 0.0f };
		D3DXMatrixIdentity(&matWorld);
	}

	static D3DXMATRIX GetSRT(D3DXVECTOR2* scale,
		D3DXVECTOR3* rotation, D3DXVECTOR2* translation,
		D3DXVECTOR2* center)
	{
		D3DXMATRIX* C = NULL;
		D3DXMATRIX* IC = NULL;
		if (center != NULL)
		{
			C = new D3DXMATRIX;
			IC = new D3DXMATRIX;

			D3DXMatrixTranslation(C, center->x, center->y, 0.0f);
			D3DXMatrixInverse(IC, NULL, C);
		}

		D3DXMATRIX S;
		D3DXMatrixIdentity(&S);

		if (scale != NULL)
		{
			if (IC != NULL)
				S = *IC;

			D3DXMATRIX matScale;
			D3DXMatrixScaling(&matScale, scale->x, scale->y, 1.0f);
			S *= matScale;

			if (C != NULL)
				S *= *C;
		}

		D3DXMATRIX R;
		D3DXMatrixIdentity(&R);

		if (rotation != NULL)
		{
			if (IC != NULL)
				R = *IC;
			D3DXVECTOR3 radian = *rotation * D3DX_PI / 180.0f;

			D3DXMATRIX matRot;
			D3DXMatrixRotationYawPitchRoll(&matRot,
				radian.y, radian.x, radian.z);
			R *= matRot;
			if (C != NULL)
				R *= *C;
		}

		D3DXMATRIX T;
		D3DXMatrixIdentity(&T);

		if (translation != NULL)
		{
			D3DXMatrixTranslation(&T, translation->x,
				translation->y, 0.0f);
		}

		SAFE_DELETE(C);
		SAFE_DELETE(IC);
		return S * R * T;
	}

	void Update()
	{
		minBox = translation;
		maxBox.x = minBox.x + scale.x * size.x;
		maxBox.y = minBox.y + scale.y * size.y;

		center = size * 0.5f;

		matWorld = GetSRT(&scale, &rotation, &translation,
			&center);
	}
};
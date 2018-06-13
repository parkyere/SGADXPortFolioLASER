#include "stdafx.h"

LPDIRECT3DVERTEXBUFFER9 Texture::vertexBuffer = NULL;
DWORD Texture::Vertex::fvf = D3DFVF_XYZ | D3DFVF_TEX1;
vector< shared_ptr<Texture> > Texture::textures;
map<wstring, LPDIRECT3DTEXTURE9> Texture::textureMap;

bool Texture::isDrawBoundBox = false;
LPDIRECT3DVERTEXBUFFER9 Texture::boundVertexBuffer = NULL;
DWORD Texture::BoundVertex::fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

void Texture::CreateVertexBuffer()
{
	SAFE_RELEASE(vertexBuffer);

	UINT vertexCount = textures.size() * 6;
	UINT vertexSize = vertexCount * sizeof(Vertex);

	HRESULT result;
	result = DEVICE->CreateVertexBuffer(vertexSize,
		0, Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	assert(SUCCEEDED(result));

	Vertex* vertex = new Vertex[vertexCount];
	for (size_t i = 0; i < textures.size(); i++)
	{
		D3DXVECTOR2 size;
		textures[i]->GetRealSize(&size);

		D3DXVECTOR2 start = textures[i]->start;
		D3DXVECTOR2 end = textures[i]->end;

		vertex[i * 6 + 0] = Vertex(0, size.y, start.x, end.y);
		vertex[i * 6 + 1] = Vertex(0, 0, start.x, start.y);
		vertex[i * 6 + 2] = Vertex(size.x, size.y, end.x, end.y);
		vertex[i * 6 + 3] = Vertex(size.x, size.y, end.x, end.y);
		vertex[i * 6 + 4] = Vertex(0, 0, start.x, start.y);
		vertex[i * 6 + 5] = Vertex(size.x, 0, end.x, start.y);
	}

	void* vertexData = NULL;
	result = vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	assert(SUCCEEDED(result));
	memcpy(vertexData, vertex, vertexSize);
	result = vertexBuffer->Unlock();
	assert(SUCCEEDED(result));

	SAFE_DELETE_ARRAY(vertex);
}

void Texture::CreateBoundVertexBuffer()
{
	SAFE_RELEASE(boundVertexBuffer);

	UINT vertexCount = textures.size() * 5;
	UINT vertexSize = vertexCount * sizeof(BoundVertex);

	HRESULT result;
	result = DEVICE->CreateVertexBuffer(vertexSize,
		0, BoundVertex::fvf, D3DPOOL_DEFAULT,
		&boundVertexBuffer, NULL);
	assert(SUCCEEDED(result));

	BoundVertex* vertex = new BoundVertex[vertexCount];
	for (size_t i = 0; i < textures.size(); i++)
	{
		D3DXVECTOR2 size;
		textures[i]->GetRealSize(&size);

		vertex[i * 5 + 0] = BoundVertex(0, 0, COLOR_G);
		vertex[i * 5 + 1] = BoundVertex(size.x, 0, COLOR_G);
		vertex[i * 5 + 2] = BoundVertex(size.x, size.y, COLOR_G);
		vertex[i * 5 + 3] = BoundVertex(0, size.y, COLOR_G);
		vertex[i * 5 + 4] = BoundVertex(0, 0, COLOR_G);
	}

	void* vertexData = NULL;
	result = boundVertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	assert(SUCCEEDED(result));
	memcpy(vertexData, vertex, vertexSize);
	result = boundVertexBuffer->Unlock();
	assert(SUCCEEDED(result));

	SAFE_DELETE_ARRAY(vertex);
}

Texture::Texture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd)
{
	this->texture = texture;
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	textureFormat = desc.Format;

	textureSize.x = (float)desc.Width;
	textureSize.y = (float)desc.Height;

	start.x = (cutStart.x > 0) ? cutStart.x / textureSize.x : 0.0f;
	start.y = (cutStart.y > 0) ? cutStart.y / textureSize.y : 0.0f;
	end.x = (cutEnd.x > 0) ? cutEnd.x / textureSize.x : 1.0f;
	end.y = (cutEnd.y > 0) ? cutEnd.y / textureSize.y : 1.0f;

	this->cutStart = cutStart;

	this->cutEnd.x = (cutEnd.x < 1) ? textureSize.x : cutEnd.x;
	this->cutEnd.y = (cutEnd.y < 1) ? textureSize.y : cutEnd.y;
}

Texture::~Texture()
{
}

shared_ptr<Texture> Texture::Add(wstring fileName, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd)
{
	LPDIRECT3DTEXTURE9 dxTexture;
	if (textureMap.count(fileName) < 1)
	{
		D3DXIMAGE_INFO textureInfo;
		D3DXCreateTextureFromFileEx(DEVICE,
			fileName.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			0xffff00ff,
			&textureInfo,
			NULL,
			&dxTexture);
		textureMap.insert({ fileName, dxTexture });
	}

	dxTexture = textureMap[fileName];

	shared_ptr<Texture> myTexture = make_shared<Texture>( dxTexture, cutStart, cutEnd );
	myTexture->number = textures.size();
	textures.push_back(myTexture);

	CreateVertexBuffer();
	CreateBoundVertexBuffer();

	return myTexture;
}

shared_ptr<Texture> Texture::Add(wstring fileName, int frameX, int frameY, int maxFrameX, int maxFrameY)
{
	LPDIRECT3DTEXTURE9 dxTexture;

	if (textureMap.count(fileName) < 1)
	{
		D3DXIMAGE_INFO textureInfo;
		D3DXCreateTextureFromFileEx(DEVICE,
			fileName.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			0,
			&textureInfo,
			NULL,
			&dxTexture);
		textureMap.insert({ fileName, dxTexture });
	}
	dxTexture = textureMap[fileName];

	D3DSURFACE_DESC desc;
	dxTexture->GetLevelDesc(0, &desc);

	D3DXVECTOR2 cutStart;
	cutStart.x = desc.Width * frameX / maxFrameX;
	cutStart.y = desc.Height * frameY / maxFrameY;
	D3DXVECTOR2 cutEnd;
	cutEnd.x = desc.Width * (frameX + 1) / maxFrameX;
	cutEnd.y = desc.Height * (frameY + 1) / maxFrameY;

	shared_ptr<Texture> myTexture = make_shared<Texture>(dxTexture, cutStart, cutEnd);
	myTexture->number = textures.size();
	textures.push_back(myTexture);

	CreateVertexBuffer();
	CreateBoundVertexBuffer();

	return myTexture;
}

void Texture::Delete()
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i].reset();
	}
	auto iter = textureMap.begin();
	for (; iter != textureMap.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
	}
	SAFE_RELEASE(vertexBuffer);
}

void Texture::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, number * 6, 2);

	if (isDrawBoundBox)
	{
		DEVICE->SetTexture(0, NULL);
		DEVICE->SetStreamSource(0, boundVertexBuffer,
			0, sizeof(BoundVertex));
		DEVICE->SetFVF(BoundVertex::fvf);
		DEVICE->DrawPrimitive(D3DPT_LINESTRIP, number * 5, 4);
	}
}

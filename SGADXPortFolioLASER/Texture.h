#pragma once

class Texture
{
private:
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;

		Vertex() {}
		Vertex(float x, float y, float u, float v)
		{
			position = { x, y, 0.0f };
			uv = { u, v };
		}

		static DWORD fvf;
	};

	UINT number;
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR2 textureSize;
	D3DFORMAT textureFormat;

	D3DXVECTOR2 cutStart;
	D3DXVECTOR2 cutEnd;
	D3DXVECTOR2 start;
	D3DXVECTOR2 end;
	D3DXVECTOR2 boundSize;

	static bool isDrawBoundBox;
	struct BoundVertex
	{
		D3DXVECTOR3 position;
		DWORD color;

		static DWORD fvf;

		BoundVertex() {}
		BoundVertex(float x, float y, DWORD color)
		{
			position = { x, y, 0.0f };
			this->color = color;
		}
	};

	static LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	static LPDIRECT3DVERTEXBUFFER9 boundVertexBuffer;

	static vector<shared_ptr<Texture> > textures;
	static map<wstring, LPDIRECT3DTEXTURE9> textureMap;

	static void CreateVertexBuffer();
	static void CreateBoundVertexBuffer();


public:
	Texture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd);
	~Texture();
	static shared_ptr<Texture> Add(wstring fileName,
		D3DXVECTOR2 cutStart = D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2 cutEnd = D3DXVECTOR2(0.0f, 0.0f));
	static shared_ptr<Texture> Add(wstring fileName,
		int frameX, int frameY,
		int maxFrameX, int maxFrameY);

	static void Delete();
	void Render();

	void GetTextureSize(D3DXVECTOR2* size) const
	{
		*size = this->textureSize;
	}

	void GetRealSize(D3DXVECTOR2* size) const
	{
		*size = cutEnd - cutStart;
	}

	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
};
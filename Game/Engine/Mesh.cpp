#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(const vector<Vertex>& vec, const vector<uint32>& indexbuffer)
{
	CreateVertexBuffer(vec);
	CreateIndexBuffer(indexbuffer);
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)
	CMD_LIST->IASetIndexBuffer(&_indexBufferView);

	// TODO
	// 1) Buffer에다가 데이터 세팅 - 위 Init에 CreateCommittedResource 관련 부분
	// 2-1) Buffer의 주소를 register에다가 전송(Old)
	// OR
	// 2-2) TableDescHeap에다가 CBV전달(New)
	// 3) 모두 세팅이 끝났으면 TableDescHeap 커밋
	// 커맨드리스트에 적립되고 수행됨으로 즉시 발동되는게 아님
	// 그에 따른 커맨드리스트 수행 중 버퍼값 변경에 주의해야함

	//GEngine->GetCB()->PushData(0, &_transform, sizeof(_transform));
	//GEngine->GetCB()->PushData(1, &_transform, sizeof(_transform));
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetCB()->PushData(0, &_transform, sizeof(_transform));
		GEngine->GetTableDescHeap()->SetCBV(handle, CBV_REGISTER::b0);
	}
	/*{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetCB()->PushData(0, &_transform, sizeof(_transform));
		GEngine->GetTableDescHeap()->SetCBV(handle, CBV_REGISTER::b1);
	}*/
	GEngine->GetTableDescHeap()->CommitTable();
	
	//CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0); // Vertex로만 그리는 함수
	CMD_LIST->DrawIndexedInstanced(_indexCount, 1, 0, 0, 0);
}

void Mesh::CreateVertexBuffer(const vector<Vertex>& buffer)
{
	_vertexCount = static_cast<uint32>(buffer.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer)); // _vertexBuffer -> 데이터는 GPU에 있음

	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &buffer[0], bufferSize); // GPU 메모리에 복사
	_vertexBuffer->Unmap(0, nullptr);

	// Initialize the vertex buffer view.
	// GPU 메모리 접근이 닫혔으므로 View로 데이터 확인
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
	_vertexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기
}

void Mesh::CreateIndexBuffer(const vector<uint32>& buffer)
{
	_indexCount = static_cast<uint32>(buffer.size());
	uint32 bufferSize = _indexCount * sizeof(uint32);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_indexBuffer)); // _vertexBuffer -> 데이터는 GPU에 있음

	// Copy the triangle data to the vertex buffer.
	void* indexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_indexBuffer->Map(0, &readRange, &indexDataBuffer);
	::memcpy(indexDataBuffer, &buffer[0], bufferSize); // GPU 메모리에 복사
	_indexBuffer->Unmap(0, nullptr);

	// Initialize the vertex buffer view.
	// GPU 메모리 접근이 닫혔으므로 View로 데이터 확인
	_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
	_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	_indexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기
}

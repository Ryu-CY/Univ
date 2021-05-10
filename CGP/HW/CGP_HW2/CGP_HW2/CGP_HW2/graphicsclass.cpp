////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	m_Model4 = 0;
	m_TextureShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}
	m_Model3 = new ModelClass;
	if (!m_Model3)
	{
		return false;
	}
	m_Model4 = new ModelClass;
	if (!m_Model4)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../CGP_HW2/data/chair.obj", L"../CGP_HW2/data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model2->Initialize(m_D3D->GetDevice(), "../CGP_HW2/data/chair_1.obj", L"../CGP_HW2/data/chair_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model3->Initialize(m_D3D->GetDevice(), "../CGP_HW2/data/table.obj", L"../CGP_HW2/data/Table.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Model4->Initialize(m_D3D->GetDevice(), "../CGP_HW2/data/floor.obj", L"../CGP_HW2/data/Tile1.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}
	if (m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}
	if (m_Model4)
	{
		m_Model4->Shutdown();
		delete m_Model4;
		m_Model4 = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, worldMatrix2, worldMatrix3, worldMatrix4, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetWorldMatrix(worldMatrix2);
	m_D3D->GetWorldMatrix(worldMatrix3);
	m_D3D->GetWorldMatrix(worldMatrix4);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixRotationY(&worldMatrix2, rotation * 5.0f);
	D3DXMatrixRotationY(&worldMatrix3, rotation * 10.0f);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture());
	if (!result)
	{
		return false;
	}

	m_Model2->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix2, viewMatrix, projectionMatrix,
		m_Model2->GetTexture());
	if (!result)
	{
		return false;
	}

	m_Model3->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix3, viewMatrix, projectionMatrix,
		m_Model3->GetTexture());
	if (!result)
	{
		return false;
	}

	m_Model4->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix4, viewMatrix, projectionMatrix,
		m_Model4->GetTexture());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

D3DClass* GraphicsClass::GetD3D()
{
	return m_D3D;
}
TextureShaderClass* GraphicsClass::GetTextureShader()
{
	return m_TextureShader;
}
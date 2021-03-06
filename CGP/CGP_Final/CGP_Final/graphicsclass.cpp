////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Card = 0;

	for (int i = 0; i < 3; i++)
		m_Fire[i] = 0;
	for (int i = 0; i < 3; i++)
		m_Map[i] = 0;
	for (int i = 0; i < 2; i++)
		m_Door[i] = 0;

	mapNum = 0;
	inCorridor = 0;
	blink = 0;

	getCard = false;
	turnOnLight = false;
	isInteractDoor = false;
	isInteractEscape = false;
	isInteractElec = false;

	gameClear = false;

	num_of_polygons = 0;
	num_of_objects = 0;

	camRotX = 0.0f;
	camRotY = 45.0f;
	camRotZ = -10.0f;

	m_TextureShader = 0;
	m_Bitmap = 0;

	m_Text = 0;

	m_SkyDome = 0;
	m_SkyDomeShader = 0;

	m_FireShader = 0;
	m_Electric = 0;
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

	D3DXMATRIX baseViewMatrix;

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
	m_Camera->SetLookAt(0.0f, 0.0f, 0.1f);

	// Create the model[CardKey] object.
	m_Card = new ModelClass;
	if (!m_Card)
	{
		return false;
	}

	// Initialize the model[CardKey] object.	
	result = m_Card->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/KeyCard/Chip_key_2/Material/key.obj", L"../CGP_Final/data/KeyCard/Chip_key_2/Texturizer/metal_1.jpg",
		L"../CGP_Final/data/stars.jpg", L"../CGP_Final/data/KeyCard/Chip_key_2/Texturizer/Blury.jpg",
		L"../CGP_Final/data/KeyCard/Chip_key_2/Texturizer/Lake.jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	for (int i = 0; i < 3; i++)
	{
		m_Fire[i] = new FireClass;
		if (!m_Fire[i])
		{
			return false;
		}

		result = m_Fire[i]->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/square.txt", L"../CGP_Final/data/fire01.dds",
			L"../CGP_Final/data/noise01.dds", L"../CGP_Final/data/alpha01.dds");

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the Fire model object.", L"Error", MB_OK);
			return false;
		}
	}

	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	result = m_FireShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the model[Map1] object.
	m_Map[0] = new ModelClass;
	if (!m_Map[0])
	{
		return false;
	}

	// Initialize the model[Map1] object.
	result = m_Map[0]->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/Map/map_01.obj", L"../CGP_Final/data/Map/map11.jpg", L"../CGP_Final/data/Map/map12.jpg", L"../CGP_Final/data/Map/map13.jpg", L"../CGP_Final/data/Map/map14.jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model[Map2] object.
	m_Map[1] = new ModelClass;
	if (!m_Map[1])
	{
		return false;
	}

	// Initialize the model[Map2] object.
	result = m_Map[1]->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/Map/map2.obj", L"../CGP_Final/data/Map/map21.jpg", L"../CGP_Final/data/Map/map22.jpg", L"../CGP_Final/data/Map/map23.jpg", L"../CGP_Final/data/Map/map23.jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}

	// Create the model[Map3] object.
	m_Map[2] = new ModelClass;
	if (!m_Map[2])
	{
		return false;
	}

	// Initialize the model[Map3] object.
	result = m_Map[2]->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/Map/map3.obj", L"../CGP_Final/data/Map/map31.jpg", L"../CGP_Final/data/Map/map32.jpg", L"../CGP_Final/data/Map/map33.jpg", L"../CGP_Final/data/Map/map34.jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}


	for (int i = 0; i < 2; i++)
	{
		m_Door[i] = new ModelClass;
		if (!m_Door[i])
		{
			return false;
		}
		result = m_Door[i]->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/Map/door.obj", L"../CGP_Final/data/Map/map21.jpg", L"../CGP_Final/data/Map/map22.jpg", L"../CGP_Final/data/Map/map23.jpg", L"../CGP_Final/data/Map/map23.jpg");
	}

	m_Electric = new ModelClass;
	if (!m_Electric)
	{
		return false;
	}

	// Initialize the model[Map3] object.
	result = m_Electric->Initialize(m_D3D->GetDevice(), "../CGP_Final/data/Electric/asd.obj", L"../CGP_Final/data/Electric/quadro de energia (Bump).jpg", L"../CGP_Final/data/Electric/quadro de energia (Bump).jpg", L"../CGP_Final/data/Electric/quadro de energia (Bump).jpg", L"../CGP_Final/data/Electric/quadro de energia (Bump).jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the door object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.075f, 0.075f, 0.075f, 1.0f);
	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDirection(0.0f, -0.5f, 0.5f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(100.0f);

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


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../CGP_Final/data/seafloor.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the card object.
	if (m_Card)
	{
		m_Card->Shutdown();
		delete m_Card;
		m_Card = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_Fire[i])
		{
			m_Fire[i]->Shutdown();
			delete m_Fire[i];
			m_Fire[i] = 0;
		}
	}

	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	// Release the map object.
	for (int i = 0; i < 3; i++)
	{
		if (m_Map[i])
		{
			m_Map[i]->Shutdown();
			delete m_Map[i];
			m_Map[i] = 0;
		}
	}

	// Release the door object.
	for (int i = 0; i < 2; i++)
	{
		if (m_Door[i])
		{
			m_Door[i]->Shutdown();
			delete m_Door[i];
			m_Door[i] = 0;
		}
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

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	if (m_Electric)
	{
		m_Electric->Shutdown();
		delete m_Electric;
		m_Electric = 0;
	}

	return;
}


bool GraphicsClass::Frame(int mouseX, int mouseY, int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	if (turnOnLight)
	{
		blink += 1;
		m_Light->Blink(m_Light, blink);
		if (blink > 120)
			blink = 0;
	}

	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetNumOfObject(num_of_objects, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetNumOfPolygons(num_of_polygons, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetNeedCard(getCard, isInteractEscape, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetLocked(1, isInteractDoor, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreen(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetIsClear(gameClear, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	camRotX += m_Camera->GetMoveZ() * 1.5f * sin(m_Camera->GetRotY());
	camRotX += m_Camera->GetMoveX() * 1.5f * cos(m_Camera->GetRotY());

	camRotZ += m_Camera->GetMoveZ() * 1.5f * cos(m_Camera->GetRotY());
	camRotZ += m_Camera->GetMoveX() * 1.5f * -sin(m_Camera->GetRotY());

	if (mapNum == 0)
	{
		isInteractElec = false;
		if (inCorridor == 0)
		{
			isInteractEscape = false;
			isInteractDoor = false;
			if (m_Camera->GetPosition().x > 55.0f)
				camRotX -= 0.75f;
			else if (m_Camera->GetPosition().x < -55.0f)
				camRotX += 0.75f;
			if (m_Camera->GetPosition().z > 400.0f)
				camRotZ -= 0.75f;
			else if (m_Camera->GetPosition().z < -400.0f)
				camRotZ += 0.75f;

			if (m_Camera->GetPosition().x <= -55.0f &&
				(m_Camera->GetPosition().z < 235.0f && m_Camera->GetPosition().z > 115.0f))	// 475 -> 235, 175 -> 115
			{
				inCorridor = 1;
				camRotX -= 75.5f;
				camRotY += 55.0f;
			}
			else if (m_Camera->GetPosition().x >= 55.0f &&
				(m_Camera->GetPosition().z < 235.0f && m_Camera->GetPosition().z > 115.0f))
			{
				inCorridor = 2;
				camRotX += 75.5f;
				camRotY += 55.0f;
			}
			else if (m_Camera->GetPosition().x <= -55.0f &&
				(m_Camera->GetPosition().z > -235.0f && m_Camera->GetPosition().z < -115.0f))
			{
				inCorridor = 3;
				camRotX -= 75.5f;
				camRotY += 55.0f;
			}
			else if (m_Camera->GetPosition().x >= 55.0f &&
				(m_Camera->GetPosition().z > -235.0f && m_Camera->GetPosition().z < -115.0f))
			{
				inCorridor = 4;
				camRotX += 75.5f;
				camRotY += 55.0f;
			}

			if (m_Camera->GetPosition().z >= 400.0f &&
				(m_Camera->GetPosition().x > -35.0f && m_Camera->GetPosition().x < 35.0f))
				isInteractEscape = true;
			else if (m_Camera->GetPosition().z <= -400.0f &&
				(m_Camera->GetPosition().x > -35.0f && m_Camera->GetPosition().x < 35.0f))
				isInteractDoor = true;
		}
		else if (inCorridor == 1)
		{
			if (m_Camera->GetPosition().x > -130.0f)
			{
				inCorridor = 0;
				camRotX += 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x < -130.0f && m_Camera->GetPosition().x > -155.0f)
			{
				isInteractDoor = false;
				if (m_Camera->GetPosition().z > 225.0f)
				{
					camRotZ -= 0.75f;
				}
				else if (m_Camera->GetPosition().z < 125.0f)
				{
					camRotZ += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x < -155.0f)
			{
				isInteractDoor = true;
				camRotX += 0.75f;
			}

			/*if (m_Camera->GetPosition().z > 200.0f && m_Camera->GetPosition().z < 250.0f)
			{
				if (m_Camera->GetPosition().x < -170.0f)
				{
					camRotX += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().z > 350.0f && m_Camera->GetPosition().z < 400.0f)
			{
				if (m_Camera->GetPosition().x < -170.0f)
				{
					camRotX += 0.75f;
				}
			}*/
		}
		else if (inCorridor == 2)
		{
			if (m_Camera->GetPosition().x < 130.0f)
			{
				inCorridor = 0;
				camRotX -= 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x > 130.0f && m_Camera->GetPosition().x < 155.0f)
			{
				isInteractDoor = false;
				if (m_Camera->GetPosition().z > 225.0f)
				{
					camRotZ -= 0.75f;
				}
				else if (m_Camera->GetPosition().z < 125.0f)
				{
					camRotZ += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x > 155.0f)
			{
				isInteractDoor = true;
				camRotX -= 0.75f;
			}

			/*if (m_Camera->GetPosition().z > 200.0f && m_Camera->GetPosition().z < 250.0f)
			{
				if (m_Camera->GetPosition().x > 170.0f)
				{
					camRotX -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().z > 350.0f && m_Camera->GetPosition().z < 400.0f)
			{
				if (m_Camera->GetPosition().x > 170.0f)
				{
					camRotX -= 0.75f;
				}
			}*/
		}
		else if (inCorridor == 3)
		{
			if (m_Camera->GetPosition().x > -130.0f)
			{
				inCorridor = 0;
				camRotX += 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x < -130.0f && m_Camera->GetPosition().x > -175.0f)
			{
				if (m_Camera->GetPosition().z < -225.0f)
				{
					camRotZ += 0.75f;
				}
				else if (m_Camera->GetPosition().z > -125.0f)
				{
					camRotZ -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x < -175.0f && m_Camera->GetPosition().x > -200.0f)
			{
				if (m_Camera->GetPosition().z < -200.0f)
				{
					camRotZ += 0.75f;
				}
				else if (m_Camera->GetPosition().z > -150.0f)
				{
					camRotZ -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x < -200.0f)
			{
				mapNum = 1;
				inCorridor = 4;
			}

			if (m_Camera->GetPosition().z < -100.0f && m_Camera->GetPosition().z > -140.0f)
			{
				if (m_Camera->GetPosition().x < -165.0f)
				{
					camRotX += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().z < -210.0f && m_Camera->GetPosition().z > -240.0f)
			{
				if (m_Camera->GetPosition().x < -165.0f)
				{
					camRotX += 0.75f;
				}
			}
		}
		else if (inCorridor == 4)
		{
			if (m_Camera->GetPosition().x < 130.0f)
			{
				inCorridor = 0;
				camRotX -= 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x > 130.0f && m_Camera->GetPosition().x < 155.0f)
			{
				isInteractDoor = false;
				if (m_Camera->GetPosition().z < -225.0f)
				{
					camRotZ += 0.75f;
				}
				else if (m_Camera->GetPosition().z > -125.0f)
				{
					camRotZ -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x > 155.0f)
			{
				isInteractDoor = true;
				camRotX -= 0.75f;
			}
		}
	}
	else if (mapNum == 1)
	{
		if (inCorridor == 0)
		{
			isInteractDoor = false;
			isInteractElec = false;
			if (m_Camera->GetPosition().x > -335.0f)
				camRotX -= 0.75f;
			else if (m_Camera->GetPosition().x < -445.0f)
				camRotX += 0.75f;
			if (m_Camera->GetPosition().z > 400.0f)
				camRotZ -= 0.75f;
			else if (m_Camera->GetPosition().z < -400.0f)
				camRotZ += 0.75f;

			if (m_Camera->GetPosition().x <= -445.0f &&
				(m_Camera->GetPosition().z < 235.0f && m_Camera->GetPosition().z > 115.0f))	// 475 -> 235, 175 -> 115
			{
				inCorridor = 1;
				camRotX -= 75.5f;
				camRotY += 55.0f;
			}
			else if (m_Camera->GetPosition().x >= -335.0f &&
				(m_Camera->GetPosition().z < 235.0f && m_Camera->GetPosition().z > 115.0f))
			{
				inCorridor = 2;
				camRotX += 75.5f;
				camRotY += 55.0f;
			}
			else if (m_Camera->GetPosition().x <= -445.0f &&
				(m_Camera->GetPosition().z > -235.0f && m_Camera->GetPosition().z < -115.0f))
			{
				inCorridor = 3;
				camRotX -= 75.5f;
				camRotY += 55.0f;
			}
			else if (m_Camera->GetPosition().x >= -335.0f &&
				(m_Camera->GetPosition().z > -235.0f && m_Camera->GetPosition().z < -115.0f))
			{
				inCorridor = 4;
				camRotX += 75.5f;
				camRotY += 55.0f;
			}

			if (m_Camera->GetPosition().z >= 400.0f &&
				(m_Camera->GetPosition().x > -425.0f && m_Camera->GetPosition().x < -355.0f))
				isInteractDoor = true;
			else if (m_Camera->GetPosition().z <= -400.0f &&
				(m_Camera->GetPosition().x > -425.0f && m_Camera->GetPosition().x < -355.0f))
				isInteractDoor = true;
			else if (m_Camera->GetPosition().z <= -398.0f &&
				(m_Camera->GetPosition().x > -355.0f && m_Camera->GetPosition().x < -335.0f))
				isInteractElec = true;
		}
		else if (inCorridor == 1)
		{
			if (m_Camera->GetPosition().x > -520.0f)
			{
				inCorridor = 0;
				camRotX += 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x < -520.0f && m_Camera->GetPosition().x > -545.0f)
			{
				isInteractDoor = false;
				if (m_Camera->GetPosition().z > 225.0f)
				{
					camRotZ -= 0.75f;
				}
				else if (m_Camera->GetPosition().z < 125.0f)
				{
					camRotZ += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x < -545.0f)
			{
				isInteractDoor = true;
				camRotX += 0.75f;
			}

			/*if (m_Camera->GetPosition().z > 200.0f && m_Camera->GetPosition().z < 250.0f)
			{
				if (m_Camera->GetPosition().x < -170.0f)
				{
					camRotX += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().z > 350.0f && m_Camera->GetPosition().z < 400.0f)
			{
				if (m_Camera->GetPosition().x < -170.0f)
				{
					camRotX += 0.75f;
				}
			}*/
		}
		else if (inCorridor == 2)
		{
			if (m_Camera->GetPosition().x < -260.0f)
			{
				inCorridor = 0;
				camRotX -= 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x > -260.0f && m_Camera->GetPosition().x < -235.0f)
			{
				isInteractDoor = false;
				if (m_Camera->GetPosition().z > 225.0f)
				{
					camRotZ -= 0.75f;
				}
				else if (m_Camera->GetPosition().z < 125.0f)
				{
					camRotZ += 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x > -235.0f)
			{
				isInteractDoor = true;
				camRotX -= 0.75f;
			}

			/*if (m_Camera->GetPosition().z > 200.0f && m_Camera->GetPosition().z < 250.0f)
			{
				if (m_Camera->GetPosition().x > 170.0f)
				{
					camRotX -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().z > 350.0f && m_Camera->GetPosition().z < 400.0f)
			{
				if (m_Camera->GetPosition().x > 170.0f)
				{
					camRotX -= 0.75f;
				}
			}*/
		}
		else if (inCorridor == 3)
		{
			if (m_Camera->GetPosition().x > -520.00f)
			{
				inCorridor = 0;
				camRotX += 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x < -520.0f && m_Camera->GetPosition().x > -545.0f)
			{
				isInteractDoor = false;
				if (m_Camera->GetPosition().z < -225.0f)
				{
					camRotZ += 0.75f;
				}
				else if (m_Camera->GetPosition().z > -125.0f)
				{
					camRotZ -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x < -545.0f)
			{
				isInteractDoor = true;
				camRotX += 0.75f;
			}
		}
		else if (inCorridor == 4)
		{
			if (m_Camera->GetPosition().x < -260.0f)
			{
				inCorridor = 0;
				camRotX -= 75.5f;
				camRotY -= 55.0f;
			}
			else if (m_Camera->GetPosition().x > -260.0f && m_Camera->GetPosition().x < -225.0f)
			{
				if (m_Camera->GetPosition().z < -225.0f)
				{
					camRotZ += 0.75f;
				}
				else if (m_Camera->GetPosition().z > -125.0f)
				{
					camRotZ -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x > -215.0f && m_Camera->GetPosition().x < -200.0f)
			{
				if (m_Camera->GetPosition().z < -200.0f)
				{
					camRotZ += 0.75f;
				}
				else if (m_Camera->GetPosition().z > -150.0f)
				{
					camRotZ -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().x > -200.0f)
			{
				mapNum = 0;
				inCorridor = 3;
			}

			if (m_Camera->GetPosition().z < -100.0f && m_Camera->GetPosition().z > -140.0f)
			{
				if (m_Camera->GetPosition().x > -225.0f)
				{
					camRotX -= 0.75f;
				}
			}
			else if (m_Camera->GetPosition().z < -210.0f && m_Camera->GetPosition().z > -240.0f)
			{
				if (m_Camera->GetPosition().x > -225.0f)
				{
					camRotX -= 0.75f;
				}
			}
		}
	}

	if (!gameClear)
		m_Camera->SetPosition(camRotX, camRotY, camRotZ);
	else
	{
		m_Camera->SetPosition(0.0f, 45.0f, 275.0f);
		m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	}
		//-435.0f, 45.0f, 320.0f
	if ((m_Camera->GetPosition().x >= -436.0f && m_Camera->GetPosition().x <= -434.0f) &&
		(m_Camera->GetPosition().z >= 318.5f && m_Camera->GetPosition().z <= 321.5f))
		getCard = true;


	return true;
}

bool GraphicsClass::Render(float rotation)
{
	// worldMatrix[0-8] = CardKey, worldMatrix[9] = Map, worldMatrix[10] = Ui
	D3DXMATRIX worldMatrix[11], viewMatrix, projectionMatrix, projectionMatrix1, orthoMatrix;
	D3DXMATRIX doorMoveMatrix[10];
	D3DXMATRIX doorScalingMatrix;
	D3DXMATRIX doorMatrix[10];
	D3DXMATRIX doorRotateMatrix[3];
	D3DXMATRIX Map2MoveMatrix;
	D3DXMATRIX Map2Scaling;
	D3DXMATRIX Map2Matrix;
	D3DXMATRIX ElectricMatrix;
	D3DXMATRIX ElectricMoveMatrix;
	D3DXMATRIX ElectricScaling;
	bool result;

	D3DXVECTOR3 cameraPosition;

	D3DXMATRIX worldMatrixFire[3];
	D3DXMATRIX worldMatrixFireRot[3];
	D3DXMATRIX worldMatrixFireSca[3];
	D3DXMATRIX worldMatrixFireTrs[3];
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;


	num_of_objects = 0;
	num_of_polygons = 0;

	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	for (int i = 0; i < 11; i++)
		m_D3D->GetWorldMatrix(worldMatrix[i]);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix1);
	for (int i = 0; i < 10; i++)
		m_D3D->GetWorldMatrix(doorMoveMatrix[i]);
	m_D3D->GetWorldMatrix(Map2Matrix);
	m_D3D->GetWorldMatrix(ElectricMatrix);

	for (int i = 0; i < 3; i++)
		m_D3D->GetWorldMatrix(worldMatrixFire[i]);
	for (int i = 0; i < 3; i++)
		m_D3D->GetWorldMatrix(worldMatrixFireRot[i]);
	for (int i = 0; i < 3; i++)
		m_D3D->GetWorldMatrix(worldMatrixFireSca[i]);
	for (int i = 0; i < 3; i++)
		m_D3D->GetWorldMatrix(worldMatrixFireTrs[i]);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	//m_D3D->SetWorldMatrix(worldMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixTranslation(&worldMatrix[10], cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling.
	m_D3D->TurnOffCulling();

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix[10], viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Turn on back face culling.
	m_D3D->TurnOnCulling();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();


	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixScaling(&worldMatrix[1], 0.2f, 0.15f, 0.2f);
	D3DXMatrixTranslation(&worldMatrix[2], 0.8f, -0.5f, 3.5f);
	D3DXMatrixRotationX(&worldMatrix[3], lY * 0.03f * 0.0174532925f);
	D3DXMatrixRotationY(&worldMatrix[4], lX * 0.03f * 0.0174532925f);
	D3DXMatrixTranslation(&worldMatrix[5], m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

	D3DXMatrixScaling(&worldMatrix[6], 1.7f, 1.7f, 1.7f);
	D3DXMatrixRotationY(&worldMatrix[7], rotation);
	D3DXMatrixTranslation(&worldMatrix[8], -435.0f, 37.5f, 320.0f);

	//m_D3D->SetWorldMatrix(worldMatrix1);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// CardKey
	m_Card->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Card->GetIndexCount();

	// Render the model using the light shader.
	if (getCard)
		for (int i = 1; i < 6; i++)
			worldMatrix[0] *= worldMatrix[i];
	else
		for (int i = 6; i < 9; i++)
			worldMatrix[0] *= worldMatrix[i];

	if (!gameClear)
	{
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Card->GetIndexCount(), worldMatrix[0], viewMatrix, projectionMatrix,
			*m_Card->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}
	else
	{
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Card->GetIndexCount(), ElectricMatrix, viewMatrix, projectionMatrix,
			*m_Card->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}
	if (!result)
	{
		return false;
	}

	//???? ??????
	D3DXMatrixTranslation(&doorMoveMatrix[0], -600.0f, 260.0f, 585.0f); // ??????

	D3DXMatrixTranslation(&doorMoveMatrix[1], 600.0f, 260.0f, 585.0f);  // ??????

	D3DXMatrixTranslation(&doorMoveMatrix[2], -700.0f, 260.0f, 585.0f); // ??????

	D3DXMatrixTranslation(&doorMoveMatrix[3], 600.0f, 260.0f, -585.0f);  // ??????

	D3DXMatrixTranslation(&doorMoveMatrix[4], -1900.0f, 260.0f, -585.0f);  // ??????

	D3DXMatrixTranslation(&doorMoveMatrix[5], -1900.0f, 260.0f, 585.0f);  // ??????

	//?????? ??????

	D3DXMatrixTranslation(&doorMoveMatrix[6], 0.0f, 130.0f, -1400.0f);
	D3DXMatrixTranslation(&doorMoveMatrix[7], 0.0f, 130.0f, 1400.0f);

	D3DXMatrixTranslation(&doorMoveMatrix[8], -1300.0f, 130.0f, -1400.0f);
	D3DXMatrixTranslation(&doorMoveMatrix[9], -1300.0f, 130.0f, 1400.0f);

	//????????
	D3DXMatrixRotationY(&doorRotateMatrix[0], 3.141592f); // 180?? ????
	D3DXMatrixRotationY(&doorRotateMatrix[1], 1.5708f); // 90?? ????
	D3DXMatrixRotationY(&doorRotateMatrix[2], 4.71239f); // 270?? ????
	//?? 2 ???? ?? ????????

	D3DXMatrixTranslation(&Map2MoveMatrix, -1300.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&Map2Scaling, 0.3f, 0.3f, 0.3f);
	D3DXMatrixMultiply(&Map2Matrix, &Map2MoveMatrix, &Map2Scaling);


	//?? ???? ??????

	D3DXMatrixScaling(&worldMatrix[9], 0.3f, 0.3f, 0.3f);
	D3DXMatrixScaling(&doorScalingMatrix, 0.3f, 0.3f, 0.3f);

	// ??????

	D3DXMatrixScaling(&ElectricScaling, 2.5f, 2.5f, 2.5f);
	D3DXMatrixTranslation(&ElectricMoveMatrix, -135.0f, 20.0f, -165.0f);
	D3DXMatrixMultiply(&ElectricMatrix, &ElectricMoveMatrix, &ElectricScaling);

	//m_D3D->SetWorldMatrix(worldMatrix1);
	// ?? ???? ??????

	D3DXMatrixMultiply(&doorMatrix[0], &doorMoveMatrix[0], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[1], &doorMoveMatrix[1], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[2], &doorMoveMatrix[2], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[3], &doorMoveMatrix[3], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[4], &doorMoveMatrix[4], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[5], &doorMoveMatrix[5], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[6], &doorMoveMatrix[6], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[7], &doorMoveMatrix[7], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[8], &doorMoveMatrix[8], &doorScalingMatrix);
	D3DXMatrixMultiply(&doorMatrix[9], &doorMoveMatrix[9], &doorScalingMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// Map1-3
	m_Map[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Map[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map[0]->GetIndexCount(), worldMatrix[9], viewMatrix, projectionMatrix1,
		*m_Map[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Map[1]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Map[1]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map[1]->GetIndexCount(), worldMatrix[9], viewMatrix, projectionMatrix1,
		*m_Map[1]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Map[2]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Map[2]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map[2]->GetIndexCount(), worldMatrix[9], viewMatrix, projectionMatrix1,
		*m_Map[2]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	// ??2 ??????

	m_Map[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Map[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map[0]->GetIndexCount(), Map2Matrix, viewMatrix, projectionMatrix1,
		*m_Map[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Map[1]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Map[1]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map[1]->GetIndexCount(), Map2Matrix, viewMatrix, projectionMatrix1,
		*m_Map[1]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Map[2]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Map[2]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map[2]->GetIndexCount(), Map2Matrix, viewMatrix, projectionMatrix1,
		*m_Map[2]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorMatrix[0], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorMatrix[4], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorMatrix[5], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[0] * doorMatrix[3], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[0] * doorMatrix[1], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[0] * doorMatrix[2], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	// ?????? ??????

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();
	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[2] * doorMatrix[6], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	if (gameClear)
	{
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), ElectricMatrix, viewMatrix, projectionMatrix1,
			*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}
	else
	{
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[1] * doorMatrix[7], viewMatrix, projectionMatrix1,
			*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[2] * doorMatrix[8], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Door[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Door[0]->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door[0]->GetIndexCount(), doorRotateMatrix[1] * doorMatrix[9], viewMatrix, projectionMatrix1,
		*m_Door[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Electric->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Electric->GetIndexCount();

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Electric->GetIndexCount(), doorRotateMatrix[0] * ElectricMatrix, viewMatrix, projectionMatrix1,
		*m_Electric->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->TurnZBufferOff();

	m_D3D->GetWorldMatrix(worldMatrix[10]);

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix[10], viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}


	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix[10], orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	D3DXMatrixScaling(&worldMatrixFireSca[0], 55.0f, 40.0f, 1.0f);
	D3DXMatrixRotationY(&worldMatrixFireRot[0], (m_Camera->GetRotation().y + 1.57f) * 0.0174532925f);
	D3DXMatrixMultiply(&worldMatrixFire[0], &worldMatrixFireSca[0], &worldMatrixFireRot[0]);
	D3DXMatrixTranslation(&worldMatrixFireTrs[0], 50.0f, 40.0f, -380.0f);
	worldMatrixFire[0] *= worldMatrixFireTrs[0];

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Fire[0]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Fire[0]->GetIndexCount();

	// Render the square model using the fire shader.
	result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_Fire[0]->GetIndexCount(), worldMatrixFire[0], viewMatrix, projectionMatrix,
		m_Fire[0]->GetTexture1(), m_Fire[0]->GetTexture2(), m_Fire[0]->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);

	if (!result)
	{
		return false;
	}

	D3DXMatrixScaling(&worldMatrixFireSca[1], 55.0f, 40.0f, 1.0f);
	D3DXMatrixRotationY(&worldMatrixFireRot[1], (m_Camera->GetRotation().y + 1.57f) * 0.0174532925f);
	D3DXMatrixMultiply(&worldMatrixFire[1], &worldMatrixFireSca[1], &worldMatrixFireRot[1]);
	D3DXMatrixTranslation(&worldMatrixFireTrs[1], -435.0f, 40.0f, -380.0f);
	worldMatrixFire[1] *= worldMatrixFireTrs[1];

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Fire[1]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Fire[1]->GetIndexCount();

	// Render the square model using the fire shader.
	result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_Fire[1]->GetIndexCount(), worldMatrixFire[1], viewMatrix, projectionMatrix,
		m_Fire[1]->GetTexture1(), m_Fire[1]->GetTexture2(), m_Fire[1]->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);

	if (!result)
	{
		return false;
	}

	D3DXMatrixScaling(&worldMatrixFireSca[2], 55.0f, 40.0f, 1.0f);
	D3DXMatrixRotationY(&worldMatrixFireRot[2], (m_Camera->GetRotation().y + 1.57f) * 0.0174532925f);
	D3DXMatrixMultiply(&worldMatrixFire[2], &worldMatrixFireSca[2], &worldMatrixFireRot[2]);
	D3DXMatrixTranslation(&worldMatrixFireTrs[2], -325.0f, 40.0f, 0.0f);
	worldMatrixFire[2] *= worldMatrixFireTrs[2];

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Fire[2]->Render(m_D3D->GetDeviceContext());
	num_of_objects++;
	num_of_polygons += m_Fire[2]->GetIndexCount();

	// Render the square model using the fire shader.
	result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_Fire[2]->GetIndexCount(), worldMatrixFire[2], viewMatrix, projectionMatrix,
		m_Fire[2]->GetTexture1(), m_Fire[2]->GetTexture2(), m_Fire[2]->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);

	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

CameraClass* GraphicsClass::GetCamera()
{
	return m_Camera;
}
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

#define WINDOW_CLASS    "UGPDX"
#define WINDOW_NAME     "D3D Texture Mapping"
#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

// Function Prototypes...
bool InitializeD3D(HWND hWnd, bool fullscreen);
bool InitializeObjects();
void RenderScene();
void Shutdown();


// Direct3D object and device.
LPDIRECT3D9 g_D3D = NULL;
LPDIRECT3DDEVICE9 g_D3DDevice = NULL;

// Matrices.
D3DXMATRIX g_projection;
D3DXMATRIX g_ViewMatrix;

// Vertex buffer to hold the geometry.
LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;

// Holds a texture image.
LPDIRECT3DTEXTURE9 g_Texture = NULL;

// A structure for our custom vertex type
struct stD3DVertex
{
    float x, y, z;
    unsigned long color;
    float tu, tv;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch(msg)
      {
         case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            break;

         case WM_KEYUP:
            if(wParam == VK_ESCAPE) PostQuitMessage(0);
            break;
      }

   return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPSTR cmdLine, int show)
{
   // Register the window class
   WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                     GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                     WINDOW_CLASS, NULL };
   RegisterClassEx(&wc);

   // Create the application's window
   HWND hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW, 100, WINDOW_WIDTH, WINDOW_HEIGHT, GetDesktopWindow(), NULL, wc.hInstance, NULL);

   // Initialize Direct3D
   if(InitializeD3D(hWnd, false))
      {
         // Show the window
         ShowWindow(hWnd, SW_SHOWDEFAULT);
         UpdateWindow(hWnd);

         // Enter the message loop
         MSG msg;
         ZeroMemory(&msg, sizeof(msg));

         while(msg.message != WM_QUIT)
            {
               if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
                  {
                     TranslateMessage(&msg);
                     DispatchMessage(&msg);
                  }
               else
                  RenderScene();
            }
      }

   // Release any and all resources.
   Shutdown();

   // Unregister our window.
   UnregisterClass(WINDOW_CLASS, wc.hInstance);
   return 0;
}


bool InitializeD3D(HWND hWnd, bool fullscreen)
{
   D3DDISPLAYMODE displayMode;

   // Create the D3D object.
   g_D3D = Direct3DCreate9(D3D_SDK_VERSION);
   if(g_D3D == NULL) return false;

   // Get the desktop display mode.
   if(FAILED(g_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
      return false;

   // Set up the structure used to create the D3DDevice
   D3DPRESENT_PARAMETERS d3dpp;
   ZeroMemory(&d3dpp, sizeof(d3dpp));

   if(fullscreen)
      {
         d3dpp.Windowed = FALSE;
         d3dpp.BackBufferWidth = WINDOW_WIDTH;
         d3dpp.BackBufferHeight = WINDOW_HEIGHT;
      }
   else
      d3dpp.Windowed = TRUE;
   d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
   d3dpp.BackBufferFormat = displayMode.Format;

   // Create the D3DDevice
   if(FAILED(g_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
             D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_D3DDevice)))
      {
         return false;
      }

   // Initialize any objects we will be displaying.
   if(!InitializeObjects()) return false;

   return true;
}


bool InitializeObjects()
{
   // Fill in our structure to draw an object.
   // x, y, z, color, texture coords.
   stD3DVertex objData[] =
      {
         {-0.3f, -0.4f, 0, D3DCOLOR_XRGB(255,255,255), 0, 1},
         {0.3f, -0.4f, 0, D3DCOLOR_XRGB(255,255,255), 1, 1},
          {0.3f, 0.4f, 0, D3DCOLOR_XRGB(255,255,255), 1, 0},

          {0.3f, 0.4f, 0, D3DCOLOR_XRGB(255,255,255), 1, 0},
         {-0.3f, 0.4f, 0, D3DCOLOR_XRGB(255,255,255), 0, 0},
          {-0.3f, -0.4f, 0, D3DCOLOR_XRGB(255,255,255), 0, 1}
      };

   // Create the vertex buffer.
   if(FAILED(g_D3DDevice->CreateVertexBuffer(sizeof(objData), 0,
             D3DFVF_VERTEX, D3DPOOL_DEFAULT,
             &g_VertexBuffer, NULL))) return false;
   
   // Fill the vertex buffer.
   void *ptr;

   if(FAILED(g_VertexBuffer->Lock(0, sizeof(objData),
      (void**)&ptr, 0))) return false;

   memcpy(ptr, objData, sizeof(objData));

   g_VertexBuffer->Unlock();


   // Load the texture image from file.
   if(D3DXCreateTextureFromFile(g_D3DDevice, "ugp.tga",&g_Texture) != D3D_OK) return false;

   // Set the image states to get a good quality image.
   // ���÷Ŵ������Ϊ���Թ�����
    g_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    // ������С������Ϊ���Թ�����
    g_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // Set default rendering states.
   g_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    g_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

   // Set the projection matrix.
   D3DXMatrixPerspectiveFovLH(&g_projection, 45.0f,
      WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.0f);

   g_D3DDevice->SetTransform(D3DTS_PROJECTION, &g_projection);

   // Define camera information.
   D3DXVECTOR3 cameraPos(0.0f, 0.0f, -1.0f);
   D3DXVECTOR3 lookAtPos(0.0f, 0.0f, 0.0f);
   D3DXVECTOR3 upDir(0.0f, 1.0f, 0.0f);

   // Build view matrix.
   D3DXMatrixLookAtLH(&g_ViewMatrix, &cameraPos,
                      &lookAtPos, &upDir);

   return true;
}


void RenderScene()
{
   // Clear the backbuffer.
   g_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET,
                      D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

   // Begin the scene.  Start rendering.
   g_D3DDevice->BeginScene();

      // Apply the view (camera).
      g_D3DDevice->SetTransform(D3DTS_VIEW, &g_ViewMatrix);

      // Draw square.
      g_D3DDevice->SetTexture(0, g_Texture);
      g_D3DDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(stD3DVertex));
      g_D3DDevice->SetFVF(D3DFVF_VERTEX);
      g_D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

   // End the scene.  Stop rendering.
   g_D3DDevice->EndScene();

   // Display the scene.
   g_D3DDevice->Present(NULL, NULL, NULL, NULL);
}


void Shutdown()
{
   if(g_D3DDevice != NULL) g_D3DDevice->Release();
   g_D3DDevice = NULL;

   if(g_D3D != NULL) g_D3D->Release();
   g_D3D = NULL;

   if(g_VertexBuffer != NULL) g_VertexBuffer->Release();
   g_VertexBuffer = NULL;

   if(g_Texture != NULL) g_Texture->Release();
   g_Texture = NULL;
}

/*
����һ������һ���豸��
HRESULT SetTexture(      
DWORD Stage,
IDirect3DBaseTexture9 *pTexture
);
����(Parameters)
Stage
[in] Stage identifier to which the texture is set. Stage identifiers are zero-based. The maximum 
number of stages supported is determined from two caps: D3DCAPS.MaxSimultaneousTextureStages and 
D3DCAPS9.MaxTextureBlendingStages.
Displacement Mapping uses a special stage index, called D3DDDMAPSAMPLER.
Vertex Textures use a special stage index called D3DVERTEXTEXTURESAMPLER.

[in(�û�����������ֵ)]��־Ҫ����������豸��,��0��ʼ.֧�ֵ�����豸������������־����:

D3DCAPS.MaxSimultaneousTextureStages �� D3DCAPS9.MaxTextureBlendingStages.

λ��ӳ�� ʹ������Ĳ�����,��Ϊ D3DDDMAPSAMPLER

�������� ʹ������Ĳ�����,��Ϊ D3DVERTEXTEXTURESAMPLER

pTexture
[in] Pointer to an IDirect3DBaseTexture9 interface, representing the texture being set.

IDirect3DBaseTexture9��ָ��,����Ҫ���õ�����
����ֵ(Return Value)

If the method succeeds, the return value is D3D_OK.

If the method fails, the return value can be D3DERR_INVALIDCALL.

����÷����ɹ�,����ֵ��D3D_OK

����÷���ʧ��,����ֵ������D3DERR_INVALICALL

��ע(Remarks)

IDirect3DDevice9::SetTexture is not allowed if the texture is created with a pool type of D3DPOOL_SCRATCH. 
IDirect3DDevice9::SetTexture is not allowed with a pool type of D3DPOOL_SYSTEMMEM texture unless DevCaps is set with D3DDEVCAPS_TEXTURESYSTEMMEMORY.

IDirect3DDevice9::SetTexture ������(����)����������D3DPOOL_SCRATCH���ͳش����Ļ�.

ͬ��D3DPOOL_SYSTEMMEM�����ʹ���������Ҳ������,����DevCaps����ΪD3DDEVCAPS_TEXTURESYSTEMMEMORY.


����IDirect3DDevice9::SetSamplerState()���ɷֱ�����������˵ķŴ����������С��������
����һ����������Ϊ����������������������ţ�0~7�������Ҫ���÷Ŵ���������ڶ���
������ΪD3DSAMP_MAGFILTER�����Ҫ������С���������ڶ���������ΪD3DSAMP_MINFILTER����
������������Ϊ��ʾ����������ö�ٳ���D3DTEXF_POINT�����д��뽫�����0��������˷�ʽ
����Ϊ����������
g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

�������Ĵ�С����ĻͼԪ��ʵ�ʴ�С��������ô������������������ͼ��������Ӱ�첻��
���ǣ������С���̫�࣬�ͻή��ͼ�񾫶ȣ��Ӷ�Ӱ��ͼ������������ɫ�����˸��ʧ������
*/
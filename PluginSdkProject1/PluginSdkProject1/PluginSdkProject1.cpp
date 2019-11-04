#include "plugin.h"
#include "CTimer.h"
#include "CHud.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include <d3d9.h>

using namespace plugin;

bool rendererActive;
bool rendererLost;

void InitializeRender();

class PluginSdkProject1 {
public:
    PluginSdkProject1() {
		static int keyPressTime = 0;
		
		// Our state
		static bool show_demo_window = false;

		static IDirect3DDevice9* g_pd3dDevice = NULL;
		static ImGuiContext* context = NULL;

		Events::initGameEvent += [] {
			
			
		};

		Events::gameProcessEvent += [] {

			if (FindPlayerPed() && KeyPressed(VK_F9) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;
				show_demo_window = !show_demo_window;
			}

		};

		Events::drawHudEvent += [] {
			
			if (!rendererActive) {

				InitializeRender();

			} else if (rendererActive && !rendererLost) {

				ImGui::SetCurrentContext(ImGui::GetCurrentContext());

				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				if (show_demo_window) {

					ImGui::ShowDemoWindow(&show_demo_window);
					//ImGui::Begin("Hello, world!");	// Create a window called "Hello, world!" and append into it.
					//ImGui::Text("Hello world!");	// Display some text (you can use a format strings too)
					//ImGui::End();

				}

				//ImGui::EndFrame();

				ImGui::SetCurrentContext(ImGui::GetCurrentContext());

				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

			}

		};

		Events::d3dLostEvent += [] {
			if (rendererActive && !rendererLost) {
				//ImGui::SetCurrentContext(ImGui::GetCurrentContext());
				ImGui_ImplDX9_InvalidateDeviceObjects();
				rendererLost = true;
			}
		};

		Events::d3dResetEvent += [] {
			if (rendererActive) {
				rendererLost = false;
			}
		};
		
    }
} pluginSdkProject1;

// Read this holy shiet:
// https://blast.hk/threads/19292/
// https://translate.google.co.ve/translate?hl=es&sl=auto&tl=en&u=https%3A%2F%2Fblast.hk%2Fthreads%2F19292%2F
// source: https://gtaforums.com/topic/910061-in-game-24h-timecycle-editor/?tab=comments#comment-1070716268

void InitializeRender() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGui_ImplWin32_Init(RsGlobal.ps->window);
	ImGui_ImplDX9_Init(GetD3DDevice());

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	rendererActive = true;
	rendererLost = false;

	ShowCursor(true);
}
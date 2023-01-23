#include "UIManager.h"
#include "..\imgui\imgui_impl_glfw.h"
#include "..\imgui\imgui_impl_opengl3.h"
#include "OpenGLDevice.h"
#include "Define.h"

#include <sstream>
#include <iomanip>

SINGLETON_FUNCTION(UIManager)
USING(Engine)
USING(ImGui)
USING(std)

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	DestroyContext();
}

void UIManager::RenderUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();

	//ImVec2 screen = ImVec2((_float)COpenGLDevice::GetInstance()->GetWidthSize(), (_float)COpenGLDevice::GetInstance()->GetHeightSize());
	ImVec2 screen = ImVec2(350.f, 275.f);
	SetNextWindowPos(ImVec2(0.f, 0.f));
	SetNextWindowSize(screen);
	if (Begin("Key Info", (bool*)0,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse))
		//ImGuiWindowFlags_NoBackground |
		//ImGuiWindowFlags_NoTitleBar))
	{
		Text("F1 : Zoom in");
		Text("F2 : Zoom out");
		Text("WASD : Move player");
		Text("QE : Rotate player");
		Text("Left Shift : Speed up/down (toggle)");
		Text("R : Reset positions of all AIs");
		Text(" ");
		Text("F3 : Active All AIs");
		Text("F4 : Deactive All AIs");
		Text("F5 : Toogle Seek (RED)");
		Text("F6 : Toogle Flee (BLUE)");
		Text("F7 : Toogle Pursue (YELLOW)");
		Text("F8 : Toogle Evade (GREEN)");
		Text("F9 : Toogle Approach (PURPLE)");
	}
	End();

	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

RESULT UIManager::Ready()
{
	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& io = GetIO();

	if (!ImGui_ImplGlfw_InitForOpenGL(COpenGLDevice::GetInstance()->GetWindow(), true) ||
		!ImGui_ImplOpenGL3_Init("#version 460"))
		return PK_ERROR_IMGUI;
	StyleColorsDark();

	return PK_NOERROR;
}
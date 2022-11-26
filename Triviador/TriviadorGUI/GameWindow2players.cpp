#include "GameWindow2players.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TriviadorGUI::GameWindow2players form;
	Application::Run(% form);
}



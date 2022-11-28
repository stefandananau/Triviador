#include "GameWindow4players.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TriviadorGUI::GameWindow4players form;
	Application::Run(% form);
}

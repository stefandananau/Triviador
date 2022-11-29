#include "../TriviadorGUI/MainWindow.h"

using namespace System;
using namespace System::Windows::Forms; 

[STAThreadAttribute]
int main() {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TriviadorGUI::MainWindow form;
	Application::Run(% form);

}

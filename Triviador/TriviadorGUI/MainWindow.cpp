#include "MainWindow.h"
//
//#include <crow.h>
//#include <string>
//#include <cpr/cpr.h>

 using namespace System;
 using namespace System::Windows::Forms;
 [STAThreadAttribute]
 void main(array<String^>^ args) {
 	Application::EnableVisualStyles();
 	Application::SetCompatibleTextRenderingDefault(false);
 	TriviadorGUI::MainWindow form;
 	Application::Run(% form);
 }


#pragma once
#include <vector>
namespace TriviadorGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	

	/// <summary>
	/// Summary for GameWindow
	/// </summary>
	public ref class GameWindow : public System::Windows::Forms::Form
	{
	public:
		GameWindow(void)
		{
			
			InitializeComponent();
			
			this->timer1->Interval = 700;
			timer1->Start();
		}
		
		
		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GameWindow::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &GameWindow::timer1_Tick);
			// 
			// GameWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DodgerBlue;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1088, 676);
			this->Name = L"GameWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GameWindow";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &GameWindow::GameWindow_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void GameWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GameWindow::typeid));
		int index = DateTime::Now.Second % 5;
		switch (index)
		{
		case 0:
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"water-2")));
			break;
		case 1:
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"water-3")));
			break;
		case 2:
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"water-4")));
			break;
		case 3:
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"water-5")));
			break;
		case 4:
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"water-6")));
			break;
		default:
			break;
		}
	}
	};
	
}
